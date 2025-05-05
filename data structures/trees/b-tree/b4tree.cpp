#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BTree{
    private:
        struct Node{
            vector <int> values;
            vector <Node*> children;
            Node* parent = nullptr;
        };
        Node* root = nullptr;

        int dumb_push_to_node(int val, Node* exact){
            if(exact==nullptr){
                return -1;
            }
            else if(exact->values.size()==0){
                exact->values.push_back(val);
                return 0;
            }
            else{
                exact->values.push_back(val);
                int i = exact->values.size()-2;
                while(i!=-1){
                    if(val<exact->values[i]){
                        swap(val, exact->values[i]);
                        --i;
                    }
                    else{
                        return 0;
                    }
                }
            }
            return 0;
        }

        Node* validate(Node* target){
            if(!isValid(target)){
                return divide(target);
            }
            return target;
        }

        bool dumb_delete(Node* target, int val) {
            if (!check_node(val, target)) {
                return false;
            }
            for (size_t i = 0; i < target->values.size(); ++i) {
                if (target->values[i] == val) {
                    target->values.erase(target->values.begin() + i);
                    return true;
                }
            }
            return false;
        }

        bool isValid(Node* target){
            if(target->values.size() > max_keys){
                return false;
            }
            return true;
        }

        Node* divide(Node* target){
            if(target->parent == nullptr){
                Node* newLeft = new Node;
                Node* newRight = new Node;
                newLeft->parent = target;
                newRight->parent = target;
                for(int i=0; i< t-1; i++){
                    newLeft->values.push_back(target->values[i]);
                }
                for(int i=t; i< 2*t-1; i++){
                    newRight->values.push_back(target->values[i]);
                }
                int buf = target->values[t-1];
                target->values.clear();
                target->values.push_back(buf);
                for(int i=0; i< t; i++){
                    newLeft->children.push_back(target->children[i]);
                    target->children[i]->parent = newLeft;
                }
                for(int i=t; i< 2*t; i++){
                    newRight->children.push_back(target->children[i]);
                    target->children[i]->parent = newRight;
                }
                target->children.clear();
                target->children.push_back(newLeft);
                target->children.push_back(newRight);
                return target;
            }

            Node* brother = new Node;
            brother->parent = target->parent;
            for(int i=t; i< 2*t-1; i++){
                brother->values.push_back(target->values[i]);
            }
            for(int i=t; i< 2*t; i++){
                brother->children.push_back(target->children[i]);
                target->children[i]->parent = brother;
            }
            int gift = target->values[t-1];
            for(int i=2*t-2; i>=t; i--){
                target->values.pop_back();
            }
            for(int i=2*t-1; i>=t; i--){
                target->children.pop_back();
            }
            auto it = std::find(target->parent->children.begin(), target->parent->children.end(), target);
            target->parent->children.insert(it + 1, brother);
            dumb_push_to_node(gift, target->parent);
            validate(target->parent);
            return target->parent;
        }

        Node* push_and_validate(Node* target, int val){
            dumb_push_to_node(val, target);
            if(!isValid(target)){
                return validate(target);
            }
            return target;
        }
        
        bool check_node(int val, Node* exact){
            if(std::find(exact->values.begin(), exact->values.end(), val) != exact->values.end()){
                return true;
            }
            return false;
        }

        Node* search(int val, Node* me){
            if(me==nullptr){
                cout << val << " cannot be found, the root is empty" << endl;
                return nullptr;
            }
            if(check_node(val, me)){
                cout << val << " was sucessfully found" << endl;
                return me;
            }
            else{
                if(me->children.size()==0){
                    cout << val << " was not found" << endl;
                    return nullptr;
                }
                if(val < me->values[0]){
                    return search(val, me->children[0]);
                }
                else{
                    for(int i=1; i<me->values.size(); i++){
                        if(val > me->values[i-1] && val < me->values[i]){
                            return search(val, me->children[i]);
                        }
                    }
                    return search(val, me->children.back());
                }
                cout << val << " was not found" << endl;
                return nullptr;
            }
            cout << val << " was not found" << endl;
            return nullptr;
        }

    public:
        int t;
        int min_keys, max_keys, min_children, max_children;

        BTree(int t_inp){
            root = nullptr;
            t = t_inp;
            min_keys = t - 1;
            max_keys = 2*t - 1;
            min_children = t;
            max_children = 2*t;
            cout << "Empty tree created" << endl;
            cout <<"The degree is "<< t << endl;
        }

        ~BTree(){

        }

        Node* find(int val){
            return search(val, root);
        }

        Node* push(int val){
            if(root == nullptr){
                root = new Node;
                root->values.push_back(val);
                cout << val << " was succesfully pushed" << endl;
                return root;
            }
            Node* current = this->find(val);
            if(current){
                cout << "ERROR" << endl;
                cout << val << " is already in the tree" << endl;
                return current;
            }
            if(root->children.size()==0 && root->values.size()<max_keys){
                dumb_push_to_node(val, root);
                cout << val << " was succesfully pushed" << endl;
                return root;
            }
            else if(root->values.size()>=max_keys){
                root = push_and_validate(root, val);
                cout << val << " was succesfully pushed" << endl;
                return root;
            }
            current = root;
            while(current->children.size()!=0){
                bool flag = false;
                if(val < current->values[0]){
                    current = current->children[0];
                    flag = true;
                }
                else{
                    for(int i=1; i<current->values.size(); i++){
                        if(val > current->values[i-1] && val < current->values[i]){
                            current = current->children[i];
                            flag = true;
                        }
                    }
                }
                if(!flag){
                    current = current->children.back();
                }
            }
            push_and_validate(current, val);
            cout << val << " was succesfully pushed" << endl;
            return current;
        }

        Node* pop(int val){
            if(root == nullptr){
                cout << "ERROR" << endl;
                cout <<val <<" cannot be popped, the tree is empty"<< endl;
            }
            else if(!find(val)){
                cout << "ERROR" << endl;
                cout <<val <<" cannot be popped, it is not present in the tree"<< endl;
            }
            Node* current = root;
            while(current->children.size()!=0){
                if(check_node(val, current)){
                    break;
                }
                bool flag = false;
                if(val < current->values[0]){
                    current = current->children[0];
                    flag = true;
                }
                else{
                    for(int i=1; i<current->values.size(); i++){
                        if(val > current->values[i-1] && val < current->values[i]){
                            current = current->children[i];
                            flag = true;
                        }
                    }
                }
                if(!flag){
                    current = current->children.back();
                }
            }
            if(current->children.size() == 0){

            }



            


        }

        void clean(){

        }
};