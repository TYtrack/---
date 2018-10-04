#include "btree.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream> 
#pragma warning(disable:4996)

//输入书的具体信息
void InBookMess(Book &book){	
	char s[5];
	printf("\t\t\t请输入书号:");
	do{		
		scanf("%s",s);
		book.key = atoi(s);
		if(book.key < 1 || book.key > 65535){
			printf("\t\t\t输入有误，请重新输入:");
		}
	}while(book.key < 1 || book.key > 65535);
	
	printf("\t\t\t请输入书名:");
	scanf("%s",&book.bname);
	printf("\t\t\t请输入作者:");
	scanf("%s",&book.writter);

	printf("\t\t\t请输入总量:");
	do{
		scanf("%s",s);
		book.total = atoi(s);
		if(book.total < 1 || book.total > 65535){
			printf("\t\t\t输入有误，请重新输入:");
		}
	}while(book.total < 1 || book.total > 65535);

	book.left = book.total;
	book.user = NULL;
	//book.user = (User *)malloc(sizeof(User));	
}

//输入书的关键字
void InBookKey(Book &book){	
	char s[5];
	printf("\t\t\t请输入书号:");
	do{		
		scanf("%s",s);
		book.key = atoi(s);
		if(book.key < 1 || book.key > 65535){
			printf("\t\t\t输入有误，请重新输入:");
		}
	}while(book.key < 1 || book.key > 65535);

	book.bname[0] = '\0';
	book.writter[0] = '\0';
	book.total = 0;
	book.left = 0;
}

//显示书的具体信息
void ShowBookMess(Book book){
	printf("\t\t\t书号为:%3d\n", book.key);
	printf("\t\t\t书名为:%3s\n", book.bname);
	printf("\t\t\t著者为:%3s\n", book.writter);
	printf("\t\t\t库存为:%3d\n", book.left);
	printf("\t\t\t总量为:%3d\n", book.total);
	printf("\n");
}

//显示某个结点的信息
string ShowBTNode(BTree p) {
	string as = "";
	if(!p)
		return "";
	printf("(");
	as += "(";
	int j = p->keynum;
	for(int i = 1; i <= p->keynum; i++){
		printf("书号为:%d", p->key[i].key);
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
