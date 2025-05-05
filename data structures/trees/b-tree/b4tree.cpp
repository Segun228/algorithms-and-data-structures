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

        void recursive_destroy(Node* target){
            if(target->children.size()==0){
                delete target;
            }
            else{
                for(auto child : target->children){
                    recursive_destroy(child);
                }
                delete target;
            }
        }

        void fix_underflow(Node* target) {
            Node* parent = target->parent;
            if(!parent){
                return;
            } 
            int idx = -1;
            for (int i = 0; i<parent->children.size(); i++) {
                if(parent->children[i] == target) {
                    idx = i;
                    break;
                }
            }
            Node* left_sibling = (idx > 0) ? parent->children[idx - 1] : nullptr;
            Node* right_sibling = (idx < parent->children.size() - 1) ? parent->children[idx + 1] : nullptr;
            if (left_sibling && left_sibling->values.size() > min_keys) {
                target->values.insert(target->values.begin(), parent->values[idx - 1]);
                parent->values[idx - 1] = left_sibling->values.back();
                left_sibling->values.pop_back();
                if (!left_sibling->children.empty()) {
                    target->children.insert(target->children.begin(), left_sibling->children.back());
                    left_sibling->children.back()->parent = target;
                    left_sibling->children.pop_back();
                }
                return;
            }
            if (right_sibling && right_sibling->values.size() > min_keys) {
                target->values.push_back(parent->values[idx]);
                parent->values[idx] = right_sibling->values.front();
                right_sibling->values.erase(right_sibling->values.begin());
        
                if (!right_sibling->children.empty()) {
                    target->children.push_back(right_sibling->children.front());
                    right_sibling->children.front()->parent = target;
                    right_sibling->children.erase(right_sibling->children.begin());
                }
                return;
            }
            if(left_sibling){
                left_sibling->values.push_back(parent->values[idx - 1]);
                left_sibling->values.insert(left_sibling->values.end(), target->values.begin(), target->values.end());
                left_sibling->children.insert(left_sibling->children.end(), target->children.begin(), target->children.end());
                for(auto child : target->children){
                    if(child){
                        child->parent = left_sibling;
                    }
                }
                parent->values.erase(parent->values.begin() + idx - 1);
                parent->children.erase(parent->children.begin() + idx);
                delete target;
                if (parent->values.size() < min_keys)
                    fix_underflow(parent);
            } 
            else if(right_sibling){
                target->values.push_back(parent->values[idx]);
                target->values.insert(target->values.end(), right_sibling->values.begin(), right_sibling->values.end());
                target->children.insert(target->children.end(), right_sibling->children.begin(), right_sibling->children.end());
                for (auto child : right_sibling->children) {
                    if (child) child->parent = target;
                }
                parent->values.erase(parent->values.begin() + idx);
                parent->children.erase(parent->children.begin() + idx + 1);
                delete right_sibling;
                if (parent->values.size() < min_keys)
                    fix_underflow(parent);
            }
            if (parent == root && parent->values.empty()) {
                if(!parent->children.empty()) {
                    root = parent->children[0];
                    root->parent = nullptr;
                } 
                else{
                    root = nullptr;
                }
                delete parent;
            }
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
            this->clean();
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

        Node* pop(int val) {
            if (root == nullptr) {
                cout << "ERROR: " << val << " cannot be popped, the tree is empty" << endl;
                return nullptr;
            }
            Node* node_with_val = find(val);
            if (!node_with_val) {
                cout << "ERROR: " << val << " cannot be popped, it is not present in the tree" << endl;
                return nullptr;
            }
            if (node_with_val->children.empty()) {
                dumb_delete(node_with_val, val);
                if (node_with_val == root && root->values.empty()) {
                    delete root;
                    root = nullptr;
                    return nullptr;
                }
                if (node_with_val->values.size() < min_keys && node_with_val != root) {
                    fix_underflow(node_with_val);
                }
                return root;
            }
            int idx = -1;
            for (int i = 0; i < node_with_val->values.size(); i++) {
                if (node_with_val->values[i] == val) {
                    idx = i;
                    break;
                }
            }
            if (idx != -1) {
                Node* pred = node_with_val->children[idx];
                while (!pred->children.empty())
                    pred = pred->children.back();
                int pred_val = pred->values.back();
                node_with_val->values[idx] = pred_val;
                dumb_delete(pred, pred_val);
                if (pred->values.size() < min_keys)
                    fix_underflow(pred);
            }
            return root;
        }

        void clean(){
            if(root==nullptr){
                cout << "The tree was succesfully cleaned" << endl;
                return;
            }
            recursive_destroy(root);
            root = nullptr;
            cout << "The tree was succesfully cleaned" << endl;
            return;
        }
};