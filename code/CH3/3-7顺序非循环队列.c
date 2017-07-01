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
 #define QUEUE_INCREMENT 2  //���д洢�ռ�ķ�������
 
 typedef struct 
 {
 	QElemType *base;//��ʼ���Ķ�̬����洢�ռ�
	int rear;//βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�� 
	int queuesize;//��ǰ����Ĵ洢��������sizeof(QElemType)Ϊ��λ�� 
 }SqQueue1;
 
 void InitQueue(SqQueue1 *Q);
 void DestroyQueue(SqQueue1 *Q);
 void ClearQueue(SqQueue1 *Q);
 Status QueueEmpty(SqQueue1 Q);
 int QueueLength(SqQueue1 Q);
 Status GetHead(SqQueue1 Q, QElemType *e);
 void EnQueue(SqQueue1 *Q, QElemType e);
 Status DeQueue(SqQueue1 *Q, QElemType *e);
 void QueueTraverse(SqQueue1 Q, void(*vi)(QElemType));
 void print(QElemType i);
 
 int main()
 {
   Status j;
   int i,k=5;
   QElemType d;
   SqQueue1 Q;
   InitQueue(&Q);
   printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   for(i=1;i<=k;i++)
     EnQueue(&Q,i); /* �������k��Ԫ�� */
   printf("�������%d��Ԫ�غ󣬶����е�Ԫ��Ϊ: ",k);
   QueueTraverse(Q,print);
   printf("���г���Ϊ%d�����пշ�%u(1:�� 0:��)\n",QueueLength(Q),QueueEmpty(Q));
   DeQueue(&Q,&d);
   printf("����һ��Ԫ�أ���ֵ��%d\n",d);
   j=GetHead(Q,&d);
   if(j)
     printf("���ڶ�ͷԪ����%d\n",d);
   ClearQueue(&Q);
   printf("��ն��к�, ���пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   DestroyQueue(&Q);
 	
 	return 0;
 }
 
 void InitQueue(SqQueue1 *Q)
 {
 	//����һ���ն���Q 
 	(*Q).base = (QElemType*)malloc(QUEUE_INIT_SIZE * sizeof(QElemType));
 	if (! (*Q).base)
 	{
 		exit(ERROR);//�洢����ʧ�� 
    }
    (*Q).rear = 0;//�ն��У�βָ��Ϊ0
	(*Q).queuesize = QUEUE_INIT_SIZE;//��ʼ�洢���� 
 } 
 
 void DestroyQueue(SqQueue1 *Q)
 {
 	//���ٶ���Q,Q������
	free((*Q).base);//�ͷŴ洢�ռ�
	(*Q).base = NULL;
	(*Q).rear = (*Q).queuesize = 0; 
 } 
 
 void ClearQueue(SqQueue1 *Q)
 {
 	//��Q��Ϊ�ն���
	(*Q).rear = 0; 
 }
 
 Status QueueEmpty(SqQueue1 Q)
 {
 	//������QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	if (Q.rear == 0)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}	
 }
 
 int QueueLength(SqQueue1 Q)
 {
 	//����Q��Ԫ�ظ����������еĳ���
	return Q.rear; 
 }
 
 Status GetHead(SqQueue1 Q, QElemType *e)
 {
 	//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	if (Q.rear)
	{
		*e = *Q.base;
		return OK; 
	} 
	else
	{
		return ERROR;
	}
 }
 
 void EnQueue(SqQueue1 *Q, QElemType e)
 {
 	//����Ԫ��eΪQ���µĶ�βԪ��
	if ((*Q).rear == (*Q).queuesize)//��ǰ�洢�ռ�����
	{
		//���ӷ���
		(*Q).base = (QElemType*)realloc((*Q).base, ( (*Q).queuesize + QUEUE_INCREMENT) * sizeof(QElemType));
		if (! (*Q).base)//����ʧ��
		{
			exit(ERROR); 
		} 
		(*Q).queuesize += QUEUE_INCREMENT;//���Ӵ洢���� 
	} 
	(*Q).base[(*Q).rear++] = e;//�����Ԫ�أ���βָ��+1 	 
 }
 
 Status DeQueue(SqQueue1 *Q, QElemType *e)
 {
 	//�����в��գ���ɾ��Q�Ķ�ͷԪ����e������ֵ��������OK�����򷵻�ERROR
	int i;
	
	if ( (*Q).rear )//���в���
	{
		*e = *(*Q).base;
		for (i=1; i<(*Q).rear; i++) 
		{
			(*Q).base[i-1] = (*Q).base[i];//����ǰ�ƶ���Ԫ�� 
		}
		(*Q).rear--;//βָ��ǰ��
		
		return OK; 
	} 
	else
	{
		return ERROR;
	}
 } 
 
 void QueueTraverse(SqQueue1 Q, void(*vi)(QElemType))
 {
 	//�Ӷ�ͷ����β���ζԶ��� Q��ÿ��Ԫ�� ���ú���vi()
 	int i;
 	
 	for (i=0; i<Q.rear; i++)
 	{
 		vi(Q.base[i]);	
    }
    printf("\n");
 }
 
 void print(QElemType i)
 {
 	printf("%d ", i);
 }
 
 