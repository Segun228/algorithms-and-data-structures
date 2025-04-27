#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() 
{
	long long x, counter = 0;
    cin >> x;
    if(x==0){
        cout << 0;
        return 0;
    }

    for(long long i=0; i<64; i++){
        if((x&(1<<i))!=0){
            counter++;
        }
    }
    cout << counter;
	return 0;
}