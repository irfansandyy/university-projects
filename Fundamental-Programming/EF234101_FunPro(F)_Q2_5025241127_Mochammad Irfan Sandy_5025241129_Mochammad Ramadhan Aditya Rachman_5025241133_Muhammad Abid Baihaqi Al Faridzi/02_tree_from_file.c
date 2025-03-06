#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 100
#define MAX_INT_SIZE 12

typedef struct TreeNode {
	struct TreeNode *left;
	int data;
	struct TreeNode *right;
	struct TreeNode *parent;
} TreeNode;

typedef TreeNode *TreeNodePtr;

void preOrder(TreeNodePtr treePtr, int sum) {
	if(treePtr->left != NULL || treePtr->right != NULL ) {
		printf("node: %d\n", treePtr->data );
		if(treePtr->left != NULL) preOrder(treePtr->left, sum + treePtr->data);
		if(treePtr->right != NULL) preOrder(treePtr->right, sum + treePtr->data);
	} else printf("leaf: %d\n", sum+ treePtr->data);
}

TreeNodePtr insertLeft(TreeNodePtr from, int data) {
	TreeNodePtr d = (TreeNodePtr)malloc(sizeof(TreeNode));
	d->parent = from;
	d->left = NULL;
	d->right = NULL;
	d->data = data;
	from->left = d;
	return d;
}

TreeNodePtr insertRight(TreeNodePtr from, int data) {
	TreeNodePtr d = (TreeNodePtr)malloc(sizeof(TreeNode));
	d->parent = from;
	d->left = NULL;
	d->right = NULL;
	d->data = data;
	from->right = d;
	return d;
}

TreeNodePtr createRoot(int data) {
	TreeNodePtr d = (TreeNodePtr)malloc(sizeof(TreeNode));
	d->parent = NULL;
	d->left = NULL;
	d->right = NULL;
	d->data = data;
	return d;
}

TreeNodePtr parseFile(const char* filename, TreeNodePtr cur) {
	FILE *fptr;
	TreeNodePtr root = NULL;
	if((fptr = fopen(filename,"r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	char c[MAX_LINE_SIZE] ;
	while(fgets(c, MAX_LINE_SIZE, (FILE*)fptr)) {
		char digit[MAX_INT_SIZE];
		fgets(digit, MAX_INT_SIZE, (FILE*)fptr);
		for(int x = 0; x < MAX_INT_SIZE; x++) if(digit[x]=='\n') digit[x] = '\0';

		int data = atoi(digit);
		int index = 1;

		if(c[0]=='l') {
			printf("left - data: %d\n",data);
			cur = insertLeft(cur, data);
		} else if(c[0]=='r') {
			printf("right - data: %d\n",data);
			cur = insertRight(cur, data);
		} else if(c[0]=='u') {
			while (c[index]=='u') index+=1;
			for (int x = 0; x < index; x++) {
				cur = cur->parent;
				printf("parent -> ");
			}
			if(c[index]=='l'){
				printf("left - data: %d\n",data);
				cur = insertLeft(cur, data);
			} else if(c[index]=='r'){
				printf("right - data: %d\n",data);
				cur = insertRight(cur, data);
			}
		} else if(c[0] == '0') {
			cur = createRoot(data);
			root = cur;
			printf("root - data: %d\n",data);
		}
	}
	fclose(fptr);
	return root;
}

int main() {
	TreeNodePtr root = NULL;
	root = parseFile("02_file_input.txt", root);
	preOrder(root, 0);
	return 0;
}
