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
 #define N 8
 
 void bubble_sort(int a[],int n)
 { /* ��a�����������������г���С�����������������(��������) */
   int i,j,t;
   Status change;
   for(i=n-1,change=TRUE;i>1&&change;--i)
   {
     change=FALSE;
     for(j=0;j<i;++j)
       if(a[j]>a[j+1])
       {
         t=a[j];
         a[j]=a[j+1];
         a[j+1]=t;
         change=TRUE;
       }
   }
 }

 void print(int r[],int n)
 {
   int i;
   for(i=0;i<n;i++)
     printf("%d ",r[i]);
   printf("\n");
 }

 int main()
 {
   int d[N]={49,38,65,97,76,13,27,49};
   printf("����ǰ:\n");
   print(d,N);
   bubble_sort(d,N);
   printf("�����:\n");
   print(d,N);
   
   return 0; 
 }
