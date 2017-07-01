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
 
 typedef struct
 {
   int x; /* ��ֵ */
   int y; /* ��ֵ */
 }PosType; /* �Թ�����λ������ */

 #define MAXLENGTH 25 /* ���Թ����������Ϊ25 */
 typedef int MazeType[MAXLENGTH][MAXLENGTH]; /* �Թ���������[��][��] */

 /* ȫ�ֱ��� */
 MazeType m; /* �Թ����� */
 int x,y; /* �Թ������������� */
 PosType begin,end; /* �Թ����������,�������� */
 
 #define D 8 /* �ƶ���������ֻ��ȡ4��8��(8������б�У�4����ֻ��ֱ��) */

 typedef struct /* �������Ԫ�غ�ջԪ��Ϊͬ���͵Ľṹ�� */
 {
   PosType seat; /* ��ǰ�����ֵ����ֵ */
   int pre; /* ǰһ���ڶ����е���� */
 }QElemType,SElemType; /* ջԪ�غͶ���Ԫ�� */
 
 #define STACK_INIT_SIZE 10 
 /* �洢�ռ��ʼ������ */
 #define STACK_INCREMENT 2 
 /* �洢�ռ�������� */
 typedef struct SqStack
 {
   SElemType *base; /* ��ջ����֮ǰ������֮��base��ֵΪNULL */
   SElemType *top; /* ջ��ָ�� */
   int stacksize; /* ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ */
 }SqStack; /* ˳��ջ */
 
 #define QUEUE_INIT_SIZE 10 /* ���д洢�ռ�ĳ�ʼ������ */
 #define QUEUE_INCREMENT 2 /* ���д洢�ռ�ķ������� */
 typedef struct
 {
   QElemType *base; /* ��ʼ���Ķ�̬����洢�ռ� */
   int front; /* ͷָ�룬�����в���,ָ�����ͷԪ�� */
   int rear; /* βָ�룬�����в���,ָ�����βԪ�ص���һ��λ�� */
   int queuesize; /* ��ǰ����Ĵ洢����(��sizeof(QElemType)Ϊ��λ) */
 }SqQueue2;
 
 void Print()
 { /* ����Թ��Ľ�(m����) */
   int i,j;
   for(i=0;i<x;i++)
   {
     for(j=0;j<y;j++)
       printf("%3d",m[i][j]);
     printf("\n");
   }
 }

 void Init(int k)
 { /* �趨�Թ�����(ǽΪֵ0,ͨ��ֵΪk) */
   int i,j,x1,y1;
   printf("�������Թ�������,����(������ǽ)��");
   scanf("%d,%d",&x,&y);
   for(i=0;i<x;i++) /* �����ܱ�ֵΪ0(��ǽ) */
   {
     m[0][i]=0; /* ���ܱ� */
     m[x-1][i]=0;
   }
   for(i=0;i<y-1;i++)
   {
     m[i][0]=0; /* ���ܱ� */
     m[i][y-1]=0;
   }
   for(i=1;i<x-1;i++)
     for(j=1;j<y-1;j++)
       m[i][j]=k; /* �������ǽ�����඼��ͨ������ֵΪk */
   printf("�������Թ���ǽ��Ԫ����");
   scanf("%d",&j);
   printf("�����������Թ���ǽÿ����Ԫ������,������\n");
   for(i=1;i<=j;i++)
   {
     scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0; /* �޸�ǽ��ֵΪ0 */
   }
   printf("�Թ��ṹ����:\n");
   Print();
   printf("��������ڵ�����,������");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("��������ڵ�����,������");
   scanf("%d,%d",&end.x,&end.y);
 }
 
  void InitStack(SqStack *S)
 { /* ����һ����ջS */
   (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
   if(!(*S).base)
     exit(OVERFLOW); /* �洢����ʧ�� */
   (*S).top=(*S).base;
   (*S).stacksize=STACK_INIT_SIZE;
 }

 void DestroyStack(SqStack *S)
 { /* ����ջS��S���ٴ��� */
   free((*S).base);
   (*S).base=NULL;
   (*S).top=NULL;
   (*S).stacksize=0;
 }

 void ClearStack(SqStack *S)
 { /* ��S��Ϊ��ջ */
   (*S).top=(*S).base;
 }

 Status StackEmpty(SqStack S)
 { /* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
   if(S.top==S.base)
     return TRUE;
   else
     return FALSE;
 }

 int StackLength(SqStack S)
 { /* ����S��Ԫ�ظ�������ջ�ĳ��� */
   return S.top-S.base;
 }

 Status GetTop(SqStack S,SElemType *e)
 { /* ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR */
   if(S.top>S.base)
   {
     *e=*(S.top-1);
     return OK;
   }
   else
     return ERROR;
 }

 void Push(SqStack *S,SElemType e)
 { /* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
   if((*S).top-(*S).base>=(*S).stacksize) /* ջ����׷�Ӵ洢�ռ� */
   {
     (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACK_INCREMENT)*sizeof(SElemType));
     if(!(*S).base)
       exit(OVERFLOW); /* �洢����ʧ�� */
     (*S).top=(*S).base+(*S).stacksize;
     (*S).stacksize+=STACK_INCREMENT;
   }
   *((*S).top)++=e;
 }

 Status Pop(SqStack *S,SElemType *e)
 { /* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
   if((*S).top==(*S).base)
     return ERROR;
   *e=*--(*S).top;
   return OK;
 }

 void StackTraverse(SqStack S,void(*visit)(SElemType))
 { /* ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit() */
   while(S.top>S.base)
     visit(*S.base++);
   printf("\n");
 }
 
  void InitQueue(SqQueue2 *Q)
 { /* ����һ���ն���Q */
   (*Q).base=(QElemType *)malloc(QUEUE_INIT_SIZE*sizeof(QElemType));
   if(!(*Q).base) /* �洢����ʧ�� */
     exit(ERROR);
   (*Q).front=(*Q).rear=0;
   (*Q).queuesize=QUEUE_INIT_SIZE;
 }

 void DestroyQueue(SqQueue2 *Q)
 { /* ���ٶ���Q��Q���ٴ��� */
   if((*Q).base)
     free((*Q).base);
   (*Q).base=NULL;
   (*Q).front=(*Q).rear=(*Q).queuesize=0;
 }

 void ClearQueue(SqQueue2 *Q)
 { /* ��Q��Ϊ�ն��� */
   (*Q).front=(*Q).rear=0;
 }

 Status QueueEmpty(SqQueue2 Q)
 { /* ������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE */
   if(Q.front==Q.rear) /* ���пյı�־ */
     return TRUE;
   else
     return FALSE;
 }

 Status GetHead(SqQueue2 Q,QElemType *e)
 { /* �����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR */
   if(Q.front==Q.rear) /* ���п� */
     return ERROR;
   *e=Q.base[Q.front];
   return OK;
 }
 
  int QueueLength(SqQueue2 Q)
 { /* ����Q��Ԫ�ظ����������еĳ��� */
   return(Q.rear-Q.front);
 }

 void EnQueue(SqQueue2 *Q,QElemType e)
 { /* ����Ԫ��eΪQ���µĶ�βԪ�� */
   if((*Q).rear==(*Q).queuesize)
   { /* �����������Ӵ洢��Ԫ */
     (*Q).base=(QElemType *)realloc((*Q).base,((*Q).queuesize+QUEUE_INCREMENT)*sizeof(QElemType));
     if(!(*Q).base) /* ���ӵ�Ԫʧ�� */
       exit(ERROR);
   }
   (*Q).base[(*Q).rear++]=e;
 }

 Status DeQueue(SqQueue2 *Q,QElemType *e)
 { /* �����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
   if((*Q).front==(*Q).rear) /* ���п� */
     return ERROR;
   *e=(*Q).base[(*Q).front++];
   return OK;
 }

 void QueueTraverse(SqQueue2 Q,void(*vi)(QElemType))
 { /* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi() */
   int i=Q.front;
   while(i!=Q.rear)
     vi(Q.base[i++]);
   printf("\n");
 }
 
  struct /* �ƶ����飬�ƶ�������������˳ʱ��ת */
 {
   int x,y;
 }move[D]={
 #if D==8
	   {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
 #endif
 #if D==4
	   {0,1},{1,0},{0,-1},{-1,0}};
 #endif

 void Path()
 { /* �����������һ���Թ�·�� */
   SqQueue2 q; /* ���÷�ѭ��˳����� */
   QElemType qf,qt; /* ��ǰ�����һ�� */
   SqStack s; /* ����˳��ջ */
   int i,flag=1; /* ���ҵ����ڣ�flag=0 */
   qf.seat.x=begin.x; /* �������Ϊ��ǰ�� */
   qf.seat.y=begin.y;
   qf.pre=-1; /* �����(��һ��)����һ������=-1 */
   m[qf.seat.x][qf.seat.y]=-1; /* ��ʼ����Ϊ-1(����ѷ��ʹ�) */
   InitQueue(&q);
   EnQueue(&q,qf); /* ������ */
   while(!QueueEmpty(q)&&flag)
   { /* �����л���û������������ĵ��һ�û�ҵ����� */
     DeQueue(&q,&qf); /* ����qfΪ��ǰ�� */
     for(i=0;i<D;i++) /* ����������� */
     {
       qt.seat.x=qf.seat.x+move[i].x; /* ��һ������� */
       qt.seat.y=qf.seat.y+move[i].y;
       if(m[qt.seat.x][qt.seat.y]==1)
       { /* �˵���ͨ���Ҳ��������ʹ� */
         m[qt.seat.x][qt.seat.y]=-1; /* ����ѷ��ʹ� */
         qt.pre=q.front-1; /* qt��ǰһ�㴦�ڶ������ֶ�ͷ��1��λ��(ûɾ��) */
	 EnQueue(&q,qt); /* ���qt */
         if(qt.seat.x==end.x&&qt.seat.y==end.y) /* �����յ� */
         {
           flag=0;
           break;
         }
       }
     }
   }
   if(flag) /* �������������л�û�����յ� */
     printf("û��·���ɵ����յ㣡\n");
   else /* �����յ� */
   {
     InitStack(&s); /* ��ʼ��sջ */
     i=q.rear-1; /* iΪ����ջԪ���ڶ����е�λ�� */
     while(i>=0) /* û����� */
     {
       Push(&s,q.base[i]); /* �������е�·����ջ(ջ��Ϊ���ڣ�ջ��Ϊ���) */
       i=q.base[i].pre; /* iΪǰһԪ���ڶ����е�λ�� */
     }
     i=0; /* iΪ�߳��Թ����㼣 */
     while(!StackEmpty(s))
     {
       Pop(&s,&qf); /* ��������ڵ����ڵ�˳�򵯳�·�� */
       i++;
       m[qf.seat.x][qf.seat.y]=i; /* ���·��Ϊ�㼣(���ǰ��ֵΪ-1) */
     }
     printf("�߳��Թ���һ��������\n");
     Print(); /* ���m���� */
   }
 }

 int main()
 {
   Init(1); /* ��ʼ���Թ���ͨ��ֵΪ1 */
   Path(); /* ��һ���Թ�·�� */
   
   return 0; 
 }
 
 
 

 
 
 
