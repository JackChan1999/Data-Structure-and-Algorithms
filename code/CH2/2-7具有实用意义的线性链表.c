 #include<string.h>
 #include<ctype.h>
 #include<malloc.h> /* malloc()�� */
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
 typedef int ElemType;
 
 typedef struct LNode //�������
 {
 	ElemType data;
 	struct LNode *next;
 }LNode, *Link, *Position;
 
 typedef struct LinkList//��������
 {
 	Link head, tail;//�ֱ�ָ�����������е�ͷ�������һ�����
	int len;//ָʾ��������������Ԫ�صĸ��� 
 }LinkList;
 
 void MakeNode(Link *p, ElemType e);
 void FreeNode(Link *p);
 void InitList(LinkList *L);
 void ClearList(LinkList *L);
 void DestroyList(LinkList *L);
 void InsFirst(LinkList *L, Link h, Link s);//�β�����L����Ϊ���޸�L
 Status DelFirst(LinkList *L, Link h, Link *q);//�β�����L����Ϊ���޸�L 
 void Append(LinkList *L, Link s);
 Position PriorPos(LinkList L, Link p);
 Status Remove(LinkList *L, Link *q);
 void InsBefore(LinkList *L, Link *p, Link s);
 void InsAfter(LinkList *L, Link *p, Link s);
 void SetCurElem(Link p, ElemType e);
 ElemType GetCurElem(Link p);
 Status ListEmpty(LinkList L);
 int ListLength(LinkList L);
 Position GetHead(LinkList L);
 Position GetLast(LinkList L);
 Position NextPos(Link p);
 Status LocatePos(LinkList L, int i, Link *p);
 Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType));
 void ListTraverse(LinkList L, void(*visit)(ElemType));
 void OrderInsert(LinkList *L, ElemType e, int (*comp)(ElemType, ElemType));
 Status LocateElemP(LinkList L, ElemType e, Position *q, int(*compare)(ElemType, ElemType));
 Status equal(ElemType c1, ElemType c2);
 int comp(ElemType a, ElemType b);
 void print(ElemType c);
 void print2(ElemType c);
 void print1(ElemType *c);
 
 int main()
 {
   Link p,h;
   LinkList L;
   Status i;
   int j,k;
   
   InitList(&L); /* ��ʼ���յ����Ա�L */
   
   for(j=1;j<=2;j++)
   {
     MakeNode(&p,j); /* ������pָ��ֵΪj�Ľ�� */
     InsFirst(&L,L.tail,p); /* ���ڱ�β */
   }
   OrderInsert(&L,0,comp); /* ��������������ͷ */
   for(j=0;j<=3;j++)
   {
     i=LocateElemP(L,j,&p,comp);
     if(i)
     {
       printf("��������ֵΪ%d��Ԫ�ء�\n",p->data);
     }
	 else
	 {
       printf("������û��ֵΪ%d��Ԫ�ء�\n",j);
	 }
   }
   printf("�������");
   ListTraverse(L,print); /* ���L */
   for(j=1;j<=4;j++)
   {
     printf("ɾ����ͷ��㣺");
     DelFirst(&L,L.head,&p); /* ɾ��L���׽�㣬����p���� */
     if(p)
     {
       printf("%d\n",GetCurElem(p));
     }
	 else
	 {
       printf("��գ��޷�ɾ�� p=%u\n",p);
	 }
   }
   printf("L�н�����=%d L�Ƿ�� %d(1:�� 0:��)\n",ListLength(L),ListEmpty(L));
   MakeNode(&p,10);
   p->next=NULL; /* β��� */
   for(j=4;j>=1;j--)
   {
     MakeNode(&h,j*2);
     h->next=p;
     p=h;
   } /* hָ��һ��5����㣬��ֵ������2 4 6 8 10 */
   Append(&L,h); /* �ѽ��h��������������L�����һ�����֮�� */
   OrderInsert(&L,12,comp); /* ��������������βͷ */
   OrderInsert(&L,7,comp); /* ���������������м� */
   printf("�������");
   ListTraverse(L,print); /* ���L */
   for(j=1;j<=2;j++)
   {
     p=LocateElem(L,j*5,equal);
     if(p)
     {
       printf("L�д���ֵΪ%d�Ľ�㡣\n",j*5);
     }
	 else
	 {
       printf("L�в�����ֵΪ%d�Ľ�㡣\n",j*5);
	 }
   }
   for(j=1;j<=2;j++)
   {
     LocatePos(L,j,&p); /* pָ��L�ĵ�j����� */
     h=PriorPos(L,p); /* hָ��p��ǰ�� */
     if(h)
     {
       printf("%d��ǰ����%d��\n",p->data,h->data);
     }
	 else
	 {
       printf("%dûǰ����\n",p->data);
	 }
   }
   k=ListLength(L);
   for(j=k-1;j<=k;j++)
   {
     LocatePos(L,j,&p); /* pָ��L�ĵ�j����� */
     h=NextPos(p); /* hָ��p�ĺ�� */
     if(h)
     {
       printf("%d�ĺ����%d��\n",p->data,h->data);
	 }
	 else
	 {
       printf("%dû��̡�\n",p->data);
	 }
   }
   printf("L�н�����=%d L�Ƿ�� %d(1:�� 0:��)\n",ListLength(L),ListEmpty(L));
   p=GetLast(L); /* pָ�����һ����� */
   SetCurElem(p,15); /* �����һ������ֵ��Ϊ15 */
   printf("��1��Ԫ��Ϊ%d ���1��Ԫ��Ϊ%d\n",GetCurElem(GetHead(L)->next),GetCurElem(p));
   MakeNode(&h,10);
   InsBefore(&L,&p,h); /* ��10�嵽β���֮ǰ��pָ���½�� */
   p=p->next; /* p�ָ�Ϊβ��� */
   MakeNode(&h,20);
   InsAfter(&L,&p,h); /* ��20�嵽β���֮�� */
   k=ListLength(L);
   printf("����ɾ����β��㲢�����ֵ��");
   for(j=0;j<=k;j++)
   {
     i=Remove(&L,&p);
     if(!i) /* ɾ�����ɹ� */
     {
       printf("ɾ�����ɹ� p=%u\n",p);
     }
	 else
	 {
       printf("%d ",p->data);
	 }

   }
   return 0;
 }
 
 void MakeNode(Link *p, ElemType e)
 {
 	//������pָ���ֵΪe�Ľ�㡣������ʧ�ܣ����˳�
	*p = (Link)malloc(sizeof(LNode));
	if (!*p)
	{
		exit(ERROR);
	}
	(*p)->data = e;
 }
 
 void FreeNode(Link *p)
 {
 	//�ͷ�p��ָ���
	 free(*p);
	 *p = NULL; 
 }
 
 void InitList(LinkList *L)
 {
 	//����һ���յ���������L
	Link p;
	p = (Link)malloc(sizeof(LNode));//����ͷ���
	
	if (p)
	{
		p->next = NULL;
		(*L).head = (*L).tail = p;
		(*L).len = 0;
	}
	else
	{
		exit(ERROR);
	}
 }
 
 void ClearList(LinkList *L)
 {
 	//����������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
	Link p, q;
	
	if ( (*L).head != (*L).tail )//���ǿձ�
	{
		p = q = (*L).head->next;
		(*L).head->next = NULL;
		
		while ( p != (*L).tail )
		{
			p = q->next;
			free(q);
			q = p;
		}
		free(q);
		(*L).tail = (*L).head;
		(*L).len = 0;
	}//if 	
 }

 void DestroyList(LinkList *L)
 {
 	//������������L��L���ٴ���
	ClearList(L);//�������
	FreeNode( &(*L).head );
	(*L).tail = NULL;
	(*L).len = 0; 
 }
 
 void InsFirst(LinkList *L, Link h, Link s)//�β�����L����Ϊ���޸�L
 {
 	//hָ��L��һ����㣬
    //��h����ͷ��㣬��s��ָ�������ڵ�һ�����֮ǰ 
    s->next = h->next;
    h->next = s;
    
    if (h == (*L).tail)//hָ��β���
	{
		(*L).tail = h->next;//�޸�βָ�� 	
	} 
	(*L).len++; 
 } 
 
 Status DelFirst(LinkList *L, Link h, Link *q)//�β�����L����Ϊ���޸�L 
 {
 	//hָ��L��һ����㣬��h����ͷ��㣬ɾ�������еĵ�һ����㲢��q���ء�
	//������Ϊ��(hָ��β���)��q=NULL,����FALSE
	*q = h->next;
	if (*q)//����ǿ� 
	{
		h->next = (*q)->next;
		if (!h->next)//ɾ��β��� 
		{
			(*L).tail = h;//�޸�βָ�� 
		}
		(*L).len--; 
		return OK;
	}
	else
	{
		return FALSE;//����� 
	}
	
 } 
 
 void Append(LinkList *L, Link s)
 {
 	//��ָ��s(s->dataΪ��һ������Ԫ��)��ָ(�˴���ָ��������NULL��β)�� 
    //һ�������������������L�����һ�����֮�󣬲��ı�����L��βָ��ָ���µ�β���
	int i = 1;
	
	(*L).tail->next = s;
	
	while (s->next)
	{
		s = s->next;
		i++;
	}
	(*L).tail = s;
	(*L).len += i;
 }
 
 Position PriorPos(LinkList L, Link p)
 {
 	//��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ��
	//��λ�á�����ǰ�����򷵻�NULL
	Link q;
	
	q = L.head->next;
	if (q == p)//��ǰ�� 
	{
		return NULL; 
	}
	else
	{
		while (q->next != p)//q����p��ֱ��ǰ�� 
		{
			q = q->next;
		}
		return q; 
	}	
 } 
 
 Status Remove(LinkList *L, Link *q)
 {
 	//ɾ�����Ա�L�е�β��㲢��q���أ��ı�����L��βָ��ָ���µ�β���
	Link p = (*L).head;
	
	if ( (*L).len == 0 )//�ձ�
	{
		*q = NULL;
		return FALSE; 
	}
	while (p->next != (*L).tail)
	{
		p = p->next;
	}
	*q = (*L).tail;
	p->next = NULL;
	(*L).tail = p;
	(*L).len--;
	
	return OK;	
 }
 
 void InsBefore(LinkList *L, Link *p, Link s)
 {
 	//��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮ǰ
	//���޸�ָ��pָ���²���Ľ�� 
	Link q;
	
	q = PriorPos(*L, *p);//q��p��ǰ��
	if (!q)//p��ǰ��
	{
		q = (*L).head; 
	}
	s->next = *p;
	q->next = s;
	*p = s;
	(*L).len++; 
 }
 
 void InsAfter(LinkList *L, Link *p, Link s)
 {
 	//��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮��
	//���޸�ָ��pָ���²���Ľ��
    if (*p == (*L).tail)//�޸�βָ��
	{
		(*L).tail = s; 
	} 
	s->next = (*p)->next;
	(*p)->next = s;
	*p = s;
	(*L).len++;	
 }
 
 void SetCurElem(Link p, ElemType e)
 {
 	//�Ѿ�pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
	p->data = e; 
 }
 
 ElemType GetCurElem(Link p)
 {
 	//��֪pָ�����������е�һ����㣬����p��ָ���������Ԫ�ص�ֵ
	return p->data; 
 }
 
 Status ListEmpty(LinkList L)
 {
 	//����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
	if (L.len)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
 }
 
 int ListLength(LinkList L)
 {
 	//������������L��Ԫ�ظ���
	return L.len; 
 } 
 
 Position GetHead(LinkList L)
 {
 	//������������L��ͷ����λ��
	 return L.head; 
 }
 
 Position GetLast(LinkList L)
 {
 	//������������L�����һ������λ��
	return L.tail; 
 }
 
 Position NextPos(Link p)
 {
 	//��֪pָ����������L�е�һ����㣬����p��ָ����ֱ�Ӻ�̵�λ�á�
    //���޺�̣��򷵻�NULL
	return p->next; 
 }
 
 Status LocatePos(LinkList L, int i, Link *p)
 {
 	//����pָʾ��������L�е�i������λ�ã�������OK��
	//iֵ���Ϸ��Ƿ���ERROR��i=0Ϊͷ���
	int j;
	
	if ((i<0) || (i>L.len))
	{
		return ERROR;
	}
	else
	{
		*p = L.head;
		for(j=1; j<=i; j++)
		{
			*p = (*p)->next;
		}
		return OK;
	}	 
 }
 
 Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
 {
 	//������������L�е�1����e���㺯��compare()�ж���ϵ��Ԫ�ص�λ��
	//��������������Ԫ�أ��򷵻�NULL
	Link p = L.head;
	do
	{
		p = p->next;
	}
	while( p && (compare(p->data, e)) );//û����β��û�ҵ������ϵ��Ԫ��
	
	return p; 	 
 }
 
 void ListTraverse(LinkList L, void(*visit)(ElemType))
 {
 	//���ζ�L��ÿ������Ԫ�ص��ú���visit()
	Link p = L.head->next;
	int j; 
	
	for (j=1; j<=L.len; j++)
	{
		visit(p->data);
		p = p->next;	
	}
	printf("\n");
 }
 
 void OrderInsert(LinkList *L, ElemType e, int (*comp)(ElemType, ElemType))
 {
 	//��֪LΪ��������������Ԫ��e���ǽ��������L�С�������һԪ����ʽ��
	Link o, p, q;
	
	q = (*L).head;
	p = q->next;
	
	while ( (p!=NULL) && (comp(p->data, e)<0) )//p����β����Ԫ��ֵС��e 
	{
		q = p;
		p = p->next;
	}
	o = (Link)malloc(sizeof(LNode));//���ɽ�� 
	o->data = e;//��ֵ 
	q->next = o;//����
	o->next = p;
	(*L).len++;//����1
	if(!p)//���ڱ�β
	{
		(*L).tail = o;//�޸�β��� 
	} 	
 }
 
 Status LocateElemP(LinkList L, ElemType e, Position *q, int(*compare)(ElemType, ElemType)) 
 {
 	//����������L�д�����e�����ж�����compare()ȡֵΪ0��Ԫ�أ���qָʾL��
	//��һ��ֵΪe�Ľ���λ�ã�������TRUE������qָʾ��һ����e�����ж�����
	//compare()ȡֵ>0��Ԫ�ص�ǰ����λ�á�������FALSE��(����һԪ����ʽ) 
	Link p = L.head, pp;
	
	do
	{
		pp = p;
		p = p->next;
	}while( p && (compare(p->data, e) < 0) );
	//û����β��p->data.expn<e.expn
	
	if ( (!p) || (compare(p->data, e) > 0) )//����β��compare(p->data, e)>0
	{
		*q = pp;
		return FALSE; 
	} 
	else//�ҵ� 
	{
		*q = p;
		return TRUE;
	}	
 }
 
 Status equal(ElemType c1, ElemType c2)
 {
 	//�ж��Ƿ���ȵĺ���
	if (c1 == c2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
 }
 
 int comp(ElemType a, ElemType b)
 {
 	//����a<��=��>b���ֱ𷵻�-1��0��1
 	if (a == b)
 	{
 		return 0;
 	}
 	else
 	{
 		return (a-b) / abs(a-b);
 	}
 }
 
 void print(ElemType c)
 {
 	printf("%d ", c);
 }
 void print2(ElemType c)
 {
 	printf("%c ", c);
 }
 
 void print1(ElemType *c)
 {
   printf("%d ", *c);
 }

