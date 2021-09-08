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

void printStatus(){
    cout << "-----------------status------------------" << endl;
    for(int i = 1; i <= gN; i++){
        cout << i << "::" << relation[i].status << endl;
    }
    cout << "-----------------------------------------" << endl;
}

void printList(){
    cout << "-----------------------------------------" << endl;
    for(int i = 1; i <= gN; i++){
        List *tempList = &relation[i];
        cout << i << "::";
        if(tempList->next != NULL) tempList = tempList->next;
        while(tempList != NULL){
            cout <<  "[" << tempList->nodeName << ", " << tempList->status << "] " "-> " ;
            tempList = tempList->next;
        }
        cout << endl;
    }
    cout << "-----------------------------------------" << endl;
}

int subSearch(int startIdx, int id, int cnt){
    if(relation[startIdx].linkedSize < gK) return cnt;
    if(relation[startIdx].status != 0) return cnt;
    List *tempList = &relation[startIdx];
    // printList();

    while(tempList != NULL){
        // cout << tempList->nodeName << "->" ;ss
        if(relation[tempList->nodeName].linkedSize >= gK && relation[tempList->nodeName].status == 0){
            // cout << "Name::" << relation[tempList->nodeName].nodeName << " | status::" << relation[tempList->nodeName].status << " | size::" << relation[tempList->nodeName].linkedSize << endl;
            relation[tempList->nodeName].status = id;
            cnt++;
            cnt = subSearch(tempList->nodeName, id, cnt);
        }

        tempList = tempList->next;
    }

    return cnt;
}

int mainSearch(){
    int maxNumSet = 0;
    int retNumSet = 0;
    for(int i = 1; i <= gN; i++){
        // cout << "main::" << i << "]" ;
        retNumSet = subSearch(i, i, 0);
        
        cout << endl;
        // printStatus();
        if(retNumSet > gK){
            cout << i << "]retNumSet::" << retNumSet <<endl;
            maxNumSet += retNumSet;
        }
        if(retNumSet > maxNumSet) maxNumSet = retNumSet;
        // cout << i << "::" << maxNumSet << endl;
    }

    return maxNumSet;
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
        relation[fellowShip1->nodeName].add(fellowShip2);
        relation[fellowShip2->nodeName].add(fellowShip1);
    }

}

int main(){
    initList();
    int answer = mainSearch();
    cout << "answer::"<< answer << endl;
    printList();
    printStatus();
}