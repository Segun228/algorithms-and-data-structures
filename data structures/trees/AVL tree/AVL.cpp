#include <iostream>
#include <vector>

using namespace std;
class AVL{
    private:
        struct Node{
            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent = nullptr;
            int val;
        };
        Node* root = nullptr;

        Node* leftTurn(Node* target){
            if(target->left==nullptr){
                return nullptr;
            }
            Node* x = target->left;
            Node** parent_link = nullptr;
            if(!target->parent){
                x->parent = nullptr;
                if(x->right==nullptr){
                    x->right = target;
                    target->left = nullptr;
                }
                else{
                    target->left = x->right;
                    x->right = target;
                }
                target->parent = x;
                return x;
            }
            else if(target->parent->left && target->parent->left == target){
                parent_link = &target->parent->left;
            }
            else if(target->parent->right && target->parent->right == target){
                parent_link = &target->parent->right;
            }
            if(x->right==nullptr){
                x->right = target;
                target->left = nullptr;
                *parent_link = x;
            }
            else{
                target->left = x->right;
                x->right->parent = target;
                x->right = target;
                *parent_link = x;
            }
            target->parent = x;
            return x;
        }

        Node* rightTurn(Node* target) {
            if (!target || !target->right)
                return nullptr;
            Node* x = target->right;
            Node** parent_link = nullptr;
            if (!target->parent){
                x->parent = nullptr;
            } 
            else{
                if(target->parent->left == target){
                    parent_link = &target->parent->left;
                }
                else if(target->parent->right == target){
                    parent_link = &target->parent->right;
                }
                *parent_link = x;
                x->parent = target->parent;
            }
            target->right = x->left;
            if(x->left){
                x->left->parent = target;
            }
            x->left = target;
            target->parent = x;
            return x;
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
                        current->right->parent = current;
                        cout <<" The node "<< val <<" has been inserted succesfully"<< endl;
                        return current->right;
                    }
                    current = current->right;
                }
                else if(val < current->val){
                    if(current->left==nullptr){
                        current->left = new Node;
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
                cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                return buf;
            }
            else if(target->left && !target->right){
                if(target->parent->right!=nullptr && target == target->parent->right){
                    target->parent->right = target->left;
                    target->left->parent = target->parent;
                    buf = target->val;
                    delete target;
                    cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                else{
                    target->parent->left = target->left;
                    target->left->parent = target->parent;
                    buf = target->val;
                    delete target;
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
                    cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                else{
                    target->parent->left = target->right;
                    target->right->parent = target->parent;
                    buf = target->val;
                    delete target;
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
                if(pointer->left!=nullptr){
                    target->val = pointer->val;
                    if(pointer->parent->right!=nullptr && pointer->parent->right==pointer){
                        pointer->parent->right = pointer->left;
                        pointer->left->parent = pointer->parent->right;
                        delete pointer;
                    }
                    else if(pointer->parent->left!=nullptr && pointer->parent->left==pointer){
                        pointer->parent->left = pointer->left;
                        pointer->left->parent = pointer->parent->left;
                        delete pointer;
                    }
                }
                else{
                    target->val = pointer->val;
                    delete pointer;
                }
                cout <<" The node with val "<< buf <<" has been succesfully removed "<< endl;
                return buf;
            }
        }
};