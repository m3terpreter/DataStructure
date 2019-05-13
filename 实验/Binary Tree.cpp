//Composed by Tentol
//2017.12.18
/* Binary Tree On Link List Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
/* end include & define*/

typedef int status;
typedef char TElemType;//数据元素类型定义 

typedef struct BiTNode
{
	TElemType data;
	int num; 
	struct BiTNode *lchild,*rchild;//左右孩子指针 
}BiTNode, *BiTree;

typedef struct QNode
{
	TElemType data1;
	struct QNode *next;
}QNode, *PtrQueue;

typedef struct
{
	PtrQueue front;
	PtrQueue rear;
}Queue;

typedef struct SqTree
{
	struct Tree *value;
	int length;
	int listsize;
}SqTree;

struct Tree
{
	int name;
	BiTree Trees;
};

struct Tree Treelist[100];//多树 


status InitQueue(Queue &Q)
//构造新队列Q 
{
	Q.front=Q.rear=(PtrQueue)malloc(sizeof(QNode));
	if (!Q.front)
		exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}

status DestroyQueue(Queue &Q)
//销毁队列Q 
{
	while (Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}

status EnQueue(Queue &Q,TElemType e)
//插入元素e为Q的新的队尾元素 
{
	PtrQueue p;
	p=(PtrQueue)malloc(sizeof(QNode));
	if (!p) 
		exit(OVERFLOW);
	p->data1=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}

status DeQueue(Queue &Q,TElemType &e)
//若队列不空则删除Q的队首元素，e返回其值 
{
	PtrQueue p;
	if (Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	e=p->data1;
	Q.front->next=p->next;
	if (Q.rear==p)
		Q.rear=Q.front;
	free(p);
	return OK; 
}

status InitBiTree(BiTree &T)
{
	T=NULL; 
	return OK;
}

status DestroyBiTree(BiTree &T)
{
	if(flag==0)  
		return FALSE;
	if (T)
	{
		if (T->lchild)
			DestroyBiTree(T->lchild);
		if (T->rchild)
			DestroyBiTree(T->rchild);
		free(T);
		T=NULL;
	}
	return OK;

}

status CreateBiTree(BiTree T,TElemType definition[],int number[])
//按先序次序输入二叉树中节点的值，-1表示空 
{
	if(flag==0)  
		return FALSE;
	TElemType ch;
	int num;
	ch=definition[i];
	i++
	if (ch='#')
		T=NULL;
	else
	{
		T=(BiTree)malloc(sizeof(BiTNode));
		if(!T)
			exit(OVERFLOW);
		k++;
		T->data=ch;
		T->num=num; 
		CreateBiTree(T->lchild,definition,number);
		CreateBiTree(T->rchild,definition,number);
	} 
	return OK;
}

status ClearBiTree(BiTree T)
{
	if(flag==0)  
		return FALSE;
	if (T==NULL)
		return OK;
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	free(T);
	T=NULL;
	return OK;
}
  
status BiTreeEmpty(BiTree T)
{
	if(flag==0)  
		return -1;
	if (T==NULL)
		return TRUE;
	else 
		return FALSE;
}
status Max(int a,int b)
{
	if(a>b)
		return a;
	return b;
}

status BiTreeDepth(BiTree T)
{
	if(flag==0)  
		return -1;
	if (T)
	{
		if ((T->lchild==NULL)&&(T->rchild==NULL)) 
			return 1;
		else 
			return Max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild))+1;
	}
	else 
		return 0;
}

TElemType Root(BiTree T)
{
	if(flag==0)  
		return FALSE;
	if (!T)
		return -1;
	else 
		return T->data;
}

TElemType Value(BiTree T,int m)
{
	BiTNode *st[10],*p;	
	if (T)
	{
		int top=0;
		st[top++]=T;
		while (top)
		{
			p=st[--top];
			if (p->num==m)
				return p->data;
			else
			{
				if (p->lchild!=NULL)
					st[top++]=p->lchild;
				if (p->rchild!=NULL)
					st[top++]=p->rchild;
			}
		}
	}
	else
		return -1; 
}

status Assign(BiTree T,TElemType e,TElemType v)
{
	BiTNode *st[10],*p;
	if (T)
	{
		int top=0;
		st[top++]=T;
		while (top)
		{
			p=st[--top];
			if (p->data==e)
			{
				p->data=v;
				return OK;
			}
			else
			{
				if (p->lchild!=NULL)
					st[top++]=p->lchild;
				if (p->rchild!=NULL)
					st[top++]=p->rchild;
			}
		}
	}
	else
		return ERROR;
}

BiTNode* Parent(BiTree T,TElemType e)
{
	BiTree t;
	if(T)
	{
		if (((T->lchild!=NULL)&&(T->lchild->data==e))||((T->rchild!=NULL)&&(T->rchild->data==e))) 
			return T;
		t=Parent(T->lchild,e);
		if (t!=NULL)
			return t;
		t=Parent(T->rchild,e);
		if (t!=NULL)
			return t;
	}
	return NULL;
}

BiTNode* LeftChild(BiTree T,TElemType e)
{
	BiTree t;
	if (T)
	{
		if (T->data==e)
			return T->lchild;
		t=LeftChild(T->lchild,e);
		if (t!=NULL)
			return t;
		t=LeftChild(T->rchild,e);
		if (t!=NULL)
			return t;	
	}
	else
		return NULL;
}

BiTNode* RightChild(BiTree T,TElemType e)
{
	BiTree t;
	if (T)
	{
		if (T->data==e)
			return T->rchild;
		t=RightChild(T->lchild,e);
		if (t!=NULL)
			return t;
		t=RightChild(T->rchild,e);
		if (t!=NULL)
			return t;	
	}
	else
		return NULL;
}

BiTNode* LeftSibling(BiTree T,TElemType e)
{
	BiTree t=NULL;
	if (T)
	{
		if (T->rchild!=NULL&&T->rchild->data==e)
			return T->lchild;
		t=LeftSibling(T->lchild,e);
		if (t!=NULL)
			return t;
		t=LeftSibling(T->rchild,e);
		if (t!=NULL)
			return t;
	}
	else
		return NULL;
}

BiTNode* RightSibling(BiTree T,TElemType e)
{
	BiTree t=NULL;
	if (T)
	{
		if (T->lchild!=NULL&&T->lchild->data==e)
			return T->rchild;
		t=RightSibling(T->lchild,e);
		if (t!=NULL)
			return t;
		t=RightSibling(T->rchild,e);
		if (t!=NULL)
			return t;
	}
	else
		return NULL;
}

status InsertChild(BiTree *T,BiTree *p,int LR,BiTree *c)
{
	BiTree s=*p;
	BiTree t=*c;
	if (LR==0)
	{
		if (s->lchild!=NULL)
		{
			s->rchild=s->lchild;
			s->lchild=t;
		}
		else
		{
			t->rchild=s->lchild;
			s->lchild=t;
		}
		return OK;
	}
	else if (LR==1)
	{
		if (s->rchild!=NULL)
		{
			s->lchild=s->rchild;
			s->rchild=t;
		}
		else
		{
			t->rchild=s->rchild;
			s->rchild=t;
		}
		return OK;
	}
	return ERROR;
}

status DeleteChild(BiTree T,BiTree p,int LR)
{
	BiTree s=*p;
	if (LR==0)
	{
		if (p->lchild==NULL)
			return ERROR;
		p->lchild=NULL;
		return OK;
	}
	else if (LR==1)
	{
		if (p->rchild==NULL)
			return ERROR;
		p->rchild=NULL;
		return OK;	
	}
	return ERROR;
}

status Visit(BiTree T)
{
	return T->data;
}

status PreOrderTraverse(BiTree T)
{
	if(T)
	{
		printf("%c ",Visit(T));
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	return OK;
}

status PreOrderTraverse_1(BiTree T)
{
	BiTNode *st[10],*p;
	int top=0;
	if(T!=NULL)
	{
		st[top++]=T;
		while(top)
		{
			p=st[--top];
			printf("%c ",Visit(T));
			if (p->lchild!=NULL)
				st[top++]=p->lchild;
			if (p->rchild!=NULL)
				st[top++]=p->rchild;
		}
		return OK;
	}
	else
		return ERROR;
}
status InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		printf("%c ",Visit(T));
		InOrderTraverse(T->rchild);
	}
	return OK;
}

status PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ",Visit(T));
	}
	return OK;
}

status LevelOrderTraverse(BiTree T,BiTree *p,BiTree *s)
{
	if (T==NULL)
		return FALSE;
	*p=T;
	printf("%c ",Visit(*p));
	if ((*p)->lchild!=NULL)
	{
		s++;
		*s=(*p)->lchild; 
	}
	if ((*p)->rchild!=NULL)
	{
		s++;
		*s=(*p)->rchild;
	}
	if (p!=s)
	{
		p++;
		LevelOrderTraverse(*p,p,s);
	}
	return OK;
}


int main(void)
{
	BiTree T;
	int op=1;
	int flag;
	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("		Menu for Binary Tree\n");
		printf("-------------------------------------------------------\n");
		printf("	1.InitBiTree		2.DestroyBiTree\n");
		printf("	3.CreateBiTree		4.ClearBiTree\n");
		printf("	5.BiTreeEmpty		6.BiTreeDepth\n");
		printf("	7.Root			8.Value\n");
		printf("	9.Assign		10.Parent\n");
		printf("	11.LeftChild		12.RightChild\n");
		printf("	13.LeftSibling		14.RightSibling\n");
		printf("	15.InsertChild		16.DeleteChild\n");
		printf("	17.PreOrderTraverse	18.InOrderTraverse\n");
		printf("	19.PostOrderTraverse	20.LevelOrderTraverse\n");
		printf("	21.SaveTree		22.WatchTree\n");
		printf("	23.ChangeTree	24.DeleteTree\n");
		printf("	0.Exit\n");
		printf("--------------------------------------------------------\n");
		printf("请选择操作：\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				if(InitBiTree(T)==OK)
				{
					flag=1;	
					printf("二叉树初始化成功！\n");
				}
				else
					printf("二叉树初始化失败！\n");
				getchar();getchar();
				break;
			case 2:
				if(DestroyBiTree(T)==OK)
				{
					flag=0;
					printf("二叉树删除成功！\n");
				}
				else
					printf("二叉树删除失败！\n");
				getchar();getchar();
				break;
			case 3:
				int i=0;
				int k=0;
				if (flag==0)
				{
					printf("二叉树新建失败！\n");
					getchar();getchar();
					break;
				}
				printf("请输入各结点的值（#代表空）：\n");
				scanf("%s",definition);
				printf("请输入各结点的编号（-1代表结束）：\n")
				int a;
				scanf("%d",&a);
				while (a!=-1)
				{
					number[k]=a;
					k++;
					scanf("%d",&a);
				}
				k=0;
				if (CreateBiTree(T,definition,number)==OK)
				{
					i=0;
					printf("二叉树创建成功！\n");
				}
				else 
					printf("二叉树创建失败！\n");
				getchar();getchar();
				break;
			case 4:
				if(ClearBiTree(T)==OK)
					printf("二叉树清空成功！\n");
				else 
					printf("二叉树清空失败！\n");
				getchar();getchar();
				break;
			case 5:
				if (BiTreeEmpty(T)==TRUE)
					printf("二叉树为空！\n");
				else
					printf("二叉树不为空！\n");
				getchar();getchar();
				break;
			case 6:
				if (BiTreeDepth(T)==-1)
					printf("求深度失败！\n");
				else
					printf("二叉树深度为%d\n",BiTreeDepth(T));
				getchar();getchar();
				break;
			case 7:
				if (Root(T)==ERROR)
					printf("不存在二叉树的根节点！\n");
				else
					printf("二叉树的根节点值为%c\n",Root(T));
				getchar();getchar();
				break;
			case 8:
				printf("请输入查找结点的编号：\n");
				scanf("%d",&a);
				if (Value(T,a)=='#')
					printf("")
				getchar();getchar();
				break;
			case 9:
				//if ()
			case 10:
				printf("请输入想要查找双亲的结点的名称：\n");
				scanf("%c",&In);
				if (Parent(T,In)==NULL)
					printf("双亲不存在！\n");
				else 
					printf("%c",*Parent(T,In));
				getchar();getchar();
				break;
			case 11:
				printf("请输入想要查找左儿子结点的名称：\n");
				scanf("%c",&In);
				if (LeftChild(T,In)==NULL)
					printf("查找失败！\n");
				else
					printf("左儿子结点为%c",*LeftChild(T,In));
				getchar();getchar();
				break;
			case 12:
				printf("请输入想要查找右儿子结点的名称：\n");
				scanf("%c",&In);
				if (RightChild(T,In)==NULL)
					printf("查找失败！\n");
				else
					printf("右儿子结点为%c",*RightChild(T,In));
				getchar();getchar();
				break;
			case 13:
				printf("请输入想要查找左兄弟结点的名称：\n");
				scanf("%c",&In);
				if (LeftSibling(T,In)==NULL)
					printf("查找失败！\n");
				else
					printf("左兄弟结点为%c",*LeftSibling(T,In));				
				getchar();getchar();
				break;
			case 14:
				printf("请输入想要查找右兄弟结点的名称：\n");
				scanf("%c",&In);
				if (RightSibling(T,In)==NULL)
					printf("查找失败！\n");
				else
					printf("右兄弟结点为%c",RightSibling(T,In));
				getchar();getchar();
				break; 
			case 15:break;
			case 16:break;
			case 17:break;
				
		}
	}
}
