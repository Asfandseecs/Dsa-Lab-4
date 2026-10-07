#include <iostream>
#include <queue>

struct Node {
	int ID;
	Node* Next;
};

Node* createlist(int n) {
	int id = 1;

	Node* head = new Node();
	head->ID = id;

	Node* t = head;

	while (id != n) {
		t->Next = new Node();
		t = t->Next;

		id++;
		t->ID = id;
	}

	t->Next = head;

	return head;
}

void DeletePerson(Node*& p, Node*& N, std::queue<int>& e) {

	p->Next = N->Next;

	e.push(N->ID);

	delete N;

	N = p->Next;
}

void DisplayEliminated(std::queue<int>& e) {

	while (!e.empty()) {
		std::cout << e.front()
			<< " was eliminated."
			<< std::endl;

		e.pop();
	}
}

Node* GetTail(Node* head) {
	Node* T=head;

	while (T->Next != head) {
		T = T->Next;
	}

	return T;
}

int main() {

	std::queue<int> eliminated;

	int n;
	int k;

	std::cin >> n;
	std::cin >> k;

	Node* Head = createlist(n);

	Node* previous = GetTail(Head);
	Node* current = Head;

	int steps = 1;

	while (Head != Head->Next) {

		if (steps == k) {

			if (current == Head) {
				Head = current->Next;
			}

			DeletePerson(previous, current, eliminated);

			steps = 1;
		}
		else {
			previous = current;
			current = current->Next;

			steps++;
		}
	}


	DisplayEliminated(eliminated);

	std::cout << "Remaining person: "
		<< Head->ID;

	delete Head;

	int c;
	std::cin >> c;

	return 0;
}
