 typedef char SElemType;
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
 
  void check()
 { /* �������������һ���ַ��������������Ƿ���� */
   SqStack s;
   SElemType ch[80],*p,e;
   InitStack(&s); /* ��ʼ��ջ�ɹ� */
   printf("����������ţ�()��[]��{}���ı��ʽ\n");
   gets(ch);
   p=ch; /* pָ���ַ��������ַ� */
   while(*p) /* û����β */
     switch(*p)
     {
       case '(':
       case '[':
       case '{':Push(&s,*p++); /* ��������ջ����p++ */
                break;
       case ')':
       case ']':
       case '}':if(!StackEmpty(s)) /* ջ���� */
                {
                  Pop(&s,&e); /* ����ջ��Ԫ�� */
                  if(!(e=='('&&*p==')'||e=='['&&*p==']'||e=='{'&&*p=='}'))
                  { /* ����3��ƥ�����֮������ */
                    printf("�������Ų����\n");
                    exit(ERROR);
                  }
                }
                else /* ջ�� */
                {
                  printf("ȱ��������\n");
                  exit(ERROR);
                }
       default: p++; /* �����ַ�������ָ������� */
     }
   if(StackEmpty(s)) /* �ַ�������ʱջ�� */
     printf("����ƥ��\n");
   else
     printf("ȱ��������\n");
 }

 void main()
 {
   check();
 }
 
 
