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
	struct LNode * next;
};
typedef struct LNode *LinkList;

void InitList(LinkList *L);
void DestroyList(LinkList *L);
void ClearList(LinkList L);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
Status GetElem(LinkList L, int i, ElemType *e);
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
Status ListInsert(LinkList L, int i, ElemType e);
Status ListDelete(LinkList L, int i, ElemType *e);
void ListTraverse(LinkList L, void (*vi)(ELemType));

Status equal(ElemType c1, ElemType c2);
int comp(ElemType a, ElemType b);
void print(ElemType c);
void print1(ElemType *c);
void print2(ElemType c);

int main()
{	 
   LinkList L; /* ��main2-1.c��ͬ */
   ElemType e,e0;
   Status i;
   int j,k;
   InitList(&L);
   for(j=1;j<=5;j++)
     i=ListInsert(L,1,j);
   printf("��L�ı�ͷ���β���1��5��L=");
   ListTraverse(L,print); /* ���ζ�Ԫ�ص���print()�����Ԫ�ص�ֵ */
   i=ListEmpty(L);
   printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);
   ClearList(L);
   printf("���L��L=");
   ListTraverse(L,print);
   i=ListEmpty(L);
   printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);
   for(j=1;j<=10;j++)
     ListInsert(L,j,j);
   printf("��L�ı�β���β���1��10��L=");
   ListTraverse(L,print);
   GetElem(L,5,&e);
   printf("��5��Ԫ�ص�ֵΪ��%d\n",e);
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,j,equal);
     if(k)
       printf("��%d��Ԫ�ص�ֵΪ%d\n",k,j);
     else
       printf("û��ֵΪ%d��Ԫ��\n",j);
   }
   for(j=1;j<=2;j++) /* ����ͷ�������� */
   {
     GetElem(L,j,&e0); /* �ѵ�j�����ݸ���e0 */
     i=PriorElem(L,e0,&e); /* ��e0��ǰ�� */
     if(i==INFEASIBLE)
       printf("Ԫ��%d��ǰ��\n",e0);
     else
       printf("Ԫ��%d��ǰ��Ϊ��%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++) /* ����������� */
   {
     GetElem(L,j,&e0); /* �ѵ�j�����ݸ���e0 */
     i=NextElem(L,e0,&e); /* ��e0�ĺ�� */
     if(i==INFEASIBLE)
       printf("Ԫ��%d�޺��\n",e0);
     else
       printf("Ԫ��%d�ĺ��Ϊ��%d\n",e0,e);
   }
   k=ListLength(L); /* kΪ�� */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,j,&e); /* ɾ����j������ */
     if(i==ERROR)
       printf("ɾ����%d��Ԫ��ʧ��\n",j);
     else
       printf("ɾ����%d��Ԫ�سɹ�����ֵΪ��%d\n",j,e);
   }
   printf("�������L��Ԫ�أ�");
   ListTraverse(L,print);
   DestroyList(&L);
   printf("����L��L=%u\n",L);
   
   return 0;
}

void InitList(LinkList *L)
{
	/*�������������һ���յ����Ա�*/ 
	*L = (LinkList)malloc(sizeof(struct LNode));/*����ͷ��㣬��ʹLָ���ͷ���*/ 
	
	if (!*L)
	{
		exit(OVERFLOW);/*�洢����ʧ��*/ 
	}
	(*L)->next = NULL;/*ָ����Ϊ��*/	
}

void DestroyList(LinkList *L)
{
	/*��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L*/
	LinkList q;
	
	while (*L)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}
}

void ClearList(LinkList L)/*���ı�L*/
{
	LinkList p, q;
	
	p = L->next;/*pָ���һ���ڵ�*/
	while (p)/*û��β��*/
	{
		q = p->next;
		free(p);
		p = q;
	}	
	
	L->next = NULL;/*ͷ���ָ����Ϊ��*/
}

Status ListEmpty(LinkList L)
{
	/*��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE*/
	if (L->next)/*�ǿ�*/
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
	/*��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ���*/
	int i = 0;
	LinkList p = L->next;/*pָ���һ�����*/
	
	while (p)/*û����β*/
	{
		i++;
		p = p->next;
	}
	return i; 	
}

Status GetElem(LinkList L, int i, ElemType *e)
{
	/*LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR*/
	int j = 1;/*jΪ������*/
	LinkList p = L->next;/*pָ���һ�����*/
	
	while (p && j<i)/*˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��*/
	{
		p = p->next;
		j++;
	}
	
	if (!p || j>i)/*��i��Ԫ�ز�����*/
	{
		return ERROR;
	}
	
	*e = p->data;/*ȡ��i��Ԫ��*/
	
	return OK; 	
}

int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	/*��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����������Ϊ1������Ϊ0��*/
	/*�������������L�е�1����e�����ϵcompare����������Ԫ�ص�λ��*/
	/*������������Ԫ�ز����ڣ��򷵻�ֵΪ0*/
	
	int i = 0;
	LinkList p = L->next;
	
	while (p)
	{
		i++;
		if ( compare(p->data, e) )/*�ҵ�������Ԫ��*/
		{
			return i;
		}
		p = p->next;  
	}
	
	return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	/*��ʼ���������Ա�L�Ѵ���*/
	/*�����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ����*/
	/*           ����OK���������ʧ�ܣ�pre_e�޶��壬����INFEASIBLE*/
	LinkList q, p = L->next;/*pָ���һ�����*/
	
	while (p->next)/*p��ָ����к��*/ 
	{
		q = p->next;/*qΪp�ĺ��*/
		
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;/*p�����*/
	}
	return INFEASIBLE; 	 
}

Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	/*��ʼ���������Ա�L�Ѵ���*/
	/*�����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣�*/
	/*          ����OK���������ʧ�ܣ�next_e�޶��壬����INFEASIBLE*/
	LinkList p = L->next;/*pָ���һ�����*/
	
	while (p->next)/*p��ָ����к��*/
	{
		if (p->data == cur_e)
		{
			*next_e = p->next->data;
			return OK;
		}
		p = p->next;
	} 
	
	return INFEASIBLE;
}

Status ListInsert(LinkList L, int i, ElemType e)/*���ı�L*/
{
	/*�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e*/
	int j = 0;
	LinkList p = L, s;
	
	while ( p && j<(i-1) )/*Ѱ�ҵ�i-1�����*/ 
	{
		p = p->next;
		j++;
	}
	
	if ( !p || j>(i-1) )/*iС��1���ߴ��ڱ�*/
	{
		return ERROR; 
	} 
	s = (LinkList)malloc( sizeof(struct LNode) );/*�����½��*/
	s->data = e;/*����L��*/
	s->next = p->next;
	p->next = s;
	
	return OK; 	 
}

Status ListDelete(LinkList L, int i, ElemType *e)/*���ı�L*/
{
	/*�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ*/
	int j = 0;
	LinkList p = L, q;
	
	while ( p->next && j<(i-1) )/*Ѱ�ҵ�i����㣬����pָ����ǰ��*/
	{
		p = p->next;
		j++;		 
	}
	
	if ( (!p->next) || j>(i-1) )/*ɾ��λ�ò�����*/
	{
		return ERROR;
	} 
	
	q = p->next;/*ɾ�����ͷŽ��*/
	p->next = q->next;
	*e = q->data;
	free(q); 
	
	return OK;
}

void ListTraverse(LinkList L, void (*vi)(ELemType))
{
	/*vi���β�����ΪElemType*/
	/*��ʼ���������Ա�L�Ѵ��ڡ�������������ζ�L��ÿ������Ԫ�ص��ú���vi()*/
	
	LinkList p = L->next;
	
	while (p)
	{
		vi(p->data);
		p = p->next;
	}
	
	printf("\n");
}

Status equal(ElemType c1, ElemType c2)
{
	/*�ж��Ƿ���ȵĺ���*/
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
	/*����a<,=��>b,�ֱ𷵻�-1,0��1*/
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
	printf("%d", c);
}

void print1(ElemType *c)
{
	printf("%d", *c);	
}

void print2(ElemType c)
{
	printf("%c", c);
}
