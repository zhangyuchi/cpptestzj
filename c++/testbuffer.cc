#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <vector>

#define IN
#define INOUT
#define OUT

template<class T>
void printvec(std::vector<T> &vecT)
{
    std::cout<<"printvec:"<<std::endl;    
    for(size_t i=vecT.size(); i>0; --i)
    {
        std::cout<<vecT[i-1]<<std::endl;
    }
    std::cout<<"printvec done"<<std::endl;    
}

template<class T>
const uint8_t* buffer_to_type(IN const uint8_t* buffer, INOUT uint32_t& buflen, OUT T& v)
{
    size_t outlen = sizeof(T);
    if ( buflen < outlen )
        return NULL;

    printf("v is %p\n", v);
    printf("v address is %p\n", &v);

    memcpy(&v, buffer, outlen);
    buflen = buflen - outlen;
    return buffer + outlen;
}

template<class T>
const uint8_t* buffer_to_type(IN const uint8_t* buffer, INOUT uint32_t& buflen, OUT std::vector<T>& vec)
{
    uint32_t vector_size=0;
    const uint8_t *rest = buffer_to_type(buffer, buflen, vector_size);
    if ( !rest )
        return rest;

    typename std::vector<T>::iterator it = vec.begin();

    for(uint32_t i=0; i<vector_size; ++i)
    {
        T v;
        rest = buffer_to_type(rest, buflen, v);
        if ( !rest )
            return rest;
        it = vec.insert(it,v);
    }

    return rest;
}

template<class T1, class T2>
inline const uint8_t* buffer_to_type(IN const uint8_t* buffer, INOUT uint32_t& buflen, OUT std::pair<T1,T2>& pair)
{
    T1 v1;
    const uint8_t *rest = buffer_to_type(buffer, buflen, v1);
    if ( !rest )
        return rest;

    T2 v2;
    rest = buffer_to_type(rest, buflen, v2);
    if ( !rest )
        return rest;

    pair.first = v1;
    pair.second = v2;

    return rest;
}

template<>
const uint8_t* buffer_to_type(IN const uint8_t* buffer, INOUT uint32_t& buflen, OUT std::string& v)
{
    uint32_t vlen=0,offset=0;
    memcpy(&vlen, buffer+offset, 4);
    offset += 4;
    if (vlen >= buflen-offset)
        return NULL;

    v.assign(reinterpret_cast<const char*>(buffer+offset), vlen);
    offset += vlen;
    buflen -= offset;
    return buffer + offset;
}

int main()
{
    char buf[5];
    char data[] = "hello the world";
    int intdata[4] = {1,2,3,4};

    uint32_t len = 10;
    buffer_to_type(reinterpret_cast<const uint8_t*>(data), len, buf);
    printf("buf is %s\n", buf);

    uint8_t  buffer[256];
    uint32_t buffer_len = 256;
    len = 8;
    memcpy(buffer, &len, 4);
    memcpy(buffer+4, data, 10);

    std::string word;
    buffer_to_type(buffer, buffer_len, word);
    std::cout<<word<<std::endl;

    std::cout<<"inidata size is "<<sizeof(intdata)<<std::endl;

    memset(buffer, 0, 256);
    len = 4;
    memcpy(buffer, &len, 4);
    memcpy(buffer+4, (char *)&intdata, sizeof(intdata));

    std::vector<int> intv; 
    buffer_to_type(buffer, buffer_len, intv);
    printvec(intv); 


    memset(buffer, 0, 256);
    len = 4;
    memcpy(buffer, &len, 4);
    len = 4;    
    memcpy(buffer+4, &len, 4);    
    memcpy(buffer+8, "abcd", 4);
    memcpy(buffer+12, &len, 4);    
    memcpy(buffer+16, "efgh", 4);
    memcpy(buffer+20, &len, 4);    
    memcpy(buffer+24, "ijkl", 4);
    memcpy(buffer+28, &len, 4);    
    memcpy(buffer+32, "mnop", 4);

    std::vector<std::string> strv; 
    buffer_to_type(buffer, buffer_len, strv);
    printvec(strv); 

    memset(buffer, 0, 256);
    len = 4;
    memcpy(buffer, &len, 4);
    len = 8;
    memcpy(buffer+4, &len, 4);
    memcpy(buffer+8, data, 10);
    std::pair<int,std::string> pair;
    buffer_to_type(buffer, buffer_len, pair);
    
    std::cout<<pair.first<<"-"<<pair.second<<std::endl;

    return 0;
}

