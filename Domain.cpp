#include "Includes.h"

using std::string;

Product::Product(string name, string type, string producer, double price) : name{ name }, type{ type }, producer{ producer }, price{ price }{
}

Product::Product(const Product& ot) : name{ ot.name }, type{ ot.type }, producer{ ot.producer }, price{ ot.price }{
}

Product::Product() noexcept : price{ 0 } {
}

const double Product::getPrice() const noexcept{
	return price;
}

const string Product::getPriceAsString() const {
	string answer = std::to_string(price);
	for (size_t i = answer.size() - 1; i >= 0 && answer.at(i) != ' ' && answer.at(i) == '0'; i--)
		answer.pop_back();
	if (answer.at(answer.size() - 1) == '.')
		answer.pop_back();
	return answer;
}

const string Product::getName() const {
	return name;
}

const string Product::getType() const {
	return type;
}

const string Product::getProducer() const {
	return producer;
}

void Product::setName(const string& newName){
	this->name = newName;
}

void Product::setType(const string& newType) {
	this->type = newType;
}

void Product::setProducer(const string& newProducer) {
	this->producer = newProducer;
}

void Product::setPrice(const double& newPrice) noexcept{
	this->price = newPrice;
}

bool Product::operator ==(const Product& p) const noexcept{
	return (*this).name == p.name;
}

bool Product::operator !=(const Product& p) const noexcept {
	return this->name != p.name;
}

std::ostream& operator<<(std::ostream& os, const Product& p){
	os << "Nume: " << p.getName() << "\nTip: " << p.getType() << "\nProducator: " << p.getProducer() << "\nPret: " << p.getPrice() << "\n";
	return os;
}