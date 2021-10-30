#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<int> people;
    int temp = 0;

    for(int i = 0; i < 2*n; i++){
        cin >> temp;
        people.push_back(temp);
    }

    sort(people.begin(), people.end());

    int sum = 99999999;
    for(int start = 0, end = 2*n-1; start < end; start++, end--){
        temp = people[start] + people[end];
        sum = min(sum, temp);
    }
    cout << sum << endl;
    return 0;
}