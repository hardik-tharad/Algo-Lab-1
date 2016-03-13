#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define REP(i, n) for(i=0;i<n;++i)
#define ri(n) scanf("%d", &(n))
#define pri(x) printf("%d ", (x))
#define endl putchar('\n')

typedef struct bin_tag{
	int key;
	struct bin_tag *left, *right;
} tree, *tree_ptr;
tree_ptr root = NULL;
#define MAX_VAL 300
#define MAX_NEG 70

#define MAX 1000
tree_ptr get_node()
{
	tree_ptr t = (tree_ptr)malloc(sizeof(tree));
	t->left = t->right = NULL;
	return t;
}
typedef struct {
	int buf[1000];
	int id;// = 0;
}printer;
printer* get_prin()
{
	printer* p = (printer*)malloc(sizeof(printer));
	memset(p, 0, sizeof(printer));
	return p;
}
int is_leaf(tree_ptr root)
{
	if (root == 0) {
		return -1;
	}
	if (root->left == 0 && root->right == 0) {
		return 1;
	}
	return 0;
}
tree_ptr get_rand(tree_ptr root, int n, int *chk)
{
	if (n <= 0) {
		return NULL;
	}
	int i, j;
	float r = (rand() % 100) / 500.0 + 0.4;
	root = get_node();
	do {
		root->key = rand() % MAX_VAL - rand() % MAX_NEG;
	} while (chk[root->key + MAX_NEG] == 1);
	chk[root->key + MAX_NEG] = 1;
	--n;
	j = n*r;
	root->left = get_rand(root->left, j, chk);
	root->right = get_rand(root->right, n - j, chk);
	return root;
}
void preoder(tree_ptr root)
{
	if (root == NULL) {
		return;
	}
	pri(root->key);
	preoder(root->left);
	preoder(root->right);
}
void inorder(tree_ptr root)
{
	if (root == NULL) {
		return;
	}
	inorder(root->left);
	pri(root->key);
	inorder(root->right);
}
void postorder(tree_ptr root)
{
	if (root == NULL) {
		return;
	}
	postorder(root->left);
	postorder(root->right);
	pri(root->key);
}
int max(int a, int b) {
	return (a) > (b) ? (a) : (b);
}
void get_max1(tree_ptr root, int now, int *max_ref, tree_ptr* target_leaf)
{
	int chk = is_leaf(root);

	if (chk == -1) {
		return;
	}
	if (chk == 1) {
		if (now + root->key > *max_ref) {
			*max_ref = now + root->key;
			*target_leaf = root;
		}
		return;// now + root->key;
	}
	int d = root->key;
	int kk = now + d;
	get_max1(root->left, kk, max_ref, target_leaf);//,
	get_max1(root->right, kk, max_ref, target_leaf);
	return;
}

int print_path(tree_ptr root, tree_ptr target_leaf, printer* a)
{
	int chk = is_leaf(root);
	if (chk == -1) {
		// EMPTY TREE.
		return -1;
	}
	else if (chk == 1) {
		if (root == target_leaf) {
			a->buf[a->id++] = root->key;
			//			printf("%d ", root->key);
			return 1;
		}
		return 0;
	}
	if (print_path(root->left, target_leaf, a) == 1) {
		a->buf[a->id++] = root->key;
		//		printf("%d ", root->key);
		return 1;
	}
	else if (print_path(root->right, target_leaf, a) == 1) {
		a->buf[a->id++] = root->key;
		//		printf("%d ", root->key);
		return 1;
	}
	return 0;
}

tree_ptr max_top_ptr = 0, max_l = 0, max_r = 0;
int lef_s = 0, rig_s = 0;
int findMaxUtil(tree_ptr root, int *res)
{
	//Base Case
	if (root == NULL)
		return 0;

	int l = findMaxUtil(root->left, res);
	int r = findMaxUtil(root->right, res);
	int max_single = max(max(l, r) + root->key, root->key);

	int max_top = max(max_single, l + r + root->key);

	if (max_top_ptr != 0) {
		if (max_top > *res) {
			max_top_ptr = root;
			lef_s = l;
			rig_s = r;
		}
	}
	else {
		max_top_ptr = root;
	}
	*res = max(*res, max_top); // Store the Maximum Result.

	return max_single;
}
#define PATH_RET //0
void path(tree_ptr root, int sum, tree_ptr* target)
{
	if (root == 0) {
		return PATH_RET;
	}
	if (sum == root->key) {
		*target = root;
		return PATH_RET;
	}
	path(root->left, sum - root->key, target);
	path(root->right, sum - root->key, target);
	return PATH_RET;
}

int final_print_path(const tree_ptr root, const tree_ptr target, printer* a)
{
	if (root == 0) {
		return 0;
	}
	if (root == target) {
		a->buf[a->id++] = root->key;
		//		pri(root->key);
		return 1;
	}
	int x = final_print_path(root->left, target, a);
	int y = final_print_path(root->right, target, a);
//	assert(x != y);
	if (x || y) {
		a->buf[a->id++] = root->key;

//		pri(root->key);
	}
//	if (y == 1) {
	//	pri(root->right->key);
//	}
	return x || y;
}
void print_printer(printer* a, int rev)
{
	if (rev == 0) { // print straight
		int i;
		for (i = 0; i < a->id; ++i) {
			pri(a->buf[i]);
		}
	}
	else if (rev == 1) { // flipped print
		int i = a->id-1;
		while (i >= 0) {
			pri(a->buf[i--]);
		}
	}
}
int main()
{
	srand(101);
	int chk[MAX];
	memset(chk, 0, MAX);
	root = get_rand(root, 100, chk);
//	root->key -= 100;
	preoder(root);
	endl; endl;
	inorder(root);
	endl; endl;
	postorder(root);
	endl; endl;
	int m = -(1 << 30);
	tree_ptr leaf = 0;
	get_max1(root, 0, &m, &leaf);
//	printf("MAX root to leaf sum is : %d\n", m);
	if (leaf == 0) {
		printf("leaf is 0\n");
	}
	printer *c = get_prin();
	print_path(root, leaf, c);
	print_printer(c, 1);
	endl;
	int max_s = -(1 << 30);
	//	printf("findmax = %d", findmax(root, &max_s));
	endl;
	max_s = -(1 << 30);
	int x = findMaxUtil(root, &max_s);

//	printf("Max sum from node to node = %d\n", max_s);
/*	if (max_top_ptr != 0) {
		printf("\nmax_top = %d\n", max_top_ptr->key);
	}
	else {
		printf("max_top is NULL\n");
	}
*/	max_s = -(1 << 30);
//	pri(lef_s); pri(rig_s);
	max_l = max_r = 0;
	path(max_top_ptr->left, lef_s, &max_l);
/*	if (max_l != 0) {
		printf("lef_most: ");	pri(max_l->key);
	}
*/	path(max_top_ptr->right, rig_s, &max_r);
/*	if (max_r != 0) {
		printf("rig_most: ");		pri(max_r->key);
	}
*/	
	printer *a = get_prin(), *b = get_prin();
	final_print_path(max_top_ptr->left, max_l,a);
	final_print_path(max_top_ptr->right, max_r,b);
	print_printer(a, 0);
	pri(max_top_ptr->key);
	print_printer(b, 1);
	endl;
	return 0;
}