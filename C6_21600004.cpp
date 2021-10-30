#include <iostream>

using namespace std;

#define DEBUG_MODE false

int deck[50001]{0, };

int lis_deck[50001]{0, 1};
int lis_size[50001]{0, 1};

int lds_deck[50001]{0, 1};
int lds_size[50001]{0, 1};

int N = 0;

int BS(int *search_deck, int left, int right, int target){
    while(left < right){
        int mid = (left + right) / 2;
        if(search_deck[mid] < target){
            left = mid + 1;
        }else{
            right = mid;
        }
    }

    return right;
}

int main(){
    int real_N = 1;
    int temp = 0;
    cin >> N;

    cin >> deck[0];
    for(int i = 1; i < N; i++){
        cin >> temp;
        if(deck[real_N - 1] != temp){
            deck[real_N] = temp;
            real_N++;
        }
    }
    N = real_N;

    int idx_lis_deck = 0;

    for(int idx_deck = 0; idx_deck < N; idx_deck++){
        if(idx_lis_deck == 0 || lis_deck[idx_lis_deck - 1] < deck[idx_deck]){
            lis_deck[idx_lis_deck] = deck[idx_deck];
            idx_lis_deck++;
        }else{
            int lis_target_pos = BS(lis_deck, 0, idx_lis_deck - 1, deck[idx_deck]);
            lis_deck[lis_target_pos] = deck[idx_deck];
        }
        lis_size[idx_deck] = idx_lis_deck;
    }

    // cout << "------------LIS--------------" << endl;
    // for(int i = 0 ; i < N; i++){
    //     cout << i << "] " << lis_size[i] << endl; 
    // }
    int idx_lds_deck = 0;

    for(int idx_deck = N - 1 ; idx_deck >= 0; idx_deck--){
        if(idx_lds_deck == 0 || lds_deck[idx_lds_deck - 1] < deck[idx_deck]){
            lds_deck[idx_lds_deck] = deck[idx_deck];
            idx_lds_deck++;
        }else{
            int lds_target_pos = BS(lds_deck, 0, idx_lds_deck - 1, deck[idx_deck]);
            lds_deck[lds_target_pos] = deck[idx_deck];
        }
        lds_size[idx_deck] = idx_lds_deck;
    }

    // cout << "------------LDS-------------" << endl;
    // for(int i = 0 ; i < N; i++){
    //     cout << i << "] " << lds_size[i] << endl; 
    // }

    // cout << "============HAP============" << endl;
    // for(int i = 0 ; i < N; i++){
    //     cout << i << "] " << lds_size[i] + lis_size[i] - 1 << endl; 
    // }

    int max_cards = 0;
    for(int i = 0 ; i < N; i++){
        if(max_cards < lis_size[i] + lds_size[i] - 1) max_cards = lis_size[i] + lds_size[i] - 1;
    }

    cout << max_cards << endl;

    return 0;
}