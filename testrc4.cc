/*
 * =============================================================================
 *
 *       Filename:  testrc4.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月23日 18时07分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */

#include <stdint.h>
#include <stdio.h>
#include <openssl/rc4.h>
#include <string.h>

int main()
{
    uint8_t key[17] = "1548701915487469";
    uint8_t plain[] = "hello"; 
    uint8_t enc[32];
    uint8_t data[32];
    
    memset(data, 0, 32);
    memset(enc, 0, 32);

    printf("plain is %s\n", plain);
    RC4_KEY rc4_key;    
    RC4_set_key( &rc4_key, 16, key);
    RC4( &rc4_key, 5, plain, plain );
    printf("plain is %s\n", plain);
    RC4_set_key( &rc4_key, 16, key);
    RC4( &rc4_key, 5, plain, plain );

    printf("plain is %s\n", plain);
    //printf("enc is %s\n", enc);
    //printf("data is %s\n", data);

    return 0;
}

