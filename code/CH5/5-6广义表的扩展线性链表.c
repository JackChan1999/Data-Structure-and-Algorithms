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
 typedef char AtomType;//����ԭ������Ϊ�ַ��� 
 
 typedef enum{ATOM, LIST}ElemTag;//ATOM==0:ԭ�ӣ�LIST==1���ӱ�
 typedef struct GLNode1
 {
 	ElemTag tag;//�������֣���������ԭ�ӽ��ͱ���
    union//ԭ�ӽ��ͱ�������ϲ���
	{
		AtomType atom;//ԭ�ӽ���ֵ��
		struct GLNode1 *hp;//����ı�ͷָ�� 	
	}a;  
	struct GLNode1 *tp;//�൱�����������next��ָ����һ��Ԫ�ؽ�� 
 }*GList1, GLNode1;//���������GList��һ����չ���������� 
 
 #define MAX_STR_LEN 40 //������255(1���ֽ�)���ڶ�����󴮳�
 typedef char SString[MAX_STR_LEN+1];//0�ŵ�Ԫ��Ŵ��ĳ���
 #define DestroyString ClearString //DestroyString()��ClearString()������ͬ
 
 
Status StrAssign(SString T, char *chars);
void StrCopy(SString T, SString S);
Status StrEmpty(SString S);
int StrCompare(SString S, SString T);
int StrLength(SString S);
void ClearString(SString S);
Status Concat(SString T, SString S1, SString S2);
Status SubString(SString Sub, SString S, int pos, int len);
int Index(SString S, SString T, int pos);
Status StrInsert(SString S, int pos, SString T);
Status StrDelete(SString S, int pos, int len);
Status Replace(SString S, SString T, SString V);//�˺����봮�Ĵ洢�⹹�޹�
void StrPrint(SString T);
void sever(SString str, SString hstr);//SString�����飬������������
void InitGList(GList1 *L);
void CreateGList(GList1 *L, SString S);
void DestroyGList(GList1 *L);
void CopyGList(GList1 *T, GList1 L);
int GListLength(GList1 L);
int GListDepth(GList1 L);
Status GListEmpty(GList1 L);
GList1 GetHead(GList1 L);
GList1 GetTail(GList1 L);
void InsertFirst_GL(GList1 *L, GList1 e);
void DeleteFirst_GL(GList1 *L, GList1 *e);
void Traverse_GL(GList1 L, void(*v)(AtomType));
void visit(AtomType e);
 
 
 int main()
 {
   char p[80];
   GList1 l,m;
   SString t;
   InitGList(&l); /* �����յĹ����l */
   printf("�չ����l�����=%d l�Ƿ�գ�%d(1:�� 0:��)\n",GListDepth(l),GListEmpty(l));
   printf("����������l(��д��ʽ���ձ�:(),��ԭ��:(a),����:(a,(b),c)):\n");
   gets(p);
   StrAssign(t,p);
   CreateGList(&l,t);
   printf("�����l�ĳ���=%d\n",GListLength(l));
   printf("�����l�����=%d l�Ƿ�գ�%d(1:�� 0:��)\n",GListDepth(l),GListEmpty(l));
   printf("���������l��\n");
   Traverse_GL(l,visit);
   printf("\n���ƹ����m=l\n");
   CopyGList(&m,l);
   printf("�����m�ĳ���=%d\n",GListLength(m));
   printf("�����m�����=%d\n",GListDepth(m));
   printf("���������m��\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetHead(l);
   printf("\nm��l�ı�ͷԪ�أ�����m��\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetTail(l);
   printf("\nm����l�ı�β�γɵĹ�������������m��\n");
   Traverse_GL(m,visit);
   InsertFirst_GL(&m,l);
   printf("\n��������lΪm�ı�ͷ�����������m��\n");
   Traverse_GL(m,visit);
   DeleteFirst_GL(&m,&l);
   printf("\nɾ��m�ı�ͷ�����������m��\n");
   Traverse_GL(m,visit);
   printf("\n");
   DestroyGList(&m);
   
   return 0; 
 }
 

 Status StrAssign(SString T, char *chars)
 {
 	//����һ����ֵ����chars�Ĵ�T
	int i;
	
	if (strlen(chars) > MAX_STR_LEN)
	{
		return ERROR; 
	} 
	else
	{
		T[0] = strlen(chars);
		for (i=1; i<=T[0]; i++)
		{
			T[i] = *(chars+i-1);
		}
		return OK;
	}//else
 } 
 
 void StrCopy(SString T, SString S)
 {
 	//�ɴ�S���Ƶô�T
	int i;
	
	for (i=0; i<=S[0]; i++)
	{
		T[i] = S[i];
	} 
 } 
 
 Status StrEmpty(SString S)
 {
 	//��SΪ�մ����򷵻�TRUE�����򷵻�FALSE
	if (S[0] == 0)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}	
 }
 
 int StrCompare(SString S, SString T)
 {
 	//��ʼ��������S��T���ڡ������������S>T,�򷵻�ֵ>0;
	//��S=T,�򷵻�ֵ=0����S<T,�򷵻�ֵ<0
	int i;
	
	for (i=1; i<=S[0] && i<=T[0]; ++i)
	{
		if (S[i] != T[i])
		{
			return S[i] - T[i];
		}
	} 
	
	return S[0] - T[0];
 }
 
 int StrLength(SString S)
 {
 	//���ش�S��Ԫ�ظ���
	return S[0]; 
 }
 
 void ClearString(SString S)
 {
 	//��ʼ��������S���ڡ������������S��Ϊ�մ�
	S[0] = 0;//���Ϊ�� 
 }
 
 Status Concat(SString T, SString S1, SString S2)
 {
 	//�� T����S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�TRUE������FALSE
	int i;
	
	if (S1[0]+S2[0] <= MAX_STR_LEN)
	{
		//δ�ض� 
		for (i=1; i<=S1[0]; i++)
		{
			T[i] = S1[i];
		} 
		for (i=1; i<=S2[0]; i++)
		{
			T[S1[0]+i] = S2[i];
		}
		T[0] = S1[0] +S2[0];
		
		return TRUE;	
	}//if
	else
	{
		//�ض�S2
		for (i=1; i<=S1[0]; i++)
		{
			T[i] = S1[i];
		} 
		for (i=1; i <= MAX_STR_LEN-S1[0]; i++)
		{
			T[S1[0]+i] = S2[i];
		}
		T[0] = MAX_STR_LEN;
		
		return FALSE;
	} 
 } 
 
 Status SubString(SString Sub, SString S, int pos, int len)
 {
 	//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���
	int i;
	
	if ( pos<1 || pos>S[0] || len<0 || len>(S[0]-pos+1) )
	{
		return ERROR;
	} 
	for (i=1; i<=len; i++)
	{
		Sub[i] = S[pos+i-1];
	}
	Sub[0] = len;
	
	return OK;
 }
 
 int Index(SString S, SString T, int pos)
 {
 	//�����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ�����ֵΪ0
	//���У�T�ǿգ�1<=pos<=StrLength(S)��
	int i, j;
	
	if ( 1<=pos && pos<=S[0] )
	{
		i = pos;
		j = 1;
		
		while ( i<=S[0] && j<=T[0] )
		{
			if (S[i] == T[j])//�����ȽϺ���ַ�
			{
				++i;
				++j; 
			} 
			else//ָ��������¿�ʼƥ�� 
			{
				i = i-j+2;
				j = 1; 
				
			}
		}//while
		if (j > T[0])
		{
			return i - T[0];
		}
		else
		{
			return 0;
		}
	}//if
	else
	{
		return 0;
	}//else 
 }
 
 Status StrInsert(SString S, int pos, SString T)
 {
 	//��ʼ��������S��T���ڣ�1<=pos<=StrLength(S)+1
	//����������ڴ�S�ĵ�pos���ַ�֮ǰ���봮T����ȫ���뷵��TRUE��
	//���ֲ��뷵��FALSE
	int i;
	
	if (pos<1 || pos>(S[0]+1))
	{
		return ERROR;
	} 
	if (S[0]+T[0] <= MAX_STR_LEN)
	{
		//��ȫ���� 
		for (i=S[0]; i>=pos; i--)
		{
			S[i+T[0]] = S[i];
		}
		for (i=pos; i<pos+T[0]; i++)
		{
			S[i] = T[i-pos+1];
		}
		S[0] += T[0];
		
		return TRUE;
	}//if
	else
	{
		//���ֲ���
		for (i=MAX_STR_LEN; i>=pos+T[0]; i--)
		{
			S[i] = S[i-T[0]];
		} 
		for(i=pos; i<pos+T[0] && i<=MAX_STR_LEN; i++)
		{
			S[i] = T[i-pos+1];
		}
		S[0] = MAX_STR_LEN;
		
		return FALSE;
	}//else
	
 }
 
 Status StrDelete(SString S, int pos, int len)
 {
 	//��ʼ��������S���ڣ�1<=pos<=StrLength(S)-len+1
	//����������Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
	int i;
	
	if (pos<1 || pos>S[0]-len+1 || len<0)
	{
		return ERROR;
	} 
	for(i=pos+len; i<=S[0]; i++)
	{
		S[i-len] = S[i];
	}
	S[0] -= len;
	
	return OK;
 }
 
 Status Replace(SString S, SString T, SString V)//�˺����봮�Ĵ洢�⹹�޹�
 {
 	//��ʼ��������S��T��V���ڣ�T�Ƿǿմ�
	//�����������V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
	int i = 1;//�Ӵ�S�ĵ�һ���ַ�����Ҵ�T
	Status k;
	
	if ( StrEmpty(T) )//T�ǿմ�
	{
		return ERROR; 
	} 
	do
	{
		i = Index(S, T, i);//���iΪ����һ��i֮���ҵ����Ӵ�T��λ��
		if (i)//��S�д��ڴ�T
		{
			StrDelete(S, i, StrLength(T));//ɾ���ô�T
			k = StrInsert(S, i, V);//��ԭ��T��λ�ò��봮V
			if (!k)//������ȫ����
			{
				return ERROR; 
			} 
			i += StrLength(V);//�ڲ���Ĵ�V����������Ҵ�T 
		}//if 
	}while (i);
	
	return OK;
 } 
 
 void StrPrint(SString T)
 {
 	//����ַ���T�����
	int i;
	for (i=1; i<=T[0]; i++)
	{
		printf("%c", T[i]);
	} 
	printf("\n");
 }
 
 void sever(SString str, SString hstr)//SString�����飬������������
 {
 	//���ǿմ�str�ָ�������֣�hstrΪ��һ��������֮ǰ���Ӵ���strΪ֮����Ӵ�
	int n, k, i;//k����δ��Ե������Ÿ���
	SString ch, c1, c2, c3;
	
	n = StrLength(str);//nΪ��str�ĳ���
	StrAssign(c1, ",");//c1=','
	StrAssign(c2, "(");//c2='('
	StrAssign(c3, ")");//c3=')'
	SubString(ch, str, 1, 1);//chΪ��str�ĵ�1���ַ�
	
	for (i=1, k=0; i<=n && StrCompare(ch, c1) || k!=0; ++i)//iС�ڴ�����ch���ǡ�����
	{
		//���������ĵ�һ������
		SubString(ch, str, i, 1);//chΪ��str�ĵ�i���ַ�
		if (! StrCompare(ch, c2))//ch='('
		{
			++k;//�����Ÿ���+1 
		}
		else if (! StrCompare(ch, c3))//ch=')'
		{
			--k;//�����Ÿ���-1 
		}	 
	} 
	
	if (i<=n)//��str�д��ڡ�����,���ǵ�i-1���ַ�
	{
		SubString(hstr, str, 1, i-2);//hstr���ش�str������ǰ���ַ�
		SubString(str, str, i, n-i+1);//str���ش�str','����ַ� 
	} 
	else//��str�в����ڡ����� 
	{
		StrCopy(hstr, str);//��hstr���Ǵ�str
		ClearString(str);//','�����ǿմ� 	
	}//else	 
 } 
 
 
 void InitGList(GList1 *L)
 {
 	//�����յĹ����L
	*L = NULL; 
 } 
 
 void CreateGList(GList1 *L, SString S)
 {
 	//������չ��������洢�ṹ���ɹ�������д��ʽ��S���������L����emp=��������
	SString emp, sub, hsub;
	GList1 p;
	
	StrAssign(emp, "()");//��emp="()"
	*L = (GList1)malloc(sizeof(GLNode1));
	if (! *L)//�����㲻�ɹ�
	{
		exit(OVERFLOW); 
	} 
	if (! StrCompare(S, emp))//�����ձ�
	{
		(*L)->tag = LIST;
		(*L)->a.hp = (*L)->tp = NULL;
	} 
	else if (StrLength(S) == 1)//������ԭ�ӹ���� 
	{
		(*L)->tag = ATOM;
		(*L)->a.atom = S[1];
		(*L)->tp = NULL; 
	}
	else//����һ��� 
	{
		(*L)->tag = LIST;
		(*L)->tp = NULL;
		SubString(sub, S, 2, StrLength(S)-2);//��������� (ȥ����1���ַ������1���ַ�)����sub 
		sever(sub, hsub);//��sub�з������ͷ��hsub
		CreateGList(&(*L)->a.hp, hsub); 
		p = (*L)->a.hp;
		while (! StrEmpty(sub))//��β���գ����ظ���n���ӱ�
		{
			sever(sub, hsub);//��sub�з������ͷ��hsub 
			CreateGList(&p->tp, hsub);
			p = p->tp; 
		}//while 	
	}//else	
 }
 
 void DestroyGList(GList1 *L)
 {
 	//��ʼ�����������L���ڡ�������������ٹ����L
	GList1 ph, pt;
	
	if (*L) //L��Ϊ�ձ� 
	{
		//��ph��pt����L������ָ��
		if ((*L)->tag)//���ӱ�
		{
			ph = (*L)->a.hp; 
		} 
		else//��ԭ�� 
		{
			ph = NULL; 	
		}
		pt = (*L)->tp;
		DestroyGList(&ph);//�ݹ����ٱ�ph
		DestroyGList(&pt);//�ݹ����ٱ�pt
		free(*L);//�ͷ�L��ָ��� 
		*L = NULL;//��LΪ�� 
	} //if 
 }
 
 void CopyGList(GList1 *T, GList1 L)
 {
 	//��ʼ�����������L���ڡ�����������ɹ����L���Ƶõ������T
	*T = NULL;
	
	if (L)//L����
	{
		*T = (GList1)malloc(sizeof(GLNode1));
		
		if (!*T)
		{
			exit(OVERFLOW);
		}  
		(*T)->tag = L->tag;//����ö�ٱ���
		if (L->tag == ATOM)//���ƹ����岿��
		{
			(*T)->a.atom = L->a.atom;//���Ƶ�ԭ�� 	
		} 
		else
		{
			CopyGList(&(*T)->a.hp, L->a.hp);//�����ӱ� 
		} 
		if (L->tp == NULL)//����β
		{
			(*T)->tp = L->tp;
		} 
		else
		{
			CopyGList(&(*T)->tp, L->tp);//�����ӱ� 
		}//else 
	}//if 	 
 } 
 
 int GListLength(GList1 L)
 {
 	//��ʼ�����������L���ڡ����������������L�ĳ��ȣ���Ԫ�ظ���
	int len = 0;
	GList1 p = L->a.hp;//pָ���1��Ԫ��
	
	while (p)
	{
		len++;
		p = p->tp;
	} 
	
	return len;
 }
 
 int GListDepth(GList1 L)
 {
 	//��ʼ�����������L���ڡ����������������L�����
	int max, dep;
	GList1 pp;
	
	if (L==NULL || L->tag==LIST && !L->a.hp)
	{
		return 1;//�ձ����Ϊ1 
	}
	else if (L->tag == ATOM)
	{
		return 0;//��ԭ�ӱ����Ϊ0��ֻ������ڵݹ������ 
	} 
	else//��һ������� 
	{
		for (max=0, pp=L->a.hp; pp; pp=pp->tp)
		{
			dep = GListDepth(pp);//����ppΪͷָ����ӱ����
			if (dep > max)
			{
				max = dep;
			} 
		} //for	
	} 
	return max+1;//�ǿձ������Ǹ�Ԫ�ص���ȵ����ֵ��1	 
 }
 
 Status GListEmpty(GList1 L)
 {
 	//��ʼ�����������L���ڡ�����������ж������L�Ƿ�Ϊ��
	if (!L || L->tag==LIST && !L->a.hp)
	{
		return OK;
	} 
	else
	{
		return ERROR;
	}
 } 
 
 GList1 GetHead(GList1 L)
 {
 	//���ɹ����L�ı�ͷԪ�أ�����ָ�����Ԫ�ص�ָ��
	GList1 h, p;
	
	if (!L || L->tag==LIST && !L->a.hp)//�ձ��ޱ�ͷ
	{
		return NULL; 
	} 
	p = L->a.hp->tp;//pָ��L�ı�β
	L->a.hp->tp = NULL;//��ȥL�ı�β����
	CopyGList(&h, L->a.hp);//����ͷԪ�ظ��Ƹ�h 
	L->a.hp->tp = p;//�ظ�L�ı�β������ԭL���䣩
	
	return h; 
 }
 
 GList1 GetTail(GList1 L)
 {
 	//�������L�ı�β����Ϊ�����,����ָ������¹�����ָ��
	GList1 t, p;
	
	if (!L || L->tag==LIST && !L->a.hp)//�ձ��ޱ�β
	{
		return NULL; 
	} 
	p = L->a.hp;//pָ���ͷ
	L->a.hp = p->tp;//��L��ɾȥ��ͷ
	CopyGList(&t, L);//��L�ı�β����t
	L->a.hp = p;//�ָ�L�ı�ͷ������ԭL���䣩
	
	return t; 
 }
 
 void InsertFirst_GL(GList1 *L, GList1 e)
 {
 	//��ʼ�������������ڡ��������������Ԫ��e(Ҳ�������ӱ�)
	//��Ϊ�����L�ĵ�1Ԫ��(��ͷ)
	GList1 p = (*L)->a.hp;
	(*L)->a.hp = e;
	e->tp = p; 
 }
 
 void DeleteFirst_GL(GList1 *L, GList1 *e)
 {
 	//��ʼ�����������L���ڡ����������ɾ�������L�ĵ�һԪ�أ�����e������ֵ
	if (*L && (*L)->a.hp)
	{
		*e = (*L)->a.hp;
		(*L)->a.hp = (*e)->tp;
		(*e)->tp = NULL;
	} 
	else
	{
		*e = *L;
	}
 }
 
 void Traverse_GL(GList1 L, void(*v)(AtomType))
 {
 	//���õݹ��㷨���������L
	GList1 hp;
	
	if (L)//L����
	{
		if (L->tag == ATOM)//LΪ��ԭ��
		{
			v(L->a.atom);
			hp = NULL; 
		} 
		else//LΪ�ӱ� 
		{
			hp = L->a.hp; 
		}
		
		Traverse_GL(hp, v);
		Traverse_GL(L->tp, v);
	} 
 }
 
 void visit(AtomType e)
 {
   printf("%c ", e);
 }
 
 
 
 
 
 