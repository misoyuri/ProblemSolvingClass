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

int max_level = 0;

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

int solve(){

    for(int i = 0; i < m; i++){
        int schedule[10001]{0, };
        pills_map[pairs[i].first].push_back(pairs[i].second);
        pills_map[pairs[i].second].push_back(pairs[i].first);

        // int before_day = schedule[pairs[i].first];
        // schedule[pairs[i].first] = NOT_DETERMINDED;
        // // schedule[pairs[i].second] = NOT_DETERMINDED;

        if(!is_valid(schedule, pairs[i].first, i)) return i + 1;


        // for(int j = 1; j <= n; j++){
        //     if(schedule[j] == NOT_DETERMINDED && pills_map[schedule[j]].size() != 0)
        //         if(!is_valid(schedule, j, i)) return i + 1;

        // }
    }
    return -1000 ;
}

int main(){
    cin >> n;
    cin >> m;
    
    for(int i = 0; i < m; i++){
        cin >> pairs[i].first >> pairs[i].second;
    }

    cout << solve() << endl;

}