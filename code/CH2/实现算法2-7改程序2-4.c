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
   ElemType *p=L.elem+1;
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
     return INFEASIBLE; /* ����ʧ�� */
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
 
 //�޸��㷨2.7�ĵ�һ��ѭ������е��������Ϊ������䣬�ҵ�*pa = *pbʱ��ֻ��
 //������֮һ����Lc�� 
 void MergeList(SqList La,SqList Lb,SqList *Lc)
 { /* ��һ�ֺϲ����Ա�ķ���(�����㷨2.7�µ�Ҫ���޸��㷨2.7)��La��Lb��Lc��Ϊ���������еı� */
   ElemType  *pa,*pa_last,*pb,*pb_last,*pc;
   pa=La.elem;
   pb=Lb.elem;
   (*Lc).listsize=La.length+Lb.length; /* �˾����㷨2.7��ͬ */
   pc=(*Lc).elem=(ElemType *)malloc((*Lc).listsize*sizeof(ElemType));
   if(!(*Lc).elem)
     exit(OVERFLOW);
   pa_last=La.elem+La.length-1;
   pb_last=Lb.elem+Lb.length-1;
   while(pa<=pa_last&&pb<=pb_last) /* ��La�ͱ�Lb���ǿ� */
     switch(comp(*pa,*pb)) /* �˾����㷨2.7��ͬ */
     {
       case  0: pb++;
       case -1: *pc++=*pa++;
                break;
       case  1: *pc++=*pb++;
     }
   while(pa<=pa_last) /* ��La�ǿ��ұ�Lb�� */
     *pc++=*pa++;
   while(pb<=pb_last) /* ��Lb�ǿ��ұ�La�� */
     *pc++=*pb++;
   (*Lc).length=pc-(*Lc).elem; /* �Ӵ˾� */
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j;
   InitList(&La); /* �����ձ�La */
   for(j=1;j<=5;j++) /* �ڱ�La�в���5��Ԫ�أ�����Ϊ1��2��3��4��5 */
     ListInsert(&La,j,j);
   printf("La= "); /* �����La������ */
   ListTraverse(La,print1);
   InitList(&Lb); /* �����ձ�Lb */
   for(j=1;j<=5;j++) /* �ڱ�Lb�в���5��Ԫ�أ�����Ϊ2��4��6��8��10 */
     ListInsert(&Lb,j,2*j);
   printf("Lb= "); /* �����Lb������ */
   ListTraverse(Lb,print1);
   MergeList(La,Lb,&Lc); /* �ɰ��������еı�La��Lb�õ����������еı�Lc */
   printf("Lc= "); /* �����Lc������ */
   ListTraverse(Lc,print1);
 }