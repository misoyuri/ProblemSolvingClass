#include <iostream>
#include <algorithm>

#define NOT_YET 0
using namespace std;


struct DEVELOPER{
    int x = 0;
    int y = 0;
    int group = 0;
};

DEVELOPER developers[8000]{{0, 0, 0}, };
int N = 0;

int solve(){
    int groups = N;
    int group_id = 1;
    bool grouping_flag = false;
    for(int i = 0; i < N; i++){
        grouping_flag = false;

        for(int j = i+1; j < N; j++){
            if(i == j) continue;

            if(developers[i].x > developers[j].x && developers[i].y < developers[j].y){
                grouping_flag = true;
            }else if(developers[i].x < developers[j].x && developers[i].y > developers[j].y){
                grouping_flag = true;
            }

            if(grouping_flag){
                // printf("[%d and %d]\n", i, j);
                groups--;   
                grouping_flag = false;                                     
            }

        }
    }

    return groups;
}

int main(){
    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> developers[i].x >> developers[i].y;
    }

    cout << solve() << endl;

    return 0;
}