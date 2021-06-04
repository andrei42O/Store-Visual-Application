#pragma once
#include "Includes.h"
class ShoppingCart{
private:
	std::vector<Product> products;
	double currentPrice;
public:
	ShoppingCart() noexcept{
		currentPrice = 0;
	}
	ShoppingCart(const ShoppingCart& ot) = delete;

	/*
	* The function empties the cart
	* Input data: -
	* Output data: -
	* Exceptions thrown: -
	*/
	void emptyCart() noexcept;
	/*
	* The function gets the current price of the shopping cart
	* Input data: -
	* Output data: ret - const double
	* Exceptions thrown: -
	*/
	const double getCurrentPrice() const noexcept;
	/*
	* The function returns the number of products in the basket
	* Input data: -
	* Output data: size - integer
	* Exceptions thrown: -
	*/
	int size() const noexcept ;
	/*
	* The function stores adds a product in the basket
	* Input data: p - const Product&
	* Output data: -
	* Exceptions thrown: -
	*/
	void store(const Product& p) ;
	void modify(const Product& p, const int poz);
	const std::vector<int> search(const Product& p);
	void remove(const Product& p);
	/*
	* The function generates a basket with random items
	* Input data:	howMuch - const integer
	*				repo - const Repository&
	* Output data:	-
	* Exceptions thrown: Exception (if there are no items in the repository)
	*/
	void generateCart(const int, const std::vector<Product>&);
	/*
	* The function returns all the products in the cart
	* Input data: -
	* Output data: const std::vector<Product>&
	* Exceptions thrown:
	*/
	const std::vector<Product>& getAll() const noexcept ;
	/*
	* The function exports the current basket items to a file
	* Input data:	type - const string (file type)
	*				fileName - const string (file name)	
	* Output data:	-
	* Exceptions thrown: Exception (if the export could not be done)
	*/
	void exportToFile(const string, const string);
};