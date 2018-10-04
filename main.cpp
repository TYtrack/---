#include "btree.h"
#pragma warning(disable:4996)


//菜单的显示,并接受用户返回的选项
char menu_selete(){
	char ch;

	//system("cls");	
	printf("\t**************** 西文图书管理系统 ***************\n");
    printf("\t*\t\t1.录入书信息\t\t\t* \n");
    printf("\t*\t\t2.查找书信息\t\t\t* \n");
    printf("\t*\t\t3.显示书信息\t\t\t* \n");
    printf("\t*\t\t4.删除书信息\t\t\t* \n");
	printf("\t*\t\t5.借阅图书  \t\t\t* \n");
	printf("\t*\t\t6.归还图书  \t\t\t* \n");
	printf("\t*\t\t7.退出系统  \t\t\t* \n");
    printf("\t*************************************************\n\n");
	printf("\t\t请选择你所需要的操作(1~7):");
	do{		
		ch = getch(); 
	}while(ch < '1' || ch > '7');
	return ch;
}


void main(){
	BTree root = NULL; //树根
	Library zzz_lib;
	zzz_lib.root=root;
	Book k;
	Result rs;  //查找的结果

	
	while(1){
		switch(menu_selete()){
		case '1':
			system("cls");
			InBookMess(k);
			zzz_lib.buyBook(k);
			printf("\t\t\t\t按任意键返回");
	        getch();
			break;
		case '2':
			system("cls");
	        printf("\t\t****************** 查找书信息 *****************\n\n");
			InBookKey(k);
			printf("\n");
			rs = zzz_lib.searchBook(k);			
			if(rs.tag == 1)
				ShowBookMess(rs.pt->key[rs.i]);
			else
				printf("\t\t\t\t你要查找的书号 %d 不存在!\n\n",k.key);	
			printf("\n\t\t****************** 查找结束 *****************\n");
			printf("\t\t\t\t按任意键返回");
			getch();
			break;
		case '3':
			system("cls");
	        printf("\t\t****************** 全部的书 *****************\n\n");
			zzz_lib.showBook(0);
			printf("\t\t****************** 显示完毕 *****************\n");
			printf("\t\t\t\t按任意键返回");
			getch();
			break;
		case '4':
			char select;
			system("cls");
			printf("\t\t****************** 删除书 *****************\n\n");
			printf("\t\t\t选择删除方式  \t\t\t \n");
			printf("\t\t\t1.清除所有图书  \t\t\t \n");
			printf("\t\t\t2.删除某本图书  \t\t\t \n");
			printf("\t\t请选择你所需要的操作(1~2):\n\t\t\t");
			do {
				select = getch();
			} while (select < '1' || select > '2');
			if (select == '1')
			{
				printf("\n\t\t\t删除之后不可找回，确定(Y/N)  \t\t\t \n");
				char so = getch();
				if (so == 'Y' || so == 'y') {
					free(zzz_lib.root);
					zzz_lib.root = NULL;
					printf("\t\t\t库存清空  \t\t\t \n");
				}
				printf("\n\t\t\t\t按任意键返回");
				getch();
				break;
			}
			else {
				InBookKey(k);
				if (zzz_lib.deleteBook(k) == 1) {
					printf("\t\t\t\t删除 %d 成功!\n\n", k.key);
				}
				else {
					printf("\t\t\t\t删除 %d 失败!\n\n", k.key);
				}
				printf("\n\t\t\t\t按任意键返回");
				getch();
				break;
			}
		case '5':
			system("cls");
			printf("\t\t****************** 借阅 *****************\n\n");
			InBookKey(k);
			zzz_lib.borrowBook(k);
			printf("\n\t\t\t\t按任意键返回");
			getch();			
			break;
		case '6':
			system("cls");
			printf("\t\t****************** 还书 *****************\n\n");
			InBookKey(k);
			if(zzz_lib.backBook(k))
				printf("\n\t\t\t归还成功!\n");
			else
				printf("\n\t\t\t归还失败!\n");
			printf("\n\t\t\t\t按任意键返回");
			getch();
			break;
		case '7':
			printf("\n\n\n\t\t\t");
			exit(0);
		}
	}
}