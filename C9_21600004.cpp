#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define NOT_YET 0
using namespace std;


struct DEVELOPER{
    int x = 0;
    int y = 0;
    int group = 0;
};

DEVELOPER developers[8000]{{0, 0, 0}, };
vector<int> relations[8000];

int N = 0;

void find_max_groups(int start_id, int group_id){
    queue<int> q;
    q.push(start_id);

    while(!q.empty()){
        int current_developer_id = q.front();
        q.pop();

        for(int i = 0; i < relations[current_developer_id].size(); i++){
            int next_developer_id = relations[current_developer_id][i];

            if(developers[next_developer_id].group == NOT_YET){
                developers[next_developer_id].group = group_id;
                q.push(next_developer_id);
            }
        }
    }
}

void find_relations(){
    bool grouping_flag = false;

    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            grouping_flag = false;
            if(developers[i].x > developers[j].x && developers[i].y < developers[j].y){
                grouping_flag = true;
            }else if(developers[i].x < developers[j].x && developers[i].y > developers[j].y){
                grouping_flag = true;
            }

            if(grouping_flag){
                relations[i].push_back(j);
                relations[j].push_back(i);
                grouping_flag = false;                                     
            }
        }
    }
}

int main(){
    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> developers[i].x >> developers[i].y;
    }

    find_relations();
    
    int groups = 0;
    for(int i = 0; i < N; i++){
        if(developers[i].group == NOT_YET){
            groups++;
            find_max_groups(i, groups);
        }
    }
    cout << groups << endl;
    return 0;
}