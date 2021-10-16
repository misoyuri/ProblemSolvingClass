#include <iostream>

using namespace std;

int pole[100001]{0, };

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
        } while(pole[i] < pole[pivot] && i <= right);       
        
        do{
            j--;
        }while(pole[j] > pole[pivot] && j >= left);

        if(i < j){
            SWAP(&pole[i], &pole[j]);
        }
    }while(i < j);

    SWAP(&pole[left], &pole[j]);

    return j;
}

void quick_sort(int left, int right){
    if(left < right){
        int pivot = partition(left, right);

        quick_sort(left, pivot-1);
        quick_sort(pivot+1, right);
    }
}

int solve(int n, int k){
    int min_dist = 1;
    int max_dist = pole[n-1] - pole[0];
    int cur_dist = 0;

    int cnt = 0;
    int ret = 0;

    while(min_dist <= max_dist){
        int idx_prev_seleted = 0;
        cur_dist = (max_dist + min_dist) / 2;
        cnt = 1;
        for(int i = 1; i < n; i++){
            if(pole[i] - pole[idx_prev_seleted] >= cur_dist){
                cnt++;
                idx_prev_seleted = i;
            }
        }

        if(cnt >= k){
            if(ret < cur_dist) ret = cur_dist;
            min_dist = cur_dist + 1;
        }else{
            max_dist = cur_dist - 1;
        }
    }

    return ret;
}

int main(){
    int n = 0, k = 0;
    cin >> n >> k;

    for(int i = 0; i < n; i++){
        scanf("%d", &pole[i]);
    }

    quick_sort(0, n-1);

    cout << solve(n, k) << endl;
}