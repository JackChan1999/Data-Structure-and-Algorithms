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

 typedef int InfoType; /* ������������������� */
 #define EQ(a,b) ((a)==(b))
 #define LT(a,b) ((a)<(b))
 #define LQ(a,b) ((a)<=(b))
 #define MAX_SIZE 20 /* һ������ʾ����С˳������󳤶� */
 typedef int KeyType; /* ����ؼ�������Ϊ���� */
 typedef struct
 {
   KeyType key; /* �ؼ����� */
   InfoType otherinfo; /* ������������������������ж��� */
 }RedType; /* ��¼���� */
 typedef struct
 {
   RedType r[MAX_SIZE+1]; /* r[0]���û������ڱ���Ԫ */
   int length; /* ˳����� */
 }SqList; /* ˳������� */
 /* ����KeyType��RedType��SqList */
 #define k 5 /* k·�鲢 */
 FILE *fp[k+1]; /* k+1���ļ�ָ��(fp[k]Ϊ���ļ�ָ��)��ȫ�ֱ��� */
 typedef int LoserTree[k]; /* ����������ȫ�������Ҳ���Ҷ�ӣ��ɲ���˳��洢�ṹ */
 typedef RedType ExNode,External[k+1]; /* ���㣬�иı� */
 External b; /* ȫ�ֱ��� */
 #define MIN_KEY INT_MIN
 #define MAX_KEY INT_MAX
 #define N 3 /* ��ÿ��С�ļ���N������(�ɽ������ļ�һ�ζ����ڴ�ĳ�ΪС�ļ�) */
 #define M 10 /* �����M�����ݻ��� */
 
 void InsertSort(SqList *L)
 { /* ��˳���L��ֱ�Ӳ��������㷨10.1 */
   int i,j;
   for(i=2;i<=(*L).length;++i)
     if LT((*L).r[i].key,(*L).r[i-1].key) /* "<",�轫L.r[i]���������ӱ� */
     {
       (*L).r[0]=(*L).r[i]; /* ����Ϊ�ڱ� */
       for(j=i-1;LT((*L).r[0].key,(*L).r[j].key);--j)
	 (*L).r[j+1]=(*L).r[j]; /* ��¼���� */
       (*L).r[j+1]=(*L).r[0]; /* ���뵽��ȷλ�� */
     }
 }

 void BInsertSort(SqList *L)
 { /* ��˳���L���۰���������㷨10.2 */
   int i,j,m,low,high;
   for(i=2;i<=(*L).length;++i)
   {
     (*L).r[0]=(*L).r[i]; /* ��L.r[i]�ݴ浽L.r[0] */
     low=1;
     high=i-1;
     while(low<=high)
     { /* ��r[low..high]���۰������������λ�� */
       m=(low+high)/2; /* �۰� */
       if LT((*L).r[0].key,(*L).r[m].key)
         high=m-1; /* ������ڵͰ��� */
       else
         low=m+1; /* ������ڸ߰��� */
     }
     for(j=i-1;j>=high+1;--j)
       (*L).r[j+1]=(*L).r[j]; /* ��¼���� */
     (*L).r[high+1]=(*L).r[0]; /* ���� */
   }
 }

 void P2_InsertSort(SqList *L)
 { /* 2_·�������� */
   int i,j,first,final;
   RedType *d;
   d=(RedType*)malloc((*L).length*sizeof(RedType)); /* ����L.length����¼����ʱ�ռ� */
   d[0]=(*L).r[1]; /* ��L�ĵ�1����¼Ϊd���ź���ļ�¼(��λ��[0]) */
   first=final=0; /* first��final�ֱ�ָʾd���ź���ļ�¼�ĵ�1�������1����¼��λ�� */
   for(i=2;i<=(*L).length;++i) /* ���ν�L�ĵ�2�������1����¼����d�� */
     if((*L).r[i].key<d[first].key)
     { /* �����¼С��d����Сֵ���嵽d[first]֮ǰ(�����ƶ�d�����Ԫ��) */
       first=(first-1+(*L).length)%(*L).length; /* ��dΪѭ������ */
       d[first]=(*L).r[i];
     }
     else if((*L).r[i].key>d[final].key)
     { /* �����¼����d�����ֵ���嵽d[final]֮��(�����ƶ�d�����Ԫ��) */
       final=final+1;
       d[final]=(*L).r[i];
     }
     else
     { /* �����¼����d����Сֵ��С��d�����ֵ���嵽d���м�(��Ҫ�ƶ�d�����Ԫ��) */
       j=final++; /* �ƶ�d��β��Ԫ���Ա㰴������¼ */
       while((*L).r[i].key<d[j].key)
       {
         d[(j+1)%(*L).length]=d[j];
         j=(j-1+(*L).length)%(*L).length;
       }
       d[j+1]=(*L).r[i];
     }
   for(i=1;i<=(*L).length;i++) /* ��d����L.r */
     (*L).r[i]=d[(i+first-1)%(*L).length]; /* ���Թ�ϵ */
 }

 void input(int i,KeyType *a)
 { /* �ӵ�i���ļ�(��i���鲢��)����öε�ǰ��1����¼�Ĺؼ��ֵ����� */
   fread(a,sizeof(KeyType),1,fp[i]);
 }

 void output(int i)
 { /* ����i���ļ�(��i���鲢��)�е�ǰ�ļ�¼д������鲢�� */
   ExNode a;
   a.key=b[i].key; /* ��ǰ��¼�Ĺؼ����Ѷ���b[i].key�� */
   fread(&a.otherinfo,sizeof(InfoType),1,fp[i]);
   fwrite(&a,sizeof(ExNode),1,fp[k]);
 }

 void Adjust(LoserTree ls,int s)
 { /* �ش�Ҷ�ӽ��b[s]�������ls[0]��·���������������㷨11.2 */
   int i,t;
   t=(s+k)/2; /* ls[t]��b[s]��˫�׽�� */
   while(t>0)
   {
     if(b[s].key>b[ls[t]].key)
     {
       i=s;
       s=ls[t]; /* sָʾ�µ�ʤ�� */
       ls[t]=i;
     }
     t=t/2;
   }
   ls[0]=s;
 }

 void CreateLoserTree(LoserTree ls)
 { /* ��֪b[0]��b[k-1]Ϊ��ȫ������ls��Ҷ�ӽ�㣬����k���ؼ��֣��ش�Ҷ�� */
   /* ������k��·����ls������Ϊ���������㷨11.3 */
   int i;
   b[k].key=MIN_KEY;
   for(i=0;i<k;++i)
     ls[i]=k; /* ����ls�С����ߡ��ĳ�ֵ */
   for(i=k-1;i>=0;--i) /* ���δ�b[k-1]��b[k-2]������b[0]������������ */
     Adjust(ls,i);
 }

 void K_Merge(LoserTree ls,External b)
 { /* ���ð�����ls����Ŵ�0��k-1��k������鲢���еļ�¼�鲢������鲢�Ρ� */
   /* b[0]��b[k-1]Ϊ�������ϵ�k��Ҷ�ӽ�㣬�ֱ���k������鲢���е�ǰ */
   /* ��¼�Ĺؼ��֡��㷨11.1 */
   int i,q;
   for(i=0;i<k;++i) /* �ֱ��k������鲢�ζ���öε�ǰ��һ����¼�Ĺؼ��ֵ����� */
     input(i,&b[i].key);
   CreateLoserTree(ls); /* ��������ls��ѡ����С�ؼ���Ϊb[ls[0]].key */
   while(b[ls[0]].key!=MAX_KEY)
   {
     q=ls[0]; /* qָʾ��ǰ��С�ؼ������ڹ鲢�� */
     output(q); /* �����Ϊq�Ĺ鲢���е�ǰ(�ؼ���Ϊb[q].key)�ļ�¼д������鲢�� */
     input(q,&b[q].key); /* �ӱ��Ϊq������鲢���ж�����һ����¼�Ĺؼ��� */
     Adjust(ls,q); /* ������������ѡ���µ���С�ؼ��� */
   }
   output(ls[0]); /* �������ؼ���MAX_KEY�ļ�¼д������鲢�� */
 }

 void print(RedType t)
 {
   printf("(%d,%d)",t.key,t.otherinfo);
 }

 int main()
 {
   RedType a[k*N]={{16,1},{15,2},{10,3},{20,4},{9,5},{18,6},{22,7},{20,8},{40,9},{15,10},{25,11},{6,12},{12,13},{48,14},{37,15}}; /* ��k*N����¼������ */
   RedType r,t={MAX_KEY}; /* С�ļ�β���Ľ�����־ */
   SqList l;
   int i,j;
   char fname[k][3],fori[4]="ori",fout[4]="out",s[3];
   LoserTree ls;
   /* ������a����1�����ļ�(���ܽ������ļ�һ�ζ����ڴ�ĳ�Ϊ���ļ�) */
   fp[k]=fopen(fori,"wb"); /* ��д�ķ�ʽ�򿪴��ļ�fori */
   fwrite(a,sizeof(RedType),k*N,fp[k]); /* ������a�е�����д���ļ�fori��(��ʾ1�����ļ�) */
   fclose(fp[k]); /* �ر��ļ�fori */
   fp[k]=fopen(fori,"rb"); /* �Զ��ķ�ʽ�򿪴��ļ�fori */
   printf("���ļ��ļ�¼Ϊ:\n");
   for(i=1;i<=N*k;i++)
   {
     fread(&r,sizeof(RedType),1,fp[k]); /* ���ν����ļ�fori�����ݶ���r */
     print(r); /* ���r������ */
     if(i%M==0)
       printf("\n");
   }
   printf("\n");
   rewind(fp[k]); /* ʹfp[k]��ָ�����·��ش��ļ�fori����ʼλ�ã��Ա����¶����ڴ棬������������ļ� */
   for(i=0;i<k;i++) /* �����ļ�fori�����ݷֳ�k�飬ÿ��N������ */
   { /* �����ֱ�浽С�ļ�f0��f1������ */
     fread(&l.r[1],sizeof(RedType),N,fp[k]); /* �����ļ�fori��N�����ݶ���l */
     l.length=N;
     InsertSort(&l); /* ��l�����ڲ����� */
     itoa(i,s,10); /* ����k���ļ���f0��f1��f2���� */
     strcpy(fname[i],"f");
     strcat(fname[i],s);
     fp[i]=fopen(fname[i],"wb"); /* ��д�ķ�ʽ���ļ�f0��f1���� */
     fwrite(&l.r[1],sizeof(RedType),N,fp[i]); /* ��������N�����ݷֱ�д��f0��f1���� */
     fwrite(&t,sizeof(RedType),1,fp[i]); /* ���ļ�������־�ֱ�д��f0��f1���� */
     fclose(fp[i]); /* �ر��ļ�f0��f1���� */
   }
   fclose(fp[k]); /* �رմ��ļ�fori */
   for(i=0;i<k;i++)
   { /* ���δ�f0��f1��f2������k���ļ� */
     itoa(i,s,10); /* ����k���ļ���f0��f1��f2���� */
     strcpy(fname[i],"f");
     strcat(fname[i],s);
     fp[i]=fopen(fname[i],"rb"); /* �Զ��ķ�ʽ���ļ�f0��f1���� */
     printf("�������ļ�f%d�ļ�¼Ϊ:\n",i);
     for(j=0;j<=N;j++)
     {
       fread(&r,sizeof(RedType),1,fp[i]); /* ���ν�f0��f1���������ݶ���r */
       print(r); /* ���r������ */
     }
     printf("\n");
     rewind(fp[i]); /* ʹfp[i]��ָ�����·���f0��f1��������ʼλ�ã��Ա����¶����ڴ� */
   }
   fp[k]=fopen(fout,"wb"); /* ��д�ķ�ʽ�򿪴��ļ�fout */
   K_Merge(ls,b); /* ���ð�����ls��k������鲢���еļ�¼�鲢������鲢�Σ������ļ�fout */
   for(i=0;i<k;i++)
     fclose(fp[i]); /* �ر��ļ�f0��f1���� */
   fclose(fp[k]); /* �ر��ļ�fout */
   fp[k]=fopen(fout,"rb"); /* �Զ��ķ�ʽ�򿪴��ļ�fout��֤���� */
   printf("�����Ĵ��ļ��ļ�¼Ϊ:\n");
   for(i=1;i<=N*k+1;i++)
   {
     fread(&t,sizeof(RedType),1,fp[k]);
     print(t);
     if(i%M==0)
       printf("\n");
   }
   printf("\n");
   fclose(fp[k]); /* �ر��ļ�fout */
   
   return 0; 
 }