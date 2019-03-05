#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"

/* ============================test function ============================*/

int main(int argc, char** argv)//��������
{
	//***************Դ�����ļ��Ķ�ȡ�͹�ϣ��Ľ���**********************
	char keywords[32][10];
	FILE *fp;//�����ļ�ָ��
	fp = fopen("keywords.txt", "r");//��һ���ļ����ҹ涨Ϊֻ��
	if (fp == NULL)
	{
		printf("open file error!\n");
		return -1;
	}
	for (int i = 0; i < 32; i++) //ѭ����ȡ�����Ʋ�����32��
	{
		if (fscanf(fp, "%s", keywords[i]) != 1) //����ÿ�����ʲ�����20��
			break;
	}
	fclose(fp);
	int m = 0;
	printf("C�����еĹؼ����У�\n");
	for (int j = 0; j < 32; j++) { //���������
		printf("%2d:%10s|      ", ++m, keywords[j]);
		if ((j + 1) % 4 == 0)
			printf("\n");
	}
	//****************��C�����еĹؼ��ֽ�����ϣ��*************************
	printf("\n��C�����еĹؼ��ֽ�����ϣ��\n");
	char str[10];
	hash_table_init();
	for (int i = 0; i < 32; i++)
	{


		hash_table_insert(keywords[i]);
	}
	printf("��ϣ���ѽ�����ɣ�����%d�����\n", hash_table_size);
	printf("�����ϣ��\n");
	hash_table_print();
	printf("������Ҫ��ѯ���ַ���:\n");
	scanf("%s", str);
	while (strcmp(str, "$") != 0)
	{
		if (hash_table_lookup(str))
		{
			printf("�ùؼ��ִ��ڣ�\n��������һ��Ҫ��ѯ�Ĺؼ��֣�(����$�˳�)\n");
			scanf("%s", str);
		}
		else
		{
		printf("�ùؼ��ֲ����ڣ�\n��������һ��Ҫ��ѯ�Ĺؼ��֣�(����$�˳�)\n");
		scanf("%s", str);
		}
	}
	printf("��ѯ���Ĺ�ϣ��״̬Ϊ��\n");
	hash_table_print();
	hash_table_release();
	return 0;
}