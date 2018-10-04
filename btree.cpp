#include "btree.h"
#pragma warning(disable:4996)



bool Library::buyBook(Book my_book) {
	printf("\t\t------------------ 录入书信息 -----------------\n");
	InsertBTree(root, my_book);
	printf("\t\t\t--------- 录入结束 ---------\n\n");
	printf("\t\t\t当前书库的库存信息如下：\n");
	showBook(0);
	return 1;
}

void Library::showBook(int k) {
	string logmess = "";
	int i = 0;
	BTNode *T = root;
	if (T) {
		for (i = 0; i <= k - 1; i++) {
			printf("\t");	  //用空格来显示第几层
			logmess += "\t";
		}
		if (k != 0) {
			printf("\t+--->");
			logmess += "\t+--->";
		}
		else {
			printf("\t");
			logmess += "\t";
		}
		logmess += ShowBTNode(T);	//显示这个结点的全部值	
		for (i = 0; i <= T->keynum; i++) { //使用递归的方法显示每个结点	
			if (T->ptr[i]) {
				Library para;
				para.root = T->ptr[i];
				para.showBook(k + 1);
			}
		}
	}
}

Result Library::searchBook(Book my_book) {
	BTree p, q=NULL;
	int found=0, i=0;
	Result R;
	p = root;
	while (p && !found) {
		i = Search(p, my_book);                 // 找到待查关键字                  
		if (i > 0 && p->key[i].key == my_book.key)
			found = 1;
		else {
			q = p;
			p = p->ptr[i]; //在另一个分支上查找
		}
	}
	if (found) {  // 查找成功
		R.pt = p;
		R.i = i;
		R.tag = 1;
	}
	else {     
		R.pt = q;
		R.i = i;
		R.tag = 0;
	}
	// 返回结果信息: K的位置(或插入位置)
	return R;
}

int Library::borrowBook(Book my_book) {
	Result R = searchBook(my_book);
	User *user;
	if (R.tag == 0) {
		printf("\t\t\t很抱歉!你要借阅的书不存在!\n");
		return 0;
	}
	if (R.pt->key[R.i].left < 1) {
		printf("\t\t\t很抱歉!你要借阅的书已经借完!\n");
		return 0;
	}
	user = (User *)malloc(sizeof(User));
	char s[5];
	printf("\n\n\t\t\t输入借阅者的信息\n");
	printf("\t\t\t请输入图书证号:");
	do {
		scanf("%s", s);
		user->number = atoi(s);
		if (user->number < 1 || user->number > 65535) {
			printf("\t\t\t输入有误,请重新输入(0到65535之间):");
		}
	} while (user->number < 1 || user->number > 65535);
	user->next = NULL;


	R.pt->key[R.i].left--;
	user->next = R.pt->key[R.i].user;
	R.pt->key[R.i].user = user;
	printf("\t\t\t恭喜!!!借阅成功!\n");
	return 1;

};

int Library::backBook(Book my_book) {
	User *user, *pre;
	int number;
	Result R = searchBook(my_book);

	
	if (R.tag == 0) {
		printf("\t\t\t很抱歉!不存在你要还的书!\n");
		return 0;
	}
	user = R.pt->key[R.i].user;
	if (!user) {
		printf("\t\t\t这本书暂无出借!\n");
		return 0;
	}
	printf("\n\t\t\t请输入图书证号:");
	scanf("%d", &number);
	pre = user;
	do {
		if (user->number == number) {
			if (user == R.pt->key[R.i].user) {
				R.pt->key[R.i].user = user->next;
				free(user);
			}
			else {
				pre->next = user->next;
				free(user);
			}
			R.pt->key[R.i].left++;
			return 1;
		}
		pre = user;
		user = user->next;
	} while (user);
	printf("\t\t\t你输入的图书证号不正确!请重新操作!\n");
	return 0;
}

int Library::deleteBook(Book my_book) {
	if (root == NULL) {              //如果还没有录入过书,就直接返回
		printf("\t\t\t书库为空!\n");
		return 0;
	}
	BTree p;                         //查找到的指针
	Result R;                     //查找的结果
	int i = 0, sk = 0;
	R = searchBook(my_book);
					         		 //如果该 B- 树中不包含该 k 就返回 false
	if (R.tag == 0) {                    //如果查找失败
		printf("\t\t\t删除失败!不存在你想要删除的信息!\n");
		return 0;
	}
	p = R.pt;                          //将查找到的结点赋值给 p
	i = R.i;                                                  //在结点中的位置	
	exchange(p, i);                                //将该结点的值和最右下左角的值交换
	if (p->keynum >= (Jie + 1) / 2 - 1) {        
		return 1;
	}
	                                   //下面的表示 p->keynum == 0
	if (p == root) {                    //当只有根结点的时候
		free(root);                     //把根结点释放掉
		root = NULL;                           //把删除的结点赋值为空                      
		return 1;
	}
	while (p) {                                 //其他的情况
		if (p == root || p->keynum >= (Jie + 1) / 2 - 1 || !p->parent)        //如果p结点删除后还有元素
			return 1;             //用于循环结束的条件          
		else {                    //否则就要向左右两边借元素
			if (fix(p->parent, p) == 1)  //判断能不能借，可以借就直接返回
				return 1;
		}
		combine(p->parent, p);
		p = p->parent;
		if ((p == root || !p->parent) && p->keynum == 0) {  //如果合并后父结点变成空
			root = p->ptr[0];
			free(p);
			p = root;
			root->parent = NULL;
			return 1;
		}
	}
	return 1;
}

//复制结点,将某个结点的值复制到另外一个值上  bookTrancerse
void BookTranverse(Book &bak,Book k){
	bak.key = k.key;
	strcpy(bak.bname,k.bname);
	bak.left = k.left;
	bak.total = k.total;
	strcpy(bak.writter,k.writter);
	bak.user = k.user;
}

//在一个结点中查找元素,返回结点的位置
int Search(BTree p, Book K) {	
	if(!p)
		return -1;
	int i=0;
    for(i = 0; i < p->keynum && p->key[i+1].key <= K.key; i++);
    return i;
}

// 在m阶B树T上查找关键字K，返回结果(pt,i,tag)
Result SearchBTree(BTree T, Book K){ 
   BTree p, q;
   int found, i;
   Result R;
   //初始化变量
   p = T; 
   q = NULL; 
   found = 0; 
   i = 0; 
   // 初始化，p指向待查结点，q指向p的双亲
   while (p && !found) {
      i = Search(p, K); 
      // 找到待查关键字                  
      if (i > 0 && p->key[i].key == K.key) 
		  found = 1;    
      else { 
		  q = p;  
		  p = p->ptr[i]; //在另一个分支上查找
	  }
   }
   if (found) {  // 查找成功
     R.pt = p; 
	 R.i = i;  
	 R.tag = 1;  
   } 
   else {      // 查找不成功
     R.pt = q;  
	 R.i = i; 
	 R.tag = 0; 
   }
   // 返回结果信息: K的位置(或插入位置)
   return R;              
}

//插入一条记录
void Insert(BTree &q, int i, Book x, BTree ap) {
	int n = q->keynum;	
	for (int j = n; j > i; j--) { //腾出空间		
		BookTranverse(q->key[j + 1],q->key[j]); //复制结点值
		q->ptr[j + 1] = q->ptr[j];
	}
	BookTranverse(q->key[i + 1],x);	
	q->ptr[i + 1] = ap;
	if (ap) 
		ap->parent = q;  
	q->keynum++;
}

//分离结点
void split(BTree &q, int s, BTree &ap) {
  int i,j,n = q->keynum;
  ap = (BTree)malloc(sizeof(BTNode));
  ap->ptr[0] = q->ptr[s];
  for (i = s + 1,j = 1; i <= n; i++,j++) {
	BookTranverse(ap->key[j],q->key[i]);
    ap->ptr[j] = q->ptr[i];
  }
  ap->keynum = n - s;
  ap->parent = q->parent;
  for (i = 0; i <= n - s; i++)     
    if (ap->ptr[i]) 
		ap->ptr[i]->parent = ap;
  q->keynum = s-1;
}

//生成一个新的树结点
void NewRoot(BTree &T, BTree p, Book x, BTree ap) {
  T = (BTree)malloc(sizeof(BTNode));

  T->keynum = 1;  
  T->ptr[0] = p;  //设置左边结点的树根
  T->ptr[1] = ap;  //设置右边的树根  
  BookTranverse(T->key[1],x);  //将 x 元素的结点值复制到 T 的第一个元素中
                          //当孩子不空的时候就设置当前结点为孩子的双亲
  if (p) 
	  p->parent= T;        
  if (ap) 
	  ap->parent = T;  
  T->parent = NULL;  //当前结点的双亲为空
}

//返回 false 表示在原有结点上增加数量，返回 true 表示创建了一个新的结点
int InsertBTree(BTree &T, Book K) {
  // 在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K。
  // 若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B树。
  BTree ap;
  Result R;
  BTree q;
  int i;
  char addnum;
  int finished, needNewRoot, s;
  // T是空树(参数q初值为NULL)
  Book x;
  //如果 T 结点为空就生成一个新的结点
  if (!T){                      
    NewRoot(T, NULL, K, NULL); 
  }
  else {
	//查找元素 k 在树中的位置
    R = SearchBTree(T,K);
	q = R.pt; //查找到包含元素 k 的结点
    i = R.i;  //元素 k 在树中的位置
    if(R.tag == 1){  //判断该元素在树中是否存在
		if(strcmp(q->key[i].bname,K.bname) != 0){
			printf("\n\t\t\t录入失败，原因:\n");
			printf(".\t\t\t书号冲突，请重新为该书编号!\n\n");
			printf("\t\t\t已经存在书号为 %d 的书为:\n",q->key[i].key);
			ShowBookMess(q->key[i]);
			return 0;
		}
	    printf("\n\t\t\t该书已经存在!\n\n");
		ShowBookMess(q->key[i]);
	    return 0;
	}
    x = K;  
	ap = NULL; 
	finished = needNewRoot = 0;     
    while (!needNewRoot && !finished) {
      Insert(q, i, x, ap);  //插入结点

	  int kk = Search(q->parent, q->key[1]);
	  cout << "a!!!!!" <<kk<< "\n";
      if (q->keynum < Jie) 
		  finished = 1;  // 插入完成

	  else {  // 分裂结点*q
		  cout << "zzzqd\n";
        s = (Jie+1)/2;
		split(q, s, ap);  
		x = q->key[s];
        if (q->parent) {  // 在双亲结点*q中查找x的插入位置
          q = q->parent; 
		  i = Search(q, x);  
        } 
		else 
			needNewRoot = 1;
      } 
    } 
    if (needNewRoot)        // 根结点已分裂为结点*q和*ap
      NewRoot(T, q, x, ap); // 生成新根结点*T,q和ap为子树指针
  }

  return 1;
}

//一个结点在双亲中的位置,返回其位置 i
int position(BTree T){
	if(!T){
		return 0;
	}
	int i = 0;
	if(T->parent){
		while(i <= T->parent->keynum){
			if(T == T->parent->ptr[i])
				return i; //返回当前的位置
			i++;
		}
	}
	return -1;
}

//调整树的结构
int fix(BTree &root,BTree p){
	int i = position(p);  //取得p 在双亲中的位置
	int mid = (Jie + 1)/2 - 1;  //要交换的临界点
	BTree temp = NULL;
	int k;
	if(i > 0 && root->ptr[i - 1]->keynum > mid){  //当 i 大于零的时候就可以向左借
		temp = root->ptr[i - 1]; //比自己小的兄弟结点
		p->keynum++; //增加一个结点
		for(k = p->keynum;k > 1;k--){
			BookTranverse(p->key[k],p->key[k - 1]); //将前面的结点后移一位
		}
		if(p->ptr[0]){
			for(k = p->keynum;k >= 1;k--){
				p->ptr[k] = p->ptr[k - 1]; //将要移动的结点的子结点向后移动
			}
		}
		BookTranverse(p->key[1],root->key[i]); //将双亲的结点复制到根
		BookTranverse(root->key[i],temp->key[temp->keynum]); //将小兄弟结点的最大的那个移动到双亲中
		if(temp->ptr[temp->keynum]){  //将兄弟结点的子结点也复制过来
			p->ptr[0] = temp->ptr[temp->keynum]; 
			temp->ptr[temp->keynum]->parent = p; //修改指向双亲的结点
			temp->ptr[temp->keynum] = NULL;
		}
		temp->keynum--;  //将左兄弟删除一个结点
		return 1;
	}
	if(i < root->keynum && root->ptr[i + 1]->keynum > mid){ //当 i 小于最大数量的时候就可以向右借
		temp = root->ptr[i + 1];
		p->keynum++;  //增加结点的个数
		BookTranverse(p->key[p->keynum],root->key[i + 1]); //将根结点的值复制过来
		BookTranverse(root->key[i + 1],temp->key[1]);  //将右兄弟的结点复制过来
		for(k = 1;k < temp->keynum;k++){
			BookTranverse(temp->key[k],temp->key[k + 1]); //将后面的结点向前移动一位
		}
		if(temp->ptr[0]){
			p->ptr[p->keynum] = temp->ptr[0];
			temp->ptr[0]->parent = p;  //修改指向双亲的结点
			for(k = 0;k < temp->keynum;k++){ //将子结点向前移动
				temp->ptr[k] = temp->ptr[k + 1];
			}
			temp->ptr[k + 1] = NULL;   //将删除的结点的子结点置为空
		}
		temp->keynum--;  //将右兄弟删除一个结点
		return 1;
	}
	return 0;
}

//合并结点
int combine(BTree &root,BTree &p){
	int k,i = position(p);  //取得p 在双亲中的位置
	int mid = (Jie + 1)/2 - 1; //交换的条件
	BTree p2;
	if(i == 0){  //如果是第一个位置
		i = 1;
		p2 = root->ptr[i];
		p->keynum++; //增加一个结点
		BookTranverse(p->key[p->keynum],root->key[i]); //将双亲的结点复制下来
		if(p2->ptr[0]){
			p->ptr[p->keynum] = p2->ptr[0]; //将兄弟的子结点也复制过来
			p2->ptr[0]->parent = p; //修改双亲
		}		
		for(k = i;k < root->keynum;k++){ //将双亲的结点向前移动一位
			BookTranverse(root->key[k],root->key[k + 1]);
		}
		p->keynum++;
		p->key[p->keynum] = p2->key[1];
		if(p2->ptr[1]){
			p->ptr[p->keynum] = p2->ptr[1]; //将兄弟的子结点也复制过来
			p2->ptr[1]->parent = p;  
		}		
		root->keynum--;
		free(p2);
		p2 = NULL;
		for(k = 1;k <= root->keynum;k++){
			root->ptr[k] = root->ptr[k + 1]; //将双亲结点子结点向前移动
		}
		root->ptr[k + 1] = NULL;
	}
	else if(i > 0){
		p2 = root->ptr[i - 1];		
		p2->keynum++;
		BookTranverse(p2->key[p2->keynum],root->key[i]); //复制根结点的值到子结点中
		if(p->ptr[0]){
			p2->ptr[p2->keynum] = p->ptr[0];
			p->ptr[0]->parent = p2; //修改指向双亲的结点
		}				
		for(k = i;k < root->keynum;k++){
			BookTranverse(root->key[k],root->key[k + 1]); //将结点前移
			root->ptr[k] = root->ptr[k + 1]; //将子结点前移			
		}
		root->ptr[k + 1] = NULL;
		root->keynum--;
		free(p); 
		p = p2;
	}
	return 1;
}

//与右最左结点交换
void exchange(BTree &T,int i){
	BTree p = T;
	User *user = NULL;
	if(p->ptr[i]){
		p = p->ptr[i];
		while(p->ptr[0]){
			p = p->ptr[0];		
		}
		while(T->key[i].user){
			user = T->key[i].user;  //指向要释放的结点
			T->key[i].user = T->key[i].user->next; //指向下一个结点
			free(user);  //释放借阅者的信息
		}
		BookTranverse(T->key[i],p->key[1]);  //交换数据
		int j = 1;
		while (j < p->keynum) { //将该结点后面的数据后移
			BookTranverse(p->key[j], p->key[j + 1]); //将后一个数据复制到前一个数据
			j++;
		}
	}
	
	
	p->keynum--;  //删除结点
	T = p;
	return;
}
