#include <stdio.h>
#include <zlib.h>

int main()
{
//ԭʼ����
	const unsigned char strSrc[]="hello world!\n\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd���Ĳ��� ���Ĳ���\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd���Ĳ��� ���Ĳ���\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd���Ĳ��� ���Ĳ���\
	aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd���Ĳ��� ���Ĳ���";

	unsigned char buf[1024]={0},strDst[1024]={0};
	unsigned long srcLen=sizeof(strSrc),bufLen=sizeof(buf),dstLen=sizeof(strDst);

	printf("Src string:%s\nLength:%d\n",strSrc,srcLen);
	//ѹ��
	compress(buf,&bufLen,strSrc,srcLen);
	printf("\nAfter Compressed Length:%d\n",bufLen);
	printf("Compressed String:%s\n",buf);

	//��ѹ��
	uncompress(strDst,&dstLen,buf,bufLen);
	printf("\nAfter UnCompressed Length:%d\n",dstLen);
	printf("UnCompressed String:%s\n",strDst);
	return 0;
}

