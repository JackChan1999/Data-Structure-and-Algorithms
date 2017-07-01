 #define CHAR //�ַ���
 //#define INT //����(����ѡһ)
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
 
 #ifdef CHAR
    typedef char TElemType;
	TElemType Nil = ' ';//�ַ����Կո��Ϊ��
	#define form "%c"//��������ĸ�ʽΪ%c
 #endif
 #ifdef INT
    typedef int TElemType;
    TElemType Nil = 0;//������0Ϊ��
	#define form "%d"//��������ĸ�ʽΪ%d 
 #endif
 
 typedef struct BiTNode
 {
 	TElemType data;
 	struct BiTNode *lchild, *rchild;//���Һ���ָ�� 
 }BiTNode, *BiTree;
 
 #define ClearBiTree DestroyBiTree//��ն����������ٶ������Ĳ���һ��  
 typedef BiTree QElemType;//�����Ԫ��Ϊ��������ָ������
 typedef struct QNode
 {
 	QElemType data;
 	struct QNode *next;
 }QNode, * QueuePtr;
 
 typedef struct 
 {
 	QueuePtr front, rear;//��ͷ����βָ�� 
 }LinkQueue;  
 
 typedef BiTree SElemType;//��ջԪ��Ϊ��������ָ������ 
 
 #define STACK_INIT_SIZE 10  //�洢�ռ��ʼ������
 #define STACK_INCREMENT 2   //�洢�ռ��������
 typedef struct SqStack
 {
 	SElemType *base;//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;//ջ��ָ��
	int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
 }SqStack;//˳��ջ
 
void InitBiTree(BiTree *T);
void DestroyBiTree(BiTree *T);
void PreOrderTraverse(BiTree T, void(*Visit)(TElemType));
void InOrderTraverse(BiTree T, void(*Visit)(TElemType));
void CreateBiTree(BiTree *T);
Status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
TElemType Root(BiTree T);
TElemType Value(BiTree p);
void Assign(BiTree p, TElemType value);
void InitQueue(LinkQueue *Q);
void DestroyQueue(LinkQueue *Q);
void ClearQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead_Q(LinkQueue Q, QElemType *e);//��������
void EnQueue(LinkQueue *Q, QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
void QueueTraverse(LinkQueue Q, void(*vi)(QElemType));
TElemType Parent(BiTree T, TElemType e);
BiTree Point(BiTree T, TElemType s);
TElemType LeftChild(BiTree T, TElemType e);
TElemType RightChild(BiTree T, TElemType e);
TElemType LeftSibling(BiTree T, TElemType e);
TElemType RightSibling(BiTree T, TElemType e);
 Status InsertChild(BiTree p, int LR, BiTree c);//�β�T���� 
Status DeleteChild(BiTree p, int LR);//�β�T����
void InitStack(SqStack *S);
void DestroyStack(SqStack *S);
void ClearStack(SqStack *S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status GetTop(SqStack S, SElemType *e);
void Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
void StackTraverse(SqStack S, void(*visit)(SElemType));
void InOrderTraverse1(BiTree T, void(*Visit)(TElemType));
void InOrderTraverse2(BiTree T, void(*Visit)(TElemType));
void PostOrderTraverse(BiTree T, void(*Visit)(TElemType));
void LevelOrderTraverse(BiTree T, void(*Visit)(TElemType));
void visitT(TElemType e);
 
 int main()
 {
   int i;
   BiTree T,p,c;
   TElemType e1,e2;
   InitBiTree(&T);
   printf("����ն�������,���շ�%d(1:�� 0:��)�������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
     printf("�������ĸ�Ϊ: "form"\n",e1);
   else
     printf("���գ��޸�\n");
 #ifdef CHAR
   printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #endif
 #ifdef INT
   printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   CreateBiTree(&T);
   printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
     printf("�������ĸ�Ϊ: "form"\n",e1);
   else
     printf("���գ��޸�\n");
   printf("����ݹ����������:\n");
   InOrderTraverse(T,visitT);
   printf("\n����ݹ����������:\n");
   PostOrderTraverse(T,visitT);
   printf("\n������һ������ֵ: ");
   scanf("%*c"form,&e1);
   p=Point(T,e1); /* pΪe1��ָ�� */
   printf("����ֵΪ"form"\n",Value(p));
   printf("���ı�˽���ֵ����������ֵ: ");
   scanf("%*c"form"%*c",&e2); /* ��һ��%*c�Ե��س�����Ϊ����CreateBiTree()��׼�� */
   Assign(p,e2);
   printf("�������������:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
     printf("%c��˫����"form"\n",e2,e1);
   else
     printf(form"û��˫��\n",e2);
   e1=LeftChild(T,e2);
   if(e1!=Nil)
     printf(form"��������"form"\n",e2,e1);
   else
     printf(form"û������\n",e2);
   e1=RightChild(T,e2);
   if(e1!=Nil)
     printf(form"���Һ�����"form"\n",e2,e1);
   else
     printf(form"û���Һ���\n",e2);
   e1=LeftSibling(T,e2);
   if(e1!=Nil)
     printf(form"�����ֵ���"form"\n",e2,e1);
   else
     printf(form"û�����ֵ�\n",e2);
   e1=RightSibling(T,e2);
   if(e1!=Nil)
     printf(form"�����ֵ���"form"\n",e2,e1);
   else
     printf(form"û�����ֵ�\n",e2);
   InitBiTree(&c);
   printf("����һ��������Ϊ�յĶ�����c:\n");
 #ifdef CHAR
   printf("���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #endif
 #ifdef INT
   printf("���������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   CreateBiTree(&c);
   printf("����ݹ����������c:\n");
   PreOrderTraverse(c,visitT);
   printf("\n�������������c:\n");
   LevelOrderTraverse(c,visitT);
   printf("��c�嵽��T��,��������T����c��˫�׽�� cΪ��(0)����(1)����: ");
   scanf("%*c"form"%d",&e1,&i);
   p=Point(T,e1); /* p��T����c��˫�׽��ָ�� */
   InsertChild(p,i,c);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\n����ǵݹ����������:\n");
   InOrderTraverse1(T,visitT);
   printf("ɾ������,�������ɾ��������˫�׽��  ��(0)����(1)����: ");
   scanf("%*c"form"%d",&e1,&i);
   p=Point(T,e1);
   DeleteChild(p,i);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\n����ǵݹ����������(��һ�ַ���):\n");
   InOrderTraverse2(T,visitT);
   DestroyBiTree(&T);
 	
 	return 0;
 }
   
 
 void InitBiTree(BiTree *T)
 {
 	//�������������ն�����T
	*T = NULL; 
 } 
 
 void DestroyBiTree(BiTree *T)
 {
 	//��ʼ������������T���ڡ�������������ٶ�����T
	if (*T)//�ǿ���
	{
		if ((*T)->lchild)//������
		{
			DestroyBiTree(&(*T)->lchild);//������������ 
		} 
		if ((*T)->rchild)//���Һ���
		{
			DestroyBiTree(&(*T)->rchild);//�����Һ������� 
		}
		free(*T);//�ͷŸ����
		*T = NULL;//��ָ�� 		
	} //if 
 }
 
 void PreOrderTraverse(BiTree T, void(*Visit)(TElemType))
 {
 	//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú�����
	//�������������ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ��
	if (T)//T����
	{
		Visit(T->data);//�ȷ��ʸ��ڵ�
		PreOrderTraverse(T->lchild, Visit);//���������������
		PreOrderTraverse(T->rchild, Visit);//���������������� 
	}//if 
 }
 
 void InOrderTraverse(BiTree T, void(*Visit)(TElemType))
 {
 	//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú���
	//�������������ݹ����T����ÿ��������Visitһ���ҽ�һ��
	if (T)
	{
		InOrderTraverse(T->lchild, Visit);//���������������
		Visit(T->data);//�ٷ��ʸ����
		InOrderTraverse(T->rchild, Visit);//���������������� 		 
	} //if 
 }
 
 void CreateBiTree(BiTree *T)
 {
 	//�������������������н���ֵ����Ϊ�ַ��ͻ����ͣ��������ж��壩��
	//������������ʾ�Ķ�����T������Nil��ʾ��(��)�����иĶ�
	TElemType ch;
	
	scanf(form, &ch);
	
	if (ch == Nil)//��
	{
		*T = NULL; 
	} 
	else
	{
		*T = (BiTree)malloc(sizeof(BiTree));//���ɸ����
		if (!*T)
		{
			exit(OVERFLOW);
		} 
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);//���������� 
		CreateBiTree(&(*T)->rchild);//���������� 
	}
 }
 
 Status BiTreeEmpty(BiTree T)
 {
 	//��ʼ������������T���ڡ������������TΪ�ն��������򷵻�TRUE������FALSE
	if (T)
	{
		return FALSE;
	} 
	else
	{
		return TRUE;
	}
 }
 
 int BiTreeDepth(BiTree T)
 {
 	//��ʼ������������T���ڡ��������������T�����
	int i, j;
	
	if (!T)
	{
		return 0;//�������Ϊ0 
	} 
	if (T->lchild)
	{
		i = BiTreeDepth(T->lchild);//iΪ����������� 
	} 
	else
	{
		i = 0;  
	} 
	
	if (T->rchild)
	{
		j = BiTreeDepth(T->rchild);//jΪ����������� 
	}
	else
	{
		j=0;
	} 
	
	return i>j? i+1 : j+1;//T�����Ϊ����������������еĴ���+1 
 } 
 
 TElemType Root(BiTree T)
 {
 	//��ʼ������������T���ڡ��������������T�ĸ�
	if (BiTreeEmpty(T))
	{
		return Nil;
	} 
	else
	{
		return T->data;
	}
 }
 
 TElemType Value(BiTree p)
 {
 	//��ʼ������������T���ڣ�pָ��T��ĳ����㡣�������������p��ָ����ֵ
	return p->data; 
 }
 
 void Assign(BiTree p, TElemType value)
 {
 	//��p��ָ��㸳ֵΪvalue
	p->data = value; 
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
 
 TElemType Parent(BiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ�����
	//�����������e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ء��ա�
	LinkQueue q;
	QElemType a;
	
	if (T)//�ǿ��� 
	{
		InitQueue(&q);//��ʼ������
		EnQueue(&q, T);//����ָ����� 
		
		while (! QueueEmpty(q))//�Ӳ��� 
		{
			DeQueue(&q, &a);//���ӣ�����Ԫ�ظ���a
			if (a->lchild && a->lchild->data==e || a->rchild && a->rchild->data==e)//�ҵ�e����������Һ��ӣ� 
			{
				return a->data;//����e��˫�׵�ֵ 
			} 
			else//û�ҵ�e,����������Һ���ָ��(����ǿ�) 
			{
				if (a->lchild)
				{
					EnQueue(&q, a->lchild); 
				} 
				if (a->rchild)
				{
					EnQueue(&q, a->rchild);
				}//if
			} //else
		} //while
	} //if
	
	return Nil;//���ջ�û�ҵ�e 
 } 
 
 BiTree Point(BiTree T, TElemType s)
 {
 	//���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣���
	LinkQueue q;
	QElemType a;
	
	if (T)//�ǿ���
	{
		InitQueue(&q);//��ʼ������
		EnQueue(&q, T);//��ָ�����
		
		while (! QueueEmpty(q))//�Ӳ���
		{
			DeQueue(&q, &a);//���ӣ�����Ԫ�ظ���a
			if (a->data == s)
			{
				return a;
			} 
			if (a->lchild)//������ 
			{
				EnQueue(&q, a->lchild);//������� 
			} 
			if (a->rchild)//���Һ���
			{
				EnQueue(&q, a->rchild);//����Һ��� 
			} //if
		} //while
		
	} //if
	
	return NULL;
 } 
 
 TElemType LeftChild(BiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e�����ӡ���e�����ӣ��򷵻ء��ա� 
 	BiTree a;
 	
 	if (T)//�ǿ���
    {
    	a = Point(T, e);//a�ǽ��e��ָ��
		if (a && a->lchild)//T�д��ڽ��e��e��������
		{
			return a->lchild->data;//����e�����ӵ�ֵ 
		}//if 
	} //if
	return Nil;//����������ؿ� 
 }
 
 TElemType RightChild(BiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e���Һ��ӡ���e���Һ��ӣ��򷵻ء��ա�
	BiTree a;
	
	if (T)//�ǿ���
	{
		a = Point(T, e);//a�ǽ��e��ָ��
		
		if (a && a->rchild)//T�д��ڽ��e��e�����Һ���
		{
			return a->rchild->data;//����e���Һ��ӵ�ֵ 
		}//if	
	} //if
	
	return Nil;//����������ؿ� 
 } 
 
 TElemType LeftSibling(BiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ�����
    //�������������e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻ء��ա�
	TElemType a;
	BiTree p;
	
	if (T)//�ǿ���
	{
		a = Parent(T, e);//aΪe��˫��
		if (a != Nil)//�ҵ�e��˫��
		{
			p = Point(T, a);//pΪָ����a��ָ��
			if (p->lchild && p->rchild && p->rchild->data==e)//p�������Һ������Һ�����e
			{
				return p->lchild->data;//����p�����ӣ�e�����ֵܣ� 
			} //if
		} //if
	} //if
	
	return Nil;//����������ؿ� 	
 } 
 
 TElemType RightSibling(BiTree T, TElemType e)
 {
 	//��ʼ������������T���ڣ�e��T��ĳ�����
	//�������������e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻�"��"
	TElemType a;
	BiTree p;
	
	if (T)//�ǿ��� 
	{
		a = Parent(T, e);//aΪe��˫��
		if (a != Nil)//�ҵ�e��˫��
		{
			p = Point(T, a);//pΪָ����a��ָ��
			if (p->lchild && p->rchild && p->lchild->data==e)//p�������Һ�����������e
			{
				return p->rchild->data;//����p���Һ���(e�����ֵ�) 
			} //if
		} //if		
	} //if
	
	return Nil;//����������ؿ� 
 } 
 
 Status InsertChild(BiTree p, int LR, BiTree c)//�β�T���� 
 {
 	//��ʼ������������T���ڣ�pָ��T��ĳ����㣬LRΪ0��1���ǿն�����c��T���뽻��������Ϊ��
	//�������������LRΪ0��1������cΪT��p��ָ���������������p��ָ����ԭ�������������
	          //ԭ��������������Ϊc��������
    if (p)//p����
	{
		if (LR == 0)
		{
			c->rchild = p->lchild;
			p->lchild = c;
		}
		else//LR==1
		{
			c->rchild = p->rchild;
			p->rchild = c;
			
		}
		return OK;
	} 
	
	return ERROR;//p�� 
 } 
 
 Status DeleteChild(BiTree p, int LR)//�β�T����
 {
 	//��ʼ������������T���ڣ�pָ��T��ĳ����㣬LRΪ0��1
	//�������������LRΪ0��1��ɾ��T��p��ָ�������������
	if (p)//p����
	{
		if (LR == 0)//ɾ��������
		{
			ClearBiTree(&p->lchild); 
		} 
		else
		{
			ClearBiTree(&p->rchild);
		}
		
		return OK;
	} //if
	return ERROR;//p�� 
 } 
 
  void InitStack(SqStack *S)
 {
 	//����һ����ջS
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (! (*S).base)
	{
		exit(OVERFLOW);//�洢����ʧ�� 
	} 
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE; 	
 } 
 
 void DestroyStack(SqStack *S)
 {
 	//����ջS��S���ٴ���
	 free( (*S).base );
	 (*S).base = NULL;
	 (*S).top = NULL;
	 (*S).stacksize = 0; 
 }
 
 void ClearStack(SqStack *S)
 {
 	//��S��Ϊ��ջ
    (*S).top = (*S).base; 
 }
 
 Status StackEmpty(SqStack S)
 {
 	//��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
	if (S.top == S.base)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}	
 }
 
 int StackLength(SqStack S)
 {
 	//����S��Ԫ�ظ�������ջ�ĳ���
	return S.top - S.base; 
 }
 
 Status GetTop(SqStack S, SElemType *e)
 {
 	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if (S.top > S.base)
	{
		*e = *(S.top - 1);
		return OK;
	} 
	else
	{
		return ERROR;
	}
 }
 
 void Push(SqStack *S, SElemType e)
 {
 	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if ( ((*S).top - (*S).base) >= (*S).stacksize )//ջ����׷�Ӵ洢�ռ�
	{
	  (*S).base = (SElemType *)realloc( (*S).base, ((*S).stacksize +STACK_INCREMENT)
                                                        * sizeof(SElemType) );
	  if (! (*S).base)
	  {
	    exit(OVERFLOW);//�洢����ʧ�� 
	  } 
			
	  (*S).top = (*S).base + (*S).stacksize;
	  (*S).stacksize += STACK_INCREMENT; 
	} 
		
	*((*S).top)++ = e;
 }
 
 Status Pop(SqStack *S, SElemType *e)
 {
 	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK��
	//���򷵻�ERROR
	if ( (*S).top == (*S).base )
	{
		return ERROR;
	} 
	
	*e = *--(*S).top ;
	return OK;
 }
 
 void StackTraverse(SqStack S, void(*visit)(SElemType))
 {
 	//��ջ����ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()
	while (S.top > S.base)
	{
		visit( *S.base++ );
	} 
	
	printf("\n");
 }
 
 void InOrderTraverse1(BiTree T, void(*Visit)(TElemType))
 {
 	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú������иĶ�
	//�������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit 
	SqStack S;
	
	InitStack(&S);
	
	while (T || StackEmpty(S))
	{
		if (T)
		{
			//��ָ���ջ������������
			Push(&S, T);
			T = T->lchild; 
		}
		else
		{
			//��ָ����ջ�����ʸ��ڵ㣬����������
			Pop(&S, &T); 
			Visit(T->data);
			T = T->rchild;
		}
	}//while
	
	printf("\n"); 
 } 
 
 void InOrderTraverse2(BiTree T, void(*Visit)(TElemType))
 {
 	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
	//�������������T�ķǵݹ��㷨������ջ������ÿ������Ԫ�ص��ú���Visit
	SqStack S;
	BiTree p;
	
	InitStack(&S); 
	Push(&S, T);//��ָ���ջ
	
	while (! StackEmpty(S))
	{
		while (GetTop(S, &p) && p)
		{
			Push(&S, p->lchild);//�����ߵ���ͷ 
		}
		Pop(&S, &p);//��ָ����ջ 
		if (! StackEmpty(S))
		{
			//���ʽ�㣬����һ��
			Pop(&S, &p);
			Visit(p->data);
			Push(&S, p->rchild); 
		} 
	} //while
	
	printf("\n");
 }
 
 void PostOrderTraverse(BiTree T, void(*Visit)(TElemType))
 {
 	//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú���
	//�������������ݹ����T����ÿ�������ú���Visitһ���ҽ�һ��
	if (T)//T����
	{
		PostOrderTraverse(T->lchild, Visit);//�Ⱥ������������
		PostOrderTraverse(T->rchild, Visit);//�ٺ�������������
		Visit(T->data);//�����ʸ��ڵ� 
	}  
 }
 
 void LevelOrderTraverse(BiTree T, void(*Visit)(TElemType))
 {
 	//��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú���
	//�������:������ݹ����T(���ö���)����ÿ�������ú���Visitһ���ҽ�һ�� 
	LinkQueue q;
	QElemType a;
	
	if (T)
	{
		InitQueue(&q);//��ʼ������q
		EnQueue(&q, T);//��ָ�����
		
		while (! QueueEmpty(q))//���в���
		{
			DeQueue(&q, &a);//����Ԫ�أ�ָ�룩������a
			Visit(a->data);//����a��ָ���
			if (a->lchild != NULL)//a������ 
			{
				EnQueue(&q, a->lchild);//���a������ 
			} 
            if (a->rchild != NULL)//a���Һ��� 
			{
				EnQueue(&q, a->rchild);//���a���Һ��� 
			} 		
		} //while 
		printf("\n");
	} 
 } 
 
 
 
 
 
 
 
 
 void visitT(TElemType e)
 {
 	printf(form" ", e);
 }
 
 
 
 
 
 
  
 
 
 
	 