#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;
class maximumSegmenTreeI{
    private:
        vector<int> buf;
        vector<int> full;
        int length;
        int power;
        int n;
    public:
        maximumSegmenTreeI(vector <int> nums){
            this->power = log2(nums.size()) + 1;
            this->buf = vector<int>(int(pow(2, power)), INT_MIN);
            this->n = this->buf.size();
            for(auto i=0; i<nums.size(); i++){
                buf[i] = nums[i];
            }
            this->length = int(pow(2, this->power+1)) - 1;
            this->full = vector<int>(length, INT_MIN);
            for(int i = length-1, j = buf.size()-1; i >= length - buf.size(); i--, j--){
                full[i] = buf[j];
            }
            for(int i = length-1; i > 1; i-=2){
                full[int((i-1)/2)]=max(full[i], full[i-1]);
            }
        }


        void printTree(){
            for(int i = 0; i < (this->length); i++){
                cout << i << "\t";
            }
            cout << endl;
            for(int i = 0; i<(this->length); i++){
                cout << full[i] << "\t";
            }
            cout << endl;
        }

        void printBuf(){
            for(auto el:buf){
                cout << el << "\t";
            }
            cout << endl;
        }

        int getMax(int l, int r){
            if(r>(this->n -1) || l>r || l>(this->n-1) || l<0 || r<0){
                cout << "invalid indexes, check the borders" << endl;
                return INT_MIN;
            }
            int val = sendRequest(l, r, 0, this->n - 1, 0);
            cout << "Искомое значение:" << val << endl;
            return val;
        }

        private:
            int sendRequest(int l, int r, int leftSelf, int rightSelf, int myIndex){
                if(l<=leftSelf && r>=rightSelf){
                    return full[myIndex];
                }
                else if(rightSelf < l || leftSelf > r){
                    return INT_MIN;
                }
                return max(sendRequest(l, r, leftSelf, (leftSelf+rightSelf)/2, (myIndex*2 + 1)), sendRequest(l, r, ((leftSelf+rightSelf)/2)+1, rightSelf, (myIndex*2 + 2)));
            }
};


int main(){
    vector<int> input = {2, 5, 3, 1, 2, 9, 4};
    maximumSegmenTreeI tree(input);
    tree.printTree();
    tree.getMax(1, 4);
}