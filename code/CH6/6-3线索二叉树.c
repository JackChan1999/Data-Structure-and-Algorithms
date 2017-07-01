#define CHAR 1  //�ַ���
//#define CHAR 0  //���ͣ�����ѡһ��
#if CHAR 
  typedef char TElemType;
  TElemType Nil = ' ';//�ַ����Կո��Ϊ��
  #define form "%c"//��������ĸ�ʽΪ%c
#else
  typedef int TElemType;
  TElemType Nil = 0;//������0Ϊ�� 
  #define form "%d"//��������ĸ�ʽΪ%d
#endif

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
 
 typedef enum{Link, Thread}PointerTag;//Link(0):ָ�룬Thread(1):����
 typedef struct BiThrNode
 {
 	TElemType data;
 	struct BiThrNode *lchild, *rchild;//���Һ���ָ��
	PointerTag LTag, RTag;//���ұ�־ 
 }BiThrNode, *BiThrTree;
 
 BiThrTree pre;//ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ�� 
 
void CreateBiThrTree(BiThrTree *T);
void InThreading(BiThrTree p);
void InOrderThreading(BiThrTree *Thrt, BiThrTree T);
void InOrderTraverse_Thr(BiThrTree T, void(*Visit)(TElemType));
void PreThreading(BiThrTree p);
void PreOrderThreading(BiThrTree *Thrt, BiThrTree T);
void PreOrderTraverse_Thr(BiThrTree T, void(*Visit)(TElemType));
void PostThreading(BiThrTree p);
void PostOrderThreading(BiThrTree *Thrt, BiThrTree T);
void DestroyBiTree(BiThrTree *T);
void DestroyBiThrTree(BiThrTree *Thrt);
void vi(TElemType c);
 
 int main()
 {
   BiThrTree H,T;
 #if CHAR
   printf("�밴�������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #else
   printf("�밴�������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   CreateBiThrTree(&T); /* ��������������� */
   InOrderThreading(&H,T); /* ����������Ĺ����У����������������� */
   printf("�������(���)����������:\n");
   InOrderTraverse_Thr(H,vi); /* �������(���)���������� */
   printf("\n");
   DestroyBiThrTree(&H); /* �������������� */
 #if CHAR
   printf("�밴�������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #else
   printf("�밴�������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   scanf("%*c"); /* �Ե��س��� */
   CreateBiThrTree(&T); /* ���������������T */
   PreOrderThreading(&H,T); /* ����������Ĺ����У����������������� */
   printf("�������(���)����������:\n");
   PreOrderTraverse_Thr(H,vi);
   DestroyBiThrTree(&H); /* �������������� */
 #if CHAR
   printf("\n�밴�������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
 #else
   printf("\n�밴�������������(��:1 2 0 0 0��ʾ1Ϊ�����,2Ϊ�������Ķ�����)\n");
 #endif
   scanf("%*c"); /* �Ե��س��� */
   CreateBiThrTree(&T); /* ���������������T */
   PostOrderThreading(&H,T); /* �ں�������Ĺ����У����������������� */
   DestroyBiThrTree(&H); /* �������������� */
 	
 	return 0;
 } 
 
 
 void CreateBiThrTree(BiThrTree *T)
 {
 	//���������������������н���ֵ����������������T��
    //0�����ͣ�/�ո��ַ��ͣ���ʾ�ս��
	TElemType ch;
	
	scanf(form, &ch);
	if (ch == Nil)
	{
		*T = NULL;
	} 
	else
	{
		*T = (BiThrTree)malloc(sizeof(BiThrNode));//���ɸ��ڵ�(����)
		if (!*T)
		{
			exit(OVERFLOW);
		} 
		(*T)->data = ch;//������㸳ֵ
		CreateBiThrTree(&(*T)->lchild);//�ݹ鹹��������
		if ((*T)->lchild)//������
		{
			(*T)->LTag = Link;//�����־��ֵ��ָ�룩 
		} 
		CreateBiThrTree(&(*T)->rchild);//�ݹ鹹�������� 
		if ((*T)->rchild)//���Һ���
		{
			(*T)->RTag = Link;//���ұ�־��ֵ(ָ��) 
		} 	
	}//else 
 } 
 
 void InThreading(BiThrTree p)
 {
 	//ͨ���������������������������������preָ�����һ����㡣
	if (p)//��������������
	{
		InThreading(p->lchild);//�ݹ�������������
		if (! p->lchild)//û������
		{
			p->LTag = Thread;//���־Ϊ����(ǰ��)
			p->lchild = pre;//����ָ��ָ��ǰ�� 
		} 
		if (! pre->rchild)//ǰ��û���Һ���
		{
			pre->RTag = Thread;//ǰ�����ұ�־Ϊ��������̣�
			pre->rchild = p;//ǰ���Һ���ָ��ָ�����̣���ǰ���p�� 
		} 
		pre = p;//����preָ��p��ǰ�� 
		InThreading(p->rchild);//�ݹ������������� 
	} 
 } 
 
 void InOrderThreading(BiThrTree *Thrt, BiThrTree T)
 {
 	//�������������T,������������������Thrtָ��ͷ��㡣
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (! *Thrt)//����ͷ��㲻�ɹ�
	{
		exit(OVERFLOW); 
	}
	(*Thrt)->LTag = Link;//��ͷ��㣬���־Ϊָ��
	(*Thrt)->RTag = Thread;//�ұ�־Ϊ����
	(*Thrt)->rchild = *Thrt;//��ָ���ָ 
	if (!T)//��������Ϊ�գ�����ָ���ָ
	{
		(*Thrt)->lchild = *Thrt;
	} 
	else
	{
		(*Thrt)->lchild = T;//ͷ������ָ��ָ����ڵ�
		pre = *Thrt;//pre��ǰ�����ĳ�ֵָ��ͷ���
		InThreading(T);//�����������������������preָ��������������һ�����
		pre->rchild = *Thrt;//���һ��������ָ��ָ��ͷ���
		pre->RTag = Thread;//���һ�������ұ�־Ϊ����
		(*Thrt)->rchild = pre;//ͷ������ָ��ָ��������������һ����� 	
	}
 } 
 
 void InOrderTraverse_Thr(BiThrTree T, void(*Visit)(TElemType))
 {
 	//�����������������T(ͷ���)�ķǵݹ��㷨��
	BiThrTree p;
	
	p = T->lchild;//pָ����ڵ�
	while (p != T)
	{
		//�������������ʱ��p == T
		while (p->LTag == Link)//�ɸ��ڵ�һֱ�ҵ���������������
		{
			p = p->lchild; 
		} 
		Visit(p->data);//���ʴ˽��
		while (p->RTag==Thread && p->rchild!=T)//p->rchild����������̣����Ҳ��Ǳ��������һ�����
		{
			p = p->rchild;
			Visit(p->data);//���ʺ�̽�� 
		} 
		p = p->rchild;//��p->rchild�������������Һ��ӣ���pָ���Һ��ӣ�����ѭ�� 
		              //�����������������ĵ�1�����	 
	} 
 } 
 
 void PreThreading(BiThrTree p)
 {
 	//PreOrderThreading()���õĵݹ麯��
	if (! pre->rchild)//p��ǰ��û���Һ���
	{
		pre->rchild = p;//pǰ���ĺ��ָ��p
		pre->RTag = Thread;//pre���Һ���Ϊ���� 
	} 
	if (! p->lchild)//pû������
	{
		p->LTag = Thread;//p������Ϊ����
		p->lchild = pre;//p������ָ��ǰ�� 
	} 
	pre = p;//�ƶ�ǰ��
	if (p->LTag == Link)//p������
	{
		PreThreading(p->lchild);//��p�����ӵݹ����preThreading() 
	} 
	if (p->RTag == Link)//p���Һ���
	{
		PreThreading(p->rchild);//��p���Һ��ӵݹ����preThreading() 
	} 
 }  
 
 void PreOrderThreading(BiThrTree *Thrt, BiThrTree T)
 {
 	//����������������T��ͷ������ָ��ָ��������������1�����
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	
	if (! *Thrt)//����ͷ���
	{
		exit(OVERFLOW); 
	} 
	(*Thrt)->LTag = Link;//ͷ������ָ��Ϊ����
	(*Thrt)->RTag = Thread;//ͷ������ָ��Ϊ����
	(*Thrt)->rchild = *Thrt;//ͷ������ָ��ָ������ 
	
	if (! T)//����
	{
		(*Thrt)->lchild = *Thrt;//ͷ������ָ��Ҳָ������ 
	} 
	else
	{
		//�ǿ���
		(*Thrt)->lchild = T;//ͷ������ָ��ָ������
		pre = *Thrt;//ǰ��Ϊͷ��� 
		PreThreading(T);//��ͷ��㿪ʼ����ݹ�������
		pre->rchild = *Thrt;//���һ�����ĺ��ָ��ͷ���
		pre->RTag = Thread;
		(*Thrt)->rchild = pre;//ͷ���ĺ��ָ�����һ����� 	
	} //else 
 }
 
 void PreOrderTraverse_Thr(BiThrTree T, void(*Visit)(TElemType))
 {
 	//�����������������T(ͷ���)�ķǵݹ��㷨
	BiThrTree p = T->lchild;//pָ������
	
	while (p != T)//pûָ��ͷ���(���������1�����ĺ��ָ��ͷ���)
	{
		Visit(p->data);//���ʸ����
		if (p->LTag == Link)//p������
		{
			p = p->lchild;//pָ������(���) 
		} 
		else
		{
			p = p->rchild;//pָ���Һ��ӻ��� 
		} 
	} 
 }
 
 void PostThreading(BiThrTree p)
 {
 	//PostOrderThreading()���õĵݹ麯��
	if (p)//p����
	{
		PostThreading(p->lchild);//��p�����ӵݹ����PostThreading()
		PostThreading(p->rchild);//��p���Һ��ӵݹ����PostThreading()
	    
	    if (! p->lchild)//pû������
		{
			p->LTag = Thread;//p������Ϊ����
			p->lchild = pre;//p������ָ��ǰ�� 
		} 
		if (! pre->rchild)//p��ǰ��û���Һ���
		{
			pre->RTag = Thread;//pǰ�����Һ���Ϊ����
			pre->rchild = p;//pǰ���ĺ��ָ��p 
		} 
		pre = p;//�ƶ�ǰ�� 
	} 	
 } 
 
 void PostOrderThreading(BiThrTree *Thrt, BiThrTree T)
 {
 	//����ݹ�������������
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	
	if (! *Thrt)//����ͷ���
	{
		exit(OVERFLOW); 
	} 
	(*Thrt)->LTag = Link;//ͷ������ָ��Ϊ����
	(*Thrt)->RTag = Thread;//ͷ������ָ��Ϊ����
	
	if (! T)//����
	{
		(*Thrt)->lchild = (*Thrt)->rchild = *Thrt;//ͷָ�������ָ��ָ������ 
	} 
	else
	{
		//�ǿ���
		(*Thrt)->lchild = (*Thrt)->rchild = T;//ͷ��������ָ��ָ������(���һ�����)
		pre = *Thrt;//ǰ��Ϊͷ���
		PostThreading(T);//��ͷ��㿪ʼ����ݹ�������
		if (pre->RTag != Link)//���һ�����û���Һ���
		{
			pre->rchild = *Thrt;//���һ�����ĺ��ָ��ͷ���
			pre->RTag = Thread; 
		} 
	}//else 
 } 
 
 void DestroyBiTree(BiThrTree *T)
 {
 	//DestroyBiThrTree���õĵݹ麯����Tָ������
	if (*T)//�ǿ���
	{
		if ((*T)->LTag == 0)//������
		{
			DestroyBiTree(&(*T)->lchild);//������������ 
		} 
		if ((*T)->RTag == 0)//���Һ���
		{
			DestroyBiTree(&(*T)->rchild);//�����Һ������� 
		} 
		free(*T);//�ͷŸ����
		T = NULL;//��ָ�븳0 
	} 
 }
 
 void DestroyBiThrTree(BiThrTree *Thrt)
 {
 	//��ʼ����������������Thrt���ڡ������������������������Thrt
	if (*Thrt)//ͷ������
	{
		if ((*Thrt)->lchild)//�������� 
		{
			DestroyBiTree(&(*Thrt)->lchild);//�ݹ�����ͷ���lchild��ָ������ 
		} 
		free(*Thrt);//�ͷ�ͷ���
		*Thrt = NULL;//����������Thrtָ�븳0 
	} 
 } 
 
 void vi(TElemType c)
 {
   printf(form" ",c);
 }
 
 
 
 
 
 
 
 
   
 