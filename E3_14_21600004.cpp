#include <iostream>

using namespace std;

long long *note;

long long rec(int x){
    if(x < 1 ) return 0;
    if(x == 1) return 1;
    if(x == 2) return 1;
    if(x == 3) return 2;
    if(x == 4) return 4;

    if(note[x-4] == 0) note[x-4] = rec(x-4);
    if(note[x-3] == 0) note[x-3] = rec(x-3);
    if(note[x-1] == 0) note[x-1] = rec(x-1);
    
    return note[x-1] + note[x-3] + note[x-4];
}

int main(){
    int n =0;
    
    cin >> n;
    note = new long long[n+1]{0, };
    cout << rec(n-1) + rec(n-3) + rec(n-4) << endl;


}