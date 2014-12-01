#include <hiredis/hiredis.h>
#include <string>
#include <cstdio>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void myfree(void* reply)
{
  cout<<"myfree:"<<reply<<endl;
  freeReplyObject(reply);
}

class RedisConn 
{
public:
    RedisConn()
        :ctx_(NULL)
    {
      ctx_ = redisConnect("127.0.0.1", 6379);
    }
    
    ~RedisConn()
    {
      if ( ctx_ )
        redisFree(ctx_);        
    }

    boost::shared_ptr<redisReply> command(const char *format, ...)
    {
      va_list ap;
      va_start(ap,format);
      redisReply *reply = (redisReply *)redisvCommand(ctx_, format, ap);
      va_end(ap);
      if (reply )
        return boost::shared_ptr<redisReply>(reply, freeReplyObject);
      else
        return boost::shared_ptr<redisReply>();
    }

    redisContext* getCtx() const {return ctx_;}
    
private:
    redisContext *ctx_;
    
};

int main()
{
  RedisConn rc;

  vector<string> values{"101", "102", "103", "104"};
  string setcmd="SADD %d %b";

  std::for_each(values.begin(), values.end(), [&](const string& key){ 
      boost::shared_ptr<redisReply> reply = rc.command(setcmd.c_str(), 1001, key.data(), key.size());
      //redisReply *reply = (redisReply *)redisCommand(rc.getCtx(), "SET key %b", v, (size_t)sizeof(v));
      if ( REDIS_REPLY_INTEGER == reply->type )
        cout<<setcmd<<" reply: "<<reply->integer<<endl;
      if ( REDIS_REPLY_ERROR == reply->type || REDIS_REPLY_STRING == reply->type )
        cout<<setcmd<<" reply: "<<reply->str<<endl;
    }
  );

  cout<<"set end, begin get"<<endl;

  string getcmd="SMEMBERS 1001";
  boost::shared_ptr<redisReply> reply1 = rc.command(getcmd.c_str());
  if (reply1)
  {
  if ( REDIS_REPLY_INTEGER == reply1->type )
    cout<<getcmd<<" reply: "<<reply1->integer<<endl;
  if ( REDIS_REPLY_ERROR == reply1->type || REDIS_REPLY_STRING == reply1->type )
    cout<<getcmd<<" reply len: "<<reply1->len<<" reply: "<<reply1->str<<endl;
  if ( REDIS_REPLY_ARRAY == reply1->type ){
    for ( size_t i=0; i<reply1->elements; ++i){
      redisReply* reply = reply1->element[i];
      if ( REDIS_REPLY_INTEGER == reply->type )
        cout<<getcmd<<" reply: "<<reply->integer<<endl;
      if ( REDIS_REPLY_ERROR == reply->type || REDIS_REPLY_STRING == reply->type )
        cout<<getcmd<<" reply len: "<<reply->len<<" reply: "<<reply->str<<endl;
    }
  }
  }
  else
  {
    cout<<"reply is null, error is "<<rc.getCtx()->errstr<<endl;   
  }

  stringstream oss;
  oss<<100<<" "<<10989<<" "<<121<<" "<<122;
  string v = oss.str();
  cout<<v<<endl;

  stringstream iss;
  iss.str(v);
  int sid;
  int token;
  int uid1;
  int uid2;
  int uid3;
  iss>>sid>>token>>uid1>>uid2>>uid3;

  cout<<"sid:"<<sid<<" token:"<<token<<" uid1:"<<uid1<<" uid2:"<<uid2<<" uid3:"<<uid3<<endl;

  return 0;
}

