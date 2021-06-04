#pragma once
#include "Includes.h"

class DefaultRepository{
public:
	DefaultRepository() = default;
	DefaultRepository(const DefaultRepository&) = delete;
	DefaultRepository(DefaultRepository&&) = delete;
	DefaultRepository& operator=(DefaultRepository&) = delete;
	DefaultRepository& operator=(DefaultRepository&&) = delete;
	virtual ~DefaultRepository() = default;

	virtual void store(const Product&) = 0;

	virtual void remove(const Product&) = 0;

	virtual void modify(const Product&, const int) = 0;

	virtual int search(const Product&) = 0;

	virtual int size() = 0;

	virtual const Product& getElement(int) = 0;

	virtual const std::vector<Product>& getAll() = 0;

	

};

class Repository: public DefaultRepository {
protected:
	std::vector<Product> products;
	friend Product;
public:
	Repository() noexcept;
	Repository(const Repository&) = delete;
	Repository(Repository&&) = delete;
	Repository& operator=(Repository&) = delete;
	Repository& operator=(Repository&&) = delete;
	virtual ~Repository() = default;
	/*
	* The function stores a product in the invetory
	* Input data: p - const Product&
	* Output data: -
	* Exceptions thrown: RepoException (if the product already exists in the inventory)
	*/
	virtual void store(const Product&) override;
	/*
	* The function removes a product form the invetory
	* Input data: p - const Porduct&
	* Output data: - 
	* Exceptions thrown: RepoException(if the product provided doens't exists in the invetory)
	*/
	virtual void remove(const Product&) override;
	/*
	* The function modifies the quantity of a product found in the inventory
	* Input data: p - const Product&
	* Output data: -
	* Exceptions thrown: RepoException(if the product doesn't exists in the invetory)
	*/
	virtual void modify(const Product&, const int) override;
	/*
	* The function searches if a product and provides it's position in the invetory
	* Input data: p - const Product&
	* Output data: position - integer 
	* Exceptions thrown: RepoException (if the give product doesn't exist in the invetory)
	*/
	virtual int search(const Product&) override;
	/*
	* The function provides the size of the actual invetory
	* Input data: -
	* Output data: size - integer
	* Exceptions thrown: -
	*/
	virtual int size() override;
	/*
	* The function provides the element from a given position
	* Input data: position - integer
	* Output data: p - const Product&
	* Exceptions thrown: RepoException (if the position is invalid)
	*/
	virtual const Product& getElement(int);
	/*
	* The function provides all the available products in the invetory
	* Input data: -
	* Output data: v - std::vector<Product>
	* Exceptions thrown: -
	*/
	virtual const std::vector<Product>& getAll();

};

class RepositoryInFile : public Repository {
private:	
	string fileName;
	void appendToFile(const Product&);
	void storeToFile();
	void loadFromFile();

public:

	RepositoryInFile(const string&);
	RepositoryInFile(const RepositoryInFile&) = delete;
	RepositoryInFile(RepositoryInFile&&) = delete;
	RepositoryInFile& operator=(RepositoryInFile&) = delete;
	RepositoryInFile& operator=(RepositoryInFile&&) = delete;
	~RepositoryInFile() noexcept {};
	/*
	* The function stores a product in the invetory
	* Input data: p - const Product&
	* Output data: -
	* Exceptions thrown: RepoException (if the product already exists in the inventory)
	*/
	void store(const Product&) override;
	/*
	* The function removes a product form the invetory
	* Input data: p - const Porduct&
	* Output data: -
	* Exceptions thrown: RepoException(if the product provided doens't exists in the invetory)
	*/
	void remove(const Product&) override;
	/*
	* The function modifies the quantity of a product found in the inventory
	* Input data: p - const Product&
	* Output data: -
	* Exceptions thrown: RepoException(if the product doesn't exists in the invetory)
	*/
	void modify(const Product&, const int) override;
	/*
	* The function searches if a product and provides it's position in the invetory
	* Input data: p - const Product&
	* Output data: position - integer
	* Exceptions thrown: RepoException (if the give product doesn't exist in the invetory)
	*/
	int search(const Product&) override;
	/*
	* The function provides the size of the actual invetory
	* Input data: -
	* Output data: size - integer
	* Exceptions thrown: -
	*/
	int size() override;
	/*
	* The function provides the element from a given position
	* Input data: position - integer
	* Output data: p - const Product&
	* Exceptions thrown: RepoException (if the position is invalid)
	*/
	const Product& getElement(int) override;
	/*
	* The function provides all the available products in the invetory
	* Input data: -
	* Output data: v - std::vector<Product>
	* Exceptions thrown: -
	*/
	const std::vector<Product>& getAll() override;
};

class MapRepository : public DefaultRepository {
private:
	std::unordered_map<std::string, Product> m;
	std::vector <Product> getVector;
	void pacanica();
public:
	MapRepository() = default;
	MapRepository(const MapRepository&) = delete;
	MapRepository(MapRepository&&) = delete;
	MapRepository& operator=(MapRepository&) = delete;
	MapRepository& operator=(MapRepository&&) = delete;
	~MapRepository() noexcept = default;

	void store(const Product&) override;

	void remove(const Product&) override;

	void modify(const Product&, const int) override;

	int search(const Product&) override;

	int size() override;

	const Product& getElement(int) override;

	const std::vector<Product>& getAll() override;
};