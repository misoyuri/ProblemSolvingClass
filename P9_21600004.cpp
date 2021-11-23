#include <iostream>
#include <vector>

using namespace std;

int N = 0;
int B = 0;

vector<int> cell_relations[450];
int weights[450];

int max_weight_sum = 0;

int calc_weighted_sum(vector<int> targets){
    if(targets.size() > 4) return 0;

    int ret = 0;
    // printf("[");
    for(int i = 0; i < targets.size(); i++){
        ret += weights[targets[i]];
        // printf("%d ", targets[i]+1);
    }
    // printf("] %d\n", ret);
    
    return ret;
}


void find_fully_connected(int start_node){
    vector<int> fully_connected;

    fully_connected.push_back(start_node);

    for(int v_id = 0; v_id < N; v_id++){
        bool continue_flag = false;
        bool append_flag = true;

        for(int fc_idx = 0; fc_idx < fully_connected.size(); fc_idx++){
            if(v_id == fully_connected[fc_idx]){
                continue_flag = true;
                break;
            }
        }

        if(continue_flag) continue;

        for(int fc_idx = 0; fc_idx < fully_connected.size(); fc_idx++){
            continue_flag = false;
            for(int adj_cell_to_v_id = 0; adj_cell_to_v_id < cell_relations[v_id].size(); adj_cell_to_v_id++){
                if(fully_connected[fc_idx] == cell_relations[v_id][adj_cell_to_v_id]){
                    continue_flag = true;
                    break;
                }
            }

            if(!continue_flag){
                append_flag = false;
                break;
            }
        }

        if(append_flag)
            fully_connected.push_back(v_id);
    }

    int ret = calc_weighted_sum(fully_connected);

    if(ret > max_weight_sum) max_weight_sum = ret;
}

int main(){
    int cell_id_first = 0;
    int cell_id_second = 0;
    cin >> N >> B;

    for(int i = 0; i < N; i++){
        cin >> weights[i];
    }

    for(int i = 0; i < B; i++){
        cin >> cell_id_first >> cell_id_second;
        cell_relations[cell_id_first-1].push_back(cell_id_second-1);
        cell_relations[cell_id_second-1].push_back(cell_id_first-01);
    }

    for(int i = 0; i < N; i++){
        // printf("Start Node: %d | ", i);
        find_fully_connected(i);
    }
    cout << max_weight_sum << endl;

    return 0;
}