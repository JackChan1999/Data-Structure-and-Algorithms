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
 
 #define NAMELEN 8 /* ������󳤶� */
 #define CLASSLEN 4 /* �༶����󳤶� */
 typedef struct
 {
   char name[NAMELEN+1]; /* ����'\0' */
   long num;
   char sex;
   int age;
   char Class[CLASSLEN+1]; /* ����'\0' */
   int health;
 }stud; /* ��¼�Ľṹ */
 typedef stud ElemType; /* ������Ԫ������Ϊ�ṹ�� */ 
 typedef struct LNode
 {
   ElemType data;
   struct LNode *next;
 };
 typedef struct LNode *LinkList; /* ��һ�ֶ���LinkList�ķ��� */
 
 #define DestroyList ClearList /* DestroyList()��ClearList()�Ĳ�����һ���� */
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
 
 char sta[3][9]={"����  ","һ��  ","��˥��"}; /* ����״��(3��) */
 FILE *fp; /* ȫ�ֱ��� */

 void Print(stud e)
 { /* ��ʾ��¼e������ */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" ��");
   else
     printf(" Ů");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

 void ReadIn(stud *e)
 { /* �ɼ�����������Ϣ */
   printf("����������(<=%d���ַ�): ",NAMELEN);
   scanf("%s",(*e).name);
   printf("������ѧ��: ");
   scanf("%ld",&(*e).num);
   printf("�������Ա�(m:�� f:Ů): ");
   scanf("%*c%c",&(*e).sex);
   printf("����������: ");
   scanf("%d",&(*e).age);
   printf("������༶(<=%d���ַ�): ",CLASSLEN);
   scanf("%s",(*e).Class);
   printf("�����뽡��״��(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   scanf("%d",&(*e).health);
 }

 void WriteToFile(stud e)
 { /* �������Ϣд��fpָ�����ļ� */
   fwrite(&e,sizeof(stud),1,fp);
 }

 Status ReadFromFile(stud *e)
 { /* ��fpָ�����ļ���ȡ�����Ϣ��e */
   int i;
   i=fread(e,sizeof(stud),1,fp);
   if(i==1) /* ��ȡ�ļ��ɹ� */
     return OK;
   else
     return ERROR;
 }

 int cmp(ElemType c1,ElemType c2)
 {
   return (int)(c1.num-c2.num);
 }

 void Modify(LinkList *L,ElemType e)
 { /* �޸Ľ�����ݣ�����ѧ�Ž����ǽ����������L */
   char s[80];
   Print(e); /* ��ʾԭ���� */
   printf("��������޸�������ݣ����޸ĵ���س�������ԭֵ:\n");
   printf("����������(<=%d���ַ�): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e.name,s);
   printf("������ѧ��: ");
   gets(s);
   if(strlen(s))
     e.num=atol(s);
   printf("�������Ա�(m:�� f:Ů): ");
   gets(s);
   if(strlen(s))
     e.sex=s[0];
   printf("����������: ");
   gets(s);
   if(strlen(s))
     e.age=atoi(s);
   printf("������༶(<=%d���ַ�): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e.Class,s);
   printf("�����뽡��״��(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e.health=atoi(s); /* �޸���� */
   InsertAscend(L,e,cmp); /* ��q��ָ�������ݰ�ѧ�ŷǽ������L(func2-1.c) */
 }

 #define N 4 /* student��¼�ĸ��� */

 Status EqualNum(ElemType c1,ElemType c2)
 {
   if(c1.num==c2.num)
     return OK;
   else
     return ERROR;
 }

 Status EqualName(ElemType c1,ElemType c2)
 {
   if(strcmp(c1.name,c2.name))
     return ERROR;
   else
     return OK;
 }

 int main()
 { /* ��ĳ�ʼ��¼ */
   stud student[N]={{"��С��",790631,'m',18,"��91",0},{"�º�",790632,'f',20,"��91",1},
                    {"����ƽ",790633,'m',21,"��91",0},{"������",790634,'m',17,"��91",2}};
   int i,j,flag=1;
   char filename[13];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* ��ʼ������ */
   while(flag)
   {
     printf("1:���ṹ������student�еļ�¼��ѧ�ŷǽ����������\n");
     printf("2:���ļ��еļ�¼��ѧ�ŷǽ����������\n");
     printf("3:���������¼�¼�������䰴ѧ�ŷǽ����������\n");
     printf("4:ɾ�������е�һ���и���ѧ�ŵļ�¼\n");
     printf("5:ɾ�������е�һ���и��������ļ�¼\n");
     printf("6:�޸������е�һ���и���ѧ�ŵļ�¼\n");
     printf("7:�޸������е�һ���и��������ļ�¼\n");
     printf("8:���������е�һ���и���ѧ�ŵļ�¼\n");
     printf("9:���������е�һ���и��������ļ�¼\n");
     printf("10:��ʾ���м�¼ 11:�������е����м�¼�����ļ� 12:����\n");
     printf("��ѡ���������: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
		 InsertAscend(&T,student[j],cmp); /* ��func2-1.c�� */
               break;
       case 2: printf("�������ļ���: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("���ļ�ʧ��!\n");
               else
               {
                 while(ReadFromFile(&e))
		   InsertAscend(&T,e,cmp); /* ��func2-1.c�� */
                 fclose(fp);
               }
               break;
       case 3: ReadIn(&e);
	       InsertAscend(&T,e,cmp); /* ��func2-1.c�� */
               break;
       case 4: printf("�������ɾ����¼��ѧ��: ");
               scanf("%ld",&e.num);
               if(!DeleteElem(&T,&e,EqualNum)) /* ��func2-1.c�� */
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",e.num);
               break;
       case 5: printf("�������ɾ����¼������: ");
               scanf("%*c%s",e.name); /* %*c�Ե��س��� */
               if(!DeleteElem(&T,&e,EqualName)) /* ��func2-1.c�� */
                 printf("û������Ϊ%s�ļ�¼\n",e.name);
               break;
       case 6: printf("��������޸ļ�¼��ѧ��: ");
               scanf("%ld%*c",&e.num);
	       if(!DeleteElem(&T,&e,EqualNum)) /* ��������ɾ���ý�㣬����e����(func2-1.c) */
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",e.num);
               else
                 Modify(&T,e); /* �޸�e����ѧ�Ų�������T */
               break;
       case 7: printf("��������޸ļ�¼������: ");
               scanf("%*c%s%*c",e.name); /* %*c�Ե��س��� */
               if(!DeleteElem(&T,&e,EqualName)) /* func2-1.c */
                 printf("û������Ϊ%s�ļ�¼\n",e.name);
               else
                 Modify(&T,e);
               break;
       case 8: printf("����������Ҽ�¼��ѧ��: ");
               scanf("%ld",&e.num);
               q=Point(T,e,EqualNum,&p); /* func2-1.c */
               if(!q)
                 printf("û��ѧ��Ϊ%ld�ļ�¼\n",e.num);
               else
                 Print(q->data);
               break;
       case 9: printf("����������Ҽ�¼������: ");
               scanf("%*c%s",e.name);
               q=Point(T,e,EqualName,&p); /* func2-1.c */
               if(!q)
                 printf("û������Ϊ%s�ļ�¼\n",e.name);
               else
                 Print(q->data);
               break;
       case 10:printf("  ����    ѧ�� �Ա� ���� �༶ ����״��\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("�������ļ���: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("���ļ�ʧ��!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
   
   return 0; 
 }
 
 
 
 
 
 