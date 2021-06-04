#pragma once
#include "Includes.h"
#include "Observers.h"

class ServObserver {
public:
	virtual void itemModified(const Product&, const Product& oldP) = 0;
	virtual void itemRemoved(const Product&) = 0;
};

class ServObservable {
private:
	std::vector<ServObserver*> v;
public:
	void addObs(ServObserver* obs) {
		v.push_back(obs);
	}

	void removeObserv(ServObserver* obs) {
		for (auto it = v.begin(); it != v.end(); it++)
			if (*it == obs) {
				v.erase(it);
				return;
			}
	}

	void notifyRemove(const Product& p) {
		for (auto& it : v)
			it->itemRemoved(p);
	}

	void notifyModify(const Product& p, const Product& oldP) {
		for (auto& it : v) {
			try { it->itemModified(p, oldP); } catch (Exception& e) {}
		}
	}
};


class ServiceInventory: public ServObservable, public Observable {
private:
	friend Product;
	friend RepositoryInFile;
	std::vector< UndoAction* > undoList;
	DefaultRepository* repo;

public:
	ServiceInventory() = delete;
	ServiceInventory(RepositoryInFile&) noexcept;
	ServiceInventory(Repository&) noexcept;
	ServiceInventory(MapRepository&) noexcept;
	ServiceInventory(const ServiceInventory&) = delete;
	/*
	* The function adds a product in the inventory
	* Input data:	name - string
	*				type - string
	*				producer - string
	*				price - string
	* Output data: - 
	* Exceptions thrown: -
	*/
	void addProduct(string, string, string, string);
	/*
	* The function deletes a product from the inventory
	* Input data:	name - string
	*				type - string
	*				producer - string
	*				price - string
	* Output data: - 
	* Exceptions thrown: - 
	*/
	void deleteProduct(string, string, string);
	/*
	* The function modifies a product available in the invetory
	* Input data:	oldName - string
	*				oldType - string
	*				oldProducer - string
	*				name - string
	*				type - string
	*				producer - string
	*				price - string
	* Output data: -
	* Exceptions thrown: -
	*/
	void modifyProduct(string, string, string, string, string, string, string);
	/*
	* The function returns the elements available in the inventory
	* Input data: -
	* Output data:	temp - const vecotr<Product>&
	* Exceptions thrown: -
	*/
	const std::vector<Product>& getProducts();
	/*
	* The function searches for a product in the invetory
	* Input data:	name - string
	*				type - string
	*				producer - string
	* Output data: p - const Product&
	* Exceptions thrown:
	*/
	const Product searchProduct(string, string, string) const;
	/*
	* The function searches for a product in the invetory
	* Input data:	name - string
	*				type - string
	*				producer - string
	* Output data: index - const int
	* Exceptions thrown:
	*/
	const int searchProductIndex(string, string, string) const;
	/*
	* The function checks if the invetory is empty
	* Input data: -
	* Output data: true or false
	* Exceptions thrown: -
	*/
	bool empty() ;
	/*
	* The function sorts a std::vector with products by a certain criteria
	* Input data:	*compair - bool ServiceInventory::function(const Product&, const Product&)
	* Output data:	temp - const std::vector<Product>
	* Exceptions thrown: -
	*/
	const std::vector<Product> sortBy(bool (ServiceInventory::*compair)(const Product&, const Product&));

	const std::vector<Product> sortVectorByCriteria(std::vector<Product>, bool (ServiceInventory::* compair)(const Product&, const Product&));
	/*
	* The function filters the products based on a certain criteria
	* Input data:	criteria* - const strig (Product::function)()
	*				goal - const string
	* Output data:	temp - const std::vector<Product>
	* Exceptions thrown: -
	*/
	const std::vector<Product> filterProducts(const string (Product::*criteria)() const, const string);
	/*
	* The function compairs two products by their price
	* Input data:	elem1 - const Product&
	*				elem2 - const Product&
	* Output data:	true (if elem1.getPrice() < elem2.getPrice())
	*				false (otherwise)
	* Exceptions thrown: -
	*/
	bool compareByPrice(const Product& elem1, const Product& elem2) noexcept;
	/*
	* The function compairs two products by their name and type
	* Input data:	elem1 - const Product&
	*				elem2 - const Product&
	* Output data:	true (if elem1.getName() < elem2.getName? if(elem1.getType() < elem2.getType())
	*				false (otherwise)
	* Exceptions thrown: -
	*/
	bool compareByNameAndType(const Product& elem1, const Product& elem2);
	/*
	* The function compairs two products by their name
	* Input data:	elem1 - const Product&
	*				elem2 - const Product&
	* Output data:	true (if elem1.getName() < elem2.getName())
	*				false (otherwise)
	* Exceptions thrown: -
	*/
	bool compareByName(const Product& elem1, const Product& elem2);/*
	* The function shows a chart of the current types of the products
	* Input data:	-
	* Output data: std::map<std::string (type), int>
	* Exceptions thrown: Exception (if there are no products)
	*/
	const std::map<std::string, int> report() const;
	/*
	* The function undo the last operation made
	* Input data: -
	* Output data: -
	* Exceptions thrown: Exception (if there are no operations left to undo)
	*/
	void undoAction();
};

class ServiceCustomer: public ServObserver, public Observable {
private:
	friend class ShoppingCart;
	ShoppingCart& cart;
	ServiceInventory* serv;
public:
	ServiceCustomer() = delete;
	ServiceCustomer(ShoppingCart&, ServiceInventory&) noexcept;
	ServiceCustomer(ServiceCustomer&) = delete;

	void addProduct(const string);
	void emptyAll() noexcept;
	void deleteProduct(const string);
	const double getCurrentPrice() const noexcept;
	const std::vector<Product>& getProducts() const noexcept;
	void generateCart(string);
	void exportCart(const string, const string);
	void itemModified(const Product&, const Product&) override;
	void itemRemoved(const Product&) override;
};