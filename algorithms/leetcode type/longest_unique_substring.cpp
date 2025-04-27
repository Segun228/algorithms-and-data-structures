#include <iostream>
#include <string>
#include <set>
using namespace std;
int main(){
    string s = "abcabcab";
    int maxi = 1;
    int counter = 0;
    set <char> repet;
    auto p1 = s.begin();
    while(p1!=s.end()){
        if(repet.find(*p1)!=repet.end()){
            repet.insert(*p1);
            counter++;
        }
        else{
            if(counter>maxi){
                maxi = counter;
            }
            repet.clear();
            repet.insert(*p1);
        }
        p1++;
    }
    if(counter>maxi){
        maxi = counter;
    }
    cout << maxi;
    return maxi;
    

}