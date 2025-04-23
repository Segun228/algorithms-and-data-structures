#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

struct Node{
    int val;
    int selfLeft;
    int selfRight;
    int promise;
    int quantity;
    Node() : val(INT_MIN), selfLeft(0), selfRight(0), promise(0), quantity(1) {}
};

pair<int, int> sendRequest(int l, int r, int myIndex, vector<Node>& full){
    int leftSelf = full[myIndex].selfLeft;
    int rightSelf = full[myIndex].selfRight;
    if(l<=leftSelf && r>=rightSelf){
        return {full[myIndex].val, full[myIndex].quantity};
    }
    else if(rightSelf < l || leftSelf > r){
        return {INT_MIN, full[myIndex].quantity};
    }
    pair <int, int> answer1 = sendRequest(l, r,(myIndex*2 + 1), full);
    pair <int, int> answer2 = sendRequest(l, r, (myIndex*2 + 2), full);
    if(answer1.first == answer2.first){
        return {answer1.first, (answer1.second+answer2.second)};
    }
    else if(answer1.first > answer2.first){
        return {answer1.first, answer1.second};
    }
    return {answer2.first, answer2.second};
}

int main(){
    int nb, k, n, length, power;
    vector<Node> buf;
    cin >> nb;
    vector<int> nums;
    vector<Node> full;
    for(int i=0; i<nb; i++){
        cin >> n;
        nums.push_back(n);
    }
    power = log2(nums.size()) + 1;
    buf = vector<Node>(int(pow(2, power)));
    n = buf.size();
    for(auto i=0; i<nums.size(); i++){
        buf[i].val = nums[i];
        buf[i].selfLeft = i;
        buf[i].selfRight = i;
    }
    length = int(pow(2, power+1)) - 1;
    full = vector<Node>(length);
    for(int i = length-1, j = buf.size()-1; i >= length - buf.size(); i--, j--){
        full[i] = buf[j];
    }
    for(int i = length-1; i > 1; i-=2){
        if((full[i].val)==(full[i-1].val)){
            full[int((i-1)/2)].val = (full[i].val);
            full[int((i-1)/2)].quantity = (full[i].quantity)+(full[i-1].quantity);
        }
        else if((full[i].val)>(full[i-1].val)){
            full[int((i-1)/2)].val = (full[i].val);
            full[int((i-1)/2)].quantity = (full[i].quantity);
        }
        else{
            full[int((i-1)/2)].val = (full[i-1].val);
            full[int((i-1)/2)].quantity = (full[i-1].quantity);
        }
        full[int((i-1)/2)].selfLeft = min((full[i].selfLeft), (full[i-1].selfLeft));
        full[int((i-1)/2)].selfRight = max((full[i].selfRight), (full[i-1].selfRight));
    }
    
    cin >> k;
    pair <int, int> answer;
    int left_input, right_input;
    for(int i = 0; i<k; i++){
        cin >> left_input;
        cin >> right_input;
        left_input--;
        right_input--;
        answer = sendRequest(left_input, right_input, 0, full);
        cout << answer.first << " " << answer.second << endl;
    }
    return 0;
}