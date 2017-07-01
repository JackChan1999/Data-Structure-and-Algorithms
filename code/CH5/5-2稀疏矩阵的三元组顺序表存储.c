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
 typedef int ElemType;
 
 #define MAX_SIZE 100 //����Ԫ���������ֵ
 typedef struct
 {
 	int i, j;//���±꣬���±�
    ElemType e;//����Ԫ��ֵ 
 }Triple;
 
 typedef struct 
 {
 	Triple data[MAX_SIZE+1];//����Ԫ��Ԫ���data[0]δ��
	int mu, nu, tu;//����������������ͷ���Ԫ���� 
 }TSMatrix; 
 
 Status CreateSMatrix(TSMatrix *M);
 void DestroySMatrix(TSMatrix *M);
 void PrintSMatrix(TSMatrix M);
 void PrintSMatrix1(TSMatrix M);
 void CopySMatrix(TSMatrix M, TSMatrix *T);
 int comp(int c1, int c2);
 Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q);
 Status SubtSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q);
 void TransposeSMatrix(TSMatrix M, TSMatrix *T);
 Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q);

int main()
{
   TSMatrix A,B,C;
   printf("��������A: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("�ɾ���A���ƾ���B:\n");
   CopySMatrix(A,&B);
   PrintSMatrix1(B);
   DestroySMatrix(&B);
   printf("���پ���B��:\n");
   PrintSMatrix1(B);
   printf("��������B2:(�����A���С�������ͬ���С��зֱ�Ϊ%d,%d)\n",A.mu,A.nu);
   CreateSMatrix(&B);
   PrintSMatrix1(B);
   AddSMatrix(A,B,&C);
   printf("����C1(A+B):\n");
   PrintSMatrix1(C);
   SubtSMatrix(A,B,&C);
   printf("����C2(A-B):\n");
   PrintSMatrix1(C);
   TransposeSMatrix(A,&C);
   printf("����C3(A��ת��):\n");
   PrintSMatrix1(C);
   printf("��������A2: ");
   CreateSMatrix(&A);
   PrintSMatrix1(A);
   printf("��������B3:(����Ӧ�����A2��������ͬ=%d)\n",A.nu);
   CreateSMatrix(&B);
   PrintSMatrix1(B);
   MultSMatrix(A,B,&C);
   printf("����C5(A��B):\n");
   PrintSMatrix1(C);
   
   return 0;
}
 
 
 Status CreateSMatrix(TSMatrix *M)
 {
 	//����ϡ�����M
	int i, m, n;
	ElemType e;
	Status k;
	
	printf("��������������������������Ԫ������");
	scanf("%d,%d,%d", &(*M).mu, &(*M).nu, &(*M).tu);
	
	if ((*M).tu > MAX_SIZE)
	{
		return ERROR; 
	} 
	(*M).data[0].i = 0;//Ϊ���±Ƚ�˳����׼��
	
	for (i=1; i<=(*M).tu; i++)
	{
		do
		{
			printf("�밴����˳�������%d������Ԫ�����ڵ���(1-%d),��(1-%d),Ԫ��ֵ��",
			       i, (*M).mu, (*M).nu);
            scanf("%d,%d,%d", &m, &n, &e);
            k = 0;
            if (m<1 || m>(*M).mu || n<1 || n>(*M).nu)//�л��г�����Χ
			{
				k = 1; 
			} 
			if (  m < (*M).data[i-1].i 
			   || m == (*M).data[i-1].i
			   && n <= (*M).data[i-1].j)//�л��е�˳���д�
			{
				k = 1; 
			} //if
		}while(k);
		(*M).data[i].i = m;
		(*M).data[i].j = n;
		(*M).data[i].e = e;	
	}//for 
	
	return OK;
 }
 
 void DestroySMatrix(TSMatrix *M)
 {
 	//����ϡ�����M
	(*M).mu = (*M).nu = (*M).tu = 0; 
 }
 
 void PrintSMatrix(TSMatrix M)
 {
 	//���ϡ�����M
	int i;
	
	printf("%d��%d��%d������Ԫ�ء�\n", M.mu, M.nu, M.tu);
	printf("��  ��  Ԫ��ֵ\n");
	
	for (i=1; i<=M.tu; i++)
	{
		printf("%2d%4d%8d\n", M.data[i].i, M.data[i].j, M.data[i].e); 
	}//for	
 }
 
 void PrintSMatrix1(TSMatrix M)
 {
 	//��������ʽ���M
	int i, j, k = 1;
	Triple *p = M.data;
	
	p++;//pָ���1������Ԫ��
	
	for (i=1; i<=M.mu; i++)
	{
		for (j=1; j<=M.nu; j++)
		{
			if (   k <= M.tu
			    && p->i == i
				&& p->j == j)//pָ�����Ԫ����p��ָԪ��Ϊ��ǰ����Ԫ��
			{
				printf("%3d", p->e);//���p��ָԪ�ص�ֵ
				p++;//pָ����һ��Ԫ�� 
				k++;//������+1 
			} 
			else//p��ָԪ�ز��ǵ�ǰ����Ԫ�� 
			{
				printf("%3d", 0);//���0 
			}		
		}//for-in
		printf("\n"); 
	}//for-out 
 }
 
 void CopySMatrix(TSMatrix M, TSMatrix *T)
 {
 	//��ϡ�����M���Ƶõ�T
	(*T) = M; 
 }
 
 int comp(int c1, int c2)
 {
 	//AddSMatrix����Ҫ�õ������
	if (c1 < c2)
	{
		return -1;
	} 
	if (c1 == c2)
	{
		return 0;
	}
	
	return 1;
 }
 
 Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q)
 {
 	//��ϡ�����ĺ�Q=M+N
	int m = 1,
	    n = 1,
		q = 0;
	
	if (M.mu!=N.mu || M.nu!=N.nu)//M,N��ϡ������л�������ͬ
	{
		return ERROR;
	} 
	(*Q).mu = M.mu;
	(*Q).nu = M.nu;
	
	while (m<=M.tu && n<=N.nu)//����M��N��Ԫ�ض�û������
	{
		switch(comp(M.data[m].i, N.data[n].i)) 
		{
			case -1:
			{
				(*Q).data[++q] = M.data[m++];//������M�ĵ�ǰԪ��ֵ��������Q 
			}
			break;
			case 0:
			{
				switch(comp(M.data[m].j, N.data[n].j))//M,N��ǰԪ�ص�����ȣ������Ƚ��� 
				{
					case -1:
					{
						(*Q).data[++q] = M.data[m++];
					} 
					break;
					case 0:
					{
						(*Q).data[++q] = M.data[m++];//M,N����ǰ����Ԫ�ص����о����
						(*Q).data[q].e += N.data[n++].e;//����M,N�ĵ�ǰԪ��ֵ��Ͳ���������Q
					    if (0 == (*Q).data[q].e)//Ԫ��ֵΪ0��������ѹ������
						{
							q--; 
						}//if 
					}
					break;
					case 1:
					{
						(*Q).data[++q] = N.data[++n];
					}
				}//switch
			}//case 
			break; 
			case 1:
			{
				(*Q).data[++q] = N.data[n++];//������N�ĵ�ǰԪ��ֵ�������� 
			}
		}//switch 
	} //while
	
	while (m <= M.tu)//����N��Ԫ��ȫ���������
	{
		(*Q).data[++q] = M.data[m++];
	} 
	while (n <=N.tu)//����M��Ԫ��ȫ���������
	{
		(*Q).data[++q] = N.data[n++]; 
	}
	(*Q).tu = q;//����Q�ķ���Ԫ�ظ���
	if (q > MAX_SIZE)//����Ԫ�ظ���̫��
	{
		return ERROR; 
	} 
	
	return OK;
 }
 
 Status SubtSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q)
 {
 	//��ϡ�����Ĳ�Q=M-N
	int i;
	
	for (i=1; i<N.tu; i++)
	{
		N.data[i].e *= -1;
	} 
	
	return AddSMatrix(M, N, Q);
 }
 
 void TransposeSMatrix(TSMatrix M, TSMatrix *T)
 {
 	//��ϡ�����M��ת�þ���T
	int p, q, col;
	
	(*T).mu = M.nu;
	(*T).nu = M.mu;
	(*T).tu = M.tu;
	
	if ((*T).tu)
	{
		q = 1;
		for (col=1; col<=M.nu; ++col)
		{
			for (p=1; p<=M.tu; ++p)
			{
				if (M.data[p].j == col)
				{
					(*T).data[q].i = M.data[p].j;
					(*T).data[q].j = M.data[p].i;
					(*T).data[q].e = M.data[p].e;
					++q;
				} //if
			}//for-in
		}//for-out
	} //if
 }
 
 Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q)
 {
 	//��ϡ�����ĳ˻�Q=M*N
	int i, j;
	ElemType *Nc, *Tc;
	TSMatrix T;//��ʱ����
	
	if (M.nu != N.mu)
	{
		return ERROR;
	} 
	T.nu = M.mu;//��ʱ����T��Q��ת�þ���
	T.mu = N.nu;
	T.tu = 0;
	//NcΪ����Nһ�е���ʱ���飨��ѹ����[0]���ã� 
	Nc = (ElemType*)malloc((N.mu+1) * sizeof(ElemType)); 
	//TcΪ����Tһ�е���ʱ���飨��ѹ����[0]���ã�
	Tc = (ElemType*)malloc((M.nu+1) * sizeof(ElemType));
	
	if (!Nc || !Tc)//������ʱ���鲻�ɹ� 
	{
		exit(ERROR); 
	} 
	for (i=1; i<=N.nu; i++)//����N��ÿһ�� 
	{
		for (j=1; j<=N.mu; j++)
		{
			Nc[j] = 0;//����Nc�ĳ�ֵΪ0 
		} 
		for (j=1; j<=M.mu; j++)
		{
			Tc[j] = 0;//��ʱ����Tc�ĳ�ֵΪ0��[0]���� 
		} 
		for (j=1; j<=N.tu; j++)//����N��ÿһ������Ԫ�� 
		{
			if (N.data[j].j == i)//���ڵ�i��
			{
				Nc[N.data[j].i] = N.data[j].e;//�����������н���Ԫ��ֵ������Ӧ��Nc 		
			} 	
		} 
		
		for (j=1; j<=M.tu; j++)//����M��ÿһ��ֵ 
		{
			Tc[M.data[j].i] += (M.data[j].e * Nc[M.data[j].j]);//Tc�д�N�ĵ�i����M��˵Ľ�� 
		} 
		
		for (j=1; j<=M.mu; j++)
		{
			if (Tc[j] != 0)
			{
				T.data[++T.tu].e = Tc[j];
				T.data[T.tu].i = i;
				T.data[T.tu].j = j; 
			}//if
		}//for
		
		if (T.tu > MAX_SIZE) //����Ԫ�ظ���̫�� 
		{
			return ERROR; 
		}		
	} 
	TransposeSMatrix(T, Q);//��T��ת�ø���Q
	DestroySMatrix(&T);//������ʱ����T
	free(Tc);//�ͷŶ�̬����Tc��Nc
	free(Nc);
	return OK;
 }
 
 
 
 
  
  