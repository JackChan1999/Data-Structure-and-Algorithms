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
 typedef int SElemType;//����ջԪ�ص�����
 typedef SElemType ElemType;//ջ������ͺ�����������һ��
  
  
 typedef struct LNode 
 {
 	ElemType data;
 	struct LNode *next;
 };
 
 typedef struct LNode *LinkList;//��һ�ֶ��巽��
 typedef LinkList LinkStack;//LinkStack��ָ��ջ����ָ������
 #define InitStack InitList // InitStack()��InitList()������ͬ
 #define DestroyStack DestroyList //DestroyStack()��DestroyList()������ͬ
 #define ClearStack ClearList
 #define StackEmpty ListEmpty
 #define StackLength ListLength
 #define DestroyList ClearList
 
 void InitList(LinkList *L);
 void ClearList(LinkList *L);
 Status ListEmpty(LinkList L);
 int ListLength(LinkList L);
 Status GetElem(LinkList L, int i, ElemType *e);
 int LocateElem(LinkList L, ElemType e, Status(*coompare)(ElemType, ElemType));
 Status ListInsert(LinkList *L, int i, ElemType e);
 Status ListDelete(LinkList *L, int i, ElemType *e);
 void ListTraverse(LinkList L, void(*vi)(ElemType));
 Status GetTop(LinkStack S, SElemType *e);
 Status Push(LinkStack *S, SElemType e);
 Status Pop(LinkStack *S, SElemType *e);
 void StackTraverse(LinkStack S, void(*visit)(SElemType));
 void print(SElemType c);
 
 int main()
 {
   int j;
   LinkStack s;
   SElemType e;
   InitStack(&s); /* ��ʼ��ջs */
   for(j=1;j<=5;j++) /* ��2,4,6,8,10��ջ */
     Push(&s,2*j);
   printf("ջ�е�Ԫ�ش�ջ�׵�ջ������Ϊ: ");
   StackTraverse(s,print);
   Pop(&s,&e);
   printf("������ջ��Ԫ��Ϊ%d\n",e);
   printf("ջ�շ�: %d(1:�� 0:��)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("��ǰջ��Ԫ��Ϊ%d��ջ�ĳ���Ϊ%d\n",e,StackLength(s));
   ClearStack(&s);
   printf("���ջ��ջ�շ�: %d(1:�� 0:��)��ջ�ĳ���Ϊ%d\n",StackEmpty(s),StackLength(s));
   DestroyStack(&s);
 	
 	return 0;
 }
 
 
 void InitList(LinkList *L)
 {
 	//�������������һ���յ����Ա�L
	*L = NULL;//ָ��Ϊ�� 
 } 
 
 void ClearList(LinkList *L)
 {
 	//��ʼ���������Ա�L�Ѵ��ڡ���������� �� L����Ϊ�ձ� 
 	LinkList p;
	
	while (*L)//L��Ϊ��
	{
		p = *L;//pָ����Ԫ���
		*L = (*L)->next;//Lָ���2�����(����Ԫ���)
		free(p);//�ͷ���Ԫ��� 
	} 
 } 
 
 Status ListEmpty(LinkList L)
 {
 	//��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻� FALSE
	if (L)
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
 	//��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ���
	int i = 0;
	LinkList p = L;
	
	while (p)//pָ����(û����β)
	{
		p = p->next;//pָ����һ����� 
		i++; 
	} 
	
	return i; 
 }
 
 Status GetElem(LinkList L, int i, ElemType *e)
 {
 	//LΪ����ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK��
	//���򷵻�ERROR
	int j = 1;
	LinkList p = L;
	
	if (i < 1)//iֵ���Ϸ� 
	{
		return ERROR; 
	} 
	while ( (j<i) && p )//û����i��Ԫ�أ�Ҳû����β
	{
		j++;
		p = p->next; 
	} 
	if (j == i)//���ڵ�i��Ԫ��
	{
		*e = p->data;
		return OK; 
	} 
	else
	{
		return ERROR; 
	}	 
 }
 
 int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
 {
 	//��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����������Ϊ1������Ϊ0��
	//�������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ��
	//�������� ����Ԫ�ز����ڣ��򷵻�ֵΪ0
	int i = 0;
	LinkList p = L;
	
	while (p)
	{
		i++;
		if (compare(p->data, e))//�ҵ�����������Ԫ��
		{
			return i; 
		} 
		p = p->next;
	} 
	
	return 0;
 }
 
 Status ListInsert(LinkList *L, int i, ElemType e)
 {
 	//�ڲ���ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
    int j = 1;
	LinkList p = *L, s;
	
	if (i < 1)//iֵ���Ϸ�
	{
		return ERROR; 
	}	 
	s = (LinkList)malloc(sizeof(struct LNode));//�����½ڵ�
	s->data = e;//��s��data��ֵ
	if (i == 1)//���ڱ�ͷ 
	{
		s->next = *L;
		*L = s;//�ı�L 
	} 
	else
	{
		//���ڱ�����ദ
		while ( p && (j < i-1) )//Ѱ�ҵ�i-1�����
		{
			p = p->next; 
			j++;
		} 
		
		if (! p)//i���ڱ�+1
		{
			return ERROR;
		} 
		s->next = p->next;
		p->next = s;	
	}//else
	
	return OK; 
 }
 
 Status ListDelete(LinkList *L, int i, ElemType *e)
 {
 	//�ڲ���ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�������e������ֵ
	int j = 1;
	LinkList p = *L, q;
	
	if (1 == i)//ɾ����1�����
	{
		*L = p->next;//L�ɵڶ�����㿪ʼ
		*e = p->data;
		free(p);//ɾ�����ͷŵ�1����� 
	} 
	else
	{
		while ( (p->next) && (j < i-1))//Ѱ�ҵ�i����㣬����pָ����ǰ��
		{
			p = p->next;
			j++; 
		} 
		if ( (!p->next) || (j > i-1) )//ɾ��λ�ò����� 
		{
			return ERROR; 
		} 
		q = p->next;//ɾ�����ͷŽ��
		p->next = q->next;
		*e = q->data;
		free(q); 
	} //else
	
	return OK;	
 }
 
 void ListTraverse(LinkList L, void(*vi)(ElemType))
 {
 	//��ʼ���������Ա�L�Ѵ��ڡ�������������� ��L��ÿ������Ԫ�ص��ú��� vi()
	LinkList p = L;
	
	while (p)
	{
		vi(p->data);
		p = p->next;
	} 
	printf("\n");
 }
 
 Status GetTop(LinkStack S, SElemType *e)
 {
 	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
	return GetElem(S, 1, e); 
 }
 
 Status Push(LinkStack *S, SElemType e)
 {
 	//����Ԫ��eΪ�µ�ջ��Ԫ�� 
 	return ListInsert(S, 1, e); 
 }
 
 Status Pop(LinkStack *S, SElemType *e)
 {
 	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	return ListDelete(S, 1, e); 
 }
 
 void StackTraverse(LinkStack S, void(*visit)(SElemType))
 {
 	//��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()
	LinkStack temp, p = S;//pָ��ջ��Ԫ��
	
	InitStack(&temp);//��ʼ����ʱջtemp
	
	while (p)
	{
		Push(&temp, p->data);//��Sջ����ջ�ף����ν�ջԪ����ջ��tempջ
		p = p->next; 
	} 
	
	ListTraverse(temp, visit);//����temp���Ա� 
 }
 
 void print(SElemType c)
 {
 	printf("%d ", c);
 } 
 
 
 
 
 
 
 
  
  