#include <iostream>
#include <string>
using namespace std;
int main(){
    string given;
    string compressed;
    cin >> given;
    int counter = 0;
    auto p1 = given.begin();
    auto p2 = given.begin();
    while(p1!=given.end()){
        if(*p1==*p2){
            counter++;
            p1++;
        }
        else{
            compressed+=*p2;
            if(counter>1){
                compressed+=to_string(counter);
            }
            
            counter = 0;
            p2=p1;
        }
    }
    compressed+=(*p2);
    compressed+=to_string(counter);
    cout << compressed;
}