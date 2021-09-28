#include <iostream>
#include <algorithm>
using namespace std;

int wArray[1000000];
bool is_used[1000000]{false, };
int wSize = 0;

void SWAP(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int left, int right){
    int pivot = left, i = left, j = right+1;

    do{
        do{
            i++;
        } while(wArray[i] > wArray[pivot] && i <= right);       
        
        do{
            j--;
        }while(wArray[j] < wArray[pivot] && j >= left);

        if(i < j){
            SWAP(&wArray[i], &wArray[j]);
        }
    }while(i < j);

    SWAP(&wArray[left], &wArray[j]);

    return j;
}

void quick_sort(int left, int right){
    if(left < right){
        int pivot = partition(left, right);

        quick_sort(left, pivot-1);
        quick_sort(pivot+1, right);
    }
}

bool comp(int a, int b){
    return a > b;
}

void print_wArray(){
    for(int i = 0; i < wSize; i++){
        cout << "[" << wArray[i] << "]";
    }
    cout << endl;
}

int solve(int M){
    int answer = 0;
    int remainder = 0;

    for(int i = 0; i < wSize; i++){
        if(is_used[i] == true) continue;
        for(int j = i+1; j < wSize; j++){
            if(is_used[j] == true) continue;
            
            if(wArray[j] + wArray[i] <= M){
                is_used[j] = true;
                break;
            }
        }
        answer++;
    }
    return answer;
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int M = 0;

    int data = 0;
    cin >> M;

    while(scanf("%d", &data) != EOF){
        wSize++;
        wArray[wSize] = data;
        // isUsed[wSize] = false;
    }
    // cout << "eee::" << wArray[wSie] << endl;
    // sort(wArray, wArray+ wSize, comp);

    quick_sort(0, wSize); 
    // print_wArray();
    cout << solve(M);

    return 0;
}