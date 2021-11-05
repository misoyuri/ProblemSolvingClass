#include <iostream>
#include <vector>
#include <queue>

#define INTMAX 2147483647
#define NOT_DETERMINDED 0
#define DAY1 1
#define DAY2 2
using namespace std;

int n = 0;
int m = 0;


pair<int, int> pairs[100001];
vector<int> pills_map[10001];

bool is_valid(int schedule[], int init_pill, int level_){
    queue<int> q;

    schedule[init_pill] = DAY1;

    q.push(init_pill);

    while(!q.empty()){
        int current_pill_id = q.front();
        q.pop();

        for(int i = 0; i < pills_map[current_pill_id].size(); i++){
            int next_pill_id = pills_map[current_pill_id][i];
            if(schedule[next_pill_id] == NOT_DETERMINDED){
                schedule[next_pill_id] = schedule[current_pill_id] == DAY1 ? DAY2 : DAY1;
                q.push(next_pill_id);

            }else if(schedule[next_pill_id] == schedule[current_pill_id]){
                return false;
            }
        }
    }
    return true;
}

void reset_schedule(int schedule[]){
    for(int i = 1; i <= n; i++){
        schedule[i] = NOT_DETERMINDED;
    }
}

int solve(){

    int schedule[10001]{0, };
    for(int i = 0; i < m; i++){
        pills_map[pairs[i].first].push_back(pairs[i].second);
        pills_map[pairs[i].second].push_back(pairs[i].first);

        if(!is_valid(schedule, pairs[i].first, i)){
            reset_schedule(schedule);
            if(!is_valid(schedule, pairs[i].first, i)){
                return i + 1;
            }
        } 
    }
    return m ;
}

int main(){
    cin >> n;
    cin >> m;
    
    for(int i = 0; i < m; i++){
        cin >> pairs[i].first >> pairs[i].second;
    }

    cout << solve() << endl;

}