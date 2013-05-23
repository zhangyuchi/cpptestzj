#include <stdint.h>
#include <iostream>
#include <vector>

using namespace std;

struct userinfo
{
    uint32_t tim; 
    uint8_t status;
    uint8_t role;     
    uint32_t gname_len; 
    uint32_t accout_len;
    uint32_t jid_len; 
};

struct ConnToGroupDataUserListResp
{
    //ConnToGroupHdr head; //hcmd=GROUP_DATA
    uint32_t seq;
    uint16_t dcmd; //dcmd=26
    uint8_t  result;
    //uint32_t user_vec_len;
    vector<struct userinfo> user_vec;
};

int main()
{
	struct ConnToGroupDataUserListResp cg;

    cout<<"bool size is "<<sizeof(bool)<<endl;

    cout<<"0x02 size is "<<sizeof(0x02)<<endl;    
    cout<<"0x02L size is "<<sizeof(0x02L)<<endl;    

    uint64_t n64 = 0x01L;    
    uint32_t n32 = 123;

    cout<<"size_t(n64) = "<<size_t(n64)<<endl;
    cout<<"size_t(n32) = "<<size_t(n32)<<endl;

	return 0;
}

