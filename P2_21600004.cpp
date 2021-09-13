#include <iostream>
#include <random>

using namespace std;

typedef struct Pair{
    int pNumber = 0;
    long long xPos = 0;
};

Pair *city;

void SWAP(Pair *a, Pair *b){
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

void printCity(Pair *city, int n){
    cout << "-------------------------------------" << endl;
    cout << "\txPose\t\tpNumber" << endl;
    for(int i = 1; i <= n; i++){
        cout << i << "]\t" << city[i].xPos <<"\t\t" << city[i].pNumber << endl;
    }
    cout << "-------------------------------------" << endl;
}

int partition(Pair *city, int left, int right){
    int pivot = left, i = left, j = right+1;

    do{
        do{
            i++;
        } while(city[i].xPos < city[pivot].xPos && i <= right);       
        
        do{
            j--;
        }while(city[j].xPos > city[pivot].xPos && j >= left);

        if(i < j){
            SWAP(&city[i], &city[j]);
        }
    }while(i < j);

    SWAP(&city[left], &city[j]);

    return j;
}

void quickSort(Pair *city, int left, int right){
    if(left < right){
        int pivot = partition(city, left, right);

        quickSort(city, left, pivot-1);
        quickSort(city, pivot+1, right);
    }
}

long long findMaxPeople(Pair *city, int n, int k){
    long long answer = 0;
    long long subAnswer = 0;
    long long possibleRange = 2 * k;
    long long currentRange = 0;
    int smallIdx = 1, largeIdx = 1;
    
    // for(smallIdx = 1, largeIdx = 1; smallIdx <= n; smallIdx++){
    //     subAnswer = 0;
    //     for(largeIdx = smallIdx; largeIdx <= n; largeIdx++){
    //         currentRange = city[largeIdx].xPos - city[smallIdx].xPos;

    //         if(currentRange <= possibleRange) {
    //             subAnswer += city[largeIdx].pNumber;
    //         }
    //         else{
    //             break;
    //         }
    //     }
    //     // largeIdx--;
    //     cout << "[" << city[smallIdx].xPos << " ~ " << city[largeIdx].xPos << "] = " << subAnswer << endl;
    //     if(subAnswer > answer) answer = subAnswer;
    //     subAnswer -= city[largeIdx].pNumber;
    // }

    do{
        while(city[largeIdx].xPos - city[smallIdx].xPos <= possibleRange && largeIdx <= n){
            subAnswer += city[largeIdx].pNumber;
            largeIdx = largeIdx + 1;
        }

        if(subAnswer > answer) answer = subAnswer;
        subAnswer -= city[smallIdx].pNumber;
        smallIdx++;
        if(smallIdx > largeIdx) largeIdx = smallIdx;

    }while(smallIdx <= n);
    

    return answer;
}


int main(){
    int n = 0, k = 0;

    cin >>  n >> k;

    city= new Pair[n+1]; 
    for(int i = 1; i <= n; i++){
        cin >> city[i].pNumber >> city[i].xPos;
    }

    quickSort(city, 1, n);
    // printCity(city, n);



    cout << findMaxPeople(city, n, k) << endl;

}