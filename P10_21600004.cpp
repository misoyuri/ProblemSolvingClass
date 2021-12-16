#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#define MAX_SIZE 1010

using namespace std;


vector<vector<pair<int, string>>> graph(26);

vector<string> sequence;
int in_degree[26]{0, };
int out_degree[26]{0, };
int start_point = -1;
int N = 0;

bool comp(pair<int, string> a, pair<int, string> b){
    return a.second > b.second;
}

void DFS(int start){
    for(int i = graph[start].size() - 1; i >= 0; i--){
        pair<int, string> current_word = graph[start][i];

        if(in_degree[current_word.first] > 0){
            graph[start].pop_back();
            in_degree[current_word.first]--;

            DFS(current_word.first);
            sequence.push_back(current_word.second);
        }
    }
}

bool is_circuit_or_trail(){
    int candidtate_start_point = 0;
    int candidtate_final_point = 0;

    int circuit_start_point = -1;
    int trail_start_point = -1;

    for(int i = 0; i < 26; i++){
        if(in_degree[i] == 0 && out_degree[i] == 0) continue;
            
        if(in_degree[i] == out_degree[i] + 1){
            // end point of euler trail.
            candidtate_final_point++;

        }else if(in_degree[i] + 1 == out_degree[i]){
            // start point of euler trail.
            candidtate_start_point++;
            trail_start_point = i;
            
        }else if(in_degree[i] == out_degree[i]){
            if(circuit_start_point == -1) circuit_start_point = i;

        }else{
            return false;
        }
    }

    if(candidtate_start_point == 1 && candidtate_final_point == 1){
        start_point = trail_start_point;
        return true;

    }else if(candidtate_start_point == 0 && candidtate_final_point == 0){
        start_point = circuit_start_point;
        return true;
    }

    return false;
}

int main(){
    string word;

    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> word;

        in_degree[word.back() - 'a']++;
        out_degree[word.front() - 'a']++;

        graph[word.front() - 'a'].push_back({word.back() - 'a', word});
    }





    if(!is_circuit_or_trail()){
        cout << 0 << endl;
        return 0;
    }

    for(int i = 0; i < 26; i++){
        sort(graph[i].begin(), graph[i].end(), comp);
    }

    DFS(start_point);

    if(sequence.size() != N) {
        cout << 0 << endl;
        return 0;
    }

    for(int i = 0; i < sequence.size(); i++){
        cout << sequence[i] << endl;
    }
    
    return 0;
}

