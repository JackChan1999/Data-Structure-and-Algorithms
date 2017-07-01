#define Qu 4 /* ������ */
#define Khjg 5 /* �����ڵ���Ŀͻ���ʱ�������ֵ */
#define Blsj 30 /* ÿ���ͻ�����ҵ���ʱ�����ֵ */
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

 typedef struct /* ����ElemTypeΪ�ṹ������ */
 {
   int OccurTime; /* �¼�����ʱ�� */
   int NType; /* �¼����ͣ�Qu��ʾ�����¼���0��Qu-1��ʾQu�����ڵ��뿪�¼� */
 }Event,ElemType; /* �¼����ͣ���������LinkList������Ԫ������ */

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
 /* ��ʵ��Ӧ�ýǶȳ������¶������������ṹ */
 typedef LinkList EventList; /* �¼�����ָ�����ͣ�����Ϊ�������� */
 typedef struct
 {
   int ArrivalTime; /* ����ʱ�� */
   int Duration; /* ������������ʱ�� */
 }QElemType; /* ������е�����Ԫ������QElemTypeΪ�ṹ������ */
 
   /* �������õ�����Ҫ����(ȫ��) */
 EventList ev; /* �¼���ͷָ�� */
 Event en,et; /* �¼�,��ʱ���� */
 /*FILE *fp; /* �ļ���ָ�룬����ָ��b.txt��d.txt�ļ� */
 typedef struct QNode
 {
   QElemType data;
   struct QNode *next;
 }QNode,*QueuePtr;

 typedef struct
 {
   QueuePtr front,rear; /* ��ͷ����βָ�� */
 }LinkQueue;
 

 long int TotalTime=0; /* �ۼƿͻ�����ʱ��(��ֵΪ0) */
 int CloseTime,CustomerNum=0; /* ����Ӫҵʱ��(��λ�Ƿ�),�ͻ���(��ֵΪ0) */

 
  LinkQueue q; /* �Ŷӻ�����q */
 QElemType customer[Qu]; /* Qu���ͻ�����Ԫ��, ������ڴ��ڰ���ҵ��Ŀͻ�����Ϣ */
 /*FILE *fq; /* �ļ���ָ�룬����ָ��c.txt�ļ� */
 /*int j=0; /* ������������c.txt�ļ��õ� */
 Boolean chk[Qu]; /* ����״̬��1Ϊ�У�0Ϊæ */
 
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


 

 


 void InitQueue(LinkQueue *Q)
 { /* ����һ���ն���Q */
   (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
   if(!(*Q).front)
     exit(OVERFLOW);
   (*Q).front->next=NULL;
 }

 void DestroyQueue(LinkQueue *Q)
 { /* ���ٶ���Q(���ۿշ����) */
   while((*Q).front)
   {
     (*Q).rear=(*Q).front->next;
     free((*Q).front);
     (*Q).front=(*Q).rear;
   }
 }

 void ClearQueue(LinkQueue *Q)
 { /* ��Q��Ϊ�ն��� */
   QueuePtr p,q;
   (*Q).rear=(*Q).front;
   p=(*Q).front->next;
   (*Q).front->next=NULL;
   while(p)
   {
     q=p;
     p=p->next;
     free(q);
   }
 }

 Status QueueEmpty(LinkQueue Q)
 { /* ��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE */
   if(Q.front->next==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(LinkQueue Q)
 { /* ����еĳ��� */
   int i=0;
   QueuePtr p;
   p=Q.front;
   while(Q.rear!=p)
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetHead_Q(LinkQueue Q,QElemType *e) /* ������bo2-6.c���� */
 { /* �����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR */
   QueuePtr p;
   if(Q.front==Q.rear)
     return ERROR;
   p=Q.front->next;
   *e=p->data;
   return OK;
 }

 void EnQueue(LinkQueue *Q,QElemType e)
 { /* ����Ԫ��eΪQ���µĶ�βԪ�� */
   QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
   if(!p) /* �洢����ʧ�� */
     exit(OVERFLOW);
   p->data=e;
   p->next=NULL;
   (*Q).rear->next=p;
   (*Q).rear=p;
 }

 Status DeQueue(LinkQueue *Q,QElemType *e)
 { /* �����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
   QueuePtr p;
   if((*Q).front==(*Q).rear)
     return ERROR;
   p=(*Q).front->next;
   *e=p->data;
   (*Q).front->next=p->next;
   if((*Q).rear==p)
     (*Q).rear=(*Q).front;
   free(p);
   return OK;
 }

 void QueueTraverse(LinkQueue Q,void(*vi)(QElemType))
 { /* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi() */
   QueuePtr p;
   p=Q.front->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
 }

 int cmp(Event a,Event b)
 { /* ���¼�a�ķ���ʱ��<��=��>�¼�b�ķ���ʱ�̷ֱ𷵻�-1��0��1 */
   if(a.OccurTime==b.OccurTime)
     return 0;
   else
     return (a.OccurTime-b.OccurTime)/abs(a.OccurTime-b.OccurTime);
 }

 void Random(int *d,int *i)
 { /* ������������� */
   *d=rand()%Blsj+1; /* 1��Blsj֮��������(����ҵ���ʱ��) */
   *i=rand()%(Khjg+1); /* 0��Khjg֮��������(�ͻ������ʱ����) */
 }
 
 void OpenForDay();
 void CustomerArrived();
 void CustomerDeparture();

 void Bank_Simulation()
 { /* ����ҵ��ģ�⺯�� */
   Link p;
   OpenForDay(); /* ��ʼ���¼���ev�Ҳ����1�������¼�����ʼ������ */
   while(!ListEmpty(ev)) /* �¼���ev���� */
   {
     DelFirst(&ev,ev.head,&p); /* ɾ���¼���ev�ĵ�1����㣬����p������ָ�룬��bo2-6.c�� */
 /*  if(p->data.OccurTime<50) /* ���ǰ50�����ڷ������¼����ļ�d.txt�� */
 /*    fprintf(fp,"p->data.OccurTime=%3d p->data.NType=%d\n",p->data.OccurTime,p->data.NType); */
     en.OccurTime=GetCurElem(p).OccurTime; /* GetCurElem()��bo2-6.c�У�����p->data(ElemType����) */
     en.NType=GetCurElem(p).NType;
     if(en.NType==Qu) /* �����¼� */
       CustomerArrived(); /* ����ͻ������¼� */
     else /* ��ĳ�����뿪���¼� */
       CustomerDeparture(); /* ����ͻ��뿪�¼� */
   } /* ���㲢���ƽ������ʱ�� */
   printf("������=%d �����ڵ���Ŀͻ���ʱ����=0��%d���� ÿ���ͻ�����ҵ���ʱ��=1��%d����\n",Qu,Khjg,Blsj);
   printf("�ͻ�����:%d, ���пͻ�����ʱ:%ld����,ƽ��ÿ�˺�ʱ:%d����,",CustomerNum,TotalTime,TotalTime/CustomerNum);
   printf("���һ���ͻ��뿪��ʱ��:%d��\n",en.OccurTime);
 }

 void OpenForDay()
 { /* ��ʼ���¼�����ev�Ҳ����1�������¼�����ʼ���Ŷӻ�q����ʼ��Qu������Ϊ1(����) */
   int i;
   InitList(&ev); /* ��ʼ���¼�����evΪ�� */
   en.OccurTime=0; /* �趨��1λ�ͻ�����ʱ��Ϊ0(����һ���ţ����пͻ���) */
   en.NType=Qu; /* ���� */
   OrderInsert(&ev,en,cmp); /* ����1�������¼�en��������¼���ev�У���bo2-6.c�� */
   InitQueue(&q); /* ��ʼ���Ŷӻ�����q */
   for(i=0;i<Qu;i++)
     chk[i]=1; /* ��ʼ��Qu������Ϊ1(����) */
 }

 int ChuangKou()
 { /* ���ؿ��д��ڵ����(0��Qu-1)�����ж�����ڿ��У����������С�ġ����޿��д��ڣ�����Qu */
   int i;
   for(i=0;i<Qu;i++)
     if(chk[i])
       return i;
   return i;
 }

 void CustomerArrived()
 { /* ����ͻ������¼�en(en.NType=Qu)����algo3-12.c��ͬ */
   QElemType f;
   int durtime,intertime,i;
   ++CustomerNum; /* �ͻ�����1 */
   Random(&durtime,&intertime); /* ���ɵ�ǰ�ͻ�����ҵ���ʱ�����һ���ͻ������ʱ����2������� */
   et.OccurTime=en.OccurTime+intertime; /* ��һ�ͻ�et����ʱ��=��ǰ�ͻ�en�ĵ���ʱ��+ʱ���� */
   et.NType=Qu; /* ��һ�ͻ������¼� */
   if(et.OccurTime<CloseTime) /* ��һ�ͻ�����ʱ������δ���� */
     OrderInsert(&ev,et,cmp); /* ��������һ�ͻ������¼�et�����¼���ev�У���bo2-6.c�� */
   f.ArrivalTime=en.OccurTime; /* ����ǰ�ͻ������¼�en��������Ԫ��f */
   f.Duration=durtime;
   EnQueue(&q,f); /* ����ǰ�ͻ�f��ӵ��Ŷӻ� */
   i=ChuangKou(); /* ����д��ڵ���� */
   if(i<Qu) /* �п��д��� */
   {
     DeQueue(&q,&customer[i]); /* ɾȥ�Ŷӻ�����ͷ�ͻ�(Ҳ���Ǹ���ӵ�f���Ŷӻ���i�Ŵ���) */
 /*  if(j++<20) /* ���ǰ20���ͻ�������Ϣ������ҵ�񴰿���Ϣ���ļ�c.txt�� */
 /*    fprintf(fq,"�ͻ�����ʱ��=%3d,����ҵ���ʱ��=%2d,���ڴ���=%d\n",customer[i].ArrivalTime,customer[i].Duration,i); */
     et.OccurTime=en.OccurTime+customer[i].Duration; /* �趨һ��i�Ŵ��ڵ��뿪�¼�et */
     et.NType=i; /* ��i�Ŵ��ڵ��뿪�¼� */
     OrderInsert(&ev,et,cmp); /* �����뿪�¼�et����������¼���ev�� */
     chk[i]=0; /* i�Ŵ���״̬��æ */
   }
 }

 void CustomerDeparture()
 { /* ����ͻ��뿪�¼�en(en.NType<Qu)����algo3-12.c��ͬ */
   int i;
   i=en.NType; /* ȷ���뿪�¼�en�����Ĵ������i */
   chk[i]=1; /* i�Ŵ���״̬���� */
   TotalTime+=en.OccurTime-customer[i].ArrivalTime; /* �ͻ�����ʱ��=�뿪�¼�en�ķ���ʱ��-�ÿͻ��ĵ���ʱ�� */
   if(!QueueEmpty(q))
   { /* ��i���ڵĿͻ��뿪���Ŷӻ��Բ��� */
     DeQueue(&q,&customer[i]); /* ɾȥ�Ŷӻ�����ͷ�ͻ������丳��customer[i](�Ŷӻ�����ͷ�ͻ�ȥi���ڰ���ҵ��) */
 /*  if(j++<20) /* ���ǰ20���ͻ�������Ϣ������ҵ�񴰿���Ϣ���ļ�c.txt�� */
 /*    fprintf(fq,"�ͻ�����ʱ��=%3d,����ҵ���ʱ��=%2d,���ڴ���=%d\n",customer[i].ArrivalTime,customer[i].Duration,i); */
     chk[i]=0; /* i�Ŵ���״̬��æ */
     et.OccurTime=en.OccurTime+customer[i].Duration; /* �趨customer[i]���뿪�¼�et,�ͻ����뿪ʱ��=ԭ�ͻ����뿪ʱ��+��ǰ�ͻ�����ҵ���ʱ�� */
     et.NType=i; /* ��i�Ŵ��ڵ��뿪�¼� */
     OrderInsert(&ev,et,cmp); /* �����뿪�¼�et����������¼���ev�� */
   }
 }

 int main()
 {
 /*fq=fopen("c.txt","w"); /* ��c.txt�ļ�������д��ͻ�������Ϣ */
 /*fp=fopen("d.txt","w"); /* ��d.txt�ļ�������д�������¼������ʷ��¼ */
   printf("����������Ӫҵʱ�䳤��(��λ:��): ");
   scanf("%d",&CloseTime);
 /*srand(time(0)); /* �������������,��ʹÿ�����г���������������ͬ(time(0)�ǳ�������,�����ʱ���й�) */
   Bank_Simulation();
 /*fclose(fq); /* �ر�c.txt */
 /*fclose(fp); /* �ر�d.txt */
 
 return 0; 
 }
