#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int N = 0;
int B = 0;

vector<int> cell_edges[450];
vector<int> circle_components;

stack<int> st;
int weights[450];
bool visited_st[450];
bool visited_cc[450];

void DFS_for_stack(int target_node){
    visited_st[target_node] = true;

    for(int i = 0; i < cell_edges[target_node].size(); i++){
        if(visited_st[cell_edges[target_node][i]] == true) continue;

        DFS_for_stack(cell_edges[target_node][i]);
    }

    st.push(target_node);
}

void DFS_for_CC(int target_node){
    visited_cc[target_node] = true;

    for(int i = 0; i < cell_edges[target_node].size(); i++){
        if(visited_cc[cell_edges[target_node][i]] == true) continue;

        DFS_for_CC(cell_edges[target_node][i]);
    }

    circle_components.push_back(target_node);
}

int calc_max_cc(){
    int sum = 0;
    cout << "[";
    for(int i = 0; i < circle_components.size(); i++){
        printf("%d ", circle_components[i]);
        sum += weights[circle_components[i]];
    }
    cout << "]" << endl;;

    circle_components.clear();

    return sum;
}

int solve(){
    int max_cc_sum = 0;
    for(int i = 0; i < N; i++){
        if(!visited_st[i]) DFS_for_stack(i);
    }

    while(!st.empty()){
        int node = st.top();
        st.pop();

        if(!visited_cc[node]){
            DFS_for_CC(node);
            int ret = calc_max_cc();
            if(ret > max_cc_sum) max_cc_sum = ret;
        }
    }


    return max_cc_sum;
}

int main(){
    int cell_id_first = 0;
    int cell_id_second = 0;
    cin >> N >> B;

    for(int i = 1; i <= N; i++){
        cin >> weights[i];
    }

    for(int i = 0; i < B; i++){
        cin >> cell_id_first >> cell_id_second;
        cell_edges[cell_id_first].push_back(cell_id_second);
        cell_edges[cell_id_second].push_back(cell_id_first);
    }

    cout << solve() << endl;

    return 0;
}