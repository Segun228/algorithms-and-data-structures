#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;
class Treap{
    private:
        static minstd_rand generator;
        struct Node{
            int key, priority;
            Node* left = nullptr;
            Node* right = nullptr;
            Node(int key) : key(key), priority(generator()) {}
        };

        Node* root = nullptr; 

        static Node* merge(Node* a, Node* b){
            if(!a || !b){
                return a ? a : b;
            }
            if(a->priority > b->priority){
                a->right = merge(a->right, b);
                return a;
            }
            else{
                b->left = merge(a, b->left);
                return b;
            }
        }

        static void split(Node* n, int key, Node*& a, Node*& b){
            if(!n){
                a = nullptr;
                b = nullptr;
                return;
            }
            if(n->key < key){
                split(n->right, key, n->right,b);
                a = n;
            }
            else{
                split(n->left, key, a, n->left);
                b = n;
            }
        }
    public:
        void insert(int key){
            Node *less, *greater;
            split(root, key, less, greater);
            less = merge(less, new Node(key));
            root = merge(less, greater);
        }

        bool find(int key){
            Node *less, *equal, *greater;
            split(root, key, less, greater);
            split(greater, key+1, equal, greater);
            bool flag = equal ? true : false;
            merge(merge(less, equal), greater);
            return flag;
        }

        void erase(int key){
            Node *less, *equal, *greater;
            split(root, key, less, greater);
            split(greater, key+1, equal, greater);
            root = merge(less, greater);
        }
};

minstd_rand Treap :: generator;