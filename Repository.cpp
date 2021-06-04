#include "Includes.h"

Repository::Repository() noexcept = default;

void Repository::store(const Product& p) {
	try {
		search(p);
	}
	catch (RepoException&) {
		products.push_back(p);
		return;}
	throw RepoException("Produsul este deja in stock!\n");
}

void Repository::remove(const Product& p) {
	auto it = std::find_if(products.begin(), products.end(), [&p](const Product& prod) noexcept {return p == prod; });
	if(it == products.end())
		throw RepoException("Produsul nu este in stock!\n");
	products.erase(it);
}

void Repository::modify(const Product& p, const int poz) {
	products.emplace(products.begin() + poz, p);
	products.erase(products.begin() + poz + 1);
}

int Repository::search(const Product& p) {
	int k = 0;
	for (const auto& it : products) {
		if (it == p)
			return k;
		k++;
	}
	throw RepoException("Produsul nu este in stock!\n");
}

int Repository::size() {
	return (int)products.size();
}

const Product& Repository::getElement(int position){
	if (position < 0 || position > size())
		throw RepoException("Pozitie invalida!\n");
	return products.at(position);
}

const std::vector<Product>& Repository::getAll(){
	return products;
}

RepositoryInFile::RepositoryInFile(const string& fileName) : Repository(), fileName{ fileName }{
	loadFromFile(); 
}

void RepositoryInFile::appendToFile(const Product& p) {
	std::ofstream g;
	g.open(fileName, std::ios::app);
	if (!g.is_open()) { throw Exception("Eroare la deschiderea fisierului pentru adaugare!\n"); }
	g << p.getName() << "," << p.getType() << "," << p.getProducer() << "," << p.getPrice() << "\n";
	g.close();
}

void RepositoryInFile::storeToFile() {
	std::ofstream g;
	g.open(fileName, std::ios::out | std::ios::trunc);
	if (!g.is_open()) { throw Exception("Eroare la deschiderea fisierului pentru adaugare!\n"); }
	for (auto it: products)
		g << it.getName() << "," << it.getType() << "," << it.getProducer() << "," << it.getPrice() << "\n";
	g.close();
}

void RepositoryInFile::loadFromFile() {
	std::ifstream f;
	f.open(fileName, std::ios::in);
	if (!f.is_open()) { throw Exception("Eroare la deschiderea fisierului pentru citire!\n"); }
	products.clear();
	string linie;
	std::vector<string> temp;
	while (std::getline(f, linie)) {
		int first = 0, last = 0;
		for (auto it = linie.begin(); it != linie.end(); it++) {
			if (*it == ',') {
				temp.push_back(linie.substr(first, last - first));
				first = last + 1;
			}
			last++;
		}
		temp.push_back(linie.substr(first, last));
		Product p{ temp.at(0), temp.at(1), temp.at(2), stod(temp.at(3)) };
		auto it3 = std::find_if(products.begin(), products.end(), [p](const Product& currentP) noexcept {return p == currentP; });
		if (products.begin() == products.end() || it3 == products.end()) { products.push_back(p); }
		temp.clear();
	}
	//for (auto it : products)
	//	cout << it << '\n';
	f.close();
}

void RepositoryInFile::store(const Product& p) {
	Repository::store(p);
	appendToFile(p);
}

void RepositoryInFile::remove(const Product& p) {
	Repository::remove(p);
	storeToFile();
}

void RepositoryInFile::modify(const Product& p, const int poz) {
	Repository::modify(p, poz);
	storeToFile();
}

int RepositoryInFile::search(const Product& p) {
	loadFromFile();
	return Repository::search(p);
}

int RepositoryInFile::size(){
	loadFromFile();
	return (int)products.size();
}

const Product& RepositoryInFile::getElement(int poz) {
	loadFromFile();
	return Repository::getElement(poz);
}

const std::vector<Product>& RepositoryInFile::getAll() {
	loadFromFile();
	return products;
}

//void MapRepository::pacanica() {
	//std::random_device dev;
	//std::mt19937 rng(dev());
	//std::uniform_int_distribution<std::mt19937::result_type> const dist(1, 6);
	//const int what = dist(rng) % 100;
	//const int newProb = dist(rng) % 100;
//	cout << what << ' ' << newProb << '\n';
//	if (what > newProb)
//		throw RepoException("Mai baga o fisa bro");
//}

void MapRepository::store(const Product& p) {
	//pacanica();
	if (m.find(p.getName()) == m.end()) {
		m[p.getName()] = p;
		return;
	}
	throw RepoException("Element existent!\n");}

void MapRepository::remove(const Product& p) {
	//pacanica();
	if (m.find(p.getName()) != m.end()) {
		m.erase(p.getName());
		return;
	}
	throw RepoException("Element inexistent!\n");
}

void MapRepository::modify(const Product& p, const int poz) {
	//pacanica();
	int counter = 0;
	auto it = m.begin();
	for (; counter != poz && it != m.end(); it++, counter++);
	auto nh = m.extract((*it).second.getName());
	nh.key() = p.getName();
	m[p.getName()] = p;
}

int MapRepository::search(const Product& p) {
	//pacanica();
	int poz = 0;
	for (const auto& it : m) {
		if (it.first == p.getName())
			return poz;
		poz++;
	}
	throw RepoException("Produsul nu este in stock!\n");
}

int MapRepository::size() {
	return (int)m.size();
}

const Product& MapRepository::getElement(int poz) {
	//pacanica();
	int counter = 0;
	for (const auto& it : m) {
		if (counter == poz)
			return it.second;
		counter++;
	}
	throw RepoException("Pozitie invalida!\n");
}

const std::vector<Product>& MapRepository::getAll() {
	//pacanica();
	getVector.clear();
	for (auto it : m) 
		getVector.push_back(it.second);
	//if (getVector.size())
		return getVector;
	//throw RepoException("Nu exista produse!\n");
}