 //define CHAR 1 //�ַ���
 #define CHAR 0 //����(����ѡһ) 
 #include<limits.h> /* INT_MAX�� */
 #include<stdio.h> /* EOF(=^Z��F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h> /* exit() */
 /* �������״̬���� */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 /* #define OVERFLOW -2 ��Ϊ��math.h���Ѷ���OVERFLOW��ֵΪ3,��ȥ������ */
 typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
 typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
 
 #if CHAR 
   typedef char TElemType;
   TElemType Nil = ' ';//���ַ����Կո��Ϊ��
   #define form "%c"
 #else
   typedef int TElemType;
   TElemType Nil = 0;//��������0Ϊ��
   #define form "%d"
 #endif 
 
 #define MAX_TREE_SIZE 100 //���������������
 typedef TElemType SqBiTree[MAX_TREE_SIZE];//0�ŵ�Ԫ�洢���ڵ�
 
 typedef struct
 {
 	int level, order;//���Ĳ㣬�������(��������������) 
 }position; 
 
 #define ClearBiTree InitBiTree//��˳��洢�ṹ�У���������ȫһ��
 #define DestroyBiTree InitBiTree//��˳��洢�ṹ�У���������ȫһ��
 
 typedef int QElemType;//�����Ԫ������Ϊ����(���) 
 typedef struct QNode
 {
 	QElemType data;
 	struct QNode *next;
 }QNode, * QueuePtr;
 
 typedef struct 
 {
 	QueuePtr front, rear;//��ͷ����βָ�� 
 }LinkQueue; 
 
void InitBiTree(SqBiTree T);
void CreateBiTree(SqBiTree T);
Status BiTreeEmpty(SqBiTree T);
int BiTreeDepth(SqBiTree T);
Status Root(SqBiTree T, TElemType *e);
TElemType Value(SqBiTree T, position e);
Status Assign(SqBiTree T, position e, TElemType value);
TElemType Parent(SqBiTree T, TElemType e);
TElemType LeftChild(SqBiTree T, TElemType e);
TElemType RightChild(SqBiTree T, TElemType e);
TElemType LeftSibling(SqBiTree T, TElemType e);
TElemType RightSibling(SqBiTree T, TElemType e);
void Move(SqBiTree q, int j, SqBiTree T, int i);//InsertChild()�õ�����
void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c);
void InitQueue(LinkQueue *Q);
void DestroyQueue(LinkQueue *Q);
void ClearQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead_Q(LinkQueue Q, QElemType *e);//��������
void EnQueue(LinkQueue *Q, QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
void QueueTraverse(LinkQueue Q, void(*vi)(QElemType));
void print(QElemType i);
Status DeleteChild(SqBiTree T, position p, int LR);
void(*VisitFunc)(TElemType);//��������
void PreTraverse(SqBiTree T, int e);
void PreOrderTraverse(SqBiTree T, void(*Visit)(TElemType));
void InTraverse(SqBiTree T, int e);
void InOrderTraverse(SqBiTree T, void(*Visit)(TElemType));
void PostTraverse(SqBiTree T, int e);
void PostOrderTraverse(SqBiTree T, void(*Visit)(TElemType));
void LevelOrderTraverse(SqBiTree T, void(*Visit)(TElemType));
void Print(SqBiTree T);
void visit(TElemType e);

int main()
{
   Status i;
   int j;
   position p;
   TElemType e;
   SqBiTree T,s;
   InitBiTree(T);
   CreateBiTree(T);
   printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   i=Root(T,&e);
   if(i)
     printf("�������ĸ�Ϊ��"form"\n",e);
   else
     printf("���գ��޸�\n");
   printf("�������������:\n");
   LevelOrderTraverse(T,visit);
   printf("�������������:\n");
   InOrderTraverse(T,visit);
   printf("�������������:\n");
   PostOrderTraverse(T,visit);
   printf("��������޸Ľ��Ĳ�� �������: ");
   scanf("%d%d",&p.level,&p.order);
   e=Value(T,p);
   printf("���޸Ľ���ԭֵΪ"form"��������ֵ: ",e);
   scanf("%*c"form"%*c",&e);
   Assign(T,p,e);
   printf("�������������:\n");
   PreOrderTraverse(T,visit);
   printf("���"form"��˫��Ϊ"form",���Һ��ӷֱ�Ϊ",e,Parent(T,e));
   printf(form","form",�����ֱֵܷ�Ϊ",LeftChild(T,e),RightChild(T,e));
   printf(form","form"\n",LeftSibling(T,e),RightSibling(T,e));
   InitBiTree(s);
   printf("����������Ϊ�յ���s:\n");
   CreateBiTree(s);
   printf("��s�嵽��T��,��������T����s��˫�׽�� sΪ��(0)����(1)����: ");
   scanf(form"%d",&e,&j);
   InsertChild(T,e,j,s);
   Print(T);
   printf("ɾ������,�������ɾ�����������Ĳ�� ������� ��(0)����(1)����: ");
   scanf("%d%d%d",&p.level,&p.order,&j);
   DeleteChild(T,p,j);
   Print(T);
   ClearBiTree(T);
   printf("�����������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   i=Root(T,&e);
   if(i)
     printf("�������ĸ�Ϊ��"form"\n",e);
   else
     printf("���գ��޸�\n");
	return 0;
}
 
 
 
 
 void InitBiTree(SqBiTree T)
 {
 	//����ն�����T����ΪT�����������ʲ���Ҫ&
	int i;
	
	for (i=0; i<MAX_TREE_SIZE; i++)
	{
		T[i] = Nil;//��ֵΪ��(Nil�������ж���) 
	} 
 } 
 
 void CreateBiTree(SqBiTree T)
 {
 	//�����������������н���ֵ(�ַ��ͻ�����)������˳��洢�Ķ�����T
	int i = 0;
   #if CHAR //�������Ϊ�ַ�
    int l;
	char s[MAX_TREE_SIZE];
	
	InitBiTree(T);//����ն�����T
	printf("�밴�����������ֵ(�ַ�),�ո��ʾ�ս�㣬�����<=%d:\n", MAX_TREE_SIZE); 
	gets(s);//�����ַ���
    l = strlen(s);//���ַ����ĳ���
    for (; i<l; i++)//���ַ�����ֵ��T
	{
		T[i] = s[i]; 
	} 
   #else  //�������Ϊ����
    InitBiTree(T);//����ն�����T
	printf("�밴�����������ֵ(����)��0��ʾ�ս�㣬��999�������ڵ�����%d:\n", MAX_TREE_SIZE);
	while (1)
	{
		scanf("%d", &T[i]);
		if (T[i] == 999)
		{
			T[i] = Nil;
			break;
		}
		i++;
	}
   #endif
     for (i=1; i<MAX_TREE_SIZE; i++)
     {
     	if (T[(i+1)/2-1]==Nil && T[i]!=Nil)//�˷Ǹ����(����)��˫��
		{
			printf("������˫�׵ķǸ���㡱form��\n", T[i]);
			exit(ERROR);
		} 	
     }
 } 
 
 Status BiTreeEmpty(SqBiTree T)
 {
 	//��ʼ������������T���ڡ������������TΪ�ն�����,���򷵻�TRUE,����FALSE
	if (T[0] == Nil)//���ڵ�Ϊ�գ�������
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
 }
 
 int BiTreeDepth(SqBiTree T)
 {
 	//��ʼ������������T���ڡ��������������T�����
	int i, j = -1;
	
	for (i=MAX_TREE_SIZE-1; i>=0; i--)//�ҵ����һ�����
	{
		if (T[i] != Nil)
		{
			break;
		} 
	} 
	i++;//Ϊ�˱��ڼ���
	do
	{
		j++;
	}while (i>=pow(2, j)); 
	
	return j;
 }
 
 Status Root(SqBiTree T, TElemType *e)
 {
 	//��ʼ������������T���ڡ������������T���գ���e����T�ĸ�������OK�����򷵻�ERROR���޶���
	if (BiTreeEmpty(T))//T��
	{
		return ERROR; 
	} 
	else
	{
		*e = T[0];
		return OK; 
	} 
 }
 
 
 TElemType Value(SqBiTree T, position e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ�����(��λ��)
	//������������ش���λ��e(�㣬�������)�Ľ���ֵ
    return T[(int)pow(2, e.level-1) + e.order - 2]; 
 }
 
 Status Assign(SqBiTree T, position e, TElemType value)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ�����(��λ��)
	//���������������λ��e(�㣬�������)�Ľ�㸳��ֵvalue
	int i = (int)pow(2, e.level-1)+e.order-2;//���㣬�������תΪ��������
	
	if (value!=Nil && T[(i+1)/2-1]==Nil)//��Ҷ�Ӹ��ǿ�ֵ��˫��Ϊ�� 
	{
		return ERROR;
	}
	else if (value==Nil && (T[i*2+1]!=Nil || T[i*2+2]!=Nil))//��˫�׸���ֵ����Ҷ��(����)
	{
		return ERROR; 
	} 
	T[i] = value;
	
	return OK;
 }
 
 TElemType Parent(SqBiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ�����
	//�����������e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ؿ�
	int i; 
	
	if (T[0] == Nil)//����
	{
		return Nil; 
	} 
	for (i=1; i<=MAX_TREE_SIZE-1; i++)
	{
		if (T[i] == e)//�ҵ�e 
		{
			return T[(i+1)/2-1]; 
		} 
	}//for
	return Nil;//û�ҵ�e 
 }
 
 TElemType LeftChild(SqBiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e�����ӡ���e�����ӣ��򷵻ء��ա�
	int i;
	
	if (T[0] == Nil)//����
	{
		return Nil; 
	} 
	
	for (i=0; i<=MAX_TREE_SIZE-1; i++)
	{
		if (T[i] == e)//�ҵ�e
		{
			return T[i*2+1]; 
		} 
	}
	
	return Nil;//û�ҵ�e 
 } 
 
 TElemType RightChild(SqBiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e���Һ��ӡ���e���Һ��ӣ��򷵻ء��ա�
	int i;
	
	if (T[0] == Nil)//���� 
	{
		return Nil; 
	} 
	
	for (i=0; i<=MAX_TREE_SIZE-1; i++)
	{
		if (T[i] == e)//�ҵ�e
		{
			return T[i*2+2];
		}
	}//for
	return Nil;//û�ҵ�e 
 }
 
 TElemType LeftSibling(SqBiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ�����
	//�������������e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻ء��ա�
	int i;
	
	if (T[0] == Nil)//����
	{
		return Nil; 
	} 
	
	for (i=1; i<=MAX_TREE_SIZE-1; i++)
	{
		if (T[i]==e && i%2==0)//�ҵ�e�������Ϊż�������Һ��ӣ�
		{
			return T[i-1]; 
		} 
	}//for
	
	return Nil;//û�ҵ�e 	
 }
 
 TElemType RightSibling(SqBiTree T, TElemType e)
 {
 	//��ʼ������������T����,e��T��ĳ�����
	//�������������e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻ء��ա�
    int i;
	
	if (T[0] == Nil)//����
	{
		return Nil; 
	}
	for (i=1; i<=MAX_TREE_SIZE-1; i++)
	{
		if (T[i]==e && i%2)//�ҵ�e�������Ϊ�����������ӣ�
		{
			return T[i+1];
		} 
	}
	
	return Nil;//û�ҵ�e 
 } 
 
 void Move(SqBiTree q, int j, SqBiTree T, int i)//InsertChild()�õ�����
 {
 	//�Ѵ�q��j��㿪ʼ��������Ϊ��T��i��㿪ʼ������
	if (q[2*j+1] != Nil)//q������������
	{
		Move(q, (2*j+1), T, (2*i+1));//��q��j������������ΪT��i���������� 
	} 
	if (q[2*j+2] != Nil)//q������������
	{
		Move(q, (2*j+2), T, (2*i+2));//��q��j������������ΪT��i���������� 
	} 
	T[i] = q[j];//��q��j�����ΪT��i���
	q[j] = Nil;//��q��j����ÿ� 
 } 
 
 void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c)
 {
 	//��ʼ������������T���ڣ�p��T��ĳ������ֵ��LRΪ0��1���ǿն�����c��T���ཻ��������Ϊ��
    //�������������LRΪ0��1������cΪT��p���������������p����ԭ��������������Ϊc��������
    int j, k, i = 0;
	
	for (j=0; j<(int)pow(2, BiTreeDepth(T))-1; j++)//����p����� 
	{
		if (T[j] == p)//jΪp�����
		{
			break; 
		} 
	} 
	k = 2*j+1+LR;//kΪp������Һ��ӵ����
	if (T[k] != Nil)//pԭ��������Һ��Ӳ���
	{
		Move(T, k, T, 2*k+2);//�Ѵ�T��k��㿪ʼ��������Ϊ��k������������ʼ������ 
	} 
	Move(c, i, T, k);//�Ѵ�c��i��㿪ʼ��������Ϊ��T��k��㿪ʼ������ 	 
 }
 
 void InitQueue(LinkQueue *Q)
 {
 	//����һ���ն���Q
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	
	if (! (*Q).front)
	{
		exit(OVERFLOW);
	}  
	
	(*Q).front->next = NULL;
 } 
 
 void DestroyQueue(LinkQueue *Q)
 {
 	//���ٶ���Q(���ۿշ����)
	while ( (*Q).front )
	{
		(*Q).rear = (*Q).front->next;
		free( (*Q).front );
		(*Q).front = (*Q).rear;
	}//while 
 } 
 
 void ClearQueue(LinkQueue *Q)
 {
 	//��Q��Ϊ�ն���
	QueuePtr p, q;
	
	(*Q).rear = (*Q).front;
	p = (*Q).front->next;
	(*Q).front->next = NULL;
	
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	} //while
 }
 
 Status QueueEmpty(LinkQueue Q)
 {
 	//��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	 if (Q.front->next == NULL)
	 {
	 	return TRUE;
 	 }  
 	 else
 	 {
 	 	return FALSE;
 	 }
 }
 
 int QueueLength(LinkQueue Q)
 {
 	//����г���
	 int i = 0;
	 QueuePtr p;
	 
	 p = Q.front;
	 
	 while (Q.rear != p)
	 {
	 	i++;
	 	p = p->next;
     } 
     
     return i;
 }
 
 Status GetHead_Q(LinkQueue Q, QElemType *e)//��������
 {
 	//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	QueuePtr p;
	
	if (Q.front == Q.rear)
	{
		return ERROR;
	}
	
	p = Q.front->next;
	*e = p->data;
	
	return OK;
 } 
 
 void EnQueue(LinkQueue *Q, QElemType e)
 {
 	//����Ԫ��eΪQ���µĶ�βԪ��
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (! p)//�洢����ʧ��
	{
		exit(OVERFLOW); 
	} 
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
 }
 
 Status DeQueue(LinkQueue *Q, QElemType *e)
 {
 	//���в�Ϊ�գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
	QueuePtr p;
	
	if ((*Q).front == (*Q).rear)
	{
		return ERROR;
	} 
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p)
	{
		(*Q).rear == (*Q).front;
	}
	free(p);
	
	return OK;	
 }
 
 void QueueTraverse(LinkQueue Q, void(*vi)(QElemType))
 {
 	//�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi����
	QueuePtr p;
	
	p = Q.front->next;
	
	while ( p )
	{
		vi(p->data);
		p = p->next;
	} 
	printf("\n");
 }
 
 void print(QElemType i)
 {
 	printf("%d ", i);
 }
 
 Status DeleteChild(SqBiTree T, position p, int LR)
 {
 	//��ʼ������������T���ڣ�pָ��T��ĳ����㣬LRΪ1��0
	//�������������LRΪ1��0��ɾ��T��p��ָ������������� 
	int i;
	Status k = OK;//���в��յı�־
	LinkQueue q;
	
	InitQueue(&q);//��ʼ�����У����ڴ�Ŵ�ɾ���Ľ��
	i = (int)pow(2, p.level-1) + p.order - 2;//���㣬�������תΪ��������
	if (T[i] == Nil)//�˽���
	{
		return ERROR; 
	} 
	i = i*2 + 1 + LR;//��ɾ�������ĸ��ڵ��ھ����е����
	
	while (k)
	{
		if (T[2*i+1] != Nil)//���㲻��
		{
			EnQueue(&q, 2*i+1);//������������� 
		} 
		if (T[2*i+2] != Nil)//�ҽ�㲻��
		{
			EnQueue(&q, 2*i+2);//������ҽ������ 
		} 
		T[i] = Nil;//ɾ���˽��
		k = DeQueue(&q, &i);//���в��� 
	} 
	
	return OK; 
 } 
 
 void(*VisitFunc)(TElemType);//��������
 
 void PreTraverse(SqBiTree T, int e)
 {
 	//PreOrderTraverse()����
	VisitFunc(T[e]);
	
	if (T[2*e+1] != Nil)//����������
	{
		PreTraverse(T, 2*e+1); 
	} 
	if (T[2*e+2] != Nil)//����������
	{
		PreTraverse(T, 2*e+2); 
	} 
 } 
 
 void PreOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
 {
 	//��ʼ����:���������ڣ�Visit�ǶԽ�������Ӧ�ú���
	//����������������T����ÿ�������ú���Visitһ���ҽ�һ��
	VisitFunc = Visit;
	
	if (! BiTreeEmpty(T))//������ 
	{
		PreTraverse(T, 0); 
	} 
	printf("\n");
 }
 
 void InTraverse(SqBiTree T, int e)
 {
 	//InOrderTraverse()����
	if (T[2*e+1] != Nil)//����������
	{
		InTraverse(T, 2*e+1); 
	} 
	VisitFunc(T[e]);
	
	if (T[2*e+2] != Nil)//����������
	{
		InTraverse(T, 2*e+2); 
	} 
 }
 
 void InOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
 {
 	//��ʼ������������ ���ڣ�Visit�ǶԽ�������Ӧ�ú���
	//����������������T����ÿ�������ú���Visitһ���ҽ�һ��
	VisitFunc = Visit;
	
	if (! BiTreeEmpty(T))//������
	{
		InTraverse(T, 0); 
	}  
	printf("\n");
 }
 
 void PostTraverse(SqBiTree T, int e)
 {
 	//PostOrderTraverse��������
	if (T[2*e+1] != Nil)//����������
	{
		PostTraverse(T, 2*e+1); 
	} 
	if (T[2*e+2] != Nil)//����������
	{
		PostTraverse(T, 2*e+2); 
	} 
	
	VisitFunc(T[e]);
 }
 
 void PostOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
 {
 	//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú���
	//����������������T����ÿ�������ú���Visitһ���ҽ�һ��
	VisitFunc = Visit;
	if (! BiTreeEmpty(T))//������
	{
		PostTraverse(T, 0); 
	}  
	printf("\n");
 }
 
 void LevelOrderTraverse(SqBiTree T, void(*Visit)(TElemType))
 {
 	//�������������
	int i = MAX_TREE_SIZE-1, j;
	
	while (T[i] == Nil)
	{
		i--;//�ҵ����һ���ǿսڵ����� 
	} 
	for (j=0; j<=0; j++)//�Ӹ��ڵ��𣬰��������������
	{
		if (T[j] != Nil)
		{
			Visit(T[j]);//ֻ�����ǿյĽ�� 
		} 
	} 
	
	printf("\n"); 
 }
 
 void Print(SqBiTree T)
 {
 	//��㣬������������������
	int j, k;
	position p;
	TElemType e;
	
	for (j=1; j<=BiTreeDepth(T); j++)
	{
		printf("��%d�㣺 ", j);
		for (k=1; k<=pow(2, j-1); k++)
		{
			p.level = j;
			p.order = k;
			e = Value(T, p);
			if (e != Nil)
			{
				printf("%d:"form" ", k, e);
			}//if
		}//for-in
		printf("\n");
	} //for-out	
 } 
 
 void visit(TElemType e)
 {
   printf(form" ",e);
 }
 
 

 
 
 
  
 
 
 
 
 
 