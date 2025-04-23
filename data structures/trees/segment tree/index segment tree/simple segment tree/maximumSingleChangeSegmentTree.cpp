#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;
class segmentTreeI{
    private:
        struct Node{
            int max_val;
            int min_val;
            int selfLeft;
            int selfRight;
            int promise;
            int index;
            Node() : max_val(INT_MIN), min_val(INT_MAX), selfLeft(0), selfRight(0), promise(0), index(1) {}
        };
        int nb, k, n, length, power;
        vector<Node> buf;
        vector<Node> full;
    public:
        void printSequence(){
            for(auto i = full.size()-buf.size(); i<full.size(); i++){
                if(full[i].max_val<=-2147483647){
                    cout  <<"NULL"<< "\t";
                }
                else if(full[i].max_val>=2147483647){
                    cout << "NULL"<< "\t";
                }
                else{
                    cout << full[i].max_val << "\t";
                }
                
            }
            cout << endl;
        }

        segmentTreeI(vector <int> nums){
            power = log2(nums.size()) + 1;
            buf = vector<Node>(int(pow(2, power)));
            n = buf.size();
            for(auto i=0; i<nums.size(); i++){
                buf[i].max_val = nums[i];
                buf[i].min_val = nums[i];
                buf[i].index = i;
                buf[i].selfLeft = i;
                buf[i].selfRight = i;
            }
            length = int(pow(2, power+1)) - 1;
            full = vector<Node>(length);
            for(int i = length-1, j = buf.size()-1; i >= length - buf.size(); i--, j--){
                full[i] = buf[j];
            }
            for(int i = length-1; i > 1; i-=2){
                if((full[i].max_val)==(full[i-1].max_val)){
                    full[int((i-1)/2)].max_val = (full[i].max_val);
                    full[int((i-1)/2)].index = (full[i].index);
                }
                else if((full[i].max_val)>(full[i-1].max_val)){
                    full[int((i-1)/2)].max_val = (full[i].max_val);
                    full[int((i-1)/2)].index = (full[i].index);
                }
                else{
                    full[int((i-1)/2)].max_val = (full[i-1].max_val);
                    full[int((i-1)/2)].index = (full[i-1].index);
                }

                if((full[i].min_val)==(full[i-1].min_val)){
                    full[int((i-1)/2)].min_val = (full[i].min_val);
                }
                else if((full[i].min_val)<(full[i-1].min_val)){
                    full[int((i-1)/2)].min_val = (full[i].min_val);
                }
                else{
                    full[int((i-1)/2)].min_val = (full[i-1].min_val);
                }

                full[int((i-1)/2)].selfLeft = min((full[i].selfLeft), (full[i-1].selfLeft));
                full[int((i-1)/2)].selfRight = max((full[i].selfRight), (full[i-1].selfRight));
            }
        }


        void updateElement( int number, int newValue){
            int origSize = buf.size();
            int tree_index, curent_index;
            number--;
            tree_index = full.size()  - origSize + number;
            full[tree_index].max_val = newValue;
            full[tree_index].min_val = newValue;
            curent_index = tree_index;
            while(curent_index>0){
                curent_index = (curent_index-1)/2;
                if(full[2*curent_index +1].max_val > full[2*curent_index +2].max_val){
                    full[curent_index].max_val = full[2*curent_index +1].max_val;
                    full[curent_index].index = full[2*curent_index +1].index;
                }
                else{
                    full[curent_index].max_val = full[2*curent_index +2].max_val;
                    full[curent_index].index = full[2*curent_index +2].index;
                }
                if(full[2*curent_index +1].min_val < full[2*curent_index +2].min_val){
                    full[curent_index].min_val = full[2*curent_index +1].min_val;
                }
                else{
                    full[curent_index].min_val = full[2*curent_index +2].min_val;
                }
            }
            if(full[2*curent_index +1].max_val > full[2*curent_index +2].max_val){
                full[curent_index].max_val = full[2*curent_index +1].max_val;
                full[curent_index].index = full[2*curent_index +1].index;
            }
            else{
                full[curent_index].max_val = full[2*curent_index +2].max_val;
                full[curent_index].index = full[2*curent_index +2].index;
            }
            if(full[2*curent_index +1].min_val < full[2*curent_index +2].min_val){
                full[curent_index].min_val = full[2*curent_index +1].min_val;
            }
            else{
                full[curent_index].min_val = full[2*curent_index +2].min_val;
            }
            return;
        }


        void printTree(){
            for(int i = 0; i < (this->length); i++){
                cout << i << "\t";
            }
            cout << endl;
            for(int i = 0; i<(this->length); i++){
                cout << full[i].max_val << "\t";
            }
            cout << endl;
        }

        int getMax(int l, int r){
            if(r>(this->n-1) || l>r || l>(this->n-1) || l<0 || r<0){
                cout << "invalid indexes, check the borders" << endl;
                return INT_MIN;
            }
            int max_val = sendMaxRequest(l, r, 0, full).first;
            cout << "Maximum from "<< l << " to " << r << " is " << max_val << endl;
            return max_val;
        }

        int getMin(int l, int r){
            if(r>(this->n-1) || l>r || l>(this->n-1) || l<0 || r<0){
                cout << "invalid indexes, check the borders" << endl;
                return INT_MAX;
            }
            int min_val = sendMinRequest(l, r, 0, full).first;
            cout << "Minimum from "<< l << " to " << r << " is " << min_val << endl;
            return min_val;
        }

        private:
            pair<int, int> sendMaxRequest(int l, int r, int myIndex, vector<Node>& full){
                int leftSelf = full[myIndex].selfLeft;
                int rightSelf = full[myIndex].selfRight;
                if(l<=leftSelf && r>=rightSelf){
                    return {full[myIndex].max_val, full[myIndex].index};
                }
                else if(rightSelf < l || leftSelf > r){
                    return {INT_MIN, full[myIndex].index};
                }
                pair <int, int> answer1 = sendMaxRequest(l, r,(myIndex*2 + 1), full);
                pair <int, int> answer2 = sendMaxRequest(l, r, (myIndex*2 + 2), full);
                if(answer1.first == answer2.first){
                    return {answer1.first, (answer1.second)};
                }
                else if(answer1.first > answer2.first){
                    return {answer1.first, answer1.second};
                }
                return {answer2.first, answer2.second};
            }

            pair<int, int> sendMinRequest(int l, int r, int myIndex, vector<Node>& full){
                int leftSelf = full[myIndex].selfLeft;
                int rightSelf = full[myIndex].selfRight;
                if(l<=leftSelf && r>=rightSelf){
                    return {full[myIndex].min_val, full[myIndex].index};
                }
                else if(rightSelf < l || leftSelf > r){
                    return {INT_MAX, full[myIndex].index};
                }
                pair <int, int> answer1 = sendMinRequest(l, r,(myIndex*2 + 1), full);
                pair <int, int> answer2 = sendMinRequest(l, r, (myIndex*2 + 2), full);
                if(answer1.first == answer2.first){
                    return {answer1.first, (answer1.second)};
                }
                else if(answer1.first < answer2.first){
                    return {answer1.first, answer1.second};
                }
                return {answer2.first, answer2.second};
            }
};

int main(){
    vector<int> input = {2, 5, 3, 1, 2, 9, 4, 99, 34, 42, 2, 3};
    segmentTreeI tree(input);
    tree.printSequence();
    tree.updateElement(2, 77);
    tree.updateElement(3, -277);
    tree.updateElement(4, 177);
    tree.updateElement(6, 87);
    tree.getMax(1, 5);
    tree.getMax(5, 6);
    tree.getMax(1, 5);
    tree.getMin(1, 8);
    tree.getMin(5, 6);
    tree.getMin(1, 5);
    tree.printSequence();
    
}