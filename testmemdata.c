#include <glib.h>
int	main(int argc, char *argv[])
{
	GMemChunk *chunk;	//�����ڴ��
	gchar *mem[10];	//����ָ��ԭ�ӵ�ָ������
	gint i, j;
	//�����ڴ��
	chunk = g_mem_chunk_new("Test MemChunk", 5, 50, G_ALLOC_AND_FREE);
				//���ƣ�ԭ�ӵĳ��ȣ� �ڴ��ĳ��ȣ�����
	for(i=0; i<10; i++)
	{
		//��������
		//mem[i] = g_chunk_new(gchar, chunk);
		mem[i] = (gchar*)g_mem_chunk_alloc(chunk);
		for(j=0; j<5; j++)
		{
			mem[i][j] = 'A' + j;//Ϊ�ڴ���е�ָ�븳ֵ
		}
	}
	
	g_mem_chunk_print(chunk);	//��ʾ�ڴ����Ϣ
	for(i=0; i<10; i++)
	{
		g_print("%s\t",mem[i]);//��ʾ�ڴ���е�����
	}
	
	for(i=0; i<10; i++)
	{
		g_mem_chunk_free(chunk,mem[i]); //�ͷ����з�����ڴ�
	}
	g_mem_chunk_destroy(chunk);
}

