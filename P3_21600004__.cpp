#include <iostream>

using namespace std;

void SWAP(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *wArray, int left, int right){
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

void quickSort(int *wArray, int left, int right){
    if(left < right){
        int pivot = partition(wArray, left, right);

        quickSort(wArray, left, pivot-1);
        quickSort(wArray, pivot+1, right);
    }
}

int solve(int N, int *wArray, int wSize, bool *isUsed){
    int ret = 0;

    for(int i = 0; i < wSize; i++){
        if(isUsed[i]) continue;

        int remainder = N - wArray[i];
        isUsed[i] = true;

        for(int j = i+1; j < wSize; j++){
            if(isUsed[j]) continue;

            if(remainder - wArray[j] >= 0){
                isUsed[j] = true;
                break;
            }
        }

        ret++;
    }

    return ret;
}


// prioriy queue, binary search;
int main(){
    int N = 0;
    int *wArray = new int[100001]{0, };  
    bool *isUsed = new bool[100001]{false, };
    int wSize = -1;
    cin >> N;

    if(N > 100000) N = 100000;

    do{
        wSize++;
        cin >> wArray[wSize];
    }while(getc(stdin) == ' ');

    quickSort(wArray, 0, wSize-1); 

    // cout << "sol::" << solve(N, wArray, wSize, isUsed) << endl;

    cout << solve(N, wArray, wSize, isUsed) << endl;

    // for(int i = 0; i < wSize; i++)
    //     cout << i << "::" << wArray[i] << endl;

    return 0;
}