#include <iostream>
#include <vector>
using namespace std;

class twoDirectionCircularList{
    private:
        struct Node{
            Node* next;
            Node* prev;
            int val;
        };
        Node* head;
    public:
        twoDirectionCircularList(){
            this->head = nullptr;
        }


        twoDirectionCircularList(int num){
            head = new Node;
            head->val = num;
            head->next = head;
            head->prev = head;
        }


        twoDirectionCircularList(const twoDirectionCircularList& b){
            if(b.head==nullptr){
                return;
            }
            head = new Node;
            head->next = nullptr;
            head->prev = nullptr;
            if(b.head->next==b.head){
                this->head->next = this->head;
                this->head->prev = this->head;
                return;
            }
            Node* curent = b.head;
            Node* our_curent = this->head;
            Node* our_new;
            our_curent->val = curent->val;
            while(curent->next!=b.head){
                our_curent->val = curent->val;
                our_new = new Node;
                our_curent->next = our_new;
                our_new->prev = our_curent;
                our_curent = our_curent->next;
                curent = curent->next;
            }
            our_curent->next=this->head;
            our_curent->val = curent->val;
            head->prev = our_curent;
            return;
        }


        ~ twoDirectionCircularList(){
            Node* del;
            Node* curent = head->next;
            while(curent->next!=head){
                del = curent;
                curent = curent->next;
                delete del;
            }
            delete curent;
            delete this->head;
        }


        Node* findElem(int elem){
            if(this->head==nullptr){
                cout << "The list is empty" <<endl;
                return nullptr;
            }
            if(head->val == elem){
                return head;
            }
            Node* curent = head->next;
            while(curent!=head && curent->val != elem){
                curent = curent->next;
            }
            if(curent==head){
                std::cout << "Element was not found" << endl;
                return nullptr;
            }
            std::cout << "Element was succesfuly found" << endl;
            return curent;
        }


        void printList(){
            cout << "head" << " <-> ";
            Node* curent = head;
            while (curent->next != head) {
                cout << curent->val << " <-> ";
                curent = curent->next;
            }
            cout << curent->val << " <-> ";
            cout << "head" << endl;
        }


        Node* removeElem(int elem){
            if(this->head==nullptr){
                cout << "The list is empty" <<endl;
                return nullptr;
            }
            if(this->findElem(elem)==nullptr){
                std::cout << "No corresponding element" << endl;
                return head;
            }
            Node* curent = head->next;
            Node* prev = head;
            while(curent->val != elem){
                prev = curent;
                curent = curent->next;
            }
            if(curent==head){
                head->next->prev = head->prev;
                head = head->next;
                prev->next = head;
                delete curent;
                std::cout << "Element was succesfuly removed" << endl;
                return head;
            }
            prev->next=curent->next;
            curent->next->prev = prev;
            delete curent;
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
                while(curent->next!=head){
                    curent = curent->next;
                }
                insert = new Node;
                insert->val = num;
                insert->next = head;
                insert->prev=curent;
                head->prev=insert;
                curent->next = insert;
                head = insert;
                return head;
            }
            while(counter!=index && curent->next!=head){
                prev = curent;
                curent = curent->next;
                counter++;
            }
            if(curent->next==head){
                cout << "list index out of range" << endl;
                return nullptr;
            }
            insert = new Node;
            insert->val = num;
            insert->next = curent;
            insert->prev=prev;
            curent->prev=insert;
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
            while(curent->next!=head){
                counter++;
                curent = curent->next;
            }
            counter++;
            std::cout << "List length: " << counter << endl;
            return counter;
        }


        Node* addElem(int num){
            Node* curent = head;
            if(head == nullptr){
                head = new Node;
                head->next = head;
                head->prev = head;
                head->val = num;
                return head;
            }
            while(curent->next!=head){
                curent = curent->next;
            }
            Node* addingEl = new Node;
            addingEl->val=num;
            addingEl->next=head;
            addingEl->prev = curent;
            head->prev = addingEl;
            curent->next=addingEl;
            return addingEl;
        }


        int popElem(){
            if(this->head==nullptr){
                cout << "The list is empty" <<endl;
                return 0;
            }
            Node* curent = head;
            Node* prev = head;
            while(curent->next!=head){
                prev = curent;
                curent = curent->next;
            }
            int data = curent->val;
            delete curent;
            prev->next = head;
            head->prev = prev;
            std::cout << "Popped last element with value: " << data << endl;
            return data;
        }
};


int main(){
    twoDirectionCircularList list1(3);
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