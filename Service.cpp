#include "Includes.h"

ServiceInventory::ServiceInventory(RepositoryInFile& repo) noexcept: repo{ &repo }{
}

ServiceInventory::ServiceInventory(Repository& repo) noexcept :repo{ &repo } {
}

ServiceInventory::ServiceInventory(MapRepository& repo) noexcept :repo{ &repo } {
}

void ServiceInventory::addProduct(string name, string type, string producer, string price) {
	Validator Inspector;
	Inspector.check(name, type, producer, price);
	Product p{ name, type, producer, stod(price) };
	repo->store(p);
	undoList.push_back(new UndoAdd{ p, repo });
	notify();
}

void ServiceInventory::deleteProduct(string name, string type, string producer) {
	Validator Inspector;
	Inspector.check(name, type, producer, "1");
	Product p{ name, type, producer, 1 }, oldProduct = repo->getElement(repo->search(p));
	notifyRemove(p);
	repo->remove(p);
	undoList.push_back(new UndoRemove{ oldProduct, repo });
	notify();
}

void ServiceInventory::modifyProduct(string oldName, string oldType, string oldProducer, string name, string type, string producer, string price) {
	Validator Inspector;
	Inspector.check(name, type, producer, price);
	Product p{ name, type, producer, stod(price) };
	const int position = repo->search(Product{ oldName, oldType, oldProducer, 10 });
	try {
		if (repo->search(p) == position)
			throw RepoException("");
	}
	catch (RepoException) {
		Product oldP = repo->getElement(position);
		repo->modify(p, position);
		// daca nu are nimic de modificat, nu modifica
		try { notifyModify(p, oldP); } catch (RepoException& e) { if (e.getMessage() == "Invalid position!\n") throw RepoException(e.getMessage()); }
		undoList.push_back(new UndoModify{ p, oldP, repo });
		notify();
		return;}
	throw RepoException("Produsul este deja in stock!\n"); }


const std::vector<Product>& ServiceInventory::getProducts() {
	return repo->getAll();
}

const Product ServiceInventory::searchProduct(string name, string type, string producer) const{
	Validator Inspector;
	Inspector.check(name, type, producer, "1");
	Product p{ name, type, producer, 1 };
	const int position = repo->search(p);
	auto it = repo->getElement(position);
	return it;
}

const int ServiceInventory::searchProductIndex(string name, string type, string producer) const {
	Validator Inspector;
	Inspector.check(name, type, producer, "1");
	Product p{ name, type, producer, 1 };
	return repo->search(p);
}

bool ServiceInventory::empty() {
	return repo->size() == 0;
}

const std::vector<Product> ServiceInventory::sortBy(bool (ServiceInventory::*compair)(const Product&, const Product&)){
	std::vector<Product> temp = getProducts();
	if (compair != nullptr) {
		sort(temp.begin(), temp.end(), [this, &compair](const Product& p1, const Product& p2) {return (this->*compair)(p1, p2); });
	}
	return temp;
}

const std::vector<Product> ServiceInventory::sortVectorByCriteria(std::vector<Product> temp, bool (ServiceInventory::* compair)(const Product&, const Product&)) {
	if (compair != nullptr) {
		sort(temp.begin(), temp.end(), [&](const Product& p1, const Product& p2) {return (this->*compair)(p1, p2); });
	}
	return temp;
}

const std::vector<Product> ServiceInventory::filterProducts(const string(Product::*criteria)() const, const string goal) {
	std::vector<Product> temp(repo->size());
	if (criteria != nullptr) {
		const std::vector<Product>& tempProducts = getProducts();
		auto it = std::copy_if(tempProducts.begin(), tempProducts.end(), temp.begin(), [&criteria, &goal](const Product& p) noexcept{return (p.*criteria)() == goal; });
		temp.resize(std::distance(temp.begin(), it));
	}
	return temp;
}

bool ServiceInventory::compareByPrice(const Product& elem1, const Product& elem2) noexcept {
	return elem1.getPrice() < elem2.getPrice();
}

bool ServiceInventory::compareByNameAndType(const Product& elem1, const Product& elem2) {
	return elem1.getName() < elem2.getName();
}

bool ServiceInventory::compareByName(const Product& elem1, const Product& elem2) {
	return elem1.getName() < elem2.getName();
}

void ServiceInventory::undoAction() {
	if (!undoList.size())
		throw Exception("Nu exista actiuni de refacut!\n");
	UndoAction* lastAction = undoList.back();
	if (lastAction != nullptr) {
		if (lastAction->getType() == "modify") {
			std::vector<Product> temp = lastAction->getArguments();
			notifyModify(temp.at(1), temp.at(0));
		}
		else if (lastAction->getType() == "remove") {
			std::vector<Product> temp = lastAction->getArguments();
			notifyRemove(temp.at(0));
		}
		lastAction->doUndo();
		notify();
		undoList.pop_back();
		delete lastAction;
	}
}

ServiceCustomer::ServiceCustomer(ShoppingCart& ot, ServiceInventory& serv) noexcept: cart{ ot }, serv{ &serv }{
	this->serv->addObs(this);
}

void ServiceCustomer::addProduct(const string name) {
	Validator Inspektor;
	Inspektor.check(name, "a", "b", "1");
	cart.store(serv->searchProduct(name, "smeker", "frumos"));
	//cart.store(repo->getElement(repo->search(Product{name, "smecher", "frumos", 100000})));
	notify();
}

void ServiceCustomer::deleteProduct(const string name) {
	Validator Inspektor;
	Inspektor.check(name, "a", "b", "1");
	cart.remove(serv->searchProduct(name, "smeker", "frumos"));
	//cart.remove(repo->getElement(repo->search(Product{ name, "smecher", "frumos", 100000 })));
	notify();
}

void ServiceCustomer::emptyAll() noexcept{
	cart.emptyCart();
	notify();
}

const double ServiceCustomer::getCurrentPrice() const noexcept{
	return cart.getCurrentPrice();
}

const std::vector<Product>& ServiceCustomer::getProducts() const noexcept{
	return cart.getAll();
}

void ServiceCustomer::generateCart(string howMuch) {
	cart.generateCart(stoi(howMuch), serv->getProducts());
	notify();
}

void ServiceCustomer::exportCart(const string type, const string fileName) {
	cart.exportToFile(type, fileName);
	cart.emptyCart();
	notify();
}

void ServiceCustomer::itemModified(const Product& p, const Product& oldP){
	for(auto& it: cart.search(oldP))
		cart.modify(p, it);
	notify();
}

void ServiceCustomer::itemRemoved(const Product& p) {
	while (1) {
		try { deleteProduct(p.getName()); }
		catch (Exception& e) { break; }
	}
	notify();
}

const std::map<std::string, int> ServiceInventory::report() const {
	std::map<std::string, int> DTO;
	const std::vector<Product>& temp = repo->getAll();
	if (!temp.size())
		throw Exception("Nu exista produse!\n");
	for (const auto& it : temp)
		if (DTO.find(it.getType()) == DTO.end())
			DTO[it.getType()] = 1;
		else
			DTO[it.getType()]++;
	return DTO;
}