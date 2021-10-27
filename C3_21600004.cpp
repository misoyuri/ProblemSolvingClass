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


vector<int> list[40001];
int dist[4][40001];

int p, q, r, N, M;

void print_list(){
    for(int i = 1; i <= N; i++){
        printf("%-5d", dist[i]);
        cout << endl;
    }
}

void bfs(int dist_idx, int start){
    for(int i = 1; i <= N; i++){
        dist[dist_idx][i] = INF;
    }
    
    CQueue q;

    q.push(start);
    dist[dist_idx][start] = 0;
    
    while(!q.empty()){
        int current_node = q.top();
        q.pop();

        for(size_t i = 0; i < list[current_node].size(); i++){
            int adj_node = list[current_node][i];

            if(dist[dist_idx][adj_node] > dist[dist_idx][current_node] + 1){
                dist[dist_idx][adj_node] = dist[dist_idx][current_node] + 1;
                q.push(adj_node);

            }
        }
    }
}


int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int city1, city2;
    long long answer = 10e16;
    long long subAnswer = 0;
    cin >> p >> q >> r >> N >> M;

    for(int i = 0; i < M; i++){
        cin >> city1 >> city2;
        list[city1].push_back(city2);
        list[city2].push_back(city1);
    }
    
    bfs(0, 1);
    bfs(1, 2);
    bfs(2, N);

    for(int i = 1; i <= N; i++){
        subAnswer = dist[0][i] * p + dist[1][i] * q + dist[2][i] * r;
        // printf("%d * %d + %d * %d + %d * %d = %d\n", dist[0][i], p, dist[1][i], q, dist[2][i], r, subAnswer);
        if(subAnswer < answer) answer = subAnswer;
    }

    cout << answer << endl;
    return 0;

}