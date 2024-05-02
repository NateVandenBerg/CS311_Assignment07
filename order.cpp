// CS311 Yoshii S22 - el_t for HW8 Hash Table
// Element type of a list node is defined here
// el_t can be changed by the client to fit its needs
// Edit ** parts
//  NEVER delete my comments!!
//----------------------------------------------------

#include "order.h"

// overload outs << for Order
ostream& operator<<(ostream& os, const Order& order)
{  
	os << "->|" << order.id << "-" << order.name << "-" << order.amount << "| ";
  return os;  
}  

// overload ins >> for Order
istream& operator>>(istream& is, Order& order)
{  
  is >> order.id >> order.name >> order.amount;
  return is;  
}