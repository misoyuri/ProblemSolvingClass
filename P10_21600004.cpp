#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#define MAX_SIZE 1010

using namespace std;

string bag_of_words[MAX_SIZE];
vector<int> word_relation[MAX_SIZE];
vector<int> sequence;
bool visited[MAX_SIZE] = {false, };

int N = 0;

void print_solution(){
    for(int i = 0; i < sequence.size(); i++){
        cout << bag_of_words[sequence[i]] << endl;
    }
}

void solve(int current_word, int seq_length) {
	visited[current_word] = true;
    if(seq_length == N){
        print_solution();
        exit(0);
    }


	for (int i = 0; i < word_relation[current_word].size(); i++) {
		int next_word = word_relation[current_word][i];

		if (!visited[next_word]) {
            sequence.push_back(next_word);
			solve(next_word, seq_length + 1);
            sequence.pop_back();

			visited[next_word] = false;	
		}
	}
}

int main(){
    cin >> N;

    cin >> bag_of_words[0];
    for(int i = 1; i < N; i++){
        cin >> bag_of_words[i];

        for(int j = 0; j < i; j++){
            if(bag_of_words[j].front() == bag_of_words[i].back()){
                word_relation[i].push_back(j);
            }
            
            if(bag_of_words[j].back() == bag_of_words[i].front()){
                word_relation[j].push_back(i);
            }
        }
    }


    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) visited[j] = false;

        sequence.push_back(i);
        solve(i, 1);
        sequence.pop_back();
    }

    cout << 0 << endl;

    return 0;
}

