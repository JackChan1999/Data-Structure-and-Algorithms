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
 
 #define QUEUE_INIT_SIZE 10//���д洢�ռ�ĳ�ʼ������
 #define QUEUE_INCREMENT 2
 typedef struct 
 {
 	QElemType *base;//��ʼ���Ķ�̬����洢�ռ�
 	int front;//ͷָ�룬�����в��գ�ָ�����ͷԪ��
	int rear; //βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��
	int queuesize;//��ǰ����Ĵ洢����(��sizeof��QElemType��Ϊ��λ)	 
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
   for(i=1;i<=3;i++)
     DeQueue(&Q,&d);
   printf("�ɶ�ͷɾ��3��Ԫ�أ����ɾ����Ԫ��Ϊ%d\n",d);
   printf("���ڶ����е�Ԫ��Ϊ: \n");
   QueueTraverse(Q,print);
   j=GetHead(Q,&d);
   if(j)
     printf("��ͷԪ��Ϊ: %d\n",d);
   else
     printf("�޶�ͷԪ��(�ն���)\n");
   for(i=1;i<=5;i++)
     EnQueue(&Q,i);
   printf("�������β����1��5�����ڶ����е�Ԫ��Ϊ: \n");
   QueueTraverse(Q,print);
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
	return (Q.rear-Q.front+Q.queuesize) % Q.queuesize; 
 }
 
 void EnQueue(SqQueue2 *Q, QElemType e)
 {
 	//����Ԫ��eΪQ���µĶ�βԪ��
	int i;
	
	if ( ((*Q).rear+1)%(*Q).queuesize == (*Q).front )
	{
		//�����������Ӵ洢��Ԫ
		(*Q).base = (QElemType *)realloc((*Q).base, ((*Q).queuesize+QUEUE_INCREMENT)
                                                  * sizeof(QElemType) );
		if (! (*Q).base)//���ӵ�Ԫʧ��
		{
			exit(ERROR); 
		}
		if ((*Q).front > (*Q).rear)//�γ�ѭ��
		{
			for (i=(*Q).queuesize-1; i>=(*Q).front; i--)
			{
				(*Q).base[i+QUEUE_INCREMENT] = (*Q).base[i];//�ƶ��߶�Ԫ�ص��µĸ߶� 
			} //for
			(*Q).front += QUEUE_INCREMENT;//�ƶ���ͷָ�� 
		}//if-in
	    (*Q).queuesize += QUEUE_INCREMENT;//���Ӷ��г��� 
	}//if-out
	(*Q).base[(*Q).rear] = e;//��e�����β
	(*Q).rear = ++(*Q).rear%(*Q).queuesize;//�ƶ���βָ��   
 }
 
 Status DeQueue(SqQueue2 *Q, QElemType *e)
 {
 	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK��
	//���򷵻�ERROR
	if ((*Q).front == (*Q).rear)//���п�
	{
		return ERROR; 
	} 
	*e = (*Q).base[(*Q).front];//��e���ض���ͷԪ��
	(*Q).front = ++(*Q).front % (*Q).queuesize;//�ƶ���ͷָ��
	
	return OK; 
 } 
 
 void QueueTraverse(SqQueue2 Q, void(*vi)(QElemType))
 {
 	//�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()
	int i = Q.front;//iָ���ͷ
	
	while (i != Q.rear)//û����β 
	{
		vi(Q.base[i]);//���ú���vi()
		i = ++i % Q.queuesize;//����ƶ�iָ�� 
	}
	
	printf("\n"); 
 }
 
 void print(QElemType i)
 {
 	printf("%d ", i);
 }
 
 
 
 
 

 
 