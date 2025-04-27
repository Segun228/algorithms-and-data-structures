#include <iostream>
#include <vector>
using namespace std;

class BST{
    private:
        struct Node{
            Node* left;
            Node* right;
            Node* parent;
            int value;
            Node() : left(nullptr), right(nullptr), parent(nullptr) {}
        };
        Node* root;
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
        BST(){
            cout <<"Creating BST..."<< endl;
            root = nullptr;
        }

        BST(int val){
            root = new Node;
            root->value = val;
        }

        BST(vector <int> nums){
            for(auto el : nums){
                this->insert(el);
            }
        }

        ~BST(){
            recursiveDestroy(root);
            cout <<" The BST has been succesfully destroyed "<< endl;
        }

        
        bool check(int val){
            if(root==nullptr){
                cout <<"The tree is empty"<< endl;
                return false;
            }
            Node* current = root;
            while(current!=nullptr){
                if(current->value==val){
                    cout <<"The node" << val << " has been succesfully found!"<< endl;
                    return true;
                }
                else if(val > current->value){
                    if(current->right!=nullptr){
                        current = current->right;
                    }
                    else{
                        cout <<"No corresponding node"<< endl;
                        return false;
                    }
                }
                else if(val < current->value){
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
                if(current->value==val){
                    cout <<"The node" << val << " has been succesfully found!"<< endl;
                    return current;
                }
                else if(val > current->value){
                    if(current->right!=nullptr){
                        current = current->right;
                    }
                    else{
                        cout <<"No corresponding node"<< endl;
                        return nullptr;
                    }
                }
                else if(val < current->value){
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
                root->value = val;
                return root;
            }
            Node* current = root;
            while(current!=nullptr){
                if(val == current->value){
                    cout <<" The node "<< val <<" is already in the tree"<< endl;
                    return current;
                }
                else if(val > current->value){
                    if(current->right==nullptr){
                        current->right = new Node;
                        current->right->value = val;
                        current->right->parent = current;
                        cout <<" The node "<< val <<" has been inserted succesfully"<< endl;
                        return current->right;
                    }
                    current = current->right;
                }
                else if(val < current->value){
                    if(current->left==nullptr){
                        current->left = new Node;
                        current->left->value = val;
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
                    buf = target->value;
                    delete target;
                    this->root = nullptr;
                    cout <<" The node with value "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                if(target->parent->right!=nullptr && target==target->parent->right){
                    target->parent->right = nullptr;
                }
                else{
                    target->parent->left = nullptr;
                }
                buf = target->value;
                delete target;
                cout <<" The node with value "<< buf <<" has been succesfully removed "<< endl;
                return buf;
            }
            else if(target->left && !target->right){
                if(target->parent->right!=nullptr && target == target->parent->right){
                    target->parent->right = target->left;
                    target->left->parent = target->parent;
                    buf = target->value;
                    delete target;
                    cout <<" The node with value "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                else{
                    target->parent->left = target->left;
                    target->left->parent = target->parent;
                    buf = target->value;
                    delete target;
                    cout <<" The node with value "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
            }
            else if(!target->left && target->right){
                if(target->parent->right!=nullptr && target == target->parent->right){
                    target->parent->right = target->right;
                    target->right->parent = target->parent;
                    buf = target->value;
                    delete target;
                    cout <<" The node with value "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
                else{
                    target->parent->left = target->right;
                    target->right->parent = target->parent;
                    buf = target->value;
                    delete target;
                    cout <<" The node with value "<< buf <<" has been succesfully removed "<< endl;
                    return buf;
                }
            }
            else{
                buf = target->value;
                pointer = target->left;
                while(pointer->right!=nullptr){
                    pointer = pointer->right;
                }
                if(pointer->left!=nullptr){
                    target->value = pointer->value;
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
                    target->value = pointer->value;
                    delete pointer;
                }
                cout <<" The node with value "<< buf <<" has been succesfully removed "<< endl;
                return buf;
            }
        }
};

int main(){
    vector<int> data = {3, 4, 5, 22, 65, 34, 98, 30, 1, 44, 3, 12};
    BST tree1(data);
    tree1.remove(4);
    tree1.remove(44);
    tree1.check(44);
    cout << tree1.find(22) << endl;
    tree1.insert(44);
    tree1.check(44);
}