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
 
 #define QUEUE_INIT_SIZE 10 //���д洢�ռ�ĳ�ʼ������
 #define QUEUE_INCREMENT 2 //���д洢�ռ�ķ�������
 
 typedef struct
 {
 	QElemType *base;//��ʼ���Ķ�̬����洢�ռ�
	int front;//ͷָ�룬�����в��գ�ָ�����ͷԪ��
	int rear;//βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��
	int queuesize;//��ǰ����Ĵ洢����(��sizeof(QElemType)Ϊ��λ) 
 }SqQueue2;
 
 
 void InitQueue(SqQueue2 *Q);
 void DestroyQueue(SqQueue2 *Q);
 void ClearQueue(SqQueue2 *Q);
 Status QueueEmpty(SqQueue2 Q);
 Status GetHead(SqQueue2 Q, QElemType *e);
 int QueueLength(SqQueue2 Q);
 void EnQueue(SqQueue2 *Q, QElemType e);
 Status DeQueue(SqQueue2 *Q, QElemType *e);
 void QueueTraverse(SqQueue2 Q, void(*vi)(QElemType));
 void print(QElemType i);
 
 int main()
 {
   Status j;
   int i,n=11;
   QElemType d;
   SqQueue2 Q;
   InitQueue(&Q);
   printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   printf("���г���Ϊ��%d\n",QueueLength(Q));
   printf("������%d�����Ͷ���Ԫ��:\n",n);
   for(i=0;i<n;i++)
   {
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   printf("���г���Ϊ��%d\n",QueueLength(Q));
   printf("���ڶ��пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   printf("���ڶ����е�Ԫ��Ϊ: \n");
   QueueTraverse(Q,print);
   DeQueue(&Q,&d);
   printf("ɾ����ͷԪ��%d\n",d);
   printf("�����е�Ԫ��Ϊ: \n");
   QueueTraverse(Q,print);
   j=GetHead(Q,&d);
   if(j)
     printf("��ͷԪ��Ϊ: %d\n",d);
   else
     printf("�޶�ͷԪ��(�ն���)\n");
   ClearQueue(&Q);
   printf("��ն��к�, ���пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   j=GetHead(Q,&d);
   if(j)
     printf("��ͷԪ��Ϊ: %d\n",d);
   else
     printf("�޶�ͷԪ��(�ն���)\n");
   DestroyQueue(&Q);
   
   return 0;
 }
 
 
 
 
 
 
 
 void InitQueue(SqQueue2 *Q)
 {
 	//����һ���ն���Q
	(*Q).base = (QElemType *)malloc(QUEUE_INIT_SIZE * sizeof(QElemType));
	if (! (*Q).base)//�洢����ʧ��
	{
		exit(ERROR); 
	}
	(*Q).front = (*Q).rear = 0;
	(*Q).queuesize = QUEUE_INIT_SIZE;
 } 
 
 void DestroyQueue(SqQueue2 *Q)
 {
 	//���ٶ���Q,Q���ٴ��� 
 	if ((*Q).base)
 	{
 		free((*Q).base);
    }
    (*Q).base = NULL;
    (*Q).front = (*Q).rear = (*Q).queuesize = 0;
 }
 
 void ClearQueue(SqQueue2 *Q)
 {
 	//��Q��Ϊ�ն���
	(*Q).front = (*Q).rear = 0; 
 }
 
 Status QueueEmpty(SqQueue2 Q)
 {
 	//������QΪ�ն��У��򷵻�TRUE�����򷵻� FALSE
 	if (Q.front == Q.rear)//���пյı�־ 
 	{
 		return TRUE; 
    } 
    else
    {
    	return FALSE;
    }
 }
 
 Status GetHead(SqQueue2 Q, QElemType *e)
 {
 	//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	if (Q.front == Q.rear)//����
	{
		return ERROR; 
	} 
	*e = Q.base[Q.front];
	
	return OK;	
 }
 
 int QueueLength(SqQueue2 Q)
 {
 	//����Q��Ԫ�ظ����������еĳ���
	return (Q.rear-Q.front); 
 }
 
 void EnQueue(SqQueue2 *Q, QElemType e)
 {
 	//����Ԫ��eΪQ���µĶ�βԪ��
	if ((*Q).rear == (*Q).queuesize)
	{
		//�����������Ӵ洢��Ԫ
		(*Q).base = (QElemType *)realloc((*Q).base, 
		                                 ( (*Q).queuesize + QUEUE_INCREMENT) * sizeof(QElemType) );
		if (! (*Q).base)//���ӵ�Ԫʧ�� 
		{
			exit(ERROR);
		}//if								  
	} //if
	
	(*Q).base[(*Q).rear++] = e;
 }
 
 Status DeQueue(SqQueue2 *Q, QElemType *e)
 {
 	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
	if ((*Q).front == (*Q).rear)//�ն���
	{
		return ERROR; 
	} 
	*e = (*Q).base[(*Q).front++];
	
	return OK;
 }
 
 void QueueTraverse(SqQueue2 Q, void(*vi)(QElemType))
 {
 	//�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()
	int i = Q.front;
	while (i != Q.rear)
	{
		vi(Q.base[i++]);
	} 
	printf("\n");	
 }
 
 void print(QElemType i)
 {
 	printf("%d ", i);
 }
 
 
 