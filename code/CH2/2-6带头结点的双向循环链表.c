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
 
 typedef struct DuLNode
 {
 	ElemType data;
 	struct DuLNode *prior, *next;
 }DuLNode, *DuLinkList;
 
  void InitList(DuLinkList *L);
  void DestroyList(DuLinkList *L);
  void ClearList(DuLinkList L);
  Status ListEmpty(DuLinkList L);
  int ListLength(DuLinkList L);
  Status GetElem(DuLinkList L, int i, ElemType *e);
  int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
  Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e);
  Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e);
  DuLinkList GetElemP(DuLinkList L, int i);
  Status ListInsert(DuLinkList L, int i, ElemType e);
  Status ListDelete(DuLinkList L, int i, ElemType *e);
  void ListTraverse(DuLinkList L, void(*visit)(ElemType));
  void ListTraverseBack(DuLinkList L, void(*visit)(ElemType));
  Status equal(ElemType c1, ElemType c2);
  int comp(ElemType a, ElemType b);
  void print(ElemType c);
  void print2(ElemType c);
  void print1(ElemType *c); 
 
 int main()
 {
   DuLinkList L;
   int i,n;
   Status j;
   ElemType e;
   
   InitList(&L);
   
   for(i=1;i<=5;i++)
   { 
	 ListInsert(L,i,i); /* �ڵ�i�����֮ǰ����i */
   }
   printf("�����������");
   ListTraverse(L,print); /* ������� */
   printf("�����������");
   ListTraverseBack(L,print); /* ������� */
   n=2;
   ListDelete(L,n,&e); /* ɾ�����ͷŵ�n����� */
   printf("ɾ����%d����㣬ֵΪ%d��������Ϊ��",n,e);
   ListTraverse(L,print); /* ������� */
   printf("�����Ԫ�ظ���Ϊ%d\n",ListLength(L));
   printf("�����Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty(L));
   ClearList(L); /* ������� */
   printf("��պ������Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty(L));
   for(i=1;i<=5;i++)
   {
     ListInsert(L,i,i); /* ���²���5����� */
   }
   ListTraverse(L,print); /* ������� */
   n=3;
   j=GetElem(L,n,&e); /* ������ĵ�n��Ԫ�ظ�ֵ��e */
   if(j)
   {
     printf("����ĵ�%d��Ԫ��ֵΪ%d\n",n,e);
   }
   else
   {
     printf("�����ڵ�%d��Ԫ��\n",n);
   }
   n=4;
   i=LocateElem(L,n,equal);
   if(i)
   {
     printf("����%d��Ԫ���ǵ�%d��\n",n,i);
   }
   else
   {
     printf("û�е���%d��Ԫ��\n",n);
   }
   j=PriorElem(L,n,&e);
   if(j)
   {
     printf("%d��ǰ����%d\n",n,e);
   }
   else
   {
     printf("������%d��ǰ��\n",n);
   }
   j=NextElem(L,n,&e);
   if(j)
   {
     printf("%d�ĺ����%d\n",n,e);
   }
   else
   {
     printf("������%d�ĺ��\n",n);
   }
   DestroyList(&L);
   
   return 0;
 }
 
 void InitList(DuLinkList *L)
 {
 	//�����յ�˫��ѭ������L
	 *L = (DuLinkList)malloc(sizeof(DuLNode));
	 
	 if (*L)
	 {
	 	(*L)->next = (*L)->prior = *L;
	 }
	 else
	 {
	 	exit(OVERFLOW);
	 }  
 }
 
 void DestroyList(DuLinkList *L)
 {
 	//�������������˫��ѭ������L
    DuLinkList q, p = (*L)->next;//pָ���һ�����
	
	while (p != *L)//pû����ͷ
	{
		q = p->next;
		free(p);
		p = q; 
	} 
	free(*L);
	*L = NULL; 
 }
 
 void ClearList(DuLinkList L)//���ı�L
 {
 	//��ʼ������L�Ѵ��ڡ������������L����Ϊ�ձ� 
 	DuLinkList q, p = L->next;//pָ���һ�����
	
	while (p != L)//pû����ͷ
	{
		q = p->next;
		free(p);
		p = q;
	}
	
	L->next = L->prior = L;//ͷ��������ָ�����ָ������ 
 }
 
 Status ListEmpty(DuLinkList L)
 {
 	//��ʼ���������Ա�L�Ѵ��ڡ�
    //�����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
	if ( (L->next==L) && (L->prior==L) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
 }
 
 int ListLength(DuLinkList L)
 {
 	//��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ���
	int i = 0;
	
	DuLinkList p = L->next;//pָ���һ�����
	
	while (p != L)//pû����ͷ
	{
		i++;
		p = p->next; 
	} 
	
	return i;	 
 }
 
 Status GetElem(DuLinkList L, int i, ElemType *e)
 {
 	//����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
 	int j = 1;//jΪ������
	DuLinkList p = L->next;//pָ���һ�����
	
	while ( (p!=L) && (j<i) )
	//˳ָ��������,ֱ��pָ���i��Ԫ�ػ�pָ��ͷ��� 
 	{
 		p = p->next;
		j++; 
    } 
    
    if ( (p==L) || (j>i) )//��i��Ԫ�ز����� 
    {
    	return ERROR; 	
    }
    
    *e = p->data;//ȡ��i��Ԫ��
	
	return OK;	 
 }
 
 int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
 {
 	//��ʼ������L�Ѵ��ڣ�compare()������Ԫ���ж�����
	//�������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ��
	//������������Ԫ�ز����ڣ��򷵻�ֵΪ0 
	int i = 0;
	DuLinkList p = L->next;//pָ���i��Ԫ��
	
	while (p != L)
	{
		i++;
		if (compare(p->data, e))//�ҵ�����������Ԫ�� 
		{
			return i; 
		}
		p = p->next;
	}
	
	return 0;
 }
 
 Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e)
 {
 	//�����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ����
	//�������ʧ�ܣ�pre_e�޶���
	DuLinkList p = L->next->next;//pָ���2��Ԫ��
	
	while (p != L)//pû����ͷ
	{
		if (p->data == cur_e)
		{
			*pre_e = p->prior->data;
			return TRUE;
		}
		p = p->next;
	}  
	
	return FALSE;
 }
 
 Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e)
 {
 	//�����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣�
	//�������ʧ�ܣ�next_e�޶���
	DuLinkList p = L->next->next;//pָ���2��Ԫ��
	while (p != L)//pû����ͷ 
	{
		if (p->prior->data == cur_e)
		{
			*next_e = p->data;
			return TRUE;
		}
		p = p->next;	
	}//while
	
	return FALSE;
 }
 
 DuLinkList GetElemP(DuLinkList L, int i)//����ӵ�
 {
 	//��˫������L�з��ص�i��Ԫ�صĵ�ַ��
	//iΪ0������ͷ���ĵ�ַ������i��Ԫ�ز�����
	//����NULL
	int j;
	
	DuLinkList p = L;//pָ��ͷ���
	
	if ( (i<0) || (i>ListLength(L)) )//iֵ���Ϸ�
	{
		return NULL; 
	} 
	
	for (j=1; j<=i; j++)
	{
		p = p->next;
	}
	
	return p;	 
 }
 
 Status ListInsert(DuLinkList L, int i, ElemType e)
 {
 	//�ڴ�ͷ����˫ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e��
	//i�ĺϷ�ֵΪ1<=i<=��+1
	//�����ϵĽ����˸Ľ������޷��ٵڱ�+1�����֮ǰ����Ԫ��
	DuLinkList p, s;
	
	if ( (i<1) || (i > ListLength(L)+1))//iֵ���Ϸ�
	{
		return ERROR; 
	} 
	
	p = GetElemP(L, i-1);//��L��ȷ����i��Ԫ��ǰ����λ��ָ��p
	if (!p)//p=NULL,����i��Ԫ�ص�ǰ�������ڣ���ͷ���Ϊ��1��Ԫ�ص�ǰ���� 
	{
		return ERROR;
	}
	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (!s)
	{
		return OVERFLOW;
	}
	s->data = e;
	s->prior = p;//�ڵ�i-1��Ԫ��֮�����
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	
	return OK; 	
 }
 
 Status ListDelete(DuLinkList L, int i, ElemType *e)
 {
 	//ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ�أ�
    //i�ĺϷ�ֵΪ1<=i<=��
	DuLinkList p;
	if (i<1)//iֵ���Ϸ�
	{
		return ERROR; 
	} 
	p = GetElemP(L, i);//��L��ȷ����i��Ԫ�ص�λ��ָ��p
	if (!p)//p=NULL������i��Ԫ�ز�����
	{
		return ERROR; 
	} 
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	
	return OK;
 }
 
 void ListTraverse(DuLinkList L, void(*visit)(ElemType))
 {
 	//��˫ѭ�����Ա�L��ͷ�������������ÿ������Ԫ�ص��ú���visit()
	DuLinkList p = L->next;//pָ��ͷ���
	
	while (p != L)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n");	
 }
 
 void ListTraverseBack(DuLinkList L, void(*visit)(ElemType))
 {
 	//��˫��ѭ�����Ա�L��ͷ�������������ÿ������Ԫ�ص��ú���visit()��
	//���
	DuLinkList p = L->prior;//pָ��β���
	
	while (p != L)
	{
		visit(p->data);
		p = p->prior;
	}
	printf("\n");	 
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
 
 
 
 
 
 
 
 
  

