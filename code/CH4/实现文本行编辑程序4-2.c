 #include<limits.h> /* INT_MAX�� */
 #include<stdio.h> /* EOF(=^Z��F6),NULL */
 #include<stdlib.h> /* atoi() */
 #include<io.h> /* eof() */
 #include<math.h> /* floor(),ceil(),abs() */
 #include<process.h> /* exit() */
 #include<string.h>
 /* �������״̬���� */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 /* #define OVERFLOW -2 ��Ϊ��math.h���Ѷ���OVERFLOW��ֵΪ3,��ȥ������ */
 typedef int Status; /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
 typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */
 /* ���ô��Ķѷ���洢�ṹ */
 typedef struct
 {
   char *ch; /* ���Ƿǿմ����򰴴�������洢��������chΪNULL */
   int length; /* ������ */
 }HString;
 
 #define DestroyString ClearString /* DestroyString()��ClearString()������ͬ */ 
 #define MAX_LEN 25 /* �ļ�������� */
 #define LINE_LEN 75 /* ÿ���ַ������ֵ+1 */
 #define NAME_LEN 20 /* �ļ�����󳤶�(�����̷���·��)+1 */

 /* ȫ�ֱ��� */
 HString T[MAX_LEN];
 char str[LINE_LEN],filename[NAME_LEN]="";
 FILE *fp;
 int n=0; /* �ı����� */
 

 void StrAssign(HString *T,char *chars)
 { /* ����һ����ֵ���ڴ�����chars�Ĵ�T */
   int i,j;
   if((*T).ch)
     free((*T).ch); /* �ͷ�Tԭ�пռ� */
   i=strlen(chars); /* ��chars�ĳ���i */
   if(!i)
   { /* chars�ĳ���Ϊ0 */
     (*T).ch=NULL;
     (*T).length=0;
   }
   else
   { /* chars�ĳ��Ȳ�Ϊ0 */
     (*T).ch=(char*)malloc(i*sizeof(char)); /* ���䴮�ռ� */
     if(!(*T).ch) /* ���䴮�ռ�ʧ�� */
       exit(OVERFLOW);
     for(j=0;j<i;j++) /* ������ */
       (*T).ch[j]=chars[j];
     (*T).length=i;
   }
 }

 void StrCopy(HString *T,HString S)
 { /* ��ʼ��������S���ڡ�����������ɴ�S���Ƶô�T */
   int i;
   if((*T).ch)
     free((*T).ch); /* �ͷ�Tԭ�пռ� */
   (*T).ch=(char*)malloc(S.length*sizeof(char)); /* ���䴮�ռ� */
   if(!(*T).ch) /* ���䴮�ռ�ʧ�� */
     exit(OVERFLOW);
   for(i=0;i<S.length;i++) /* ������ */
     (*T).ch[i]=S.ch[i];
   (*T).length=S.length;
 }

 Status StrEmpty(HString S)
 { /* ��ʼ��������S���ڡ������������SΪ�մ����򷵻�TRUE�����򷵻�FALSE */
   if(S.length==0&&S.ch==NULL)
     return TRUE;
   else
     return FALSE;
 }

 int StrCompare(HString S,HString T)
 { /* ��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0 */
   int i;
   for(i=0;i<S.length&&i<T.length;++i)
     if(S.ch[i]!=T.ch[i])
       return S.ch[i]-T.ch[i];
   return S.length-T.length;
 }

 int StrLength(HString S)
 { /* ����S��Ԫ�ظ�������Ϊ���ĳ��� */
   return S.length;
 }

 void ClearString(HString *S)
 { /* ��S��Ϊ�մ� */
   free((*S).ch);
   (*S).ch=NULL;
   (*S).length=0;
 }

 void Concat(HString *T,HString S1,HString S2)
 { /* ��T������S1��S2���Ӷ��ɵ��´� */
   int i;
   if((*T).ch)
     free((*T).ch); /* �ͷžɿռ� */
   (*T).length=S1.length+S2.length;
   (*T).ch=(char *)malloc((*T).length*sizeof(char));
   if(!(*T).ch)
     exit(OVERFLOW);
   for(i=0;i<S1.length;i++)
     (*T).ch[i]=S1.ch[i];
   for(i=0;i<S2.length;i++)
     (*T).ch[S1.length+i]=S2.ch[i];
 }

 Status SubString(HString *Sub, HString S,int pos,int len)
 { /* ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ��� */
   /* ���У�1��pos��StrLength(S)��0��len��StrLength(S)-pos+1 */
   int i;
   if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
     return ERROR;
   if((*Sub).ch)
     free((*Sub).ch); /* �ͷžɿռ� */
   if(!len) /* ���Ӵ� */
   {
     (*Sub).ch=NULL;
     (*Sub).length=0;
   }
   else
   { /* �����Ӵ� */
     (*Sub).ch=(char*)malloc(len*sizeof(char));
     if(!(*Sub).ch)
       exit(OVERFLOW);
     for(i=0;i<=len-1;i++)
       (*Sub).ch[i]=S.ch[pos-1+i];
     (*Sub).length=len;
   }
   return OK;
 }

 void InitString(HString *T)
 { /* ��ʼ��(�����մ�)�ַ���T����� */
   (*T).length=0;
   (*T).ch=NULL;
 }

 int Index(HString S,HString T,int pos) /* �㷨4.1 */
 { /* TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���*/
   /* �򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0 */
   int n,m,i;
   HString sub;
   InitString(&sub);
   if(pos>0)
   {
     n=StrLength(S);
     m=StrLength(T);
     i=pos;
     while(i<=n-m+1)
     {
       SubString(&sub,S,i,m);
       if(StrCompare(sub,T)!=0)
         ++i;
       else
	 return i;
     }
   }
   return 0;
  }

 Status StrInsert(HString *S,int pos,HString T) /* �㷨4.4 */
 { /* 1��pos��StrLength(S)+1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T */
   int i;
   if(pos<1||pos>(*S).length+1) /* pos���Ϸ� */
     return ERROR;
   if(T.length) /* T�ǿգ������·���ռ䣬����T */
   {
     (*S).ch=(char*)realloc((*S).ch,((*S).length+T.length)*sizeof(char));
     if(!(*S).ch)
       exit(OVERFLOW);
     for(i=(*S).length-1;i>=pos-1;--i) /* Ϊ����T���ڳ�λ�� */
       (*S).ch[i+T.length]=(*S).ch[i];
     for(i=0;i<T.length;i++)
       (*S).ch[pos-1+i]=T.ch[i]; /* ����T */
     (*S).length+=T.length;
   }
   return OK;
 }

 Status StrDelete(HString *S,int pos,int len)
 { /* �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ� */
   int i;
   if((*S).length<pos+len-1)
     return ERROR;
   for(i=pos-1;i<=(*S).length-len;i++)
     (*S).ch[i]=(*S).ch[i+len];
   (*S).length-=len;
   (*S).ch=(char*)realloc((*S).ch,(*S).length*sizeof(char));
   return OK;
 }

 Status Replace(HString *S,HString T,HString V) /* �˺����봮�Ĵ洢�ṹ�޹� */
 { /* ��ʼ��������S��T��V���ڣ�T�Ƿǿմ� */
   /* �����������V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ� */
   int i=1; /* �Ӵ�S�ĵ�һ���ַ�����Ҵ�T */
   if(StrEmpty(T)) /* T�ǿմ� */
     return ERROR;
   do
   {
     i=Index(*S,T,i); /* ���iΪ����һ��i֮���ҵ����Ӵ�T��λ�� */
     if(i) /* ��S�д��ڴ�T */
     {
       StrDelete(S,i,StrLength(T)); /* ɾ���ô�T */
       StrInsert(S,i,V); /* ��ԭ��T��λ�ò��봮V */
       i+=StrLength(V); /* �ڲ���Ĵ�V����������Ҵ�T */
     }
   }while(i);
   return OK;
 }

 void StrPrint(HString T)
 { /* ���T�ַ�������� */
   int i;
   for(i=0;i<T.length;i++)
     printf("%c",T.ch[i]);
   printf("\n");
 }

 void Open()
 { /* ���ļ�(�»��) */
   if(filename[0]) /* �ļ��Ѵ� */
     printf("�Ѵ��ڴ򿪵��ļ�\n");
   else
   {
     printf("�������ļ���(�ɰ����̷���·����������%d���ַ�): ",NAME_LEN-1);
     scanf("%s",filename);
     fp=fopen(filename,"r"); /* �Զ��ķ�ʽ���ļ� */
     if(fp) /* �Ѵ��ڴ��ļ� */
     {
       while(fgets(str,LINE_LEN,fp)) /* ���ļ�����1���ַ��ɹ� */
       {
         str[strlen(str)-1]=0; /* �����з�10ǿ�Ƹ�Ϊ��������0 */
         if(n>=MAX_LEN)
         {
           printf("�ļ�̫��\n");
           return;
         }
	 StrAssign(&T[n],str);
         n++;
       }
       fclose(fp); /* �ر��ļ� */
     }
     else
       printf("���ļ�\n");
   }
 }

 void List()
 { /* ��ʾ�ı����� */
   int i;
   for(i=0;i<n;i++)
   {
     printf("%d: ",i+1);
     StrPrint(T[i]);
   }
 }

 void Insert()
 { /* ������ */
   int i,l,m;
   printf("�ڵ�l��ǰ��m��,������l m: ");
   scanf("%d%d%*c",&l,&m);
   if(n+m>MAX_LEN)
   {
     printf("������̫��\n");
     return;
   }
   if(n>=l-1&&l>0)
   {
     for(i=n-1;i>=l-1;i--)
       T[i+m]=T[i];
     n+=m;
     printf("��˳���������������:\n");
     for(i=l-1;i<l-1+m;i++)
     {
       gets(str);
       InitString(&T[i]);
       StrAssign(&T[i],str);
     }
   }
   else
     printf("�г�����Χ\n");
 }

 void Delete()
 { /* ɾ���� */
   int i,l,m;
   printf("�ӵ�l����ɾ��m��,������l m: ");
   scanf("%d%d",&l,&m);
   if(n>=l+m-1&&l>0)
   {
     for(i=l-1+m;i<n;i++)
     {
       free(T[i-m].ch);  
       T[i-m]=T[i];
     }
     for(i=n-m;i<n;i++)
       InitString(&T[i]);
     n-=m;
   }
   else
     printf("�г�����Χ\n");
 }

 void Copy()
 { /* ������ */
   int i,l,m,k;
   printf("�ѵ�l�п�ʼ��m�в���ԭk��֮ǰ,������l m k: ");
   scanf("%d%d%d",&l,&m,&k);
   if(n+m>MAX_LEN)
   {
     printf("������̫��\n");
     return;
   }
   if(n>=k-1&&n>=l-1+m&&(k>=l+m||k<=l))
   {
     for(i=n-1;i>=k-1;i--)
       T[i+m]=T[i];
     n+=m;
     if(k<=l)
       l+=m;
     for(i=l-1;i<l-1+m;i++)
     {
       InitString(&T[i+k-l]);
       StrCopy(&T[i+k-l],T[i]);
     }
   }
   else
     printf("�г�����Χ\n");
 }

 void Modify()
 { /* �޸��� */
   int i;
   printf("��������޸ĵ��к�: ");
   scanf("%d%*c",&i);
   if(i>0&&i<=n) /* �кźϷ� */
   {
     printf("%d: ",i);
     StrPrint(T[i-1]);
     printf("������������: ");
     gets(str);
     StrAssign(&T[i-1],str);
   }
   else
     printf("�кų�����Χ\n");
 }

 void Search()
 { /* �����ַ��� */
   int i,k,f=1; /* fΪ�������ұ�־ */
   char b[2];
   HString s;
   printf("����������ҵ��ַ���: ");
   scanf("%s%*c",str);
   InitString(&s);
   StrAssign(&s,str);
   for(i=0;i<n&&f;i++) /* ���в��� */
   {
     k=1; /* ��ÿ�е�1���ַ������ */
     while(k)
     {
       k=Index(T[i],s,k); /* �ɱ��еĵ�k���ַ���ʼ���� */
       if(k) /* �ҵ� */
       {
         printf("��%d��: ",i+1);
         StrPrint(T[i]);
         printf("��%d���ַ����ҵ�������������(Y/N)? ",k);
         gets(b);
	 if(b[0]!='Y'&&b[0]!='y') /* �жϲ��� */
	 {
           f=0;
           break;
         }
         else
	   k++;
       }
     }
   }
   if(f)
     printf("û�ҵ�\n");
 }

 void Replace1()
 { /* �滻�ַ��� */
   int i,k,f=1; /* fΪ�����滻��־ */
   char b[2];
   HString s,t;
   printf("��������滻���ַ���: ");
   scanf("%s%*c",str);
   InitString(&s);
   StrAssign(&s,str);
   printf("�滻Ϊ: ");
   scanf("%s%*c",str);
   InitString(&t);
   StrAssign(&t,str);
   for(i=0;i<n&&f;i++) /* ���в��ҡ��滻 */
   {
     k=1; /* ��ÿ�е�1���ַ������ */
     while(k)
     {
       k=Index(T[i],s,k); /* �ɱ��еĵ�k���ַ���ʼ���� */
       if(k) /* �ҵ� */
       {
         printf("��%d��: ",i+1);
         StrPrint(T[i]);
         printf("��%d���ַ����ҵ����Ƿ��滻(Y/N)? ",k);
         gets(b);
         if(b[0]=='Y'||b[0]=='y')
         {
	   StrDelete(&T[i],k,StrLength(s));
	   StrInsert(&T[i],k,t);
         }
         printf("�����滻��(Y/N)?");
         gets(b);
         if(b[0]!='Y'&&b[0]!='y') /* �жϲ��ҡ��滻 */
         {
           f=0;
           break;
         }
         else
           k+=StrLength(t);
       }
     }
   }
   if(f)
     printf("û�ҵ�\n");
 }

 void Save()
 { /* ���� */
   int i,j;
   fp=fopen(filename,"w"); /* ��д�ķ�ʽ���´��ļ� */
   if(fp) /* ���ļ��ɹ� */
   {
     for(i=0;i<n;i++)
     { /* ���ν�ÿ�д����ļ� */
       for(j=0;j<T[i].length;j++) /* ���δ���ÿ���ַ� */
         fputc(T[i].ch[j],fp);
       fputc(10,fp); /* ���뻻�з� */
       ClearString(&T[i]); /* �ͷŴ��ռ� */
     }
     fclose(fp); /* �ر��ļ� */
   }
   else
     printf("����ʧ��\n");
 }

 int main()
 {
   Status s=TRUE;
   int i,k;
   for(i=0;i<MAX_LEN;i++) /* ��ʼ���� */
     InitString(&T[i]);
   while(s)
   {
     printf("��ѡ��: 1.���ļ�(�»��)  2.��ʾ�ļ�����\n");
     printf("        3.������  4.ɾ����  5.������  6.�޸���\n");
     printf("        7.�����ַ���        8.�滻�ַ���\n");
     printf("        9.�����˳�          0.�����༭\n");
     scanf("%d",&k);
     switch(k)
     {
       case 1: Open();
               break;
       case 2: List();
               break;
       case 3: Insert();
               break;
       case 4: Delete();
               break;
       case 5: Copy();
               break;
       case 6: Modify();
               break;
       case 7: Search();
               break;
       case 8: Replace1();
               break;
       case 9: Save();
       case 0: s=FALSE;
     }
   }
   
   return 0;
 }
 