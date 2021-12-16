#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

#define PIZZA 1
#define CHINESE 2
#define NOT_DETERMINDED 0

using namespace std;

int N = 0;
pair<long long, long long> position[50000];
vector<int> building_map[50000];
int brands[50000]{0, };

int BFS(int start){
    queue<int> q;

    int num_of_brands[3] = {0, 0, 0};

    q.push(start);
    brands[start] = PIZZA;
    num_of_brands[PIZZA]++;

    while(!q.empty()){
        int curr_postion = q.front();
        q.pop();

        for(int i = 0; i < building_map[curr_postion].size(); i++){
            int next_position = building_map[curr_postion][i];
            if(brands[next_position] == NOT_DETERMINDED){
                q.push(next_position);
                brands[next_position] = 3 - brands[curr_postion];
                num_of_brands[brands[next_position]] += 1;
            }
        }
    }

    return min(num_of_brands[1], num_of_brands[2]);
}

void define_graphs(){
    long long x_dist2 = 0;
    long long y_dist2 = 0;
    
    for(int curr = 0; curr < N; curr++){
        for(int next = curr+1; next < N; next++){
            if(position[next].first - position[curr].first > 5) break;

            x_dist2 = (position[next].first  - position[curr].first)  * (position[next].first  - position[curr].first);
            y_dist2 = (position[next].second - position[curr].second) * (position[next].second - position[curr].second);

            if(x_dist2 + y_dist2 <= 25){
                building_map[curr].push_back(next);
                building_map[next].push_back(curr);
            }
        }
    }

}

int main(){
    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> position[i].first >> position[i].second;
    }

    sort(position, position + N);
    
    int ans = 0;
    define_graphs();

    for(int i = 0; i < N; i++){
        if(brands[i] == NOT_DETERMINDED){
            ans += BFS(i);
        }
    }
    
    cout << ans << endl;

    return 0;
}