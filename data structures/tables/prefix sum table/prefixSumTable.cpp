#include <iostream>
#include <vector>
using namespace std;
class prefixSumTable{
    private:
        vector <vector<int>> mainTable;
        vector <int> buf;

    public:
    prefixSumTable(vector <int> nums){
        std:: cout<<"building the table..."<<endl;
        mainTable = vector<vector<int>>(2);
        for(auto el : nums){
            this->mainTable[0].push_back(el);
        }
        int acumSum=0;
        for(int i=0; i<this->mainTable[0].size();i++){
            mainTable[1].push_back(acumSum + mainTable[0][i]);
            acumSum = acumSum + mainTable[0][i];
        }
        std:: cout<<endl;
        std:: cout<<"the table is ready"<<endl;
    }


    void printTable(){
        std::cout << endl;
        std::cout << endl;
        std::cout << endl;
        for(int i=0; i<this->mainTable[0].size();i++){
            std::cout << i << "\t";
        }
        std::cout << endl;
        for(auto el : mainTable[0]){
            std::cout << el << "\t";
        }
        std::cout << endl;
        for(auto el : mainTable[1]){
            std::cout << el << "\t";
        }
        std::cout << endl;
        std::cout << endl;
        std::cout << endl;
    }


    void addElement(int elem){
        this->mainTable[0].push_back(elem);
        this->mainTable[1].push_back(elem + *(mainTable[1].end() - 1));
        std:: cout<<"Element added"<<endl;
    }

    int sumOnInterval(int l, int r){
        if(l<0 || r<0 || r<l || l>=mainTable[0].size() || r>=mainTable[0].size()){
            std::cout << "Index range error, check the indexes" << endl;
            return -1;
        }
        if(l==0){
            std::cout << "sum between " << l << " and " << r << " indexes is " << (mainTable[1][r]) << endl;
            return mainTable[1][r];
        }
        std::cout << "sum between " << l << " and " << r << " indexes is " << (mainTable[1][r] - mainTable[1][l-1]) << endl;
        return (mainTable[1][r] - mainTable[1][l-1]);
    }

    void rearrangeTable(vector <int> nums){
        mainTable[0].clear();
        mainTable[1].clear();
        for(auto el : nums){
            this->mainTable[0].push_back(el);
        }
        int acumSum=0;
        for(int i=0; i<this->mainTable[0].size();i++){
            mainTable[1].push_back(acumSum + mainTable[0][i]);
            acumSum = acumSum + mainTable[0][i];
        }
        std:: cout<<endl;
        std:: cout<<"the table is ready"<<endl;
    }

    void removeLastElement(){
        if(!mainTable[0].empty()){
            mainTable[0].pop_back();
            mainTable[1].pop_back();
            cout << "Last element removed" << endl;
        }
        else{
            cout << "Table is already empty" << endl;
        }
    }
};


int main(){
    vector <int> nums = {1, 4, 5, 3 ,55 ,6 ,7 ,7 ,88 , 9 ,0, 0, 44, 5,33};
    prefixSumTable table1(nums);
    table1.printTable();
    table1.addElement(77);
    table1.sumOnInterval(1, 5);
    table1.sumOnInterval(4, 6);
    table1.sumOnInterval(0, 6);
    table1.sumOnInterval(9, 5);
    table1.addElement(88);
    table1.addElement(88);
    table1.addElement(88);
    table1.addElement(88);
    table1.printTable();
    return 0;
}