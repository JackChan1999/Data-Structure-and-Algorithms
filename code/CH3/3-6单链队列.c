 //�õ�����Ļ�������ʵ�������� 
 
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
 } QNode, *QueuePtr;
 
 typedef struct 
 {
 	QueuePtr front, rear;//��ͷ����βָ��
 }LinkQueue; 
 typedef QElemType ElemType;
 #define LinkList QueuePtr  //���嵥�������������Ӧ�������е�������ͬ
 #define LNode QNode
 
 void InitList(LinkList *L);
 void DestroyList(LinkList *L);
 void ClearList(LinkList L);
 Status ListEmpty(LinkList L);
 int ListLength(LinkList L);
 Status GetElem(LinkList L, int i, ElemType *e);
 int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
 Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
 Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
 Status ListInsert(LinkList L, int i, ElemType e);
 Status ListDelete(LinkList L, int i, ElemType *e);
 void ListTraverse(LinkList L, void (*vi)(ELemType));
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
   	
   return 0;
 }
 
 
 void InitList(LinkList *L)
{
	/*�������������һ���յ����Ա�*/ 
	*L = (LinkList)malloc(sizeof(struct LNode));/*����ͷ��㣬��ʹLָ���ͷ���*/ 
	
	if (!*L)
	{
		exit(OVERFLOW);/*�洢����ʧ��*/ 
	}
	(*L)->next = NULL;/*ָ����Ϊ��*/	
}

void DestroyList(LinkList *L)
{
	/*��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L*/
	LinkList q;
	
	while (*L)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}
}

void ClearList(LinkList L)/*���ı�L*/
{
	LinkList p, q;
	
	p = L->next;/*pָ���һ���ڵ�*/
	while (p)/*û��β��*/
	{
		q = p->next;
		free(p);
		p = q;
	}	
	
	L->next = NULL;/*ͷ���ָ����Ϊ��*/
}

Status ListEmpty(LinkList L)
{
	/*��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE*/
	if (L->next)/*�ǿ�*/
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int ListLength(LinkList L)
{
	/*��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ���*/
	int i = 0;
	LinkList p = L->next;/*pָ���һ�����*/
	
	while (p)/*û����β*/
	{
		i++;
		p = p->next;
	}
	return i; 	
}

Status GetElem(LinkList L, int i, ElemType *e)
{
	/*LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR*/
	int j = 1;/*jΪ������*/
	LinkList p = L->next;/*pָ���һ�����*/
	
	while (p && j<i)/*˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��*/
	{
		p = p->next;
		j++;
	}
	
	if (!p || j>i)/*��i��Ԫ�ز�����*/
	{
		return ERROR;
	}
	
	*e = p->data;/*ȡ��i��Ԫ��*/
	
	return OK; 	
}

int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{
	/*��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����������Ϊ1������Ϊ0��*/
	/*�������������L�е�1����e�����ϵcompare����������Ԫ�ص�λ��*/
	/*������������Ԫ�ز����ڣ��򷵻�ֵΪ0*/
	
	int i = 0;
	LinkList p = L->next;
	
	while (p)
	{
		i++;
		if ( compare(p->data, e) )/*�ҵ�������Ԫ��*/
		{
			return i;
		}
		p = p->next;  
	}
	
	return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	/*��ʼ���������Ա�L�Ѵ���*/
	/*�����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ����*/
	/*           ����OK���������ʧ�ܣ�pre_e�޶��壬����INFEASIBLE*/
	LinkList q, p = L->next;/*pָ���һ�����*/
	
	while (p->next)/*p��ָ����к��*/ 
	{
		q = p->next;/*qΪp�ĺ��*/
		
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;/*p�����*/
	}
	return INFEASIBLE; 	 
}

Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	/*��ʼ���������Ա�L�Ѵ���*/
	/*�����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣�*/
	/*          ����OK���������ʧ�ܣ�next_e�޶��壬����INFEASIBLE*/
	LinkList p = L->next;/*pָ���һ�����*/
	
	while (p->next)/*p��ָ����к��*/
	{
		if (p->data == cur_e)
		{
			*next_e = p->next->data;
			return OK;
		}
		p = p->next;
	} 
	
	return INFEASIBLE;
}

Status ListInsert(LinkList L, int i, ElemType e)/*���ı�L*/
{
	/*�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e*/
	int j = 0;
	LinkList p = L, s;
	
	while ( p && j<(i-1) )/*Ѱ�ҵ�i-1�����*/ 
	{
		p = p->next;
		j++;
	}
	
	if ( !p || j>(i-1) )/*iС��1���ߴ��ڱ�*/
	{
		return ERROR; 
	} 
	s = (LinkList)malloc( sizeof(struct LNode) );/*�����½��*/
	s->data = e;/*����L��*/
	s->next = p->next;
	p->next = s;
	
	return OK; 	 
}

Status ListDelete(LinkList L, int i, ElemType *e)/*���ı�L*/
{
	/*�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ*/
	int j = 0;
	LinkList p = L, q;
	
	while ( p->next && j>(i-1) )/*Ѱ�ҵ�i����㣬����pָ����ǰ��*/
	{
		p = p->next;
		j++;		 
	}
	
	if ( (!p->next) || j>(i-1) )/*ɾ��λ�ò�����*/
	{
		return ERROR;
	} 
	
	q = p->next;/*ɾ�����ͷŽ��*/
	p->next = q->next;
	*e = q->data;
	free(q); 
	
	return OK;
}

void ListTraverse(LinkList L, void (*vi)(ELemType))
{
	/*vi���β�����ΪElemType*/
	/*��ʼ���������Ա�L�Ѵ��ڡ�������������ζ�L��ÿ������Ԫ�ص��ú���vi()*/
	
	LinkList p = L->next;
	
	while (p)
	{
		vi(p->data);
		p = p->next;
	}
	
	printf("\n");
}
 
 void InitQueue(LinkQueue *Q)
 {
 	//����һ���ն���Q
	InitList(&(*Q).front);//���õ�����Ļ������� 
	(*Q).rear = (*Q).front; 
 } 
 
 void DestroyQueue(LinkQueue *Q)
 {
 	//���ٶ���Q�����ۿշ���ɣ�
	DestroyList(&(*Q).front);
	(*Q).rear = (*Q).front; 	
 }
 
 void ClearQueue(LinkQueue *Q)
 {
 	//��Q��Ϊ�ն��� 
 	ClearList((*Q).front);
    (*Q).rear = (*Q).front; 
 }
 
 Status QueueEmpty(LinkQueue Q)
 {
 	//��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE
	return ListEmpty(Q.front); 
 }  
 
 int QueueLength(LinkQueue Q)
 {
 	//����еĳ���
	return ListLength(Q.front); 
 }
 
 Status GetHead_Q(LinkQueue Q, QElemType *e)
 {
 	//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR
	return GetElem(Q.front, 1, e); 
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
 	//�����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
	if ( ((*Q).front->next) == (*Q).rear )//���н���1��Ԫ�� ��ɾ����Ҳ�Ƕ�βԪ�أ�
	{
		(*Q).rear = (*Q).front;//���βָ��ָ��ͷ��� 
	}
	
	return ListDelete((*Q).front, 1, e); 
 }
 
 void QueueTraverse(LinkQueue Q, void(*vi)(QElemType))
 {
 	//�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()
	ListTraverse(Q.front, vi); 
 }
 
 void print(QElemType i)
 {
   printf("%d ",i);
 }
 
  
 
 
  

 
 