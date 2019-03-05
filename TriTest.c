#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Trie.h"
//#include"Hash.h"
//#include"Status.h"

void main()
{
	//****************��ȡ�ļ��е�C���Թؼ���*****************
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
		printf("%2d:%10s|      ", ++m,keywords[j]);
		if ((j + 1) % 4 == 0)
		printf("\n");
	}
	//****************��C�����еĹؼ��ֽ�������*************************
	printf("\n��C�����еĹؼ��ֽ���������\n");
	char str[20];
	Trie_node root = NULL;
	root = CreateTrie();
	if (root == NULL)
		printf("����Trie��ʧ��\n");
	for (int i = 0; i < 32; i++)
	{
		insert_node(root,keywords[i]);
	}
	printf("Trie���ѽ������\n");
	printf("������Ҫ��ѯ���ַ���:\n");
	while (scanf("%s", str) != NULL)
	{
		search_str(root, str);
	}
	//***************Դ�����ļ��Ķ�ȡ�͹�ϣ��Ľ���**********************
	
	return 0;
}
