//CS311 htable.h
//INSTRUCTION:
//hashtable class - header file template 
//You should always comments to each function to describe its PURPOSE and PARAMETERS 
#pragma once
#include <vector>
#include "linkedlist.h"

using namespace std;
// =======================================================
// Your name: Nathaniel VandenBerg
// Compiler:  g++ 
// File type: header file  htable.h
//=======================================================


/**
 * @brief Implement a HashTable class using separate chaining
 */
class HashTable {
private:
    // The hash table is an array (vector) of linked lists
    vector<LinkedList> table;

    int table_size; // The size of the hash table

    // Hash function to map an order ID to key
    int hash(int id);
public:
    /**
     * @brief Constructor to create an empty hash table
     * @param size The size (number of buckets) of the hash table
     */
    HashTable(int size = 23);

    // destructor for your hash table
    ~HashTable();

    /**
     * @brief Fill the hash table with orders from a file
     */
    void fillTable(string file_name);

    /**
     * @brief Find an order by its ID
     * @param id: the order ID
     * @param order: the reference to stored found order (if found)
     * @return true if found, false otherwise
     */
     bool findOrder(int id, Order &order);

     /**
     * @brief Insert an order into the hash table. The order ID is used as the key.
     *        A order is inserted only if its ID isn't in the table
     * @param order Order to be inserted
     * @return true if inserted, false otherwise
     */
    bool insertOrder(const Order& order);
	
    /**
     * @brief Remove an order from the hash table. The order ID is used as the key.
     * @param int id: the order ID
     * @return true if removed, false otherwise
     */
    bool removeOrder(int id);

    /**
     * @brief Update an order in the table with given ID.
     *        An order is updated only if its ID is in the table
     * @param order: the updated order
     * @return true if updated, false otherwise
     */
    bool updateOrder(const Order& order);

    /**
     * @brief Print the hash table
     */
    void printTable();

    /**
     * @brief the number of orders in the hash table
     * @return int: the number of orders in the hash table
     */
    int numOrders() const;

    /**
     * @brief Get the number of buckets in the hash table
     * 
     * @return int the number of buckets in the hash table
     */
    int numBuckets() const {
        return table_size;
    }

    /**
     * @brief Rehash the hash table to a new size
     */
    void rehash(int newSize);
	
	//use this when table automatically increases in size based off of loadfactor
	bool loadFactor(); // used to determine if table size should be increased
	int findNextPrime();//used to find next table size
	bool isPrime(int nextPrime);//check if the value from findNextPrime() is infact a prime number
};

