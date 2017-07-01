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
 typedef struct //��ı�ʾ������ʽ������ΪLinkList������Ԫ�� 
 {
 	float coef;//ϵ��
    int expn;//ָ�� 
 }term, ElemType;//������������term�������ADT�������������ͣ�
 //ElemTypeΪLinkList�����ݶ�����

  typedef struct LNode /* ������� */
 {
   ElemType data;
   struct LNode *next;
 }LNode,*Link,*Position;

 typedef struct LinkList /* �������� */
 {
   Link head,tail; /* �ֱ�ָ�����������е�ͷ�������һ����� */
   int len; /* ָʾ��������������Ԫ�صĸ��� */
 }LinkList; 
 
 typedef LinkList polynomial;
 #define DestroyPolyn DestroyList //����ͬ�岻ͬ��
 #define PolynLength ListLength //����ͬ�岻ͬ��
 
 void OrderInsertMerge(LinkList *L, ElemType e, int(* compare)(term, term));
 int cmp(term a, term b);//CreatPolyn()�� ʵ�� 
 void CreatPolyn(polynomial *P, int m);
 void PrintPolyn(polynomial P);
 void AddPolyn(polynomial *Pa, polynomial *Pb);
 void AddPolyn1(polynomial *Pa, polynomial *Pb);
 void Opposite(polynomial Pa);
 void SubtractPolyn(polynomial *Pa, polynomial *Pb);
 void MultiplyPolyn(polynomial *Pa, polynomial *Pb);
 void MakeNode(Link *p,ElemType e);
 void FreeNode(Link *p);
 void InitList(LinkList *L);
 void ClearList(LinkList *L);
 void DestroyList(LinkList *L);
 void InsFirst(LinkList *L,Link h,Link s); /* �β�����L,��Ϊ���޸�L */
 Status DelFirst(LinkList *L,Link h,Link *q); /* �β�����L,��Ϊ���޸�L */
 void Append(LinkList *L,Link s);
 Position PriorPos(LinkList L,Link p);
 Status Remove(LinkList *L,Link *q);
 void InsBefore(LinkList *L,Link *p,Link s);
 void InsAfter(LinkList *L,Link *p,Link s);
 void SetCurElem(Link p,ElemType e);
 ElemType GetCurElem(Link p);
 Status ListEmpty(LinkList L);
 int ListLength(LinkList L);
 Position GetHead(LinkList L);
 Position GetLast(LinkList L);
 Position NextPos(Link p);
 Status LocatePos(LinkList L,int i,Link *p);
 Position LocateElem(LinkList L,ElemType e,Status (*compare)(ElemType,ElemType));
 void ListTraverse(LinkList L,void(*visit)(ElemType));
 void OrderInsert(LinkList *L,ElemType e,int (*comp)(ElemType,ElemType));
 Status LocateElemP(LinkList L,ElemType e,Position *q,int(*compare)(ElemType,ElemType));
 
 int main()
 {
   polynomial p,q;
   int m;
   printf("�������1��һԪ����ʽ�ķ�����ĸ�����");
   scanf("%d",&m);
   CreatPolyn(&p,m);
   printf("�������2��һԪ����ʽ�ķ�����ĸ�����");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   AddPolyn(&p,&q);
   printf("2��һԪ����ʽ��ӵĽ����\n");
   PrintPolyn(p);
   printf("�������3��һԪ����ʽ�ķ�����ĸ�����");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   AddPolyn1(&p,&q);
   printf("2��һԪ����ʽ��ӵĽ��(��һ�ַ���)��\n");
   PrintPolyn(p);
   printf("�������4��һԪ����ʽ�ķ�����ĸ�����");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   SubtractPolyn(&p,&q);
   printf("2��һԪ����ʽ����Ľ����\n");
   PrintPolyn(p);
   printf("�������5��һԪ����ʽ�ķ�����ĸ�����");
   scanf("%d",&m);
   CreatPolyn(&q,m);
   MultiplyPolyn(&p,&q);
   printf("2��һԪ����ʽ��˵Ľ����\n");
   PrintPolyn(p);
   DestroyPolyn(&p);
   
   return 0;
 }
 
 void OrderInsertMerge(LinkList *L, ElemType e, int(* compare)(term, term))
 {
 	//�������ж�����compare()��Լ������ֵΪe�Ľ������ϲ�����������L���ʵ�λ��
	Position q, s;
	if ( LocateElemP(*L, e, &q, compare) )//L�д��ڸ�ָ����
	{
		q->data.coef += e.coef;//�ı䵱ǰ���ϵ����ֵ 
		
		if (! q->data.coef)//ϵ��Ϊ0
		{
			//ɾ������ʽL�е�ǰ���
			s = PriorPos(*L, q);//sΪ��ǰ����ǰ��
			if (!s)//q��ǰ��
			{
				s = (*L).head;
			}
			DelFirst(L, s, &q);
			FreeNode(&q);
		}//if	 
	} //if
	else//���ɸ�ָ����������� 
	{
		MakeNode(&s, e);//���ɽ��
		InsFirst(L, q, s); 		
	}	 
 }
 
 int cmp(term a, term b)//CreatPolyn()�� ʵ�� 
 {
 	//��a��ָ��ֵ< ,=��>b��ָ��ֵ���ֱ𷵻�-1��0��+1
	if (a.expn == b.expn)
	{
		return 0;
	} 
	else
	{
		return (a.expn-b.expn) / abs(a.expn-b.expn);
	}
 }
 
 void CreatPolyn(polynomial *P, int m)
 {
 	//����m���ϵ����ָ����������ʾһԪ����ʽ����������P
	Position q, s;
	term e;
	int i;
    
    InitList(P);
    printf("����������%d��ϵ����ָ����\n", m);
    
    for (i=1; i<=m; ++i)
	{
		//��������m��������ɰ�����˳��
		scanf("%f,%d", &e.coef, &e.expn);
		
		if (! LocateElemP(*P, e, &q, cmp))//��ǰ�����в����ڸ�ָ���cmp��ʵ�� 
		{
			MakeNode(&s, e);//���ɽ�㲢��������
			InsFirst(P, q, s); 
		} 	 
	} //for
 }
 
 void PrintPolyn(polynomial P)
 {
 	//��ӡ���һԪ����ʽP
	Link q;
	
	q = P.head->next;//qָ���1����� 
	printf(" ϵ��   ָ��\n");
	
	while (q)
	{
		printf("%f  %d\n", q->data.coef, q->data.expn);
		q = q->next;	
	} 	
 }
 
 void AddPolyn(polynomial *Pa, polynomial *Pb)
 {
 	Position ha, hb, qa, qb;
 	term a, b;
 	
 	ha = GetHead(*Pa);
 	hb = GetHead(*Pb);//ha��hb�ֱ�ָ��Pa��Pb��ͷ���
	//qa��qb�ֱ�ָ��Pa��Pb�е�ǰ��㣨�����ǵ�һ����㣩 
	qa = NextPos(ha);
	qb = NextPos(hb);
	
	while ( (!ListEmpty(*Pa)) && (!ListEmpty(*Pb)) && qa )
	{
		//Pa��Pb���ǿ���haûָ��β���(qa!=0)
		a = GetCurElem(qa);
		b = GetCurElem(qb);//a��bΪ�����е�ǰ�Ƚ�Ԫ��
		
		switch ( cmp(a, b) )
		{
			case -1:
			{
				ha = qa;//����ʽ Pa�е�ǰ����ָ��ֵС
				qa = NextPos(ha);//ha��qa�������һ����� 
			}
			break; 
			case 0:
			{
				//���ߵ�ָ��ֵ��� ���޸�Pa��ǰ����ϵ��ֵ 
				qa->data.coef += qb->data.coef;
				if ( (qa->data.coef) == 0 )//ɾ������ʽPa�е�ǰ��� 
				{
					DelFirst(Pa, ha, &qa);
					FreeNode(&qa); 
				} 
				else
				{
					ha = qa;
				}
				
				DelFirst(Pb, hb, &qb);
				FreeNode(&qb);
				qb = NextPos(hb);
				qa = NextPos(ha);	
			}
			break;
			case 1:
			{
				DelFirst(Pb, hb, &qb);//����ʽPb�е�ǰ����ָ��ֵС
				InsFirst(Pa, ha, qb);
				ha = ha->next;
				qb = NextPos(hb); 
			}
			break;
		} //switch
	} //while
	if (! ListEmpty(*Pb))
	{
		(*Pb).tail = hb;
		Append(Pa, qb);//����Pb��ʣ���� 
	}
	DestroyPolyn(Pb);//����Pb 
 }
 
 void AddPolyn1(polynomial *Pa, polynomial *Pb)
 {
 	//��һ�ֶ���ʽ�ӷ����㷨��Pa=Pa+Pb�� ������һԪ����ʽPb
	Position qb;
	term b;
	
	qb = GetHead(*Pb);//qbָ��Pb��ͷ���
	qb = qb->next;//qbָ��Pb�ĵ�1����� 
	
	while (qb)
	{
		b = GetCurElem(qb);
		OrderInsertMerge(Pa, b, cmp);
		qb = qb->next;	
	} 
	DestroyPolyn(Pb);//����Pb 
 } 
 
 void Opposite(polynomial Pa)
 {
 	//һԪ����ʽPaϵ��ȡ��
	 Position p;
	 
	 p = Pa.head;
	 
	 while (p->next)
	 {
	 	p = p->next;
	 	p->data.coef *= -1; 
 	 } 
 } 
 
 void SubtractPolyn(polynomial *Pa, polynomial *Pb)
 {
 	//����ʽ������Pa=Pa-Pb��������һԪ����ʽPb
	Opposite(*Pb);
	AddPolyn(Pa, Pb); 
 }
 
 void MultiplyPolyn(polynomial *Pa, polynomial *Pb)
 {
 	//����ʽ�˷���Pa=Pa*Pb,������һԪ����ʽPb
	polynomial Pc;
	Position qa, qb;
	term a, b, c;
	
	InitList(&Pc);
	qa = GetHead(*Pa);
	qa = qa->next;
	
	while (qa)
	{
		a = GetCurElem(qa);
		qb = GetHead(*Pb);
		qb = qb->next; 
		while (qb)
		{
		    b = GetCurElem(qb);
		    c.coef = a.coef * b.coef;
			c.expn = a.expn + b.expn;
			OrderInsertMerge(&Pc, c, cmp);
			qb = qb->next;	
		}
		qa = qa->next;
	}//while
	DestroyPolyn(Pb);//����Pb
	ClearList(Pa);//��Pa����Ϊ�ձ�
	(*Pa).head = Pc.head;
	(*Pa).tail = Pc.tail;
	(*Pa).len = Pc.len;
 }
 
 void MakeNode(Link *p,ElemType e)
 { /* ������pָ���ֵΪe�Ľ�㡣������ʧ�ܣ����˳� */
   *p=(Link)malloc(sizeof(LNode));
   if(!*p)
     exit(ERROR);
   (*p)->data=e;
 }

 void FreeNode(Link *p)
 { /* �ͷ�p��ָ��� */
   free(*p);
   *p=NULL;
 }

 void InitList(LinkList *L)
 { /* ����һ���յ���������L */
   Link p;
   p=(Link)malloc(sizeof(LNode)); /* ����ͷ��� */
   if(p)
   {
     p->next=NULL;
     (*L).head=(*L).tail=p;
     (*L).len=0;
   }
   else
     exit(ERROR);
 }

 void ClearList(LinkList *L)
 { /* ����������L����Ϊ�ձ����ͷ�ԭ����Ľ��ռ� */
   Link p,q;
   if((*L).head!=(*L).tail) /* ���ǿձ� */
   {
     p=q=(*L).head->next;
     (*L).head->next=NULL;
     while(p!=(*L).tail)
     {
       p=q->next;
       free(q);
       q=p;
     }
     free(q);
     (*L).tail=(*L).head;
     (*L).len=0;
   }
 }

 void DestroyList(LinkList *L)
 { /* ������������L��L���ٴ��� */
   ClearList(L); /* ������� */
   FreeNode(&(*L).head);
   (*L).tail=NULL;
   (*L).len=0;
 }

 void InsFirst(LinkList *L,Link h,Link s) /* �β�����L,��Ϊ���޸�L */
 { /* hָ��L��һ����㣬��h����ͷ��㣬��s��ָ�������ڵ�һ�����֮ǰ */
   s->next=h->next;
   h->next=s;
   if(h==(*L).tail) /* hָ��β��� */
     (*L).tail=h->next; /* �޸�βָ�� */
   (*L).len++;
 }

 Status DelFirst(LinkList *L,Link h,Link *q) /* �β�����L,��Ϊ���޸�L */
 { /* hָ��L��һ����㣬��h����ͷ��㣬ɾ�������еĵ�һ����㲢��q���ء� */
   /* ������Ϊ��(hָ��β���)��q=NULL������FALSE */
   *q=h->next;
   if(*q) /* ����ǿ� */
   {
     h->next=(*q)->next;
     if(!h->next) /* ɾ��β��� */
       (*L).tail=h; /* �޸�βָ�� */
     (*L).len--;
     return OK;
   }
   else
     return FALSE; /* ����� */
 }

 void Append(LinkList *L,Link s)
 { /* ��ָ��s(s->dataΪ��һ������Ԫ��)��ָ(�˴���ָ����������NULL��β)�� */
   /* һ�������������������L�����һ�����֮�󣬲��ı�����L��βָ��ָ���µ�β��� */
   int i=1;
   (*L).tail->next=s;
   while(s->next)
   {
     s=s->next;
     i++;
   }
   (*L).tail=s;
   (*L).len+=i;
 }

 Position PriorPos(LinkList L,Link p)
 { /* ��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ����λ�á�����ǰ�����򷵻�NULL */
   Link q;
   q=L.head->next;
   if(q==p) /* ��ǰ�� */
     return NULL;
   else
   {
     while(q->next!=p) /* q����p��ֱ��ǰ�� */
       q=q->next;
     return q;
   }
 }

 Status Remove(LinkList *L,Link *q)
 { /* ɾ����������L�е�β��㲢��q���أ��ı�����L��βָ��ָ���µ�β��� */
   Link p=(*L).head;
   if((*L).len==0) /* �ձ� */
   {
     *q=NULL;
     return FALSE;
   }
   while(p->next!=(*L).tail)
     p=p->next;
   *q=(*L).tail;
   p->next=NULL;
   (*L).tail=p;
   (*L).len--;
   return OK;
 }

 void InsBefore(LinkList *L,Link *p,Link s)
 { /* ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮ǰ�� */
   /* ���޸�ָ��pָ���²���Ľ�� */
   Link q;
   q=PriorPos(*L,*p); /* q��p��ǰ�� */
   if(!q) /* p��ǰ�� */
     q=(*L).head;
   s->next=*p;
   q->next=s;
   *p=s;
   (*L).len++;
 }

 void InsAfter(LinkList *L,Link *p,Link s)
 { /* ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮�� */
   /* ���޸�ָ��pָ���²���Ľ�� */
   if(*p==(*L).tail) /* �޸�βָ�� */
     (*L).tail=s;
   s->next=(*p)->next;
   (*p)->next=s;
   *p=s;
   (*L).len++;
 }

 void SetCurElem(Link p,ElemType e)
 { /* ��֪pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ */
   p->data=e;
 }

 ElemType GetCurElem(Link p)
 { /* ��֪pָ�����������е�һ����㣬����p��ָ���������Ԫ�ص�ֵ */
   return p->data;
 }

 Status ListEmpty(LinkList L)
 { /* ����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
   if(L.len)
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { /* ������������L��Ԫ�ظ��� */
   return L.len;
 }

 Position GetHead(LinkList L)
 { /* ������������L��ͷ����λ�� */
   return L.head;
 }

 Position GetLast(LinkList L)
 { /* ������������L�����һ������λ�� */
   return L.tail;
 }

 Position NextPos(Link p)
 { /* ��֪pָ����������L�е�һ����㣬����p��ָ����ֱ�Ӻ�̵�λ�á����޺�̣��򷵻�NULL */
   return p->next;
 }

 Status LocatePos(LinkList L,int i,Link *p)
 { /* ����pָʾ��������L�е�i������λ�ã�������OK��iֵ���Ϸ�ʱ����ERROR��i=0Ϊͷ��� */
   int j;
   if(i<0||i>L.len)
     return ERROR;
   else
   {
     *p=L.head;
     for(j=1;j<=i;j++)
       *p=(*p)->next;
     return OK;
   }
 }

 Position LocateElem(LinkList L,ElemType e,Status (*compare)(ElemType,ElemType))
 { /* ������������L�е�1����e���㺯��compare()�ж���ϵ��Ԫ�ص�λ�ã� */
   /* ��������������Ԫ�أ��򷵻�NULL */
   Link p=L.head;
   do
     p=p->next;
   while(p&&!(compare(p->data,e))); /* û����β��û�ҵ������ϵ��Ԫ�� */
   return p;
 }

 void ListTraverse(LinkList L,void(*visit)(ElemType))
 { /* ���ζ�L��ÿ������Ԫ�ص��ú���visit() */
   Link p=L.head->next;
   int j;
   for(j=1;j<=L.len;j++)
   {
     visit(p->data);
     p=p->next;
   }
   printf("\n");
 }

 void OrderInsert(LinkList *L,ElemType e,int (*comp)(ElemType,ElemType))
 { /* ��֪LΪ��������������Ԫ��e���ǽ��������L�С�(����һԪ����ʽ) */
   Link o,p,q;
   q=(*L).head;
   p=q->next;
   while(p!=NULL&&comp(p->data,e)<0) /* p���Ǳ�β��Ԫ��ֵС��e */
   {
     q=p;
     p=p->next;
   }
   o=(Link)malloc(sizeof(LNode)); /* ���ɽ�� */
   o->data=e; /* ��ֵ */
   q->next=o; /* ���� */
   o->next=p;
   (*L).len++; /* ����1 */
   if(!p) /* ���ڱ�β */
     (*L).tail=o; /* �޸�β��� */
 }

 Status LocateElemP(LinkList L,ElemType e,Position *q,int(*compare)(ElemType,ElemType))
 { /* ����������L�д�����e�����ж�����compare()ȡֵΪ0��Ԫ�أ���qָʾL�� */
   /* ��һ��ֵΪe�Ľ���λ�ã�������TRUE������qָʾ��һ����e�����ж����� */
   /* compare()ȡֵ>0��Ԫ�ص�ǰ����λ�á�������FALSE��(����һԪ����ʽ) */
   Link p=L.head,pp;
   do
   {
     pp=p;
     p=p->next;
   }while(p&&(compare(p->data,e)<0)); /* û����β��p->data.expn<e.expn */
   if(!p||compare(p->data,e)>0) /* ����β��compare(p->data,e)>0 */
   {
     *q=pp;
     return FALSE;
   }
   else /* �ҵ� */
   {
     *q=p;
     return TRUE;
   }
 }
 
 
 
