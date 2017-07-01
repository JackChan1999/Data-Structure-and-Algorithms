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
 typedef struct
 {
 	char *ch;//���Ƿǿմ����򰴴�������洢��������chΪNULL
    int length;//������ 
 }HString;
 #define DestroyString ClearString//DestroyString()�� ClearString()������ͬ
 
 void StrAssign(HString *T, char *chars);
 void StrCopy(HString *T, HString S);
 Status StrEmpty(HString S);
 int StrCompare(HString S, HString T);
 int StrLength(HString S);
 void ClearString(HString *S);
 void Concat(HString *T, HString S1, HString S2);
 Status SubString(HString *Sub, HString S, int pos, int len);
 void InitString(HString *T);
 int Index(HString S, HString T, int pos);
 Status StrInsert(HString *S, int pos, HString T);
 Status StrDelete(HString *S, int pos, int len);
 Status Replace(HString *S, HString T, HString V);//�˺����봮�Ĵ洢�ṹ�޹�
 void StrPrint(HString T);
 
 int main()
 {
   int i;
   char c,*p="God bye!",*q="God luck!";
   HString t,s,r;
   InitString(&t); /* HString���ͱ����ʼ�� */
   InitString(&s);
   InitString(&r);
   StrAssign(&t,p);
   printf("��tΪ: ");
   StrPrint(t);
   printf("����Ϊ%d ���շ�%d(1:�� 0:��)\n",StrLength(t),StrEmpty(t));
   StrAssign(&s,q);
   printf("��sΪ: ");
   StrPrint(s);
   i=StrCompare(s,t);
   if(i<0)
     c='<';
   else if(i==0)
     c='=';
   else
     c='>';
   printf("��s%c��t\n",c);
   Concat(&r,t,s);
   printf("��t���Ӵ�s�����Ĵ�rΪ: ");
   StrPrint(r);
   StrAssign(&s,"oo");
   printf("��sΪ: ");
   StrPrint(s);
   StrAssign(&t,"o");
   printf("��tΪ: ");
   StrPrint(t);
   Replace(&r,t,s);
   printf("�Ѵ�r�кʹ�t��ͬ���Ӵ��ô�s����󣬴�rΪ: ");
   StrPrint(r);
   ClearString(&s);
   printf("��s��պ󣬴���Ϊ%d �շ�%d(1:�� 0:��)\n",StrLength(s),StrEmpty(s));
   SubString(&s,r,6,4);
   printf("��sΪ�Ӵ�r�ĵ�6���ַ����4���ַ�������Ϊ%d ��sΪ: ",s.length);
   StrPrint(s);
   StrCopy(&t,r);
   printf("���ƴ�tΪ��r,��tΪ: ");
   StrPrint(t);
   StrInsert(&t,6,s);
   printf("�ڴ�t�ĵ�6���ַ�ǰ���봮s�󣬴�tΪ: ");
   StrPrint(t);
   StrDelete(&t,1,5);
   printf("�Ӵ�t�ĵ�1���ַ���ɾ��5���ַ���,��tΪ: ");
   StrPrint(t);
   printf("%d�ǴӴ�t�ĵ�1���ַ��𣬺ʹ�s��ͬ�ĵ�1���Ӵ���λ��\n",Index(t,s,1));
   printf("%d�ǴӴ�t�ĵ�2���ַ��𣬺ʹ�s��ͬ�ĵ�1���Ӵ���λ��\n",Index(t,s,2));
   DestroyString(&t); /* ���ٲ���ͬ��� */
 	return 0;
 }
 
 void StrAssign(HString *T, char *chars)
 {
 	//����һ����ֵ���ڴ�����chars�Ĵ�T
	int i, j;
	
	if ((*T).ch)
	{
		free((*T).ch);//�ͷ�Tԭ�пռ� 		
	} 
	i = strlen(chars);//��chars�ĳ���i
	
	if (!i)
	{
		//chars�ĳ���Ϊ0
		(*T).ch = NULL;
		(*T).length = 0; 
	} 
	else
	{
		//chars�ĳ��Ȳ�Ϊ0
		(*T).ch = (char *)malloc(i*sizeof(char));//����ջ�ռ�
		if (! (*T).ch)//���䴮�ռ�ʧ��
		{
			exit(OVERFLOW); 
		} 
		for (j=0; j<i; j++)//������
		{
			(*T).ch[j] = chars[j]; 
		} 
		(*T).length = i;
	}//else
 } 
 
 void StrCopy(HString *T, HString S)
 {
 	//��ʼ��������S���ڡ�����������ɴ�S���Ƶô�T
	int i;
	
	if ((*T).ch)
	{
		free((*T).ch);//�ͷ�Tԭ�пռ� 
	} 
	(*T).ch = (char*)malloc(S.length * sizeof(char));//���䴮�ռ�
	if (! (*T).ch)//���䴮�ռ�ʧ��
	{
		exit(OVERFLOW); 
	} 
	for (i=0; i<S.length; i++)//������
	{
		(*T).ch[i] = S.ch[i]; 
	}
	
	(*T).length = S.length; 
 }
 
 Status StrEmpty(HString S)
 {
 	//��ʼ��������S���ڡ������������SΪ�մ����򷵻�TRUE�����򷵻�FALSE
	if ( S.length==0 && S.ch==NULL )
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
 }
 
 int StrCompare(HString S, HString T)
 {
 	//�� S>T,�򷵻�ֵ>0,��S=T���򷵻�ֵ=0����S<T,�򷵻�ֵ<0
	int i;
	
	for (i=0; i<S.length&&i<T.length; ++i)
	{
		if (S.ch[i] != T.ch[i])
		{
			return S.ch[i] - T.ch[i];
		}
		
		return S.length - T.length;	
	} //for
 }
 
 int StrLength(HString S)
 {
 	//����S��Ԫ�ظ�������Ϊ���ĳ���
	return S.length; 
 } 
 
 void ClearString(HString *S)
 {
 	//��S��Ϊ�մ�
	free((*S).ch);
	(*S).ch = NULL;
	(*S).length = 0; 
 }
 
 void Concat(HString *T, HString S1, HString S2)
 {
 	//��T������S1��S2���Ӷ��ɵ��´�
	int i;
	
	if ((*T).ch)
	{
		free((*T).ch);//�ͷžɿռ� 
	} 
	(*T).length = S1.length + S2.length;
	(*T).ch = (char *)malloc((*T).length * sizeof(char));
	if (! (*T).ch)
	{
		exit(OVERFLOW);
	}
	for (i=0; i<S1.length; i++)
	{
		(*T).ch[i] = S1.ch[i];
	}
	for (i=0; i<S2.length; i++)
	{
		(*T).ch[S1.length+i] = S2.ch[i];
	}//for	
 }
 
 Status SubString(HString *Sub, HString S, int pos, int len)
 {
 	//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
	//���У�1<=pos<=StrLength(S)��0<=len<=StrLength(S)-pos+1
	int i;
	
	if ( pos<1 || pos>S.length || len<0 || (len > S.length-pos+1) )
	{
		return ERROR;
	}
	 
	if ( (*Sub).ch )
	{
		free((*Sub).ch);//�ͷžɿռ� 
	}
	
	if (! len)//���Ӵ�
	{
		(*Sub).ch = NULL;
		(*Sub).length = 0;
	} 
	else
	{
		//�����Ӵ�
		(*Sub).ch = (char*)malloc(len * sizeof(char));
		if (! (*Sub).ch)
		{
			exit(OVERFLOW);
		} 
		for (i=0; i <= len-1; i++)
		{
			(*Sub).ch[i] = S.ch[pos-1+i];
		}
		(*Sub).length = len;
	}//else
	
	return OK;
 }
 
 void InitString(HString *T)
 {
 	//��ʼ���������մ����ַ���T�����
	(*T).length = 0;
	(*T).ch = NULL; 
 }
 
 int Index(HString S, HString T, int pos)
 {
 	//TΪ�ǿմ���������S�е�pos���ַ�֮�������T��ȵ��Ӵ���
	//�򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0
	int n, m, i;
	HString sub;
	
	InitString(&sub);
	
	if (pos > 0)
	{
		n = StrLength(S);
		m = StrLength(T);
		i = pos;
		while (i <= n-m+1)
		{
			SubString(&sub, S, i, m);
			if (StrCompare(sub, T) != 0)
			{
				++i;
			}
			else
			{
				return i;
			}
		}//while 
	} //if 
	return 0; 
 }
 
 Status StrInsert(HString *S, int pos, HString T)
 {
 	//1<=pos<=StrLength(S)+1���ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
	int i;
	
	if ( pos<1 || (pos > (*S).length+1) )//pos���Ϸ�
	{
		return ERROR; 
	} 
	if (T.length)// T�ǿգ������·���ռ䣬����T
	{
		(*S).ch = (char*)realloc((*S).ch, ((*S).length + T.length) *sizeof(char));
		if (! (*S).ch)
		{
			exit(OVERFLOW);
		}
		for (i=(*S).length-1; i>=pos-1; --i)//Ϊ����T���ڳ�λ��
		{
			(*S).ch[i+T.length] = (*S).ch[i]; 
		} 
		for (i=0; i<T.length; i++)
		{
			(*S).ch[pos-1+i] = T.ch[i];//����T 
		}
		(*S).length += T.length; 
	}//if-out 
	
	return OK;
 }
 
 Status StrDelete(HString *S, int pos, int len)
 {
 	//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
	int i;
	
	if ( (*S).length < (pos+len-1) )
	{
		return ERROR;
	} 
	
	for (i=pos-1; i<=(*S).length-len; i++)
	{
		(*S).ch[i] = (*S).ch[i+len];
	}
	(*S).length -= len;
	(*S).ch = (char*)realloc((*S).ch, (*S).length*sizeof(char));
	
	return OK;
 }
 
 Status Replace(HString *S, HString T, HString V)//�˺����봮�Ĵ洢�ṹ�޹�
 {
 	//��ʼ��������S��T��V���ڣ�T�Ƿǿմ�
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
		}//if  
	}while(i);
	
	return OK;	 
 } 
 
 void StrPrint(HString T)
 {
 	//���T�ַ��������
 	int i;
 	
 	for (i=0; i<T.length; i++)
 	{
	 	printf("%c", T.ch[i]);
    }
    
    printf("\n");	
 }
 
 
 
  
 