#include <iostream>

using namespace std;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int gN = 0;
int **map;
int **mem;

bool isAccessible(int x, int y){
    if(0 > x || x >= gN) return false;
    if(0 > y || y >= gN) return false;

    return true;
}

int subSolve(int i, int j){
    int ret = 0;
    int subAns = 0;
    int tempAns = 0;

    if(mem[i][j] == -1){
        if(isAccessible(i+1, j) && map[i][j] > map[i+1][j]){
            tempAns = subSolve(i+1, j) + map[i][j] - map[i+1][j];
            subAns = MAX(tempAns, subAns);
        }

        if(isAccessible(i-1, j) && map[i][j] > map[i-1][j]){
            tempAns = subSolve(i-1, j) + map[i][j] - map[i-1][j];
            subAns = MAX(tempAns, subAns);
        }

        if(isAccessible(i, j+1) && map[i][j] > map[i][j+1]){
            tempAns = subSolve(i, j+1) + map[i][j] - map[i][j+1];
            subAns = MAX(tempAns, subAns);
        }

        if(isAccessible(i, j-1) && map[i][j] > map[i][j-1]){
            tempAns = subSolve(i, j-1) + map[i][j] - map[i][j-1];
            subAns = MAX(tempAns, subAns);
        }

        mem[i][j] = subAns;
        ret = MAX(ret, subAns);
    }else{
        ret = mem[i][j];
    }

    
    // cout << "[" << i << ", "<< j <<"]::" << ret << endl;
    return ret;
}


int solve(){
    int ret = 0;
    int subAns = 0;
    int tempAns = 0;
    for(int i = 0; i < gN; i++){
        for(int j = 0; j < gN; j++){
            tempAns = subAns = 0;
            if(mem[i][j] == -1){
                if(isAccessible(i+1, j) && map[i][j] > map[i+1][j]){
                    tempAns = subSolve(i+1, j) + map[i][j] - map[i+1][j];
                    subAns = MAX(tempAns, subAns);
                }

                if(isAccessible(i-1, j) && map[i][j] > map[i-1][j]){
                    tempAns = subSolve(i-1, j) + map[i][j] - map[i-1][j];
                    subAns = MAX(tempAns, subAns);
                }

                if(isAccessible(i, j+1) && map[i][j] > map[i][j+1]){
                    tempAns = subSolve(i, j+1) + map[i][j] - map[i][j+1];
                    subAns = MAX(tempAns, subAns);
                }

                if(isAccessible(i, j-1) && map[i][j] > map[i][j-1]){
                    tempAns = subSolve(i, j-1) + map[i][j] - map[i][j-1];
                    subAns = MAX(tempAns, subAns);
                }

                mem[i][j] = subAns;
                ret = MAX(ret, subAns);
            }
        }
    }

    return ret;
}

void printMaps(){
    for(int i = 0; i < gN; i++){
        for(int j = 0; j < gN; j++){
            cout << mem[i][j] << " ";
        }
        cout << endl;
    }
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
    // printMaps();
    return 0;
}