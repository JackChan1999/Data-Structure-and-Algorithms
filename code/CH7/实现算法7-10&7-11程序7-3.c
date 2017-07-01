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
 
 #define MAX_NAME 2 /* �����ַ�������󳤶�+1 */
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; /* �ַ������� */
 
 #define MAX_VERTEX_NUM 20
 typedef enum{DG,DN,UDG,UDN}GraphKind; /* {����ͼ,������,����ͼ,������} */
 typedef struct /* �� */
 {
   int adjvex; /* �û���ָ��Ķ����λ�� */
   InfoType *info; /* ����Ȩֵָ�� */
 }ElemType;

 typedef struct ArcNode /* �� */
 {
   ElemType data; /* ��ָ������Ĳ��ֶ�����ElemType */
   struct ArcNode *nextarc; /* ָ����һ������ָ�� */
 }ArcNode; /* ���� */

 typedef struct
 {
   VertexType data; /* ������Ϣ */
   ArcNode *firstarc; /* ��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ�� */
 }VNode,AdjList[MAX_VERTEX_NUM]; /* ͷ��� */

 typedef struct
 {
   AdjList vertices;
   int vexnum,arcnum; /* ͼ�ĵ�ǰ�������ͻ��� */
   GraphKind kind; /* ͼ�������־ */
 }ALGraph;
 #define LNode ArcNode /* �ӣ����嵥����Ľ��������ͼ�ı�������� */
 #define next nextarc /* �ӣ����嵥�������ָ�����Ǳ���ָ����һ������ָ���� */
 typedef ArcNode *LinkList; /* �ӣ�����ָ���������ָ����ָ��ͼ�ı����ָ�� */
 
 #define DestroyList ClearList /* DestroyList()��ClearList()�Ĳ�����һ���� */
 Boolean visited[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */
 void(*VisitFunc)(char* v); /* ��������(ȫ����) */
 typedef int QElemType; /* ����Ԫ������ */
 typedef struct QNode
 {
   QElemType data;
   struct QNode *next;
 }QNode,*QueuePtr;

 typedef struct
 {
   QueuePtr front,rear; /* ��ͷ����βָ�� */
 }LinkQueue;
 
 int count,lowcount=1; /* ȫ����count�Է���˳�����,lowcount�����lowֵ��˳����� */
 int low[MAX_VERTEX_NUM],lowOrder[MAX_VERTEX_NUM];
 /* ȫ�����飬low[]�涥���lowֵ��lowOrder�涥�����lowֵ��˳�� */
 
 void InitList(LinkList *L)
 { /* �������������һ���յ����Ա�L */
   *L=NULL; /* ָ��Ϊ�� */
 }

 void ClearList(LinkList *L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
   LinkList p;
   while(*L) /* L���� */
   {
     p=*L; /* pָ����Ԫ��� */
     *L=(*L)->next; /* Lָ���2�����(����Ԫ���) */
     free(p); /* �ͷ���Ԫ��� */
   }
 }

 Status ListEmpty(LinkList L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
   if(L)
     return FALSE;
   else
     return TRUE;
 }

 int ListLength(LinkList L)
 { /* ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
   int i=0;
   LinkList p=L;
   while(p) /* pָ����(û����β) */
   {
     p=p->next; /* pָ����һ����� */
     i++;
   }
   return i;
 }

 Status GetElem(LinkList L,int i,ElemType *e)
 { /* LΪ����ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR */
   int j=1;
   LinkList p=L;
   if(i<1) /* iֵ���Ϸ� */
     return ERROR;
   while(j<i&&p) /* û����i��Ԫ�أ�Ҳû����β */
   {
     j++;
     p=p->next;
   }
   if(j==i) /* ���ڵ�i��Ԫ�� */
   {
     *e=p->data;
     return OK;
   }
   else
     return ERROR;
 }

 int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����(����Ϊ1������Ϊ0) */
   /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
   /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
   int i=0;
   LinkList p=L;
   while(p)
   {
     i++;
     if(compare(p->data,e)) /* �ҵ�����������Ԫ�� */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status ListInsert(LinkList *L,int i,ElemType e)
 { /* �ڲ���ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
   int j=1;
   LinkList p=*L,s;
   if(i<1) /* iֵ���Ϸ� */
     return ERROR;
   s=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
   s->data=e; /* ��s��data��ֵ */
   if(i==1) /* ���ڱ�ͷ */
   {
     s->next=*L;
     *L=s; /* �ı�L */
   }
   else
   { /* ���ڱ�����ദ */
     while(p&&j<i-1) /* Ѱ�ҵ�i-1����� */
     {
       p=p->next;
       j++;
     }
     if(!p) /* i���ڱ�+1 */
       return ERROR;
     s->next=p->next;
     p->next=s;
   }
   return OK;
 }

 Status ListDelete(LinkList *L,int i,ElemType *e)
 { /* �ڲ���ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ */
   int j=1;
   LinkList p=*L,q;
   if(i==1) /* ɾ����1����� */
   {
     *L=p->next; /* L�ɵ�2����㿪ʼ */
     *e=p->data;
     free(p); /* ɾ�����ͷŵ�1����� */
   }
   else
   {
     while(p->next&&j<i-1) /* Ѱ�ҵ�i����㣬����pָ����ǰ�� */
     {
       p=p->next;
       j++;
     }
     if(!p->next||j>i-1) /* ɾ��λ�ò����� */
       return ERROR;
     q=p->next; /* ɾ�����ͷŽ�� */
     p->next=q->next;
     *e=q->data;
     free(q);
   }
   return OK;
 }

 void ListTraverse(LinkList L,void(*vi)(ElemType))
 { /* ��ʼ���������Ա�L�Ѵ��ڡ�������������ζ�L��ÿ������Ԫ�ص��ú���vi() */
   LinkList p=L;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
 }
 
  void InsertAscend(LinkList *L,ElemType e,int(*compare)(ElemType,ElemType))
 { /* ���ؼ��ַǽ���e�����L������compare()����ֵΪ���β�1�Ĺؼ���-�β�2�Ĺؼ��� */
   LinkList q=*L;
   if(!*L||compare(e,(*L)->data)<=0) /* ����ջ�e�Ĺؼ���С�ڵ����׽��Ĺؼ��� */
     ListInsert(L,1,e); /* ��e���ڱ�ͷ����bo2-8.c�� */
   else
   {
     while(q->next&&compare(q->next->data,e)<0) /* q����β�����q����һ���ؼ���<e�Ĺؼ��� */
       q=q->next;
     ListInsert(&q,2,e); /* ����q��ָ����(��q��Ϊͷָ��) */
   }
 }

 LinkList Point(LinkList L,ElemType e,Status(*equal)(ElemType,ElemType),LinkList *p)
 { /* ���ұ�L�����������Ľ�㡣���ҵ�������ָ��ý���ָ�룬pָ��ý���ǰ��(���ý���� */
   /* ��Ԫ��㣬��p=NULL)�����L�������������Ľ�㣬�򷵻�NULL��p�޶��塣*/
   /* ����equal()�����βεĹؼ�����ȣ�����OK�����򷵻�ERROR */
   int i,j;
   i=LocateElem(L,e,equal);
   if(i) /* �ҵ� */
   {
     if(i==1) /* ����Ԫ��� */
     {
       *p=NULL;
       return L;
     }
     *p=L;
     for(j=2;j<i;j++)
       *p=(*p)->next;
     return (*p)->next;
   }
   return NULL; /* û�ҵ� */
 }

 Status DeleteElem(LinkList *L,ElemType *e,Status(*equal)(ElemType,ElemType))
 { /* ɾ����L�����������Ľ�㣬������TRUE�����޴˽�㣬�򷵻�FALSE�� */
   /* ����equal()�����βεĹؼ�����ȣ�����OK�����򷵻�ERROR */
   LinkList p,q;
   q=Point(*L,*e,equal,&p);
   if(q) /* �ҵ��˽�㣬��qָ��ý�� */
   {
     if(p) /* �ý�㲻����Ԫ��㣬pָ����ǰ�� */
       ListDelete(&p,2,e); /* ��p��Ϊͷָ�룬ɾ����2����� */
     else /* �ý������Ԫ��� */
       ListDelete(L,1,e);
     return TRUE;
   }
   return FALSE;
 }
 
  int LocateVex(ALGraph G,VertexType u)
 { /* ��ʼ������ͼG���ڣ�u��G�ж�������ͬ���� */
   /* �����������G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vertices[i].data)==0)
       return i;
   return -1;
 }

 void CreateGraph(ALGraph *G)
 { /* �����ڽӱ�洢�ṹ������û�������Ϣͼ����G(��һ����������4��ͼ) */
   int i,j,k,w; /* w��Ȩֵ */
   VertexType va,vb; /* ���ӱ߻򻡵�2���� */
   ElemType e;
   printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3): ");
   scanf("%d",&(*G).kind);
   printf("������ͼ�Ķ�����,����: ");
   scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
   printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
   {
     scanf("%s",(*G).vertices[i].data);
     (*G).vertices[i].firstarc=NULL; /* ��ʼ����ö����йصĳ������� */
   }
   if((*G).kind%2) /* �� */
     printf("������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���):\n");
   else /* ͼ */
     printf("������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���):\n");
   for(k=0;k<(*G).arcnum;++k) /* ������ػ����� */
   {
     if((*G).kind%2) /* �� */
       scanf("%d%s%s",&w,va,vb);
     else /* ͼ */
       scanf("%s%s",va,vb);
     i=LocateVex(*G,va); /* ��β */
     j=LocateVex(*G,vb); /* ��ͷ */
     e.info=NULL; /* ���������e��ֵ��ͼ��Ȩ */
     e.adjvex=j; /* ��ͷ */
     if((*G).kind%2) /* �� */
     {
       e.info=(int *)malloc(sizeof(int)); /* ��̬���ɴ��Ȩֵ�Ŀռ� */
       *(e.info)=w;
     }
     ListInsert(&(*G).vertices[i].firstarc,1,e); /* ���ڵ�i��Ԫ��(����)�ı�ͷ����bo2-8.c�� */
     if((*G).kind>=2) /* ����ͼ������������2�����㣬�����ڵ�j��Ԫ��(�뻡)�ı�ͷ */
     {
       e.adjvex=i; /* e.info���䣬�����ٸ�ֵ */
       ListInsert(&(*G).vertices[j].firstarc,1,e); /* ���ڵ�j��Ԫ�صı�ͷ����bo2-8.c�� */
     }
   }
 }

 void CreateGraphF(ALGraph *G)
 { /* �����ڽӱ� �洢�ṹ�����ļ�����û�������Ϣͼ����G(��һ����������4��ͼ) */
   int i,j,k,w; /* w��Ȩֵ */
   VertexType va,vb; /* ���ӱ߻򻡵�2���� */
   ElemType e;
   char filename[13];
   FILE *graphlist;
   printf("�����������ļ���(f7-1.txt��f7-2.txt)��");
   scanf("%s",filename);
   printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3): ");
   scanf("%d",&(*G).kind);
   graphlist=fopen(filename,"r"); /* �Զ��ķ�ʽ�������ļ�������graphlist��ʾ */
   fscanf(graphlist,"%d",&(*G).vexnum);
   fscanf(graphlist,"%d",&(*G).arcnum);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
   {
     fscanf(graphlist,"%s",(*G).vertices[i].data);
     (*G).vertices[i].firstarc=NULL; /* ��ʼ����ö����йصĳ������� */
   }
   for(k=0;k<(*G).arcnum;++k) /* ������ػ����� */
   {
     if((*G).kind%2) /* �� */
       fscanf(graphlist,"%d%s%s",&w,va,vb);
     else /* ͼ */
       fscanf(graphlist,"%s%s",va,vb);
     i=LocateVex(*G,va); /* ��β */
     j=LocateVex(*G,vb); /* ��ͷ */
     e.info=NULL; /* ���������e��ֵ��ͼ��Ȩ */
     e.adjvex=j; /* ��ͷ */
     if((*G).kind%2) /* �� */
     {
       e.info=(int *)malloc(sizeof(int)); /* ��̬���ɴ��Ȩֵ�Ŀռ� */
       *(e.info)=w;
     }
     ListInsert(&(*G).vertices[i].firstarc,1,e); /* ���ڵ�i��Ԫ��(����)�ı�ͷ����bo2-8.c�� */
     if((*G).kind>=2) /* ����ͼ������������2�����㣬�����ڵ�j��Ԫ��(�뻡)�ı�ͷ */
     {
       e.adjvex=i; /* e.info���䣬�����ٸ�ֵ */
       ListInsert(&(*G).vertices[j].firstarc,1,e); /* ���ڵ�j��Ԫ�صı�ͷ����bo2-8.c�� */
     }
   }
   fclose(graphlist); /* �ر������ļ� */
 }

 void DestroyGraph(ALGraph *G)
 { /* ��ʼ������ͼG���ڡ��������������ͼG */
   int i;
   ElemType e;
   for(i=0;i<(*G).vexnum;++i) /* �������ж��� */
     if((*G).kind%2) /* �� */
       while((*G).vertices[i].firstarc) /* ��Ӧ�Ļ���������� */
       {
	 ListDelete(&(*G).vertices[i].firstarc,1,&e); /* ɾ������ĵ�1����㣬����ֵ����e */
         if(e.adjvex>i) /* �������>i(��֤��̬���ɵ�Ȩֵ�ռ�ֻ�ͷ�1��) */
           free(e.info);
       }
     else /* ͼ */
       DestroyList(&(*G).vertices[i].firstarc); /* ���ٻ����������bo2-8.c�� */
   (*G).vexnum=0; /* ������Ϊ0 */
   (*G).arcnum=0; /* �߻���Ϊ0 */
 }

 VertexType* GetVex(ALGraph G,int v)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ���������š��������������v��ֵ */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.vertices[v].data;
 }

 Status PutVex(ALGraph *G,VertexType v,VertexType value)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ�����㡣�����������v����ֵvalue */
   int i;
   i=LocateVex(*G,v);
   if(i>-1) /* v��G�Ķ��� */
   {
     strcpy((*G).vertices[i].data,value);
     return OK;
   }
   return ERROR;
 }

 int FirstAdjVex(ALGraph G,VertexType v)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ������ */
   /* �������������v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1 */
   LinkList p;
   int v1;
   v1=LocateVex(G,v); /* v1Ϊ����v��ͼG�е���� */
   p=G.vertices[v1].firstarc;
   if(p)
     return p->data.adjvex;
   else
     return -1;
 }

 Status equalvex(ElemType a,ElemType b)
 { /* DeleteArc()��DeleteVex()��NextAdjVex()Ҫ���õĺ��� */
   if(a.adjvex==b.adjvex)
     return OK;
   else
     return ERROR;
 }

 int NextAdjVex(ALGraph G,VertexType v,VertexType w)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ�����㣬w��v���ڽӶ��� */
   /* �������������v��(�����w��)��һ���ڽӶ������š���w��v�����һ���ڽӵ㣬�򷵻�-1 */
   LinkList p,p1; /* p1��Point()����������ָ�룬Point()��func2-1.c�� */
   ElemType e;
   int v1;
   v1=LocateVex(G,v); /* v1Ϊ����v��ͼG�е���� */
   e.adjvex=LocateVex(G,w); /* e.adjvexΪ����w��ͼG�е���� */
   p=Point(G.vertices[v1].firstarc,e,equalvex,&p1); /* pָ�򶥵�v���������ڽӶ���Ϊw�Ľ�� */
   if(!p||!p->next) /* û�ҵ�w��w�����һ���ڽӵ� */
     return -1;
   else /* p->data.adjvex==w */
     return p->next->data.adjvex; /* ����v��(�����w��)��һ���ڽӶ������� */
 }

 void InsertVex(ALGraph *G,VertexType v)
 { /* ��ʼ������ͼG���ڣ�v��ͼ�ж�������ͬ���� */
   /* �����������ͼG�������¶���v(�������붥����صĻ�������InsertArc()ȥ��) */
   strcpy((*G).vertices[(*G).vexnum].data,v); /* �����¶������� */
   (*G).vertices[(*G).vexnum].firstarc=NULL;
   (*G).vexnum++; /* ͼG�Ķ�������1 */
 }

 Status DeleteVex(ALGraph *G,VertexType v)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ�����㡣���������ɾ��G�ж���v������صĻ� */
   int i,j,k;
   ElemType e;
   LinkList p,p1;
   j=LocateVex(*G,v); /* j�Ƕ���v����� */
   if(j<0) /* v����ͼG�Ķ��� */
     return ERROR;
   i=ListLength((*G).vertices[j].firstarc); /* ��vΪ���ȵĻ����������bo2-8.c�� */
   (*G).arcnum-=i; /* �߻���-i */
   if((*G).kind%2) /* �� */
     while((*G).vertices[j].firstarc) /* ��Ӧ�Ļ���������� */
     {
       ListDelete(&(*G).vertices[j].firstarc,1,&e); /* ɾ������ĵ�1����㣬����ֵ����e */
       free(e.info); /* �ͷŶ�̬���ɵ�Ȩֵ�ռ� */
     }
   else /* ͼ */
     DestroyList(&(*G).vertices[i].firstarc); /* ���ٻ����������bo2-8.c�� */
   (*G).vexnum--; /* ��������1 */
   for(i=j;i<(*G).vexnum;i++) /* ����v����Ķ���ǰ�� */
     (*G).vertices[i]=(*G).vertices[i+1];
   for(i=0;i<(*G).vexnum;i++) /* ɾ����vΪ��ȵĻ�����ұ�Ҫʱ�޸ı���Ķ���λ��ֵ */
   {
     e.adjvex=j;
     p=Point((*G).vertices[i].firstarc,e,equalvex,&p1); /* Point()��func2-1.c�� */
     if(p) /* ����i���ڽӱ�����vΪ��ȵĽ�� */
     {
       if(p1) /* p1ָ��p��ָ����ǰ�� */
         p1->next=p->next; /* ��������ɾ��p��ָ��� */
       else /* pָ����Ԫ��� */
         (*G).vertices[i].firstarc=p->next; /* ͷָ��ָ����һ��� */
       if((*G).kind<2) /* ���� */
       {
         (*G).arcnum--; /* �߻���-1 */
         if((*G).kind==1) /* ������ */
           free(p->data.info); /* �ͷŶ�̬���ɵ�Ȩֵ�ռ� */
       }
       free(p); /* �ͷ�vΪ��ȵĽ�� */
     }
     for(k=j+1;k<=(*G).vexnum;k++) /* ����adjvex��>j�Ľ�㣬�����-1 */
     {
       e.adjvex=k;
       p=Point((*G).vertices[i].firstarc,e,equalvex,&p1); /* Point()��func2-1.c�� */
       if(p)
         p->data.adjvex--; /* ���-1(��Ϊǰ��) */
     }
   }
   return OK;
 }

 Status InsertArc(ALGraph *G,VertexType v,VertexType w)
 { /* ��ʼ������ͼG���ڣ�v��w��G���������� */
   /* �����������G������<v,w>����G������ģ�������Գƻ�<w,v> */
   ElemType e;
   int i,j;
   i=LocateVex(*G,v); /* ��β��ߵ���� */
   j=LocateVex(*G,w); /* ��ͷ��ߵ���� */
   if(i<0||j<0)
     return ERROR;
   (*G).arcnum++; /* ͼG�Ļ���ߵ���Ŀ��1 */
   e.adjvex=j;
   e.info=NULL; /* ��ֵ */
   if((*G).kind%2) /* �� */
   {
     e.info=(int *)malloc(sizeof(int)); /* ��̬���ɴ��Ȩֵ�Ŀռ� */
     printf("�����뻡(��)%s��%s��Ȩֵ: ",v,w);
     scanf("%d",e.info);
   }
   ListInsert(&(*G).vertices[i].firstarc,1,e); /* ��e���ڻ�β�ı�ͷ����bo2-8.c�� */
   if((*G).kind>=2) /* ����������һ������ */
   {
     e.adjvex=i; /* e.info���� */
     ListInsert(&(*G).vertices[j].firstarc,1,e); /* ��e���ڻ�ͷ�ı�ͷ */
   }
   return OK;
 }

 Status DeleteArc(ALGraph *G,VertexType v,VertexType w)
 { /* ��ʼ������ͼG���ڣ�v��w��G���������� */
   /* �����������G��ɾ����<v,w>����G������ģ���ɾ���Գƻ�<w,v> */
   int i,j;
   Status k;
   ElemType e;
   i=LocateVex(*G,v); /* i�Ƕ���v(��β)����� */
   j=LocateVex(*G,w); /* j�Ƕ���w(��ͷ)����� */
   if(i<0||j<0||i==j)
     return ERROR;
   e.adjvex=j;
   k=DeleteElem(&(*G).vertices[i].firstarc,&e,equalvex); /* ��func2-1.c�� */
   if(k) /* ɾ���ɹ� */
   {
     (*G).arcnum--; /* ���������1 */
     if((*G).kind%2) /* �� */
       free(e.info);
     if((*G).kind>=2) /* ����ɾ���Գƻ�<w,v> */
     {
       e.adjvex=i;
       DeleteElem(&(*G).vertices[j].firstarc,&e,equalvex);
     }
     return OK;
   }
   else /* û�ҵ���ɾ���Ļ� */
     return ERROR;
 }

 void DFS(ALGraph G,int v)
 { /* �ӵ�v����������ݹ��������ȱ���ͼG���㷨7.5 */
   int w;
   visited[v]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
   VisitFunc(G.vertices[v].data); /* ���ʵ�v������ */
   for(w=FirstAdjVex(G,G.vertices[v].data);w>=0;w=NextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
     if(!visited[w])
       DFS(G,w); /* ��v����δ���ʵ��ڽӵ�w�ݹ����DFS */
 }

 void DFSTraverse(ALGraph G,void(*Visit)(char*))
 { /* ��ͼG��������ȱ������㷨7.4 */
   int v;
   VisitFunc=Visit; /* ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ����� */
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* ���ʱ�־�����ʼ�� */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); /* ����δ���ʵĶ������DFS */
   printf("\n");
 }

  void InitQueue(LinkQueue *Q)
 { /* ����һ���ն���Q */
   (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
   if(!(*Q).front)
     exit(OVERFLOW);
   (*Q).front->next=NULL;
 }

 void DestroyQueue(LinkQueue *Q)
 { /* ���ٶ���Q(���ۿշ����) */
   while((*Q).front)
   {
     (*Q).rear=(*Q).front->next;
     free((*Q).front);
     (*Q).front=(*Q).rear;
   }
 }

 void ClearQueue(LinkQueue *Q)
 { /* ��Q��Ϊ�ն��� */
   QueuePtr p,q;
   (*Q).rear=(*Q).front;
   p=(*Q).front->next;
   (*Q).front->next=NULL;
   while(p)
   {
     q=p;
     p=p->next;
     free(q);
   }
 }

 Status QueueEmpty(LinkQueue Q)
 { /* ��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE */
   if(Q.front->next==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(LinkQueue Q)
 { /* ����еĳ��� */
   int i=0;
   QueuePtr p;
   p=Q.front;
   while(Q.rear!=p)
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetHead_Q(LinkQueue Q,QElemType *e) /* ������bo2-6.c���� */
 { /* �����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR */
   QueuePtr p;
   if(Q.front==Q.rear)
     return ERROR;
   p=Q.front->next;
   *e=p->data;
   return OK;
 }

 void EnQueue(LinkQueue *Q,QElemType e)
 { /* ����Ԫ��eΪQ���µĶ�βԪ�� */
   QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
   if(!p) /* �洢����ʧ�� */
     exit(OVERFLOW);
   p->data=e;
   p->next=NULL;
   (*Q).rear->next=p;
   (*Q).rear=p;
 }

 Status DeQueue(LinkQueue *Q,QElemType *e)
 { /* �����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
   QueuePtr p;
   if((*Q).front==(*Q).rear)
     return ERROR;
   p=(*Q).front->next;
   *e=p->data;
   (*Q).front->next=p->next;
   if((*Q).rear==p)
     (*Q).rear=(*Q).front;
   free(p);
   return OK;
 }

 void QueueTraverse(LinkQueue Q,void(*vi)(QElemType))
 { /* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi() */
   QueuePtr p;
   p=Q.front->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
 }
 
 void BFSTraverse(ALGraph G,void(*Visit)(char*))
 {/*��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited���㷨7.6 */
   int v,u,w;
   LinkQueue Q;
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; /* �ó�ֵ */
   InitQueue(&Q); /* �ÿյĸ�������Q */
   for(v=0;v<G.vexnum;v++) /* �������ͨͼ��ֻv=0�ͱ���ȫͼ */
     if(!visited[v]) /* v��δ���� */
     {
       visited[v]=TRUE;
       Visit(G.vertices[v].data);
       EnQueue(&Q,v); /* v����� */
       while(!QueueEmpty(Q)) /* ���в��� */
       {
         DeQueue(&Q,&u); /* ��ͷԪ�س��Ӳ���Ϊu */
         for(w=FirstAdjVex(G,G.vertices[u].data);w>=0;w=NextAdjVex(G,G.vertices[u].data,G.vertices[w].data))
           if(!visited[w]) /* wΪu����δ���ʵ��ڽӶ��� */
           {
             visited[w]=TRUE;
             Visit(G.vertices[w].data);
             EnQueue(&Q,w); /* w��� */
           }
       }
     }
   printf("\n");
 }

 void DFS1(ALGraph G,int v,void(*Visit)(char*))
 { /* �ӵ�v����������ݹ��������ȱ���ͼG�����������ڽӱ�洢�ṹ */
   ArcNode *p; /* pָ����� */
   visited[v]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
   Visit(G.vertices[v].data); /* ���ʸö��� */
   for(p=G.vertices[v].firstarc;p;p=p->next) /* p����ָ��v���ڽӶ��� */
     if(!visited[p->data.adjvex])
       DFS1(G,p->data.adjvex,Visit); /* ��v����δ���ʵ��ڽӵ�ݹ����DFS1 */
 }

 void DFSTraverse1(ALGraph G,void(*Visit)(char*))
 { /* ��ͼG��������ȱ�����DFS1�躯��ָ����� */
   int v;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* ���ʱ�־�����ʼ�����ó�ֵΪδ������ */
   for(v=0;v<G.vexnum;v++) /* �������ͨͼ��ֻv=0�ͱ���ȫͼ */
     if(!visited[v]) /* v��δ������ */
       DFS1(G,v,Visit); /* ��v����DFS1 */
   printf("\n");
 }

 void BFSTraverse1(ALGraph G,void(*Visit)(char*))
 { /* ��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited�����������ڽӱ�ṹ */
   int v,u;
   ArcNode *p; /* pָ����� */
   LinkQueue Q; /* ���������� */
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; /* �ó�ֵΪδ������ */
   InitQueue(&Q); /* ��ʼ����������Q */
   for(v=0;v<G.vexnum;v++) /* �������ͨͼ��ֻv=0�ͱ���ȫͼ */
     if(!visited[v]) /* v��δ������ */
     {
       visited[v]=TRUE; /* ��vΪ�ѱ����� */
       Visit(G.vertices[v].data); /* ����v */
       EnQueue(&Q,v); /* v����� */
       while(!QueueEmpty(Q)) /* ���в��� */
       {
         DeQueue(&Q,&u); /* ��ͷԪ�س��Ӳ���Ϊu */
         for(p=G.vertices[u].firstarc;p;p=p->next) /* p����ָ��u���ڽӶ��� */
           if(!visited[p->data.adjvex]) /* u���ڽӶ�����δ������ */
           {
             visited[p->data.adjvex]=TRUE; /* ���ڽӶ�����Ϊ�ѱ����� */
             Visit(G.vertices[p->data.adjvex].data); /* ���ʸ��ڽӶ��� */
             EnQueue(&Q,p->data.adjvex); /* ��Ӹ��ڽӶ������ */
           }
       }
     }
   printf("\n");
 }

 void Display(ALGraph G)
 { /* ���ͼ���ڽӾ���G */
   int i;
   LinkList p;
   switch(G.kind)
   {
     case DG: printf("����ͼ\n");
	      break;
     case DN: printf("������\n");
              break;
     case UDG:printf("����ͼ\n");
              break;
     case UDN:printf("������\n");
   }
   printf("%d�����㣺\n",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     printf("%s ",G.vertices[i].data);
   printf("\n%d����(��):\n",G.arcnum);
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       if(G.kind<=1||i<p->data.adjvex) /* ��������������е�һ�� */
       {
         printf("%s��%s ",G.vertices[i].data,G.vertices[p->data.adjvex].data);
	 if(G.kind%2) /* �� */
           printf(":%d ",*(p->data.info));
       }
       p=p->nextarc;
     }
     printf("\n");
   }
 }

 void DFSArticul(ALGraph G,int v0)
 { /* �ӵ�v0���������������ȱ���ͼG�����Ҳ�����ؽڵ� */
   int min,w;
   ArcNode *p;
   visited[v0]=min=++count;
   /* v0�ǵ�count�����ʵĶ��㣬visited[]��ȫ�ֱ���,��bo7-2.c�ж���,min�ĳ�ֵΪv0�ķ���˳�� */
   for(p=G.vertices[v0].firstarc;p;p=p->nextarc) /* ���ζ�v0��ÿ���ڽӶ����� */
   {
     w=p->data.adjvex; /* wΪv0���ڽӶ���λ�� */
     if(visited[w]==0) /* wδ�����ʣ���v0�ĺ��� */
     {
       DFSArticul(G,w);
       /* �ӵ�w���������������ȱ���ͼG�����Ҳ�����ؽڵ㡣����ǰ���low[w] */
       if(low[w]<min) /* ���v0�ĺ��ӽ��w��low[]С����˵�����ӽ�㻹���������(����)���� */
	 min=low[w]; /* ȡminֵΪ���ӽ���low[]����v0���ǹؽڵ� */
       else if(low[w]>=visited[v0]) /* v0�ĺ��ӽ��wֻ��v0��������v0�ǹؽڵ� */
	 printf("%d %s\n",v0,G.vertices[v0].data); /* ����ؽڵ�v0 */
     }
     else if(visited[w]<min) /* w�ѷ��ʣ���w��v0���������ϵ����ȣ����ķ���˳���С��min */
       min=visited[w]; /* ��ȡminΪvisited[w] */
   }
   low[v0]=min; /* vo��low[]ֵΪ�����е���Сֵ */
   lowOrder[v0]=lowcount++; /* ��¼v0���low[]ֵ��˳��(����),�����ڷ�����������֮ǰ���low[] */
 }

 void FindArticul(ALGraph G)
 { /* ��ͨͼG���ڽӱ����洢�ṹ�����Ҳ����G��ȫ���ؽڵ㡣ȫ����count�Է��ʼ������㷨7.10 */
   int i,v;
   ArcNode *p;
   count=1; /* ����˳�� */
   visited[0]=count; /* �趨�ڽӱ���0�Ŷ���Ϊ�������ĸ�����1�������� */
   for(i=1;i<G.vexnum;++i)
     visited[i]=0; /* ���ඥ����δ���ʣ����ֵΪ0 */
   p=G.vertices[0].firstarc; /* pָ������ĵ�1���ڽӶ��� */
   v=p->data.adjvex; /* v�Ǹ����ĵ�1���ڽӶ������� */
   DFSArticul(G,v); /* �ӵ�v�������������Ȳ��ҹؽڵ� */
   if(count<G.vexnum) /* �ɸ����ĵ�1���ڽӶ���������ȱ���G�����ʵĶ���������G�Ķ����� */
   { /* ˵���������ĸ���������������������ǹؽڵ� */
     printf("%d %s\n",0,G.vertices[0].data); /* ���ǹؽڵ㣬����� */
     while(p->nextarc) /* ������һ���ڽӵ� */
     {
       p=p->nextarc; /* pָ�������һ���ڽӵ� */
       v=p->data.adjvex;
       if(visited[v]==0) /* ���ڽӵ�δ������ */
	 DFSArticul(G,v); /* �Ӵ˶������������Ȳ��ҹؽڵ� */
     }
   }
 }

 int main()
 {
   int i;
   ALGraph g;
   printf("��ѡ������ͼ\n");
   CreateGraph(&g); /* ��������ͼg */
   Display(g); /* �������ͼg */
   printf("����ؽڵ㣺\n");
   FindArticul(g); /* ����ͨͼg�Ĺؽڵ� */
   printf(" i G.vertices[i].data visited[i] low[i] lowOrder[i]\n"); /* ����������� */
   for(i=0;i<g.vexnum;++i)
     printf("%2d %9s %14d %8d %8d\n",i,g.vertices[i].data,visited[i],low[i],lowOrder[i]);
     
   return 0; 
 }
 
 
