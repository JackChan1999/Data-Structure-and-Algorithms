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
 
 typedef int InfoType; /* Ȩֵ���� */
 #define MAX_VERTEX_NAME 3  /* �����ַ�����󳤶�+1 */
 typedef char  VertexType[MAX_VERTEX_NAME];
 
 #define MAX_VERTEX_NUM 20
 typedef struct ArcBox1 /* ��������hlink������ */
 {
   int tailvex,headvex; /* �û���β��ͷ�����λ�� */
   InfoType *info; /* �û������Ϣ��ָ�룬��ָ��Ȩֵ��������Ϣ */
   struct ArcBox1 *hlink,*tlink; /* �ֱ�Ϊ��ͷ��ͬ��β��ͬ�Ļ������� */
 }ArcBox1;
 typedef struct
 {
   int tailvex,headvex; /* �û���β��ͷ�����λ�� */
   InfoType *info; /* �û������Ϣ��ָ�룬��ָ��Ȩֵ��������Ϣ */
   ArcBox1 *hlink;
 }ElemType;
 typedef struct ArcBox
 {
   ElemType data;
   struct ArcBox *tlink;
 }ArcBox;
 typedef struct /* ������ */
 {
   VertexType data;
   ArcBox1 *firstin; /* ָ��ö����һ���뻡 */
   ArcBox *firstout; /* ָ��ö����һ������ */
 }VexNode;
 typedef struct
 {
   VexNode xlist[MAX_VERTEX_NUM]; /* ��ͷ����(����) */
   int vexnum,arcnum; /* ����ͼ�ĵ�ǰ�������ͻ��� */
 }OLGraph;
 #define LNode ArcBox /* �ӣ����嵥����Ľ��������ͼ�ı�������� */
 #define next tlink /* �ӣ����嵥�������ָ�����Ǳ���ָ����һ��������ָ���� */
 typedef ArcBox *LinkList; /* �ӣ�����ָ���������ָ����ָ��ͼ�ı����ָ�� */
 
 #define DestroyList ClearList /* DestroyList()��ClearList()�Ĳ�����һ���� */
 Boolean visited[MAX_VERTEX_NUM]; /* ���ʱ�־���� */
 void(*VisitFunc)(VertexType); /* �������� */
 
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
 
 
void InitList(LinkList *L);
void ClearList(LinkList *L);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
Status GetElem(LinkList L, int i, ElemType *e);
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status ListInsert(LinkList *L, int i, ElemType e);
Status ListDelete(LinkList *L, int i, ElemType *e);
void ListTraverse(LinkList L, void(*vi)(ElemType));
int LocateVex(OLGraph G, VertexType u);
void CreateDG(OLGraph *G);
void DestroyGraph(OLGraph *G);
VertexType* GetVex(OLGraph G, int v);
Status PutVex(OLGraph *G, VertexType v, VertexType value);
int FirstAdjVex(OLGraph G, VertexType v);
int NextAdjVex(OLGraph G, VertexType v, VertexType w);
void InsertVex(OLGraph *G, VertexType v);
Status equal(ElemType c1, ElemType c2);
Status DeleteVex(OLGraph *G, VertexType v);
Status InsertArc(OLGraph *G, VertexType v, VertexType w);
Status DeleteArc(OLGraph *G, VertexType v, VertexType w);
void DFS(OLGraph G, int i); /* DFSTraverse()���� */
void DFSTraverse(OLGraph G, void(*Visit)(VertexType));
void InitQueue(LinkQueue *Q);
void DestroyQueue(LinkQueue *Q);
void ClearQueue(LinkQueue *Q);
Status QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
Status GetHead_Q(LinkQueue Q, QElemType *e);//��������
void EnQueue(LinkQueue *Q, QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
void QueueTraverse(LinkQueue Q, void(*vi)(QElemType));
void BFSTraverse(OLGraph G, void(*Visit)(VertexType));
void Display(OLGraph G);
void visit(VertexType v);

 int main()
 {
 	int j,k,n;
   OLGraph g;
   VertexType v1,v2;
   CreateDG(&g);
   Display(g);
   printf("�޸Ķ����ֵ��������ԭֵ ��ֵ: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("�����¶��㣬�����붥���ֵ: ");
   scanf("%s",v1);
   InsertVex(&g,v1);
   printf("�������¶����йصĻ��������뻡��: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("��������һ�����ֵ ��һ����ķ���(0:��ͷ 1:��β): ");
     scanf("%s%d",v2,&j);
     if(j)
       InsertArc(&g,v2,v1);
     else
       InsertArc(&g,v1,v2);
   }
   Display(g);
   printf("ɾ��һ�������������ɾ�����Ļ�β ��ͷ��");
   scanf("%s%s",v1,v2);
   DeleteArc(&g,v1,v2);
   Display(g);
   printf("ɾ�����㼰��صĻ��������붥���ֵ: ");
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

 
 
 
 
 
 void InitList(LinkList *L)
 { 
   /* �������������һ���յ����Ա�L */
   *L = NULL; /* ָ��Ϊ�� */
 }

 void ClearList(LinkList *L)
 { 
   /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
   LinkList p;
   while(*L) /* L���� */
   {
     p = *L; /* pָ����Ԫ��� */
     *L = (*L)->next; /* Lָ���2�����(����Ԫ���) */
     free(p); /* �ͷ���Ԫ��� */
   }
 }

 Status ListEmpty(LinkList L)
 { 
   /* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
   if(L)
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
   /* ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
   int i = 0;
   LinkList p = L;
   
   while(p) /* pָ����(û����β) */
   {
     p = p->next; /* pָ����һ����� */
     i++;
   }
   return i;
 }

 Status GetElem(LinkList L, int i, ElemType *e)
 { 
   /* LΪ����ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR */
   int j = 1;
   LinkList p = L;
   
   if(i < 1) /* iֵ���Ϸ� */
   { 
     return ERROR;
   } 
   while(j<i && p) /* û����i��Ԫ�أ�Ҳû����β */
   {
     j++;
     p = p->next;
   }
   if(j == i) /* ���ڵ�i��Ԫ�� */
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
   /* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����(����Ϊ1������Ϊ0) */
   /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
   /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
   int i = 0;
   LinkList p = L;
   
   while(p)
   {
     i++;
     if(compare(p->data, e)) /* �ҵ�����������Ԫ�� */
     { 
       return i;
     } 
	 p = p->next;
   }
   return 0;
 }

 Status ListInsert(LinkList *L, int i, ElemType e)
 { 
   /* �ڲ���ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
   int j = 1;
   LinkList p = *L, s;
   if(i < 1) /* iֵ���Ϸ� */
   { 
     return ERROR;
   } 
   s = (LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
   s->data = e; /* ��s��data��ֵ */
   if(i == 1) /* ���ڱ�ͷ */
   {
     s->next = *L;
     *L = s; /* �ı�L */
   }
   else
   { 
     /* ���ڱ�����ദ */
     while(p && j<i-1) /* Ѱ�ҵ�i-1����� */
     {
       p = p->next;
       j++;
     }
     if(! p) /* i���ڱ�+1 */
     { 
       return ERROR;
     } 
	 s->next = p->next;
     p->next = s;
   }
   return OK;
 }

 Status ListDelete(LinkList *L, int i, ElemType *e)
 { 
   /* �ڲ���ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ */
   int j = 1;
   LinkList p = *L, q;
   if(i == 1) /* ɾ����1����� */
   {
     *L = p->next; /* L�ɵ�2����㿪ʼ */
     *e = p->data;
     free(p); /* ɾ�����ͷŵ�1����� */
   }
   else
   {
     while(p->next && j<i-1) /* Ѱ�ҵ�i����㣬����pָ����ǰ�� */
     {
       p = p->next;
       j++;
     }
     if(!p->next || j>i-1) /* ɾ��λ�ò����� */
     { 
       return ERROR;
     } 
	 q = p->next; /* ɾ�����ͷŽ�� */
     p->next = q->next;
     *e = q->data;
     free(q);
   }
   
   return OK;
 }

 void ListTraverse(LinkList L, void(*vi)(ElemType))
 { 
   /* ��ʼ���������Ա�L�Ѵ��ڡ�������������ζ�L��ÿ������Ԫ�ص��ú���vi() */
   LinkList p = L;
   while(p)
   {
     vi(p->data);
     p = p->next;
   }
   printf("\n");
 }
 
 int LocateVex(OLGraph G, VertexType u)
 { 
   /* ���ض���u������ͼG�е�λ��(���)���粻�����򷵻�-1 */
   int i;
   for(i=0; i<G.vexnum; ++i) /* ��ѭ�����Ҹý�� */
   {  
     if(! strcmp(G.xlist[i].data,u))
     { 
       return i;
     } 
   } 
   return -1;
 }

 void CreateDG(OLGraph *G)
 { 
   /* ����ʮ������洢��ʾ����������ͼG���㷨7.3 */
   int i, j, k;
   int IncInfo;
   ArcBox *p;
   VertexType v1, v2;
   printf("����������ͼ�Ķ�����,����,�Ƿ�Ϊ��Ȩͼ(��:1����:0): ");
   scanf("%d,%d,%d", &(*G).vexnum, &(*G).arcnum, &IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n", (*G).vexnum, MAX_VERTEX_NAME);
   
   for(i=0; i<(*G).vexnum; ++i)
   { 
     /* �����ͷ���� */
     scanf("%s", &(*G).xlist[i].data); /* ���붥��ֵ */
     (*G).xlist[i].firstin = NULL; /* ��ʼ���뻡������ͷָ�� */
     (*G).xlist[i].firstout = NULL; /* ��ʼ������������ͷָ�� */
   }
   printf("������%d�����Ļ�β�ͻ�ͷ(�ո�Ϊ���):\n", (*G).arcnum);
   for(k=0; k<(*G).arcnum; ++k)
   { 
     /* �������������ʮ������ */
     scanf("%s%s", &v1, &v2);
     i = LocateVex(*G, v1); /* ȷ��v1��v2��G�е�λ�� */
     j = LocateVex(*G, v2);
     p = (ArcBox *)malloc(sizeof(ArcBox)); /* ���������(�ٶ����㹻�ռ�) */
     p->data.tailvex = i; /* �Ի���㸳ֵ */
     p->data.headvex = j;
     p->data.hlink = (*G).xlist[j].firstin; /* ������뻡�ͳ��������ͷ�Ĳ��� */
     p->tlink = (*G).xlist[i].firstout;
     (*G).xlist[j].firstin = (ArcBox1 *)p; /* ǿ������ת�� */
     (*G).xlist[i].firstout = p;
     if(IncInfo)
     { 
	   /* ���� */
       p->data.info = (InfoType *)malloc(sizeof(InfoType));
       printf("������û���Ȩֵ: ");
       scanf("%d", p->data.info);
     }
     else
	 { /* �������������Ϣ */
       p->data.info = NULL;
     }  
   }
 }

 void DestroyGraph(OLGraph *G)
 { /* ��ʼ����������ͼG���ڡ������������������ͼG */
   int i;
   ElemType e;
   
   for(i=0; i<(*G).vexnum; i++) /* �����ж��� */
   { 
     while( (*G).xlist[i].firstout ) /* ���������� */
     {
       ListDelete(&(*G).xlist[i].firstout, 1, &e); /* ɾ�����1����㣬��ֵ����e����bo2-8.c�� */
       if(e.info) /* ��Ȩ */
       { 
	     free(e.info); /* �ͷŶ�̬���ɵ�Ȩֵ�ռ� */
       } 
	 }
   } 
   
   (*G).arcnum = 0;
   (*G).vexnum = 0;
 }

 VertexType* GetVex(OLGraph G, int v)
 { /* ��ʼ����������ͼG���ڣ�v��G��ĳ���������š��������������v��ֵ */
   if(v>=G.vexnum || v<0)
   { 
     exit(ERROR);
   } 
   return &G.xlist[v].data;
 }

 Status PutVex(OLGraph *G, VertexType v, VertexType value)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ�����㡣�����������v����ֵvalue */
   int i;
   
   i = LocateVex(*G, v);
   if(i < 0) /* v����G�Ķ��� */
   { 
     return ERROR;
   } 
   strcpy((*G).xlist[i].data, value);
   
   return OK;
 }

 int FirstAdjVex(OLGraph G, VertexType v)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ������ */
   /* �������������v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1 */
   int i;
   ArcBox *p;
   
   i = LocateVex(G, v);
   p = G.xlist[i].firstout; /* pָ�򶥵�v�ĵ�1������ */
   if(p)
   { 
     return p->data.headvex;
   } 
   else
   { 
     return -1;
   } 
 }

 int NextAdjVex(OLGraph G, VertexType v, VertexType w)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ�����㣬w��v���ڽӶ��� */
   /* �������������v��(�����w��)��һ���ڽӶ������ţ���w��v�����һ���ڽӶ��㣬�򷵻�-1 */
   int i, j;
   ArcBox *p;
   i = LocateVex(G, v); /* i�Ƕ���v����� */
   j = LocateVex(G, w); /* j�Ƕ���w����� */
   p = G.xlist[i].firstout; /* pָ�򶥵�v�ĵ�1������ */
   while(p && p->data.headvex!=j)
   { 
     p = p->tlink;
   } 
   if( p ) /* w����v�����һ���ڽӶ��� */
   { 
     p = p->tlink; /* pָ�������w����һ���ڽӶ��� */
   } 
   if(p) /* ����һ���ڽӶ��� */
   { 
     return p->data.headvex;
   } 
   else
   { 
     return -1;
   } 
 }

 void InsertVex(OLGraph *G, VertexType v)
 { 
   /* ��ʼ����������ͼG���ڣ�v������ͼG�ж�������ͬ���� */
   /* ���������������ͼG�������¶���v(�������붥����صĻ�������InsertArc()ȥ��) */
   strcpy((*G).xlist[(*G).vexnum].data, v); /* ������������ */
   (*G).xlist[(*G).vexnum].firstin = NULL; /* ��ʼ���뻡���� */
   (*G).xlist[(*G).vexnum].firstout = NULL; /* ��ʼ���������� */
   (*G).vexnum++; /* ������+1 */
 }

 Status equal(ElemType c1, ElemType c2)
 {
   if(c1.headvex == c2.headvex)
   { 
     return TRUE;
   } 
   else
   { 
     return FALSE;
   } 
 }

 Status DeleteVex(OLGraph *G, VertexType v)
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ�����㡣���������ɾ��G�ж���v������صĻ� */
   int i, j, k;
   ElemType e1, e2;
   ArcBox *p;
   ArcBox1 *p1, *p2;
   
   k = LocateVex(*G, v); /* k�Ƕ���v����� */
   if(k < 0) /* v����ͼG�Ķ��� */
   { 
     return ERROR; /* ����ɾ������v���뻡 */
   } 
   e1.headvex = k; /* e1��ΪLocateElem()�ıȽ�Ԫ�� */
   for(j=0; j<(*G).vexnum; j++) /* ����v���뻡����������ĳ��� */
   {
     i = LocateElem((*G).xlist[j].firstout, e1, equal);
     if( i ) /* ����v�Ƕ���j�ĳ��� */
     {
       ListDelete(&(*G).xlist[j].firstout, i, &e2); /* ɾ���û���㣬��ֵ����e2 */
       (*G).arcnum--; /* ����-1 */
       if(e2.info) /* ��Ȩ */
       { 
	     free(e2.info); /* �ͷŶ�̬���ɵ�Ȩֵ�ռ� */
       } 
     }//if 
   }//for 
   /* ����ɾ������v�ĳ��� */
   for(j=0; j<(*G).vexnum; j++) /* ����v�ĳ���������������뻡 */
   {
     p1 = (*G).xlist[j].firstin;
     while(p1 && p1->tailvex!=k)
     {
       p2 = p1;
       p1 = p1->hlink;
     }
     if( p1 ) /* �ҵ�����v�ĳ��� */
     {
       if(p1 == (*G).xlist[j].firstin) /* ���׽�� */
       {
	     (*G).xlist[j].firstin = p1->hlink; /* �뻡ָ��ָ����һ����� */
       }
	   else /* �����׽�� */
	   {
	     p2->hlink = p1->hlink; /* ����������ȥp1��ָ��� */
	   }
	   if(p1->info) /* ��Ȩ */
	   {
	     free(p1->info); /* �ͷŶ�̬���ɵ�Ȩֵ�ռ� */
	   }
	   free(p1); /* �ͷ�p1��ָ��� */
       (*G).arcnum--; /* ����-1 */
     }//if
   }//for
   
   for(j=k+1; j<(*G).vexnum; j++) /* ���>k�Ķ���������ǰ�� */
   {
     (*G).xlist[j-1] = (*G).xlist[j];
   }
   (*G).vexnum--; /* ��������1 */
   for(j=0; j<(*G).vexnum; j++) /* ������>k��Ҫ��1 */
   {
     p = (*G).xlist[j].firstout; /* ������� */
     while(p)
     {
       if(p->data.tailvex > k)
       {
         p->data.tailvex--; /* ���-1 */
       }
	   if(p->data.headvex > k)
	   {
	     p->data.headvex--; /* ���-1 */
	   }
	   p = p->tlink;
     }//while
   }//for
   
   return OK;
 }

 Status InsertArc(OLGraph *G, VertexType v, VertexType w)
 { 
   /* ��ʼ����������ͼG���ڣ�v��w��G���������㡣�����������G������<v,w> */
   int i, j;
   int IncInfo;
   ArcBox *p;
   
   i = LocateVex(*G, v); /* ��β����� */
   j = LocateVex(*G, w); /* ��ͷ����� */
   if(i<0 || j<0)
   {
     return ERROR;
   }
   p = (ArcBox *)malloc(sizeof(ArcBox)); /* �����½�� */
   p->data.tailvex = i; /* ���½�㸳ֵ */
   p->data.headvex = j;
   p->data.hlink = (*G).xlist[j].firstin; /* �����뻡�ͳ�������ͷ */
   p->tlink = (*G).xlist[i].firstout;
   (*G).xlist[j].firstin = (ArcBox1*)p;
   (*G).xlist[i].firstout = p;
   (*G).arcnum++; /* ������1 */
   printf("Ҫ����Ļ��Ƿ��Ȩ(��: 1,��: 0): ");
   scanf("%d", &IncInfo);
   if(IncInfo) /* ��Ȩ */
   {
     p->data.info = (InfoType *)malloc(sizeof(InfoType)); /* ��̬����Ȩֵ�ռ� */
     printf("������û���Ȩֵ: ");
     scanf("%d", p->data.info);
   }
   else
   { 
     p->data.info = NULL;
   } 
   
   return OK;
 }

 Status DeleteArc(OLGraph *G, VertexType v, VertexType w)
 { 
   /* ��ʼ����������ͼG���ڣ�v��w��G���������㡣�����������G��ɾ����<v,w> */
   int i, j, k;
   ElemType e;
   ArcBox1 *p1, *p2;
   i = LocateVex(*G, v); /* ��β����� */
   j = LocateVex(*G, w); /* ��ͷ����� */
   if(i<0 || j<0 || i==j)
   { 
     return ERROR;
   } 
   p1 = (*G).xlist[j].firstin; /* p1ָ��w���뻡���� */
   while(p1 && p1->tailvex!=i) /* ʹp1ָ���ɾ��� */
   {
     p2 = p1;
     p1 = p1->hlink;
   }
   if(p1 == (*G).xlist[j].firstin) /* �׽���Ǵ�ɾ��� */
   { 
     (*G).xlist[j].firstin = p1->hlink; /* �뻡ָ��ָ����һ����� */
   } 
   else /* �׽�㲻�Ǵ�ɾ��� */
   { 
     p2->hlink = p1->hlink; /* ����������ȥp1��ָ���(�ý�����ڳ���������) */
   } 
   e.headvex = j; /* ��ɾ�����Ļ�ͷ�������Ϊj��e��ΪLocateElem()�ıȽ�Ԫ�� */
   k = LocateElem((*G).xlist[i].firstout, e, equal); /* �ڳ��������е�λ�� */
   ListDelete(&(*G).xlist[i].firstout, k, &e); /* �ڳ���������ɾ���ý�㣬��ֵ����e */
   if(e.info) /* ��Ȩ */
   { 
     free(e.info); /* �ͷŶ�̬���ɵ�Ȩֵ�ռ� */
   } 
   (*G).arcnum--; /* ����-1 */
   
   return OK;
 }

 void DFS(OLGraph G, int i) /* DFSTraverse()���� */
 {
   ArcBox *p;
   
   visited[i] = TRUE; /* ���ʱ�־������1(�ѱ�����) */
   VisitFunc(G.xlist[i].data); /* ������i������ */
   p = G.xlist[i].firstout; /* pָ���i������ĳ��� */
   while(p && visited[p->data.headvex]) /* pû����β�Ҹû���ͷ�����ѱ����� */
   { 
     p = p->tlink; /* ������һ����� */
   } 
   if(p && !visited[p->data.headvex]) /* �û���ͷ����δ������ */
   { 
     DFS(G, p->data.headvex); /* �ݹ����DFS() */
   } 
 }

 void DFSTraverse(OLGraph G, void(*Visit)(VertexType))
 { 
   /* ��ʼ����������ͼG���ڣ�v��G��ĳ�����㣬Visit�Ƕ����Ӧ�ú���(�㷨7.4) */
   /* �������:�ӵ�1��������,��������ȵݹ��������ͼG,����ÿ��������ú���Visitһ���ҽ�һ�� */
   int v;
   
   VisitFunc=Visit;
   for(v=0; v<G.vexnum; v++)
   { 
     visited[v] = FALSE; /* ���ʱ�־�����ó�ֵ(δ������) */
   } 
   for(v=0; v<G.vexnum; v++) /* �����0��ʼ����������δ�����ʹ��Ķ��� */
   {  
     if(! visited[v])
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
 
 void BFSTraverse(OLGraph G, void(*Visit)(VertexType))
 { 
   /* ��ʼ����������ͼG���ڣ�Visit�Ƕ����Ӧ�ú������㷨7.6 */
   /* ����������ӵ�1�������𣬰�������ȷǵݹ��������ͼG������ÿ��������ú���Visit */
   /*           һ���ҽ�һ�Ρ�ʹ�ø�������Q�ͷ��ʱ�־����visited */
   int v, u, w;
   LinkQueue Q;
   
   for(v=0; v<G.vexnum; v++)
   { 
     visited[v]=FALSE;
   } 
   InitQueue(&Q);
   for(v=0; v<G.vexnum; v++)
   { 
     if(! visited[v])
     {
       visited[v] = TRUE;
       Visit(G.xlist[v].data);
       EnQueue(&Q, v);
       while(! QueueEmpty(Q))
       {
	     DeQueue(&Q,&u);
	     for(w=FirstAdjVex(G,G.xlist[u].data); w>=0; w=NextAdjVex(G,G.xlist[u].data,G.xlist[w].data))
	     { 
	       if(!visited[w]) /* wΪu����δ���ʵ��ڽӶ������� */
	       {
	         visited[w]=TRUE;
	         Visit(G.xlist[w].data);
	         EnQueue(&Q,w);
	       }
	     } //for
       }//while
     }//if
   } //for 
   
   printf("\n");
 }

 void Display(OLGraph G)
 { 
   /* �������ͼG */
   int i;
   ArcBox *p;
   
   printf("��%d������: ", G.vexnum);
   for(i=0; i<G.vexnum; i++) /* ������� */
   {
     printf("%s ", G.xlist[i].data);
   }
   printf("\n%d����:\n", G.arcnum);
   for(i=0; i<G.vexnum; i++) /* ˳����������� */
   {
     p = G.xlist[i].firstout;
     while( p )
     {
       printf("%s��%s ",G.xlist[i].data,G.xlist[p->data.headvex].data);
       if(p->data.info) /* �û��������Ϣ(Ȩֵ) */
       {
	     printf("Ȩֵ: %d ",*p->data.info);
       }
	   p = p->tlink;
     }
     printf("\n");
   }
 }
 
 void visit(VertexType v)
 {
   printf("%s ",v);
 }
 