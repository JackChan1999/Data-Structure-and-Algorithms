char blank = '#';//ȫ�ֱ��������������
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
 
 #define CHUNK_SIZE 4//���û������Ĵ�С
 typedef struct Chunk
 {
 	char ch[CHUNK_SIZE];
 	struct Chunk *next;
 }Chunk;
 typedef struct
 {
 	Chunk *head, *tail;//����ͷ��βָ��
	int curlen;//���ĵ�ǰ���� 
 }LString;
 #define DestroyString ClearString//DestroyString()��ClearString()������ͬ
 
 void InitString(LString *T);
 Status StrAssign(LString *T, char *chars);
 Status ToChars(LString T, char* *chars);
 Status StrCopy(LString *T, LString S);
 Status StrEmpty(LString S);
 int StrCompare(LString S, LString T);
 int StrLength(LString S);
 void ClearString(LString *S);
 Status Concat(LString *T, LString S1, LString S2);
 Status SubString(LString *Sub, LString S, int pos, int len);
 int Index(LString S, LString T, int pos);
 Status StrInsert(LString *S, int pos, LString T);
 Status StrDelete(LString *S, int pos, int len);
 Status Replace(LString *S, LString T, LString V);//�˺����봮�Ĵ洢�ṹ�޹�
 void StrPrint(LString T);
 
 int main()
 {
   char *s1="ABCDEFGHI",*s2="12345",*s3="",*s4="asd#tr",*s5="ABCD";
   Status k;
   int pos,len;
   LString t1,t2,t3,t4;
   InitString(&t1);
   InitString(&t2);
   printf("��ʼ����t1�󣬴�t1�շ�%d(1:�� 0:��) ����=%d\n",StrEmpty(t1),StrLength(t1));
   k=StrAssign(&t1,s3);
   if(k==ERROR)
     printf("����\n"); /* �������ɿմ� */
   k=StrAssign(&t1,s4);
   if(k==ERROR)
     printf("����\n"); /* �������ɺ��б���blank��������ַ��Ĵ� */
   k=StrAssign(&t1,s1);
   if(k==OK)
   {
     printf("��t1Ϊ: ");
     StrPrint(t1);
   }
   else
     printf("����\n");
   printf("��t1�շ�%d(1:�� 0:��) ����=%d\n",StrEmpty(t1),StrLength(t1));
   StrAssign(&t2,s2);
   printf("��t2Ϊ: ");
   StrPrint(t2);
   StrCopy(&t3,t1);
   printf("�ɴ�t1�����õ���t3,��t3Ϊ: ");
   StrPrint(t3);
   InitString(&t4);
   StrAssign(&t4,s5);
   printf("��t4Ϊ: ");
   StrPrint(t4);
   Replace(&t3,t4,t2);
   printf("��t2ȡ����t3�е�t4���󣬴�t3Ϊ: ");
   StrPrint(t3);
   ClearString(&t1);
   printf("��մ�t1�󣬴�t1�շ�%d(1:�� 0:��) ����=%d\n",StrEmpty(t1),StrLength(t1));
   Concat(&t1,t2,t3);
   printf("��t1(=t2+t3)Ϊ: ");
   StrPrint(t1);
   pos=Index(t1,t3,1);
   printf("pos=%d\n",pos);
   printf("�ڴ�t1�ĵ�pos���ַ�֮ǰ���봮t2��������pos: ");
   scanf("%d",&pos);
   k=StrInsert(&t1,pos,t2);
   if(k)
   {
     printf("���봮t2�󣬴�t1Ϊ: ");
     StrPrint(t1);
   }
   else
     printf("����ʧ�ܣ�\n");
   printf("���t1�ĵ�pos���ַ���,����Ϊlen���Ӵ�t2,������pos,len: ");
   scanf("%d,%d",&pos,&len);
   SubString(&t2,t1,pos,len);
   printf("��t2Ϊ: ");
   StrPrint(t2);
   printf("StrCompare(t1,t2)=%d\n",StrCompare(t1,t2));
   printf("ɾ����t1�е����ַ������ӵ�pos���ַ���ɾ��len���ַ���������pos,len��");
   scanf("%d,%d",&pos,&len);
   k=StrDelete(&t1,pos,len);
   if(k)
   {
     printf("�ӵ�%dλ����ɾ��%d��Ԫ�غ�t1Ϊ:",pos,len);
     StrPrint(t1);
   }
   DestroyString(&t1); /* ���ٲ���ͬ��� */
 	
 	
 	return 0;
 }
 
 void InitString(LString *T)
 {
 	//��ʼ��(�����մ�)�ַ���T�����
	(*T).curlen = 0;
	(*T).head = (*T).tail = NULL; 
 }
 
 Status StrAssign(LString *T, char *chars)
 {
 	//����һ����ֵ����chars�Ĵ�T��Ҫ��chars�в������������ַ�����
	//�ɹ�����OK�����򷵻�ERROR
	int i, j, k, m;
	Chunk *p, *q;
	i = strlen(chars);//iΪ���ĳ���
	if ( !i || strchr(chars, blank) )//����Ϊ0��chars�����������ַ�
	{
		return ERROR; 
	}
	(*T).curlen = i;
	j = i / CHUNK_SIZE;//jΪ�����Ľ����
	
	if (i % CHUNK_SIZE)
	{
		j++;
	}
	
	for (k=0; k<j; k++)
	{
		p = (Chunk*)malloc(sizeof(Chunk));//���ɿ���
		if (!p)//���ɿ���ʧ��
		{
			return ERROR; 
		} 
		for (m=0; m<CHUNK_SIZE && *chars; m++)//�������������ֵ
		{
			*(p->ch+m) = *chars++; 
		} 
		
		if (k == 0)//��һ������ 
		{
			(*T).head = q = p;//ͷָ��ָ���һ������ 
		}
		else
		{
			q->next = p;
			q = p;
		} 
		
		if (!*chars)//���һ������
		{
			(*T).tail = q;
			q->next = NULL;
			for (; m < CHUNK_SIZE; m++)//���������ַ��������� 
			{
				*(q->ch+m) = blank; 
				
			}//for 
		}//if
	}//for 
	
	return OK;
 }
 
 Status ToChars(LString T, char* *chars)
 {
 	//����T������ת��Ϊ�ַ�����charsΪͷָ�롣�ɹ�����OK�����򷵻�ERROR�����
	Chunk *p = T.head;//pָ���1������
	int i;
	char *q;
	*chars = (char*)malloc((T.curlen+1) * sizeof(char));
	
	if ( !chars || !T.curlen)//�����ַ�������ʧ�ܻ�T��Ϊ0
	{
		return ERROR;
	}  
	q = *chars;//qָ��chars�ĵ�1���ַ� 
	while (p)//����û����
	{
		for (i=0; i<CHUNK_SIZE; i++)
		{
			if (p->ch[i] != blank)//��ǰ�ַ������������ַ�
			{
				*q++ = (p->ch[i]);//����q��ָ�ַ��ռ� 
			}//if 		 
		}//for
		p = p->next; 
	} 
	(*chars)[T.curlen] = 0;//��������
	
	return OK; 	
 } 
 
 Status StrCopy(LString *T, LString S)
 {
 	//��ʼ��������S����
	//����������ɴ�S���Ƶô�T,ȥ���������ַ����ɹ�����OK�����򷵻�ERROR
	char *c;
	Status i;
	
	if (!ToChars(S, &c))//cΪ��S������
	{
		return ERROR; 
	} 
	i = StrAssign(T, c);//����S�����ݸ���T
	free(c);//�ͷ�c�Ŀռ�
	
	return i; 
 }
 
 Status StrEmpty(LString S)
 {
 	//��ʼ��������S���ڡ������������SΪ�մ����򷵻�TRUE�����򷵻�FALSE
	if (S.curlen)//�ǿ�
	{
		return FALSE; 
	} 
	else
	{
		return TRUE; 
	} 	
 }
 
 int StrCompare(LString S, LString T)
 {
 	//��S>T,�򷵻�ֵ>0;��S=T,�򷵻�ֵ=0����S<T,�򷵻�ֵ<0
	char *s, *t;
	Status i;
	
	if (!ToChars(S, &s))//sΪ��S������
	{
		return ERROR; 
	} 
	if (!ToChars(T, &t))//tΪ��T������
	{
		return ERROR; 
	} 
	i = strcmp(s, t);//����C�Ŀ⺯��
	free(s);//�ͷ�s��t�Ŀռ�
	free(t);
	
	return i; 
 } 
 
 int StrLength(LString S)
 {
 	//����S��Ԫ�ظ�������Ϊ���ĳ���
	return S.curlen; 
 }
 
 void ClearString(LString *S)
 {
 	//��ʼ���� ����S���ڡ������������S��Ϊ�մ�
 	Chunk *p, *q;
	
	p = (*S).head;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	} 
	(*S).head = (*S).tail = NULL;
	(*S).curlen = 0;	  
 }
 
 Status Concat(LString *T, LString S1, LString S2)
 {
 	//��T������S1��S2���Ӷ��ɵ��´����м�������������ַ���
	LString a1, a2;
	Status i, j;
	
	InitString(&a1);
	InitString(&a2);
	
	i = StrCopy(&a1, S1);
	j = StrCopy(&a2, S2);
	
	if (!i || !j)//������1�����������ɹ�
	{
		return ERROR; 
	} 
	(*T).curlen = S1.curlen + S2.curlen;//���ɴ�T
	(*T).head = a1.head;
	a1.tail->next = a2.head;//a1,a2������β����
	(*T).tail = a2.tail;
	
	return OK; 	
 }
 
 Status SubString(LString *Sub, LString S, int pos, int len)
 {
 	//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
	//���У�1<=pos<=StrLength(S)��0<=len<=StrLength(S)-pos+1
	char *b, *c;
	Status i;
	
	if (pos<1 || pos>S.curlen || len<0 || len>S.curlen-pos+1)//pos��lenֵ���Ϸ�
	{
		return ERROR; 
	} 
	if (!ToChars(S, &c))//cΪ��S������
	{
		return ERROR; 
	} 
	b = c+pos-1;//bָ��c�д�Sub���ݵ��׵�ַ
	b[len] = 0;//Sub��������0���ַ�����������
	i = StrAssign(Sub, b);//����b�����ݸ���Sub
	free(c); 
	
	return i;	 
 }
 
 int Index(LString S, LString T, int pos)
 {
 	//TΪ�ǿ��ַ�����������S�� ��pos���ַ�֮�������T��ȵ��Ӵ�
	//�򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0
	int i, n, m;
	LString sub;
	
	if (pos>=1 && pos<=StrLength(S))//pos��������
	{
		n = StrLength(S);//��������
		m = StrLength(T);//��T����
		i = pos;
		while (i <= n-m+1)
		{
			SubString(&sub, S, i, m);//subΪ��S�ĵ�i���ַ��𣬳���Ϊm���Ӵ�
			if (StrCompare(sub, T))//sub������T
			{
				++i; 
			} 
			else
			{
				return i; 
			}//else 
		}//while 
	} //if
	
	return 0;
 } 
 
 Status StrInsert(LString *S, int pos, LString T)
 {
 	//1<=pos<=StrLength(S)+1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
	char *b, *c;
	int i, j;
	Status k;
	
	if ( pos<1 || (pos>(*S).curlen+1) )//pos��ֵ������Χ
	{
		return ERROR;
	}
	if (!ToChars(*S, &c))//cΪ��S������
	{
		return ERROR; 
	} 
	if (!ToChars(T, &b))//bΪ��T������
	{
		return ERROR;
	} 
	j = (int)strlen(c);//jΪ��S���������
	c = (char*)realloc(c, (j+strlen(b)+1)*sizeof(char));//����c�Ĵ洢�ռ�
	
	for (i=j; i>=pos-1; i--)
	{
		c[i+strlen(b)] = c[i];//Ϊ���봮b�ڳ��ռ� 
	} 
	
	for (i=0; i<(int)strlen(b); i++)//�ڴ�c�в��봮b
	{
		c[pos+i-1] = b[i]; 
	} 
	InitString(S);//�ͷ�S��ԭ�д洢�ռ�
	k = StrAssign(S, c);//��c�����µĴ�S
	free(b);
	free(c);
	
	return k;  
 }
 
 Status StrDelete(LString *S, int pos, int len)
 {
 	//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
	char *c;
	int i;
	Status k;
	
	if (pos<1 || pos>(*S).curlen-len+1 || len<0)//pos,len��ֵ������Χ
	{
		return ERROR; 
	} 
	if (! ToChars(*S, &c))//cΪ��S������
	{
		return ERROR; 
	} 
	for (i=pos+len-1; i<=(int)strlen(c); i++)
	{
		c[i-len] = c[i];//cΪɾ����S������ 
	}
	InitString(S);//�ͷ�S��ԭ�д洢�ռ�
	k = StrAssign(S, c);//��c�����µĴ�S
	free(c);
	
	return k; 
 }
 
 Status Replace(LString *S, LString T, LString V)//�˺����봮�Ĵ洢�ṹ�޹�
 {
 	//��ʼ����:��S,T��V���ڣ�T�Ƿǿմ�
	//�����������V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
	int i = 1;//�Ӵ�S�ĵ�һ���ַ�����Ҵ�T
	
	if (StrEmpty(T))//T�ǿմ�
	{
		return ERROR;
	} 
	do
	{
		i = Index(*S, T, i);//���iΪ����һ��i֮���ҵ����Ӵ�T��λ��
		if (i)//��S�д��ڴ�T
		{
			StrDelete(S, i, StrLength(T));//ɾ���ô�T
			StrInsert(S, i, V);//��ԭ��T��λ�ò��봮V
			i += StrLength(V);//�ڲ���Ĵ�V����������Ҵ�T 
		} //if 	
	}while(i);
	
	return OK; 
 } 
 
 void StrPrint(LString T)
 {
 	//����ַ���T�����
	int i = 0, j;
	Chunk *h;
	
	h = T.head;
	
	while (i < T.curlen)
	{
		for (j=0; j<CHUNK_SIZE; j++)
		{
			if (*(h->ch+j) != blank)//�����������ַ� 
			{
				printf("%c", *(h->ch+j));
				i++; 
			}//if
		}//for 
		h = h->next;
	} 
	
	printf("\n");
 }
 
 
 
  
  