#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(){
    vector <int> big_number;
    for (int i = 0; i < 10; i++){
        big_number.push_back(9);
    }
    int buf=1;
    big_number.push_back(0);

    for(int i = big_number.size()-1;i>0;i--){
        big_number[i]=big_number[i-1];
    }
    big_number[0]=0;
    cout << "moved array:" << endl;
    for(int el : big_number){
        cout << el << endl;
    }
    for(int i = big_number.size()-1;i>0;i--){
        big_number[i]+=buf;
        if(big_number[i]==10){
            big_number[i]=0;
        }
        else{
            buf = 0;
            break;
        }
    }
    if(buf==1){
        big_number[0]=1;
    }
    if(big_number[0]==0){
        big_number.erase(big_number.begin());
    }
    cout<<"result array"<<endl;
    for(int el : big_number){
        cout << el << endl;
    }
    return 0;
}