#pragma once
#include <iostream>
using namespace std;
template <typename T>

class List {

public:
    struct Node {
        T data;
        Node* next;
        Node(T _data)
        {
            data = _data;
            next = nullptr;
        }
    };
    List();
    Node* getHead();
    void insertAtTheEnd(T& aData);
    void eliminateNode(int pos);
    void deleteNode(Node* nodeToDelete);
    void removeLast();
    bool findData(T& aData);
    int getSize();
    T getAt(int pos) const;
    ~List();
    void deleteNodeWithData(int index);
    void clear();
private:
    Node* head;
    int size;
};

template <typename T>
List<T>::List() : head(nullptr), size(0) { }

template <typename T>
typename List<T>::Node* List<T>::getHead()
{
    return head;
}

template <typename T>
void List<T>::insertAtTheEnd(T& aData)
{
    Node* newNode = new Node(aData);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    size++;
}

template <typename T>
void List<T>::eliminateNode(int pos)
{
    if (head == nullptr)
    {
        return;
    }
    if (pos == 0)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    else {
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < pos - 1; i++)
        {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr)
        {
            return;
        }
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }
    size--;
}

template <typename T>
void List<T>::deleteNodeWithData(int index) {
    if (index < 0) {
        std::cerr << "Error: índice fuera de rango en deleteNode." << std::endl;
        return;
    }
    Node* temp = nullptr;
    if (index == 0) {
        temp = head;
        head = head->next;
        delete temp;
    }
    else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
        delete temp;
    }
    size--;
}

template <typename T>
void List<T>::deleteNode(Node* nodeToDelete)
{
    T value = nodeToDelete->data;
    if (head == nullptr)
    {
        return;
    }
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr && current->data != value)
    {
        prev = current;
        current = current->next;
    }
    if (current != nullptr)
    {
        prev->next = current->next;
        delete current;
    }
    size--;
}

template <typename T>
void List<T>::removeLast()
{
    if (head == nullptr) {
        cout << "La lista esta vacia. No se puede eliminar el ultimo nodo." << endl;
        return;
    }
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr && current->next->next != nullptr)
        {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
}

template <typename T>
bool List<T>::findData(T& aData)
{
    Node* temp = head;
    while (temp != nullptr)
    {
        if (temp->data == aData)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <typename T>
int List<T>::getSize()
{
    
    return size;
}

template <typename T>
List<T>::~List()
{
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr)
    {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <typename T>
void List<T>::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template <typename T>
T List<T>::getAt(int pos) const {
    Node* temp = head;
    int counter = 0;

    while (temp != nullptr) {
        if (counter == pos) {
            return temp->data;
        }
        temp = temp->next;
        counter++;
    }
}


