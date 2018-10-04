#ifndef BITREE_H
#define BITREE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include <iostream>
#include <string>
using namespace std;


#define Jie 4 //表示是 2-3 树

typedef struct User{
	unsigned int number; //借书证号码
	struct User *next;  //下一个借阅者
}User;                  //定义用户的的信息


typedef struct Book{
	unsigned int key;      //图书的书号
    char bname[20];        // 书名
    char writter[20];      // 著者 
    unsigned int left;     // 现存量
    unsigned int total;    // 总存量
	User *user;            //借阅该书的人
}Book;                     //定义书的信息



typedef struct BTNode{
	int keynum; //结点中关键字个数，即结点的大小
	struct BTNode *parent; //指向双亲结点
	Book key[Jie+1];  //关键字向量， 0 号单元没有用
	struct BTNode *ptr[Jie+1]; //子树指针向量
}BTNode,*BTree;


typedef struct{
	BTNode *pt;  //指向找到的结点
 	int i;  //1……Jie，在结点中的关键字序号
	int tag; //B- 树的查找结果类型
}Result;

class Library {
public:
	BTNode *root;
	bool buyBook(Book my_book);
	Result searchBook(Book my_book);
	int deleteBook(Book my_book);
	int borrowBook(Book my_book);
	int backBook(Book my_book);
	void showBook(int k);
};


int ReturnBook(BTree T, Book k);

int combine(BTree &root, BTree &p);

int fix(BTree &root, BTree p);


//输入书的具体信息
void InBookMess(Book &book);
//输入书的关键字
void InBookKey(Book &book);
//显示书的具体信息,如果书存在就显示
void ShowBookMess(Book book);
//显示一个结点中所包含的全部信息,显示单个结点
string ShowBTNode(BTree p);
//查找在某个结点中的位置
int Search(BTree p, Book K);

Result SearchBTree(BTree T, Book K);

void Insert(BTree &q, int i, Book x, BTree ap);
//分裂结点
void split(BTree &q, int s, BTree &ap);
//生成一个新的结点
void NewRoot(BTree &T, BTree p, Book x, BTree ap);

int InsertBTree(BTree &T, Book K);
//与右最左结点交换
void exchange(BTree &T,int i);
//用户借阅的登记与还
int BorrowBook(BTree T,Book k);
int ReturnBook(BTree T, Book k);

#endif