#include <iostream>

using namespace std;

typedef struct Node{
    Node *prev = NULL;
    Node *next = NULL;
    int data = 0;
    int count = 0;
};

Node *head;
Node *tail;

void initList(){
    head = new Node();
    tail = new Node();

    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;

}

Node* searchSmallerNode(int data)
{
	Node* iterateNode = head->next;	

	while (iterateNode != tail)
	{
		if (iterateNode->data <= data)
		{
			return iterateNode;
		}
		iterateNode = iterateNode->next;
	}

	return iterateNode;
}

void deltNode(Node *target){
	// if (target == head || target == tail)
	// 	return;
    if(target->count > 1){ 
        target->count--;
        return;    
    }

	target->next->prev = target->prev;
	target->prev->next = target->next;
	free(target);
}

void addNode(Node *target, int data){
    if(target->count > 0 && target->data == data){
        target->count++;
        return;
    }

    Node *newNode = new Node();
    newNode->data = data;
    newNode->count++;
    if(target == head){
        target->next->prev = newNode;
        newNode->next = target->next;
        newNode->prev = target;
        target->next = newNode;
    }else{
        target->prev->next = newNode;			
        newNode->next = target;
        newNode->prev = target->prev;
        target->prev = newNode;
    }

}

void printList(){
    Node* iterateNode = head->next;	

    while (iterateNode != tail){
        cout << "[" << iterateNode->data << "::" << iterateNode->count << "] ";
		iterateNode = iterateNode->next;
	}

}

int solve(int M){
    int ret = 0;

	for(;;)
    {
        Node* iterateNode = head->next;
        if(iterateNode == tail) break;

        int remainder = M - iterateNode->data;

        cout << "[" << iterateNode->data << "]";

        iterateNode = iterateNode->next;
        deltNode(iterateNode->prev);
        ret++;

        if(remainder == 0) cout << endl;
        if(remainder == 0) continue;

        while (iterateNode != tail){
            if(remainder - iterateNode->data >= 0){
                cout << "[" << iterateNode->data << "]";
                deltNode(iterateNode);
                break;
            }
            iterateNode = iterateNode->next;
        }
        cout << endl;
	}

    return ret;
}

int main(){
    initList();
    int data = 0;
    int M = 0;

    cin >> M;

    while(cin >> data){
        addNode(searchSmallerNode(data), data);
    }

    
    // printList();
    cout << solve(M) << endl;

    return 0;
}