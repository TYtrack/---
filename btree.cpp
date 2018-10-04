#include "btree.h"
#pragma warning(disable:4996)



bool Library::buyBook(Book my_book) {
	printf("\t\t------------------ ¼������Ϣ -----------------\n");
	InsertBTree(root, my_book);
	printf("\t\t\t--------- ¼����� ---------\n\n");
	printf("\t\t\t��ǰ���Ŀ����Ϣ���£�\n");
	showBook(0);
	return 1;
}

void Library::showBook(int k) {
	string logmess = "";
	int i = 0;
	BTNode *T = root;
	if (T) {
		for (i = 0; i <= k - 1; i++) {
			printf("\t");	  //�ÿո�����ʾ�ڼ���
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
		logmess += ShowBTNode(T);	//��ʾ�������ȫ��ֵ	
		for (i = 0; i <= T->keynum; i++) { //ʹ�õݹ�ķ�����ʾÿ�����	
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
		i = Search(p, my_book);                 // �ҵ�����ؼ���                  
		if (i > 0 && p->key[i].key == my_book.key)
			found = 1;
		else {
			q = p;
			p = p->ptr[i]; //����һ����֧�ϲ���
		}
	}
	if (found) {  // ���ҳɹ�
		R.pt = p;
		R.i = i;
		R.tag = 1;
	}
	else {     
		R.pt = q;
		R.i = i;
		R.tag = 0;
	}
	// ���ؽ����Ϣ: K��λ��(�����λ��)
	return R;
}

int Library::borrowBook(Book my_book) {
	Result R = searchBook(my_book);
	User *user;
	if (R.tag == 0) {
		printf("\t\t\t�ܱ�Ǹ!��Ҫ���ĵ��鲻����!\n");
		return 0;
	}
	if (R.pt->key[R.i].left < 1) {
		printf("\t\t\t�ܱ�Ǹ!��Ҫ���ĵ����Ѿ�����!\n");
		return 0;
	}
	user = (User *)malloc(sizeof(User));
	char s[5];
	printf("\n\n\t\t\t��������ߵ���Ϣ\n");
	printf("\t\t\t������ͼ��֤��:");
	do {
		scanf("%s", s);
		user->number = atoi(s);
		if (user->number < 1 || user->number > 65535) {
			printf("\t\t\t��������,����������(0��65535֮��):");
		}
	} while (user->number < 1 || user->number > 65535);
	user->next = NULL;


	R.pt->key[R.i].left--;
	user->next = R.pt->key[R.i].user;
	R.pt->key[R.i].user = user;
	printf("\t\t\t��ϲ!!!���ĳɹ�!\n");
	return 1;

};

int Library::backBook(Book my_book) {
	User *user, *pre;
	int number;
	Result R = searchBook(my_book);

	
	if (R.tag == 0) {
		printf("\t\t\t�ܱ�Ǹ!��������Ҫ������!\n");
		return 0;
	}
	user = R.pt->key[R.i].user;
	if (!user) {
		printf("\t\t\t�Ȿ�����޳���!\n");
		return 0;
	}
	printf("\n\t\t\t������ͼ��֤��:");
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
	printf("\t\t\t�������ͼ��֤�Ų���ȷ!�����²���!\n");
	return 0;
}

int Library::deleteBook(Book my_book) {
	if (root == NULL) {              //�����û��¼�����,��ֱ�ӷ���
		printf("\t\t\t���Ϊ��!\n");
		return 0;
	}
	BTree p;                         //���ҵ���ָ��
	Result R;                     //���ҵĽ��
	int i = 0, sk = 0;
	R = searchBook(my_book);
					         		 //����� B- ���в������� k �ͷ��� false
	if (R.tag == 0) {                    //�������ʧ��
		printf("\t\t\tɾ��ʧ��!����������Ҫɾ������Ϣ!\n");
		return 0;
	}
	p = R.pt;                          //�����ҵ��Ľ�㸳ֵ�� p
	i = R.i;                                                  //�ڽ���е�λ��	
	exchange(p, i);                                //���ý���ֵ����������ǵ�ֵ����
	if (p->keynum >= (Jie + 1) / 2 - 1) {        
		return 1;
	}
	                                   //����ı�ʾ p->keynum == 0
	if (p == root) {                    //��ֻ�и�����ʱ��
		free(root);                     //�Ѹ�����ͷŵ�
		root = NULL;                           //��ɾ���Ľ�㸳ֵΪ��                      
		return 1;
	}
	while (p) {                                 //���������
		if (p == root || p->keynum >= (Jie + 1) / 2 - 1 || !p->parent)        //���p���ɾ������Ԫ��
			return 1;             //����ѭ������������          
		else {                    //�����Ҫ���������߽�Ԫ��
			if (fix(p->parent, p) == 1)  //�ж��ܲ��ܽ裬���Խ��ֱ�ӷ���
				return 1;
		}
		combine(p->parent, p);
		p = p->parent;
		if ((p == root || !p->parent) && p->keynum == 0) {  //����ϲ��󸸽���ɿ�
			root = p->ptr[0];
			free(p);
			p = root;
			root->parent = NULL;
			return 1;
		}
	}
	return 1;
}

//���ƽ��,��ĳ������ֵ���Ƶ�����һ��ֵ��  bookTrancerse
void BookTranverse(Book &bak,Book k){
	bak.key = k.key;
	strcpy(bak.bname,k.bname);
	bak.left = k.left;
	bak.total = k.total;
	strcpy(bak.writter,k.writter);
	bak.user = k.user;
}

//��һ������в���Ԫ��,���ؽ���λ��
int Search(BTree p, Book K) {	
	if(!p)
		return -1;
	int i=0;
    for(i = 0; i < p->keynum && p->key[i+1].key <= K.key; i++);
    return i;
}

// ��m��B��T�ϲ��ҹؼ���K�����ؽ��(pt,i,tag)
Result SearchBTree(BTree T, Book K){ 
   BTree p, q;
   int found, i;
   Result R;
   //��ʼ������
   p = T; 
   q = NULL; 
   found = 0; 
   i = 0; 
   // ��ʼ����pָ������㣬qָ��p��˫��
   while (p && !found) {
      i = Search(p, K); 
      // �ҵ�����ؼ���                  
      if (i > 0 && p->key[i].key == K.key) 
		  found = 1;    
      else { 
		  q = p;  
		  p = p->ptr[i]; //����һ����֧�ϲ���
	  }
   }
   if (found) {  // ���ҳɹ�
     R.pt = p; 
	 R.i = i;  
	 R.tag = 1;  
   } 
   else {      // ���Ҳ��ɹ�
     R.pt = q;  
	 R.i = i; 
	 R.tag = 0; 
   }
   // ���ؽ����Ϣ: K��λ��(�����λ��)
   return R;              
}

//����һ����¼
void Insert(BTree &q, int i, Book x, BTree ap) {
	int n = q->keynum;	
	for (int j = n; j > i; j--) { //�ڳ��ռ�		
		BookTranverse(q->key[j + 1],q->key[j]); //���ƽ��ֵ
		q->ptr[j + 1] = q->ptr[j];
	}
	BookTranverse(q->key[i + 1],x);	
	q->ptr[i + 1] = ap;
	if (ap) 
		ap->parent = q;  
	q->keynum++;
}

//������
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

//����һ���µ������
void NewRoot(BTree &T, BTree p, Book x, BTree ap) {
  T = (BTree)malloc(sizeof(BTNode));

  T->keynum = 1;  
  T->ptr[0] = p;  //������߽�������
  T->ptr[1] = ap;  //�����ұߵ�����  
  BookTranverse(T->key[1],x);  //�� x Ԫ�صĽ��ֵ���Ƶ� T �ĵ�һ��Ԫ����
                          //�����Ӳ��յ�ʱ������õ�ǰ���Ϊ���ӵ�˫��
  if (p) 
	  p->parent= T;        
  if (ap) 
	  ap->parent = T;  
  T->parent = NULL;  //��ǰ����˫��Ϊ��
}

//���� false ��ʾ��ԭ�н������������������ true ��ʾ������һ���µĽ��
int InsertBTree(BTree &T, Book K) {
  // ��m��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��
  // ���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B����
  BTree ap;
  Result R;
  BTree q;
  int i;
  char addnum;
  int finished, needNewRoot, s;
  // T�ǿ���(����q��ֵΪNULL)
  Book x;
  //��� T ���Ϊ�վ�����һ���µĽ��
  if (!T){                      
    NewRoot(T, NULL, K, NULL); 
  }
  else {
	//����Ԫ�� k �����е�λ��
    R = SearchBTree(T,K);
	q = R.pt; //���ҵ�����Ԫ�� k �Ľ��
    i = R.i;  //Ԫ�� k �����е�λ��
    if(R.tag == 1){  //�жϸ�Ԫ���������Ƿ����
		if(strcmp(q->key[i].bname,K.bname) != 0){
			printf("\n\t\t\t¼��ʧ�ܣ�ԭ��:\n");
			printf(".\t\t\t��ų�ͻ��������Ϊ������!\n\n");
			printf("\t\t\t�Ѿ��������Ϊ %d ����Ϊ:\n",q->key[i].key);
			ShowBookMess(q->key[i]);
			return 0;
		}
	    printf("\n\t\t\t�����Ѿ�����!\n\n");
		ShowBookMess(q->key[i]);
	    return 0;
	}
    x = K;  
	ap = NULL; 
	finished = needNewRoot = 0;     
    while (!needNewRoot && !finished) {
      Insert(q, i, x, ap);  //������

	  int kk = Search(q->parent, q->key[1]);
	  cout << "a!!!!!" <<kk<< "\n";
      if (q->keynum < Jie) 
		  finished = 1;  // �������

	  else {  // ���ѽ��*q
		  cout << "zzzqd\n";
        s = (Jie+1)/2;
		split(q, s, ap);  
		x = q->key[s];
        if (q->parent) {  // ��˫�׽��*q�в���x�Ĳ���λ��
          q = q->parent; 
		  i = Search(q, x);  
        } 
		else 
			needNewRoot = 1;
      } 
    } 
    if (needNewRoot)        // ������ѷ���Ϊ���*q��*ap
      NewRoot(T, q, x, ap); // �����¸����*T,q��apΪ����ָ��
  }

  return 1;
}

//һ�������˫���е�λ��,������λ�� i
int position(BTree T){
	if(!T){
		return 0;
	}
	int i = 0;
	if(T->parent){
		while(i <= T->parent->keynum){
			if(T == T->parent->ptr[i])
				return i; //���ص�ǰ��λ��
			i++;
		}
	}
	return -1;
}

//�������Ľṹ
int fix(BTree &root,BTree p){
	int i = position(p);  //ȡ��p ��˫���е�λ��
	int mid = (Jie + 1)/2 - 1;  //Ҫ�������ٽ��
	BTree temp = NULL;
	int k;
	if(i > 0 && root->ptr[i - 1]->keynum > mid){  //�� i �������ʱ��Ϳ��������
		temp = root->ptr[i - 1]; //���Լ�С���ֵܽ��
		p->keynum++; //����һ�����
		for(k = p->keynum;k > 1;k--){
			BookTranverse(p->key[k],p->key[k - 1]); //��ǰ��Ľ�����һλ
		}
		if(p->ptr[0]){
			for(k = p->keynum;k >= 1;k--){
				p->ptr[k] = p->ptr[k - 1]; //��Ҫ�ƶ��Ľ����ӽ������ƶ�
			}
		}
		BookTranverse(p->key[1],root->key[i]); //��˫�׵Ľ�㸴�Ƶ���
		BookTranverse(root->key[i],temp->key[temp->keynum]); //��С�ֵܽ��������Ǹ��ƶ���˫����
		if(temp->ptr[temp->keynum]){  //���ֵܽ����ӽ��Ҳ���ƹ���
			p->ptr[0] = temp->ptr[temp->keynum]; 
			temp->ptr[temp->keynum]->parent = p; //�޸�ָ��˫�׵Ľ��
			temp->ptr[temp->keynum] = NULL;
		}
		temp->keynum--;  //�����ֵ�ɾ��һ�����
		return 1;
	}
	if(i < root->keynum && root->ptr[i + 1]->keynum > mid){ //�� i С�����������ʱ��Ϳ������ҽ�
		temp = root->ptr[i + 1];
		p->keynum++;  //���ӽ��ĸ���
		BookTranverse(p->key[p->keynum],root->key[i + 1]); //��������ֵ���ƹ���
		BookTranverse(root->key[i + 1],temp->key[1]);  //�����ֵܵĽ�㸴�ƹ���
		for(k = 1;k < temp->keynum;k++){
			BookTranverse(temp->key[k],temp->key[k + 1]); //������Ľ����ǰ�ƶ�һλ
		}
		if(temp->ptr[0]){
			p->ptr[p->keynum] = temp->ptr[0];
			temp->ptr[0]->parent = p;  //�޸�ָ��˫�׵Ľ��
			for(k = 0;k < temp->keynum;k++){ //���ӽ����ǰ�ƶ�
				temp->ptr[k] = temp->ptr[k + 1];
			}
			temp->ptr[k + 1] = NULL;   //��ɾ���Ľ����ӽ����Ϊ��
		}
		temp->keynum--;  //�����ֵ�ɾ��һ�����
		return 1;
	}
	return 0;
}

//�ϲ����
int combine(BTree &root,BTree &p){
	int k,i = position(p);  //ȡ��p ��˫���е�λ��
	int mid = (Jie + 1)/2 - 1; //����������
	BTree p2;
	if(i == 0){  //����ǵ�һ��λ��
		i = 1;
		p2 = root->ptr[i];
		p->keynum++; //����һ�����
		BookTranverse(p->key[p->keynum],root->key[i]); //��˫�׵Ľ�㸴������
		if(p2->ptr[0]){
			p->ptr[p->keynum] = p2->ptr[0]; //���ֵܵ��ӽ��Ҳ���ƹ���
			p2->ptr[0]->parent = p; //�޸�˫��
		}		
		for(k = i;k < root->keynum;k++){ //��˫�׵Ľ����ǰ�ƶ�һλ
			BookTranverse(root->key[k],root->key[k + 1]);
		}
		p->keynum++;
		p->key[p->keynum] = p2->key[1];
		if(p2->ptr[1]){
			p->ptr[p->keynum] = p2->ptr[1]; //���ֵܵ��ӽ��Ҳ���ƹ���
			p2->ptr[1]->parent = p;  
		}		
		root->keynum--;
		free(p2);
		p2 = NULL;
		for(k = 1;k <= root->keynum;k++){
			root->ptr[k] = root->ptr[k + 1]; //��˫�׽���ӽ����ǰ�ƶ�
		}
		root->ptr[k + 1] = NULL;
	}
	else if(i > 0){
		p2 = root->ptr[i - 1];		
		p2->keynum++;
		BookTranverse(p2->key[p2->keynum],root->key[i]); //���Ƹ�����ֵ���ӽ����
		if(p->ptr[0]){
			p2->ptr[p2->keynum] = p->ptr[0];
			p->ptr[0]->parent = p2; //�޸�ָ��˫�׵Ľ��
		}				
		for(k = i;k < root->keynum;k++){
			BookTranverse(root->key[k],root->key[k + 1]); //�����ǰ��
			root->ptr[k] = root->ptr[k + 1]; //���ӽ��ǰ��			
		}
		root->ptr[k + 1] = NULL;
		root->keynum--;
		free(p); 
		p = p2;
	}
	return 1;
}

//���������㽻��
void exchange(BTree &T,int i){
	BTree p = T;
	User *user = NULL;
	if(p->ptr[i]){
		p = p->ptr[i];
		while(p->ptr[0]){
			p = p->ptr[0];		
		}
		while(T->key[i].user){
			user = T->key[i].user;  //ָ��Ҫ�ͷŵĽ��
			T->key[i].user = T->key[i].user->next; //ָ����һ�����
			free(user);  //�ͷŽ����ߵ���Ϣ
		}
		BookTranverse(T->key[i],p->key[1]);  //��������
		int j = 1;
		while (j < p->keynum) { //���ý���������ݺ���
			BookTranverse(p->key[j], p->key[j + 1]); //����һ�����ݸ��Ƶ�ǰһ������
			j++;
		}
	}
	
	
	p->keynum--;  //ɾ�����
	T = p;
	return;
}
