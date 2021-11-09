#include <iostream>

using namespace std;


void SWAP(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *data, int left, int right){
    int pivot = left, i = left, j = right+1;

    do{
        do{
            i++;
        } while(data[i] < data[pivot] && i <= right);       
        
        do{
            j--;
        }while(data[j] > data[pivot] && j >= left);

        if(i < j){
            SWAP(&data[i], &data[j]);
        }
    }while(i < j);

    SWAP(&data[left], &data[j]);

    return j;
}

void quick_sort(int *data, int left, int right){
    if(left < right){
        int pivot = partition(data, left, right);

        quick_sort(data, left, pivot-1);
        quick_sort(data, pivot+1, right);
    }
}

int solve(int *tasks, int n, int d, int m){
    int min_rent = 1;
    int max_rent = m;
    int current_rent = (m + 1) / 2;

    int proper_rent = current_rent;

    while(min_rent <= max_rent){
        current_rent = (min_rent + max_rent) / 2;

        bool possible = true;
        int task_days = 0;
        int task_idx = 0;
        while(task_idx < m){
            int i = 0;
            task_days++;
            
            if(task_days > n){
                possible = false;
                break;
            }

            while(i < current_rent){
                if(tasks[task_idx] <= task_days && task_days <= tasks[task_idx] + d){
                    task_idx++;
                }else{
                    break;
                }
                i++;
            }
        }

        if(possible){
            proper_rent = current_rent;
            max_rent = current_rent - 1;
        }else{
            min_rent = current_rent + 1;
        }
    }

    return proper_rent;
}

int main(){
    int tasks[100001]{0, };
    int n = 0, d = 0, m = 0;
    cin >> n >> d >> m;

    for(int i = 0; i < m; i++){
        scanf("%d", &tasks[i]);
    }

    quick_sort(tasks, 0, m-1);

    cout << solve(tasks, n, d, m) << endl;
}