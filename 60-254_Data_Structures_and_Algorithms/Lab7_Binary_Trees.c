#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1 // 1 for debug prints, 0 for clean
#define FREECHK 0 // 1 to display printouts verifying memory freed

// structure of binary tree node
struct btree
{
    int val;
    struct btree *leftChild, *rightChild;
};
// define type as "node"
typedef struct btree node;

// globals - tree information
int numLeaves = 0;
int numSingleChild = 0;
int numTwoChildren = 0;

node* createNode(int val);
void insertNode(node **root, int val);
void preorderTraversal(node *root);
void freeTree(node **root);

int main()
{
	node *root = NULL;	// root of binary tree

	int numNodes;
	printf("Number of nodes to add: ");
	scanf("%d", &numNodes);

	while (numNodes > 0)
	{
		int nodeValue;
		printf("Enter val of node to insert: ");
		scanf("%d", &nodeValue);

		insertNode(&root, nodeValue);

		numNodes--;
	}
	if (DEBUG) puts("Preorder Traversal:");
	preorderTraversal(root);

	printf("\nNumber of Nodes with 2 Children: %d\n"
		"Number of Nodes with only 1 Child: %d\n"
		"Number of Leaves: %d\n",
		numTwoChildren, numSingleChild, numLeaves);

	freeTree(&root);
	return 0;
}

// creates a binary search tree node given value
node* createNode(int val)
{
	node *new = malloc(sizeof(node));
	new->val = val;
	new->leftChild = NULL;
	new->rightChild = NULL;

	return new;
}

// free a tree, given address of root
void freeTree(node **root)
{
	if (*root == NULL)
		return;	// empty subtree, return

	// populated tree, free subtree recursively from leaf to root
	freeTree(&(*root)->rightChild);	// recursively free right subtree
	freeTree(&(*root)->leftChild);	// recursively free left subtree

	if (FREECHK) printf("Freeing %d...\n", (*root)->val);
	free(*root);	// free leaf
}

// Inserts node into binary tree, given address of root node and new node
void insertNode(node **root, int val)
{
    node *node = createNode(val);   // create node

	if (*root == NULL) // empty root/subtree
	{
		*root = createNode(val);	// place node
	}
	else
	{
		// recursively add to appropriate branch
		// If smaller than root, insert using left child as root
		// If larger, insert node using right child as root
		if (val < (*root)->val)
			insertNode(&(*root)->leftChild, val);
		else if (val > (*root)->val)
			insertNode(&(*root)->rightChild, val);
		else
            return; // duplicate so just return
	}
}

// Displays node information in preorder
void preorderTraversal(node *root)
{
	// empty subtree
	if (root == NULL)
		return;
	else
	{
		// Find root's type, increment global variable
		if (root->leftChild == NULL && root->rightChild == NULL)
			numLeaves++;
		else if (root->leftChild != NULL && root->rightChild != NULL)
			numTwoChildren++;
		else
			numSingleChild++;

		if (DEBUG) printf("%d ", root->val); // print root's val

		// Run recursively on left subtree, then right subtree (pre-order)
		preorderTraversal(root->leftChild);

		preorderTraversal(root->rightChild);
	}
}
