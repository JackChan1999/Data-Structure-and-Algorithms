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
 typedef struct QNode
 {
 	QElemType data;
 	struct QNode *next;
 }QNode, * QueuePtr;
 
 typedef struct 
 {
 	QueuePtr front, rear;//��ͷ����βָ�� 
 }LinkQueue; 
 
 void InitQueue(LinkQueue *Q);
 void DestroyQueue(LinkQueue *Q);
 void ClearQueue(LinkQueue *Q);
 Status QueueEmpty(LinkQueue Q);
 int QueueLength(LinkQueue Q);
 Status GetHead_Q(LinkQueue Q, QElemType *e);
 void EnQueue(LinkQueue *Q, QElemType e);
 Status DeQueue(LinkQueue *Q, QElemType *e);
 void QueueTraverse(LinkQueue Q, void(*vi)(QElemType));
 void print(QElemType i);
 
 int main()
 {
   int i;
   QElemType d;
   LinkQueue q;
   InitQueue(&q);
   printf("�ɹ��ع�����һ���ն���!\n");
   printf("�Ƿ�ն��У�%d(1:�� 0:��)  ",QueueEmpty(q));
   printf("���еĳ���Ϊ%d\n",QueueLength(q));
   EnQueue(&q,-5);
   EnQueue(&q,5);
   EnQueue(&q,10);
   printf("����3��Ԫ��(-5,5,10)��,���еĳ���Ϊ%d\n",QueueLength(q));
   printf("�Ƿ�ն��У�%d(1:�� 0:��)  ",QueueEmpty(q));
   printf("���е�Ԫ������Ϊ��");
   QueueTraverse(q,print);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("��ͷԪ���ǣ�%d\n",d);
   DeQueue(&q,&d);
   printf("ɾ���˶�ͷԪ��%d\n",d);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("�µĶ�ͷԪ���ǣ�%d\n",d);
   ClearQueue(&q);
   printf("��ն��к�,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
   DestroyQueue(&q);
   printf("���ٶ��к�,q.front=%u q.rear=%u\n",q.front, q.rear);
 	
 }
 
 void InitQueue(LinkQueue *Q)
 {
 	//����һ���ն���Q
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	
	if (! (*Q).front)
	{
		exit(OVERFLOW);
	}  
	
	(*Q).front->next = NULL;
 } 
 
 void DestroyQueue(LinkQueue *Q)
 {
 	//���ٶ���Q(���ۿշ����)
	while ( (*Q).front )
	{
		(*Q).rear = (*Q).front->next;
		free( (*Q).front );
		(*Q).front = (*Q).rear;
	}//while 
 } 
 
 void ClearQueue(LinkQueue *Q)
 {
 	//��Q��Ϊ�ն���
	QueuePtr p, q;
	
	(*Q).rear = (*Q).front;
	p = (*Q).front->next;
	(*Q).front->next = NULL;
	
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	} //while
 }
 
 Status QueueEmpty(LinkQueue Q)
 {
 	//��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	 if (Q.front->next == NULL)
	 {
	 	return TRUE;
 	 }  
 	 else
 	 {
 	 	return FALSE;
 	 }
 }
 
 int QueueLength(LinkQueue Q)
 {
 	//����г���
	 int i = 0;
	 QueuePtr p;
	 
	 p = Q.front;
	 
	 while (Q.rear != p)
	 {
	 	i++;
	 	p = p->next;
     } 
     
     return i;
 }
 
 Status GetHead_Q(LinkQueue Q, QElemType *e)//��������
 {
 	//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	QueuePtr p;
	
	if (Q.front == Q.rear)
	{
		return ERROR;
	}
	
	p = Q.front->next;
	*e = p->data;
	
	return OK;
 } 
 
 void EnQueue(LinkQueue *Q, QElemType e)
 {
 	//����Ԫ��eΪQ���µĶ�βԪ��
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (! p)//�洢����ʧ��
	{
		exit(OVERFLOW); 
	} 
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
 }
 
 Status DeQueue(LinkQueue *Q, QElemType *e)
 {
 	//���в�Ϊ�գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
	QueuePtr p;
	
	if ((*Q).front == (*Q).rear)
	{
		return ERROR;
	} 
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p)
	{
		(*Q).rear == (*Q).front;
	}
	free(p);
	
	return OK;	
 }
 
 void QueueTraverse(LinkQueue Q, void(*vi)(QElemType))
 {
 	//�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi����
	QueuePtr p;
	
	p = Q.front->next;
	
	while ( p )
	{
		vi(p->data);
		p = p->next;
	} 
	printf("\n");
 }
 
 void print(QElemType i)
 {
 	printf("%d ", i);
 }

 
 