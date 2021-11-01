#include <iostream>

#define INTMAX 2147483647

using namespace std;

int pipes[501]{0, };
int total_ret = 0;
int divide(int left, int right){
    if(left - right == 0) return pipes[left];
    if(right - left == 1) return pipes[left] + pipes[right];

    int ret = INTMAX;
    for(int i = left ; i < right; i++){
        int div1 = divide(left, i);
        int div2 = divide(i+1, right);
        ret = min(ret, div1 + div2);
        printf("[%d ~ %d]-> [%d, %d]= %d |  [%d, %d] div2 = %d\n", left, right, pipes[left], pipes[i], div1, pipes[i+1], pipes[right], div2, div1 + div1);
    }
    total_ret += ret;
    return ret;
}

int main(){
    bool used[501]{0, };
    int N = 0;

    cin >> N;
    int unused = N;
    for(int i = 0; i < N; i++){
        cin >> pipes[i];
    }

    int ret = divide(0, N-1);

    cout << "ret::" << total_ret << endl;
}