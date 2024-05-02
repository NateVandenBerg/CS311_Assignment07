// You must complete the TODO parts and then complete LinkedList.cpp. Delete "TODO" after you are done.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "htable.h"
#include <stdlib.h>

using namespace std;

//PURPOSE of the Program: to test hashing to a doubly linked list with FIFO ordering.
int main() {
	cout << "\tTesting the Hash table of customer orders " << endl;
	HashTable table;
	cout << "Number of Hashtable buckets: " << table.numBuckets() << endl;
	cout << "The initial # of orders: " << table.numOrders() << endl << endl;

	cout << "Reading orders from file orders.txt" << endl;
	table.fillTable("orders.txt");
	cout << "The # of orders: " << table.numOrders() << endl << endl;

	// Read the orders in the "orders.txt" file
	Order order;
	vector<Order> orders;
	ifstream fin;
	fin.open("orders.txt");
	if (!fin.good()) throw "I/O error";
	while (fin >> order) {
		orders.push_back(order);//send each order into the orders vector
	}

	cout << "\nAll orders should be in the hash table\n";
	for (Order order : orders) {
		assert(table.findOrder(order.id, order));
	}

	// Create a vector of orders not in the hash table
	vector<Order> new_orders(10);
	new_orders[0] = Order(0, "Michael", 10);
	new_orders[1] = Order(1, "Christopher", 20);
	new_orders[2] = Order(2, "Jessica", 30);
	new_orders[3] = Order(3, "Matthew", 40);
	new_orders[4] = Order(4, "Ashley", 50);
	new_orders[5] = Order(5, "Jennifer", 60);
	new_orders[6] = Order(6, "Joshua", 70);
	new_orders[7] = Order(7, "Amanda", 80);
	new_orders[8] = Order(8, "Daniel", 90);
	new_orders[9] = Order(9, "David", 100);
	cout << "\nThese orders should not be in the hash table\n";
	for (Order order : new_orders) {
		assert(!table.findOrder(order.id, order));
	}

	cout << "\nInsert the new orders into the hash table\n";
	for (Order order : new_orders) {
		assert (table.insertOrder(order));
	}
	
	cout << "\nAll orders should be in the hash table now\n";
	for (Order order : new_orders) {
		assert (table.findOrder(order.id, order));
	}

	// Update the orders in the hash table
	cout << "\nUpdating the orders in the hash table\n";
	for (Order order : new_orders) {
		//Cannot insert because the order ID already exists
		assert (!table.insertOrder(order));
		//Update the order
		assert (table.findOrder(order.id, order));
		cout << "\nBefore update: " << order << "\t";
		order.amount = 150;
		assert (table.updateOrder(order));
		// Find the updated order
		assert (table.findOrder(order.id, order));
		cout << "\nAfter update: " << order << endl;
	}
	// Remove the new orders from the hash table
	for (Order order : new_orders) {
		assert (table.removeOrder(order.id));
	}

	// Test the rehashing
	cout << "\nRehashing the hash table\n";
	table.rehash(47);
	table.printTable();
	cout << "Number of Hashtable buckets: " << table.numBuckets() << endl;
	cout << "The # of Orders: " << table.numOrders() << endl;

	cout << "\nAll orders should be in the hash table\n";
	for (Order order : orders) {
		//cout << order << endl;
		assert (table.findOrder(order.id, order)); 
	}
	cout << "\nThese orders should not be in the hash table\n";
	for (Order order : new_orders) {
		assert (!table.findOrder(order.id, order));
	}
	
}


