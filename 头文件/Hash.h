/*=================��ϣ���׼���׶Ρ������Ŷ�ַ����������̽����ɢ��=========================================*/

#define HASH_TABLE_MAX_SIZE 43//��ϣ��������ܸ���
typedef struct HashNode_Struct HashNode;//������ϣ��Ľ��ṹ

struct HashNode_Struct//д����ϣ��Ľ��ģ��
{
	char* sKey;//��ϣ����еĹؼ���
	int nValue;//��ϣ����е�Ȩֵ
	int conflict;//��¼��ͻ�Ĵ���
};

HashNode* hashTable[HASH_TABLE_MAX_SIZE]; //�����ϣ������ϣ����
int hash_table_size;  //������ϣ����ʵ������Ĵ�С

//��ʼ����ϣ��
void hash_table_init()
{
	hash_table_size = 0;//ʹ��ϣ���鳤��Ϊ0
	memset(hashTable, 0, sizeof(HashNode*) * HASH_TABLE_MAX_SIZE);//Ϊ��ϣ��������ڴ�ռ�
}


//�����ϣ����
int hash_table_hash_str(char* skey)
{
	char *p = skey;//����ָ��ָ��Ҫ���ݵ��ַ���
	int h;
	int i;//����һ���µ�intֵ
	for (i = 0; i < 10; i++)//��һ���ַ��ĳ��Ȳ���������ƶ�ָ��
		if (p[i] == '\0')//���ָ��ָ���˿յĵط�
			break;//����ѭ��
	h = ((p[0] - 97) * 100 + (p[i - 1] - 97)) % 41;//�����ϣֵ

	return h;//���ؼ�������������
}

//���������ϣ��
void hash_table_insert(char* skey)
{
	if (hash_table_size >= HASH_TABLE_MAX_SIZE)//�жϹ�ϣ���ʵ��Ԫ����Ŀ�Ƿ��Ѿ������˹�ϣ��Ĺ涨���鳤��
	{
		printf("out of hash table memory!\n");//��������ˣ��͸�����ʾ
		return;//���жϷ���
	}

	int pos = hash_table_hash_str(skey);//ͨ����ϣ�����������������

	HashNode* pHead = hashTable[pos];//����һ��ָ��ָ�������Ľ��
	int i = 1, j = 0, k = pos;
	while (pHead)//����������Ѿ���ռ����
	{
		if (strcmp(pHead->sKey, skey) == 0)//����������ֵ�������Ľ��ֵ���
		{
			printf("%s already exists!\n", skey);//�����ʾ�ַ���
			return;//�жϲ�����
		}
		//�������ж���̽��
		else if (j % 2 == 0) {
			//pHead = hashTable[pos + i * i];
			k = pos + i * i;
			if (k > HASH_TABLE_MAX_SIZE)
				k = k - HASH_TABLE_MAX_SIZE;
			pHead = hashTable[k];
			j++;
		}
		else
		{
			pHead = hashTable[pos - i * i];
			j++;
			k = pos - i * i;
			i++;
		}
	}

	HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));//����һ���µĽ�㲢Ϊ����������ռ�
	memset(pNewNode, 0, sizeof(HashNode));//����ָ��ռ�Ŷ
	pNewNode->sKey = (char*)malloc(sizeof(char) * (strlen(skey) + 1));//Ϊ���Ĺؼ��ַ��䶯̬�洢�ռ�
	strcpy(pNewNode->sKey, skey);//���ƴ������ַ������ոշ���Ľ��Ĺؼ���
	pNewNode->nValue = 0;//���������valueֵ�����ոս����Ľ���value
	pNewNode->conflict = j;//�����ȷ��Ҫ����һ�²��ܿ�����
	//pNewNode->pNext = hashTable[pos];//���·���Ľ��nextָ���ϣ�������еĶ�Ӧ����ַ-----ʵ���˽����һ�����ָ�����鱾��
	hashTable[k] = pNewNode;//����ϣ�������еĶ�Ӧ���ָ���µĽ��
	hash_table_size++;//��ϣ���ʵ�ʳ��ȼ�һ
}
/*
//�ڹ�ϣ��������ɾ��һ���ؼ���
void hash_table_remove(const char* skey)
{
	unsigned int pos = hash_table_hash_str(skey);//ͨ����ϣ�����������������
	if (hashTable[pos])//�����Ӧ��ϣֵ����ϵ�ֵ����
	{
		HashNode* pHead = hashTable[pos];//�����µ�ָ��ָ��ý��
		HashNode* pLast = NULL;//������һ����һ�����ָ��
		HashNode* pRemove = NULL;//����ɾ�����ָ��
		while (pHead)//���ָ��Ľ��һֱ����ֵ
		{
			if (strcmp(skey, pHead->sKey) == 0)//���Ҫɾ����ֵ��ý�������ֵ���
			{
				pRemove = pHead;//����������ɾ��ָ��ָ��ý��
				break;//����ѭ��
			}
			pLast = pHead;//����������һ������ָ��ָ��ýڵ�
			pHead = pHead->pNext;//�ýڵ�����ƶ�һλ
		}
		if (pRemove)//���ɾ��������ֵ
		{
			if (pLast)//�����һ��������ֵ
				pLast->pNext = pRemove->pNext;//��һ������nextָ��ָ��ɾ��������һ�����
			else
				hashTable[pos] = NULL;//��һ����㲻����ָ�룬��ֱ���ù�ϣ���ж�Ӧ�Ľ������ָ���

			free(pRemove->sKey);//�ͷ�Ҫɾ�����Ŀռ�
			free(pRemove);
		}
	}
}
*/
//�ڹ�ϣ���в���һ���ؼ���
HashNode* hash_table_lookup(char* skey)
{
	int pos = hash_table_hash_str(skey);//ͨ����ϣ�����������������;
	if (hashTable[pos])//�����Ӧ������ֵ
	{
		HashNode* pHead = hashTable[pos];//����һ���µĽ��ָ��ָ��ý��
		int i = 1, j = 0, k = pos;
		while (pHead)//����µĽ��ָ��ָ��Ľ���ֵ����
		{
			if (strcmp(skey, pHead->sKey) == 0)
			{//���Ҫ���ҵĹؼ�����ָ������¹ؼ������
				pHead->nValue++;
				return pHead;//���ظýڵ�
			}
			//�������ж���̽��
			else if (j % 2 == 0) {
				//pHead = hashTable[pos + i * i];
				j++;
				k = pos + i * i;
				if (k > HASH_TABLE_MAX_SIZE)
					k = k - HASH_TABLE_MAX_SIZE;
				pHead = hashTable[k];
			}
			else
			{
				pHead = hashTable[pos - i * i];
				j++;
				k = pos - i * i;
				i++;
			}
		}
	}
	return NULL;//�����Ӧ���ֵ�����ڣ��򷵻ؿ�ֵ
}

//��ӡ��ϣ���еĴ��ڵĽ��
void hash_table_print()
{
	printf(" ���     �ؼ��� Ƶ�� ��ͻ\n");//
	int i;//����һ��int���͵�ֵ
	for (i = 0; i < HASH_TABLE_MAX_SIZE; i++)//��ͷ������ϣ��Ľ������
	{
		HashNode* pHead = hashTable[i];//�����µĽ��ָ��ָ��ý��
		if (pHead)
		{
			printf("%4d=>", i);//��ӡ������		
			printf("%9s:%4d %4d", pHead->sKey, pHead->nValue, pHead->conflict);//��ӡ���Ĺؼ��ֺ�Ȩֵ
			//pHead = pHead->pNext;//ָ����һ�����		
			printf("\n");//��ӡ���з�
		}
	}
}

//�ͷ�������ϣ����ڴ�ռ�
void hash_table_release()
{
	int i;//����һ��intֵi
	for (i = 0; i < HASH_TABLE_MAX_SIZE; ++i)//��ͷ������ϣ��Ľ������
	{
		if (hashTable[i])//�����㲻ΪNULL
		{
			HashNode* pTemp = hashTable[i];//�����µĹ�ϣ���ָ��ָ��ý��
			if (pTemp)//��������õĹ�ϣ���ָ�벻ΪNULL
			{
				free(pTemp->sKey);//�ͷ�������Ŀռ��
				free(pTemp);
			}


		}
	}
}
//ʹ��ϣ���е�����ȨֵΪ0
void hash_table_revalue()
{
	int i;//����һ��int���͵�ֵ
	for (i = 0; i < HASH_TABLE_MAX_SIZE; i++)//��ͷ������ϣ��Ľ������
	{
		HashNode* pHead = hashTable[i];//�����µĽ��ָ��ָ��ý��
		if (pHead)
		{			
			pHead->nValue = 0;//ʹ����ȨֵΪ0
		}
	}
}

hash_table_nvalue()
{
	int i, j=0;//����һ��int���͵�ֵ
	for (i = 0; i < HASH_TABLE_MAX_SIZE; i++)//��ͷ������ϣ��Ľ������
	{
		HashNode* pHead = hashTable[i];//�����µĽ��ָ��ָ��ý��
		if (pHead)
		{		
			printf("%4d", pHead->nValue);//��ӡ���Ĺؼ��ֺ�Ȩֵ
			//pHead = pHead->pNext;//ָ����һ�����		
			j++;
			if (j % 8 == 0)
				printf("\n");//��ӡ���з�
		}
	}
}


/* ===============================��ϣ��Ĺ����Լ�ʵ�ֵĲ�������������=========================*/