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
 
 #define MAX_NAME 3 /* �����ַ�������󳤶�+1 */
 typedef int InfoType; /* Ȩֵ���� */
 typedef char VertexType[MAX_NAME]; /* �ַ������� */
 #define MAX_VERTEX_NUM 20
 typedef enum{unvisited, visited} VisitIf;
 typedef struct EBox
 {
   VisitIf mark; /* ���ʱ�� */
   int ivex, jvex; /* �ñ����������������λ�� */
   struct EBox *ilink, *jlink; /* �ֱ�ָ�������������������һ���� */
   InfoType *info; /* �ñ���Ϣָ�룬��ָ��Ȩֵ��������Ϣ */
 }EBox;
 typedef struct
 {
   VertexType data;
   EBox *firstedge; /* ָ���һ�������ö���ı� */
 }VexBox;
 typedef struct
 {
   VexBox adjmulist[MAX_VERTEX_NUM];
   int vexnum, edgenum; /* ����ͼ�ĵ�ǰ�������ͱ��� */
 }AMLGraph;
 
 Boolean visite[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */
 void(*VisitFunc)(VertexType v);
 typedef int QElemType; /* ����Ԫ������ */
 typedef struct QNode
 {
 	QElemType data;
 	struct QNode *next;
 }QNode, * QueuePtr;
 typedef struct 
 {
 	QueuePtr front, rear;//��ͷ����βָ�� 
 }LinkQueue;
 
int LocateVex(AMLGraph G, VertexType u);
void CreateGraph(AMLGraph *G);
VertexType* GetVex(AMLGraph G, int v);
Status PutVex(AMLGraph *G, VertexType v, VertexType value);
int FirstAdjVex(AMLGraph G, VertexType v);
int NextAdjVex(AMLGraph G, VertexType v, VertexType w);
Status InsertVex(AMLGraph *G, VertexType v);
Status DeleteArc(AMLGraph *G, VertexType v, VertexType w);
Status DeleteVex(AMLGraph *G, VertexType v);
void DestroyGraph(AMLGraph *G);
Status InsertArc(AMLGraph *G, VertexType v, VertexType w);
void DFS(AMLGraph G, int v);
void DFSTraverse(AMLGraph G, void(*visit)(VertexType));
void InitQueue(LinkQueue *Q);
void DestroyQueue(LinkQueue *Q);
void ClearQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead_Q(LinkQueue Q, QElemType *e);//��������
void EnQueue(LinkQueue *Q, QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
void QueueTraverse(LinkQueue Q, void(*vi)(QElemType));
void BFSTraverse(AMLGraph G, void(*Visit)(VertexType));
void MarkUnvizited(AMLGraph G);
void Display(AMLGraph G);
void visit(VertexType v);

int main()
{
   int k,n;
   AMLGraph g;
   VertexType v1,v2;
   
   CreateGraph(&g);
   Display(g);
   printf("�޸Ķ����ֵ��������ԭֵ ��ֵ: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("�����¶��㣬�����붥���ֵ: ");
   scanf("%s",v1);
   InsertVex(&g,v1);
   printf("�������¶����йصıߣ����������: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("��������һ�����ֵ: ");
     scanf("%s",v2);
     InsertArc(&g,v1,v2);
   }
   Display(g);
   printf("ɾ��һ���ߣ��������ɾ���ߵ�������(�Կո���Ϊ���)��");
   scanf("%s%s",v1,v2);
   DeleteArc(&g,v1,v2);
   Display(g);
   printf("ɾ�����㼰��صıߣ������붥���ֵ: ");
   scanf("%s",v1);
   DeleteVex(&g,v1);
   Display(g);
   printf("������������Ľ��:\n");
   DFSTraverse(g,visit);
   printf("������������Ľ��:\n");
   BFSTraverse(g,visit);
   DestroyGraph(&g);
	
	return 0;
}
 
 
 int LocateVex(AMLGraph G, VertexType u)
 { /* ��ʼ����������ͼG���ڣ�u��G�ж�������ͬ���� */
   /* �����������G�д��ڶ���u���򷵻ظö���������ͼ��λ�ã����򷵻�-1 */
   int i;
   
   for(i=0; i<G.vexnum; ++i)
   { 
     if(strcmp(u,G.adjmulist[i].data) == 0)
     { 
       return i;
     } 
   } 
   return -1;
 }

 void CreateGraph(AMLGraph *G)
 { 
   /* �����ڽӶ��ر�洢�ṹ����������ͼG */
   int i, j, k, IncInfo;
   VertexType va, vb;
   EBox *p;
   
   printf("����������ͼ�Ķ�����,����,�Ƿ�Ϊ��Ȩͼ(��:1����:0): ");
   scanf("%d,%d,%d", &(*G).vexnum, &(*G).edgenum, &IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n", (*G).vexnum, MAX_NAME);
   for(i=0; i<(*G).vexnum; ++i) /* ���춥������ */
   {
     scanf("%s", (*G).adjmulist[i].data);
     (*G).adjmulist[i].firstedge = NULL;
   }
   
   printf("��˳������ÿ���ߵ������˵�(�Կո���Ϊ���):\n");
   
   for(k=0; k<(*G).edgenum; ++k) /* ����������� */
   {
     scanf("%s%s%*c", va, vb); /* %*c�Ե��س��� */
     i = LocateVex(*G, va); /* һ�� */
     j = LocateVex(*G, vb); /* ��һ�� */
     p = (EBox*)malloc(sizeof(EBox));
     p->mark = unvisited; /* ���ֵ */
     p->ivex = i;
     p->ilink = (*G).adjmulist[i].firstedge; /* ���ڱ�ͷ */
     (*G).adjmulist[i].firstedge = p;
     p->jvex = j;
     p->jlink = (*G).adjmulist[j].firstedge; /* ���ڱ�ͷ */
     (*G).adjmulist[j].firstedge = p;
     if(IncInfo) /* �� */
     {
       p->info = (InfoType*)malloc(sizeof(InfoType));
       printf("������ñߵ�Ȩֵ: ");
       scanf("%d", p->info);
     }
     else
     { 
       p->info = NULL;
     } 
   }
 }

 VertexType* GetVex(AMLGraph G, int v)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ���������š��������������v��ֵ */
   if(v>=G.vexnum || v<0)
   { 
     exit(ERROR);
   } 
   return &G.adjmulist[v].data;
 }

 Status PutVex(AMLGraph *G, VertexType v, VertexType value)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ�����㡣�����������v����ֵvalue */
   int i;
   
   i = LocateVex(*G, v);
   if(i < 0) /* v����G�Ķ��� */
   { 
     return ERROR;
   } 
   strcpy((*G).adjmulist[i].data, value);
   
   return OK;
 }

 int FirstAdjVex(AMLGraph G, VertexType v)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ������ */
   /* �������������v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1 */
   int i;
   i = LocateVex(G, v);
   if(i < 0) /* G�в����ڶ���v */
   { 
     return -1;
   }
    
   if(G.adjmulist[i].firstedge) /* v���ڽӶ��� */
   { 
     if(G.adjmulist[i].firstedge->ivex == i)
     { 
       return G.adjmulist[i].firstedge->jvex;
     } 
	 else
	 { 
       return G.adjmulist[i].firstedge->ivex;
     } 
   } 
   else
   { 
     return -1;
   } 
 }

 int NextAdjVex(AMLGraph G, VertexType v, VertexType w)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ�����㣬w��v���ڽӶ��� */
   /* �������������v��(�����w��)��һ���ڽӶ������š���w��v�����һ���ڽӵ㣬�򷵻�-1 */
   int i, j;
   EBox *p;
   
   i = LocateVex(G, v); /* i�Ƕ���v����� */
   j = LocateVex(G, w); /* j�Ƕ���w����� */
   if(i<0 || j<0) /* v��w����G�Ķ��� */
   { 
     return -1;
   } 
   p = G.adjmulist[i].firstedge; /* pָ�򶥵�v�ĵ�1���� */
   while( p )
   { 
     if(p->ivex==i && p->jvex!=j) /* �����ڽӶ���w(���1) */
     { 
       p = p->ilink; /* ����һ���ڽӶ��� */
     } 
	 else if(p->jvex==i && p->ivex!=j) /* �����ڽӶ���w(���2) */
	 { 
       p = p->jlink; /* ����һ���ڽӶ��� */
     } 
	 else /* ���ڽӶ���w */
	 { 
       break;
     } 
   } 
   
   if(p && p->ivex==i && p->jvex==j) /* �ҵ��ڽӶ���w(���1) */
   {
     p = p->ilink;
     if(p && p->ivex==i)
     { 
       return p->jvex;
     } 
	 else if(p && p->jvex==i)
	 { 
       return p->ivex;
     } 
   }
   if(p && p->ivex==j && p->jvex==i) /* �ҵ��ڽӶ���w(���2) */
   {
     p = p->jlink;
     if(p && p->ivex==i)
     { 
       return p->jvex;
     } 
	 else if(p && p->jvex==i)
	 { 
       return p->ivex;
     } 
   }
   
   return -1;
 }

 Status InsertVex(AMLGraph *G, VertexType v)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G�ж�������ͬ���� */
   /* �����������G�������¶���v(�������붥����صĻ�������InsertArc()ȥ��) */
   if((*G).vexnum == MAX_VERTEX_NUM) /* ������������ܲ��� */
   { 
     return ERROR;
   } 
   if(LocateVex(*G,v) >= 0) /* ����Ѵ��ڣ����ܲ��� */
   { 
     return ERROR;
   } 
   strcpy((*G).adjmulist[(*G).vexnum].data, v);
   (*G).adjmulist[(*G).vexnum++].firstedge = NULL;
   
   return OK;
 }

 Status DeleteArc(AMLGraph *G, VertexType v, VertexType w)
 { 
   /* ��ʼ����������ͼG���ڣ�v��w��G���������㡣�����������G��ɾ����<v,w> */
   int i, j;
   EBox *p, *q;
   i = LocateVex(*G, v);
   j = LocateVex(*G, w);
   if(i<0 || j<0 || i==j)
   { 
     return ERROR;  /* ͼ��û�иõ�򻡡�����ʹָ���ɾ���ߵĵ�1��ָ���ƹ������� */
   } 
   p = (*G).adjmulist[i].firstedge; /* pָ�򶥵�v�ĵ�1���� */
   if(p && p->jvex==j) /* ��1���߼�Ϊ��ɾ����(���1) */
   { 
     (*G).adjmulist[i].firstedge = p->ilink;
   } 
   else if(p && p->ivex==j) /* ��1���߼�Ϊ��ɾ����(���2) */
   { 
     (*G).adjmulist[i].firstedge = p->jlink;
   } 
   else /* ��1���߲��Ǵ�ɾ���� */
   {
     while(p) /* �����һ�<v,w> */
     { 
       if(p->ivex==i && p->jvex!=j) /* ���Ǵ�ɾ���� */
       {
         q = p;
         p = p->ilink; /* ����һ���ڽӶ��� */
       }
       else if(p->jvex==i && p->ivex!=j) /* ���Ǵ�ɾ���� */
       {
         q = p;
         p = p->jlink; /* ����һ���ڽӶ��� */
       }
       else /* ���ڽӶ���w */
       { 
         break;
       } 
	 } //while
     if(! p) /* û�ҵ��ñ� */
     { 
       return ERROR;
     } 
	 if(p->ivex==i && p->jvex==j) /* �ҵ���<v,w>(���1) */
	 { 
       if(q->ivex == i)
       {
         q->ilink = p->ilink;
       }
	   else
	   {
   		
   	
         q->jlink = p->ilink;
	   }
	 } 
	 else if(p->ivex==j && p->jvex==i) /* �ҵ���<v,w>(���2) */
	 {
       if(q->ivex == i)
       {
         q->ilink = p->jlink;
       }
	   else
	   {
         q->jlink = p->jlink;
	   }
	 }//else if
   }//else
    /* ��������һ�������Ҵ�ɾ������ɾ��֮ */
   p = (*G).adjmulist[j].firstedge; /* pָ�򶥵�w�ĵ�1���� */
   if(p->jvex == i) /* ��1���߼�Ϊ��ɾ����(���1) */
   {
     (*G).adjmulist[j].firstedge = p->ilink;
   }
   else if(p->ivex == i) /* ��1���߼�Ϊ��ɾ����(���2) */
   {
     (*G).adjmulist[j].firstedge = p->jlink;
   }
   else /* ��1���߲��Ǵ�ɾ���� */
   {
     while(p) /* �����һ�<v,w> */
     {
       if(p->ivex==j && p->jvex!=i) /* ���Ǵ�ɾ���� */
       {
         q = p;
         p = p->ilink; /* ����һ���ڽӶ��� */
       }
       else if(p->jvex==j && p->ivex!=i) /* ���Ǵ�ɾ���� */
       {
         q = p;
         p = p->jlink; /* ����һ���ڽӶ��� */
       }
       else /* ���ڽӶ���v */
       {
         break;
       }
	 }//while
     if(p->ivex==i && p->jvex==j) /* �ҵ���<v,w>(���1) */
     {
       if(q->ivex == j)
       {
         q->ilink = p->jlink;
       }
	   else
	   {
         q->jlink = p->jlink;
	   }
	 }
	 else if(p->ivex==j && p->jvex==i) /* �ҵ���<v,w>(���2) */
	 {
       if(q->ivex == j)
       {
         q->ilink = p->ilink;
       }
	   else
	   {
         q->jlink = p->ilink;
	   }
	 }//else if
   }//else
   if( p->info ) /* �������Ϣ(��Ȩֵ) */
   {
     free(p->info); /* �ͷ������Ϣ(��Ȩֵ) */
   }
   free(p); /* �ͷŽ�� */
   (*G).edgenum--; /* ����-1 */
   
   return OK;
 }

 Status DeleteVex(AMLGraph *G, VertexType v)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ�����㡣���������ɾ��G�ж���v������صı� */
   int i, j;
   EBox *p;
   
   i = LocateVex(*G, v); /* iΪ��ɾ���������� */
   if(i < 0)
   {
     return ERROR;
   }
   for(j=0; j<(*G).vexnum; j++) /* ɾ���붥��v�����ı�(����еĻ�) */
   {
     DeleteArc(G, v, (*G).adjmulist[j].data); /* ������ڴ˻�����ɾ�� */
   }
   for(j=i+1; j<(*G).vexnum; j++) /* ���ڶ���v����Ķ������ż�1 */
   {
     (*G).adjmulist[j-1] = (*G).adjmulist[j];
   }
   (*G).vexnum--; /* ��������1 */
   for(j=i; j<(*G).vexnum; j++) /* �޸���Ŵ���i�Ķ����ڱ����е���� */
   {
     p = (*G).adjmulist[j].firstedge;
     if(p)
     {
       if(p->ivex == j+1)
       {
         p->ivex--;
         p = p->ilink;
       }
       else
       {
         p->jvex--;
         p = p->jlink;
       }//else
     }//if
   }//for
   
   return OK;
 }

 void DestroyGraph(AMLGraph *G)
 { 
   /* ��ʼ����������ͼG���ڡ������������������ͼG */
   int i;
   
   for(i=(*G).vexnum-1; i>=0; i--) /* �ɴ�С����ɾ������ */
   {
     DeleteVex(G, (*G).adjmulist[i].data);
   }
 }

 Status InsertArc(AMLGraph *G, VertexType v, VertexType w)
 { 
   /* ��ʼ����������ͼG���ڣ�v��W��G���������㡣�����������G������<v,w> */
   int i, j, IncInfo;
   EBox *p;
   i = LocateVex(*G, v); /* һ�� */
   j = LocateVex(*G, w); /* ��һ�� */
   if(i<0 || j<0 || i==j)
   {
     return ERROR;
   }
   p = (EBox*)malloc(sizeof(EBox));
   p->mark = unvisited;
   p->ivex = i;
   p->ilink = (*G).adjmulist[i].firstedge; /* ���ڱ�ͷ */
   (*G).adjmulist[i].firstedge = p;
   p->jvex = j;
   p->jlink = (*G).adjmulist[j].firstedge; /* ���ڱ�ͷ */
   (*G).adjmulist[j].firstedge = p;
   printf("�ñ��Ƿ���Ȩֵ(1:�� 0:��): ");
   scanf("%d", &IncInfo);
   if(IncInfo) /* ��Ȩֵ */
   {
     p->info = (InfoType*)malloc(sizeof(InfoType));
     printf("������ñߵ�Ȩֵ: ");
     scanf("%d", p->info);
   }
   else
   {
     p->info = NULL;
   }
   (*G).edgenum++;
   
   return OK;
 }

 void DFS(AMLGraph G, int v)
 {
   int j;
   EBox *p;
   
   VisitFunc(G.adjmulist[v].data);
   visite[v] = TRUE;
   p = G.adjmulist[v].firstedge;
   while( p )
   {
     j = p->ivex==v ? p->jvex : p->ivex;
     
     if(! visite[j])
     {
       DFS(G, j);
     }
	 p = p->ivex == v ? p->ilink : p->jlink;
   }
 }

 void DFSTraverse(AMLGraph G, void(*visit)(VertexType))
 { 
   /* ��ʼ������ͼG���ڣ�Visit�Ƕ����Ӧ�ú������㷨7.4 */
   /* ����������ӵ�1��������������ȱ���ͼG������ÿ��������ú���Visitһ���ҽ�һ�� */
   int v;
   
   VisitFunc = visit;
   for(v=0; v<G.vexnum; v++)
   {
     visite[v] = FALSE;
   }
   for(v=0; v<G.vexnum; v++)
   {
     if(! visite[v])
     {
       DFS(G, v);
     }
   }
   printf("\n");
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
 
 void BFSTraverse(AMLGraph G, void(*Visit)(VertexType))
 { 
   /* ��ʼ������ͼG���ڣ�Visit�Ƕ����Ӧ�ú������㷨7.6 */
   /* ����������ӵ�1�������𣬰�������ȷǵݹ����ͼG������ÿ��������ú��� */
   /*           Visitһ���ҽ�һ�Ρ�ʹ�ø�������Q�ͷ��ʱ�־����visite */
   int v, u, w;
   LinkQueue Q;
   
   for(v=0; v<G.vexnum; v++)
   {
     visite[v] = FALSE; /* �ó�ֵ */
   }
   InitQueue(&Q); /* �ÿյĸ�������Q */
   for(v=0; v<G.vexnum; v++)
   {
     if(! visite[v]) /* v��δ���� */
     {
       visite[v] = TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
       Visit(G.adjmulist[v].data);
       EnQueue(&Q, v); /* v����� */
       while(! QueueEmpty(Q)) /* ���в��� */
       {
         DeQueue(&Q,&u); /* ��ͷԪ�س��Ӳ���Ϊu */
         for(w=FirstAdjVex(G,G.adjmulist[u].data); w>=0; w=NextAdjVex(G,G.adjmulist[u].data,G.adjmulist[w].data))
         {
		   if(! visite[w]) /* wΪu����δ���ʵ��ڽӶ������� */
           {
             visite[w] = TRUE;
             Visit(G.adjmulist[w].data);
             EnQueue(&Q, w);
           }
         }//for
       }//while
     }//if
   }//for
   
   printf("\n");
 }

 void MarkUnvizited(AMLGraph G)
 { 
   /* �ñߵķ��ʱ��Ϊδ������ */
   int i;
   EBox *p;
   
   for(i=0; i<G.vexnum; i++)
   {
     p = G.adjmulist[i].firstedge;
     while( p )
     {
       p->mark = unvisited;
       if(p->ivex == i)
       {
         p = p->ilink;
       }
	   else
	   {
         p = p->jlink;
	   }
	 }//while
   }//for
   
 }

 void Display(AMLGraph G)
 { 
   /* �������ͼ���ڽӶ��ر�G */
   int i;
   EBox *p;
   
   MarkUnvizited(G); /* �ñߵķ��ʱ��Ϊδ������ */
   printf("%d�����㣺\n",G.vexnum);
   
   for(i=0; i<G.vexnum; ++i)
   {
     printf("%s ", G.adjmulist[i].data);
   }
   printf("\n%d����:\n",G.edgenum);
   for(i=0; i<G.vexnum; i++)
   {
     p = G.adjmulist[i].firstedge;
     while(p)
     {
       if(p->ivex == i) /* �ߵ�i����ö����й� */
       {
         if(! p->mark) /* ֻ���һ�� */
         {
           printf("%s��%s ", G.adjmulist[i].data, G.adjmulist[p->jvex].data);
           p->mark = visited;
           if( p->info) /* ���������Ϣ */
           {
             printf("Ȩֵ: %d ", *p->info);
           }
		 }
		 
         p = p->ilink;
       }
       else /* �ߵ�j����ö����й� */
       {
         if(! p->mark) /* ֻ���һ�� */
         {
           printf("%s��%s ", G.adjmulist[p->ivex].data, G.adjmulist[i].data);
           p->mark = visited;
           if(p->info) /* ���������Ϣ */
           {
             printf("Ȩֵ: %d ",*p->info);
           }
		 }//if
         p = p->jlink;
       }//else
     }//while
     printf("\n");
   }//for
 }
 
 void visit(VertexType v)
 {
   printf("%s ",v);
 }
 
 