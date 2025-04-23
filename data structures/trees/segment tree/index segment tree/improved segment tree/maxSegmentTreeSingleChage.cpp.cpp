#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include <fstream>
using namespace std;

struct Node{
    int val;
    int selfLeft;
    int selfRight;
    int promise;
    int index;
    Node() : val(INT_MIN), selfLeft(0), selfRight(0), promise(0), index(1) {}
};

pair<int, int> sendRequest(int l, int r, int myIndex, vector<Node>& full){
    int leftSelf = full[myIndex].selfLeft;
    int rightSelf = full[myIndex].selfRight;
    if(l<=leftSelf && r>=rightSelf){
        return {full[myIndex].val, full[myIndex].index};
    }
    else if(rightSelf < l || leftSelf > r){
        return {INT_MIN, full[myIndex].index};
    }
    pair <int, int> answer1 = sendRequest(l, r,(myIndex*2 + 1), full);
    pair <int, int> answer2 = sendRequest(l, r, (myIndex*2 + 2), full);
    if(answer1.first == answer2.first){
        return {answer1.first, (answer1.second)};
    }
    else if(answer1.first > answer2.first){
        return {answer1.first, answer1.second};
    }
    return {answer2.first, answer2.second};
}

void updateElement(vector<Node>& full, int number, int newValue, int origSize){
    int tree_index, curent_index;
    number--;
    tree_index = full.size()  - origSize + number;
    full[tree_index].val = newValue;
    curent_index = tree_index;
    while(curent_index>0){
        curent_index = (curent_index-1)/2;
        if(full[2*curent_index +1].val > full[2*curent_index +2].val){
            full[curent_index].val = full[2*curent_index +1].val;
            full[curent_index].index = full[2*curent_index +1].index;
        }
        else{
            full[curent_index].val = full[2*curent_index +2].val;
            full[curent_index].index = full[2*curent_index +2].index;
        }
    }
    if(full[2*curent_index +1].val > full[2*curent_index +2].val){
        full[curent_index].val = full[2*curent_index +1].val;
        full[curent_index].index = full[2*curent_index +1].index;
    }
    else{
        full[curent_index].val = full[2*curent_index +2].val;
        full[curent_index].index = full[2*curent_index +2].index;
    }
    return;
}


int main(){
    ifstream fin("answerinput2.txt");
    ofstream fout("answeroutput.txt");
    int nb, k, n, length, power;
    vector<Node> buf;
    fin >> nb;
    vector<int> nums;
    vector<Node> full;
    for(int i=0; i<nb; i++){
        fin >> n;
        nums.push_back(n);
    }
    power = log2(nums.size()) + 1;
    buf = vector<Node>(int(pow(2, power)));
    n = buf.size();
    for(auto i=0; i<nums.size(); i++){
        buf[i].val = nums[i];
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
        if((full[i].val)==(full[i-1].val)){
            full[int((i-1)/2)].val = (full[i].val);
            full[int((i-1)/2)].index = (full[i].index);
        }
        else if((full[i].val)>(full[i-1].val)){
            full[int((i-1)/2)].val = (full[i].val);
            full[int((i-1)/2)].index = (full[i].index);
        }
        else{
            full[int((i-1)/2)].val = (full[i-1].val);
            full[int((i-1)/2)].index = (full[i-1].index);
        }
        full[int((i-1)/2)].selfLeft = min((full[i].selfLeft), (full[i-1].selfLeft));
        full[int((i-1)/2)].selfRight = max((full[i].selfRight), (full[i-1].selfRight));
    }
    fin >> k;
    pair <int, int> answer;
    int left_input, right_input;
    char id;
    for(int i = 0; i<k; i++){
        fin >> id;
        if(id=='u'){
            fin >> left_input;
            fin >> right_input;
            updateElement(full, left_input, right_input, buf.size());
            for(int i=length-n; i<length; i++){
                cout << full[i].val << " ";
            }
            cout << endl;
        }
        else{
            fin >> left_input;
            fin >> right_input;
            left_input--;
            right_input--;
            answer = sendRequest(left_input, right_input, 0, full);

            fout << answer.first << " ";
        }
    }
    return 0;
}