#include <iostream>

using namespace std;

typedef struct List{
    private:
        List *next = NULL;
        int linkedSize = 0;
        int status = 0;
        int nodeNumber = 0;

    public:
        void add(List *newList){
            this->next = newList;
            this->linkedSize++;
        }

        int getSize(){
            return this->linkedSize;
        }

        List* getNext(){
            return this->next;
        }
};

int gN=0;
int gK=0;
int gF=0;

List *relation;

void initList(){
    cin >> gN >> gK >> gF;

    relation = new List[gN];

    for(int i = 0; i < gF; i++){
        cout << relation[i].getNext() << endl;
    }

}

int main(){
    initList();
}