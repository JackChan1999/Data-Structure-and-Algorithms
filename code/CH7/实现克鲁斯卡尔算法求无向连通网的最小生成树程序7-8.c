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
 typedef int VRType;
 typedef char InfoType;
 #define MAX_NAME 3 /* �����ַ�������󳤶�+1 */
 #define MAX_INFO 20 /* �����Ϣ�ַ�������󳤶�+1 */
 typedef char VertexType[MAX_NAME];
 
 #define INFINITY INT_MAX /* ���������ֵ����� */
 #define MAX_VERTEX_NUM 26 /* ��󶥵���� */
 typedef enum{DG,DN,UDG,UDN}GraphKind; /* {����ͼ,������,����ͼ,������} */
 typedef struct
 {
   VRType adj; /* �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ */
   InfoType *info; /* �û������Ϣ��ָ��(����) */
 }ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /* ��ά���� */
 typedef struct
 {
   VertexType vexs[MAX_VERTEX_NUM]; /* �������� */
   AdjMatrix arcs; /* �ڽӾ��� */
   int vexnum,arcnum; /* ͼ�ĵ�ǰ�������ͻ��� */
   GraphKind kind; /* ͼ�������־ */
 }MGraph;
 Boolean visited[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */
 void(*VisitFunc)(VertexType); /* �������� */
 typedef VRType QElemType; /* ����Ԫ������ */
 typedef struct QNode
 {
   QElemType data;
   struct QNode *next;
 }QNode,*QueuePtr;

 typedef struct
 {
   QueuePtr front,rear; /* ��ͷ����βָ�� */
 }LinkQueue;
 
 int LocateVex(MGraph G,VertexType u)
 { /* ��ʼ������ͼG���ڣ�u��G�ж�������ͬ���� */
   /* �����������G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vexs[i])==0)
       return i;
   return -1;
 }

 void CreateFUDG(MGraph *G)
 { /* ��������(�ڽӾ���)��ʾ�������ļ�����û�������Ϣ������ͼG */
   int i,j,k;
   char filename[13];
   VertexType va,vb;
   FILE *graphlist;
   printf("�����������ļ���(f7-1.txt��f7-2.txt)��");
   scanf("%s",filename);
   graphlist=fopen(filename,"r");/* �������ļ�������graphlist��ʾ */
   fscanf(graphlist,"%d",&(*G).vexnum);
   fscanf(graphlist,"%d",&(*G).arcnum);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
     fscanf(graphlist,"%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* ͼ */
       (*G).arcs[i][j].info=NULL; /* û�������Ϣ */
     }
   for(k=0;k<(*G).arcnum;++k)
   {
     fscanf(graphlist,"%s%s",va,vb);
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* ����ͼ */
   }
   fclose(graphlist); /* �ر������ļ� */
   (*G).kind=UDG;
 }

 void CreateFUDN(MGraph *G)
 { /* ��������(�ڽӾ���)��ʾ�������ļ�����û�������Ϣ��������G */
   int i,j,k,w;
   char filename[13];
   VertexType va,vb;
   FILE *graphlist;
   printf("�����������ļ�����");
   scanf("%s",filename);
   graphlist=fopen(filename,"r"); /* �������ļ�������graphlist��ʾ */
   fscanf(graphlist,"%d",&(*G).vexnum);
   fscanf(graphlist,"%d",&(*G).arcnum);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
     fscanf(graphlist,"%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=INFINITY; /* �� */
       (*G).arcs[i][j].info=NULL; /* û�������Ϣ */
     }
   for(k=0;k<(*G).arcnum;++k)
   {
     fscanf(graphlist,"%s%s%d",va,vb,&w);
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* ������ */
   }
   fclose(graphlist); /* �ر������ļ� */
   (*G).kind=UDN;
 }

 void CreateDG(MGraph *G)
 { /* ��������(�ڽӾ���)��ʾ������������ͼG */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO];
   VertexType va,vb;
   printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* ͼ */
       (*G).arcs[i][j].info=NULL;
     }
   printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%*c",va,vb);  /* %*c�Ե��س��� */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=1; /* ����ͼ */
     if(IncInfo)
     {
       printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         (*G).arcs[i][j].info=(char*)malloc((l+1)*sizeof(char)); /* ���� */
         strcpy((*G).arcs[i][j].info,s);
       }
     }
   }
   (*G).kind=DG;
 }

 void CreateDN(MGraph *G)
 { /* ��������(�ڽӾ���)��ʾ��������������G */
   int i,j,k,w,IncInfo;
   char s[MAX_INFO];
   VertexType va,vb;
   printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=INFINITY; /* �� */
       (*G).arcs[i][j].info=NULL;
     }
   printf("������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w);  /* %*c�Ե��س��� */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=w; /* ������ */
     if(IncInfo)
     {
       printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         (*G).arcs[i][j].info=(char*)malloc((w+1)*sizeof(char)); /* ���� */
         strcpy((*G).arcs[i][j].info,s);
       }
     }
   }
   (*G).kind=DN;
 }

 void CreateUDG(MGraph *G)
 { /* ��������(�ڽӾ���)��ʾ������������ͼG */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO];
   VertexType va,vb;
   printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* ͼ */
       (*G).arcs[i][j].info=NULL;
     }
   printf("������%d���ߵĶ���1 ����2(�Կո���Ϊ���): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%*c",va,vb); /* %*c�Ե��س��� */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* ����ͼ */
     if(IncInfo)
     {
       printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         (*G).arcs[i][j].info=(*G).arcs[j][i].info=(char*)malloc((l+1)*sizeof(char));
	 /* ��������ָ��ָ��ͬһ����Ϣ */
         strcpy((*G).arcs[i][j].info,s);
       }
     }
   }
   (*G).kind=UDG;
 }

 void CreateUDN(MGraph *G)
 { /* ��������(�ڽӾ���)��ʾ��������������G���㷨7.2 */
   int i,j,k,w,IncInfo;
   char s[MAX_INFO];
   VertexType va,vb;
   printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=INFINITY; /* �� */
       (*G).arcs[i][j].info=NULL;
     }
   printf("������%d���ߵĶ���1 ����2 Ȩֵ(�Կո���Ϊ���): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w); /* %*c�Ե��س��� */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* ���� */
     if(IncInfo)
     {
       printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         (*G).arcs[i][j].info=(*G).arcs[j][i].info=(char*)malloc((w+1)*sizeof(char));
         /* ��������ָ��ָ��ͬһ����Ϣ */
         strcpy((*G).arcs[i][j].info,s);
       }
     }
   }
   (*G).kind=UDN;
 }

 void CreateGraph(MGraph *G)
 { /* ��������(�ڽӾ���)��ʾ��������ͼG���㷨7.1�� */
   printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3): ");
   scanf("%d",&(*G).kind);
   switch((*G).kind)
   {
     case DG: CreateDG(G); /* ��������ͼ */
              break;
     case DN: CreateDN(G); /* ���������� */
              break;
     case UDG:CreateUDG(G); /* ��������ͼ */
              break;
     case UDN:CreateUDN(G); /* ���������� */
   }
 }

 void DestroyGraph(MGraph *G)
 { /* ��ʼ������ͼG���ڡ��������������ͼG */
   int i,j,k=0;
   if((*G).kind%2) /* �� */
     k=INFINITY; /* kΪ������֮���ޱ߻�ʱ�ڽӾ���Ԫ�ص�ֵ */
   for(i=0;i<(*G).vexnum;i++) /* �ͷŻ���ߵ������Ϣ(����еĻ�) */
     if((*G).kind<2) /* ���� */
     {
       for(j=0;j<(*G).vexnum;j++)
         if((*G).arcs[i][j].adj!=k) /* �л� */
           if((*G).arcs[i][j].info) /* �������Ϣ */
           {
             free((*G).arcs[i][j].info);
             (*G).arcs[i][j].info=NULL;
           }
     } /* ������Ϊ����if-else����� */
     else /* ���� */
       for(j=i+1;j<(*G).vexnum;j++) /* ֻ�������� */
         if((*G).arcs[i][j].adj!=k) /* �б� */
           if((*G).arcs[i][j].info) /* �������Ϣ */
           {
             free((*G).arcs[i][j].info);
             (*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
           }
   (*G).vexnum=0; /* ������Ϊ0 */
   (*G).arcnum=0; /* ����Ϊ0 */
 }

 VertexType* GetVex(MGraph G,int v)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ���������š��������������v��ֵ */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.vexs[v];
 }

 Status PutVex(MGraph *G,VertexType v,VertexType value)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ�����㡣�����������v����ֵvalue */
   int k;
   k=LocateVex(*G,v); /* kΪ����v��ͼG�е���� */
   if(k<0)
     return ERROR;
   strcpy((*G).vexs[k],value);
   return OK;
 }

 int FirstAdjVex(MGraph G,VertexType v)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ������ */
   /* �������������v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1 */
   int i,j=0,k;
   k=LocateVex(G,v); /* kΪ����v��ͼG�е���� */
   if(G.kind%2) /* �� */
     j=INFINITY;
   for(i=0;i<G.vexnum;i++)
     if(G.arcs[k][i].adj!=j)
       return i;
   return -1;
 }

 int NextAdjVex(MGraph G,VertexType v,VertexType w)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ�����㣬w��v���ڽӶ��� */
   /* �������������v��(�����w��)��һ���ڽӶ������ţ���w��v�����һ���ڽӶ��㣬�򷵻�-1 */
   int i,j=0,k1,k2;
   k1=LocateVex(G,v); /* k1Ϊ����v��ͼG�е���� */
   k2=LocateVex(G,w); /* k2Ϊ����w��ͼG�е���� */
   if(G.kind%2) /* �� */
     j=INFINITY;
   for(i=k2+1;i<G.vexnum;i++)
     if(G.arcs[k1][i].adj!=j)
       return i;
   return -1;
 }

 void InsertVex(MGraph *G,VertexType v)
 { /* ��ʼ������ͼG���ڣ�v��ͼG�ж�������ͬ���� */
   /* �����������ͼG�������¶���v(�������붥����صĻ�������InsertArc()ȥ��) */
   int i,j=0;
   if((*G).kind%2) /* �� */
     j=INFINITY;
   strcpy((*G).vexs[(*G).vexnum],v); /* �����¶������� */
   for(i=0;i<=(*G).vexnum;i++)
   {
     (*G).arcs[(*G).vexnum][i].adj=(*G).arcs[i][(*G).vexnum].adj=j;
     /* ��ʼ�������С��������ڽӾ����ֵ(�ޱ߻�) */
     (*G).arcs[(*G).vexnum][i].info=(*G).arcs[i][(*G).vexnum].info=NULL; /* ��ʼ�������Ϣָ�� */
   }
   (*G).vexnum++; /* ͼG�Ķ�������1 */
 }

 Status DeleteVex(MGraph *G,VertexType v)
 { /* ��ʼ������ͼG���ڣ�v��G��ĳ�����㡣���������ɾ��G�ж���v������صĻ� */
   int i,j,k;
   VRType m=0;
   if((*G).kind%2) /* �� */
     m=INFINITY;
   k=LocateVex(*G,v); /* kΪ��ɾ������v����� */
   for(j=0;j<(*G).vexnum;j++)
     if((*G).arcs[j][k].adj!=m) /* ���뻡��� */
     {
       if((*G).arcs[j][k].info) /* �������Ϣ */
         free((*G).arcs[j][k].info); /* �ͷ������Ϣ */
       (*G).arcnum--; /* �޸Ļ��� */
     }
   if((*G).kind<2) /* ���� */
     for(j=0;j<(*G).vexnum;j++)
       if((*G).arcs[k][j].adj!=m) /* �г��� */
       {
         if((*G).arcs[k][j].info) /* �������Ϣ */
           free((*G).arcs[k][j].info); /* �ͷ������Ϣ */
         (*G).arcnum--; /* �޸Ļ��� */
       }
   for(j=k+1;j<(*G).vexnum;j++) /* ���k����Ķ�����������ǰ�� */
     strcpy((*G).vexs[j-1],(*G).vexs[j]);
   for(i=0;i<(*G).vexnum;i++)
     for(j=k+1;j<(*G).vexnum;j++)
       (*G).arcs[i][j-1]=(*G).arcs[i][j]; /* �ƶ���ɾ������֮��ľ���Ԫ�� */
   for(i=0;i<(*G).vexnum;i++)
     for(j=k+1;j<(*G).vexnum;j++)
       (*G).arcs[j-1][i]=(*G).arcs[j][i]; /* �ƶ���ɾ������֮�µľ���Ԫ�� */
   (*G).vexnum--; /* ����ͼ�Ķ����� */
   return OK;
 }

 Status InsertArc(MGraph *G,VertexType v,VertexType w)
 { /* ��ʼ������ͼG���ڣ�v��w��G���������� */
   /* �����������G������<v,w>����G������ģ�������Գƻ�<w,v> */
   int i,l,v1,w1;
   char s[MAX_INFO];
   v1=LocateVex(*G,v); /* β */
   w1=LocateVex(*G,w); /* ͷ */
   if(v1<0||w1<0)
     return ERROR;
   (*G).arcnum++; /* ���������1 */
   if((*G).kind%2) /* �� */
   {
     printf("������˻���ߵ�Ȩֵ: ");
     scanf("%d",&(*G).arcs[v1][w1].adj);
   }
   else /* ͼ */
     (*G).arcs[v1][w1].adj=1;
   printf("�Ƿ��иû���ߵ������Ϣ(0:�� 1:��): ");
   scanf("%d%*c",&i);
   if(i)
   {
     printf("������û���ߵ������Ϣ(<%d���ַ�)��",MAX_INFO);
     gets(s);
     l=strlen(s);
     if(l)
     {
       (*G).arcs[v1][w1].info=(char*)malloc((l+1)*sizeof(char));
       strcpy((*G).arcs[v1][w1].info,s);
     }
   }
   if((*G).kind>1) /* ���� */
   {
     (*G).arcs[w1][v1].adj=(*G).arcs[v1][w1].adj;
     (*G).arcs[w1][v1].info=(*G).arcs[v1][w1].info; /* ָ��ͬһ�������Ϣ */
   }
   return OK;
 }

 Status DeleteArc(MGraph *G,VertexType v,VertexType w)
 { /* ��ʼ������ͼG���ڣ�v��w��G���������� */
   /* �����������G��ɾ����<v,w>����G������ģ���ɾ���Գƻ�<w,v> */
   int v1,w1,j=0;
   if((*G).kind%2) /* �� */
     j=INFINITY;
   v1=LocateVex(*G,v); /* β */
   w1=LocateVex(*G,w); /* ͷ */
   if(v1<0||w1<0) /* v1��w1��ֵ���Ϸ� */
     return ERROR;
   (*G).arcs[v1][w1].adj=j;
   if((*G).arcs[v1][w1].info) /* ��������Ϣ */
   {
     free((*G).arcs[v1][w1].info);
     (*G).arcs[v1][w1].info=NULL;
   }
   if((*G).kind>=2) /* ����ɾ���Գƻ�<w,v> */
   {
     (*G).arcs[w1][v1].adj=j;
     (*G).arcs[w1][v1].info=NULL;
   }
   (*G).arcnum--;
   return OK;
 }

 void DFS(MGraph G,int v)
 { /* �ӵ�v����������ݹ��������ȱ���ͼG���㷨7.5 */
   int w;
   visited[v]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
   VisitFunc(G.vexs[v]); /* ���ʵ�v������ */
   for(w=FirstAdjVex(G,G.vexs[v]);w>=0;w=NextAdjVex(G,G.vexs[v],G.vexs[w]))
     if(!visited[w])
       DFS(G,w); /* ��v����δ���ʵ����Ϊw���ڽӶ���ݹ����DFS */
 }

 void DFSTraverse(MGraph G,void(*Visit)(VertexType))
 { /* ��ʼ������ͼG���ڣ�Visit�Ƕ����Ӧ�ú������㷨7.4 */
   /* ����������ӵ�1��������������ȱ���ͼG������ÿ��������ú���Visitһ���ҽ�һ�� */
   int v;
   VisitFunc=Visit; /* ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ����� */
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* ���ʱ�־�����ʼ��(δ������) */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); /* ����δ���ʵĶ���v����DFS */
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
 
 void BFSTraverse(MGraph G,void(*Visit)(VertexType))
 { /* ��ʼ������ͼG���ڣ�Visit�Ƕ����Ӧ�ú������㷨7.6 */
   /* ����������ӵ�1�������𣬰�������ȷǵݹ����ͼG,����ÿ��������ú���Visitһ���ҽ�һ�� */
   int v,u,w;
   LinkQueue Q; /* ʹ�ø�������Q�ͷ��ʱ�־����visited */
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* �ó�ֵ */
   InitQueue(&Q); /* �ÿյĸ�������Q */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v]) /* v��δ���� */
     {
       visited[v]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
       Visit(G.vexs[v]);
       EnQueue(&Q,v); /* v����� */
       while(!QueueEmpty(Q)) /* ���в��� */
       {
         DeQueue(&Q,&u); /* ��ͷԪ�س��Ӳ���Ϊu */
         for(w=FirstAdjVex(G,G.vexs[u]);w>=0;w=NextAdjVex(G,G.vexs[u],G.vexs[w]))
           if(!visited[w]) /* wΪu����δ���ʵ��ڽӶ������� */
           {
             visited[w]=TRUE;
             Visit(G.vexs[w]);
             EnQueue(&Q,w);
           }
       }
     }
   printf("\n");
 }

 void Display(MGraph G)
 { /* ����ڽӾ���洢��ʾ��ͼG */
   int i,j;
   char s[7];
   switch(G.kind)
   {
     case DG: strcpy(s,"����ͼ");
              break;
     case DN: strcpy(s,"������");
              break;
     case UDG:strcpy(s,"����ͼ");
              break;
     case UDN:strcpy(s,"������");
   }
   printf("%d������%d���߻򻡵�%s������������: ",G.vexnum,G.arcnum,s);
   for(i=0;i<G.vexnum;++i) /* ���G.vexs */
     printf("%s ",G.vexs[i]);
   printf("\nG.arcs.adj:\n"); /* ���G.arcs.adj */
   for(i=0;i<G.vexnum;i++)
   {
     for(j=0;j<G.vexnum;j++)
       printf("%11d",G.arcs[i][j].adj);
     printf("\n");
   }
   printf("G.arcs.info:\n"); /* ���G.arcs.info */
   printf("����1(��β) ����2(��ͷ) �ñ߻򻡵���Ϣ��\n");
   for(i=0;i<G.vexnum;i++)
     if(G.kind<2) /* ���� */
     {
       for(j=0;j<G.vexnum;j++)
         if(G.arcs[i][j].info)
           printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
     } /* ������Ϊ����if-else����� */
     else /* ����,��������� */
       for(j=i+1;j<G.vexnum;j++)
         if(G.arcs[i][j].info)
           printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
 }
 
 void kruskal(MGraph G)
 {
   int set[MAX_VERTEX_NUM],i,j;
   int k=0,a=0,b=0,min=G.arcs[a][b].adj;
   for(i=0;i<G.vexnum;i++)
     set[i]=i; /* ��̬��������ֱ����ڸ������� */
   printf("��С�����������ĸ�����Ϊ:\n");
   while(k<G.vexnum-1) /* ��С�������ı���С�ڶ�����-1 */
   { /* Ѱ����СȨֵ�ı� */
     for(i=0;i<G.vexnum;++i)
       for(j=i+1;j<G.vexnum;++j) /* ��������ֻ�������ǲ��� */
         if(G.arcs[i][j].adj<min)
         {
           min=G.arcs[i][j].adj; /* ��СȨֵ */
           a=i; /* �ߵ�һ������ */
           b=j; /* �ߵ���һ������ */
         }
     min=G.arcs[a][b].adj=INFINITY; /* ɾ���������иñߣ��´β��ٲ��� */
     if(set[a]!=set[b]) /* �ߵ������㲻����ͬһ���� */
     {
       printf("%s-%s\n",G.vexs[a],G.vexs[b]); /* ����ñ� */
       k++; /* ����+1 */
       for(i=0;i<G.vexnum;i++)
         if(set[i]==set[b]) /* ������b���ڼ��ϲ��붥��a������ */
       set[i]=set[a];
     }
   }
 }

 int main()
 {
   MGraph g;
   CreateUDN(&g); /* ����������g */
   Display(g); /* ���������g */
   kruskal(g); /* �ÿ�³˹�����㷨���g����С�������ĸ����� */
  
   return 0; 
 }