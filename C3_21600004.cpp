#include <iostream>
#include <vector>

using namespace std;

#define INF 2147483646

struct CQueue{
    int front = 0, rear = 0;
    int space[40001];
    int queue_size = 40001;
    
    bool empty(){
        return front == rear;
    }

    void push(int node){
        space[rear] = node;
        rear = (rear+1)%queue_size;
    }
    
    void pop(){
        space[front] = 0;
        front = (front+ 1)%queue_size;
    }

    int top(){
        return space[front];
    }
};


vector<int> list[40010];
int dist[40010];
int parent[40010]{0, };

int p, q, r, N, M;

void init_dist(){
    for(int i = 1; i <= N; i++){
        dist[i] = INF;
    }
}

void print_list(){
    for(int i = 1; i <= N; i++){
        cout << "[" << i << "]->" << parent[i] << " :: " << dist[i] <<endl; 
    }
}

void bfs_from_N(){
    init_dist();
    bool *visited = new bool[N+1]{false, };
    
    CQueue q;

    q.push(N);
    visited[N] = true;
    dist[N] = 0;
    
    while(!q.empty()){
        int current_node = q.top();
        q.pop();

        for(int i = 0; i < list[current_node].size(); i++){
            int adj_node = list[current_node][i];

            // if(!visited[adj_node]){
            //     visited[adj_node] = true;
                if(dist[adj_node] > dist[current_node] + 1){
                    dist[adj_node] = dist[current_node] + 1;
                    q.push(adj_node);

            }
        }
    }
}

int bfs_how_far_2_from_1(){
    init_dist();
    bool *visited = new bool[N+1]{false, };
    
    CQueue q;

    // visited[1] = true;
    q.push(1);
    dist[1] = 0;
    
    while(!q.empty()){
        int current_node = q.top();
        q.pop();

        if(current_node == 2) return dist[2];

        for(int i = 0; i < list[current_node].size(); i++){
            int adj_node = list[current_node][i];

            // if(!visited[adj_node]){
                // visited[adj_node] = true;
            if(dist[adj_node] > dist[current_node] + 1){
                q.push(adj_node);
                parent[adj_node] = current_node;
                dist[adj_node] = dist[current_node] + 1;
            }
        }
    }

    return -1;
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int city1, city2;
    long long answer = 10e16;
    int subAnswer = 0;
    cin >> p >> q >> r >> N >> M;

    for(int i = 0; i < M; i++){
        cin >> city1 >> city2;
        list[city1].push_back(city2);
        list[city2].push_back(city1);
    }


    int dist_from_1 = bfs_how_far_2_from_1();
    int dist_from_2 = 0;
    
    // cout << "dist12::" << dist_from_1 << endl;

    bfs_from_N();



    long long offset = p * dist_from_1 + q * dist_from_2;
    int cur_node = 0;
    parent[0] = 2;

    do{
        cur_node = parent[cur_node];
        offset = p * dist_from_1 + q * dist_from_2;
        subAnswer = r * dist[cur_node] + offset;
        cout << "cur::" << cur_node << " - " << subAnswer << endl;
        cout << "\t" << p * dist_from_1 << " " << q * dist_from_2 << " " << r * dist[cur_node] <<endl;
        dist_from_1--; dist_from_2++;

        if(subAnswer < answer) answer = subAnswer;
    }while(cur_node != 1);

    cout << answer << endl;
    return 0;

}