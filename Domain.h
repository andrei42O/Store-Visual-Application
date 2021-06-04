#pragma once
#include "Includes.h"
#include <iostream>
using std::string;
class Product {
private:
	string name;
	string type;
	string producer;
	double price;
public:
	Product() noexcept;
	Product(string, string, string, double);
	Product(const Product&);
	Product(Product&& p) = default;
	Product& operator=(const Product& p) = default;
	Product& operator=(Product&& p) = default;
	~Product() = default;

	const double getPrice() const noexcept;
	const string getPriceAsString() const;
	const string getName() const ;
	const string getType() const ;
	const string getProducer() const ;
	void setName(const string&);
	void setType(const string&);
	void setProducer(const string&);
	void setPrice(const double&) noexcept;
	friend std::ostream& operator<<(std::ostream&, const Product&) ;
	bool operator ==(const Product&) const noexcept;
	bool operator !=(const Product&) const noexcept;

};