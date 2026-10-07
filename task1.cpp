#include <iostream>
#include <string>

struct Node {
	int Song_id;
	std::string Song_Name;
	int min;
	float sec;
	Node* Next;
	Node* prev;

	Node(int s, std::string sn, int m, float se) {
		this->Song_id = s;
		this->Song_Name = sn;
		this->min = m;
		this->sec = se;
		this->Next = nullptr;
		this->prev = nullptr;
	}
};

Node* GetTail(Node* head) {
	if (head == nullptr) {
		return head;
	}

	while (head->Next != nullptr) {
		head = head->Next;
	}

	return head;
}

void AddSong(Node* t, Node* Added) {
	Node* Tail = GetTail(t);

	Tail->Next = Added;
	Added->prev = Tail;
	Added->Next = nullptr;
}

void DeleteSong(Node* t, int ID) {

	while (t != nullptr && t->Song_id != ID) {
		t = t->Next;
	}

	if (t == nullptr) {
		std::cout << "Song not found.\n";
		return;
	}

	if (t->prev == nullptr) {
		std::cout << "Cannot delete the head using this function.\n";
		return;
	}

	if (t->Next == nullptr) {
		t->prev->Next = nullptr;
		delete t;
		return;
	}

	t->prev->Next = t->Next;
	t->Next->prev = t->prev;

	delete t;
}

void DisplayListForward(Node* head) {

	while (head != nullptr) {
		std::cout << "Song ID: " << head->Song_id << std::endl;
		std::cout << "Song Name: " << head->Song_Name << std::endl;
		std::cout << "Song Duration: "
			<< head->min << " minutes "
			<< head->sec << " seconds"
			<< std::endl;

		std::cout << "------------------------------------------------------------------"
			<< std::endl << std::endl;

		head = head->Next;
	}
}

void DisplayListBackward(Node* Head) {

	Node* Tail = GetTail(Head);

	while (Tail != nullptr) {
		std::cout << "Song ID: " << Tail->Song_id << std::endl;
		std::cout << "Song Name: " << Tail->Song_Name << std::endl;
		std::cout << "Song Duration: "
			<< Tail->min << " minutes "
			<< Tail->sec << " seconds"
			<< std::endl;

		std::cout << "------------------------------------------------------------------"
			<< std::endl << std::endl;

		Tail = Tail->prev;
	}
}

void PlayNextSong(Node*& curr) {

	if (curr->Next == nullptr) {
		std::cout << "No songs left." << std::endl;
		return;
	}

	curr = curr->Next;

	std::cout << "Now Playing: "
		<< curr->Song_Name << std::endl;
}

void PlayPrevSong(Node*& curr) {

	if (curr->prev == nullptr) {
		std::cout << "No previous song." << std::endl;
		return;
	}

	curr = curr->prev;

	std::cout << "Now Playing: "
		<< curr->Song_Name << std::endl;
}


void ReverseList(Node*& head) {

	Node* current = head;
	Node* temp = nullptr;

	while (current != nullptr) {

		
		temp = current->prev;
		current->prev = current->Next;
		current->Next = temp;

	
		current = current->prev;
	}


	if (temp != nullptr) {
		head = temp->prev;
	}
}


int main() {

	Node* Song1 = new Node(1, "Blinding Lights", 3, 20);
	Node* Song2 = new Node(2, "Believer", 3, 24);
	Node* Song3 = new Node(3, "Shape of You", 3, 53);
	Node* Song4 = new Node(4, "Perfect", 4, 23);
	Node* Song5 = new Node(5, "Faded", 3, 32);

	Node* head = Song1;

	AddSong(head, Song2);
	AddSong(head, Song3);
	AddSong(head, Song4);
	AddSong(head, Song5);


	std::cout << "========== FORWARD ==========\n\n";
	DisplayListForward(head);

	std::cout << "========== BACKWARD ==========\n\n";
	DisplayListBackward(head);


	Node* current = head;

	std::cout << "========== PLAYING SONGS ==========\n\n";

	std::cout << "Current Song: "
		<< current->Song_Name << std::endl;

	PlayNextSong(current);

	PlayNextSong(current);

	PlayPrevSong(current);


	std::cout << "\n========== DELETING SONG 3 ==========\n\n";

	DeleteSong(head, 3);

	std::cout << "========== UPDATED PLAYLIST ==========\n\n";
	DisplayListForward(head);


	std::cout << "\n========== ADDING A NEW SONG ==========\n\n";

	Node* Song6 = new Node(6, "Starboy", 3, 50);

	AddSong(head, Song6);

	DisplayListForward(head);


	std::cout << "\n========== REVERSING PLAYLIST ==========\n\n";

	ReverseList(head);

	DisplayListForward(head);


	std::cout << "\n========== BACKWARD AFTER REVERSE ==========\n\n";

	DisplayListBackward(head);


	int c;
	std::cin >> c;

	return 0;
}


