 #include<stdio.h>
 typedef int InfoType; /* ������������������� */
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
 #define N 8
 
 int Partition(SqList *L,int low,int high)
 { /* ����˳���L���ӱ�r[low..high]�ļ�¼�������¼��λ���������� */
   /* ����λ�ã���ʱ����֮ǰ(��)�ļ�¼������(С)�������㷨10.6(b) */
   KeyType pivotkey;
   (*L).r[0]=(*L).r[low]; /* ���ӱ�ĵ�һ����¼�������¼ */
   pivotkey=(*L).r[low].key; /* �����¼�ؼ��� */
   while(low< high)
   { /* �ӱ�����˽�������м�ɨ�� */
     while(low<high&&(*L).r[high].key>=pivotkey)
       --high;
     (*L).r[low]=(*L).r[high]; /* ���������¼С�ļ�¼�Ƶ��Ͷ� */
     while(low<high&&(*L).r[low].key<=pivotkey)
       ++low;
     (*L).r[high]=(*L).r[low]; /* ���������¼��ļ�¼�Ƶ��߶� */
   }
   (*L).r[low]=(*L).r[0]; /* �����¼��λ */
   return low; /* ��������λ�� */
 }

 void QSort(SqList *L,int low,int high)
 { /* ��˳���L�е�������L.r[low..high]�����������㷨10.7 */
   int pivotloc;
   if(low<high)
   { /* ���ȴ���1 */
     pivotloc=Partition(L,low,high); /* ��L.r[low..high]һ��Ϊ�� */
     QSort(L,low,pivotloc-1); /* �Ե��ӱ�ݹ�����pivotloc������λ�� */
     QSort(L,pivotloc+1,high); /* �Ը��ӱ�ݹ����� */
   }
 }

 void QuickSort(SqList *L)
 { /* ��˳���L�����������㷨10.8 */
   QSort(L,1,(*L).length);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }
 
 int main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("����ǰ:\n");
   print(l);
   QuickSort(&l);
   printf("�����:\n");
   print(l);
   
   return 0; 
 }