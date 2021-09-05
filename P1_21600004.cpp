#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

long subSolve(string numbers){
    int len = numbers.length();
    long ret = 0;

    for(int i = 2; i <= len; i++){
        ret += (long)pow(10, len - i) * (long)pow(9, i - 2);
    }
    return ret;
}

long solve(string brokenCounter){
    long ret = 0;
    int len = brokenCounter.length() - 1;
    for(int i = 0 ; i <= len; i++){
        if(brokenCounter[i] > '4'){
            ret += (long)pow(10, len - i);
            ret += (brokenCounter[i] - '0' - 1) * subSolve(to_string((int)pow(10, len -i)));
        }else if(brokenCounter[i] != '0'){
            ret += (brokenCounter[i] - '0') * subSolve(to_string((int)pow(10, len - i)));
        }
    }

    return ret;
}

int main(){
    string brokenCounter = "";
    long fixedCounter = 0;

    cin >> brokenCounter;

    fixedCounter = stol(brokenCounter) - solve(brokenCounter);
    cout << fixedCounter << endl;
    return 0;
}