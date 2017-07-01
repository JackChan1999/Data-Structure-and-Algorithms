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
 
 typedef struct LNode
 {
   ElemType data;
   struct LNode *next;
 };
 typedef struct LNode *LinkList; /* ��һ�ֶ���LinkList�ķ��� */
 
  void InitList(LinkList *L)
 { /* �������������һ���յ����Ա�L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ��㣬��ʹLָ���ͷ��� */
   if(!*L) /* �洢����ʧ�� */
     exit(OVERFLOW);
   (*L)->next=NULL; /* ָ����Ϊ�� */
 }

 void DestroyList(LinkList *L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L */
   LinkList q;
   while(*L)
   {
     q=(*L)->next;
     free(*L);
     *L=q;
   }
 }

 void ClearList(LinkList L) /* ���ı�L */
 { /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
   LinkList p,q;
   p=L->next; /* pָ���һ����� */
   while(p) /* û����β */
   {
     q=p->next;
     free(p);
     p=q;
   }
   L->next=NULL; /* ͷ���ָ����Ϊ�� */
 }

 Status ListEmpty(LinkList L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
   if(L->next) /* �ǿ� */
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
   int i=0;
   LinkList p=L->next; /* pָ���һ����� */
   while(p) /* û����β */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem(LinkList L,int i,ElemType *e) /* �㷨2.8 */
 { /* LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR */
   int j=1; /* jΪ������ */
   LinkList p=L->next; /* pָ���һ����� */
   while(p&&j<i) /* ˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ�� */
   {
     p=p->next;
     j++;
   }
   if(!p||j>i) /* ��i��Ԫ�ز����� */
     return ERROR;
   *e=p->data; /* ȡ��i��Ԫ�� */
   return OK;
 }

 int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* ��ʼ����: ���Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����(����Ϊ1������Ϊ0) */
   /* �������: ����L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
   /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
   int i=0;
   LinkList p=L->next;
   while(p)
   {
     i++;
     if(compare(p->data,e)) /* �ҵ�����������Ԫ�� */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e)
 { /* ��ʼ����: ���Ա�L�Ѵ��� */
   /* �������: ��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
   /*           ����OK���������ʧ�ܣ�pre_e�޶��壬����INFEASIBLE */
   LinkList q,p=L->next; /* pָ���һ����� */
   while(p->next) /* p��ָ����к�� */
   {
     q=p->next; /* qΪp�ĺ�� */
     if(q->data==cur_e)
     {
       *pre_e=p->data;
       return OK;
     }
     p=q; /* p����� */
   }
   return INFEASIBLE;
 }

 Status NextElem(LinkList L,ElemType cur_e,ElemType *next_e)
 { /* ��ʼ���������Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
   /*           ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE */
   LinkList p=L->next; /* pָ���һ����� */
   while(p->next) /* p��ָ����к�� */
   {
     if(p->data==cur_e)
     {
       *next_e=p->next->data;
       return OK;
     }
     p=p->next;
   }
   return INFEASIBLE;
 }

 Status ListInsert(LinkList L,int i,ElemType e) /* �㷨2.9�����ı�L */
 { /* �ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
   int j=0;
   LinkList p=L,s;
   while(p&&j<i-1) /* Ѱ�ҵ�i-1����� */
   {
     p=p->next;
     j++;
   }
   if(!p||j>i-1) /* iС��1���ߴ��ڱ� */
     return ERROR;
   s=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
   s->data=e; /* ����L�� */
   s->next=p->next;
   p->next=s;
   return OK;
 }

 Status ListDelete(LinkList L,int i,ElemType *e) /* �㷨2.10�����ı�L */
 { /* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ */
   int j=0;
   LinkList p=L,q;
   while(p->next&&j<i-1) /* Ѱ�ҵ�i����㣬����pָ����ǰ� */
   {
     p=p->next;
     j++;
   }
   if(!p->next||j>i-1) /* ɾ��λ�ò����� */
     return ERROR;
   q=p->next; /* ɾ�����ͷŽ�� */
   p->next=q->next;
   *e=q->data;
   free(q);
   return OK;
 }

 void ListTraverse(LinkList L,void(*vi)(ElemType))
 /* vi���β�����ΪElemType����bo2-1.c����Ӧ�������β�����ElemType&��ͬ */
 { /* ��ʼ���������Ա�L�Ѵ��ڡ�������������ζ�L��ÿ������Ԫ�ص��ú���vi() */
   LinkList p=L->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
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
 
  void MergeList(LinkList La,LinkList Lb,LinkList *Lc) /* �㷨2.2,�˾���algo2-2.c��ͬ */
 { /* ��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����С�*/
   /* �鲢La��Lb�õ��µ����Ա�Lc��Lc������Ԫ��Ҳ��ֵ�ǵݼ����� */
   int i=1,j=1,k=0;
   int La_len,Lb_len;
   ElemType ai,bj;
   InitList(Lc); /* �����ձ�Lc */
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   while(i<=La_len&&j<=Lb_len) /* ��La�ͱ�Lb���ǿ� */
   {
     GetElem(La,i,&ai);
     GetElem(Lb,j,&bj);
     if(ai<=bj)
     {
       ListInsert(*Lc,++k,ai);
       ++i;
     }
     else
     {
       ListInsert(*Lc,++k,bj);
       ++j;
     }
   }
   while(i<=La_len) /* ��La�ǿ��ұ�Lb�� */
   {
     GetElem(La,i++,&ai);
     ListInsert(*Lc,++k,ai);
   }
   while(j<=Lb_len) /* ��Lb�ǿ��ұ�La�� */
   {
     GetElem(Lb,j++,&bj);
     ListInsert(*Lc,++k,bj);
   }
 }

 int main()
 {
   LinkList La,Lb,Lc; /* �˾���algo2-2.c��ͬ */
   int j,a[4]={3,5,8,11},b[7]={2,6,8,9,11,15,20}; /* �̿�����2�C2������ */
   InitList(&La); /* �����ձ�La */
   for(j=1;j<=4;j++) /* �ڱ�La�в���4��Ԫ�� */
     ListInsert(La,j,a[j-1]);
   printf("La= "); /* �����La������ */
   ListTraverse(La,print);
   InitList(&Lb); /* �����ձ�Lb */
   for(j=1;j<=7;j++) /* �ڱ�Lb�в���7��Ԫ�� */
     ListInsert(Lb,j,b[j-1]);
   printf("Lb= "); /* �����Lb������ */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* �����Lc������ */
   ListTraverse(Lc,print);
   
   return 0; 
 }
 
 