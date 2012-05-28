#include <stdio.h>
#include <zlib.h>

int main()
{
//原始数据
	const unsigned char strSrc[]="hello world!\n\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试";

	unsigned char buf[1024]={0},strDst[1024]={0};
	unsigned long srcLen=sizeof(strSrc),bufLen=sizeof(buf),dstLen=sizeof(strDst);

	printf("Src string:%s\nLength:%d\n",strSrc,srcLen);
	//压缩
	compress(buf,&bufLen,strSrc,srcLen);
	printf("\nAfter Compressed Length:%d\n",bufLen);
	printf("Compressed String:%s\n",buf);

	//解压缩
	uncompress(strDst,&dstLen,buf,bufLen);
	printf("\nAfter UnCompressed Length:%d\n",dstLen);
	printf("UnCompressed String:%s\n",strDst);
	return 0;
}

