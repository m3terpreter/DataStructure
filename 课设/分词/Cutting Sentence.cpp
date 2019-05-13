//中文分词系统
//Composed by Tentol
//2018.3.5 
//首字为“啊”，B0A1
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define WORDMAX	40			
#define MAX_SWORD_LEN 256				
#define	DICTLEN	100
#define	MAX_WORD 10000

typedef struct LNode
{
	char s[WORDMAX+1];
	struct  LNode *next;//词组结点 
}LNode,*Linklist; 

struct Dictionary{
	LNode *next;
}Dict[DICTLEN][DICTLEN];//词典 


char cutsent[MAX_WORD];//剪切后存放处 
int EOF_Flag;
int SEG_Flag=0;

int max(int a,int b)
{
	if(a>b)
		return a;
	return b;
}

int searchWord(unsigned char s[],int len)
{
	unsigned char start,end;
	LNode* cur,* tmp;
	start=s[0];
	end=s[1];
	start=start-0xA1;
	end=end-0xA1;
	cur=Dict[start][end].next;
	tmp=cur;
	while(tmp!=NULL)
	{
		if (strcmp((char *)s,tmp->s)==0)//找到 
		{
			return TRUE;
		}
		tmp=tmp->next;
	}
	return FALSE;
}

int Delete(unsigned char s[],int len)
{
	unsigned char start,end;
	LNode* cur,* tmp;
	start=s[0];
	end=s[1];
	start=start-0xA1;
	end=end-0xA1;
	cur=Dict[start][end].next;
	tmp=cur;
	LNode *p=cur;
	while(p->next!=NULL)
	{
		if (strcmp((char *)s,p->next->s)==0)//找到 
		{
			tmp=p->next;
			p->next=p->next->next;
			tmp->next=NULL;
			free(tmp);
		}
		p=p->next;
	}
}

char *Simplify(char s[])
{
	int i,first,prior,next;
	first=0;
	prior=0;
	next=0;
	for (i=0;s[i]!='\0';i++)
	{
		if (s[i]==' '||s[i]=='\n'||s[i]=='\t')
		{
			if (first==0)
				prior++;
		}
		else
		{
			next=i;
			first=i;
		}
	}
	for (i=prior;i<=next;i++)
	{
		s[i-prior]=s[i];//去除空格换行 
	}
	s[i-prior]='\0';
	return s;
}

int addDict(char *s)//建立词典索引 
{
	unsigned char first,second;
	LNode* cur,* newWord ,*tmp ;
	first=s[0] ;
	second=s[1];
	if (first<0xA1||second<0xA1)//非汉字 
		  return ERROR;
	newWord=(LNode*)malloc(sizeof(LNode));
	if (newWord==NULL)
		return ERROR;
	strcpy(newWord->s,s);
	newWord->next=NULL;
	first=first-0xA1;second=second-0xA1;
	cur=Dict[first][second].next;
	if(cur==NULL)	
	{
		Dict[first][second].next=newWord;
		return 0;
	}
	tmp=cur; 
	while(tmp->next!=NULL)
	{
		tmp=tmp->next;	
	}
	tmp->next=newWord;
	return 0;
}

int loadDict(char *Filename)//从文件中读取 
{
	int len=0;
	int i,j;
	FILE *fp;
	unsigned char firstChar,lastChar;
	char sLine[128];
    for (i=0;i<DICTLEN;i++) 
	{
    	for (j=0;j<DICTLEN;j++) 
		{
    		Dict[i][j].next= (LNode *)NULL;
    	}
    }
	fp=fopen(Filename,"r");
	if (fp==NULL) 
	{
		 printf("Error!\n",Filename);
		 return ERROR;	
	}
	while ( !feof(fp)) {
		fgets(sLine,128,fp);
		Simplify(sLine);//删掉无用字符 
		len = strlen(sLine);
		if ( len < 1 || len > WORDMAX )
			printf("%s error!\n",sLine);
		addDict(sLine);		
	}	
    fclose(fp);
    return OK;
}

void addSegWord(unsigned char *s ,int len)//分隔算法 
{
	char *c=(char *)s;
	strcat(cutsent,c);
	strcat(cutsent,"|");
	SEG_Flag=SEG_Flag+len+1;
}

int segWord(unsigned char *strText,int wordlen,int If_Chi)
{
	int i,j,k,l,temp;
	i=0;j=0;k=0;l=0;
	temp=0;
	unsigned char strChar[WORDMAX+1];//过渡字符串 
	int If_Found=FALSE;
	i=wordlen; 
	if (If_Chi==FALSE)// not Chinese
	{		
		addSegWord(strText,wordlen);
		return 0;	
	}
	while (i>1)//i为未匹配字数  
	{	
		for(j=WORDMAX;j>=2;j-=2)//正向最大匹配算法 
		{			
			if (i<j)//句长小于最大词长 
				continue;   
			l=0;
			for(k=temp,l=0;k<temp+j;k++,l++)
				strChar[l]=strText[k];
			strChar[l]='\0';
			if (j==2) //单个汉字 
			{
				addSegWord(strChar,2);
				i-=2;
				temp+=j;
				break;
			} 
			If_Found = searchWord(strChar,l);//在词典中匹配 
			if (If_Found==TRUE)//找到 
			{
				i-=j;
				temp+=j;
				addSegWord(strChar,l);
				break; 
			} 
		} 
	}
	return 0;
}

int isAsciiSymbol (char c)//是否为英文字符 
{
	char Ascii[] ={'!','\\','*','(',')','-','_','+','{','}','[',']',':',';','\'','\"','<','>','.','?','/','|','@','#','$','%','^','&'};
	for(int i=0;i<28;i ++ ) 
		if (c==Ascii[i])
			return TRUE;
	return FALSE;
}

int segSentence (char *strText ,int If_Space ) 
{	
	unsigned char c;
	int iTextLen=strlen(strText);
	int wordlen=0;//未处理 
	int	i=0,iNexti=0,If_Sep=FALSE,If_Chi=FALSE,If_Found=FALSE,If_Sym=FALSE;
	//If_Sep是否为分隔符，If_Chi上个有效字的类型（中文TRUE）
	//If_Found找到，If_Sym是否标点 
	unsigned char s[MAX_SWORD_LEN+1],strChar[3];
	memset(s,0,sizeof(s));
	strChar[0] = '\0';
	for (i=0;i<iTextLen;i++)
	{
		c=(unsigned char)strText[i];
		if (c<128)//为英文字符 
		{		
			if(c=='\n'||c==' '||c=='\t'||c=='\r')
			{
				if (If_Chi==TRUE)//上个有效字符为中文 
				{		
					if (If_Space==TRUE&&(c=='\t'||c==' ')) 
						If_Sep=TRUE;			
					else 
						continue ;//换行空格隔开情况			
				} 
				else  
					If_Sep=TRUE;
			}
			else
			{ 						
				If_Sym=isAsciiSymbol(c);//看是否英文标点	
				If_Sep=If_Sym;
			} 
			if ((If_Sep==TRUE||If_Chi==TRUE)&&wordlen>=0)//当一个单词结束 
			{		
				if (wordlen>MAX_SWORD_LEN)
					wordlen=MAX_SWORD_LEN;
				s[wordlen] = '\0';//找一句可以断开的话   
				segWord(s,wordlen,If_Chi);
				wordlen=0;
				if (If_Sym==TRUE)
				{
					s[0]=c;
					s[1]='\0';
					addSegWord(s,1);
				}//对标点进行操作 
			}
			if (If_Sep==FALSE)
			{
				s[wordlen]=c;//同一个单词字母合并输出	
				wordlen++;
			}
			If_Chi=FALSE;    
		}  
		else//下面处理中文 
		{						
			if(If_Chi==FALSE&&If_Sep==FALSE&&wordlen>0)//英文碰到汉字情况，代表英文结束 
			{
				if(wordlen>MAX_SWORD_LEN)
					wordlen=MAX_SWORD_LEN;
				s[wordlen]='\0';
				If_Found=FALSE;
				if(If_Found==FALSE)
				{
					segWord(s,wordlen,If_Chi);
				} 
				wordlen = 0 ;
			} 
			iNexti=i+1;
			if (iNexti<iTextLen)
			{
				if(((unsigned char)strText[iNexti])<128)//单字符<128则不作处理 
					continue;					
			} 
			else 			
				break;//大于128跳出 
			strChar[0] = strText[i];
			strChar[1] = strText[i+1];
			strChar[2] = '\0';//此情况为应对>128的情况	
			If_Chi=TRUE;//若汉字只加1就行了			
			i++;				
			if (strChar[0]==0xA1&&strChar[1]==0xA1)//中文空格0xA1,0xA1 
			{			
				if (If_Space==TRUE)
					If_Sep=TRUE;
				else
					continue ;//连续中文空格				
			}
			else if (strChar[0]<0xB0)//中文标点 
			{
				If_Sep=TRUE;
				If_Sym=TRUE;
			}
			else 
				If_Sep=FALSE;
			if(TRUE==If_Sep&&wordlen>=0)
			{
				if(wordlen>MAX_SWORD_LEN )
					wordlen = MAX_SWORD_LEN;
				s[wordlen]='\0';
				segWord(s,wordlen,If_Chi);
				wordlen=0 ;
				if(If_Sym==TRUE)
				{
					addSegWord(strChar,2);
				}//分隔标点输出 
			} 
			if (FALSE==If_Sep)
			{
				s[wordlen++] = strChar[0];
				s[wordlen++] = strChar[1];
			}
		}
	}
	if(wordlen>0)//若还有未处理单词 
	{					
		if ( wordlen > MAX_SWORD_LEN )
			 wordlen = MAX_SWORD_LEN;
		s[wordlen] = '\0';
		segWord(s,wordlen,If_Chi);
		wordlen=0;	
	}
	return 0;
}

int freeSeg()
{
	FILE *fp;
	fp=fopen("output.txt","w");
	if(fp==NULL)
	{
		printf("Error!\n");
		return ERROR;
	}
	fwrite(cutsent,SEG_Flag,1,fp);//输出到文件中 
	fclose(fp);
	return 0;
}

int Save()
{
	FILE *fp;
	int i,j;
	LNode *curLst,*curTmp,*tmp;
	fp=fopen("dict.txt","w");
	for (i=0;i<DICTLEN;i++)
	{
		for (j=0;j<DICTLEN;j++)
		{
			curLst=Dict[i][j].next;
			curTmp=curLst;
			while(curTmp!=NULL)
			{
				fputs(curTmp->s,fp);
				fputc('\n',fp);//将索引保存在文件中 
				curTmp=curTmp->next;
			}
	    }
	}
	fclose(fp); 
}

int ReadIn(char *word)
{ 
	FILE *fp;
	int i;
    for (i=0;i<MAX_WORD;i++)
    		word[i]='\0';
	fp=fopen("input.txt","r");
	if(fp==NULL)
	{
		printf("Error!\n");
		return ERROR;
	}
	fseek(fp,0,SEEK_END);//SEEK_SET文件头,SEE_CUR当前,SEEK_END尾 
	EOF_Flag=ftell(fp);//定位文件尾 
	rewind(fp);//定位句首 
	fread(word,EOF_Flag,1,fp);//从句首读到句尾 
	fclose(fp);
}

int main()
{
	char word[MAX_WORD]; 
	ReadIn(word);
	int op=1;
	while(op)
	{
		system("cls");
		printf("            中文分词操作菜单\n");
		printf("-----------------------------------------\n");
		printf("|	1.读入词典	2.查询词条	|\n");
		printf("|	3.添加词条	4.删除词条	|\n");
		printf("|	5.开始分词	6.保存词典	|\n");
		printf("|	0.退出系统			|\n"); 
		printf("-----------------------------------------\n");
		printf("请选择操作（0~6）：\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				if(loadDict("Dictionary.txt")==OK)
				{
					printf("载入词典成功！\n");
					getchar();getchar();
					break;
				}
				else
				{
					printf("载入失败！\n");
					getchar();getchar();
					break;
				}
			case 2:
				unsigned char u[WORDMAX];
				printf("请输入要查询的词：\n"); 
				scanf("%s",u);
				if (searchWord(u,WORDMAX)==TRUE) printf("存在\n");
				else printf("不存在\n");
				getchar();getchar();
				break;
			case 3:
				char y[100];
				printf("请输入要添加的词：\n"); 
				scanf("%s",y);
				addDict(y);
				printf("添加成功！\n");
				getchar();getchar();
				break;
			case 4:
				unsigned char z[100];
				printf("请输入要删除的词：\n");
				scanf("%s",z);
				if (searchWord(z,WORDMAX)==FALSE)
				{
					printf("输入错误！该词不存在！\n");
					getchar();getchar();
					break;
				}
				else
				{
					Delete(z,32);
					printf("删除成功！\n");
					getchar();getchar();
					break;
				}
			case 5:
				segSentence(word,FALSE);
				freeSeg();
				printf("分词成功！\n"); 
				getchar();getchar();
				break;
			case 6:
				Save();
				printf("保存成功！\n");
				getchar();getchar();
				break;
			case 0:
				break;
		}
	}
	printf("欢迎下次使用本系统！\n"); 
	return 0 ;
}
