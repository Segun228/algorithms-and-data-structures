#include <iostream>
#include <vector>
using namespace std;

class Bitset{
    private:
        int32_t n;
        vector <int32_t> container;

    public:
        Bitset(){
            cout << "The set will have the capacity of 32.000 integers." <<endl
            << "If you want to change the capacity, use the capacity, use resize() method"<<endl;
            this->n = 1000;
            container = vector<int32_t>(n, 0);
        }

        Bitset(int inp){
            this->n = inp;
            container = vector<int>(n, 0);
        }

        void insert(int inp){
            if(this->check(inp)){
                cout << inp << " is already in the set" << endl;
                return;
            }
            if(inp>container.size()*32){
                while(container.size()<=inp){
                    this->resize();
                }
            }
            int containerNumber = inp>>5;
            int bitNumber = inp << 27;
            bitNumber = bitNumber >> 27;
            int32_t buf = 1;
            buf = buf << bitNumber;
            container[containerNumber] |= buf;
            cout << inp << " was sucessfully inserted!" << endl;
            return;
        }

        void remove(int inp){
            if(inp>container.size()*32){
                while(container.size()<=inp){
                    this->resize();
                }
                cout << "no corresponding element" << endl;
                return;
            }
            if(!this->check(inp)){
                cout << inp << " is already in the set" << endl;
                return;
            }
            int containerNumber = inp>>5;
            int bitNumber = inp << 27;
            bitNumber = bitNumber >> 27;
            int32_t buf = 1;
            buf = buf << bitNumber;
            buf = ~buf;
            container[containerNumber] &= buf;
            cout << inp << " was sucessfully removed!" << endl;
        }

        bool check(int inp){
            if(inp>container.size()*32){
                while(container.size()<=inp){
                    this->resize();
                }
            }
            int containerNumber = inp>>5;
            int bitNumber = inp << 27;
            bitNumber = bitNumber >> 27;
            int32_t buf = 1;
            buf = buf << bitNumber;
            int32_t example = container[containerNumber];
            example &= buf;
            if(example==0){
                cout << inp << " not found" << endl;
                return false;
            }
            else{
                cout << inp << " was sucessfully found!" << endl;
                return true;
            }
            return true;
        }

        void resize(){
            for(int i=0; i<container.size(); i++){
                container.push_back(0);
            }
            for(int i=(container.size()-1); i>=(container.size()-1)/2; i--){
                container[i] = container[(container.size()-1)/2-i];
                container[(container.size()-1)/2-i] = 0;
            }
        }

        void print(){
            for(int i=0; i<container.size()*32; i++){
                if(silentCheck(i)){
                    cout << i << "\t";
                }
            }
            cout << endl;
        }

    private:
        bool silentCheck(int inp){
            if(inp>container.size()*32){
                while(container.size()<=inp){
                    this->resize();
                }
            }
            int containerNumber = inp>>5;
            int bitNumber = inp << 27;
            bitNumber = bitNumber >> 27;
            int32_t buf = 1;
            buf = buf << bitNumber;
            int32_t example = container[containerNumber];
            example &= buf;
            if(example==0){
                return false;
            }
            else{
                return true;
            }
            return true;
        }
};

int main(){
    Bitset setus(500);
    cout << setus.check(20) << endl;

    setus.insert(48);
    setus.insert(4);
    setus.insert(434);
    setus.insert(4);
    setus.insert(777);
    setus.insert(23);
    setus.insert(1);
    setus.insert(2);

    setus.remove(1);
    setus.check(1);
    setus.print();
    return 0;
}