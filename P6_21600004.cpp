#include <iostream>

#define INT_MAX 2147483647

using namespace std;

int N = 0;
int pipes_accum[501]{0, };
int pipes[501]{0, };
int pipes_assmeble_subset[501][501]{{0, }, };

int solve(){
    int front = 0, rear = 0, middle = 0, cost = 0, possible_cost = 0;

    for(int i = 2; i <= N; i++){
        for(front = 1; front <= N - i + 1; front++){
            rear = front + i - 1;
            cost = pipes_accum[rear] - pipes_accum[front - 1];
            pipes_assmeble_subset[front][rear] = INT_MAX;

            for(middle = front; middle < rear; middle++){
                possible_cost = pipes_assmeble_subset[front][middle] + pipes_assmeble_subset[middle + 1][rear] + cost;

                if(possible_cost < pipes_assmeble_subset[front][rear]){
                    pipes_assmeble_subset[front][rear] = possible_cost;
                }
            }
        }
    }

    return pipes_assmeble_subset[1][N];
}    

int main(){
    cin >> N;

    for(int i = 1; i <= N; i++){
        cin >> pipes[i];
        pipes_accum[i] = pipes_accum[i-1] + pipes[i];
    }

    cout << solve() << endl;
    return 0;

}