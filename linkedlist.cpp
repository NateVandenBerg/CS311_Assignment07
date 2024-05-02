//CS311 Yoshii S22 Linked List class

//INSTRUCTION:
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//  Highly recommended to copy HW3P1-help as PURPOSE of each function.
//  Add sufficient comments to your code body to describe what it does.
//      - Make sure all if-then-else are commented describing which case it is
//      - Make sure all local variables are described fully with their purposes

// ====================================================
//Your name: Nathaniel VandenBerg
//Complier:  g++
//File type: linkedList.cpp implementation file
//=====================================================

#include<iostream>
#include"linkedlist.h"

using namespace std;

/**
 * @brief Destructor to destroy all nodes and release memory
 */
LinkedList::~LinkedList() {
    Node *temp = front;
    while (temp != nullptr) {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
}

/**
 * @brief Purpose: Checks if the list is empty
 * @return true if the list is empty, false otherwise
 */
bool LinkedList::isEmpty() const {
    if (count == 0) {
        //cout << ">isEmpty();";
        return true;
    }
    return false;
}

/**
 * @brief  Get the number of nodes in the list
 * @return int The number of nodes in the list
 */
int LinkedList::length() const {
    return count;
}


/**
 * @brief Displays the contents of the list
 */
void LinkedList::displayAll() {
    Node *ptr = front;
    cout << "[";
    if (ptr != nullptr) {
          // Head node is not preceded by separator
          cout << ptr->val;
          ptr = ptr->next;
      }
    while (ptr != nullptr) {
        cout << ptr->val;
        ptr = ptr->next;
    }
    cout << "] count: " << length() << endl;
}

// Add a node to the rear of the list
void LinkedList::addRear(T val) {
    //cout << ">addRear();";
    //cout << "~~" << val.id << "-" << val.name << "-" << val.amount << "| ";
    // consider the two cases of whether the list was empty or not
    if (isEmpty()) {
        front = new Node(val);
        rear = front;
    } else {
        rear->next = new Node(val);
        rear = rear->next;
    }
        count++;
    //displayAll();
}

// Add a node to the front of the list
void LinkedList::addFront(T val) {
    //cout << ">addFront();";
    // consider the two cases of whether the list was empty
    if (isEmpty()) {
        front = new Node(val);
        rear = front;
    } else {
        Node *temp = front;
        front = new Node(val);
        front->next = temp;
    }
    if (count < 0) {
        count = 1;
    }
    else
        count++;
}

// Delete a node from the front of the list
bool LinkedList::deleteFront(T &OldNum) {
    //cout << ">deleteFront();";
    // consider if the list was empty and return false if the list is empty
    // consider the special case of deleting the only node in the list
    if (isEmpty()) {
        return false;
    } else if (count == 1) {
        OldNum = front->val;
        delete front;
        front = nullptr;
        rear = nullptr;
        count = 0;
        return true;
    } else {
        Node *temp = front;
        front = front->next;
        OldNum = temp->val;
        delete temp;
        count--;
        return true;
    }
}

// Delete a node from the rear of the list
bool LinkedList::deleteRear(T &OldNum) {
    //cout << ">deleteRear();";
    // consider if the list was empty and return false if the list is empty
    // consider the special case of deleting the only node in the list
    if (isEmpty()) {
        return false;
    } else if (count == 1) {
        OldNum = front->val;
        delete front;
        front = nullptr;
        rear = nullptr;
        count = 0;
        return true;
    } else {
        Node *temp = front;
        while (temp->next != rear) {
            temp = temp->next;
        }
        OldNum = rear->val;
        delete rear;
        rear = temp;
        rear->next = nullptr;
        count--;
        return true;
    }
}

/* --- harder ones for test 2 and 3 -- */

/**
     * @brief Delete a node at a given position from the list. The
     * node at position pos is deleted and the value of the deleted node is returned in val.
     * The valid range of pos is 0 to count-1. pos = 0 is the first node, and pos = count-1 is the last node.
     * @param pos: position of the node to be deleted
     * @param val: it is set to the value of the node to be deleted
     * @return true: if the node was deleted successfully
     * @return false: if the node was not deleted successfully because the position was out of range
    */
bool LinkedList::deleteAt(int pos, T &val) {
    //cout << ">deleteAt();";
    // check if the pos is valid first, then move the ptr to the rigth positon
    // consider the special case of deleting the first node and the last node
    // Do not forget to set value.
    if (pos < 0 || pos > count-1) {
        return false;
    } else {
        if (pos == 0) {
            deleteFront(val);
        } else if (pos == count-1) {
            deleteRear(val);
        } else {
            Node* temp = front;
            for (int i = 0; i < pos - 1; i++) {
                temp = temp->next;
            }
            val = temp->next->val;
            Node *temp2 = temp->next;
            temp->next = temp2->next;
            delete temp2;
            count--;
        }
        return true;
    }
}

/**
     * @brief Insert a value at a specified position in the list. The valid pos is in the range of 0 to count.
     * The value will be inserted before the node at the specified position. if pos = 0, the value will be inserted
     * at the front of the list. if pos = count, the value will be inserted at the rear of the list.
     * @param pos: position to insert the value at.
     * @param val: value to insert.
     * @return true: if the value was inserted.
     * @return false: if the value was not inserted because pos is out of the range.
     */
bool LinkedList::insertAt(int pos, T val) {
    //cout << ">insertAt();";
    // check if the pos is valid first, then move the ptr to the rigth positon
    // consider the special case of inserting the first node and the last node
    if (pos < 0 || pos > count) {
        return false;
    }
    else if (pos == 0) {
        addFront(val);
    } else if (pos == count) {
        addRear(val);
    } else {
        Node *temp = front;
        for (int i = 0; i < pos-1; i++) {
            temp = temp->next;
        }
        Node *temp2 = new Node(val);
        temp2->next = temp->next;
        temp->next = temp2;
        count++;
        return true;
    }
    return true;
}

/**
 * @brief Copy Constructor to allow pass by value and return by value of a LinkedList
 * @param other LinkedList to be copied
 */
LinkedList::LinkedList(const LinkedList &other) {
    //cout << ">linkedList(const);";
    // Start with an empty list
    front = nullptr;
    rear = nullptr;
    count = 0;
    // Interate through the other list and add a new node to this list
    // for each node in the other list. The new node should have the same value as the other node.
    Node *ptr = other.front;
    while (ptr != nullptr) {
        addRear(ptr->val);
        ptr = ptr->next;
    }
}

/**
 * @brief Overloading of = (returns a reference to a LinkedList)
 * @param other LinkedList to be copied
 * @return reference to a LinkedList
 */
LinkedList &LinkedList::operator=(const LinkedList &other) {
    //cout << ">operator=();";
    if (this != &other) { // check if the same object
        // Delete all nodes in this list
        Node *temp = front;
        while (temp != nullptr) {
            Node *temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
        front = nullptr;
        rear = nullptr;
        count = 0;
        // Interate through the other list and add a new node to this list
        // Be sure to set the front and rear pointers to the correct values
        // Be sure to set the count to the correct value
        Node *ptr = other.front;
        while (ptr != nullptr) {
            addRear(ptr->val);
            ptr = ptr->next;
        }
    }
    return *this;
}

int LinkedList::search(const T& val) const {
    //cout << ">search();";
    Node *ptr = front;
    int pos = 0;
    while (ptr != nullptr) {
        if (ptr->val.id == val.id) {
            //val = ptr->val;
            return pos;
        }
        ptr = ptr->next;
        pos++;
    }
    return -1;
}

