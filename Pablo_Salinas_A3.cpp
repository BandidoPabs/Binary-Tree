//Pablo Salinas
//COSC 2436
//Assignment 3: Binary Trees
//Due Date: 11/30/2016

#include <iostream> //Declaring my headers using Fstream to read and write into the program from a file
#include <string>
#include <fstream>

using namespace std;

template <class elemType>
struct nodeType {
	elemType info;
	nodeType<elemType> *llink;
	nodeType<elemType> *rlink;
	nodeType<elemType> *root;
};
template <class elemType>
class binaryTreeType {
private:
	void inorder(nodeType<elemType> *p) {
		if (p != nullptr) {
			inorder(p->llink);
			cout << p->info << " ";
			inorder(p->rlink);
			
		}
	}
	void preorder(nodeType<elemType> *p) {
		if (p != nullptr) {
			cout << p->info << " ";
			preorder(p->llink);
			preorder(p->rlink);
		}
	}
	void postorder(nodeType<elemType> *p) {
		if (p != nullptr) {
			postorder(p->llink);
			postorder(p->rlink);
			cout << p->info << " ";
		}
	}
	void bfirst(nodeType<elemType> *p) {
		if (p != nullptr) {
			cout << p->info << " ";
			bfirst(p->rlink);
			bfirst(p->llink);
		}
	}
	int height(nodeType<elemType> *p) {
		if (p != nullptr) {
			return 0;
		}
		else {
			return 1 + max(height(p->llink), height(p->rlink));
		}
	}
	int max(int x, int y) {
		if (x >= y) {
			return x;
		}
		else {
			return y;
		}
	}
	void destroy(nodeType<elemType>* &p) {
		if (p != nullptr) {
			destroy(p->llink);
			destroy(p->rlink);
			delete p;
			p = nullptr;
		}
	}


protected:
	nodeType<elemType> *root;
public:
	binaryTreeType() {
		root = nullptr;
	}
	bool isEmpty() {
		return (root == nullptr);
	}
	void inorderTraversal() {
		inorder(root);
	}
	void preorderTraversal() {
		preorder(root);
	}
	void postorderTraversal() {
		postorder(root);
	}
	void bfirstTraversal() {
		bfirst(root);
	}
	int treeHeight() {
		return height(root);
	}
	void destroyTree() {
		destroy(root);
	}
};
template<class elemType>
class bsearchtree: public binaryTreeType<elemType> {
public:
	bool search(const elemType& searchItem) {
		nodeType<elemType> *current;
		bool found = false;
		if (root == nullptr) {
			cout << "Cannot search an emptry tree." << endl;
		}
		else {
			current = root;
			while (current != nullptr && !found) {
				if (current->info == searchItem) {
					found = true;
				}
				else if (current->info > searchItem) {
					current = current->llink;
				}
				else {
					current = current->rlink;
				}
			}
		}
	}
	void insert(const elemType& insertItem){
		nodeType<elemType> *current; //pointer to traverse the tree
		nodeType<elemType> *trailCurrent= nullptr; //pointer behind current
		nodeType<elemType> *newNode; //pointer to create the node
		newNode = new nodeType<elemType>;
		newNode->info = insertItem;
		newNode->llink = nullptr;
		newNode->rlink = nullptr;
		if (root == nullptr) {
			root = newNode;
		}
		else{
			current = root;
			while (current != nullptr){
				trailCurrent = current;
				if (current->info == insertItem){
					cout << "The item to be inserted is already ";
					cout << "in the tree -- duplicates are not allowed." << endl;
					return;
				}
				else if (current->info > insertItem){
					current = current->llink;
				}
				else {
					current = current->rlink;
				}
			}
			if (trailCurrent->info > insertItem)
				trailCurrent->llink = newNode;
			else
				trailCurrent->rlink = newNode;
		}
	}

	void deleteNode(const elemType& deleteItem) {
		nodeType<elemType> *current; //pointer to traverse the tree
		nodeType<elemType> *trailCurrent; //pointer behind current
		bool found = false;
		if (root == nullptr)
			cout << "Cannot delete from an empty tree."
			<< endl;
		else{
			current = root;
			trailCurrent = root;
			while (current != nullptr && !found)
			{
				if (current->info == deleteItem)
					found = true;
				else
				{
					trailCurrent = current;
					if (current->info > deleteItem)
						current = current->llink;
					else
						current = current->rlink;
				}
			}//end while
			if (current == nullptr) {
				cout << "The item to be deleted is not in the tree." << endl;
			}
			else if (found){
				if (current == root) {
					deleteFromTree(root);
				}
				else if (trailCurrent->info > deleteItem){
					deleteFromTree(trailCurrent->llink);
				}
				else {
					deleteFromTree(trailCurrent->rlink);
				}
			}
			else {
				cout << "The item to be deleted is not in the tree." << endl;
			}
		}
	}

private:
	void deleteFromTree(nodeType<elemType>* &p){
		nodeType<elemType> *current; //pointer to traverse the tree
		nodeType<elemType> *trailCurrent; //pointer behind current
		nodeType<elemType> *temp; //pointer to delete the node
		if (p == nullptr) {
			cout << "Error: The node to be deleted does not exist."<< endl;
		}
		else if (p->llink == nullptr && p->rlink == nullptr){
			temp = p;
			p = nullptr;
			delete temp;
		}
		else if (p->llink == nullptr){
			temp = p;
			p = temp->rlink;
			delete temp;
		}
		else if (p->rlink == nullptr){
			temp = p;
			p = temp->llink;
			delete temp;
		}
		else{
			current = p->llink;
			trailCurrent = nullptr;
			while (current->rlink != nullptr){
				trailCurrent = current;
				current = current->rlink;
			}//end while
			p->info = current->info;
			if (trailCurrent == nullptr) { //current did not move;
										 //current == p->lLink; adjust p
				p->llink = current->llink;
			}
			else {
				trailCurrent->rlink = current->llink;
				delete current;
			}
		}
	} 
};

int main() {
	
	bsearchtree<string> btree;
	string str;
	
	
	ifstream infile;
	infile.open("names.txt");
	while (infile) {
		infile >> str;
		btree.insert(str);
	}
	infile.close();
	btree.deleteNode("5");
	btree.preorderTraversal();
	cout << endl;
	btree.inorderTraversal();
	cout << endl;
	btree.postorderTraversal();
	cout << endl;
	btree.bfirstTraversal();
	cout << endl;



	system("pause");
	return 0;
}

