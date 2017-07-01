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
 
  int curstep=1; /* ��ǰ�㼣����ֵ(����ڴ�)Ϊ1 */
 typedef struct
 {
   int ord; /* ͨ������·���ϵģ���ţ� */
   PosType seat; /* ͨ�������Թ��еģ�����λ�ã� */
   int di; /* �Ӵ�ͨ����������һͨ����ģ�����(0��3��ʾ������) */
 }SElemType; /* ջ��Ԫ������ */
 
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
 
 

 /* ����ǽԪ��ֵΪ0����ͨ��·��Ϊ1������ͨ��·��Ϊ-1��ͨ��·��Ϊ�㼣 */
 Status Pass(PosType b)
 { /* ���Թ�m��b������Ϊ1(��ͨ��·��)������OK�����򣬷���ERROR */
   if(m[b.x][b.y]==1)
     return OK;
   else
     return ERROR;
 }

 void FootPrint(PosType a)
 { /* ʹ�Թ�m��a���ֵ��Ϊ�㼣(curstep) */
   m[a.x][a.y]=curstep;
 }

 void NextPos(PosType *c,int di)
 { /* ���ݵ�ǰλ�ü��ƶ����������һλ�� */
   PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}}; /* {������,������},�ƶ�����,����Ϊ�������� */
   (*c).x+=direc[di].x;
   (*c).y+=direc[di].y;
 }

 void MarkPrint(PosType b)
 { /* ʹ�Թ�m��b�����ű�Ϊ-1(����ͨ����·��) */
   m[b.x][b.y]=-1;
 }

 Status MazePath(PosType start,PosType end) /* �㷨3.3 */
 { /* ���Թ�m�д��ڴ����start������end��ͨ���������һ�� */
   /* �����ջ��(��ջ�׵�ջ��)��������TRUE�����򷵻�FALSE */
   SqStack S; /* ˳��ջ */
   PosType curpos; /* ��ǰλ�� */
   SElemType e; /* ջԪ�� */
   InitStack(&S); /* ��ʼ��ջ */
   curpos=start; /* ��ǰλ������� */
   do
   {
     if(Pass(curpos))
     { /* ��ǰλ�ÿ���ͨ��������δ���ߵ�����ͨ���� */
       FootPrint(curpos); /* �����㼣 */
       e.ord=curstep;
       e.seat=curpos;
       e.di=0;
       Push(&S,e); /* ��ջ��ǰλ�ü�״̬ */
       curstep++; /* �㼣��1 */
       if(curpos.x==end.x&&curpos.y==end.y) /* �����յ�(����) */
         return TRUE;
       NextPos(&curpos,e.di); /* �ɵ�ǰλ�ü��ƶ�����ȷ����һ����ǰλ�� */
     }
     else
     { /* ��ǰλ�ò���ͨ�� */
       if(!StackEmpty(S)) /* ջ���� */
       {
         Pop(&S,&e); /* ��ջ��ǰһλ�� */
         curstep--; /* �㼣��1 */
         while(e.di==3&&!StackEmpty(S)) /* ǰһλ�ô������һ������(��) */
         {
           MarkPrint(e.seat); /* ��ǰһλ�����²���ͨ���ı��(-1) */
           Pop(&S,&e); /* ���˻�һ�� */
           curstep--; /* �㼣�ټ�1 */
         }
         if(e.di<3) /* û�����һ������(��) */
         {
           e.di++; /* ����һ������̽�� */
           Push(&S,e); /* ��ջ��λ�õ���һ������ */
           curstep++; /* �㼣��1 */
           curpos=e.seat; /* ȷ����ǰλ�� */
           NextPos(&curpos,e.di); /* ȷ����һ����ǰλ���Ǹ��·����ϵ����ڿ� */
         }
       }
     }
   }while(!StackEmpty(S));
   return FALSE;
 }

 int main()
 {
   Init(1); /* ��ʼ���Թ���ͨ��ֵΪ1 */
   if(MazePath(begin,end)) /* ��ͨ· */
   {
     printf("���Թ�����ڵ����ڵ�һ��·������:\n");
     Print(); /* �����ͨ· */
   }
   else
     printf("���Թ�û�д���ڵ����ڵ�·��\n");
 
   return 0;
 }
 