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
 #include<stdarg.h> /* ʵ�ֱ䳤������Ҫ������ͷ�ļ� */
 
 typedef int ElemType;
 ElemType Max(int num,...) /* ...��ʾ�䳤������λ���βα�����,ǰ�����������һ���̶����� */
 { /* �������ܣ�����num�����е����ֵ */
   va_list ap; /* ����ap�Ǳ䳤����������(C���Ե���������) */
   int i;
   ElemType m,n;
   if(num<1)
     exit(ERROR);
   va_start(ap,num); /* apָ��̶�����num�����ʵ�α� */
   m=va_arg(ap,ElemType); /* ���ζ�ȡap��ָ��ʵ��(�Զ���Ϊ�ָ���)��ΪElemType����ʵ��,ap����� */
   for(i=1;i<num;++i)
   {
     n=va_arg(ap,ElemType); /* ͬ�� */
     if(m<n)
       m=n;
   }
   va_end(ap); /* ��va_start()��ԣ������Ա䳤������Ķ�ȡ��ap����ָ��䳤������ */
   return m;
 }

 int main()
 {
   printf("1.���ֵΪ%d\n",Max(4,7,9,5,8)); /* ��4�����������ֵ��ap���ָ��7,9,5,8�� */
   printf("2.���ֵΪ%d\n",Max(3,17,36,25)); /* ��3�����������ֵ��ap���ָ��17,36,25�� */
   
   return 0;
 }
 
 
