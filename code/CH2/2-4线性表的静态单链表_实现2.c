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

#define MAX_SIZE 100/*�������󳤶�*/
#define DestroyList ClearList
//DestroyList()��ClearList()�Ĳ�����һ���� 
typedef int Status;
typedef int ElemType;
typedef struct 
{
	ElemType data;
	int cur;
}component, SLinkList[MAX_SIZE];

int Malloc(SLinkList space);
void Free(SLinkList space, int k);
void InitSpace(SLinkList L);
int InitList(SLinkList L);
void ClearList(SLinkList L, int n);
Status ListEmpty(SLinkList L, int n);
int ListLength(SLinkList L, int n);
Status GetElem(SLinkList L, int n, int i, ElemType *e);
int LocateElem(SLinkList L, int n, ElemType e);
Status PriorElem(SLinkList L, int n, ElemType cur_e, ElemType *pre_e);
Status NextElem(SLinkList L, int n, ElemType cur_e, ElemType *next_e);
Status ListInsert(SLinkList L, int n, int i, ElemType e);
Status ListDelete(SLinkList L, int n, int i, ElemType *e);
void ListTraverse(SLinkList L, int n, void(*vi)(ElemType));
Status equal(ElemType c1, ElemType c2);
int comp(ElemType a, ElemType b);
void print(ElemType c);
void print1(ElemType *c);
void print2(ElemType c);


int main()
{
	 int j,k,La,Lb;
   Status i;
   ElemType e,e0;
   SLinkList L;
   InitSpace(L); /* ������������ */
   La=InitList(L); /* ��ʼ������La */
   Lb=InitList(L); /* ��ʼ������Lb */
   printf("La��շ�%d(1:�� 0:��) La�ı�=%d\n",ListEmpty(L,La),ListLength(L,La));
   for(j=1;j<=5;j++)
     ListInsert(L,La,1,j);
   printf("�ڿձ�La�ı�ͷ���β���1��5��La=");
   ListTraverse(L,La,print);
   for(j=1;j<=5;j++)
     ListInsert(L,Lb,j,j);
   printf("�ڿձ�Lb�ı�β���β���1��5��Lb=");
   ListTraverse(L,Lb,print);
   printf("La��շ�%d(1:�� 0:��) La�ı�=%d\n",ListEmpty(L,La),ListLength(L,La));
   ClearList(L,La);
   printf("���La��La=");
   ListTraverse(L,La,print);
   printf("La��շ�%d(1:�� 0:��) La�ı�=%d\n",ListEmpty(L,La),ListLength(L,La));
   for(j=2;j<8;j+=5)
   {
     i=GetElem(L,Lb,j,&e);
     if(i)
       printf("Lb��ĵ�%d��Ԫ�ص�ֵΪ��%d\n",j,e);
     else
       printf("Lb�����ڵ�%d��Ԫ�أ�\n",j,e);
   }
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,Lb,j);
     if(k)
       printf("Lb����ֵΪ%d��Ԫ���ھ�̬�����е�λ��Ϊ%d\n",j,k);
     else
       printf("Lb����û��ֵΪ%d��Ԫ��\n",j);
   }
   for(j=1;j<=2;j++) /* ����ͷ�������� */
   {
     GetElem(L,Lb,j,&e0); /* �ѵ�j�����ݸ���e0 */
     i=PriorElem(L,Lb,e0,&e); /* ��e0��ǰ�� */
     if(!i)
       printf("Lb���е�Ԫ��%d��ǰ��\n",e0);
     else
       printf("Lb����Ԫ��%d��ǰ��Ϊ��%d\n",e0,e);
   }
   for(j=ListLength(L,Lb)-1;j<=ListLength(L,Lb);j++) /* ����������� */
   {
     GetElem(L,Lb,j,&e0); /* �ѵ�j�����ݸ���e0 */
     i=NextElem(L,Lb,e0,&e); /* ��e0�ĺ�� */
     if(!i)
       printf("Lb����Ԫ��%d�޺��\n",e0);
     else
       printf("Lb����Ԫ��%d�ĺ��Ϊ��%d\n",e0,e);
   }
   k=ListLength(L,Lb); /* kΪ�� */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,Lb,j,&e); /* ɾ����j������ */
     if(i)
       printf("Lb���е�%d��Ԫ��Ϊ%d,��ɾ����\n",j,e);
     else
       printf("ɾ��Lb���е�%d��Ԫ��ʧ��(�����ڴ�Ԫ��)��\n",j);
   }
   printf("�������Lb��Ԫ�أ�");
   ListTraverse(L,Lb,print); /* ���ζ�Ԫ�ص���print()�����Ԫ�ص�ֵ */
	

	return 0;
}

int Malloc(SLinkList space)
{
	//����������ǿգ��򷵻ط���Ľ���±꣨��������ĵ�һ����㣩�����򷵻�0
	int i = space[0].cur;
	if (i)//��������ǿ�
	{
		space[0].cur = space[i].cur;
		//���������ͷ���ָ��ԭ��������ĵڶ������ 
	} 
	
	return i;//�����¿��ٵĽ������ 
}

void Free(SLinkList space, int k)
{
	//���±�Ϊk�Ŀ��н����յ�����������Ϊ��������ĵ�һ��㣩
	space[k].cur = space[0].cur;//���ս��ġ��αꡱָ��������ĵ�һ����� 
	space[0].cur = k;//���������ͷ���ָ���»��յĽ�� 
}

void InitSpace(SLinkList L)
{
	//��һά����L�и���������һ����������L[0].curΪͷ�ļ�����0����ʾ��ָ��
	int i;
	
	for (i=0; i<MAX_SIZE-1; i++)
	{
		L[i].cur = i + 1;
	}
	L[MAX_SIZE-1].cur = 0;
}

int InitList(SLinkList L)
{
	//����һ������������ֵΪ�ձ��������е�λ�� 
	int i;
	
	i = Malloc(L);//����Malloc(),�򻯳���
	L[i].cur = 0;//������ı�ͷָ��Ϊ��(0)
	
	return i; 
}

void ClearList(SLinkList L, int n)
{
	//��ʼ������L�б�ͷλ��Ϊn�ľ�̬�����Ѵ��ڡ�������������˱�����Ϊ�ձ�
	int j, k, i = L[n].cur;//�����һ������λ��
	
	L[n].cur = 0;//�����
	k = L[0].cur;//���������һ������λ��
	L[0].cur = i;//������Ľ��������������ı�ͷ
	
	while (i)//û������β
	{
		j = i;
		i = L[i].cur;//ָ����һ��Ԫ�� 	 
	}
	 
	L[j].cur = k;//��������ĵ�һ�����ӵ������β�� 
}

Status ListEmpty(SLinkList L, int n)
{
	//�ж�L�б�ͷλ��Ϊn�������Ƿ�Ϊ�գ����ǿձ���TRUE�����򷵻�FALSE
	if (0 == L[n].cur)//�ձ�
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int ListLength(SLinkList L, int n)
{
	//����L�б�ͷλ��Ϊn�����������Ԫ�ظ���
	int j = 0, i = L[n].cur;//iָ���һ��Ԫ��
	while (i)//û����̬����β
	{
		i = L[i].cur;//ָ����һ��Ԫ��
		j++;
	} 

	return j; 
}

Status GetElem(SLinkList L, int n, int i, ElemType *e)
{
	//��e����L�б�ͷλ��Ϊn������ĵ�i��Ԫ�ص�ֵ
	int l, k = n;//kָ���ͷ���
	
	if ( (i<1) || (i>ListLength(L, n)) )//iֵ������
	{
		return ERROR;		 
	} 
	
	for (l=1; l<=i; l++)//�ƶ�i-1��Ԫ�� 
	{
		k = L[k].cur;
	}
	*e = L[k].data; 
	
	return OK;	 
}

int LocateElem(SLinkList L, int n, ElemType e)
{
	//��L�б�ͷλ��Ϊn�ľ�̬�������в��ҵ�1��ֵΪe��Ԫ��
	//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0.
	//��������LocateElem()�Ķ��岻ͬ�� 
	int i = L[n].cur;//iָʾ���е�һ�����
	while ( i && (L[i].data != e) )//�ڱ���˳�����ң�e����ʹ�ַ�����
	{
		i = L[i].cur;
	}
	
	return i;	
}

Status PriorElem(SLinkList L, int n, ElemType cur_e, ElemType *pre_e)
{
	//��ʼ��������L�б�ͷλ��Ϊn�ľ�̬�������Ѵ���
	//�����������cur_e�Ǵ˵����������Ԫ�أ��Ҳ��ǵ�һ��
	//����pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶���
	int j, i = L[n].cur;//iΪ�����һ������λ��
	
	do
	{
		//����ƶ����
		j = i;
		i = L[i].cur; 
	}while( i && (cur_e != L[i].data) );
	
	if (i)//�ҵ���Ԫ��
	{
		*pre_e = L[j].data;
		return OK; 
	}
	 
	 return ERROR;
} 

Status NextElem(SLinkList L, int n, ElemType cur_e, ElemType *next_e)
{
	//��ʼ��������L�б�ͷλ��Ϊn�ľ�̬�������Ѵ���
	//�����������cur_e�Ǵ˵����������Ԫ���Ҳ������һ��
	//����next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶���
	int i;
	
	i = LocateElem(L, n, cur_e);
	//�������в��ҵ�һ��ֵΪcur_e��Ԫ�ص�λ��
	if (i)//�ھ�̬�������д���Ԫ��cur_e
	{
		i = L[i].cur;//cur_e�ĺ�̵�λ��
		if (i)//cur_e�к��
		{
			*next_e = L[i].data;
			return OK;//cur_eԪ���к�� 
		}	 
	}
	 return ERROR;//L������cur_eԪ�أ�cur_eԪ���޺�� 	 
}

Status ListInsert(SLinkList L, int n, int i, ElemType e)
{
	//��L�б�ͷλ��Ϊn������ĵ�i��Ԫ��֮ǰ�����µ�����Ԫ��e 
	int l, j, k = n;//kָ���ͷ��
	
	if ( (i<1) || (i>ListLength(L, n) + 1) )
	{
		return ERROR;	
	}
	j = Malloc(L);//�����µ�Ԫ
	
	if (j)//����ɹ�
	{
		L[j].data = e;//��ֵ���µ�Ԫ
		
		for (l=1; l<i; l++)//�α�����ƶ�i-1��Ԫ��
		{
			k = L[k].cur;
		} 
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return OK;
	} 
	
	return ERROR;
}

Status ListDelete(SLinkList L, int n, int i, ElemType *e)
{
	//ɾ����L�б�ͷΪ��Ϊn������ĵ�i������Ԫ��e����������ֵ
	int j, k = n;
	
	if ( (i<1) || (i>ListLength(L, n)) )
	{
		return ERROR;
	}
	
	for (j=1; j<i; j++)//�α�����ƶ�i-1��Ԫ�� 
	{
		k = L[k].cur;
	}
	j = L[k].cur;
	L[k].cur = L[j].cur;
	*e = L[j].data;
	Free(L, j);
	
	return OK; 	 
}

void ListTraverse(SLinkList L, int n, void(*vi)(ElemType))
{
	//���ζ�L�б�ͷλ��Ϊn�������ÿ������Ԫ�ص��ú���vi����
	int i = L[n].cur;//ָ���һ��Ԫ��
	
	while (i)//û����̬����β 
	{
		vi(L[i].data);//����vi���� 
	    i = L[i].cur;//ָ����һ��Ԫ�� 
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
	//����a<,=��>b,�ֱ𷵻�-1,0��1
	if (a == b)
	{
		return 0;
	}
	else
	{
		return (a-b)/abs(a-b);
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


