#include <iostream>
#include <algorithm>

using namespace std;

struct Pair{
    long long position = 0;
    long long velocity = 0;
    long long final_pose = 0;
};

Pair person[100001]{{0, 0}, };
int n = 0, t = 0;

bool comp(Pair a, Pair b){
    return a.position < b.position;
}

int solve_(){
    int groups = 1;

    for(int i = n-1; i >= 1; i--){
        if(person[i-1].final_pose <= person[i].final_pose){
            groups++;
        }else{
           person[i-1].final_pose = person[i].final_pose; 
        }
    }

    return groups;
}

int main(){
    cin >> n >> t;

    for(int i = 0; i < n; i++){
        cin >> person[i].position >> person[i].velocity;
        person[i].final_pose = person[i].position + person[i].velocity * t;
    }

    sort(person, person + n, comp);
    cout << solve_() << endl;
}