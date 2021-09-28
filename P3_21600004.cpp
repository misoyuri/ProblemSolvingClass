#include <iostream>
#include <algorithm>

using namespace std;

int weights[1000001]{0, };

int weights_size = 0;
int M = 0;

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
        } while(weights[i] > weights[pivot] && i <= right);       
        
        do{
            j--;
        }while(weights[j] < weights[pivot] && j >= left);

        if(i < j){
            SWAP(&weights[i], &weights[j]);
        }
    }while(i < j);

    SWAP(&weights[left], &weights[j]);

    return j;
}

void quick_sort(int left, int right){
    if(left < right){
        int pivot = partition(left, right);

        quick_sort(left, pivot-1);
        quick_sort(pivot+1, right);
    }
}
int main(){
    int data = 0;
    int answer = 0;
    scanf("%d", &M);
    
    while(cin >> weights[weights_size]){
        weights_size++;
    }

    quick_sort(0, weights_size); 

    int rear = weights_size - 1;

    for(int front = 0; front <= rear; front++){
        answer++;

        if(weights[front] + weights[rear] <= M){
            rear--;
        }

    }

    cout << answer;
    return 0;
}