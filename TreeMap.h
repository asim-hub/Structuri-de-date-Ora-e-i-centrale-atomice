#ifndef TREEMAP_H_
#define TREEMAP_H_
#include <stdlib.h>


//-------------------------------------------------------------------------

typedef struct node{
	void* elem; // Node key
	void* info; // Node satellite information
	struct node *pt; // Parent link
	struct node *lt; // left child link
	struct node *rt; // right child link
	struct node* next; // next link in the list of duplicates
	struct node* prev; // prev link in the list of duplicates
	struct node* end; // pointer to the end of the duplicates list
	long height;
}TreeNode;

typedef struct TTree{
	TreeNode *root; // pointer to the root of the tree
	void* (*createElement)(void*); // create element method
	void (*destroyElement)(void*); // destroy element method
	void* (*createInfo)(void*); // create info method
	void (*destroyInfo)(void*); // destroy info method
	int (*compare)(void*, void*); // comparison method between elements
	long size;
}TTree;


TTree* createTree(void* (*createElement)(void*), void (*destroyElement)(void*),
		void* (*createInfo)(void*), void (*destroyInfo)(void*),
		int compare(void*, void*)){

	// aloc spatiu pentru structura
	TTree *tree = calloc(1, sizeof(TTree));
	if (tree == NULL) {
		exit(-1);
	}

	// pointer la functii
	tree->createElement = createElement;
	tree->destroyElement = destroyElement;
	tree->createInfo = createInfo;
	tree->destroyInfo = destroyInfo;
	tree->compare = compare;

	return tree;
}

	long max(long a, long b)
	{
		// valoarea maxima
		return (a > b)? a : b;
	}

int isEmpty(TTree* tree){

	return (tree->root == NULL);
	
}


TreeNode* search(TTree* tree, TreeNode* x, void* elem){
	//caut un element in arbore
	TreeNode *aux = x;
	while (aux != NULL) {
		if(aux!=NULL && tree->compare(aux->elem, elem) == 0)
			return aux;
		while (aux!=NULL && tree->compare(aux->elem, elem) < 0)
			aux = aux->rt;
		while (aux!=NULL && tree->compare(aux->elem, elem) > 0)
			aux = aux->lt;
		
	}

	return NULL;
}


TreeNode* minimum(TreeNode* x){
	// returnez nodul stang al arborelui
	TreeNode *aux = x;
	if (aux != NULL) 
		while (aux->lt)
			aux = aux->lt;
	if(aux != x)
		return aux;
	else
		if(aux == x)
			return x;	
	return NULL;
}

TreeNode* maximum(TreeNode* x){
//returnez nodul drept al arborelui
	TreeNode *aux = x;
	if (aux != NULL) 
		while (aux->rt)
			aux = aux->rt;
		if(aux!=x)
			return aux;
			else
			 if(aux==x)
			 return x;
	return NULL;
			
	
}

TreeNode* successor(TreeNode* x){
	
//elementul minim din subarborele drept al nodului, dacă nodul are subarbore drept
	if (x->rt != NULL)
		return minimum(x->rt);
	else {
		//dacă nodul nu are subarbore drept, el va fi element maxim într-un subarbore.
		//Părintele rădăcinii acestui subarbore este nodul succesor
		TreeNode *node = x->pt;
		while (node != NULL && node->rt == x) {
			x = node;
			node = node->pt;
		}

		return node;
	}
}

TreeNode* predecessor(TreeNode* x){
//elementul maxim din subarborele stâng al nodului, dacă nodul are subarbore stâng
	if (x->lt != NULL)
		return maximum(x->lt);
	else {
		//dacă nodul nu are subarbore stâng, el va fi element minim într-un subarbore.
		// Părintelerădăcinii acestui subarbore este nodul succesor
		TreeNode *node = x->pt;
		while (node != NULL && node->lt == x) {
			x = node;
			node = node->pt;
		}

		return node;
	}
}

void updateHeight(TreeNode* x){
	int leftH , rightH;
	if(x == NULL)
	exit(-1);
	
		if(x->lt != NULL) 
			leftH = x->lt->height;
		else
			leftH = 0;
		
		if(x->rt != NULL) 
			rightH = x->rt->height;
			else
			rightH=0;
			
		if(rightH > leftH)
			x->height=rightH +1 ;
			else
			x->height=leftH + 1;
				
}




void refreshHeights(TreeNode *node)
{//recalcuez inaltimea de jos in sus
	if (node == NULL) return;

	//recalculez inaltimea nodului curent
	if (node == NULL) return;

	long high1;
	if (node->lt == NULL)
		high1 = 0;
	else high1 = node->lt->height;

	long high2;
	if (node->rt == NULL)
		high2 = 0;
	else high2 = node->rt->height;

	node->height = 1 + max(high1, high2);

	TreeNode *aux = node->pt;
	while (aux != NULL) {
		refreshHeights(aux);
		aux = aux->pt;
	}
}

int height(TreeNode *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 


void avlRotateLeft(TTree* tree, TreeNode* x){
	// rotire la stanga 
	if (tree == NULL) return;
		//arbore neinitializat;
	TreeNode *aux = x->pt;
	TreeNode *y = x->rt;
	if(aux)
	if (aux->rt == x)
	{
		aux->rt = y;
		y->pt = aux;
	}
	else if (aux->lt == x)
	{
		aux->lt = y;
		y->pt = aux;
	}
	y->pt = aux;

	x->rt = y->lt;
	y->lt = x;
	if (x->rt)
		x->rt->pt = x;
	x->pt = y;
	

	x->height = max(height(x->lt),     
                    height(x->rt)) + 1;  
    y->height = max(height(y->lt),  
                    height(y->rt)) + 1;  
	
	if(aux)
	aux->height = max(height(aux->lt),  
                    height(aux->rt)) + 1;  

	if (x == tree->root) tree->root = y;
	

}
	


void avlRotateRight(TTree* tree, TreeNode* y){
	//rotire la dreapta
	if (tree == NULL) return;
		//arbore neinitializat;
	TreeNode *aux = y->pt;
	TreeNode *x = y->lt;
	if(aux)
	if (aux->lt == y)
	{
		aux->lt = x;
		x->pt = aux;
	}
	else if (aux->rt == y)
	{
		aux->rt = x;
		x->pt = aux;
	}
	x->pt = aux;

	y->lt = x->rt;
	x->rt = y;
	if (y->lt)
		y->lt->pt = y;
	y->pt = x;
	

	y->height = max(height(y->lt),     
                    height(y->rt)) + 1;  
    x->height = max(height(x->lt),  
                    height(x->rt)) + 1;  
	
	if(aux)
	aux->height = max(height(aux->lt),  
                    height(aux->rt)) + 1;  

	if (y == tree->root) tree->root = x;
	

}

/* Get AVL balance factor for node x */
int avlGetBalance(TTree *tree, TreeNode *x){
	
	if (x == NULL) 
        return 0; 
		else
			if(x!=NULL)
    			return height(x->lt) - height(x->rt); 
}


void avlFixUp(TTree* tree, TreeNode *node, TreeNode *fiu){
	
	TreeNode *aux = node->pt;
	TreeNode *old = node;
	while (aux != NULL) {
		if (avlGetBalance(tree, aux) > 1 && (aux->lt == old && aux->lt != NULL && aux->lt->lt == fiu)) {
			
				avlRotateRight(tree, aux);
			
		}
		if (avlGetBalance(tree, aux) > 1 && (aux->lt != old || aux->lt == NULL || aux->lt->lt != fiu)) {
			
				avlRotateLeft(tree, aux->lt);
				avlRotateRight(tree, aux);
			
		}
		 if (avlGetBalance(tree, aux) < -1 && (aux->rt == old && aux->rt != NULL && aux->rt->rt == fiu)) {
			
				avlRotateLeft(tree, aux);
			
		}

		if (avlGetBalance(tree, aux) < -1 && (aux->rt != old || aux->rt == NULL || aux->rt->rt != fiu)) {
			
				avlRotateRight(tree, aux->rt);
				avlRotateLeft(tree, aux);
			
		}

		fiu = old;
		old = aux;
		aux = aux->pt;
	}
}


TreeNode* createTreeNode(TTree *tree, void* value, void* info){
	// initiaizarea nod nou
	TreeNode *newNode = (TreeNode*) calloc(1, sizeof(TreeNode));
	if (newNode == NULL)
	exit(-1);
	
	newNode->height = 1;
	newNode->info = tree->createInfo(info);
	newNode->elem = tree->createElement(value);
	
	// cresc numarul de elemente din arbore
	tree->size++;

	// lista de duplicate
	newNode->end = newNode;

	return newNode;
}



//distrug arborele
void destroyTreeNode(TTree *tree, TreeNode* node){

	// Check argumentsLeft rotate subtree rooted by node x C
	if(tree == NULL || node == NULL) return;

	// Use object methods to de-alocate node fields
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);

	// De-allocate the node
	free(node);
}
//insert

TreeNode *parcurgerelista(TTree *tree)
{
	//parcurg lista pana la gasirea ultimului nod si in returnez
	TreeNode *aux = tree->root;
	while (aux->next != NULL)
		aux = aux->next;
	return aux;
}

void addList(TTree *tree, TreeNode *node, void *elem, void *info,int a)
{if(a==1)
	{// aloc memorie pentru lista de noduri duplicate 
	TreeNode *newNode = createTreeNode(tree, elem, info);
	// leg nodul la lista
	newNode->prev = node->end;
	newNode->next = node->end->next;
	newNode->end = newNode;
	if (newNode->next!=NULL)
		newNode->next->prev = newNode;
	node->end->next = newNode;
	node->end = newNode;
}
else if(a==0)
{
// adaug un nou nod la lista neinitializata 
	TreeNode *newNode = node;
	TreeNode *end = parcurgerelista(tree);
	end->next = newNode;newNode->prev = end;
}

}

void insert(TTree* tree, void* elem, void* info) {
	// verific daca arborele este gol
	if (tree->root == NULL)
		tree->root = createTreeNode(tree, elem, info);

		//in caz contrar caut pozitia corecta in arbore
	else {
		TreeNode *node = tree->root;
		TreeNode *nodaux;
		
		while (node != NULL) {
			 if(search(tree, node, elem)==node) {
				//  inseamna ca e un duplicat si il adaug in lista
				addList(tree, node, elem, info,1);
				break;
			}
			
			 if (tree->compare(node->elem, elem) < 0) {
				if (node->rt != NULL)
				while(node->rt != NULL)	node = node->rt;
				else {
					// nodul trebuie amplasat in subarborele drept
					node->rt = createTreeNode(tree, elem, info);
					node->rt->pt = node;
					nodaux = node->rt;
					// adaug un nou nod listei , dar o si creez pe aceasta 
					addList(tree, nodaux, elem, info,0);
					// reactualizez inaltimea arborelui
					refreshHeights(node);
					// reechilibrez arborele dupa insertie 
					avlFixUp(tree, node, nodaux);
					break;
				}
			}

			 if (tree->compare(node->elem, elem) > 0) {
				if (node->lt != NULL)
					while(node->lt != NULL) node = node->lt;
				else {
					// nodul trebuie amplasat in subarborele stang
					node->lt = createTreeNode(tree, elem, info);
					node->lt->pt = node;
					//nodul abia creeat
					nodaux = node->lt;
					// adaug nodul la lista , dar o si creez pe aceasta 
					addList(tree, nodaux, elem, info,0);
					// noua inaltime
					refreshHeights(node);
					// reechilibrez arborele
					avlFixUp(tree, node, nodaux);					
					break;
				}
			}	
			
		}

	}
}




void delete(TTree* tree, void* elem){
	
	TreeNode  *nod_s,*noddeleted, *fiu;

	// caut nodul care trebuie sters
	if ((noddeleted = search(tree, tree->root, elem)) == NULL)
		exit(-1);
	// sterg conexiunea
		if (noddeleted->end == noddeleted) {
			if (noddeleted->prev)
				noddeleted->prev->next = noddeleted->next;
			if (noddeleted->next)
				noddeleted->next->prev = noddeleted->prev;
		}

	// daca nodul are duplicate sterg una
	if (noddeleted->end != noddeleted) {
		TreeNode *old = noddeleted->end;
		noddeleted->end = noddeleted->end->prev;
		if (old->prev && old->next)
		{
			old->prev->next = old->next;
			old->next->prev = old->prev;
		}
		else if (old->next )
				old->next->prev = old->prev;
		if (old->prev )
		{
			old->prev->next = old->next;
		}
		destroyTreeNode(tree, old);
		return;
	}
	

	// daca nodul de sters are un copil sau niciunul
	if (noddeleted->lt == NULL || noddeleted->rt == NULL)
		{nod_s = noddeleted;
		//pastram unul dintre copii
		if (nod_s->lt)
		fiu = nod_s->lt;
	else
		fiu = nod_s->rt;}
	// daca nodul are doi copii
	else
		{nod_s = successor(noddeleted);
		//pastram unul dintre copii
		if (nod_s->lt)
		fiu = nod_s->lt;
	else
		fiu = nod_s->rt;}

	if (nod_s->pt == NULL)
		{// daca are copii, parinti lor vor deveni succesorul nodului care a fost sters
		if (fiu)
			fiu->pt = nod_s->pt;
		tree->root = fiu;}
	else if (nod_s == nod_s->pt->lt) {
		// 	daca are copii, parinti lor vor deveni succesorul nodului care a fost sters
		if (fiu)
			fiu->pt = nod_s->pt;
		nod_s->pt->lt = fiu;
		if (noddeleted->pt == NULL)
			tree->root = nod_s;
	}
	else {
		// 	daca are copii, parinti lor vor deveni succesorul nodului care a fost sters
		if (fiu)
			fiu->pt = nod_s->pt;
		nod_s->pt->rt = fiu;
		if (noddeleted->pt == NULL)
			tree->root = nod_s;
	}

	//	daca nodul spliced nu este acelasi cu nodul care a fost sters atunci ii ia locul
	TreeNode* old=noddeleted->pt;
	if (nod_s != noddeleted){
		TreeNode *prt = nod_s->pt;

		nod_s->lt = noddeleted->lt;
		nod_s->rt = noddeleted->rt;
		nod_s->pt = noddeleted->pt;

		if (noddeleted->lt)
		{	noddeleted->lt->pt = nod_s;
			if (noddeleted->pt != NULL) {
				if (noddeleted == noddeleted->pt->lt)
					noddeleted->pt->lt = nod_s;
				else
					noddeleted->pt->rt = nod_s;
			}
		}
		if (noddeleted->rt)
		{	noddeleted->rt->pt = nod_s;
			if (noddeleted->pt != NULL) {
				if (noddeleted == noddeleted->pt->lt)
					noddeleted->pt->lt = nod_s;
				else
					noddeleted->pt->rt = nod_s;
			}
		}
		// reactualizez inaltimea tree
	refreshHeights(prt);
	refreshHeights(noddeleted->pt);
	//distrug nodul sters
	destroyTreeNode(tree, noddeleted);
	}
	//daca nodu spliced este acelasi cu nodul sters,
	// actualizez inatimea si distrug nodul
	 
	else {
		// actualizez inaltimea tree
		refreshHeights(old);

		destroyTreeNode(tree, nod_s);
	}

	// Reechilibrez tree
	
	TreeNode *m = minimum(tree->root);
	if (minimum(tree->root) != tree->root)
		avlFixUp(tree, m->pt, minimum(tree->root));
	m = maximum(tree->root);
	if (maximum(tree->root) != tree->root) {
		if (m->lt != NULL )
			if( m->rt == NULL)
				m = m->lt;
		avlFixUp(tree, m->pt, maximum(tree->root));
	}

	// scad inaltimea
	tree->size--;
}




void Destroy(TTree *tree, TreeNode *aux)
{
	if (aux) {
		//avansez in arbore
		Destroy(tree, aux->lt);
		Destroy(tree, aux->rt);
		 // daca nodul are duplicate distrug nodul si duplicatele lui
		if (aux->end != aux) 
			{
				TreeNode *nod = aux->next;
				while (nod != aux->end) {
					nod = nod->next;
					destroyTreeNode(tree, nod->prev);
			}
			destroyTreeNode(tree, nod);
			destroyTreeNode(tree, aux);
			
		}
		//distrug nodul daca nu are duplicate
		else {
			destroyTreeNode(tree, aux);
		}
	}
}

void destroyTree(TTree *tree){
	if (!isEmpty(tree))
		Destroy(tree, tree->root);

	free(tree);
}


#endif /* TREEMAP_H_ */
