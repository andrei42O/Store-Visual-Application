 #pragma once
#include "Includes.h"
using std::cin;
using std::cout;
class Console {
private:
	ServiceInventory& serv;
	ServiceCustomer& servCustomer;
	Validator& Inspektor;
public:
	Console() noexcept = default;
	Console(ServiceInventory&, ServiceCustomer&, Validator&) noexcept;
	Console(const Console&) = delete;

	void run();
	/*
	* The function reads the details of a product and adds it
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void add();
	/*
	* The function reads the details of a product and deletes it
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void remove();	
	/*
	* The function read the details of a product and modifies it
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void modify();	
	/*
	* The function read the details of a product and searches for it in the inventory
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void search() const;
	void showMenu() const;
	void showSortMenu() const;
	/*
	* The function shows the products that are currently in the invetory sorted by a certain criteria
	* Input data: -
	* Output data: -
	* Excepctions thrown: -
	*/
	void sortMethod() const;
	void filterMenu() const;
	/*
	* The function reads the details of a product shows products which have the same criterieas
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void filterMethod() const;
	/*
	* The function prints all Products
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void showProducts() const;
	/*
	* The function sends the user to the shopping menu
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void shopping();
	/*
	* The function prints the shopping Menu available
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void shoppingMenu() const;
	void report() const;
	/*
	* The function undo the last operation
	* Input data: -
	* Output data:-
	* Exceptions thrown: -
	*/
	void undo();
};