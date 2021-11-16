#include <iostream>
#include <cmath>
using namespace std;

struct Pair{
    int x = 0;
    int y = 0;
};

Pair village[10001]{{0, 0}, };

int n = 0;
int d = 0;

void SWAP(Pair *a, Pair *b){
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Pair *data, int left, int right){
    int pivot = left, i = left, j = right+1;

    do{
        do{
            i++;
        } while(data[i].x < data[pivot].x && i <= right);       
        
        do{
            j--;
        }while(data[j].x > data[pivot].x && j >= left);

        if(i < j){
            SWAP(&data[i], &data[j]);
        }
    }while(i < j);

    SWAP(&data[left], &data[j]);

    return j;
}

void quick_sort(Pair *data, int left, int right){
    if(left < right){
        int pivot = partition(data, left, right);

        quick_sort(data, left, pivot-1);
        quick_sort(data, pivot+1, right);
    }
}

int solve(){
    int num_of_wells = 1;
    double pos_well = 0.0;

    double d2 = d * d;
    double x = 0.0, y = 0.0;
    double abs_x = 0;

    pos_well = sqrt(d2 - village[0].y * village[0].y) + village[0].x;

    for(int i = 1; i < n; i++){
        x = village[i].x;
        y = village[i].y;

        abs_x = sqrt(d2 - y*y);

        double rng1 = -1 * abs_x + x;
        double rng2 =  abs_x + x;
        
        if(pos_well < rng1){
            num_of_wells++;
            pos_well = rng2;
        }else if(rng2 < pos_well){
            pos_well = rng2;
        }
    }

    return num_of_wells;
}


int main(){
    cin >> n >> d;

    for(int i = 0; i < n; i++){
        cin >> village[i].x >> village[i].y;
    }

    quick_sort(village, 0, n - 1);

    std::cout << solve() << std::endl;

    return 0;
}  