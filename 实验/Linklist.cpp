#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef int ElemType;
typedef int status;

typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node,*Linklist;

int k=0,m,flag=0; 

void Create(Node **headp,int *p)
{
	Node *loc_head=NULL,*tail;
	if (*p==0);
	else
	{
		loc_head=(Node*)malloc(sizeof(Node));
		loc_head->data=*p++;
		tail=loc_head;
		while(*p)
		{
			tail->next=(Node*)malloc(sizeof(Node));
			tail=tail->next;
			tail->data=*p++;	
		}
		tail->next=NULL;
	}
	*headp=loc_head;
}

Node* Insert(Node* head,int n)
{
	Node *current=head,*after,*other;
	while(current->data!=n&&current!=NULL)
		current=current->next;
	if (!current)
		return NULL;
	after=current->next;
	other=(Node*)malloc(sizeof(Node));
	other->data=m;
	if (after)
	{
		other->next=after;
		current->next=other;
	}
	else
	{
		other->next=NULL;
		current->next=other;
	}
	return current;
}


Node *Delete(Node **headp,int n)
{
	Node *current=*headp,*prior=*headp;
	while(current->data!=n&&current!=NULL)
	{
		prior=current;
		current=current->next;
	}
	if (!current)
		return NULL;
	if (current==*headp)
		*headp=current->next;
	else
		prior->next=current->next;
	free(current);
	return current;
}

Node* Find(Node* head,int n)
{
	Node *tp=head;
	k++;
	if (tp)
	{
		if (tp->data==n)
			return tp;
		else
			Find(tp->next,n);
	}
	else 
		return NULL;
}

status Change(Node* head,int n,int m)
{
	Node *t=Find(head,n);
	if (t==NULL)
		return 0;
	t->data=m;
	return 1; 
}

status Traverse(Node *head)
{
	Node *p=head;
	printf("链表的值分别为：\n");
	while (p)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	return 1;
}

void DeleteAll(Node *head)
{
	Node *p=head,*temp;
	while (p!=NULL)
	{
		temp=p;
		p=p->next;
		free(temp); 
	}
	flag=1;
}

int main()
{
	Node *head=NULL,*p;
	int n[10]={1,2,3,4,5,6,0};
	Create(&head,n);
	int op=1,num;
	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("	Menu For Linklist\n");
		printf("--------------------------------------\n");
		printf("	1.Insert	2.Delete\n");
		printf("	3.Search	4.Change\n");
		printf("	5.Traverse	6.DeleteAll\n");
		printf("	0.Exit\n");
		printf("--------------------------------------\n");
		printf("Please Choose Option:[0~6]\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				{
					printf("请输入想要在哪个结点的值后面插入：\n");
					scanf("%d",&num);
					printf("请输入要插入的值：\n");
					scanf("%d",&m);
					if (Insert(head,num)==NULL)
					{
						printf("插入失败，未找到该结点！\n");
						getchar();getchar();
						break;
					}
					else
					{ 
						printf("插入成功！\n");
						getchar();getchar();
						break;
					}
				}
			case 2:
				{
					printf("请输入想要删除结点的值：\n");
					scanf("%d",&num);
					if(Delete(&head,num)==NULL)
					{
						printf("删除失败，未找到该结点！\n");
						getchar();getchar();
						break;
					}
					else
					{
						printf("删除成功！\n"); 
						getchar();getchar();
						break;
					} 
				}
			case 3:
				{
					printf("请输入想要查询的值：\n");
					scanf("%d",&num);
					if(Find(head,num)==NULL)
					{
						printf("查询失败，未找到结点！\n");
						k=0;
						getchar();getchar();
						break;
					}
					else
					{
						k=0;
						p=Find(head,num);
						printf("查找成功！\n");
						printf("该结点为第%d个结点",k);
						k=0;
						getchar();getchar();
						break;
					}
				}
			case 4:
				{
					printf("请输入要更改的值：\n");
					scanf("%d",&num);
					printf("请输入要改变的值：\n");
					scanf("%d",&m);
					k=0;
					if (Change(head,num,m)==0)
					{
						printf("操作失败！\n");
						k=0;
						getchar();getchar();
						break; 
					}
					else 
					{
						printf("操作成功！\n");
						Change(head,num,m);
						k=0;
						getchar();getchar();
						break;
					}
				} 
			case 5:
				{
					if(flag==1)
					{
						printf("链表为空！\n");
						getchar();getchar();
						break;
					}
					else
					{
						Traverse(head);
						getchar();getchar();
						break;
					}
					
				}
			case 6:
				{
					DeleteAll(head);
					printf("操作成功！\n");
					getchar();getchar();
					break;
				}
			case 0:
				{
					break; 
				}
					 
		}//end of switch
	}//end of while
	printf("欢迎您的下次使用！\n");
	getchar();
	return 0;
}

