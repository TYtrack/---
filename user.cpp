#include "btree.h"
#pragma warning(disable:4996)


//输入借阅的信息
int InUserMess(User *user){
	char s[5];
	printf("\n\n\t\t\t输入借阅者的信息\n");
	printf("\t\t\t请输入图书证号:");
	do{
		scanf("%s",s);
		user->number = atoi(s);
		if(user->number < 1 || user->number > 65535){
			printf("\t\t\t输入有误,请重新输入(0到65535之间):");
		}
	}while(user->number < 1 || user->number > 65535);
	user->next = NULL;
	return 1;
}

//借阅,如果一种书的显存量大于零，则借出一本，登记借阅着的图书证号和归还期限
int BorrowBook(BTree T,Book k){
	Result rs = SearchBTree(T,k);
	User *user;
	if(rs.tag == 0){
		printf("\t\t\t很抱歉!你要借阅的书不存在!\n");
		return 0;
	}
	if(rs.pt->key[rs.i].left < 1){
		printf("\t\t\t很抱歉!你要借阅的书已无库存!\n");
		return 0;
	}
	user = (User *)malloc(sizeof(User));
	InUserMess(user);
	//查找该用户是否已经借过这本书
	User *temp;
	temp = rs.pt->key[rs.i].user;
	while(temp){
		if(temp->number == user->number){
			printf("\n\t\t\t你已经借了这本书，不能够重复借!\n");			
			free(user);
			return 0;
		}
		temp = temp->next;
	}
	rs.pt->key[rs.i].left--;
	user->next = rs.pt->key[rs.i].user;
	rs.pt->key[rs.i].user = user;
	return 1;
}

//注销对借阅者的登记，改变该书的显存量
int ReturnBook(BTree T,Book k){
	User *user,*pre;
	int number;
	Result rs = SearchBTree(T,k);
	if(rs.tag == 0){
		printf("\t\t\t很抱歉!不存在你要还的书!\n");
		return 0;
	}
	user = rs.pt->key[rs.i].user;
	if(!user){
		printf("\t\t\t这本书暂无出借!\n");
		return 0;
	}
	printf("\n\t\t\t请输入图书证号:");
	scanf("%d",&number);	
	pre = user;
	do{
		if(user->number == number){
			if(user == rs.pt->key[rs.i].user){
				rs.pt->key[rs.i].user = user->next;
				free(user);
			}
			else{
				pre->next = user->next;
				free(user);
			}
			rs.pt->key[rs.i].left++;
			return 1;
		}
		pre = user;
		user = user->next;
	}while(user);
	printf("\t\t\t你输入的图书证号不正确!请重新操作!\n");
	return 0;
}

//显示某个结点的信息
void ShowWriterBook(BTree p,char writer[]) {
  for(int i = 1; i <= p->keynum; i++){
	  if(strcmp(p->key[i].writter,writer) == 0){
		  printf("\t\t\t书号为:%d   ", p->key[i].key);
		  printf("书名为:%s   ",p->key[i].bname);
		  printf("作者为:%3s\n", p->key[i].writter);
	  }
  }
}

//显示整棵树的信息
void displayAuthor(BTree T,char writer[]){
	int i = 0;
	if(T) { 
		ShowWriterBook(T,writer);
		for(i=0; i<=T->keynum; i++){	
			if(T->ptr[i]){
				displayAuthor(T->ptr[i],writer);
			}
		}
	}
}


