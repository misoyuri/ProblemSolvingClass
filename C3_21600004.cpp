#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define INF 9999999

vector<int> list[40001];
int dist[40001];
int parent[40001]{0, };

int p, q, r, N, M;

void init_dist(){
    for(int i = 1; i <= N; i++){
        dist[i] = INF;
    }
}


int dijkstra_without_parent(int start){
    priority_queue<pair<int, int>> q;
    int dist_sofar = 0;
    int cur_node = 0;
    int cur_cost = 0;

    q.push({0, start});
    dist[start] = 0;

    // q.push({start, 0});
    // dist[start] = 0;

    while(!q.empty()){
        dist_sofar = -q.top().first;
        cur_node = q.top().second;
        
        q.pop();

        if(dist[cur_node] < dist_sofar) continue;

        for(int i=0; i < list[cur_node].size(); i++){
            cur_cost = dist_sofar + 1;

            if(dist_sofar < dist[list[cur_node][i]]){
                dist[list[cur_node][i]] = cur_cost;
                q.push({-cur_cost, list[cur_node][i]});
                // q.push({list[cur_node][i], -cur_cost});
            }
        }
    }
    
    return dist[N];

}

void dijkstra_with_parent(){
    priority_queue<pair<int, int>> q;
    int dist_sofar = 0;
    int cur_node = 0;
    int cur_cost = 0;

    q.push({1, 0});
    dist[1] = 0;

    while(!q.empty()){
        cur_node = q.top().first;
        dist_sofar = q.top().second;
        
        q.pop();

        if(dist[cur_node] < dist_sofar) continue;

        for(int i=0; i < list[cur_node].size(); i++){
            cur_cost = dist_sofar + 1;

            if(dist_sofar < dist[list[cur_node][i]]){
                dist[list[cur_node][i]] = cur_cost;
                parent[list[cur_node][i]] = cur_node;
                q.push({list[cur_node][i], cur_cost});
            }
        }
    }

}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int city1, city2;
    int answer = 0;
    int subAnswer = 0;
    cin >> p >> q >> r >> N >> M;

    for(int i = 0; i < M; i++){
        cin >> city1 >> city2;
        list[city1].push_back(city2);
        list[city2].push_back(city1);
    }

    init_dist();
    dijkstra_with_parent();

    int dist_12 = dist[2];
    int offset = dist_12 * p;

    init_dist();
    dijkstra_without_parent(N);

    answer = offset + dist[2] * r;
    
    int cur_node = parent[2];
    while(1){
        offset -= p - q;
        subAnswer = offset + r * dist[cur_node];
        if(answer > subAnswer) answer = subAnswer;
        if(cur_node == 1) break;
        cur_node = parent[cur_node];
    }

    cout << answer << endl;
    return 0;

}