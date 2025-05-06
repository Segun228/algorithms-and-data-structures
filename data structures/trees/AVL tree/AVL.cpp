#include <iostream>
#include <vector>

using namespace std;
class AVL{
    private:
        struct Node{
            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent = nullptr;
            int height = 1;
            int val;
        };
        Node* root = nullptr;

        Node* rightTurn(Node* target){
            if(target==nullptr || target->left==nullptr){
                return target;
            }
            Node* x = target->left;
            target->left = x->right;
            if(x->right){
                x->right->parent = target;
            }
            x->right = target;
            x->parent = target->parent;
            target->parent = x;
            if(x->parent){
                if(x->parent->left==target){
                    x->parent->left = x;
                }
                else{
                    x->parent->right = x;
                }
            }
            else{
                root = x;
            }
            target->height = max(getHeight(target->left), getHeight(target->right)) + 1;
            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
            return x;
        }

        Node* leftTurn(Node* target){
            if(target==nullptr || target->right==nullptr){
                return target;
            }
            Node* x = target->right;
            target->right = x->left;
            if(x->left){
                x->left->parent = target;
            }
            x->left = target;
            x->parent = target->parent;
            target->parent = x;
            if(x->parent){
                if(x->parent->left==target){
                    x->parent->left = x;
                }
                else{
                    x->parent->right = x;
                }
            }
            else{
                root = x;
            }
            target->height = max(getHeight(target->left), getHeight(target->right)) + 1;
            x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
            return x;
        }

        int getHeight(Node* node) {
            return node ? node->height : 0;
        }

        void updateHeight(Node* node){
            if(node == nullptr){
                return;
            }
            if(!node->left && !node->right){
                node->height=1;
                if(node->parent){
                    updateHeight(node->parent);
                }
            }
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
            Node* balanced = solveProblem(node);
            if (balanced && balanced->parent == nullptr) {
                root = balanced;
            }
            if(node->parent){
                updateHeight(node->parent);
            }
        }

        int getBalance(Node* node) {
            return getHeight(node->left) - getHeight(node->right);
        }


        Node* solveProblem(Node* target){
            int balance = getBalance(target);
            if(balance >= 2){
                if(getBalance(target->left) == 1){
                    return rightTurn(target);
                }
                else if(getBalance(target->left) == -1){
                    target->left = leftTurn(target->left);
                    return rightTurn(target);
                }
            }
            else if(balance <= -2){
                if(getBalance(target->right) == -1){
                    return leftTurn(target);
                }
                else if(getBalance(target->right) == 1){
                    target->right = rightTurn(target->right);
                    return leftTurn(target);
                }
            }
            return target;
        }


    public:
        AVL(){
            cout << "Tree initialized" << endl;
            root = new Node;
        }

        AVL(int val){
            cout << "Tree initialized" << endl;
            root = new Node;
            root->val = val;
        }

        AVL(vector <int> data){
            cout << "Tree initialized" << endl;
            root = new Node;
            for(auto el : data){
                this->insert(el);
            }
        }

        void recursiveDestroy(Node* target){
            if(target->left!=nullptr){
                recursiveDestroy(target->left);
            }
            if(target->right!=nullptr){
                recursiveDestroy(target->right);
            }
            delete target;
        }
    public:
        
        bool check(int val){
            if(root==nullptr){
                cout <<"The tree is empty"<< endl;
                return false;
            }
            Node* current = root;
            while(current!=nullptr){
                if(current->val==val){
                    cout <<"The node" << val << " has been succesfully found!"<< endl;
                    return true;
                }
                else if(val > current->val){
                    if(current->right!=nullptr){
                        current = current->right;
                    }
                    else{
                        cout <<"No corresponding node"<< endl;
                        return false;
                    }
                }
                else if(val < current->val){
                    if(current->left!=nullptr){
                        current = current->left;
                    }
                    else{
                        cout <<"No corresponding node"<< endl;
                        return false;
                    }
                }
            }
            cout <<"No corresponding node"<< endl;
            return false;
        }

        Node* find(int val){
            if(root==nullptr){
                cout <<"The tree is empty"<< endl;
                return nullptr;
            }
            Node* current = root;
            while(current!=nullptr){
                if(current->val==val){
                    cout <<"The node" << val << " has been succesfully found!"<< endl;
                    return current;
                }
                else if(val > current->val){
                    if(current->right!=nullptr){
                        current = current->right;
                    }
                    else{
                        cout <<"No corresponding node"<< endl;
                        return nullptr;
                    }
                }
                else if(val < current->val){
                    if(current->left!=nullptr){
                        current = current->left;
                    }
                    else{
                        cout <<"No corresponding node"<< endl;
                        return nullptr;
                    }
                }
            }
            cout <<"No corresponding node"<< endl;
            return nullptr;
        }


        Node* insert(int val){
            if(root==nullptr){
                cout <<" The node "<< val <<" has been inserted succesfully"<< endl;
                root = new Node;
                root->val = val;
                return root;
            }
            Node* current = root;
            while(current!=nullptr){
                if(val == current->val){
                    cout <<" The node "<< val <<" is already in the tree"<< endl;
                    return current;
                }
                else if(val > current->val){
                    if(current->right==nullptr){
                        current->right = new Node;
                        current->right->val = val;
                        updateHeight(current->right);
                        current->right->parent = current;
                        cout <<" The node "<< val <<" has been inserted succesfully"<< endl;
                        return current->right;
                    }
                    current = current->right;
                }
                else if(val < current->val){
                    if(current->left==nullptr){
                        current->left = new Node;
                        updateHeight(current->left);
                        current->left->val = val;
                        current->left->parent = current;
                        cout <<" The node "<< val <<" has been inserted succesfully"<< endl;
                        return current->left;
                    }
                    current = current->left;
                }
            }
            cout <<" The node "<< val <<" has been inserted succesfully"<< endl;
            return current;
        }

        int remove(int val){
            int buf;
            Node* target = find(val);
            Node* pointer;
            Node* father = target->parent;
            if(root==nullptr || !target){
                cout <<" The node can`t be removed "<< endl;
                return -1;
            }
            if(!target->left && !target->right){
                if(target->parent==nullptr){
                    buf = target->val;
                    delete target;
                    this->root = nullptr;
                    cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                if(target->parent->right!=nullptr && target==target->parent->right){
                    target->parent->right = nullptr;
                }
                else{
                    target->parent->left = nullptr;
                }
                buf = target->val;
                delete target;
                updateHeight(father);
                cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                return buf;
            }
            else if(target->left && !target->right){
                if(target->parent->right!=nullptr && target == target->parent->right){
                    target->parent->right = target->left;
                    target->left->parent = target->parent;
                    buf = target->val;
                    delete target;
                    updateHeight(father);
                    cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                else{
                    target->parent->left = target->left;
                    target->left->parent = target->parent;
                    buf = target->val;
                    delete target;
                    updateHeight(father);
                    cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
            }
            else if(!target->left && target->right){
                if(target->parent->right!=nullptr && target == target->parent->right){
                    target->parent->right = target->right;
                    target->right->parent = target->parent;
                    buf = target->val;
                    delete target;
                    updateHeight(father);
                    cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                else{
                    target->parent->left = target->right;
                    target->right->parent = target->parent;
                    buf = target->val;
                    delete target;
                    updateHeight(father);
                    cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
            }
            else{
                buf = target->val;
                pointer = target->left;
                while(pointer->right!=nullptr){
                    pointer = pointer->right;
                }
                father = pointer->parent;
                if(pointer->left!=nullptr){
                    target->val = pointer->val;
                    if(pointer->parent->right!=nullptr && pointer->parent->right==pointer){
                        pointer->parent->right = pointer->left;
                        pointer->left->parent = pointer->parent->right;
                        delete pointer;
                        updateHeight(father);
                    }
                    else if(pointer->parent->left!=nullptr && pointer->parent->left==pointer){
                        pointer->parent->left = pointer->left;
                        pointer->left->parent = pointer->parent->left;
                        delete pointer;
                        updateHeight(father);
                    }
                }
                else{
                    target->val = pointer->val;
                    delete pointer;
                    updateHeight(father);
                }
                cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                return buf;
            }
        }
};