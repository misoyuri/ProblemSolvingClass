#include <iostream>

#define INTMAX 2147483647

using namespace std;

int main(){
    int pipes[501]{0, };
    bool used[501]{0, };
    int N = 0;

    cin >> N;
    int unused = N;
    for(int i = 0; i < N; i++){
        cin >> pipes[i];
    }


    int ret = 0;

    while(unused > 1){
        int idx_adj_left = 0, idx_adj_right = 1;
        int min_adj_left = 0, min_adj_right = 1;
        int loop_min_sum = INTMAX;
        int current_sum = 0;
        while(true){
            while(used[idx_adj_left] == true){
                idx_adj_left++;
            }

            idx_adj_right = idx_adj_left + 1;

            while(used[idx_adj_right] == true){
                idx_adj_right++;
            }

            if(idx_adj_left >= N - 1 || idx_adj_right >= N) break; 

            current_sum = pipes[idx_adj_left] + pipes[idx_adj_right];
            if(loop_min_sum > current_sum){
                min_adj_left = idx_adj_left;
                min_adj_right = idx_adj_right;
                loop_min_sum = current_sum;
            }

            idx_adj_left++;
            idx_adj_right++;
        }

        for(int i = 0; i < N; i++){
            printf("[%3d] ", pipes[i]);
        }
        cout << endl;
        for(int i = 0; i < N; i++){
            printf("[%3d] ", used[i]);
        }
        cout << endl;
        cout << "---------------------------------------------------------------" << endl;
        
        pipes[min_adj_left] = pipes[min_adj_left] + pipes[min_adj_right];
        used[min_adj_right] = true;
        ret += pipes[min_adj_left];
        unused--;
    }

    for(int i = 0; i < N; i++){
        printf("[%3d] ", pipes[i]);
    }
        cout << endl;
    for(int i = 0; i < N; i++){
        printf("[%3d] ", used[i]);
    }
        cout << endl;
    cout << "ret::" << ret << endl;

    cout << ret << endl;
}