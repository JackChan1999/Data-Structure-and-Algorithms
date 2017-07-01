 #include<limits.h> /* INT_MAX�� */
 #include<stdio.h> /* EOF(=^Z��F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h> /* exit() */
 #include<string.h>
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
 
 typedef struct
 {
   char *ch; /* ���Ƿǿմ����򰴴�������洢��������chΪNULL */
   int length; /* ������ */
 }HString;
 
 #define DestroyString ClearString /* DestroyString()��ClearString()������ͬ */
 #define MaxKeyNum 25 /* ��������������(�ؼ��ʵ������Ŀ) */
 #define MaxLineLen 52 /* ��Ŀ��(��Ŀ�ļ���1��)buf����󳤶� */
 #define MaxNoIdx 10 /* ��������(Ҳ��һ����Ŀ�йؼ���)�������Ŀ */

 typedef struct
 {
   char *item[MaxNoIdx]; /* �ʱ�(�ַ���)ָ������ */
   int last; /* �ʵ����� */
 }WordListType; /* һ����Ŀ�Ĵʱ�(˳���)�ͷ������ʱ�(�����)�������� */

 typedef struct
 {
   HString key; /* �ؼ���(�ѷ������ͣ�c4-2.h) */
   LinkList bnolist; /* ����������������(c2-5.h) */
 }IdxTermType; /* ���������� */

 typedef struct
 {
   IdxTermType item[MaxKeyNum+1]; /* �������������� */
   int last; /* �ؼ��ʵĸ��� */
 }IdxListType; /* ����������(�����) */

 /* ȫ�ֱ��� */
 char buf[MaxLineLen+1]; /* ��ǰ��Ŀ��(����'\0') */
 WordListType wdlist,noidx; /* �ݴ�һ����Ĵʱ��������ʱ� */
 
  
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
 


 void StrAssign(HString *T,char *chars)
 { /* ����һ����ֵ���ڴ�����chars�Ĵ�T */
   int i,j;
   if((*T).ch)
     free((*T).ch); /* �ͷ�Tԭ�пռ� */
   i=strlen(chars); /* ��chars�ĳ���i */
   if(!i)
   { /* chars�ĳ���Ϊ0 */
     (*T).ch=NULL;
     (*T).length=0;
   }
   else
   { /* chars�ĳ��Ȳ�Ϊ0 */
     (*T).ch=(char*)malloc(i*sizeof(char)); /* ���䴮�ռ� */
     if(!(*T).ch) /* ���䴮�ռ�ʧ�� */
       exit(OVERFLOW);
     for(j=0;j<i;j++) /* ������ */
       (*T).ch[j]=chars[j];
     (*T).length=i;
   }
 }

 void StrCopy(HString *T,HString S)
 { /* ��ʼ��������S���ڡ�����������ɴ�S���Ƶô�T */
   int i;
   if((*T).ch)
     free((*T).ch); /* �ͷ�Tԭ�пռ� */
   (*T).ch=(char*)malloc(S.length*sizeof(char)); /* ���䴮�ռ� */
   if(!(*T).ch) /* ���䴮�ռ�ʧ�� */
     exit(OVERFLOW);
   for(i=0;i<S.length;i++) /* ������ */
     (*T).ch[i]=S.ch[i];
   (*T).length=S.length;
 }

 Status StrEmpty(HString S)
 { /* ��ʼ��������S���ڡ������������SΪ�մ����򷵻�TRUE�����򷵻�FALSE */
   if(S.length==0&&S.ch==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(HString S,HString T)
 { /* ��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0 */
   int i;
   for(i=0;i<S.length&&i<T.length;++i)
     if(S.ch[i]!=T.ch[i])
       return S.ch[i]-T.ch[i];
   return S.length-T.length;
 }

 int StrLength(HString S)
 { /* ����S��Ԫ�ظ�������Ϊ���ĳ��� */
   return S.length;
 }

 void ClearString(HString *S)
 { /* ��S��Ϊ�մ� */
   free((*S).ch);
   (*S).ch=NULL;
   (*S).length=0;
 }

 void Concat(HString *T,HString S1,HString S2)
 { /* ��T������S1��S2���Ӷ��ɵ��´� */
   int i;
   if((*T).ch)
     free((*T).ch); /* �ͷžɿռ� */
   (*T).length=S1.length+S2.length;
   (*T).ch=(char *)malloc((*T).length*sizeof(char));
   if(!(*T).ch)
     exit(OVERFLOW);
   for(i=0;i<S1.length;i++)
     (*T).ch[i]=S1.ch[i];
   for(i=0;i<S2.length;i++)
     (*T).ch[S1.length+i]=S2.ch[i];
 }

 Status SubString(HString *Sub, HString S,int pos,int len)
 { /* ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ��� */
   /* ���У�1��pos��StrLength(S)��0��len��StrLength(S)-pos+1 */
   int i;
   if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
     return ERROR;
   if((*Sub).ch)
     free((*Sub).ch); /* �ͷžɿռ� */
   if(!len) /* ���Ӵ� */
   {
     (*Sub).ch=NULL;
     (*Sub).length=0;
   }
   else
   { /* �����Ӵ� */
     (*Sub).ch=(char*)malloc(len*sizeof(char));
     if(!(*Sub).ch)
       exit(OVERFLOW);
     for(i=0;i<=len-1;i++)
       (*Sub).ch[i]=S.ch[pos-1+i];
     (*Sub).length=len;
   }
   return OK;
 }

 void InitString(HString *T)
 { /* ��ʼ��(�����մ�)�ַ���T����� */
   (*T).length=0;
   (*T).ch=NULL;
 }

 int Index(HString S,HString T,int pos) /* �㷨4.1 */
 { /* TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���*/
   /* �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0 */
   int n,m,i;
   HString sub;
   InitString(&sub);
   if(pos>0)
   {
     n=StrLength(S);
     m=StrLength(T);
     i=pos;
     while(i<=n-m+1)
     {
       SubString(&sub,S,i,m);
       if(StrCompare(sub,T)!=0)
         ++i;
       else
	 return i;
     }
   }
   return 0;
  }

 Status StrInsert(HString *S,int pos,HString T) /* �㷨4.4 */
 { /* 1��pos��StrLength(S)+1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T */
   int i;
   if(pos<1||pos>(*S).length+1) /* pos���Ϸ� */
     return ERROR;
   if(T.length) /* T�ǿգ������·���ռ䣬����T */
   {
     (*S).ch=(char*)realloc((*S).ch,((*S).length+T.length)*sizeof(char));
     if(!(*S).ch)
       exit(OVERFLOW);
     for(i=(*S).length-1;i>=pos-1;--i) /* Ϊ����T���ڳ�λ�� */
       (*S).ch[i+T.length]=(*S).ch[i];
     for(i=0;i<T.length;i++)
       (*S).ch[pos-1+i]=T.ch[i]; /* ����T */
     (*S).length+=T.length;
   }
   return OK;
 }

 Status StrDelete(HString *S,int pos,int len)
 { /* �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ� */
   int i;
   if((*S).length<pos+len-1)
     return ERROR;
   for(i=pos-1;i<=(*S).length-len;i++)
     (*S).ch[i]=(*S).ch[i+len];
   (*S).length-=len;
   (*S).ch=(char*)realloc((*S).ch,(*S).length*sizeof(char));
   return OK;
 }

 Status Replace(HString *S,HString T,HString V) /* �˺����봮�Ĵ洢�ṹ�޹� */
 { /* ��ʼ��������S��T��V���ڣ�T�Ƿǿմ� */
   /* �����������V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ� */
   int i=1; /* �Ӵ�S�ĵ�һ���ַ�����Ҵ�T */
   if(StrEmpty(T)) /* T�ǿմ� */
     return ERROR;
   do
   {
     i=Index(*S,T,i); /* ���iΪ����һ��i֮���ҵ����Ӵ�T��λ�� */
     if(i) /* ��S�д��ڴ�T */
     {
       StrDelete(S,i,StrLength(T)); /* ɾ���ô�T */
       StrInsert(S,i,V); /* ��ԭ��T��λ�ò��봮V */
       i+=StrLength(V); /* �ڲ���Ĵ�V����������Ҵ�T */
     }
   }while(i);
   return OK;
 }

 void StrPrint(HString T)
 { /* ���T�ַ�������� */
   int i;
   for(i=0;i<T.length;i++)
     printf("%c",T.ch[i]);
   printf("\n");
 }
 
  void InitIdxList(IdxListType *idxlist)
 { /* ��ʼ����������������idxlistΪ�ձ�����idxlist.item[0]��һ�մ� */
   (*idxlist).last=0;
   InitString(&(*idxlist).item[0].key); /* ��ʼ��[0]��Ԫ��������bo4-2.c�� */
   InitList(&(*idxlist).item[0].bnolist); /* ��ʼ��[0]��Ԫ��������bo2-6.c�� */
 }

 void ExtractKeyWord(int *BookNo)
 { /* ��buf����ȡ�����ؼ��ʵ��ʱ�wdlist����Ŵ���BookNo */
   int i,l,f=1; /* f���ַ���buf������־ 0������ 1��δ���� */
   char *s1,*s2;
   for(i=1;i<=wdlist.last;i++)
   { /* �ͷ���һ����Ŀ�ڴʱ�wdlist�Ĵ洢�ռ� */
     free(wdlist.item[i]);
     wdlist.item[i]=NULL;
   }
   wdlist.last=0; /* ��ʼ���ʱ�wdlist�Ĵ����� */
   *BookNo=atoi(buf); /* ��ǰ��λ����ת��Ϊ�������������BookNo */
   s1=&buf[4]; /* s1ָ�����������ַ� */
   while(f)
   { /* ��ȡ�����ؼ��ʵ��ʱ�wdlist */
     s2=strchr(s1,' '); /* s2ָ��s1��ĵ�һ���ո���û�У�����NULL */
     if(!s2) /* ����β(û�ո�) */
     {
       s2=strchr(s1,'\12'); /* s2ָ��buf�����һ���ַ�(�س���10) */
       f=0;
     }
     l=s2-s1; /* ���ʳ��� */
     if(s1[0]>='A'&&s1[0]<='Z') /* ��������ĸΪ��д */
     { /* д��ʱ� */
       wdlist.item[wdlist.last]=(char *)malloc((l+1)*sizeof(char)); /* ���ɴ��ռ�(����'\0') */
       for(i=0;i<l;i++)
         wdlist.item[wdlist.last][i]=s1[i]; /* д��ʱ� */
       wdlist.item[wdlist.last][l]=0; /* �������� */
       for(i=0;i<noidx.last&&(l=strcmp(wdlist.item[wdlist.last],noidx.item[i]))>0;i++);
       /* �����Ƿ�Ϊ�������� */
       if(!l) /* �Ƿ������� */
       {
         free(wdlist.item[wdlist.last]); /* �Ӵʱ���ɾ���ô� */
         wdlist.item[wdlist.last]=NULL;
       }
       else
         wdlist.last++; /* �ʱ���+1 */
     }
     s1=s2+1; /* s1�ƶ�����һ�����ʵ����ַ��� */
   };
 }

 void GetWord(int i,HString *wd)
 { /* ��wd���شʱ�wdlist�е�i���ؼ��ʣ��㷨4.11 */
   StrAssign(wd,wdlist.item[i]); /* ���ɹؼ����ַ��� bo4-2.c */
 }

 int Locate(IdxListType *idxlist,HString wd,Status *b)
 { /* ��������idxlist�в�ѯ�Ƿ������wd��ȵĹؼ��ʡ������ڣ��򷵻��� */
   /* ���������е�λ�ã���bȡֵTRUE�����򷵻ز���λ�ã���bȡֵFALSE���㷨4.12 */
   int i,m;
   for(i=(*idxlist).last;(m=StrCompare((*idxlist).item[i].key,wd))>0;--i); /* bo4-2.c */
   if(m==0) /* �ҵ� */
   {
     *b=TRUE;
     return i;
   }
   else
   {
     *b=FALSE;
     return i+1;
   }
 }

 void InsertNewKey(IdxListType *idxlist,int i,HString wd)
 { /* ��������idxlist�ĵ�i���ϲ����¹ؼ���wd������ʼ���������������Ϊ�ձ��㷨4.13 */
   int j;
   for(j=(*idxlist).last;j>=i;--j) /* ���������� */
     (*idxlist).item[j+1]=(*idxlist).item[j];
   InitString(&(*idxlist).item[i].key); /* bo4-2.c */
   StrCopy(&(*idxlist).item[i].key,wd); /* �����������µ������� bo4-2.c */
   InitList(&(*idxlist).item[i].bnolist); /* ��ʼ�����������Ϊ�ձ� bo2-6.c */
   (*idxlist).last++;
 }

 void InsertBook(IdxListType *idxlist,int i,int bno)
 { /* ��������idxlist�ĵ�i���в������Ϊbno���������㷨4.14 */
   Link p;
   MakeNode(&p,bno); /* ������ bo2-6.c */
   p->next=NULL;
   Append(&(*idxlist).item[i].bnolist,p); /* �����µ�������� bo2-6.c */
 }

 void InsIdxList(IdxListType *idxlist,int bno)
 { /* �����Ϊbno�Ĺؼ��ʲ����������㷨4.10 */
   int i,j;
   Status b;
   HString wd;
   InitString(&wd); /* bo4-2.c */
   for(i=0;i<wdlist.last;i++)
   {
     GetWord(i,&wd);
     j=Locate(idxlist,wd,&b); /* �ؼ��ʵ�λ�û�������λ��(���������в����ڸô�) */
     if(!b) /* �������в����ڹؼ���wd */
       InsertNewKey(idxlist,j,wd); /* ���������в����µ������� */
     InsertBook(idxlist,j,bno); /* ����������� */
   }
 }

 void PutText(FILE *f,IdxListType idxlist)
 { /* �����ɵ�������idxlist������ļ�f */
   int i,j;
   Link p;
   fprintf(f,"%d\n",idxlist.last);
   for(i=1;i<=idxlist.last;i++)
   {
     for(j=0;j<idxlist.item[i].key.length;j++)
       fprintf(f,"%c",idxlist.item[i].key.ch[j]); /* HString���ʹ�βû��\0��ֻ������ַ���� */
     fprintf(f,"\n%d\n",idxlist.item[i].bnolist.len);
     p=idxlist.item[i].bnolist.head;
     for(j=1;j<=idxlist.item[i].bnolist.len;j++)
     {
       p=p->next;
       fprintf(f,"%d ",p->data);
     }
     fprintf(f,"\n");
   }
 }

 int main()
 { /* �㷨4.9 */
   FILE *f; /* �κ�ʱ������һ���ļ� */
   IdxListType idxlist; /* ������ */
   int BookNo; /* ��ű��� */
   int k;
   f=fopen("NoIdx.txt","r"); /* �򿪷��������ļ� */
   if(!f)
     exit(OVERFLOW);
   fscanf(f,"%d",&noidx.last); /* ��ȡ�������ʸ��� */
   for(k=0;k<noidx.last;k++) /* �ѷ��������ļ����������ο���noidx�� */
   {
     fscanf(f,"%s",buf);
     noidx.item[k]=(char*)malloc((strlen(buf)+1)*sizeof(char));
     strcpy(noidx.item[k],buf);
   }
   fclose(f); /* �رշ��������ļ� */
   f=fopen("BookInfo.txt","r"); /* ����Ŀ�ļ� */
   if(!f)
     exit(FALSE);
   InitIdxList(&idxlist); /* ��������idxlistΪ�գ�����ʼ��[0]��Ԫ */
   while(fgets(buf,MaxLineLen,f)) /* ����Ŀ�ļ���ȡ1����Ϣ��buf�ɹ� */
   {
     ExtractKeyWord(&BookNo);/*��buf�е���Ŵ���BookNo,�ؼ�����ȡ���ʱ�(��ǰ��Ŀ�Ĺؼ��ʱ�)�� */
     InsIdxList(&idxlist,BookNo); /* �����ΪBookNo�Ĺؼ��ʼ���Ų���������idxlist�� */
   }
   fclose(f); /* �ر���Ŀ�ļ� */
   f=fopen("BookIdx.txt","w"); /* �������ؼ��������ļ� */
   if(!f)
     exit(INFEASIBLE);
   PutText(f,idxlist); /* �����ɵ�������idxlist����������ؼ��������ļ� */
   fclose(f); /* �ر������ؼ��������ļ� */
   
   return 0;
 }
 