#include <stdint.h>
#include <iostream>
#include <vector>

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
    std::vector<struct userinfo> user_vec;
};

int main()
{
	struct ConnToGroupDataUserListResp cg;

    std::cout<<"bool size is "<<sizeof(bool)<<std::endl;

    std::cout<<"0x02 size is "<<sizeof(0x02)<<std::endl;    
    std::cout<<"0x02L size is "<<sizeof(0x02L)<<std::endl;    

    uint64_t n = 0x01L;    

	return 0;
}

