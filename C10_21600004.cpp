#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

#define BOTH 2
#define PIZZA 1
#define CHINESE -1
#define NOT_YET 0

using namespace std;

int N = 0;
pair<int, int> position[50000];
int brand[50000]{0, };

int pizza_combinations = 0;
int chinese_combinations = 0;

int min_combinations = 50001;

vector<int> vPizza;
vector<int> vChinese;

int define_brand(int idx){
    int distance_x = 0;
    int distance_y = 0;
    int distance = 0;
    
    for(int i = 0; i < idx; i++){
        distance_x = position[i].first - position[idx].first;
        distance_y = position[i].second - position[idx].second;
        
        distance = distance_x * distance_x + distance_y * distance_y;

        if(distance <= 25){
            if(brand[i] == PIZZA) return CHINESE;
            if(brand[i] == CHINESE) return PIZZA;
        } 
    }

    return BOTH;
}

void dfs(int idx){
    if(idx == 0){
        brand[idx] = PIZZA;
        // vPizza.push_back(idx);
        
        dfs(idx+1);

        // vPizza.pop_back();
        return;
    }

    if(idx == N){
        // cout << "pizza[" << vPizza.size() << "]";
        // for(auto val : vPizza) printf("%d ", val);
        // cout << endl << "chine[" << vChinese.size() << "]";
        // for(auto val : vChinese) printf("%d ", val);
        // cout << endl << "-------------------------" << endl;


        min_combinations = min(min_combinations, min(pizza_combinations, chinese_combinations));
        if(pizza_combinations == 0 || chinese_combinations == 0){
            cout << 0 << endl;
            exit(0);
        }
        return;
    }

    int possible_brand = define_brand(idx);

    if(possible_brand == PIZZA){
        brand[idx] = PIZZA;
        pizza_combinations++;
        // vPizza.push_back(idx);
        
        dfs(idx+1);

        // vPizza.pop_back();
        pizza_combinations--;
        brand[idx] = NOT_YET;

    }else if(possible_brand == CHINESE){
        brand[idx] = CHINESE;
        chinese_combinations++;
        // vChinese.push_back(idx);

        dfs(idx+1);
        
        // vChinese.pop_back();
        chinese_combinations--;
        brand[idx] = NOT_YET;
    }else{
        brand[idx] = PIZZA;
        pizza_combinations++;
        // vPizza.push_back(idx);

        dfs(idx+1);
        
        // vPizza.pop_back();
        pizza_combinations--;
        brand[idx] = NOT_YET;

        ////////// C //////////
        brand[idx] = CHINESE;
        chinese_combinations++;
        // vChinese.push_back(idx);

        dfs(idx+1);
        
        // vChinese.pop_back();
        chinese_combinations--;
        brand[idx] = NOT_YET;
    }

    return;
}


int main(){
    cin >> N;

    for(int i = 0; i < N; i++){
        cin >> position[i].first >> position[i].second;
    }

    // sort(position, position + N);

    dfs(0);

    cout << min_combinations << endl;
    return 0;
}