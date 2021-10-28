#include <iostream>

using namespace std;

#define MAX_INT 2147483647
#define DEBUG_MODE false

int deck[50001]{0, };
int debug_deck[50001]{0, 1};
int N = 0;

int max_score = 0;
int lower_card = MAX_INT;
bool is_ascending = true;

void print_debug_log(int score){
    for(int i = 0; i < score; i++){
        printf("%d(%d)", deck[debug_deck[i]], debug_deck[i]);
        if(i != score - 1){
            printf("->");
        }else{
            printf("\n");
        }
    }
}

void dfs(int card_seq, int score, int selected_card){
    if(card_seq == N){
        // if(max_score < score) 
        if(DEBUG_MODE) print_debug_log(score);
        max_score = max(max_score, score);
        return;
    }

    dfs(card_seq + 1, score, selected_card);

    if(score == 0){
        if(DEBUG_MODE) debug_deck[score] = card_seq;
        is_ascending = true;
        dfs(card_seq + 1, score + 1, deck[card_seq]);
    }else{
        if(is_ascending == true){
            if(selected_card < deck[card_seq]){
                if(DEBUG_MODE) debug_deck[score] = card_seq;
                dfs(card_seq + 1, score + 1, deck[card_seq]);
            }else if(selected_card > deck[card_seq]){
                lower_card = deck[card_seq];
                is_ascending = false;
                if(DEBUG_MODE) debug_deck[score] = card_seq;
                dfs(card_seq + 1, score + 1, deck[card_seq]);

                is_ascending = true;
            }
        }
        
        if(is_ascending == false){
            if(selected_card > deck[card_seq]){
                if(DEBUG_MODE) debug_deck[score] = card_seq;
                dfs(card_seq + 1, score + 1, deck[card_seq]);
            }    
        }
    }
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> deck[i];
    }
    // cout << "---------------" << endl;
    dfs(0, 0, 0);
    cout << max_score << endl;
    // cout << "ret::" << max_score << endl;
}