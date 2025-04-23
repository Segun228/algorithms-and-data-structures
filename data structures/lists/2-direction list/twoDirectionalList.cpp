#include <iostream>
#include <vector>
using namespace std;

class twoDirectionalList{
    private:
        struct Node{
            Node* next;
            Node* prev;
            int val;
        };
        Node* head;
    public:
        twoDirectionalList(){
            this->head = nullptr;
        }


        twoDirectionalList(int num){
            head = new Node;
            head->val = num;
            head->next = nullptr;
            head->prev = nullptr;
        }


        twoDirectionalList(const twoDirectionalList& b){
            if(b.head==nullptr){
                this->head = nullptr;
                return;
            }
            head = new Node;
            head->next = nullptr;
            Node* curent = b.head;
            Node* our_curent = this->head;
            Node* our_new;
            our_curent->val = curent->val;
            while(curent!=nullptr){
                our_curent->val = curent->val;
                our_new = new Node;
                our_curent->next = our_new;
                our_new->prev = our_curent;
                our_curent = our_curent->next;
                curent = curent->next;
            }
            delete our_curent->next;
            our_curent->next=nullptr;
            return;
        }


        ~ twoDirectionalList(){
            Node* del = this->head;
            while(head!=nullptr){
                del = head;
                head = head->next;
                delete del;
            }
        }


        Node* findElem(int elem){
            if(this->head==nullptr){
                cout << "The list is empty" <<endl;
                return nullptr;
            }
            Node* curent = head;
            while(curent!=nullptr && curent->val != elem){
                curent = curent->next;
            }
            if(curent==nullptr){
                std::cout << "Element was not found" << endl;
                return nullptr;
            }
            std::cout << "Element was succesfuly found" << endl;
            return curent;
        }


        void printList(){
            Node* curent = head;
            while (curent != nullptr) {
                cout << curent->val << " <-> ";
                curent = curent->next;
            }
            cout << "NULL" << endl;
        }


        Node* removeElem(int elem){
            if(this->head==nullptr){
                cout << "The list is empty" <<endl;
                return nullptr;
            }
            Node* rem = this->findElem(elem);
            if(rem==nullptr){
                std::cout << "No corresponding element" << endl;
                return head;
            }
            Node* curent = head;
            Node* prev = head;
            if(rem==head){
                head->next->prev = nullptr;
                head = head->next;
                delete rem;
                std::cout << "Element was succesfuly removed" << endl;
                return head;
            }
            else if (rem->next==nullptr){
                prev->next = nullptr;
                delete rem;
                std::cout << "Element was succesfuly removed" << endl;
                return head;
            }
            prev->next=rem->next;
            rem->next->prev = prev;
            delete rem;
            std::cout << "Element was succesfuly removed" << endl;
            return head;
        }


        Node* insertElem(int index, int num){
            if(this->head==nullptr){
                cout << "The list is empty" <<endl;
                return nullptr;
            }
            int counter = 0;
            Node* insert;
            Node* curent = head;
            Node* prev = head;
            if(index<0){
                std::cout << "Index can`t be negative" << endl;
                return nullptr;
            }
            else if(index==0){
                insert = new Node;
                insert->val = num;
                insert->next = head;
                head = insert;
                return head;
            }
            while(counter!=index && curent->next!=nullptr){
                prev = curent;
                curent = curent->next;
                counter++;
            }
            if(curent->next==nullptr){
                insert = new Node;
                insert->val = num;
                insert->next = nullptr;
                curent->next = insert;
                insert->prev = curent;
                std::cout << "Element was sucessfully inserted" << endl;
                return head;
            }
            insert = new Node;
            insert->val = num;
            insert->next = curent;
            curent->prev = insert;
            insert->prev = prev;
            prev->next = insert;
            std::cout << "Element was sucessfully inserted" << endl;
            return head;
        }


        int getLength(){
            Node* curent = head;
            int counter = 0;
            if(head == nullptr){
                std::cout << "List length: 0" << endl;
                return 0;
            }
            while(curent!=nullptr){
                counter++;
                curent = curent->next;
            }
            std::cout << "List length: " << counter << endl;
            return counter;
        }


        Node* addElem(int num){
            Node* curent = head;
            if(head == nullptr){
                head = new Node;
                head->next = nullptr;
                head->val = num;
                return head;
            }
            while(curent->next!=nullptr){
                curent = curent->next;
            }
            Node* addingEl = new Node;
            addingEl->val=num;
            addingEl->next=nullptr;
            addingEl->prev=curent;
            curent->next=addingEl;
            return addingEl;
        }


        int popElem(){
            if(this->head==nullptr){
                cout << "The list is empty" <<endl;
                return 0;
            }
            if (head->next == nullptr) {
                int data = head->val;
                delete head;
                head = nullptr;
                return data;
            }
            Node* curent = head;
            Node* prev = head;
            while(curent->next!=nullptr){
                prev = curent;
                curent = curent->next;
            }
            int data = curent->val;
            delete curent;
            prev->next = nullptr;
            std::cout << "Popped last element with value: " << data << endl;
            return data;
        }
};


int main(){
    twoDirectionalList list1(3);
    list1.addElem(3);
    list1.addElem(3);
    list1.addElem(4);
    list1.addElem(3);
    list1.addElem(5);
    list1.addElem(3);
    list1.addElem(77);
    list1.getLength();
    list1.findElem(3);
    list1.printList();
}