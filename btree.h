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


#define Jie 4 //��ʾ�� 2-3 ��

typedef struct User{
	unsigned int number; //����֤����
	struct User *next;  //��һ��������
}User;                  //�����û��ĵ���Ϣ


typedef struct Book{
	unsigned int key;      //ͼ������
    char bname[20];        // ����
    char writter[20];      // ���� 
    unsigned int left;     // �ִ���
    unsigned int total;    // �ܴ���
	User *user;            //���ĸ������
}Book;                     //���������Ϣ



typedef struct BTNode{
	int keynum; //����йؼ��ָ����������Ĵ�С
	struct BTNode *parent; //ָ��˫�׽��
	Book key[Jie+1];  //�ؼ��������� 0 �ŵ�Ԫû����
	struct BTNode *ptr[Jie+1]; //����ָ������
}BTNode,*BTree;


typedef struct{
	BTNode *pt;  //ָ���ҵ��Ľ��
 	int i;  //1����Jie���ڽ���еĹؼ������
	int tag; //B- ���Ĳ��ҽ������
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


//������ľ�����Ϣ
void InBookMess(Book &book);
//������Ĺؼ���
void InBookKey(Book &book);
//��ʾ��ľ�����Ϣ,�������ھ���ʾ
void ShowBookMess(Book book);
//��ʾһ���������������ȫ����Ϣ,��ʾ�������
string ShowBTNode(BTree p);
//������ĳ������е�λ��
int Search(BTree p, Book K);

Result SearchBTree(BTree T, Book K);

void Insert(BTree &q, int i, Book x, BTree ap);
//���ѽ��
void split(BTree &q, int s, BTree &ap);
//����һ���µĽ��
void NewRoot(BTree &T, BTree p, Book x, BTree ap);

int InsertBTree(BTree &T, Book K);
//���������㽻��
void exchange(BTree &T,int i);
//�û����ĵĵǼ��뻹
int BorrowBook(BTree T,Book k);
int ReturnBook(BTree T, Book k);

#endif