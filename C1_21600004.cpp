#include <iostream>

using namespace std;

typedef struct List{
    List *next = NULL;
    int nodeName = 0;
    int linkedSize = 0;
    int status = 0;
    
    void add(List *newList){
        newList->next = this->next;
        this->next = newList;
        this->linkedSize++;
    }
};

int gN=0;
int gK=0;
int gF=0;

List *relation;

void printList(){
    for(int i = 1; i <= gN; i++){
        List *tempList = &relation[i];
        cout << i << "::";
        while(tempList != NULL){
            cout <<  tempList->nodeName << "-> " ;
            tempList = tempList->next;
        }
        cout << endl;
    }
}

void subSearch(int startIdx, int id){

}

void mainSearch(){

}

void initList(){
    int f1 = 0, f2 = 0;
    cin >> gN >> gK >> gF;

    relation = new List[gN+1];
    for(int i = 1; i <= gN; i++) relation[i].nodeName = i;

    for(int i = 0; i < gF; i++){
        List *fellowShip1 = new List;
        List *fellowShip2 = new List;
        cin >> fellowShip1->nodeName >> fellowShip2->nodeName;
        cout << "[" << fellowShip1->nodeName << " | " << fellowShip2->nodeName << "]"<< endl;
        relation[fellowShip1->nodeName].add(fellowShip2);
        relation[fellowShip2->nodeName].add(fellowShip1);
        printList();
        cout << "-------------------------------------------------------" << endl;
        // cout << relation[i].getNext() << endl;
    }

}

int main(){
    initList();
    printList();
}