#include <iostream>
#include <unistd.h>
using namespace std;

typedef struct List{
    List *next = NULL;
    List *prev = NULL;
    int nodeName = 0;
    int linkedSize = 0;
    int status = 0;
    
    void add(List *newList){
        newList->next = this->next;
        this->next = newList;
        this->linkedSize++;
    }

    void del(int target){
        List *tempList = this->next;
        List *prevList = this;

        if(tempList == NULL ) {
            return;
        }

        if(tempList->nodeName == target && tempList->next == NULL){
            tempList = NULL;
            prevList->next = NULL;
            return;
        }

        cout << "del]curNode::" << this->nodeName << " for " << target << endl;
        while(tempList != NULL){
            // cout << "del]rootNode::" << this->nodeName << "-> curNode::" << tempList->nodeName << " ";
            if(tempList->nodeName == target){
                // if(this->linkedSize == 1){
                    tempList->next = NULL;
                    // delete tempList;
                // }else{
                    List *delNode = tempList;
                    prevList->next = delNode->next;
                    // delete delNode;
                    this->linkedSize--;
                // }
                
            }
            tempList = tempList->next;
            if(prevList != this)
                prevList = prevList->next;
        }
        cout << endl;
        
        // delete tempList;
    }
};


int gN=0;
int gK=0;
int gF=0;

int *targetNodes;
int targetNodesIdx = 0;

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
        // if(tempList->next != NULL) tempList = tempList->next;
        while(tempList != NULL){
            cout <<  "[" << tempList->nodeName << ", " << tempList->status << "] " "-> " ;
            tempList = tempList->next;
        }
        cout << endl;

        // delete tempList;
    }
    cout << "-----------------------------------------" << endl;
}

void resetList(){
    for(int i = 1; i<= gN; i++){
        relation[i].status = 0;
    }
}

int subSearch(int startIdx, int id, int cnt){
    if(relation[startIdx].linkedSize < gK) return cnt;
    if(relation[startIdx].status != 0) return cnt;
    List *tempList = &relation[startIdx];

    while(tempList != NULL){
        cout << tempList->nodeName << "->" ;
        if(relation[tempList->nodeName].linkedSize >= gK && relation[tempList->nodeName].status == 0){
            cout << endl <<"Name::" << relation[tempList->nodeName].nodeName << " | status::" << relation[tempList->nodeName].status << " | size::" << relation[tempList->nodeName].linkedSize << endl;
            relation[tempList->nodeName].status = id;
            cnt++;
            cnt = subSearch(tempList->nodeName, id, cnt);
        }

        tempList = tempList->next;
    }

    // delete tempList;
    return cnt;
}

int mainSearch(){
    int maxNumSet = 0;
    int retNumSet = 0;
    for(int i = 1; i <= gN; i++){
        cout << "main::" << i << "]" ;
        retNumSet = subSearch(i, i, 0);
        
        cout << endl;
        printStatus();
        if(0 < retNumSet && retNumSet <= gK){
            cout << i << "]retNumSet::" << retNumSet <<endl;
            maxNumSet += retNumSet;
            resetList();
        }
        if(retNumSet > gK && retNumSet > maxNumSet) maxNumSet = retNumSet;
        cout << i << "::" << maxNumSet << endl;
    }

    return maxNumSet;
}

void resetTargetNodes(){
    cout << "hi" << endl;
    for(int i = 1; i <=gN;i++){
        targetNodes[i] = 0;
    }
    cout << "bye" << endl;
}

void optimizeList(){
    List* tempList;
    bool isEnd = true;
    int trial = 1;
    printList();
    while(true){
        isEnd = true;
        // resetTargetNodes();
        std::cout << "while in!"<< endl;
        for(int i = 1; i <= gN; i++){
            if(relation[i].linkedSize < gK){
                targetNodes[relation[i].nodeName] = 1;
                isEnd = false;
            }
        }

        if(isEnd) break;
        cout << "Opt::" << trial << endl;

        cout << "target List::";
        for(int j = 1; j <= gN; j++){
            if(targetNodes[j]) cout << j << " ";
        }
        cout << endl;

        for(int i = 1; i <= gN; i++){
            for(int j = 1; j <= gN; j++){
                if(targetNodes[j] == 1)
                    relation[i].del(j);
            }
            
        }
        if(trial < 3){

            printList();
            // usleep(500000000);
        }else if(trial == 3){
            printList();
            usleep(500000000);
        }
        trial++;
    }

}

void initList(){
    int f1 = 0, f2 = 0;
    cin >> gN >> gK >> gF;

    relation = new List[gN+1];
    targetNodes = new int[gN+1];
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
    optimizeList();

    cout << "opt out!" << endl;
    int answer = mainSearch();
    cout << "answer::"<< answer << endl;
    printList();
    printStatus();
}