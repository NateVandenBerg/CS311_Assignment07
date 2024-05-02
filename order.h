// A simple data structure representing customer orders

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Order {
public:
    int id;      // order ID
    string name;  // customer name
    float amount; // order amount

    // Default constructor
    Order() {
        id = 0;
        name = "";
        amount = 0.0;
    }

    // Constructor
    Order(int id, string name, float amount) {
        this->id = id;
        this->name = name;
        this->amount = amount;
    };
	
	void printOrder(){
		cout << "->|"<<id<<"-"<<name<<"-"<<amount<<"| ";
	}

    // Overloading of equality operator
    bool operator==(const Order &other) const {
        // Two orders are equal if they have the same ID
        return (id == other.id);
    }

    // This overloads cout for the Order object
    // This is a friend function 
    friend ostream &operator<<(ostream &, const Order & order);

    // This overloads cin for the Order object
    // This is a friend function
    friend istream &operator>>(istream &, Order & order);
};

  


