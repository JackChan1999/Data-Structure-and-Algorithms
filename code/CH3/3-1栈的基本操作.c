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
 typedef int SElemType;//����ջԪ������
 
 #define STACK_INIT_SIZE 10  //�洢�ռ��ʼ������
 #define STACK_INCREMENT 2   //�洢�ռ��������
 typedef struct SqStack
 {
 	SElemType *base;//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;//ջ��ָ��
	int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
 }SqStack;//˳��ջ
 
 void InitStack(SqStack *S);
 void DestroyStack(SqStack *S);
 void ClearStack(SqStack *S);
 Status StackEmpty(SqStack S);
 int StackLength(SqStack S);
 Status GetTop(SqStack S, SElemType *e);
 void Push(SqStack *S, SElemType e);
 Status Pop(SqStack *S, SElemType *e);
 void StackTraverse(SqStack S, void(*visit)(SElemType));
 void print(SElemType c);
 
 int main()
 {
   int j;
   SqStack s;
   SElemType e;
   InitStack(&s);
   for(j=1;j<=12;j++)
     Push(&s,j);
   printf("ջ��Ԫ������Ϊ��");
   StackTraverse(s,print);
   Pop(&s,&e);
   printf("������ջ��Ԫ�� e=%d\n",e);
   printf("ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("ջ��Ԫ�� e=%d ջ�ĳ���Ϊ%d\n",e,StackLength(s));
   ClearStack(&s);
   printf("���ջ��ջ�շ�%d(1:�� 0:��)\n",StackEmpty(s));
   DestroyStack(&s);
   printf("����ջ��s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
   
   return 0;
 }
 
 
 void InitStack(SqStack *S)
 {
 	//����һ����ջS
    (*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (! (*S).base)
	{
		exit(OVERFLOW);//�洢����ʧ�� 
	} 
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE; 	
 } 
 
 void DestroyStack(SqStack *S)
 {
 	//����ջS��S���ٴ���
	 free( (*S).base );
	 (*S).base = NULL;
	 (*S).top = NULL;
	 (*S).stacksize = 0; 
 }
 
 void ClearStack(SqStack *S)
 {
 	//��S��Ϊ��ջ
    (*S).top = (*S).base; 
 }
 
 Status StackEmpty(SqStack S)
 {
 	//��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
	if (S.top == S.base)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}	
 }
 
 int StackLength(SqStack S)
 {
 	//����S��Ԫ�ظ�������ջ�ĳ���
	return S.top - S.base; 
 }
 
 Status GetTop(SqStack S, SElemType *e)
 {
 	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	if (S.top > S.base)
	{
		*e = *(S.top - 1);
		return OK;
	} 
	else
	{
		return ERROR;
	}
 }
 
 void Push(SqStack *S, SElemType e)
 {
 	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if ( ((*S).top - (*S).base) >= (*S).stacksize )//ջ����׷�Ӵ洢�ռ�
	{
	  (*S).base = (SElemType *)realloc( (*S).base, ((*S).stacksize +STACK_INCREMENT)
                                                        * sizeof(SElemType) );
	  if (! (*S).base)
	  {
	    exit(OVERFLOW);//�洢����ʧ�� 
	  } 
			
	  (*S).top = (*S).base + (*S).stacksize;
	  (*S).stacksize += STACK_INCREMENT; 
	} 
		
	*((*S).top)++ = e;
 }
 
 Status Pop(SqStack *S, SElemType *e)
 {
 	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK��
	//���򷵻�ERROR
	if ( (*S).top == (*S).base )
	{
		return ERROR;
	} 
	
	*e = *--(*S).top ;
	return OK;
 }
 
 void StackTraverse(SqStack S, void(*visit)(SElemType))
 {
 	//��ջ����ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()
	while (S.top > S.base)
	{
		visit( *S.base++ );
	} 
	
	printf("\n");
 }
 
 void print(SElemType c)
 {
 	printf("%d ", c);
 }