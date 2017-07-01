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
 #define LIST_INIT_SIZE 10 /* ���Ա�洢�ռ�ĳ�ʼ������ */
 #define LIST_INCREMENT 2 /* ���Ա�洢�ռ�ķ������� */
 typedef struct
 {
   ElemType *elem; /* �洢�ռ��ַ */
   int length; /* ��ǰ���� */
   int listsize; /* ��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ) */
 }SqList;
 
 
 Status equal(ElemType c1,ElemType c2)
 { /* �ж��Ƿ���ȵĺ��� */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 int comp(ElemType a,ElemType b)
 { /* ����a<��=��>b���ֱ𷵻�-1��0��1 */
   if(a==b)
     return 0;
   else
     return (a-b)/abs(a-b);
 }

 void print(ElemType c)
 {
   printf("%d ",c);
 }

 void print2(ElemType c)
 {
   printf("%c ",c);
 }

 void print1(ElemType *c)
 {
   printf("%d ",*c);
 }
 
 
 Status sq(ElemType c1,ElemType c2)
 { /* ����Ԫ���ж�����(ƽ����ϵ)��LocateElem()���õĺ��� */
   if(c1==c2*c2)
     return TRUE;
   else
     return FALSE;
 }

 void dbl(ElemType *c)
 { /* ListTraverse()���õ���һ����(Ԫ��ֵ�ӱ�) */
   *c*=2;
 }

 void InitList(SqList *L);
 void DestroyList(SqList *L);
 void ClearList(SqList *L);
 Status ListEmpty(SqList L);
 int ListLength(SqList L);
 Status GetElem(SqList L,int i,ElemType *e);
 int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType));
 Status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e);
 Status NextElem(SqList L,ElemType cur_e,ElemType *next_e);
 Status ListInsert(SqList *L,int i,ElemType e); 
 Status ListDelete(SqList *L,int i,ElemType *e);
 void ListTraverse(SqList L,void(*vi)(ElemType*));
 void Union(SqList *La, SqList Lb);
 void MergeList(SqList La, SqList Lb, SqList *Lc);
 
 
 int main()
 {
   SqList L;
   ElemType e,e0;
   Status i;
   int j,k;
   
   InitList(&L);
   printf("��ʼ��L��L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
   for(j=1;j<=5;j++)
     i=ListInsert(&L,1,j);
   printf("��L�ı�ͷ���β���1��5��*L.elem=");
   for(j=1;j<=5;j++)
     printf("%d ",*(L.elem+j-1));
   printf("\n");
   printf("L.elem=%u L.length=%d L.listsize=%d ",L.elem,L.length,L.listsize);
   i=ListEmpty(L);
   printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);
   ClearList(&L);
   printf("���L��L.elem=%u L.length=%d L.listsize=%d ",L.elem,L.length,L.listsize);
   i=ListEmpty(L);
   printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);
   for(j=1;j<=10;j++)
     ListInsert(&L,j,j);
   printf("��L�ı�β���β���1��10��*L.elem=");
   for(j=1;j<=10;j++)
     printf("%d ",*(L.elem+j-1));
   printf("\n");
   printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
   ListInsert(&L,1,0);
   printf("��L�ı�ͷ����0��*L.elem=");
   for(j=1;j<=ListLength(L);j++) /* ListLength(L)ΪԪ�ظ��� */
     printf("%d ",*(L.elem+j-1));
   printf("\n");
   printf("L.elem=%u(�п��ܸı�) L.length=%d(�ı�) L.listsize=%d(�ı�)\n",L.elem,L.length,L.listsize);
   GetElem(L,5,&e);
   printf("��5��Ԫ�ص�ֵΪ��%d\n",e);
   for(j=10;j<=11;j++)
   {
     k=LocateElem(L,j,equal);
     if(k) /* k��Ϊ0�������з���������Ԫ�أ�����λ��Ϊk */
       printf("��%d��Ԫ�ص�ֵΪ%d\n",k,j);
     else
       printf("û��ֵΪ%d��Ԫ��\n",j);
   }
   for(j=3;j<=4;j++)
   {
     k=LocateElem(L,j,sq);
     if(k) /* k��Ϊ0�������з���������Ԫ�أ�����λ��Ϊk */
       printf("��%d��Ԫ�ص�ֵΪ%d��ƽ��\n",k,j);
     else
       printf("û��ֵΪ%d��ƽ����Ԫ��\n",j);
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
     i=ListDelete(&L,j,&e); /* ɾ����j������ */
     if(i==ERROR)
       printf("ɾ����%d��Ԫ��ʧ��\n",j);
     else
       printf("ɾ����%d��Ԫ�سɹ�����ֵΪ��%d\n",j,e);
   }
   printf("�������L��Ԫ�أ�");
   ListTraverse(L,print1); /* ���ζ�Ԫ�ص���print1()�����Ԫ�ص�ֵ */
   printf("L��Ԫ��ֵ�ӱ���");
   ListTraverse(L,dbl); /* ���ζ�Ԫ�ص���dbl()��Ԫ��ֵ��2 */
   ListTraverse(L,print1);
   DestroyList(&L);
   printf("����L��L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
   return 0;
 }

 
 

 void InitList(SqList *L) /* �㷨2.3 */
 { /* �������������һ���յ�˳�����Ա�L */
   (*L).elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
   if(!(*L).elem)
     exit(OVERFLOW); /* �洢����ʧ�� */
   (*L).length=0; /* �ձ���Ϊ0 */
   (*L).listsize=LIST_INIT_SIZE; /* ��ʼ�洢���� */
 }

 void DestroyList(SqList *L)
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������˳�����Ա�L */
   free((*L).elem);
   (*L).elem=NULL;
   (*L).length=0;
   (*L).listsize=0;
 }

 void ClearList(SqList *L)
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
   (*L).length=0;
 }

 Status ListEmpty(SqList L)
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
   if(L.length==0)
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SqList L)
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
   return L.length;
 }

 Status GetElem(SqList L,int i,ElemType *e)
 { /* ��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ */
   if(i<1||i>L.length)
     return ERROR;
   *e=*(L.elem+i-1);
   return OK;
 }

 int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����(����Ϊ1������Ϊ0) */
   /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
   /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0���㷨2.6 */
   ElemType *p;
   int i=1; /* i�ĳ�ֵΪ��1��Ԫ�ص�λ�� */
   p=L.elem; /* p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ�� */
   while(i<=L.length&&!compare(*p++,e))
     ++i;
   if(i<=L.length)
     return i;
   else
     return 0;
 }

 Status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e)
 { /* ��ʼ������˳�����Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
   /*           �������ʧ�ܣ�pre_e�޶��� */
   int i=2;
   ElemType *p = L.elem+1;
   while(i<=L.length&&*p!=cur_e)
   {
     p++;
     i++;
   }
   if(i>L.length)
     return INFEASIBLE; /* ����ʧ�� */
   else
   {
     *pre_e=*--p;
     return OK;
   }
 }

 Status NextElem(SqList L,ElemType cur_e,ElemType *next_e)
 { /* ��ʼ������˳�����Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
   /*           �������ʧ�ܣ�next_e�޶��� */
   int i=1;
   ElemType *p=L.elem;
   while(i<L.length&&*p!=cur_e)
   {
     i++;
     p++;
   }
   if(i==L.length)
   {
     return INFEASIBLE; /* ����ʧ�� */
   }
   else
   {
     *next_e=*++p;
     return OK;
   }
 }

 Status ListInsert(SqList *L,int i,ElemType e) /* �㷨2.4 */
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1 */
   /* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
   ElemType *newbase,*q,*p;
   if(i<1||i>(*L).length+1) /* iֵ���Ϸ� */
     return ERROR;
   if((*L).length>=(*L).listsize) /* ��ǰ�洢�ռ�����,���ӷ��� */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LIST_INCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* �洢����ʧ�� */
     (*L).elem=newbase; /* �»�ַ */
     (*L).listsize+=LIST_INCREMENT; /* ���Ӵ洢���� */
   }
   q=(*L).elem+i-1; /* qΪ����λ�� */
   for(p=(*L).elem+(*L).length-1;p>=q;--p) /* ����λ�ü�֮���Ԫ������ */
     *(p+1)=*p;
   *q=e; /* ����e */
   ++(*L).length; /* ����1 */
   return OK;
 }

 Status ListDelete(SqList *L,int i,ElemType *e) /* �㷨2.5 */
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
   /* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
   ElemType *p,*q;
   if(i<1||i>(*L).length) /* iֵ���Ϸ� */
     return ERROR;
   p=(*L).elem+i-1; /* pΪ��ɾ��Ԫ�ص�λ�� */
   *e=*p; /* ��ɾ��Ԫ�ص�ֵ����e */
   q=(*L).elem+(*L).length-1; /* ��βԪ�ص�λ�� */
   for(++p;p<=q;++p) /* ��ɾ��Ԫ��֮���Ԫ������ */
     *(p-1)=*p;
   (*L).length--; /* ����1 */
   return OK;
 }

 void ListTraverse(SqList L,void(*vi)(ElemType*))
 { /* ��ʼ������˳�����Ա�L�Ѵ��� */
   /* ������������ζ�L��ÿ������Ԫ�ص��ú���vi() */
   /*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
   ElemType *p;
   int i;
   p=L.elem;
   for(i=1;i<=L.length;i++)
     vi(p++);
   printf("\n");
 }


 void Union(SqList *La, SqList Lb)
 {
 	ElemType e;
 	int La_len, Lb_len;
 	int i;

 	//�����������Ա�Lb�е�����La�е�����Ԫ�ز���La��
     La_len = ListLength(*La);
	 Lb_len = ListLength(Lb); 
	 
	 for (i=0; i<=Lb_len; i++)
	 {
	 	GetElem(Lb, i, &e);
	 	
	 	if (!LocateElem(*La, e, equal))
	 	{
	 		ListInsert(La, ++La_len, e);
	 	}
	 	//La�в����ں�e��ͬ��Ԫ�������֮	 	
	 }
 }
 
  void MergeList(SqList La, SqList Lb, SqList *Lc)
  {
  	//��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����С�
    //�鲢La��Lb�õ��µ����Ա�Lc��Lc������Ԫ��Ҳ��ֵ�ǵݼ����С�
	int i = 1;
	int j = 1;
	int k = 0;
	int La_len, Lb_len;
	ElemType ai, bj;
	
	InitList(Lc);
    La_len = ListLength(La);
	Lb_len = ListLength(Lb);
	
	while ( (i <= La_len) && (j <= Lb_len) )
	{
		//La��Lb���ǿ�
		GetElem(La, i, &ai);
		GetElem(Lb, j, &bj);
		
		if (ai <= bj)
		{
			ListInsert(Lc,++k, ai);
			++i;
		}
		else
		{
			ListInsert(Lc, ++k, bj);
			++j;
		}		 
	}
	
	while (i <= La_len)
	{
		GetElem(La, i++, &ai);
		ListInsert(Lc, ++k, ai);
	}
	while (j <= Lb_len)
	{
		GetElem(Lb, j++, &bj);
		ListInsert(Lc, ++k, bj);	
	}	   
  }
 



