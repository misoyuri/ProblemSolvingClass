#include <iostream>

using namespace std;

#define FIRST 1 
#define SECOND 2
#define THIRD 3

int *target_rod;
int *current_rod;

void hanoi(int n, int start, int to, int by, long long &cnt)
{
    cnt++;
    if(n == 1){
        current_rod[n] = to;
    }else{
        hanoi(n-1, start, by, to, cnt);
        current_rod[n] = to;
        hanoi(n-1, by, to, start, cnt);
    }
}

int main() {
    int n, k;
    int num_disk = 0, dist_name = 0;;
    long long answer = 0;
    cin >> n >> k;

    target_rod = new int[n + 1];
    current_rod = new int[n + 1];

    for(int i = 1; i < 4; i++){
        cin >> num_disk;
        for(int j = 0; j < num_disk; j++){
            cin >> dist_name; 
            target_rod[dist_name] = i;
        }
    }

    for(int i = 1; i <= n; i++){
        current_rod[i] = k;
    }

    for(int i = n; i >= 1; i--){
        if(target_rod[i] == current_rod[i]) continue;
        if(i == 1){
            answer++;
            break;
        }
        hanoi(i-1, current_rod[i],  6 - current_rod[i] - target_rod[i], target_rod[i], answer);
        answer++;
    }

    cout << answer << endl;

    return 0;
}