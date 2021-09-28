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


vector<int> *list;
int *dist;
int *parent;

int p, q, r, N, M;

void init_dist(){
    for(int i = 1; i <= N; i++){
        dist[i] = INF;
    }
}

void init_parent(){
    for(int i = 1; i <= N; i++){
        parent[i] = -1;
    }
}

void print_list(){
    for(int i = 1; i <= N; i++){
        cout << "[" << i << "]->" << parent[i] << " :: " << dist[i] <<endl; 
    }
}

void bfs_from_N(){
    init_dist();
    
    CQueue q;

    q.push(N);
    dist[N] = 0;
    
    while(!q.empty()){
        int current_node = q.top();
        q.pop();

        for(size_t i = 0; i < list[current_node].size(); i++){
            int adj_node = list[current_node][i];

            if(dist[adj_node] > dist[current_node] + 1){
                dist[adj_node] = dist[current_node] + 1;
                q.push(adj_node);

            }
        }
    }
}

int bfs_how_far_2_from_1(){
    init_dist();
    init_parent();
    CQueue q;

    q.push(1);
    dist[1] = 0;
    
    while(!q.empty()){
        int current_node = q.top();
        q.pop();

        for(size_t i = 0; i < list[current_node].size(); i++){
            int adj_node = list[current_node][i];

            if(dist[adj_node] > dist[current_node] + 1){
                dist[adj_node] = dist[current_node] + 1;
                parent[adj_node] = current_node;
                q.push(adj_node);
            }
        }
    }

    return dist[2];
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int city1, city2;
    long long answer = 10e16;
    long long subAnswer = 0;
    cin >> p >> q >> r >> N >> M;

    list = new vector<int>[N+1];
    dist = new int[N+1];
    parent = new int[N+1];

    for(int i = 0; i < M; i++){
        cin >> city1 >> city2;
        list[city1].push_back(city2);
        list[city2].push_back(city1);
    }


    long long dist_from_1 = bfs_how_far_2_from_1();
    long long dist_from_2 = 0;
    // cout << "bfs_how_far_2_from_1s() out" << endl;
    // print_list();
    
    bfs_from_N();
    // cout << "bfs_from_N() out" << endl;
    long long offset = p * dist_from_1 + q * dist_from_2;
    int cur_node = 0;
    parent[0] = 2;
    do{
        cur_node = parent[cur_node];
        // cout << "cur node is " << cur_node <<endl; 
        offset = p * dist_from_1 + q * dist_from_2;
        subAnswer = r * dist[cur_node] + offset;
        dist_from_1--; dist_from_2++;

        if(subAnswer < answer) answer = subAnswer;
    }while(cur_node != 1);

    cout << answer << endl;
    return 0;

}