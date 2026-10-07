#include <iostream>
#include <string>

using namespace std;

struct Node {
    int bit;
    Node* next;
    Node* prev;
};

struct BinaryList {
    Node* head;
    Node* tail;
};

BinaryList createEmptyList() {
    BinaryList list;
    list.head = nullptr;
    list.tail = nullptr;
    return list;
}

Node* createNode(int bit) {
    Node* newNode = new Node;
    newNode->bit = bit;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void insertAtHead(BinaryList& list, int bit) {
    Node* newNode = createNode(bit);
    if (!list.head) {
        list.head = list.tail = newNode;
    } else {
        newNode->next = list.head;
        list.head->prev = newNode;
        list.head = newNode;
    }
}

void insertAtTail(BinaryList& list, int bit) {
    Node* newNode = createNode(bit);
    if (!list.tail) {
        list.head = list.tail = newNode;
    } else {
        newNode->prev = list.tail;
        list.tail->next = newNode;
        list.tail = newNode;
    }
}

void clearList(BinaryList& list) {
    Node* current = list.head;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    list.head = list.tail = nullptr;
}

BinaryList cloneList(BinaryList& list) {
    BinaryList copy = createEmptyList();
    Node* current = list.head;
    while (current) {
        insertAtTail(copy, current->bit);
        current = current->next;
    }
    return copy;
}

void removeLeadingZeros(BinaryList& list) {
    while (list.head && list.head->bit == 0 && list.head != list.tail) {
        Node* temp = list.head;
        list.head = list.head->next;
        list.head->prev = nullptr;
        delete temp;
    }
}

void padToMultiplesOfEight(BinaryList& list) {
    int length = 0;
    Node* current = list.head;
    while (current) {
        length++;
        current = current->next;
    }

    if (length == 0) {
        for (int i = 0; i < 8; i++) {
            insertAtTail(list, 0);
        }
        return;
    }

    int remainder = length % 8;
    if (remainder != 0) {
        int padCount = 8 - remainder;
        for (int i = 0; i < padCount; i++) {
            insertAtHead(list, 0);
        }
    }
}

void printList(BinaryList& list) {
    if (!list.head) {
        cout << "0";
        return;
    }
    Node* current = list.head;
    while (current) {
        cout << current->bit;
        current = current->next;
    }
}

void printGrouped8Bit(BinaryList& list) {
    if (!list.head) {
        cout << "00000000";
        return;
    }

    Node* current = list.head;
    int count = 0;

    while (current) {
        cout << current->bit;
        count++;
        if (count % 8 == 0 && current->next != nullptr) {
            cout << " ";
        }
        current = current->next;
    }
}

BinaryList storeBinaryNumber(string& str) {
    BinaryList list = createEmptyList();
    for (char ch : str) {
        if (ch == '0' || ch == '1') {
            insertAtTail(list, ch - '0');
        }
    }
    padToMultiplesOfEight(list);
    return list;
}

BinaryList onesComplement(BinaryList& list) {
    BinaryList result = createEmptyList();
    Node* current = list.head;
    while (current) {
        insertAtTail(result, current->bit == 0 ? 1 : 0);
        current = current->next;
    }
    return result;
}

BinaryList binaryAddition(BinaryList& num1, BinaryList& num2) {
    BinaryList result = createEmptyList();
    Node* p1 = num1.tail;
    Node* p2 = num2.tail;
    int carry = 0;

    while (p1 || p2 || carry) {
        int sum = carry;
        if (p1) {
            sum += p1->bit;
            p1 = p1->prev;
        }
        if (p2) {
            sum += p2->bit;
            p2 = p2->prev;
        }

        insertAtHead(result, sum % 2);
        carry = sum / 2;
    }

    padToMultiplesOfEight(result);
    return result;
}

BinaryList twosComplement(BinaryList& list) {
    BinaryList comp1 = onesComplement(list);
    
    BinaryList one = createEmptyList();
    insertAtTail(one, 1);

    BinaryList result = binaryAddition(comp1, one);
    
    clearList(comp1);
    clearList(one);

    return result;
}

BinaryList binaryMultiplication(BinaryList& num1, BinaryList& num2) {
    BinaryList product = createEmptyList();
    insertAtTail(product, 0);
    padToMultiplesOfEight(product);

    BinaryList currentShifted = cloneList(num1);
    Node* p2 = num2.tail;

    while (p2) {
        if (p2->bit == 1) {
            BinaryList temp = binaryAddition(product, currentShifted);
            clearList(product);
            product = temp;
        }

        insertAtTail(currentShifted, 0);
        p2 = p2->prev;
    }

    clearList(currentShifted);
    removeLeadingZeros(product);
    padToMultiplesOfEight(product);

    return product;
}

long long convertToDecimal(BinaryList& list) {
    long long decimalValue = 0;
    Node* current = list.head;

    while (current) {
        decimalValue = (decimalValue * 2) + current->bit;
        current = current->next;
    }

    return decimalValue;
}

int main() {
    string str1, str2;

    cout << "=== Binary Arithmetic Simulation Using DLL ===" << endl << endl;

    cout << "Enter first binary number: ";
    cin >> str1;
    cout << "Enter second binary number: ";
    cin >> str2;

    BinaryList num1 = storeBinaryNumber(str1);
    BinaryList num2 = storeBinaryNumber(str2);

    cout << "\n--------------------------------------------" << endl;
    cout << "Stored Binary Number 1 (8-bit blocks): ";
    printGrouped8Bit(num1);
    cout << "\nStored Binary Number 2 (8-bit blocks): ";
    printGrouped8Bit(num2);
    cout << "\n--------------------------------------------" << endl;

    BinaryList ones1 = onesComplement(num1);
    BinaryList ones2 = onesComplement(num2);
    cout << "\n1's Complement of Num 1: ";
    printGrouped8Bit(ones1);
    cout << "\n1's Complement of Num 2: ";
    printGrouped8Bit(ones2);

    BinaryList twos1 = twosComplement(num1);
    BinaryList twos2 = twosComplement(num2);
    cout << "\n\n2's Complement of Num 1: ";
    printGrouped8Bit(twos1);
    cout << "\n2's Complement of Num 2: ";
    printGrouped8Bit(twos2);

    BinaryList sum = binaryAddition(num1, num2);
    cout << "\n\nBinary Addition (Num1 + Num2): ";
    printGrouped8Bit(sum);

    BinaryList product = binaryMultiplication(num1, num2);
    cout << "\nBinary Multiplication (Num1 * Num2): ";
    printGrouped8Bit(product);

    cout << "\n--------------------------------------------" << endl;
    cout << "Decimal Equivalent of Num 1: " << convertToDecimal(num1) << endl;
    cout << "Decimal Equivalent of Num 2: " << convertToDecimal(num2) << endl;
    cout << "Decimal Equivalent of Sum:   " << convertToDecimal(sum) << endl;
    cout << "Decimal Equivalent of Prod:  " << convertToDecimal(product) << endl;
    cout << "--------------------------------------------" << endl;

    clearList(num1);
    clearList(num2);
    clearList(ones1);
    clearList(ones2);
    clearList(twos1);
    clearList(twos2);
    clearList(sum);
    clearList(product);

    return 0;
}