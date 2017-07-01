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
 
 #define N 2
 typedef char ElemType;
 #define MAX_SIZE 100 /* �������󳤶� */
 typedef struct
 {
   ElemType data;
   int cur;
 }component,SLinkList[MAX_SIZE];
 
 int Malloc(SLinkList space) /* �㷨2.15 */
 { /* ����������ǿգ��򷵻ط���Ľ���±�(��������ĵ�һ�����)�����򷵻�0 */
   int i=space[0].cur;
   if(i) /* ��������ǿ� */
     space[0].cur=space[i].cur; /* ���������ͷ���ָ��ԭ��������ĵڶ������ */
   return i; /* �����¿��ٽ������� */
 }

 void Free(SLinkList space,int k) /* �㷨2.16 */
 { /* ���±�Ϊk�Ŀ��н����յ���������(��Ϊ��������ĵ�һ�����) */
   space[k].cur=space[0].cur; /* ���ս��ģ��αָ꣢��������ĵ�һ����� */
   space[0].cur=k; /* ���������ͷ���ָ���»��յĽ�� */
 }
 
 #define DestroyList ClearList // DestroyList()��ClearList()�Ĳ�����һ����
 void InitList(SLinkList L)
 { /* ����һ���յ�����L����ͷΪL�����һ����ԪL[MAX_SIZE-1]�����൥Ԫ���� */
   /* һ������������ͷΪL�ĵ�һ����ԪL[0]����0����ʾ��ָ�� */
   int i;
   L[MAX_SIZE-1].cur=0; /* L�����һ����ԪΪ������ı�ͷ */
   for(i=0;i<MAX_SIZE-2;i++) /* �����൥Ԫ���ӳ���L[0]Ϊ��ͷ�ı������� */
     L[i].cur=i+1;
   L[MAX_SIZE-2].cur=0;
 }

 void ClearList(SLinkList L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
   int i,j,k;
   i=L[MAX_SIZE-1].cur; /* �����һ������λ�� */
   L[MAX_SIZE-1].cur=0; /* ����� */
   k=L[0].cur; /* ���������һ������λ�� */
   L[0].cur=i; /* ������Ľ��������������ı�ͷ */
   while(i) /* û������β */
   {
     j=i;
     i=L[i].cur; /* ָ����һ��Ԫ�� */
   }
   L[j].cur=k; /* ��������ĵ�һ�����ӵ������β�� */
 }

 Status ListEmpty(SLinkList L)
 { /* ��L�ǿձ�����TRUE�����򷵻�FALSE */
   if(L[MAX_SIZE-1].cur==0) /* �ձ� */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SLinkList L)
 { /* ����L������Ԫ�ظ��� */
   int j=0,i=L[MAX_SIZE-1].cur; /* iָ���һ��Ԫ�� */
   while(i) /* û����̬����β */
   {
     i=L[i].cur; /* ָ����һ��Ԫ�� */
     j++;
   }
   return j;
 }

 Status GetElem(SLinkList L,int i,ElemType *e)
 { /* ��e����L�е�i��Ԫ�ص�ֵ */
   int l,k=MAX_SIZE-1; /* kָ���ͷ��� */
   if(i<1||i>ListLength(L))
     return ERROR;
   for(l=1;l<=i;l++) /* �ƶ�����i��Ԫ�ش� */
     k=L[k].cur;
   *e=L[k].data;
   return OK;
 }

 int LocateElem(SLinkList L,ElemType e) /* �㷨2.13(�иĶ�) */
 { /* �ھ�̬�������Ա�L�в��ҵ�1��ֵΪe��Ԫ�ء����ҵ����򷵻�����L�е� */
   /* λ�򣬷��򷵻�0��(������LocateElem()�Ķ��岻ͬ) */
   int i=L[MAX_SIZE-1].cur; /* iָʾ���е�һ����� */
   while(i&&L[i].data!=e) /* �ڱ���˳������(e�������ַ���) */
     i=L[i].cur;
   return i;
 }

 Status PriorElem(SLinkList L,ElemType cur_e,ElemType *pre_e)
 { /* ��ʼ���������Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
   /*           �������ʧ�ܣ�pre_e�޶��� */
   int j,i=L[MAX_SIZE-1].cur; /* iָʾ�����һ������λ�� */
   do
   { /* ����ƶ���� */
     j=i;
     i=L[i].cur;
   }while(i&&cur_e!=L[i].data);
   if(i) /* �ҵ���Ԫ�� */
   {
     *pre_e=L[j].data;
     return OK;
   }
   return ERROR;
 }

 Status NextElem(SLinkList L,ElemType cur_e,ElemType *next_e)
 { /* ��ʼ���������Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
   /*           �������ʧ�ܣ�next_e�޶��� */
   int j,i=LocateElem(L,cur_e); /* ��L�в��ҵ�һ��ֵΪcur_e��Ԫ�ص�λ�� */
   if(i) /* L�д���Ԫ��cur_e */
   {
     j=L[i].cur; /* cur_e�ĺ�̵�λ�� */
     if(j) /* cur_e�к�� */
     {
       *next_e=L[j].data;
       return OK; /* cur_eԪ���к�� */
     }
   }
   return ERROR; /* L������cur_eԪ�أ�cur_eԪ���޺�� */
 }

 Status ListInsert(SLinkList L,int i,ElemType e)
 { /* ��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e */
   int l,j,k=MAX_SIZE-1; /* kָ���ͷ */
   if(i<1||i>ListLength(L)+1)
     return ERROR;
   j=Malloc(L); /* �����µ�Ԫ */
   if(j) /* ����ɹ� */
   {
     L[j].data=e; /* ��ֵ���µ�Ԫ */
     for(l=1;l<i;l++) /* �ƶ�i-1��Ԫ�� */
       k=L[k].cur;
     L[j].cur=L[k].cur;
     L[k].cur=j;
     return OK;
   }
   return ERROR;
 }

 Status ListDelete(SLinkList L,int i,ElemType *e)
 { /* ɾ����L�е�i������Ԫ��e����������ֵ */
   int j,k=MAX_SIZE-1; /* kָ���ͷ */
   if(i<1||i>ListLength(L))
     return ERROR;
   for(j=1;j<i;j++) /* �ƶ�i-1��Ԫ�� */
     k=L[k].cur;
   j=L[k].cur;
   L[k].cur=L[j].cur;
   *e=L[j].data;
   Free(L,j);
   return OK;
 }

 void ListTraverse(SLinkList L,void(*vi)(ElemType))
 { /* ��ʼ���������Ա�L�Ѵ��ڡ�������������ζ�L��ÿ������Ԫ�ص��ú���vi() */
   int i=L[MAX_SIZE-1].cur; /* ָ���һ��Ԫ�� */
   while(i) /* û����̬����β */
   {
     vi(L[i].data); /* ����vi() */
     i=L[i].cur; /* ָ����һ��Ԫ�� */
   }
   printf("\n");
 }
 
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
 
  void difference(SLinkList space) /* �Ľ��㷨2.17(�������û�������ʵ��) */
 { /* �������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ����(A-B)��(B-A)�ľ�̬���� */
   int m,n,i,j;
   ElemType b,c;
   InitList(space); /* ��������� */
   printf("�����뼯��A��B��Ԫ�ظ���m,n:");
   scanf("%d,%d%*c",&m,&n); /* %*c�Ե��س��� */
   printf("�����뼯��A��Ԫ�أ���%d����:",m);
   for(j=1;j<=m;j++) /* ��������A������ */
   {
     scanf("%c",&b); /* ����A��Ԫ��ֵ */
     ListInsert(space,1,b); /* ���뵽��ͷ */
   }
   scanf("%*c"); /* �Ե��س��� */
   printf("�����뼯��B��Ԫ�أ���%d����:",n);
   for(j=1;j<=n;j++)
   { /* ��������B��Ԫ�أ������ڵ�ǰ���У�����룬����ɾ�� */
     scanf("%c",&b);
     for(i=1;i<=ListLength(space);i++)
     {
       GetElem(space,i,&c); /* ������ñ��е�i��Ԫ�ص�ֵ�������丳��c */
       if(c==b) /* ���д���b,�����ǵ�i��Ԫ�� */
       {
	 ListDelete(space,i,&c); /* ɾ����i��Ԫ�� */
	 break; /* ����iѭ�� */
       }
     }
     if(i>ListLength(space)) /* ���в�����b */
       ListInsert(space,1,b); /* ��b���ڱ�ͷ */
   }
 }

 void main()
 {
   SLinkList s;
   difference(s);
   ListTraverse(s,print2);
 }
 
 
 
 