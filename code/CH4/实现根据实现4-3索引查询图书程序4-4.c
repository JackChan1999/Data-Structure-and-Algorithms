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
  #define MaxBookNum 10 /* ����ֻ��10�������������� */
 #define MaxKeyNum 25 /* ��������������(�ؼ��ʵ������Ŀ) */
 #define MaxLineLen 46 /* ��������󳤶� */

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

 typedef struct
 {
   char bookname[MaxLineLen+1]; /* ������(����'\0') */
   int bookno; /* ��� */
 }BookTermType; /* ��Ŀ������ */

 typedef struct
 {
   BookTermType item[MaxBookNum]; /* ��Ŀ���������� */
   int last; /* ��Ŀ������ */
 }BookListType; /* ��Ŀ������(�����) */
 
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
 
 int main()
 {
   FILE *f; /* �κ�ʱ������һ���ļ� */
   IdxListType idxlist; /* ������ */
   BookListType booklist; /* ��Ŀ�� */
   char buf[MaxLineLen+5]; /* ��ǰ��Ŀ��(������ź�'\0') */
   HString ch; /* �����ַ��� */
   int BookNo; /* ��� */
   Link p; /* ����ָ�� */
   int i,j,k,flag=1; /* flag�Ǽ�����ѯ�ı�־ */
   InitString(&ch); /* ��ʼ��HString���͵ı��� */
   f=fopen("BookIdx.txt","r"); /* �������ؼ����������ļ� */
   if(!f)
     exit(OVERFLOW);
   fscanf(f,"%d",&idxlist.last); /* �����ؼ��ʸ��� */
   for(k=0;k<idxlist.last;k++) /* �ѹؼ����ļ������ݿ���idxlist�� */
   {
     fscanf(f,"%s",buf);
     i=0;
     while(buf[i])
       buf[i++]=tolower(buf[i]); /* ��ĸתΪСд */
     InitString(&idxlist.item[k].key);
     StrAssign(&idxlist.item[k].key,buf);
     InitList(&idxlist.item[k].bnolist); /* ��ʼ���������bo2-6.c */
     fscanf(f,"%d",&i);
     for(j=0;j<i;j++)
     {
       fscanf(f,"%d",&BookNo);
       MakeNode(&p,BookNo); /* �����µ���Ž�㣬bo2-6.c */
       p->next=NULL; /* ����Ž���ָ����ֵ */
       Append(&idxlist.item[k].bnolist,p); /* �ڱ�β�����µ���Ž�㣬bo2-6.c */
     }
   }
   fclose(f);
   f=fopen("BookInfo.txt","r"); /* ����Ŀ�ļ� */
   if(!f)
     exit(FALSE);
   i=0;
   while(fgets(buf,MaxLineLen,f))
   { /* ����Ŀ�ļ������ݿ���booklist�� */
     booklist.item[i].bookno=atoi(buf); /* ǰ��λ����Ϊ��� */
     strcpy(booklist.item[i++].bookname,&buf[4]); /* ��buf��������ʼ���ַ���������booklist�� */
   }
   booklist.last=i;
   while(flag)
   {
     printf("��������Ŀ�Ĺؼ���(һ��)��");
     scanf("%s",buf);
     i=0;
     while(buf[i])
       buf[i++]=tolower(buf[i]); /* ��ĸתΪСд */
     StrAssign(&ch,buf);
     i=0;
     do
     {
       k=StrCompare(ch,idxlist.item[i++].key); /* bo4-2.c */
     }while(k&&i<=idxlist.last);
     if(!k) /* ���������д˹ؼ��� */
     {
       p=idxlist.item[--i].bnolist.head->next; /* pָ���������д˹ؼ�����Ӧ�������Ԫ��� */
       while(p)
       {
         j=0;
         while(j<booklist.last&&p->data!=booklist.item[j].bookno) /* ��booklist������Ӧ����� */
           j++;
         if(j<booklist.last)
           printf("%3d %s",booklist.item[j].bookno,booklist.item[j].bookname);
         p=p->next; /* ��������� */
       }
     }
     else
       printf("û�ҵ�\n");
     printf("��������������1���˳�����������0��");
     scanf("%d",&flag);
   }
   
   return 0;
 }

 
 