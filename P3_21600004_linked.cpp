#include <iostream>

using namespace std;

struct Node{
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

void discountNode(Node *target){
    target->count--;
}

void addNode(Node *target, int data){
    if(target->count > 0 && target->data == data){
        target->count++;
        return;
    }

    Node *newNode = new Node();
    newNode->data = data;
    newNode->count = 1;

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
        cout << "[" << iterateNode->data << "::" << iterateNode->count << "]";
		iterateNode = iterateNode->next;
	}
    cout << endl;

}

int solve(int M){
    int ret = 0;

    Node* front_iterateNode = head->next;
    Node* rear_iterateNode = tail->prev;
	for(;;){
        if(front_iterateNode == rear_iterateNode && front_iterateNode->count == 0) break;


        if(front_iterateNode->data + rear_iterateNode->data <= M){
            discountNode(rear_iterateNode);
            if(rear_iterateNode->count == 0) rear_iterateNode = rear_iterateNode->prev;
        }

        discountNode(front_iterateNode);
        if(front_iterateNode->count == 0) front_iterateNode = front_iterateNode->next;
        ret++;
	}

    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    initList();
    int data = 0;
    int M = 0;

    cin >> M;

    while(cin >> data){
        if(data > M || data < 1) continue;
        addNode(searchSmallerNode(data), data);
        // cout << "data::" << data << endl;
    }

    
    // printList();
    cout << solve(M) << endl;

    return 0;
}