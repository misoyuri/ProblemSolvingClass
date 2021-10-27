#include <iostream>

using namespace std;

#define MAX_INT 2147483647

int deck[50001]{0, };
int N = 0;

int max_score = 0;
int lower_card = MAX_INT;
bool is_ascending = true;

void dfs(int card_seq, int score){
    if(card_seq == N){
        max_score = max(max_score, score);
        return;
    }

    dfs(card_seq + 1, score);

    if(score == 0){
        dfs(card_seq + 1, score + 1);
    }



    if(score != 0 && is_ascending){
        if(deck[card_seq - 1] < deck[card_seq]){
            dfs(card_seq + 1, score + 1);
        }else if(deck[card_seq - 1] > deck[card_seq]){
            is_ascending = false;
            lower_card = deck[card_seq];
            dfs(card_seq + 1, score + 1);
            lower_card = MAX_INT;
            is_ascending = true;
        }

    if(!is_ascending && lower_card > deck[card_seq]){
            dfs(card_seq + 1, score + 1);
        }
    }
    
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> deck[i];
    }

    dfs(0, 0);
    cout << max_score << endl;
    // cout << "ret::" << max_score << endl;
}