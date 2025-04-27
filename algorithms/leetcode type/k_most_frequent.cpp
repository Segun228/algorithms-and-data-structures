#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <unordered_map>
using namespace std;
int main(){
    priority_queue <char, int> letters;
    map <char, int> freq;
    int k = 2;
    string s = "iriufhwuhfewojfoiejfewjfjwefjwfebvewfwfvbi";
    for(char el : s){
        freq[el]++;
    }
    for(auto pair : freq){
        letters.push(pair.first(), pair.second());
    }
    for(int i = 0; i<k;i++){
        int a = letters.top();
        letters.pop();
        cout << a << endl;
    }
}