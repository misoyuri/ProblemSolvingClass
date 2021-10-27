#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

#define RIGHT 1
#define DOWN 0

int m, n;
int map[301][301]{0, };
int w[301][301]{0, };

bool flag = false;
int ret = 0;

vector<int> path;

void DFS(int i, int j, int k, int l, int c){
    if(k >= m || l >= n) return;

    int area = w[k][l];

    if(i > 0) area -= w[i-1][l];
    if(j > 0) area -= w[k][j-1];
    if(i > 0 && j > 0) area += w[i-1][j-1];

    if(area == 10){
        for(auto val : path){
            if(val == c) return;
        }
        path.push_back(c);
        ret++;
        flag = true;
        // printf("[%d, %d] : [%d, %d]\n", i, j, k, l);
    }else if(area < 10){
        DFS(i, j, k+1, l  , c+1);
        DFS(i, j, k  , l+1, c  );
    }

    return;
}

int main(){
    cin >> m >> n;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> map[i][j];
            if(i == 0 && j == 0) w[i][j] = map[i][j];
            else if(i == 0 && j > 0) w[i][j] = w[i][j-1] + map[i][j];
            else if(j == 0 && i > 0) w[i][j] = w[i-1][j] + map[i][j];
            else{
                w[i][j] = map[i][j] + w[i-1][j] + w[i][j-1] - w[i-1][j-1];
            }
        }
    }
clock_t begin = clock();


    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            path.clear();
            DFS(i, j, i+1, j  , 1);
            DFS(i, j, i  , j+1, 0);
        }
    }
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs << endl;
    cout << ret << endl;
}