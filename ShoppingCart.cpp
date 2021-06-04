#include "Includes.h"

void ShoppingCart::emptyCart() noexcept {
	while (products.size())
		products.pop_back();
	currentPrice = 0;
}

void ShoppingCart::store(const Product& p) {
	products.push_back(p);
	currentPrice += p.getPrice();
}

void ShoppingCart::modify(const Product& p, const int poz)
{
	if (products.empty()) { throw RepoException("Nu exista produse in cos!\n"); }
	if (poz < 0 || poz >= products.size()) { throw RepoException("Invalid position!\n"); }
	currentPrice -= products.at(poz).getPrice();
	currentPrice += p.getPrice();
	products.emplace(products.begin() + poz, p);
	products.erase(products.begin() + poz + 1);
}

const std::vector<int> ShoppingCart::search(const Product& p)
{
	std::vector<int> temp;
	int k = 0;
	for (const auto& it : products) {
		if (it == p)
			temp.push_back(k);
		k++;
	}
	if (temp.size())
		return temp;
	throw RepoException("There's no such product in the shopping cart!\n");}

void ShoppingCart::remove(const Product& p) {
	if (products.empty())
		throw RepoException("Nu exista produse in cos!\n");
	auto it = std::find_if(products.begin(), products.end(), [&p](const Product& prod) {return p == prod; });
	if (it == products.end()) { throw RepoException("Nu exista acest produs in cos!\n"); }
	currentPrice -= (*it).getPrice();
	products.erase(it);
}

int ShoppingCart::size() const noexcept {
	return products.size();
}

const double ShoppingCart::getCurrentPrice() const noexcept {
	return currentPrice;
}

const std::vector<Product>& ShoppingCart::getAll() const noexcept {
	return products;
}

void ShoppingCart::generateCart(const int howMuch, const std::vector<Product>& repo) {
	if (repo.size()) {
		const int limit = repo.size();
		qDebug() << howMuch;
		if (limit < howMuch || !howMuch) {
			throw Exception("Nu exista suficiente produse!\n");
		}
		emptyCart();
		for (int i = 0; i < howMuch; i++) {
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> const dist(1, 6);
			const int position = dist(rng) % limit;
			store(repo.at(position));
		}
	}
}

void ShoppingCart::exportToFile(const string sentType, const string fileName) {
	string type = sentType;
	std::for_each(type.begin(), type.end(), [](char& c) { if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a'; });
	/// CSV type
	if (type == "csv") {
		std::ofstream out("C:\\Users\\andre\\Desktop\\" + fileName + ".csv");
		if (!out.is_open()) { throw Exception("Nu s-a putut face exportul...\n"); }
		out << "Nume Produs, Tip, Producator, Pret" << std::endl;
		std::for_each(products.begin(), products.end(), [&out](const Product& p) {
			out << p.getName() << ", ";
			out << p.getType() << ", ";
			out << p.getProducer() << ", ";
			out << p.getPrice() << std::endl;
			});
		out << std::endl << ", , Pret Total:," << currentPrice << std::endl;
		out.close();
		return;
	}
	/// HTML type
	if (type == "html") {
		std::ofstream out("C:\\Users\\andre\\Desktop\\" + fileName + ".html");
		if (!out.is_open()) { throw Exception("Nu s-a putut face exportul...\n"); }
		out << "<!DOCTYPE html><html><head><h1>Marele cos de cumparaturi</h1></head><body>";
		std::for_each(products.begin(), products.end(), [&out](const Product& p) {
			out << "<p><span style='font-weight: bold'>Nume: " << p.getName();
			out << " Tip: " << p.getType();
			out << " Producator: " << p.getProducer();
			out << " Pret: " << p.getPrice();
			out << "</span></p>";
			});
		out << "<br><br><p><span style='font-weight: bold'>Pret total: " << currentPrice << "</span></p></body></html>";
		out.close();
		return;
	}
	throw Exception("Tip de fisier invalid!\n");}