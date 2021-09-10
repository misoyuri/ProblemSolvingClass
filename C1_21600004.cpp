#include <iostream>
#include <unistd.h>

using namespace std;

int gN, gK, gF;

int **map;
int *adjMap;

void printMap(){
    for(int i = 1; i <= gN; i++){
        for(int j = 1; j <= gN; j++){
            cout << map[i][j] << " ";
        }    
        cout << endl;
    }

    for(int i =1;i <= gN; i++){
        cout << "["<<i<<"]::"<<adjMap[i]<<endl;
    }
}

int findMaxTeamMember(){
    int number = 0;
    for(int i =1;i <= gN; i++){
        if(adjMap[i] >= gK) number++;
    }

    return number;
}

void eraseNode(int target){
    for(int i = 1; i <= gN; i++){
        if(map[i][target] == 1){
            map[i][target] = 0;
            adjMap[i]--;
        }

        if(map[target][i] == 1){
            map[target][i] = 0;
            adjMap[target]--;
        }
    } 
}

void optimizeMap(){
    bool isNotEnd = true;
    int cnt = 0;
    while(isNotEnd){
        isNotEnd = false;
        for(int i = 1; i <= gN; i++){
            if(0 < adjMap[i] && adjMap[i] < gK){
                eraseNode(i);
                isNotEnd = true;
            }
        }

        // if(cnt == 3){
        //     cout << "isNotEnd::" << isNotEnd <<endl;
        //     printMap();
        //     usleep(500000000);
        
        // }
        // cout << cnt << endl;
    }
}

void initMap(){
    int fellowShip1, fellowShip2;
    cin >> gN >> gK >> gF;

    map = new int*[gN+1];
    adjMap = new int[gN+1]{0, };
    for(int i = 1; i <= gN; i++){
        map[i] = new int[gN + 1]{0, };
    }

    for(int i = 0; i < gF; i++){
        cin >> fellowShip1 >> fellowShip2;
        map[fellowShip1][fellowShip2] = 1;
        map[fellowShip2][fellowShip1] = 1;

        adjMap[fellowShip1]++;
        adjMap[fellowShip2]++;
    }

}

int main(){
    initMap();
    optimizeMap();
    
    // printMap();
    cout << findMaxTeamMember() << endl;
}