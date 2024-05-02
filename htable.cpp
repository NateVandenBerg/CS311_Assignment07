// ====================================================
// Your name: Nathaniel VandenBerg
// Complier:  g++
// File type: htable.cpp implementation file
//=====================================================

#include "htable.h"
#include<fstream>
#include <cassert>


/**
 * @brief Constructor to create an empty hash table
 * @param size The number of buckets in the hash table
 */
HashTable::HashTable(int size) {
	//cout << ">HashTable(int);";
	table_size = size;//default size is 23
	table = vector<LinkedList>(table_size);
}

/**
 * @brief Destructor
 */
HashTable::~HashTable() {
	cout << "\n\n>~HashTable();\n";
	table.clear();//clear out the vector
}
/**
 * @brief  Get the hash key of the order
 * @return int The hashed index of the order ID
 */
int HashTable::hash(int id) {
	//cout << ">hash();="<< id % table_size << "| ";
	return id % table_size;
}

/**
 * @brief Find an order by its ID
 * @param id: the order ID
 * @param order: the reference to stored found order (if found)
 * @return true if found, false otherwise
 */
bool HashTable::findOrder(int id, Order& order) {
	cout << "\n>findOrder();";
	cout << order;
	if (numOrders() == 0) {//if table is empty return false
		return false;
	}
	else{
		int hashVal = hash(id);//vector index value
		Order toFind = order;//copy of object Order
		toFind.id = id;//update id to new value passed to function
		int pos = table[hashVal].search(toFind);//search the LL at the vector index
		if (pos == -1) {//if not in LL
			cout << "->fail";
			return false;
		}
		else
			return true;
	}
}

/**
 * @brief Insert an order into the hash table. The order ID is used as the key.
 * A order is inserted only if its ID isn't in the table
 * @return true if inserted, false otherwise
 */
bool HashTable::insertOrder(const Order& order) {
	//cout << ">insertOrder()"; 
	cout << order << endl;
	int hashVal = hash(order.id);//brief function to find order location in array

	//use this when table automatically increases in size based off of loadfactor
	//!!! warning !!! 
	//this has causes problems when trying to rehash the table to a specific size
	/*if (loadFactor()) {//check the order count to bucket ratio
		int newSize = findNextPrime();//get next prime value for new table size
		rehash(newSize);//if it greater than the loadFactor (.3) it should resize the vector
	}*/

	if (table[hashVal].search(order) == -1) {//If the bucket is empty or the ID is not a duplicate
		table[hashVal].addRear(order);//add to the rear
		return true;
	}
	return false;
}

/**
 * @brief Load orders from a file
 * 
 * @param file_name The name of the file to load
 */
void HashTable::fillTable(string file_name) {
	// Open the file to read
	//cout << ">fillTable();\n";
	ifstream fin;
	fin.open(file_name.c_str());
	if (!fin) {
		cout << "Error opening file " << file_name << endl;
		return;
	}
	Order order;//object Order created
	while (fin >> order) {//while there not at the end of the file copy info to order
		//cout << endl << order;
		insertOrder(order);//insert into table vector
	}
	rehash(table_size);//use this when table automatically increases in size based off of loadfactor
	printTable();
}

// 
/**
 * @brief Remove an order from the hash table. The order ID is used as the key.
 *        A order is removed only if its ID is in the table
 * 
 * @param id 
 * @return true if the order is removed, false otherwise
 */ 
bool HashTable::removeOrder(int id) {
	cout << "\n>removeOrder();";//cout << " id: " << id << endl;
	if (numOrders() == 0) {//return false if vectro is empty
		return false;
	}
	else {
		int hashVal = hash(id);//brief function to find order location in array
		Order delOrder;//Order object must be created to reference in search
		delOrder.id = id;//update Order X.id to id sent to function
		int pos = table[hashVal].search(delOrder);//search by ID value
		if (pos == -1) {
			return false;
		}
		else {
			table[hashVal].deleteAt(pos, delOrder);
			//delOrder.printOrder();
			cout << delOrder;
			return true;
		}
	}
}

// Display the hash table
void HashTable::printTable() {
	cout << "\n\n>printTable();\n";

	for (int i = 0; i < table_size; i++) {
		cout << "Bucket " << i << ": ";
		table[i].displayAll();
	}
}

/**
 * @brief Get the total number of orders in the hash table
 * 
 * @return int The number of orders in the hash table
 */
int HashTable::numOrders() const {
	//cout << ">numOrders();";
	int orderCount = 0;
	int i = 0;
	for (auto j : table) {
		orderCount += table[i].length();
		i++;
	}
	//cout << " = " << orderCount << "| ";
	return orderCount;
}

// Update the order in the hash table
/**
 * @brief Update a order in the hash table. The order ID is used as the key.
 * 		  A order is updated only if its ID is in the table
 * @param order the new order that is used to update the old order 
 * @return true if the order is updated, false otherwise
 */
bool HashTable::updateOrder(const Order& order) {
	//cout << "\n>updateOrder();\n";
	if (numOrders() == 0) {
		return false;
	}
	else {
		int hashVal = hash(order.id);//brief function to find order location in array
		int pos = table[hashVal].search(order);//searh LL for the order ID
		if (pos == -1) {//-1 means not found
			return false;//return false if not found
		}
		else {//if the seached for value is found...
			Node* temp = table[hashVal].getNode(pos);//create a node pointer to the found order
			temp->val = order;//update the node value to the updated order
			return true;
		}
	}
}

/**
 * @brief Rehash the hash table to a new size. The orders are rehashed to the new table
 * 
 * @param new_size The new number of buckets in the hash table
 */
void HashTable::rehash(int newSize) {
	//cout << "\n\n>rehash();";
	HashTable* newTable = new HashTable(newSize);
	//cout << " new Size = " << newSize <<", tablesize = "<<newTable->table_size<< "\n\n";
	int i = 0;
	for (auto j : table) {//traverse through vector
		cout << endl << i << endl;
		while (!table[i].isEmpty()) {//while the LL at index i is not empty
			Order temp;//create temp Order object
			table[i].deleteFront(temp);//delete front node and copy deleted info to temp
			cout << " <=temp=-";
			newTable->insertOrder(temp);//insert the temp into the new table
		}
		i++;
	}
	//newTable->printTable();
	table_size = newSize;//update table size to new size
	table = newTable->table;//copy the table to the new table vector
	//printTable();
	delete newTable;//delete newTable to make space
	//cout << "\n\n>rehash(); COMPLETE\n\n";
}

//use this when table automatically increases in size based off of loadfactor

bool HashTable::loadFactor() {// used to determine if table size should be increased
	//cout << ">loadFactor();";
	float factorLimit = .6;
	float check = ((float)numOrders() / (float)table_size);
	//cout << " = " << check << "| ";
	if (check > factorLimit) {
		return true;
	}
	else
		return false;
}

//use this when table automatically increases in size based off of loadfactor
int HashTable::findNextPrime() {//used to find next table size
	//cout << ">findNextPrime();";
	int nextPrime = 2 * table_size;
	bool found = false;
	//loop continuously until isPrime returns true for a number above n
	while (!found) 	{
		nextPrime++;
		if (isPrime(nextPrime))
			found = true;
	}

	return nextPrime;
}

//use this when table automatically increases in size based off of loadfactor
//given a number n, determine if it is prime
//check if the value from findNextPrime() is infact a prime number
bool HashTable::isPrime(int nextPrime) {
	//cout << ">isPrime();";
	//loop from 2 to n/2 to check for factors
	for (int i = 2; i <= nextPrime / 2; i++) 	{
		if (nextPrime % i == 0)     //found a factor that isn't 1 or n, therefore not prime
			return false;
	}

	return true;
}


