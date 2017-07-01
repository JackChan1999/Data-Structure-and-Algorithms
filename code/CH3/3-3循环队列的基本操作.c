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
 typedef int QElemType;
 
 #define MAX_QSIZE 5 //�����г���+1
 typedef struct
 {
 	QElemType *base;//��ʼ���Ķ�̬����洢�ռ�
	int front;//ͷָ�룬�����в��գ�ָ�����ͷԪ�� 
	int rear; //βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�� 
 }SqQueue;
 
 void InitQueue(SqQueue *Q);
 void DestroyQueue(SqQueue *Q);
 void ClearQueue(SqQueue *Q);
 Status QueueEmpty(SqQueue Q);
 int QueueLength(SqQueue Q);
 Status GetHead(SqQueue Q, QElemType *e);
 Status EnQueue(SqQueue *Q, QElemType e);
 Status DeQueue(SqQueue *Q, QElemType *e);
 void QueueTraverse(SqQueue Q, void(*vi)(QElemType));
 void print(QElemType i);
          
 int main()
 {
   Status j;
   int i=0,l;
   QElemType d;
   SqQueue Q;
   InitQueue(&Q);
   printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   printf("���������Ͷ���Ԫ��(������%d��),-1Ϊ��ǰ������: ",MAX_QSIZE-1);
   do
   {
     scanf("%d",&d);
     if(d==-1)
       break;
     i++;
     EnQueue(&Q,d);
   }while(i<MAX_QSIZE-1);
   printf("���г���Ϊ: %d\n",QueueLength(Q));
   printf("���ڶ��пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   printf("����%d���ɶ�ͷɾ��Ԫ��,��β����Ԫ��:\n",MAX_QSIZE);
   for(l=1;l<=MAX_QSIZE;l++)
   {
     DeQueue(&Q,&d);
     printf("ɾ����Ԫ����%d,������������Ԫ��: ",d);
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   l=QueueLength(Q);
   printf("���ڶ����е�Ԫ��Ϊ: \n");
   QueueTraverse(Q,print);
   printf("�����β������%d��Ԫ��\n",i+MAX_QSIZE);
   if(l-2>0)
     printf("�����ɶ�ͷɾ��%d��Ԫ��:\n",l-2);
   while(QueueLength(Q)>2)
   {
     DeQueue(&Q,&d);
     printf("ɾ����Ԫ��ֵΪ%d\n",d);
   }
   j=GetHead(Q,&d);
   if(j)
     printf("���ڶ�ͷԪ��Ϊ: %d\n",d);
   ClearQueue(&Q);
   printf("��ն��к�, ���пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   DestroyQueue(&Q);
	
 	return 0;
 }
 
 void InitQueue(SqQueue *Q)
 {
 	//����һ���ն���
	(*Q).base = (QElemType *)malloc(MAX_QSIZE * sizeof(QElemType));
	if (! (*Q).base)//�洢����ʧ��
	{
		exit(OVERFLOW); 
	} 
	(*Q).front = (*Q).rear = 0;
 }
 
 void DestroyQueue(SqQueue *Q)
 {
 	//���ٶ���Q,Q���ٴ���
	if ((*Q).base)
	{
		free((*Q).base);
	} 
	(*Q).base = NULL;
	(*Q).front = (*Q).rear = 0;
 }
 
 void ClearQueue(SqQueue *Q)
 {
 	//��Q��Ϊ�ն���
	(*Q).front = (*Q).rear = 0; 
 }
 
 Status QueueEmpty(SqQueue Q)
 {
 	//������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	if (Q.front == Q.rear)//���пյı�־
	{
		return TRUE; 
	} 
	else
	{
		return FALSE; 
	}
 }
 
 int QueueLength(SqQueue Q)
 {
 	//����Q��Ԫ�ظ����������еĳ���
	return (Q.rear-Q.front+MAX_QSIZE) % MAX_QSIZE;  
 }
 
 Status GetHead(SqQueue Q, QElemType *e)
 {
 	//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	if (Q.front == Q.rear)//���п�
	{
		return ERROR;
	} 
	*e = Q.base[Q.front];
	
	return OK;
 }
 
 Status EnQueue(SqQueue *Q, QElemType e)
 {
 	//����Ԫ��eΪQ���µĶ�βԪ��
	if ( ((*Q).rear + 1)%MAX_QSIZE == (*Q).front )//������ 
	{
		return ERROR;
	}
	(*Q).base[ (*Q).rear ] = e;
	(*Q).rear = ( (*Q).rear + 1) % MAX_QSIZE;
	
	return OK;
 }
 
 Status DeQueue(SqQueue *Q, QElemType *e)
 {
 	//�����в�Ϊ�գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
	if ((*Q).front == (*Q).rear)//���п� 
	{
		return ERROR;
	}
	*e = (*Q).base[(*Q).front];
	(*Q).front = ((*Q).front+1)%MAX_QSIZE;
	
	return OK; 
 }
 
 void QueueTraverse(SqQueue Q, void(*vi)(QElemType))
 {
 	//�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()
	int i;
	i = Q.front;
	
	while (i != Q.rear)
	{
		vi(Q.base[i]);
		i = (i+1) % MAX_QSIZE;
	}
	printf("\n");
 }
 
 void print(QElemType i)
 {
 	printf("%d ", i);
 }
 
 
 
  
  
 