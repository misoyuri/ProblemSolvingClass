#include <iostream>

using namespace std;

struct Pair{
    long long position = 0;
    long long velocity = 0;
    int group = 1;
    int presenter = 0;
};

Pair person[100001]{{0, 0}, };
int n = 0, t = 0;

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
        } while(data[i].position < data[pivot].position && i <= right);       
        
        do{
            j--;
        }while(data[j].position > data[pivot].position && j >= left);

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


void print_log(int t_){
        cout << "---------" << t_ << "----------" << endl;
    for(int i = 0; i < n; i++){
        printf("[%d]pose: %3lld | velocity: %3lld | gorupd: %3d\n", i, person[i].position, person[i].velocity, person[i].group);
    }
}

int solve(){
    int max_num_groupd = 1;
    long long target_pos = 0;
    
    for(int t_ = 0; t_ < t; t_++){
        for(int i = n-1; i >= 0; i--){
            if(person[i].group == 0) continue;

            if(i < n-1 ){ 
                target_pos = person[i+1].group == 0 ? person[person[i+1].presenter].position : person[i+1].position;
                if(target_pos - person[i].position <= person[i].velocity ){
                    person[i+1].group += person[i].group;
                    person[i].group = 0;
                    person[i].presenter = i+1;
                    max_num_groupd = max(max_num_groupd, person[i+1].group);
                }else{
                    person[i].position += person[i].velocity;
                }    
            }else{
                person[i].position += person[i].velocity;
            }

        }

        // print_log(t_);
        if(max_num_groupd == n) return max_num_groupd;
    }

    return max_num_groupd;
}

int main(){
    cin >> n >> t;
    

    for(int i = 0; i < n; i++){
        cin >> person[i].position >> person[i].velocity;
        person[i].presenter = i;
    }

    quick_sort(person, 0, n-1);
    
    cout << solve() << endl;
}