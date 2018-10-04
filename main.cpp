#include "btree.h"
#pragma warning(disable:4996)


//�˵�����ʾ,�������û����ص�ѡ��
char menu_selete(){
	char ch;

	//system("cls");	
	printf("\t**************** ����ͼ�����ϵͳ ***************\n");
    printf("\t*\t\t1.¼������Ϣ\t\t\t* \n");
    printf("\t*\t\t2.��������Ϣ\t\t\t* \n");
    printf("\t*\t\t3.��ʾ����Ϣ\t\t\t* \n");
    printf("\t*\t\t4.ɾ������Ϣ\t\t\t* \n");
	printf("\t*\t\t5.����ͼ��  \t\t\t* \n");
	printf("\t*\t\t6.�黹ͼ��  \t\t\t* \n");
	printf("\t*\t\t7.�˳�ϵͳ  \t\t\t* \n");
    printf("\t*************************************************\n\n");
	printf("\t\t��ѡ��������Ҫ�Ĳ���(1~7):");
	do{		
		ch = getch(); 
	}while(ch < '1' || ch > '7');
	return ch;
}


void main(){
	BTree root = NULL; //����
	Library zzz_lib;
	zzz_lib.root=root;
	Book k;
	Result rs;  //���ҵĽ��

	
	while(1){
		switch(menu_selete()){
		case '1':
			system("cls");
			InBookMess(k);
			zzz_lib.buyBook(k);
			printf("\t\t\t\t�����������");
	        getch();
			break;
		case '2':
			system("cls");
	        printf("\t\t****************** ��������Ϣ *****************\n\n");
			InBookKey(k);
			printf("\n");
			rs = zzz_lib.searchBook(k);			
			if(rs.tag == 1)
				ShowBookMess(rs.pt->key[rs.i]);
			else
				printf("\t\t\t\t��Ҫ���ҵ���� %d ������!\n\n",k.key);	
			printf("\n\t\t****************** ���ҽ��� *****************\n");
			printf("\t\t\t\t�����������");
			getch();
			break;
		case '3':
			system("cls");
	        printf("\t\t****************** ȫ������ *****************\n\n");
			zzz_lib.showBook(0);
			printf("\t\t****************** ��ʾ��� *****************\n");
			printf("\t\t\t\t�����������");
			getch();
			break;
		case '4':
			char select;
			system("cls");
			printf("\t\t****************** ɾ���� *****************\n\n");
			printf("\t\t\tѡ��ɾ����ʽ  \t\t\t \n");
			printf("\t\t\t1.�������ͼ��  \t\t\t \n");
			printf("\t\t\t2.ɾ��ĳ��ͼ��  \t\t\t \n");
			printf("\t\t��ѡ��������Ҫ�Ĳ���(1~2):\n\t\t\t");
			do {
				select = getch();
			} while (select < '1' || select > '2');
			if (select == '1')
			{
				printf("\n\t\t\tɾ��֮�󲻿��һأ�ȷ��(Y/N)  \t\t\t \n");
				char so = getch();
				if (so == 'Y' || so == 'y') {
					free(zzz_lib.root);
					zzz_lib.root = NULL;
					printf("\t\t\t������  \t\t\t \n");
				}
				printf("\n\t\t\t\t�����������");
				getch();
				break;
			}
			else {
				InBookKey(k);
				if (zzz_lib.deleteBook(k) == 1) {
					printf("\t\t\t\tɾ�� %d �ɹ�!\n\n", k.key);
				}
				else {
					printf("\t\t\t\tɾ�� %d ʧ��!\n\n", k.key);
				}
				printf("\n\t\t\t\t�����������");
				getch();
				break;
			}
		case '5':
			system("cls");
			printf("\t\t****************** ���� *****************\n\n");
			InBookKey(k);
			zzz_lib.borrowBook(k);
			printf("\n\t\t\t\t�����������");
			getch();			
			break;
		case '6':
			system("cls");
			printf("\t\t****************** ���� *****************\n\n");
			InBookKey(k);
			if(zzz_lib.backBook(k))
				printf("\n\t\t\t�黹�ɹ�!\n");
			else
				printf("\n\t\t\t�黹ʧ��!\n");
			printf("\n\t\t\t\t�����������");
			getch();
			break;
		case '7':
			printf("\n\n\n\t\t\t");
			exit(0);
		}
	}
}