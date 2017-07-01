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
 
 #define N 6 /* �ַ������� */
 typedef char ElemType[N];
 
 #define MAX_SIZE 100 /* �������󳤶� */
 typedef struct
 {
   ElemType data;
   int cur;
 }component,SLinkList[MAX_SIZE];
 
 int main()
 {
   SLinkList s={{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0}}; /* �̿�����ͼ2.10(a)��״̬ */
   int i;
   i=s[0].cur; /* iָʾ��1������λ�� */
   while(i)
   { /* ����̿�����ͼ2.10(a)��״̬ */
     printf("%s ",s[i].data); /* �������ĵ�ǰֵ */
     i=s[i].cur; /* �ҵ���һ�� */
   }
   printf("\n");
   s[4].cur=9; /* ���̿�����ͼ2.10(b)�޸�(��"LI"֮�����"SHI") */
   s[9].cur=5;
   strcpy(s[9].data,"SHI");
   s[6].cur=8; /* ɾ��"ZHENG" */
   i=s[0].cur; /* iָʾ��1������λ�� */
   while(i)
   { /* ����̿�����ͼ2.10(b)��״̬ */
     printf("%s ",s[i].data); /* �������ĵ�ǰֵ */
     i=s[i].cur; /* �ҵ���һ�� */
   }
   printf("\n");
   
   return 0; 
 }
 
 