#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//todo delete fun
//todo opt the insert index, because it is now sorted-index ,result in that it is just like link list
static int cas_int_inc(int *addr,int delta){
	int ret =0;
	__asm__ __volatile__(
			"lock;xaddl %2,%1;"
			:"=a"(ret)
			:"m"(*addr),"0"(delta)
			:"memory","cc"
	);
	return ret;
}

struct TreeNode_;
typedef struct TreeNode_ TreeNode;
typedef 	TreeNode *		TreeRoot;
typedef  int IndexData;

struct TreeNode_{
	TreeNode *right,*left;
	IndexData indx;
	void *data;
};

struct Tree_;
typedef struct Tree_ Tree;

struct Tree_{
	TreeNode *root;
	int size;
	
	
};


/**************
struct Data_;
typedef struct Data_ Data;

typedef struct Data_{
	//index -d
	int index;
  //udata -d
	int dataUid;
    int topic;
  //pdata  -d
	int partition ;
};

*****/

TreeNode* createNode(void* data);
void  append(TreeRoot root,TreeNode *node);
TreeNode* findNodeByIndex(TreeRoot root,IndexData indx);


Tree* createTree(){
	Tree * tree = malloc(sizeof(Tree));
	memset(tree,0,sizeof(Tree));
	tree->size =0;
	return tree;
}
void destoryTree(Tree *tree){
	if (tree!=NULL){
		free(tree);
		printf("release Tree complete  ...\n");
	}
}
int TreeInsert(Tree * tree,void* data){
		int id = tree->size;
		TreeNode *n = (TreeNode*)createNode(data);
		n->indx = id;
		cas_int_inc(&tree->size,1);
		if (tree->root==NULL){
			tree->root = n;
		}else{
		   append(tree->root,n);
		}
		return id;
}

void* TreeFind(Tree * tree,int idx){
	TreeNode * n =findNodeByIndex(tree->root,idx);
	if (n!=NULL){
		return n->data;
	}
    return NULL;
}


TreeNode* createNode(void* data){
	TreeNode*  node =0;
	do{
		node=(TreeNode*) malloc(sizeof(TreeNode));
	}while(node==0);
	memset(node,0,sizeof(TreeNode));
	node->data=data;
	return  node;
}

void  append(TreeRoot root,TreeNode *node){
	if (root==NULL || node==NULL)return;
	if (node->indx<=root->indx){
		if (root->left!=NULL){
			append(root->left,node);
		}else{
			root->left = node;
			printf("inserted node idx:%d \n",node->indx);
		}
	}else{
		if (root->right!=NULL){
			append(root->right,node);
		}else{
			root->right = node;
			printf("inserted node idx:%d \n",node->indx);
		}
	}
}


void  forEachInOrder(TreeRoot root){
	if (root==NULL){
		return ;
	}
	forEachInOrder(root->left);
	printf("%d\n",root->indx);
	forEachInOrder(root->right);
}

typedef void (*ForeachCallback)(TreeNode* node);
void  forEachPostOrderByCallack(TreeRoot root,ForeachCallback callbackFn){
	if (root==NULL || callbackFn==NULL){
		return ;
	}
	forEachPostOrderByCallack(root->left,callbackFn);
	forEachPostOrderByCallack(root->right,callbackFn);
	//printf("%d\n",root->indx);
	callbackFn(root);
}



TreeNode* findNodeByIndex(TreeRoot root,int indx){
	 if (root==NULL)return NULL;
	// printf("  right -> currIndx=%d, target=%d\n",root->indx,indx);
	if (root->indx==indx){
		  printf("find finished\n");
		  return	root;
		} 
	 
	if (indx<root->indx){
		if (root->left!=NULL){
			printf("  left  <- \n");
			return findNodeByIndex(root->left,indx);
		}else{
			return NULL;//已经是nil 往下没有节点了，就是没找到了
		}
	}else{
		if (root->right!=NULL){
			
			return findNodeByIndex(root->right,indx);
		}else{
			return NULL;//已经是nil 往下没有节点了，就是没找到了
		}
	}
	return NULL;
}

void foreachDestroyInner(TreeNode* node){
	 if (node!=NULL){
	 	free(node);
		printf("release element idx:%d \n",node->indx);
	 }
}


//数的作用就是导航检索，适合猜数据的左右方向导航的


struct File_;
typedef struct File_ File;
struct File_{
	int fd;
	char name[30];
};




int main(int argc,const char *argvs[]){

	File f1={1,"helloworld"};
	File f8={8,"helloworld8"};
	File f6={6,"helloworld6"};
	File f5={5,"helloworld5"};
	File f3={3,"helloworld3"};

	Tree *tree = createTree();
	int indx_1= TreeInsert(tree,&f1);
	int indx_8= TreeInsert(tree,&f8);
	int indx_6= TreeInsert(tree,&f6);
	int indx_5= TreeInsert(tree,&f5);
	int indx_3= TreeInsert(tree,&f3);
	printf("indx_1=%d,indx_8=%d,indx_6=%d,indx_5=%d,indx_3=%d \n",
		   indx_1,indx_8,indx_6,indx_5,indx_3
		);

	forEachInOrder(tree->root);
	printf("==========================\n");
	File * target= TreeFind(tree, indx_6);
	if (target!=0){
		printf("result: fd=%d  name=%s \n",target->fd,target->name);
	}else{
		printf("find nil\n");
	}
	forEachPostOrderByCallack(tree->root,foreachDestroyInner);
	destoryTree(tree);
	
	return 0;
}





