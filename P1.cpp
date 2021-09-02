#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

int subSolve(string numbers){
    int len = numbers.length();
    int ret = 0;
    for(int i = 2; i <= len; i++){
        ret += (int)pow(10, len - i) * (int)pow(9, i - 2);
    }
    cout << "In sub::" << numbers << " | " << ret << endl;
    
    return ret;
}

int solve(string brokenCounter){
    int ret = 0;
    int len = brokenCounter.length() - 1;
    for(int i = 0 ; i < len; i++){
        if(brokenCounter[i] > '4'){
            ret += pow(10, len - i);
            ret += (brokenCounter[i] - '0' - 1) * subSolve(to_string((int)pow(10, len - i)));
        }else{
            ret += (brokenCounter[i] - '0') * subSolve(to_string((int)pow(10, len - i)));
        }
        cout << "brokenCounter: " << brokenCounter << "] " << ret << endl;
    }

    return ret;
}

int main(){
    string brokenCounter = "";
    size_t fixedCounter = 0;

    cin >> brokenCounter;

    // fixedCounter = brokenCounter - solve(brokenCounter);
    
    cout << stoi(brokenCounter) - solve(brokenCounter) << endl;
    // cout << fixedCounter << endl;
    return 0;
}