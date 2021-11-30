#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

#define BOTH 2
#define PIZZA 1
#define CHINESE -1
#define NOT_DETERMINDED 0

using namespace std;

int N = 0;
pair<int, int> position[50000];
vector<int> building_map[50000];
int brands[50000]{0, };

void print_brands(){
    int pizza_buildings = 0;
    int chinese_buildings = 0;
    printf("pizza: ");
    for(int i = 0; i < N; i++){
        if(brands[i] == PIZZA){
            pizza_buildings++;
            printf("%d ", i);
        }else{
            chinese_buildings++;
        }
    }

    printf("\nchine: ");
    for(int i = 0; i < N; i++){
        if(brands[i] == CHINESE){
            printf("%d ", i);
        }
    }

    cout << endl << "sol:: " << min(pizza_buildings, chinese_buildings) << endl;

}

void print_answer(){
    int pizza_buildings = 0;
    int chinese_buildings = 0;
    for(int i = 0; i < N; i++){
        if(brands[i] == PIZZA){
            pizza_buildings++;
        }else{
            chinese_buildings++;
        }
    }

    cout << min(pizza_buildings, chinese_buildings) << endl;


}

int define_brands(int init_building){
    int c=0, p=0;
    queue<int> q;

    brands[init_building] = PIZZA;
    p++;
    q.push(init_building);

    while(!q.empty()){
        int current_building = q.front();
        q.pop();

        for(int i = 0; i < building_map[current_building].size(); i++){
            int next_building = building_map[current_building][i];
            if(brands[next_building] == NOT_DETERMINDED){
                if(brands[current_building] == PIZZA){
                    brands[next_building] = CHINESE;
                    c++;
                }else{
                    brands[next_building] = PIZZA;
                    p++;
                }
                q.push(next_building);

            }
        }
    }
    
    return min(p, c);
}

void solve(){
    int min = 0;
    for(int i = 0; i < N; i++){
        if(brands[i] == NOT_DETERMINDED){
            int c = 0, p = 0;
            min += define_brands(i);
        }
    }
    // cout << "min::" <<min <<endl;
    cout << min <<endl;
}

void define_building_map(){
    int distance = 0;
    int distance_x = 0;
    int distance_y = 0;
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            distance_x = position[j].first - position[i].first;
            distance_y = position[j].second - position[i].second;

            distance = distance_x * distance_x + distance_y * distance_y;

            if(distance <= 25){
                building_map[i].push_back(j);
                building_map[j].push_back(i);
            }

            if(distance_x > 5 && abs(distance_y) > 5) break;
        }
    }
}


int main(){
    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> position[i].first >> position[i].second;
    }
    
    sort(position, position + N);

    define_building_map();
    solve();
    // print_brands();
    // print_answer();
    return 0;
}