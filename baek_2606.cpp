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

void bfs_from_N(int start){
    init_dist();
    bool *visited = new bool[N+1]{false, };
    
    CQueue q;

    q.push(start);
    visited[start] = true;
    dist[start] = 0;
    
    while(!q.empty()){
        int current_node = q.top();
        q.pop();

        for(int i = 0; i < list[current_node].size(); i++){
            int adj_node = list[current_node][i];

            if(!visited[adj_node]){
                visited[adj_node] = true;
                q.push(adj_node);
                parent[adj_node] = parent[current_node];
                if(dist[adj_node] > dist[current_node] + 1)
                    dist[adj_node] = dist[current_node] + 1;
            }
        }
    }
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
}