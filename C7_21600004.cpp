#include <iostream>
#include <vector>
#define INTMAX 2147483647

using namespace std;
int n = 0;
int m = 0;

int max_level = 0;

vector<int> day1;
vector<int> day2;
pair<int, int> pairs[100001];

bool is_valid(int level_, bool flag){
    if(flag){
        for(int i = 0; i <= level_; i++){
            if(day1[i] == pairs[level_].second) return false;
            if(day2[i] == pairs[level_].first) return false;
        }
    }else{
        for(int i = 0; i <= level_; i++){
            if(day1[i] == pairs[level_].first) return false;
            if(day2[i] == pairs[level_].second) return false;
        }
    }
    

    return true;
}

void solve(int level_){
    if(level_ >= m) return;



    // if(level_ > 0){
    //     cout << "level::" << level_ + 1 << endl;
    //     cout << "Day1:: ";
    //     for(int i = 0; i < level_; i++){
    //         printf("%d ", day1[i]);
    //     }
    //     printf("\nDay2:: ");

    //     for(int i = 0; i < level_; i++){
    //         printf("%d ", day2[i]);
    //     }
    //     printf("\n---------------------------\n");
    // }

    max_level = max(level_, max_level);

    // first trial
    day1.push_back(pairs[level_].first);
    day2.push_back(pairs[level_].second);

    // check valid
    if(is_valid(level_, true)) solve(level_ + 1);
    day1.pop_back();
    day2.pop_back();
    
    // second trial
    day1.push_back(pairs[level_].second);
    day2.push_back(pairs[level_].first);
    
    if(is_valid(level_, false)) solve(level_ + 1);
    day1.pop_back();
    day2.pop_back();
    
    return;
}

int main(){
    cin >> n;
    cin >> m;
    
    for(int i = 0; i < m; i++){
        cin >> pairs[i].first >> pairs[i].second;
    }

    solve(0);

    cout << max_level + 1 << endl;

}


    // if(level_ > 0 && max_level < level_ + 1){
    //         cout << "level::" << level_ << endl;
    //     for(int i = 0; i < level_; i++){
    //         printf("%d ", day1[i]);
    //     }
    //     printf("\n---------------------------\n");

    //     for(int i = 0; i < level_; i++){
    //         printf("%d ", day2[i]);
    //     }
    //     printf("\n---------------------------\n");
    // }