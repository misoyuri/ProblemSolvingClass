#include <iostream>

using namespace std;

typedef struct Node{
    Node *prev = NULL;
    Node *next = NULL;
    float data = 0;
};

Node *head;
Node *tail;
float nodeSize = 0;

void initList(){
    head = new Node();
    tail = new Node();

    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;

    nodeSize = 0;
}

Node* searchSmallerNode(float data)
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

	target->next->prev = target->prev;
	target->prev->next = target->next;
	free(target);
	nodeSize--;
}

void addNode(Node *target, float data){
    Node *newNode = new Node();
    newNode->data = data;

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

    nodeSize++;
}

void printList(){
    Node* iterateNode = head->next;	

    while (iterateNode != tail){
        cout << "[" << iterateNode << ", " << iterateNode->data << "] ";
		iterateNode = iterateNode->next;
	}

    cout << endl << "size::" << nodeSize << endl;
}

float solve(float M){
    int ret = 0;

	for(;;)
    {
        Node* iterateNode = head->next;
        if(iterateNode == tail) break;

        float remainder = M - iterateNode->data;
        iterateNode = iterateNode->next;
        deltNode(iterateNode->prev);
        ret++;

        if(remainder == 0) continue;

        while (iterateNode != tail){
            if(remainder - iterateNode->data){
                deltNode(iterateNode);

                break;
            }
            iterateNode = iterateNode->next;
        }
        // printList();
	}

    return ret;
}

int main(){
    initList();
    float data = 0;
    int M = 0;

    cin >> M;
    if(M > 100000) M = 100000;

    while(cin >> data){
        if(data <= 0 || data > M) continue;
        addNode(searchSmallerNode(data), data);
    }

    // printList();
    cout << solve(M) << endl;
    // cout << "sol::" << solve(M) << endl;
    

    return 0;
}