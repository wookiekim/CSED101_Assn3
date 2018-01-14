/*

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	char data;
	struct Node *left;
	struct Node *right;
}Node;

Node* make(char a,char b,char c);//a,c is number, b is operator 
void con(Node *par,Node *ch1,Node *ch2);
void print_tree(Node* root);
void print_tree2(Node* root);
void print_tree3(Node* root);


int main(){
	Node *root,*tmp1,*tmp2;
	tmp1=make('3','-','5');
	tmp2=(Node*)malloc(sizeof(Node));
	tmp2->data='7';tmp2->left=tmp2->right=NULL;
	root=(Node*)malloc(sizeof(Node));
	root->data='+';
	con(root,tmp1,tmp2);
	tmp1=root;
	tmp2=make('4','/','2');
	root=(Node*)malloc(sizeof(Node));
	root->data='*';
	con(root,tmp1,tmp2);
	
	print_tree(root);
	printf("\n");
	print_tree2(root);
		printf("\n");
	print_tree3(root);
	return 0;
}

Node* make(char a,char b,char c){
	int i;
	Node *tmp1,*tmp2,*tmp3;
	tmp1=(Node*)malloc(sizeof(Node));
	tmp2=(Node*)malloc(sizeof(Node));
	tmp3=(Node*)malloc(sizeof(Node));
	tmp1->data=b;tmp2->data=a;tmp3->data=c;
	tmp1->left=tmp2;tmp1->right=tmp3;
	tmp2->left=tmp2->right=NULL;
	tmp3->left=tmp3->right=NULL;
	return tmp1;
}
void con(Node *par,Node *ch1,Node *ch2){
	par->left=ch1;par->right=ch2;
}
void print_tree(Node* root){
	if(root!=NULL){
		print_tree(root->left);
		printf("%c",root->data);
		print_tree(root->right);
	}
}
void print_tree2(Node* root){
	if(root!=NULL){
		printf("%c",root->data);
		print_tree2(root->left);
		print_tree2(root->right);
	}
}
void print_tree3(Node* root){
	if(root!=NULL){
		print_tree3(root->left);
		print_tree3(root->right);
		printf("%c",root->data);
	}
}

*/