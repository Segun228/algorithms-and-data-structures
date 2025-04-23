#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;
class SparceTable{
    private:
        vector <vector<int>> mainTable;
        int length;
        int height;

    public:
    SparceTable(vector <int> nums){
        std:: cout<<"building the table..."<<endl;
        this->length = nums.size();
        this->height = log2(length);
        mainTable = vector<vector<int>>(height+1, vector<int>(length+1, INT_MAX));
        for(auto i=0; i<length; i++){
            this->mainTable[0][i] = nums[i];
        }
        for(int i=1, k=0; i<height+1; k+=int(pow(2, (i-1))), i++){
            for(int j=0; j<length - int(pow(2, (i-1))) - k; j++){
                mainTable[i][j] = min(mainTable[i-1][j], mainTable[i-1][j+int( pow(2, (i-1)) )]);
            }
        }
        
        std:: cout<<endl;
        std:: cout<<"the table is ready"<<endl;
    }


    void printTable(){
        std::cout << endl;
        for(int i=0; i<this->length;i++){
            std::cout << i << "\t";
        }
        std::cout << endl;
        for(int i=0; i<this->length;i++){
            std::cout << mainTable[0][i] << "\t";
        }
        std::cout << endl;
        for(int i=1, k=0; i<height+1; k+=int(pow(2, (i-1))), i++){
            for(int j=0; j<length - int(pow(2, (i-1))) - k; j++){
                std::cout << mainTable[i][j] << "\t";
            }
            std::cout << endl;
        }
        std::cout << endl;
        std::cout << endl;
        std::cout << endl;
    }


    

    int getminOnInterval(int l, int r){
        if(l<0 || r<0 || r<l || l>=length || r>=length){
            std::cout << "Index range error, check the indexes" << endl;
            return INT_MAX;
        }
        int interval_length = r - l + 1;
        int line = int(log2(interval_length));
        int min_val = min(mainTable[line][l], mainTable[line][r+1-int(pow(2, line))]);
        std::cout << "minimum value from " << l << " to "<< r <<" is "<< min_val << endl;
        return min_val;
    }


    void rearrangeTable(vector <int> nums){
        std:: cout<<"rebuilding the table..."<<endl;
        this->length = nums.size();
        this->height = log2(length);
        mainTable = vector<vector<int>>(height+1, vector<int>(length+1, INT_MAX));
        for(auto i=0; i<length; i++){
            this->mainTable[0][i] = nums[i];
        }
        for(int i=1, k=0; i<height+1; k+=int(pow(2, (i-1))), i++){
            for(int j=0; j<length - int(pow(2, (i-1))) - k; j++){
                mainTable[i][j] = min(mainTable[i-1][j], mainTable[i-1][j+int(pow(2, (i-1)) )]);
            }
        }
        std:: cout<<endl;
        std:: cout<<"new table is ready"<<endl;
    }
};


int main(){
    vector<int> nums = {7, 1, 2, 4, 2, 3, 1, 5, 9, 6};
    SparceTable table(nums);
    table.printTable();
    table.getminOnInterval(0, 4);
    table.getminOnInterval(2, 8);
    table.getminOnInterval(1, 8);
    table.getminOnInterval(4, 5);
    table.getminOnInterval(3, 9);
    table.getminOnInterval(2, 20);
    return 0;
}