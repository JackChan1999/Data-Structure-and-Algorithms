#define CHAR /* �ַ��� */
 /* #define INT /* ����(����ѡһ) */
 #ifdef CHAR
   typedef char TElemType;
   TElemType Nil=' '; /* �ַ����Կո��Ϊ�� */
   #define form "%c" /* ��������ĸ�ʽΪ%c */
 #endif
 #ifdef INT
   typedef int TElemType;
   TElemType Nil=0; /* ������0Ϊ�� */
   #define form "%d" /* ��������ĸ�ʽΪ%d */
 #endif
 
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
 
 typedef struct BiTPNode
 {
   TElemType data;
   struct BiTPNode *parent, *lchild, *rchild; /* ˫�ס����Һ���ָ�� */
 }BiTPNode, * BiPTree;
 
 #define ClearBiTree DestroyBiTree /* ��ն����������ٶ������Ĳ���һ�� */
 typedef BiPTree QElemType; /* �����Ԫ��Ϊ��������ָ������ */
 typedef struct QNode
 {
 	QElemType data;
 	struct QNode *next;
 }QNode, * QueuePtr;
 
 typedef struct 
 {
 	QueuePtr front, rear;//��ͷ����βָ�� 
 }LinkQueue; 
 
void InitBiTree(BiPTree *T);
void DestroyBiTree(BiPTree *T);
void CreateBiTree(BiPTree *T);
Status BiTreeEmpty(BiPTree T);
int BiTreeDepth(BiPTree T);
TElemType Root(BiPTree T);
TElemType Value(BiPTree p);
void Assign(BiPTree p, TElemType value);
void InitQueue(LinkQueue *Q);
void DestroyQueue(LinkQueue *Q);
void ClearQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead_Q(LinkQueue Q, QElemType *e);//��������
void EnQueue(LinkQueue *Q, QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
void QueueTraverse(LinkQueue Q, void(*vi)(QElemType));
BiPTree Point(BiPTree T, TElemType e);
TElemType Parent(BiPTree T, TElemType e);
TElemType LeftChild(BiPTree T, TElemType e);
TElemType LeftSibling(BiPTree T, TElemType e);
TElemType RightChild(BiPTree T, TElemType e);
TElemType RightSibling(BiPTree T, TElemType e); 
Status InsertChild(BiPTree p, int LR, BiPTree c); /* �β�T���� */
Status DeleteChild(BiPTree p, int LR); /* �β�T���� */
void PreOrderTraverse(BiPTree T, void(*Visit)(BiPTree));
void InOrderTraverse(BiPTree T, void(*Visit)(BiPTree));
void PostOrderTraverse(BiPTree T, void(*Visit)(BiPTree));
void LevelOrderTraverse(BiPTree T, void(*Visit)(BiPTree));
void visitT(BiPTree T);

 int main()
 {
   int i;
   BiPTree T,c,q;
   TElemType e1,e2;
   InitBiTree(&T);
   printf("����ն�������,���շ�%d(1:�� 0:��)�������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
     printf("�������ĸ�Ϊ: "form"\n",e1);
   else
     printf("���գ��޸�\n");
 #ifdef CHAR
   printf("�밴�������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #endif
 #ifdef INT
   printf("�밴�������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
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
   printf("\n�������������:\n");
   LevelOrderTraverse(T,visitT);
   printf("\n������һ������ֵ: ");
   scanf("%*c"form,&e1);
   c=Point(T,e1); /* cΪe1��ָ�� */
   printf("����ֵΪ"form"\n",Value(c));
   printf("���ı�˽���ֵ����������ֵ: ");
   scanf("%*c"form"%*c",&e2);
   Assign(c,e2);
   printf("�������������:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
     printf("\n"form"��˫����"form"\n",e2,e1);
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
   printf("\n��c�嵽��T��,��������T����c��˫�׽�� cΪ��(0)����(1)����: ");
   scanf("%*c"form"%d",&e1,&i);
   q=Point(T,e1);
   InsertChild(q,i,c);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\nɾ������,�������ɾ��������˫�׽��  ��(0)����(1)����: ");
   scanf("%*c"form"%d",&e1,&i);
   q=Point(T,e1);
   DeleteChild(q,i);
   printf("����ݹ����������:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");
   DestroyBiTree(&T);
 	
   return 0;
 } 
 
 void InitBiTree(BiPTree *T)
 { 
   /* �������������ն�����T */
   *T = NULL;
 }

 void DestroyBiTree(BiPTree *T)
 { 
   /* ��ʼ������������T���ڡ�������������ٶ�����T */
   if(*T) /* �ǿ��� */
   {
     if((*T)->lchild) /* ������ */
     { 
       DestroyBiTree(&(*T)->lchild); /* ������������ */
     }
	 if((*T)->rchild) /* ���Һ��� */
     {  
	   DestroyBiTree(&(*T)->rchild); /* �����Һ������� */
     } 
     
	 free(*T); /* �ͷŸ���� */
     *T = NULL; /* ��ָ�븳0 */
   }
 }

 void CreateBiTree(BiPTree *T)
 { 
   /* �������������������н���ֵ(��Ϊ�ַ��ͻ����ͣ��������ж���)��*/
   /* �������������ʾ�Ķ�����T */
   TElemType ch;
   
   scanf(form, &ch);
   if(ch == Nil) /* �� */
   {  
     *T=NULL;
   }
   else
   {
     *T = (BiPTree)malloc(sizeof(BiTPNode)); /* ��̬���ɸ���� */
     if(! *T)
     { 
       exit(OVERFLOW);
     } 
	 (*T)->data = ch; /* ������㸳ֵ */
     (*T)->parent = NULL; /* �������˫�� */
     CreateBiTree(&(*T)->lchild); /* ���������� */
     if((*T)->lchild) /* ������ */
     {  
	   (*T)->lchild->parent = *T; /* �����ӵ�˫����ֵ */
     }
	 CreateBiTree(&(*T)->rchild); /* ���������� */
     if((*T)->rchild) /* ���Һ��� */
     {	
       (*T)->rchild->parent = *T; /* ���Һ��ӵ�˫����ֵ */
     }
   }
 }

 Status BiTreeEmpty(BiPTree T)
 { 
   /* ��ʼ������������T���ڡ������������TΪ�ն��������򷵻�TRUE������FALSE */
   if(T)
   {
     return FALSE;
   }
   else
   {
     return TRUE;
   }
 }

 int BiTreeDepth(BiPTree T)
 { 
   /* ��ʼ������������T���ڡ��������������T����� */
   int i, j;
   
   if(! T)
   {
     return 0; /* �������Ϊ0 */
   }
   
   if(T->lchild)
   {
     i = BiTreeDepth(T->lchild); /* iΪ����������� */
   }
   else
   {
     i = 0;
   }
   
   if(T->rchild)
   {
     j = BiTreeDepth(T->rchild); /* jΪ����������� */
   }
   else
   {
     j = 0;
   }
   return i>j ? i+1 : j+1; /* T�����Ϊ����������������еĴ���+1 */
 }

 TElemType Root(BiPTree T)
 { /* ��ʼ������������T���ڡ��������������T�ĸ� */
   if(T)
   {
     return T->data;
   }
   else
   {
     return Nil;
   }
 }

 TElemType Value(BiPTree p)
 { 
   /* ��ʼ������������T���ڣ�pָ��T��ĳ����㡣�������������p��ָ����ֵ */
   return p->data;
 }

 void Assign(BiPTree p, TElemType value)
 { 
   /* ��p��ָ��㸳ֵΪvalue */
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
 
 BiPTree Point(BiPTree T, TElemType e)
 { /* ���ض�����T��ָ��Ԫ��ֵΪe�Ľ���ָ�롣�� */
   LinkQueue q;
   QElemType a;
   
   if(T) /* �ǿ��� */
   {
     InitQueue(&q); /* ��ʼ������ */
     EnQueue(&q, T); /* �������� */
     while(! QueueEmpty(q)) /* �Ӳ��� */
     {
       DeQueue(&q, &a); /* ���ӣ�����Ԫ�ظ���a */
       if(a->data == e)
       {
         return a;
       }
	   if(a->lchild) /* ������ */
       {
         EnQueue(&q, a->lchild); /* ������� */
       }
	   if(a->rchild) /* ���Һ��� */
       {
         EnQueue(&q, a->rchild); /* ����Һ��� */
       }
	 }//while
   }//if
   
   return NULL;
 }

 TElemType Parent(BiPTree T, TElemType e)
 { 
   /* ��ʼ������������T���ڣ�e��T��ĳ����� */
   /* �����������e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻أ��գ�*/
   BiPTree a;
   if(T) /* �ǿ��� */
   {
     a = Point(T, e); /* a�ǽ��e��ָ�� */
     if(a && a!=T) /* T�д��ڽ��e��e�ǷǸ���� */
     {
       return a->parent->data; /* ����e��˫�׵�ֵ */
     }
   }
   
   return Nil; /* ����������ؿ� */
 }

 TElemType LeftChild(BiPTree T, TElemType e)
 { 
   /* ��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e�����ӡ���e������,�򷵻�"��" */
   BiPTree a;
   
   if(T) /* �ǿ��� */
   {
     a = Point(T, e); /* a�ǽ��e��ָ�� */
     if(a && a->lchild) /* T�д��ڽ��e��e�������� */
     {
       return a->lchild->data; /* ����e�����ӵ�ֵ */
     }
   }
   
   return Nil; /* ����������ؿ� */
 }

 TElemType RightChild(BiPTree T, TElemType e)
 { 
   /* ��ʼ������������T���ڣ�e��T��ĳ����㡣�������������e���Һ��ӡ���e���Һ���,�򷵻�"��" */
   BiPTree a;
   
   if(T) /* �ǿ��� */
   {
     a = Point(T, e); /* a�ǽ��e��ָ�� */
     if(a && a->rchild) /* T�д��ڽ��e��e�����Һ��� */
     {
       return a->rchild->data; /* ����e���Һ��ӵ�ֵ */
     }
   }
   
   return Nil; /* ����������ؿ� */
 }

 TElemType LeftSibling(BiPTree T, TElemType e)
 { 
   /* ��ʼ������������T���ڣ�e��T��ĳ����� */
   /* �������������e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻أ��գ�*/
   BiPTree a;
   
   if(T) /* �ǿ��� */
   {
     a = Point(T, e); /* a�ǽ��e��ָ�� */
     if(a && a!=T && a->parent->lchild && a->parent->lchild!=a) /* T�д��ڽ��e��e�������ֵ� */
     {
       return a->parent->lchild->data; /* ����e�����ֵܵ�ֵ */
     }
   }
   
   return Nil; /* ����������ؿ� */
 }

 TElemType RightSibling(BiPTree T, TElemType e)
 { 
   /* ��ʼ������������T���ڣ�e��T��ĳ����� */
   /* �������������e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻أ��գ�*/
   BiPTree a;
   
   if(T) /* �ǿ��� */
   {
     a = Point(T,e); /* a�ǽ��e��ָ�� */
     if(a && a!=T && a->parent->rchild && a->parent->rchild!=a) /* T�д��ڽ��e��e�������ֵ� */
     {
       return a->parent->rchild->data; /* ����e�����ֵܵ�ֵ */
     }
   }
   
   return Nil; /* ����������ؿ� */
 }

 Status InsertChild(BiPTree p, int LR, BiPTree c) /* �β�T���� */
 { 
   /* ��ʼ������������T���ڣ�pָ��T��ĳ����㣬LRΪ0��1���ǿն�����c��T���ཻ��������Ϊ�� */
   /* �������������LRΪ0��1������cΪT��p��ָ���������������p��ָ��� */
   /*           ��ԭ��������������Ϊc�������� */
   if(p) /* p���� */
   {
     if(LR == 0)
     {
       c->rchild = p->lchild;
       if(c->rchild) /* c���Һ���(pԭ������) */
       {
         c->rchild->parent = c;
       }
	   p->lchild = c;
       c->parent = p;
     }
     else /* LR==1 */
     {
       c->rchild = p->rchild;
       if(c->rchild) /* c���Һ���(pԭ���Һ���) */
       {
         c->rchild->parent = c;
       }
	   p->rchild = c;
       c->parent = p;
     }
     
     return OK;
   }
   
   return ERROR; /* p�� */
 }

 Status DeleteChild(BiPTree p, int LR) /* �β�T���� */
 { 
   /* ��ʼ������������T���ڣ�pָ��T��ĳ����㣬LRΪ0��1 */
   /* �������������LRΪ0��1��ɾ��T��p��ָ������������� */
   if(p) /* p���� */
   {
     if(LR == 0) /* ɾ�������� */
     {
       ClearBiTree(&p->lchild);
     }
	 else /* ɾ�������� */
	 {
       ClearBiTree(&p->rchild);
	 }
	 return OK;
   }
   return ERROR; /* p�� */
 }

 void PreOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
 { /* ����ݹ����������T */
   if(T)
   {
     Visit(T); /* �ȷ��ʸ���� */
     PreOrderTraverse(T->lchild, Visit); /* ��������������� */
     PreOrderTraverse(T->rchild, Visit); /* ���������������� */
   }
 }

 void InOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
 { /* ����ݹ����������T */
   if(T)
   {
     InOrderTraverse(T->lchild, Visit); /* ������������� */
     Visit(T); /* �ٷ��ʸ���� */
     InOrderTraverse(T->rchild, Visit); /* ���������������� */
   }
 }

 void PostOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
 { /* ����ݹ����������T */
   if(T)
   {
     PostOrderTraverse(T->lchild, Visit); /* ������������� */
     PostOrderTraverse(T->rchild, Visit); /* ������������� */
     Visit(T); /* �����ʸ���� */
   }
 }

 void LevelOrderTraverse(BiPTree T, void(*Visit)(BiPTree))
 { /* �������������T(���ö���) */
   LinkQueue q;
   QElemType a;
   if(T)
   {
     InitQueue(&q);
     EnQueue(&q, T);
     while(! QueueEmpty(q))
     {
       DeQueue(&q, &a);
       Visit(a);
       if(a->lchild != NULL)
       {
         EnQueue(&q, a->lchild);
       }
	   if(a->rchild!=NULL)
	   {
         EnQueue(&q, a->rchild);
	   }
	 }//while
   }//if
 }
 
 void visitT(BiPTree T)
 {
   if(T) /* T�ǿ� */
   {
     printf(form" ", T->data);
   }
 }
 
 