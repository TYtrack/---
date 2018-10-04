#include "btree.h"
#pragma warning(disable:4996)


//������ĵ���Ϣ
int InUserMess(User *user){
	char s[5];
	printf("\n\n\t\t\t��������ߵ���Ϣ\n");
	printf("\t\t\t������ͼ��֤��:");
	do{
		scanf("%s",s);
		user->number = atoi(s);
		if(user->number < 1 || user->number > 65535){
			printf("\t\t\t��������,����������(0��65535֮��):");
		}
	}while(user->number < 1 || user->number > 65535);
	user->next = NULL;
	return 1;
}

//����,���һ������Դ��������㣬����һ�����Ǽǽ����ŵ�ͼ��֤�ź͹黹����
int BorrowBook(BTree T,Book k){
	Result rs = SearchBTree(T,k);
	User *user;
	if(rs.tag == 0){
		printf("\t\t\t�ܱ�Ǹ!��Ҫ���ĵ��鲻����!\n");
		return 0;
	}
	if(rs.pt->key[rs.i].left < 1){
		printf("\t\t\t�ܱ�Ǹ!��Ҫ���ĵ������޿��!\n");
		return 0;
	}
	user = (User *)malloc(sizeof(User));
	InUserMess(user);
	//���Ҹ��û��Ƿ��Ѿ�����Ȿ��
	User *temp;
	temp = rs.pt->key[rs.i].user;
	while(temp){
		if(temp->number == user->number){
			printf("\n\t\t\t���Ѿ������Ȿ�飬���ܹ��ظ���!\n");			
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

//ע���Խ����ߵĵǼǣ��ı������Դ���
int ReturnBook(BTree T,Book k){
	User *user,*pre;
	int number;
	Result rs = SearchBTree(T,k);
	if(rs.tag == 0){
		printf("\t\t\t�ܱ�Ǹ!��������Ҫ������!\n");
		return 0;
	}
	user = rs.pt->key[rs.i].user;
	if(!user){
		printf("\t\t\t�Ȿ�����޳���!\n");
		return 0;
	}
	printf("\n\t\t\t������ͼ��֤��:");
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
	printf("\t\t\t�������ͼ��֤�Ų���ȷ!�����²���!\n");
	return 0;
}

//��ʾĳ��������Ϣ
void ShowWriterBook(BTree p,char writer[]) {
  for(int i = 1; i <= p->keynum; i++){
	  if(strcmp(p->key[i].writter,writer) == 0){
		  printf("\t\t\t���Ϊ:%d   ", p->key[i].key);
		  printf("����Ϊ:%s   ",p->key[i].bname);
		  printf("����Ϊ:%3s\n", p->key[i].writter);
	  }
  }
}

//��ʾ����������Ϣ
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


