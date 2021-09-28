#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 9999999

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


vector<int> list[40001];
int dist[40001];
int parent[40001]{0, };

int p, q, r, N, M;

void init_dist(){
    for(int i = 1; i <= N; i++){
        dist[i] = INF;
    }
}

void bfs_without_parent(int start){
    init_dist();
    queue<int> q;
    
    int cur_node = 0;

    q.push(start);
    dist[start] = 0;

    while(!q.empty()){
        cur_node = q.front();
        q.pop();
        
        for(int i=0; i < list[cur_node].size(); i++){
            if(dist[cur_node] + 1 < dist[list[cur_node][i]]){
                dist[list[cur_node][i]] = dist[cur_node] + 1;
                q.push(list[cur_node][i]);
            }
        }
    }

}

void bfs_with_parent(){
    init_dist();
    queue<int> q;
    
    int cur_node = 0;

    q.push(1);
    dist[1] = 0;

    while(!q.empty()){
        cur_node = q.front();
        q.pop();
        
        for(int i=0; i < list[cur_node].size(); i++){
            if(dist[cur_node] + 1 < dist[list[cur_node][i]]){
                dist[list[cur_node][i]] = dist[cur_node] + 1;
                parent[list[cur_node][i]] = cur_node;
                q.push(list[cur_node][i]);
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

    bfs_with_parent();

    int dist_12 = dist[2];
    int aaa = 0;

    int offset = p * dist_12 + q * aaa;
    dist_12--; aaa++;

    bfs_without_parent(N);
    answer = r * dist[2] + offset;

    // for(int i = 1; i <= N; i++){
    //     cout << "[" << i << "]->" << parent[i] << " :: " << dist[i] <<endl; 
    // }

    int cur_node = parent[2];

    while(1){
        offset = p * dist_12 + q * aaa;
        // cout << "[" << cur_node << "] " << r * dist[cur_node] << " + " << p*dist_12 << " + " << aaa * q << endl;
        dist_12--; aaa++;
        subAnswer = r * dist[cur_node] + offset ;


        if(answer > subAnswer) answer = subAnswer;
        if(cur_node == 1) break;
        cur_node = parent[cur_node];
    }

    cout << answer << endl;
    return 0;

}