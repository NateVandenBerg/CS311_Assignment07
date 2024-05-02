//CS311 LinkedList.h
//INSTRUCTION:
//Linkedlist class - header file template 
//You must complete the TODO parts and then complete LinkedList.cpp. Delete "TODO" after you are done.
//You should always comments to each function to describe its PURPOSE and PARAMETERS 
#pragma once

// =======================================================
// Your name: 
// Compiler:  g++ 
// File type: headher file  linkedlist.h
//=======================================================
#include <string>
#include "order.h"
using namespace std;

// Datatype T : element type definition
typedef Order T;  // Use Order as the data type for the Linked List. An alternative is to use template class.

//a list node is defined here as a struct Node for now
struct Node {
    T val;   // stored value
    Node *next;  // pointer to the next node

    // Constructor
    Node(T val, Node *next = nullptr) {
        //cout << ">Node(T,Node*);";
		//cout << ">>" << val.id << "-" << val.name << "-" << val.amount << "| ";
		this->val = val;
		//cout << "~~" << this->val.id << "-" << this->val.name << "-" << this->val.amount << "| ";
        this->next = next;
    }
};
//---------------------------------------------------------

class LinkedList {
private:
    Node *front;       // pointer to the front node
    Node *rear;        // pointer to the rear node
    int count;        // the number of nodes in the list

public:
    LinkedList() {     // constructor to create an empty list
        front = nullptr;
        rear = nullptr;
        count = 0;//
    }

    ~LinkedList();     // destructor to destroy all nodes and release memory

    /**
     * @brief Copy Constructor to allow pass by value and return by value of a LinkedList
     * @param other LinkedList to be copied
     */
    LinkedList(const LinkedList &other);

    /**
     * @brief Overloading of = (returns a reference to a LinkedList)
     * @param other LinkedList to be copied
     * @return reference to a LinkedList
     */
    LinkedList &operator=(const LinkedList &other);


    /**
     * @brief Purpose: Checks if the list is empty
     * @return true if the list is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief  Get the number of nodes in the list
     * @return int The number of nodes in the list
     */
    int length() const;

    /**
     * @brief  Displays the contents of the list
     *
     */
    void displayAll();

    //Add a new node at the front of the list
    void addFront(T val);

    //Add a new node at the rear of the list
    void addRear(T val);

    //Delete the front node
    bool deleteFront(T &val);

    //Delete the rear node
    bool deleteRear(T &val);

    /**
     * @brief Delete a node at a given position from the list. The
     * node at position pos is deleted and the value of the deleted node is returned in val.
     * The valid range of pos is 0 to count-1. pos = 0 for the first node, and pos = count-1 for the last node.
     * @param pos: position of the node to be deleted
     * @param val: it is set to the value of the node to be deleted
     * @return true: if the node was deleted successfully
     * @return false: if the node was not deleted successfully because the position was out of range
    */
    bool deleteAt(int pos, T &val);

    /**
     * @brief Insert a value at a specified position in the list. The valid pos is in the range of 0 to count.
     * The value will be inserted before the node at the specified position. if pos = 0, the value will be inserted
     * at the front of the list. if pos = count, the value will be inserted at the rear of the list.
     * @param pos: position to insert the value at.
     * @param val: value to insert.
     * @return true: if the value was inserted.
     * @return false: if the value was not inserted because pos is out of the range.
     */
    bool insertAt(int pos, T val);

    /**
     * @brief check whether a value is in the list or not
     * @param val
     * @return int: the position of the value in the list. If the value is not in the list, return -1.
     */
    int search(const T& val) const;

    /**
     * @brief Get the pointer to the node at a given position
     * @param pos
     * @return
     */
    Node* getNode(int pos) const {
        if (pos < 0 || pos >= count) {
            return nullptr;
        }
        Node *p = front;
        for (int i = 0; i < pos; i++) {
            p = p->next;
        }
        return p;
    }

    /**
     * @brief Get the pointer to the front node
     */
    Node *getFront() const { return front; }
    /**
     * @brief Get the pointer to the rear node
     */
    Node *getRear() const { return rear; }
};
