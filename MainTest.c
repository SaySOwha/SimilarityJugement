#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"                //���ù�ϣ�ṹͷ�ļ�
#include "Trie.h"                //���ü����ṹͷ�ļ�
void chengxu();
int main()
{

	//**********************************��ȡ�ļ��е�C���Թؼ���*****************
	char keywords[32][10];                                   //����һ���洢�ؼ��ֵĶ�ά����
	FILE *fp;                                                //�����ļ�ָ��
	fp = fopen("keywords.txt", "r");                         //�򿪴洢C���Թؼ��ֵ��ļ����ҹ涨Ϊֻ��
	if (fp == NULL)                                          //����ļ�ָ��ָ��Ϊ��
	{
		printf("open file error!\n");                        //��ӡ��ʾ�ַ���
		return -1;                                           //����-1
	}
	for (int i = 0; i < 32; i++)                             //ѭ����ȡ�����Ʋ�����32��
	{
		if (fscanf(fp, "%s", keywords[i]) != 1)              //����ÿ�����ʲ�����20��
			break;
	}
	fclose(fp);                                              //�ر��ļ�ָ��
	int m = 0;
	printf("C�����еĹؼ����У�\n");                         //��ӡC���Թؼ���
	for (int j = 0; j < 32; j++)
	{                                                        
		printf("%2d:%10s|      ", ++m, keywords[j]);         //����ָ����ʽ�����ź͹ؼ���
		if ((j + 1) % 4 == 0)
			printf("\n");
	}

	//***********************************��C�����еĹؼ��ֽ�������*************************
	printf("\n��C�����еĹؼ��ֽ���������\n");               //��ӡ��ʾ�ַ�
	//char str[10];                                            //�����ַ�����洢�ַ���
	Trie_node root = NULL;                                   //����һ�������ĸ��ڵ�
	root = CreateTrie();                                     //��ʼ��һ������
	if (root == NULL)                                        //������ڵ�ָ��Ϊ��  ����������ʧ��
		printf("����Trie��ʧ��\n");                          //��ӡ��ʾ�ַ�
	for (int i = 0; i < 32; i++)                             //ѭ���ڼ��������β���֮ǰ����洢�Ĺؼ���
	{
		insert_node(root, keywords[i]);                       
	}
	printf("Trie���ѽ������\n");                            //��ӡ��ʾ�ַ���
	/*
	printf("������Ҫ��ѯ���ַ���:\n");                        //�����ѯ
	scanf("%s", str);
	while (strcmp(str, "$") != 0)
	{
		if (search_str(root, str))
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
	*/
	//***********************************��C�����еĹؼ��ֽ�����ϣ��*************************
	printf("\n��C�����еĹؼ��ֽ�����ϣ��\n");             //��ӡ��ʾ�ַ���

	hash_table_init();                                       //��ʼ����ϣ��
	for (int i = 0; i < 32; i++)                             //ѭ���ڹ�ϣ�������β���ؼ���
	{


		hash_table_insert(keywords[i]);
	}
	printf("��ϣ���ѽ�����ɣ�����%d�����\n", hash_table_size);//��ӡ��ʾ�ַ���
	printf("�����ϣ��\n"); 
	hash_table_print();                                       //�����ϣ��
	/*
	printf("������Ҫ��ѯ���ַ���:\n");                        //�����ѯ
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
	*/

	//***********************************��CԴ����1���в�ѯ����*************************
	
	//��ȡ�������һ��Դ����                                  
	FILE * fp1;
	int ch1;
	if ((fp1 = fopen("chengxu1.txt", "r")) == NULL)
	{
		printf("�򿪲����ļ�ʧ��");
		exit(1);
	}
	
	char words1[10];
	int i = 0;
	while ((ch1 = getc(fp1)) != EOF)
	{
		if ((ch1 >= 'a') && (ch1 <= 'z'))
		{
			words1[i] = ch1;
			i++;
		}
		else if ((words1[0] >= 'a') && (words1[0] <= 'z'))
		{
			if (search_str(root, words1))
				hash_table_lookup(words1);
			i = 0;
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
			i = 0;
		}
	}
	if (fclose(fp1) != 0)
	{
		printf("�رղ����ļ�ʧ��");
		exit(1);
	}
	
	printf("\n��һ�������ѯ���Ĺ�ϣ��״̬Ϊ��\n");                      //��ӡ��ʾ�ַ���
	hash_table_print();                                                    //��ӡ��ϣ��

	printf("��һ�������Ƶ��Ϊ��\n\n");
	hash_table_nvalue();
	hash_table_revalue();
	
	//printf("\n���Ȩֵ���Ĺ�ϣ��״̬Ϊ��\n");                         //��ӡ��ʾ�ַ���
	//hash_table_print();                                                 //��ӡ��ϣ��
	
	hash_table_release();                                               //�ͷŹ�ϣ��Ĵ洢�ռ�     
	
	chengxu();
	return 0;
}



void chengxu()
{
	char keywords[32][10];                                   //����һ���洢�ؼ��ֵĶ�ά����
	FILE *fp;                                                //�����ļ�ָ��
	fp = fopen("keywords.txt", "r");                         //�򿪴洢C���Թؼ��ֵ��ļ����ҹ涨Ϊֻ��
	if (fp == NULL)                                          //����ļ�ָ��ָ��Ϊ��
	{
		printf("open file error!\n");                        //��ӡ��ʾ�ַ���
		return -1;                                           //����-1
	}
	for (int i = 0; i < 32; i++)                             //ѭ����ȡ�����Ʋ�����32��
	{
		if (fscanf(fp, "%s", keywords[i]) != 1)              //����ÿ�����ʲ�����20��
			break;
	}
	fclose(fp);                                              //�ر��ļ�ָ��

	//***********************************��C�����еĹؼ��ֽ�������*************************
	//printf("\n��C�����еĹؼ��ֽ���������\n");               //��ӡ��ʾ�ַ�
	//char str[10];                                            //�����ַ�����洢�ַ���
	Trie_node root = NULL;                                   //����һ�������ĸ��ڵ�
	root = CreateTrie();                                     //��ʼ��һ������
	if (root == NULL)                                        //������ڵ�ָ��Ϊ��  ����������ʧ��
		printf("����Trie��ʧ��\n");                          //��ӡ��ʾ�ַ�
	for (int i = 0; i < 32; i++)                             //ѭ���ڼ��������β���֮ǰ����洢�Ĺؼ���
	{
		insert_node(root, keywords[i]);
	}
	//printf("Trie���ѽ������\n");                            //��ӡ��ʾ�ַ���
	/*
	printf("������Ҫ��ѯ���ַ���:\n");                        //�����ѯ
	scanf("%s", str);
	while (strcmp(str, "$") != 0)
	{
		if (search_str(root, str))
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
	*/
	//***********************************��C�����еĹؼ��ֽ�����ϣ��*************************
	//printf("\n��C�����еĹؼ��ֽ�����ϣ��\n");             //��ӡ��ʾ�ַ���

	hash_table_init();                                       //��ʼ����ϣ��
	for (int i = 0; i < 32; i++)                             //ѭ���ڹ�ϣ�������β���ؼ���
	{


		hash_table_insert(keywords[i]);
	}
	//printf("��ϣ���ѽ�����ɣ�����%d�����\n", hash_table_size);//��ӡ��ʾ�ַ���
	//printf("�����ϣ��\n");
	//hash_table_print();                                       //�����ϣ��
	/*
	printf("������Ҫ��ѯ���ַ���:\n");                        //�����ѯ
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
	*/

	//***********************************��CԴ����1���в�ѯ����*************************

	//��ȡ������ڶ���Դ����                                  
	FILE * fp1;
	int ch1;
	if ((fp1 = fopen("chengxu2.txt", "r")) == NULL)
	{
		printf("�򿪲����ļ�ʧ��");
		exit(1);
	}

	char words1[10];
	int i = 0;
	while ((ch1 = getc(fp1)) != EOF)
	{
		if ((ch1 >= 'a') && (ch1 <= 'z'))
		{
			words1[i] = ch1;
			i++;
		}
		else if ((words1[0] >= 'a') && (words1[0] <= 'z'))
		{
			if (search_str(root, words1))
				hash_table_lookup(words1);
			i = 0;
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				words1[j] = '\0';
			}
			i = 0;
		}
	}
	if (fclose(fp1) != 0)
	{
		printf("�رղ����ļ�ʧ��");
		exit(1);
	}

	printf("\n�ڶ��������ѯ���Ĺ�ϣ��״̬Ϊ��\n");                      //��ӡ��ʾ�ַ���
	hash_table_print();                                                    //��ӡ��ϣ��

	printf("�ڶ��������Ƶ��Ϊ��\n");
	hash_table_nvalue();
	//hash_table_revalue();

	//printf("\n���Ȩֵ���Ĺ�ϣ��״̬Ϊ��\n");                         //��ӡ��ʾ�ַ���
	//hash_table_print();                                                 //��ӡ��ϣ��

	hash_table_release();                                               //�ͷŹ�ϣ��Ĵ洢�ռ�    
}