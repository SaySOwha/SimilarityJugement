#define MAX_CHILD 26                          //�˺���ֻ��26��Ӣ����ĸ�����

typedef struct Tree                           //����Trie����ģ��
{
	int count;                                //������Ǹýڵ��Ǹ������γ�һ�����ʣ����count��=0����Ӹ��ڵ㵽�ýڵ��·�������γ�һ������
	struct Tree *child[MAX_CHILD];            //���������������
}Node, *Trie_node;

Node* CreateTrie()                             //����Trie����Ҷ�ӽ��ģ��
{
	Node *node = (Node*)malloc(sizeof(Node));  //ΪTrie����Ҷ�ӽ�����ռ�
	memset(node, 0, sizeof(Node));             //����ռ�
	return node;                               //����Ҷ�ӽ��ָ��
}

//Trie���Ľ�����
void insert_node(Trie_node root, char *str)      
{
	if (root == NULL || *str == '\0')          //������ڵ�ΪNULL�����ַ���Ϊ��
		return;                                //�жϲ��벢����
	Node *t = root;                            //����һ��ָ�������ָ��
	char *p = str;                             //����һ��ָ���ַ�����ָ��
	while (*p != '\0')                         //�����ָ����ַ���Ϊ��β���ַ�
	{
		if (t->child[*p - 'a'] == NULL)        //��������ĺ����������ĸΪ�׵Ľ��Ϊ��
		{
			Node *tmp = CreateTrie();          //����һ�����
			t->child[*p - 'a'] = tmp;          //�����ӽ��ָ�������������Ҷ�ӽ��
		}
		t = t->child[*p - 'a'];                //ָ��ָ���ӽڵ�
		p++;                                   //�ַ���ָ�����
	}
	t->count++;                                //��Ǹý��Ϊ1��������ָ���ַ�����ָ��
}

int search_str(Trie_node root, char *str)             //���Ҵ��Ƿ��ڸ�trie����
{
	if (NULL == root || *str == '\0')                  //���Trie��Ϊ�ջ��ߴ����ҵ��ַ���Ϊ��
	{
		printf("trie is empty or str is null\n");      //��ӡ��ʾ
		return 0;                                        //�жϲ�����
	}

	char *p = str;                                      //��������ָ��ָ���ַ������׸��ַ�
	Node *t = root;
	while (*p != '\0')                                  //����ָ��ָ��Trie�����ڵ�
	{
		if (t->child[*p - 'a'] != NULL)                 //�������ַ������ӽ���в���
		{
			t = t->child[*p - 'a'];                      //ָ��ָ���ӽڵ�
			p++;                                         //����ƶ��ַ���ָ��
		}
		else                                              //�ӽڵ�Ϊ��
			break;                                        //����ѭ��
	}
	if (*p == '\0')                                       //�ַ���ָ�����ַ�����β
	{
		if (t->count == 0)                                 //���Ǹý���Ҷ�ӽڵ���ĿΪ0
		{
			return 0;
		}
		else                                               //�ý����ӽ�㲻Ϊ0�������������Ҷ�ӽ��
		{
			return 1;
		}
	}
	else                                                   //��û�е��ַ�����β���еĽ��ͽ�����
	{
		return 0;
	}
}

void del(Trie_node root)                    //�ͷ�����Trie��ռ�Ķѿռ�
{
	int i;                                  //����һ��int���͵ı���i
	for (i = 0; i < MAX_CHILD; i++)         //���i<26(��ĸ������ĸ����)
	{
		if (root->child[i] != NULL)         //����ý�㲻Ϊ��
			del(root->child[i]);            //�ݹ�ɾ������ĺ��ӽ�㣬ֱ����������Ϊ��
	}
	free(root);                             //�ͷ�����Trie�������Ŀռ�
}
