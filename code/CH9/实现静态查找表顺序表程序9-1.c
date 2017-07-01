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
 
 #define N 5 /* ����Ԫ�ظ��� */
 typedef long KeyType; /* ��ؼ�����Ϊ������ */
 #define key number /* ����ؼ���Ϊ׼��֤�� */
 typedef struct
 {
   long number; /* ׼��֤�ţ���ؼ�������ͬ */
   char name[9]; /* ����(4�����ּ�1����������־) */
   int politics; /* ���� */
   int Chinese; /* ���� */
   int English; /* Ӣ�� */
   int math; /* ��ѧ */
   int physics; /* ���� */
   int chemistry; /* ��ѧ */
   int biology; /* ���� */
   int total; /* �ܷ� */
 }ElemType; /* ����Ԫ������(�Խ̿���ͼ9.1�߿��ɼ�Ϊ��) */
 #define EQ(a,b) ((a)==(b))
 #define LT(a,b) ((a)<(b))
 #define LQ(a,b) ((a)<=(b))
 typedef struct
 {
   ElemType *elem; /* ����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ���� */
   int length; /* ���� */
 }SSTable;

void Creat_Seq(SSTable *ST,ElemType r[],int n)
 { /* ����������ɺ�n������Ԫ�ص�����r���쾲̬˳����ұ�ST */
   int i;
   (*ST).elem=(ElemType*)calloc(n+1,sizeof(ElemType)); /* ��̬����n+1������Ԫ�ؿռ�(0�ŵ�Ԫ����) */
   if(!(*ST).elem)
     exit(ERROR);
   for(i=1;i<=n;i++)
     (*ST).elem[i]=r[i-1]; /* ������r��ֵ���θ���ST */
   (*ST).length=n;
 }

 void Ascend(SSTable *ST)
 { /* �ؽ���̬���ұ�Ϊ���ؼ��ַǽ������� */
   int i,j,k;
   for(i=1;i<(*ST).length;i++)
   {
     k=i;
     (*ST).elem[0]=(*ST).elem[i]; /* ���Ƚ�ֵ��[0]��Ԫ */
     for(j=i+1;j<=(*ST).length;j++)
       if LT((*ST).elem[j].key,(*ST).elem[0].key)
       {
	 k=j;
	 (*ST).elem[0]=(*ST).elem[j];
       }
     if(k!=i) /* �и�С��ֵ�򽻻� */
     {
       (*ST).elem[k]=(*ST).elem[i];
       (*ST).elem[i]=(*ST).elem[0];
     }
   }
 }

 void Creat_Ord(SSTable *ST,ElemType r[],int n)
 { /* ����������ɺ�n������Ԫ�ص�����r���찴�ؼ��ַǽ�����ұ�ST */
   Creat_Seq(ST,r,n); /* ��������Ĳ��ұ�ST */
   Ascend(ST); /* ������Ĳ��ұ�ST�ؽ�Ϊ���ؼ��ַǽ�����ұ� */
 }

 Status Destroy(SSTable *ST)
 { /* ��ʼ��������̬���ұ�ST���ڡ�������������ٱ�ST */
   free((*ST).elem);
   (*ST).elem=NULL;
   (*ST).length=0;
   return OK;
 }

 int Search_Seq(SSTable ST,KeyType key)
 { /* ��˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء����ҵ����򷵻� */
   /* ��Ԫ���ڱ��е�λ�ã����򷵻�0���㷨9.1 */
   int i;
   ST.elem[0].key=key; /* �ڱ� */
   for(i=ST.length;!EQ(ST.elem[i].key,key);--i); /* �Ӻ���ǰ�� */
   return i; /* �Ҳ���ʱ��iΪ0 */
 }

 int Search_Bin(SSTable ST,KeyType key)
 { /* �������ST���۰������ؼ��ֵ���key������Ԫ�ء����ҵ����򷵻� */
   /* ��Ԫ���ڱ��е�λ�ã����򷵻�0���㷨9.2 */
   int low,high,mid;
   low=1; /* �������ֵ */
   high=ST.length;
   while(low<=high)
   {
     mid=(low+high)/2;
     if EQ(key,ST.elem[mid].key)  /* �ҵ�����Ԫ�� */
       return mid;
     else if LT(key,ST.elem[mid].key)
       high=mid-1; /* ������ǰ��������в��� */
     else
       low=mid+1; /* �����ں��������в��� */
   }
   return 0; /* ˳����в����ڴ���Ԫ�� */
 }

 void Traverse(SSTable ST,void(*Visit)(ElemType))
 { /* ��ʼ��������̬���ұ�ST���ڣ�Visit()�Ƕ�Ԫ�ز�����Ӧ�ú��� */
   /* �����������˳���ST��ÿ��Ԫ�ص��ú���Visit()һ���ҽ�һ�� */
   ElemType *p;
   int i;
   p=++ST.elem; /* pָ���һ��Ԫ�� */
   for(i=1;i<=ST.length;i++)
     Visit(*p++);
 }

 void print(ElemType c) /* Traverse()���õĺ��� */
 {
   printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,
	   c.Chinese,c.English,c.math,c.physics,c.chemistry,c.biology,c.total);
 }

 int main()
 {
   ElemType r[N]={{179328,"�η���",85,89,98,100,93,80,47},
   {179325,"�º�",85,86,88,100,92,90,45},
	{179326,"½��",78,75,90,80,95,88,37},
	{179327,"��ƽ",82,80,78,98,84,96,40},
	{179324,"��С��",76,85,94,57,77,69,44}}; /* ���鲻���ؼ������� */
   SSTable st;
   int i;
   long s;
   for(i=0;i<N;i++) /* �����ܷ� */
     r[i].total=r[i].politics+r[i].Chinese+r[i].English+r[i].math+r[i].physics+
	 r[i].chemistry+r[i].biology;
   Creat_Seq(&st,r,N); /* ������r����˳��̬���ұ�st */
   printf("׼��֤��  ����  ���� ���� ���� ��ѧ ���� ��ѧ ���� �ܷ�\n");
   Traverse(st,print); /* ��˳�������̬���ұ�st */
   printf("������������˵Ŀ���: ");
   scanf("%ld",&s);
   i=Search_Seq(st,s); /* ˳����� */
   if(i)
     print(st.elem[i]);
   else
     printf("û�ҵ�\n");
   Destroy(&st);
   
   return 0;
 }