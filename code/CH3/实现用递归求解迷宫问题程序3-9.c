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
 
  void Try(PosType cur,int curstep)
 { /* �ɵ�ǰλ��cur����ǰ����curstep��̽��һ�� */
   int i;
   PosType next; /* ��һ��λ�� */
   PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}}; /* {������,������},�ƶ�����,����Ϊ�������� */
   for(i=0;i<=3;i++) /* ������̽���������ĸ����� */
   {
     next.x=cur.x+direc[i].x; /* �����ƶ����򣬸���һλ�ø�ֵ */
     next.y=cur.y+direc[i].y;
     if(m[next.x][next.y]==-1) /* ��һ��λ����ͨ· */
     {
       m[next.x][next.y]=++curstep; /* ����һ��λ����Ϊ�㼣 */
       if(next.x!=end.x||next.y!=end.y) /* û���յ� */
         Try(next,curstep); /* ����һ��λ�ü�����̽(���׵ݹ���ã����յ����) */
       else /* ���յ� */
       {
         Print(); /* ������(���ڣ����ٵݹ����) */
         printf("\n");
       }
       m[next.x][next.y]=-1; /* �ָ�Ϊͨ·���Ա�����һ��������̽��һ��· */
       curstep--; /* �㼣Ҳ��1 */
     }
   }
 }

 int main()
 {
   Init(-1); /* ��ʼ���Թ���ͨ��ֵΪ-1 */
   printf("���Թ�����ڵ����ڵ�·������:\n");
   m[begin.x][begin.y]=1; /* ��ڵ��㼣Ϊ1 */
   Try(begin,1); /* �ɵ�1�������̽�� */
   
   return 0; 
 }
 
 