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

 typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
 typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
 typedef int ElemType; 
 typedef struct LNode
 {
 	ElemType data;
 	struct LNode *next;
 };
 typedef struct LNode *LinkList;
 
 void InitList(LinkList *L);
 void DestroyList(LinkList *L);
 void ClearList(LinkList *L);//�ı�L;
 Status ListEmpty(LinkList L);
 int ListLength(LinkList L);
 Status GetElem(LinkList L, int i, ElemType *e);
 int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
 Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
 Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e); 
 Status ListInsert(LinkList *L, int i, ElemType e);//�ı�L
 Status ListDelete(LinkList *L, int i, ElemType *e);//�ı�L
 void ListTraverse(LinkList L, void(*vi)(ElemType));
 Status equal(ElemType c1, ElemType c2);
 int comp(ElemType a, ElemType b);
 void print(ElemType c);
 void print2(ElemType c);
 void print1(ElemType *c);


    
 
 int main()
 {
   LinkList L;
   ElemType e;
   int j;
   Status i;
   
   InitList(&L); /* ��ʼ����ѭ������L */
   i=ListEmpty(L);
   printf("L�Ƿ�� i=%d(1:�� 0:��)\n",i);
   ListInsert(&L,1,3); /* ��L�����β���3,5 */
   ListInsert(&L,2,5);
   i=GetElem(L,1,&e);
   j=ListLength(L);
   printf("L������Ԫ�ظ���=%d,��1��Ԫ�ص�ֵΪ%d��\n",j,e);
   printf("L�е�����Ԫ������Ϊ��");
   ListTraverse(L,print);
   PriorElem(L,5,&e); /* ��Ԫ��5��ǰ�� */
   printf("5ǰ���Ԫ�ص�ֵΪ%d��\n",e);
   NextElem(L,3,&e); /* ��Ԫ��3�ĺ�� */
   printf("3�����Ԫ�ص�ֵΪ%d��\n",e);
   printf("L�Ƿ�� %d(1:�� 0:��)\n",ListEmpty(L));
   j=LocateElem(L,5,equal);
   if(j)
   {
	 printf("L�ĵ�%d��Ԫ��Ϊ5��\n",j);
   }
   else
   {
	 printf("������ֵΪ5��Ԫ��\n");
   }
   i=ListDelete(&L,2,&e);
   printf("ɾ��L�ĵ�2��Ԫ�أ�\n");
   if(i)
   {
     printf("ɾ����Ԫ��ֵΪ%d,����L�е�����Ԫ������Ϊ��",e);
     ListTraverse(L,print);
   }
   else
   {
     printf("ɾ�����ɹ���\n");
   }
   ClearList(&L);
   printf("���L��L�Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty(L));
   DestroyList(&L);
 	
   return 0;
 }
 
 void InitList(LinkList *L)
 {
 	//�������������һ���յ����Ա�
    *L = (LinkList)malloc(sizeof(struct LNode));//����ͷ��㣬��ʹLָ���ͷ���
	
	if (!*L)//�洢����ʧ��
	{
		exit(OVERFLOW); 
	} 
	(*L)->next = *L;//ָ����ָ��ͷ��� 	 
 }
 
 void DestroyList(LinkList *L)
 {
 	//����������������Ա�L
	 LinkList q, p = (*L)->next;//pָ��ͷ���
	 
	 while (p != *L)//û����β
	 {
	 	q = p->next;
	 	free(p);
	 	p = q;
	 }
	 free(*L);
	 *L = NULL;
 }
 
 void ClearList(LinkList *L)//�ı�L
 {
 	//��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ�
	 LinkList p, q;
	 
	 *L = (*L)->next;//Lָ��ͷ���
	 p = (*L)->next;//pָ���һ�����
	 
	 while (p != *L)//û����β 
	 {
	 	q = p->next;
	 	free(p);
	 	p = q;
	 }
	 (*L)->next = *L;//ͷ���ָ����ָ������ 	  
 }
 
 Status ListEmpty(LinkList L)
 {
 	//��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ���
	 int i = 0;
	 LinkList p = L->next;//pָ��ͷ���
	 
	 while (p != L)//û����β 
	 {
	 	i++;
	 	p =  p->next;
	 }
	 
	 return i; 
 }
 
 int ListLength(LinkList L)
 {
 	//��ʼ����:L�Ѵ��ڡ��������:����L������Ԫ�ظ���
    int i = 0;
	LinkList p = L->next;//pָ��ͷ���
	
	while (p != L)//û����β 
	{
		i++;
		p = p->next; 
	}
	
	return i;
 }
 
 Status GetElem(LinkList L, int i, ElemType *e)
 {
 	//����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
 	int j = 1;//��ʼ����jΪ������
    LinkList p = L->next->next;//pָ���һ�����
	if ( (i<=0) || (i>ListLength(L)) )//��i��Ԫ�ز�����
	{
		return ERROR;
	}
	
	while (j<i)
	{
		//˳ָ�������ң�֪��pָ���i��Ԫ��
		p = p->next;
		j++; 
	}
	*e = p->data;//ȡ��i��Ԫ�� 
	
	return OK; 
 }
 
 int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
 {
 	//��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����
	//�������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ��
	//������������Ԫ�ز����ڣ��򷵻�ֵΪ0
	int i = 0;
	LinkList p = L->next->next;//pָ���һ�����
	
	while (p != L->next)
	{
		i++;
		if (compare(p->data, e))//�����ϵ
		{
			return i;
		}
		p = p->next;
	}
	
	return 0;	 
 }
 
 Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	//��ʼ���������Ա�L�Ѵ���
	//�����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��
	//�������ʧ�ܣ�pre_e�޶���
	LinkList q, p = L->next->next;//pָ���һ�����
	
	q = p->next;
	
	while (q != L->next)//pû����β
	{
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return TRUE;
		}
		p = q;
		q = q->next;
	}
	
	return FALSE;//����ʧ�� 
}

Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e) 
{
	//��ʼ���������Ա�L�Ѵ���
	//�����������cur_e��L������Ԫ�أ�
	//�Ҳ������һ��������next_e�������ĺ��
	//�������ʧ�ܣ�next_e������
	LinkList p = L->next->next;//pָ���һ�����
	while (p != L)//pû����β 
	{
		if (p->data == cur_e)
		{
			*next_e = p->next->data;
			return TRUE;
		}
		p = p->next;
	}//while
	return FALSE;//����ʧ�� 
}

Status ListInsert(LinkList *L, int i, ElemType e)//�ı�L
{
	//��L�ĵ�i��λ��֮ǰ����Ԫ��e
	LinkList p = (*L)->next, s;//pָ��ͷ���
	int j = 0;
	if ( i<=0 || i>(ListLength(*L) + 1) )//�޷��ٵ�i��Ԫ��֮ǰ����
	{
		return ERROR; 
	} 
	
	while (j < i-1)//Ѱ�ҵ�i-1�����
	{
		p = p->next;
		j++; 
	} 
	
	s = (LinkList)malloc(sizeof(struct LNode));//�����½ڵ�
	s->data = e;//����L��
	s->next = p->next;
	p->next = s;
	if (p == *L)//�ı�β��� 
	{
		*L = s;
	}
	
	return OK; 
} 

Status ListDelete(LinkList *L, int i, ElemType *e)//�ı�L
{
	//ɾ��L�ĵ�i��Ԫ�أ�����e������ֵ
	LinkList p = (*L)->next, q;//pָ��ͷ���
	int j = 0;
	if (i<=0 || i>ListLength(*L))//��i��Ԫ�ز�����
	{
		return ERROR; 
	} 
	
	while (j < i-1)//Ѱ�ҵ�i-1����� 
	{
		p = p->next;
		j++; 
	}
	q = p->next;//qָ���ɾ�����
	p->next = q->next;
	*e = q->data;
	
	if (*L == q)//ɾ�����Ǳ�βԪ�� 
	{
		*L = p;
	}
	free(q);//�ͷŴ�ɾ�����
	
	return OK; 
} 

void ListTraverse(LinkList L, void(*vi)(ElemType))
{
	//��ʼ������L�Ѵ��ڡ�
	//��������� ���ζ�L��ÿ������Ԫ�ص��� ����vi()
	LinkList p = L->next->next;//ָ����Ԫ���
	
	while (p != L->next)//p��ָ��ͷ��� 
	{
		vi(p->data);
		p = p->next; 
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
	printf("%d", *c);
}

 
 
