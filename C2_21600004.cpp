#include <iostream>

using namespace std;

int gN = 0;
int **map;
int **mem;

int subSolve(int x, int y){
    if( x < 0 || x >= gN) return 0;
    if( y < 0 || y >= gN) return 0;

    if(mem[x][y] >= 0) return mem[x][y];

    cout << "[" << x << ", " << y << "]" << endl;

    int ret = 0;
    int diff = 0;
    int subAns1 = subSolve(x+1, y+1);
    int subAns2 = subSolve(x-1, y+1);
    int subAns3 = subSolve(x+1, y-1);
    int subAns4 = subSolve(x-1, y-1);
    
    if(ret < subAns1){
        ret = subAns1;
        diff = map[x][y] - map[x+1][y+1];
    } 
    if(ret < subAns2) {
        ret = subAns2;
        diff = map[x][y] - map[x-1][y+1];
    }

    if(ret < subAns3) {
        ret = subAns3;
        diff = map[x][y] - map[x+1][y-1];
    }

    if(ret < subAns4) {
        ret = subAns4;
        diff = map[x][y] - map[x-1][y-1];
    }
    
    mem[x][y] = ret + diff;
    return mem[x][y];
}

int solve(){
    int ret = 0;
    int subAns = 0;

    for(int i = 0; i < gN; i++){
        for(int j = 0; j < gN; j++){
            if(mem[i][j] == -1){
                subAns = subSolve(i, j);
                if(subAns > ret) ret = subAns;
            }
        }
    }

    return subAns;
}

void initMaps(){
    cin >> gN;

    map = new int*[gN];
    mem = new int*[gN];

    for(int i = 0; i < gN; i++){
        map[i] = new int[gN]{0, };
        mem[i] = new int[gN]{0, };
    }

    for(int i = 0; i < gN; i++){
        for(int j = 0; j < gN; j++){
            cin >> map[i][j];
            mem[i][j] = -1;
        }
    }
}

int main(){
    initMaps();
    cout << solve() << endl;

    return 0;
}