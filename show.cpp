#include "btree.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream> 
#pragma warning(disable:4996)

//������ľ�����Ϣ
void InBookMess(Book &book){	
	char s[5];
	printf("\t\t\t���������:");
	do{		
		scanf("%s",s);
		book.key = atoi(s);
		if(book.key < 1 || book.key > 65535){
			printf("\t\t\t������������������:");
		}
	}while(book.key < 1 || book.key > 65535);
	
	printf("\t\t\t����������:");
	scanf("%s",&book.bname);
	printf("\t\t\t����������:");
	scanf("%s",&book.writter);

	printf("\t\t\t����������:");
	do{
		scanf("%s",s);
		book.total = atoi(s);
		if(book.total < 1 || book.total > 65535){
			printf("\t\t\t������������������:");
		}
	}while(book.total < 1 || book.total > 65535);

	book.left = book.total;
	book.user = NULL;
	//book.user = (User *)malloc(sizeof(User));	
}

//������Ĺؼ���
void InBookKey(Book &book){	
	char s[5];
	printf("\t\t\t���������:");
	do{		
		scanf("%s",s);
		book.key = atoi(s);
		if(book.key < 1 || book.key > 65535){
			printf("\t\t\t������������������:");
		}
	}while(book.key < 1 || book.key > 65535);

	book.bname[0] = '\0';
	book.writter[0] = '\0';
	book.total = 0;
	book.left = 0;
}

//��ʾ��ľ�����Ϣ
void ShowBookMess(Book book){
	printf("\t\t\t���Ϊ:%3d\n", book.key);
	printf("\t\t\t����Ϊ:%3s\n", book.bname);
	printf("\t\t\t����Ϊ:%3s\n", book.writter);
	printf("\t\t\t���Ϊ:%3d\n", book.left);
	printf("\t\t\t����Ϊ:%3d\n", book.total);
	printf("\n");
}

//��ʾĳ��������Ϣ
string ShowBTNode(BTree p) {
	string as = "";
	if(!p)
		return "";
	printf("(");
	as += "(";
	int j = p->keynum;
	for(int i = 1; i <= p->keynum; i++){
		printf("���Ϊ:%d", p->key[i].key);
		stringstream sz;
		sz << p->key[i].key;
		as += sz.str();
		j--;
		if(j){
			printf(",----");
			as += ",----";
		}
	}
	printf(")\n");	
	as += ")\n";
	return as;
}
