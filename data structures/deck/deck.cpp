#include <iostream>
#include <string>
using namespace std;
class Deck{
    private:
        struct Node{
            int val;
            Node* left = nullptr;
            Node* right = nullptr;
        };
        Node* head = nullptr;
        Node* current = nullptr;
        int length = 0;

        void recursive_destroy_left(Node* myself){
            Node* current = nullptr;
            if(myself->left==nullptr){
                delete myself;
                return;
            }
            recursive_destroy_left(myself->left);
            delete myself;
            return;
        }

        void recursive_destroy_right(Node* myself){
            Node* current = nullptr;
            if(myself->right==nullptr){
                delete myself;
                return;
            }
            recursive_destroy_right(myself->right);
            delete myself;
            return;
        }

    public:
        void push_front(int n){
            Node* current = nullptr;
            length++;
            if(head==nullptr){
                head = new Node;
                head->val = n;
                cout << "ok" << endl;
                return;
            }
            current = head;
            while(current->left!=nullptr){
                current = current->left;
            }
            current->left = new Node;
            current->left->right = current;
            current->left->val = n;
            cout << "ok" << endl;
        }

        void push_back(int n){
            Node* current = nullptr;
            length++;
            if(head==nullptr){
                head = new Node;
                head->val = n;
                cout << "ok" << endl;
                return;
            }
            current = head;
            while(current->right!=nullptr){
                current = current->right;
            }
            current->right = new Node;
            current->right->left = current;
            current->right->val = n;
            cout << "ok" << endl;
        }
        
        void pop_front(){
            Node* current = nullptr;
            if(head==nullptr || length==0){
                cout << "error" << endl;
                return;
            }
            if(length==1){
                length--;
                int buf = head->val;
                delete head;
                head = nullptr;
                cout << buf << endl;
                return;
            }
            if(head->left==nullptr){
                length--;
                int buf = head->val;
                head=head->right;
                delete head->left;
                head->left = nullptr;
                cout << buf << endl;
                return;
            }
            length--;
            current = head;
            while(current->left!=nullptr){
                current = current->left;
            }
            current->right->left = nullptr;
            int buf = current->val;
            delete current;
            cout << buf << endl;
        }

        
        void pop_back(){
            Node* current = nullptr;
            if(head==nullptr || length==0){
                cout << "error" << endl;
                return;
            }
            if(length==1){
                length--;
                int buf = head->val;
                delete head;
                head = nullptr;
                cout << buf << endl;
                return;
            }
            if(head->right==nullptr){
                length--;
                int buf = head->val;
                head=head->left;
                delete head->right;
                head->right = nullptr;
                cout << buf << endl;
                return;
            }
            length--;
            current = head;
            while(current->right!=nullptr){
                current = current->right;
            }
            current->left->right = nullptr;
            int buf = current->val;
            delete current;
            cout << buf << endl;
        }

        
        void front(){
            Node* current = nullptr;
            if(head==nullptr){
                cout << "error" << endl;
                return;
            }
            if(length==1){
                cout<<head->val<<endl;
                return;
            }
            current = head;
            while(current->left!=nullptr){
                current = current->left;
            }
            cout << current->val << endl;
            return;
        }
        
        void back(){
            Node* current = nullptr;
            if(head==nullptr){
                cout << "error" << endl;
                return;
            }
            if(length==1){
                cout<<head->val<<endl;
                return;
            }
            current = head;
            while(current->right!=nullptr){
                current = current->right;
            }
            cout << current->val << endl;
            return;
        }

        
        void size(){
            Node* current = nullptr;
            cout << length << endl;
        }
        
        void clear(){
            Node* current = nullptr;
            if(head==nullptr){
                cout << "ok" << endl;
                return;
            }
            if(head->left != nullptr){
                recursive_destroy_left(head->left);
            }
            if(head->right != nullptr){
                recursive_destroy_right(head->right);
            }
            delete head;
            head = nullptr;
            cout << "ok" << endl;
            length = 0;
            return;
        }
};

int main(){
    string command;
    int num;
    Deck sample;
    while(true){
        cin >> command;
        if(command=="exit"){
            cout << "bye" << endl;
            return 0;
        }
        else if(command=="clear"){
            sample.clear();
        }
        else if(command=="size"){
            sample.size();
        }
        else if(command=="back"){
            sample.back();
        }
        else if(command=="front"){
            sample.front();
        }
        else if(command=="pop_back"){
            sample.pop_back();
        }
        else if(command=="pop_front"){
            sample.pop_front();
        }
        else if(command=="push_front"){
            cin >> num;
            sample.push_front(num);
        }
        else if(command=="push_back"){
            cin >> num;
            sample.push_back(num);
        }
    }
    return 0;
}