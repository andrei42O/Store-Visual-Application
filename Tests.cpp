#include "Includes.h"

void testDomain() {
	Product p{"Laptop", "Ultrabook", "Lenovo", 9999.99};
	assert(p.getName() == "Laptop");
	assert(p.getType() == "Ultrabook");
	assert(p.getProducer() == "Lenovo");
	assert(p.getPrice() == 9999.99);
	Product temP{ "Termos", "Rosu", "Altex", 40 };
	assert(p != temP);
	p.setName("Monitor");
	p.setType("Eye Friendly");
	p.setProducer("Asus");
	p.setPrice(569.99);
	assert(p.getName() == "Monitor");
	assert(p.getType() == "Eye Friendly");
	assert(p.getProducer() == "Asus");
	assert(p.getPrice() == 569.99);
	assert(p.getPriceAsString() == "569.99");
	Product p2;
	p2 = p;
	assert(p == p2);
	std::ostringstream os;
	os << p2;
	assert(os.str() == "Nume: Monitor\nTip: Eye Friendly\nProducator: Asus\nPret: 569.99\n");
}

void testRepo() {
	Repository repoProducts;
	assert(repoProducts.size() == 0);
	assert(repoProducts.getAll().size() == 0);

	Product p1{ "Turbina", "1.9 TDI", "Volkswagen", 1800 };
	Product p2{ "Scaun", "Lemn", "Ikeea", 60 };
	Product p3{ "Tractor", "9R 490", "John Deere", 1969385.3 };

	repoProducts.store(p1);
	assert(repoProducts.size() == 1);
	repoProducts.store(p2);
	assert(repoProducts.size() == 2);
	repoProducts.store(p3);
	assert(repoProducts.size() == 3);

	std::vector<Product> temp;
	temp.push_back(p1);
	temp.push_back(p2);
	temp.push_back(p3);

	assert(repoProducts.getAll() == temp);

	assert(repoProducts.search(p2) == 1);
	try { repoProducts.search(Product{ "nu stiu", "da", "poate", 420 }); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul nu este in stock!\n");
	}

	try { repoProducts.store(p1); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul este deja in stock!\n");
	}

	try { repoProducts.remove(Product{ "nu stiu", "da", "poate", 420 }); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul nu este in stock!\n");
	}

	repoProducts.remove(p3);
	assert(repoProducts.size() == 2);

	temp.clear();
	temp.push_back(p1);
	temp.push_back(p2);
	assert(repoProducts.getAll() == temp);
	repoProducts.modify(p3, repoProducts.search(p2));
	temp.pop_back();
	temp.push_back(p3);
	assert(repoProducts.getAll() == temp);
	assert(repoProducts.size() == 2);

	try { repoProducts.getElement(-1); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Pozitie invalida!\n");
	}

	try { repoProducts.getElement(5); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Pozitie invalida!\n");
	}

	assert(repoProducts.getElement(0) == p1);
	assert(repoProducts.getElement(1) == p3);


	MapRepository repoProductsMap;
	assert(repoProductsMap.size() == 0);
	assert(repoProductsMap.getAll().size() == 0);

	//Product p1{ "Turbina", "1.9 TDI", "Volkswagen", 1800 };
	//Product p2{ "Scaun", "Lemn", "Ikeea", 60 };
	//Product p3{ "Tractor", "9R 490", "John Deere", 1969385.3 };

	repoProductsMap.store(p1);
	assert(repoProductsMap.size() == 1);
	repoProductsMap.store(p2);
	assert(repoProductsMap.size() == 2);
	repoProductsMap.store(p3);
	assert(repoProductsMap.size() == 3);

	temp.clear();
	temp.push_back(p3);
	temp.push_back(p1);
	temp.push_back(p2);

	assert(repoProductsMap.getAll() == temp);

	assert(repoProductsMap.search(p2) == 2);
	try { repoProductsMap.search(Product{ "nu stiu", "da", "poate", 420 }); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul nu este in stock!\n");
	}

	try { repoProductsMap.store(p1); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Element existent!\n");
	}

	try { repoProductsMap.remove(Product{ "nu stiu", "da", "poate", 420 }); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Element inexistent!\n");
	}

	repoProductsMap.remove(p3);
	assert(repoProductsMap.size() == 2);

	temp.clear();
	temp.push_back(p1);
	temp.push_back(p2);
	assert(repoProductsMap.getAll() == temp);
	repoProductsMap.modify(p3, repoProductsMap.search(p2));
	temp.pop_back();
	temp.insert(temp.begin(), p3);
	assert(repoProductsMap.getAll() == temp);
	assert(repoProductsMap.size() == 2);

	try { repoProductsMap.getElement(-1); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Pozitie invalida!\n");
	}

	try { repoProductsMap.getElement(5); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Pozitie invalida!\n");
	}

	assert(repoProductsMap.getElement(0) == p3);
	assert(repoProductsMap.getElement(1) == p1);

	RepositoryInFile filerepo{ "testfile.txt" };
	assert(!filerepo.size());
	filerepo.store(p1);
	assert(filerepo.getElement(0) == p1);
	assert(filerepo.size() == 1);
	filerepo.store(p2);
	assert(filerepo.getElement(1) == p2);
	assert(filerepo.size() == 2);
	filerepo.store(p3);
	assert(filerepo.getElement(2) == p3);
	assert(filerepo.size() == 3);
	temp.clear();
	temp.push_back(p1);
	temp.push_back(p2);
	temp.push_back(p3);
	assert(filerepo.getAll() == temp);
	temp.erase(temp.begin() + 1);
	filerepo.remove(p2);
	assert(filerepo.getAll() == temp);
	filerepo.modify(p2, 0);
	temp.clear();
	temp.push_back(p2);
	temp.push_back(p3);
	assert(filerepo.getAll() == temp);
	assert(filerepo.search(p3) == 1);
	std::ofstream f;
	f.open("testfile.txt", std::ios::out | std::ios::trunc);
	f.close();
}

void testShoppingCart() {
	Repository repo;
	repo.store(Product{ "Turbina", "1.9 TDI", "Volkswagen", 1800 });
	repo.store(Product{ "Scaun", "Lemn", "Ikeea", 60 });
	repo.store(Product{ "Tractor", "9R 490", "John Deere", 1969385.3 });
	repo.store(Product{ "Telefon", "Smartphone", "Huawei", 950});
	repo.store(Product{ "Monitor", "IPS", "Asus", 1200});
	repo.store(Product{ "Masina", "Cabrio", "Mercedes", 420000});
	ShoppingCart cart;
	assert(!cart.size());
	cart.store(Product{ "Turbina", "1.9 TDI", "Volkswagen", 1800 });
	assert(cart.getCurrentPrice() == 1800);
	assert(cart.size() == 1);
	cart.store(Product{ "Turbina", "1.9 TDI", "Volkswagen", 1800 });
	assert(std::vector<Product>(2, Product{ "Turbina", "1.9 TDI", "Volkswagen", 1800 }) == cart.getAll());
	assert(cart.getCurrentPrice() == 3600);
	assert(cart.size() == 2);
	cart.emptyCart();
	assert(!cart.size());
	assert(!cart.getCurrentPrice());
	cart.generateCart(5, repo.getAll());
	try { cart.generateCart(10000, repo.getAll()); }
	catch (Exception& e) {}
	assert(cart.size() == 5);
	cart.exportToFile("htmL", "cumparaturi");
	remove("C:\\Users\\andre\\Desktop\\cumparaturi.html");
	MapRepository repoProductsMap;
	ServiceInventory servProductsMap(repoProductsMap);
	ShoppingCart cartul;
	ServiceCustomer serv(cartul, servProductsMap);
}

void testValidator() {
	Validator Inspector;
	try { Inspector.check("Lalalal1", "lala", "lalala", "1"); assert(false);}
	catch (ValidateException& e) {
		assert(e.getMessage() == "Nume invalid!\n");
	}

	try { Inspector.check("Lalala", "lala3", "lalala", "1"); assert(false);}
	catch (ValidateException& e) {
		assert(e.getMessage() == "Tip invalid!\n");
	}

	try { Inspector.check("Lalala", "lala", "lalala4", "1"); assert(false);}
	catch (ValidateException& e) {
		assert(e.getMessage() == "Producator invalid!\n");
	}

	try { Inspector.check("Lalala", "lala", "lalala", "1..59"); assert(false);}
	catch (ValidateException& e) {
		assert(e.getMessage() == "Pret invalid!\n");
	}

	try { Inspector.check("Lalala", "lala", "lalala", ".59"); assert(false);}
	catch (ValidateException& e) {
		assert(e.getMessage() == "Pret invalid!\n");
	}


	try { Inspector.check("213", "213123", "1111", "1.9a"); assert(false);}
	catch (ValidateException& e) {
		assert(e.getMessage() == "Nume invalid!\nTip invalid!\nProducator invalid!\nPret invalid!\n");
	}

	try { Inspector.check("", "", "", ""); assert(false);}
	catch (ValidateException& e) {
		assert(e.getMessage() == "Nume invalid!\nTip invalid!\nProducator invalid!\nPret invalid!\n");
	}
}

void testService() {
	Product p1{ "Gantera", "Premium", "Decathlon", 160 };
	Product p2{ "Parfum", "Sweet", "Tom Ford", 700 };
	Product p3{ "Stick", "SSD", "Kingston", 89 };
	Repository repo;
	ServiceInventory serv{ repo };
	try { serv.undoAction(); }
	catch (Exception& e) {
		assert(e.getMessage() == "Nu exista actiuni de refacut!\n");
	}
	assert(serv.empty());
	serv.addProduct("Gantera", "Premium", "Decathlon", "160");
	assert(serv.searchProductIndex("Gantera", "Premium", "Decathlon") == 0);
	serv.modifyProduct("Gantera", "Premium", "Decathlon", "DA", "Poate", "Nush", "160");
	serv.deleteProduct("DA", "Poate", "Nush");
	assert(serv.empty());
	serv.undoAction();
	assert(serv.getProducts() == std::vector<Product>(1, Product{ "DA", "Poate", "Nush", 160 }));
	serv.undoAction();
	assert(serv.getProducts() == std::vector<Product>(1, p1));
	serv.undoAction();
	assert(serv.empty());
	try { serv.undoAction(); }
	catch (Exception& e) {
		assert(e.getMessage() == "Nu exista actiuni de refacut!\n");
	}
	serv.addProduct("Gantera", "Premium", "Decathlon", "160");
	assert(!serv.empty());
	assert(serv.searchProduct("Gantera", "Premium", "Decathlon") == p1);
	serv.addProduct("Parfum", "Sweet", "Tom Ford", "700");

	try { serv.addProduct("Parfum", "Sweet", "Tom Ford", "700"); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul este deja in stock!\n");
	}

	try { serv.searchProduct("teava", "aluminiu", "nush"); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul nu este in stock!\n");
	}

	try { serv.searchProduct("1", "da1", "da2"); assert(false); }
	catch (ValidateException& e) {
		assert(e.getMessage() == "Nume invalid!\nTip invalid!\nProducator invalid!\n");
	}

	try { serv.addProduct("la_", "da&", "da@", ".."); assert(false); }
	catch (ValidateException& e) {
		assert(e.getMessage() == "Nume invalid!\nTip invalid!\nProducator invalid!\nPret invalid!\n");
	}

	serv.addProduct("Stick", "SSD", "Kingston", "89");
	try { serv.deleteProduct("lalala", "la", "la"); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul nu este in stock!\n");
	}

	std::vector<Product> temp;
	temp.push_back(p1);
	temp.push_back(p2);
	temp.push_back(p3);

	assert(serv.getProducts() == temp);

	try { serv.deleteProduct("nusth", "lelele", "da"); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul nu este in stock!\n");
	}

	serv.deleteProduct("Gantera", "Premium", "Decathlon");
	temp.clear();

	temp.push_back(p2);
	temp.push_back(p3);

	assert(serv.getProducts() == temp);
	try { serv.modifyProduct("trolololo", "da", "poate", "nush", "maine", "poate", "10"); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul nu este in stock!\n");
	}

	serv.modifyProduct("Stick", "SSD", "Kingston", "Stick", "SSD", "Kingston", "101");

	try { serv.modifyProduct("Stick", "SSD", "Kingston", "Parfum", "Sweet", "Tom Ford", "650"); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Produsul este deja in stock!\n");
	}
	p3.setPrice(101);
	temp.pop_back();
	temp.push_back(p3);
	assert(serv.getProducts() == temp);

	serv.addProduct("Rasta de gaming", "Ultra HD", "LG", "4500");
	temp.pop_back();
	temp.push_back(Product{ "Rasta de gaming", "Ultra HD", "LG", 4500 });
	temp.push_back(p3);

	assert(temp == serv.sortBy(&ServiceInventory::compareByName));
	temp.clear();
	system("cls");
	temp.push_back(p3);
	temp.push_back(p2);
	temp.push_back(Product{ "Rasta de gaming", "Ultra HD", "LG", 4500 });
	assert(temp == serv.sortBy(&ServiceInventory::compareByPrice));
	serv.addProduct("Rasta de gaminG", "Ultra A", "LG", "4501");

	temp.clear();
	temp.push_back(p2);
	temp.push_back(Product{ "Rasta de gaminG", "Ultra A", "LG", 4501 });
	temp.push_back(Product{ "Rasta de gaming", "Ultra HD", "LG", 4500 });
	temp.push_back(p3);
	assert(temp == serv.sortBy(&ServiceInventory::compareByNameAndType));
	std::vector<Product> servProductsCopy = serv.getProducts();	
	assert(temp == serv.sortVectorByCriteria(servProductsCopy, &ServiceInventory::compareByNameAndType));

	temp.clear();
	temp.push_back(Product{ "Rasta de gaming", "Ultra HD", "LG", 4500 });
	assert(temp == serv.filterProducts(&Product::getName, "Rasta de gaming"));
	temp.push_back(Product{ "Rasta de gaminG", "Ultra A", "LG", 4501 });
	assert(temp == serv.filterProducts(&Product::getProducer, "LG"));
	temp.pop_back();
	temp.push_back(Product{ "Laptop", "Yoga Slim", "Lenovo", 4500 });
	serv.addProduct("Laptop", "Yoga Slim", "Lenovo", "4500");
	assert(temp == serv.filterProducts(&Product::getPriceAsString, "4500"));

	/// testul pt report
	serv.addProduct("asd", "Yoga Slim", "asd", "900");
	for (auto& it : serv.report())
		if (it.first != "Yoga Slim")
			assert(it.second == 1);
		else
			assert(it.second == 2);
	serv.deleteProduct("asd", "Yoga Slim", "asd");
	///
	Repository emptyRepo;
	const ServiceInventory tempservice{ emptyRepo };
	try { tempservice.report(); }
	catch (Exception& e) {
		assert(e.getMessage() == "Nu exista produse!\n");
	}

	ShoppingCart tempCart;
	ServiceInventory emptyServ(emptyRepo);
	ServiceCustomer tempServ{ tempCart, emptyServ};
	try { tempCart.search(Product()); }
	catch (Exception& e) {}
	//catch (Exception& e) { assert(e.getMessage() == "Nu exista suficiente produse!\n"); }
	RepositoryInFile tempFileRepo("testfile.txt");
	ServiceInventory tempFileServ(tempFileRepo);
	ShoppingCart cart;
	ServiceCustomer servCustomer{cart, tempFileServ};
	tempFileServ.addProduct("Stick", "SSD", "Kingston", "89");
	servCustomer.addProduct("Stick"); 
	try { tempCart.remove(Product()); }
	catch (Exception& e) {}
	assert(servCustomer.getProducts() == std::vector<Product>(1, Product{ "Stick", "SSD", "Kingston", 89 }));

	try { servCustomer.deleteProduct("Laptop"); }
	catch (Exception& e) {}
	servCustomer.deleteProduct("Stick");
	assert(!servCustomer.getProducts().size());
	assert(!servCustomer.getCurrentPrice());
	try { servCustomer.deleteProduct("Laptop"); }
	catch (Exception& e) {}
	
	Repository tempRepo5;
	UndoAdd* addU = new UndoAdd(Product(), &tempRepo5);
	UndoModify* modU = new UndoModify(Product(), Product(), &tempRepo5);
	UndoRemove* remU = new UndoRemove(Product(), &tempRepo5);

	assert(addU->getArguments() == std::vector<Product>(1, Product()));
	assert(modU->getArguments() == std::vector<Product>(2, Product()));
	assert(remU->getArguments() == std::vector<Product>(1, Product()));
	delete addU;
	delete modU;
	delete remU;

	servCustomer.addProduct("Stick");
	assert(servCustomer.getCurrentPrice() == 89);
	tempFileServ.modifyProduct("Stick", "SSD", "Kingston", "Stick", "SSD", "Kingston", "89");
	servCustomer.emptyAll();
	assert(!servCustomer.getProducts().size());
	servCustomer.addProduct("Stick");
	servCustomer.generateCart("1");
	assert(servCustomer.getProducts().size() == 1);
	servCustomer.emptyAll();
	servCustomer.addProduct("Stick");
	servCustomer.exportCart("CSV", "temporary");
	std::fstream in;
	in.open("C:\\Users\\andre\\Desktop\\temporary.csv");
	string line;
	getline(in, line);
	assert(line == "Nume Produs, Tip, Producator, Pret");
	getline(in, line);
	assert(line == "Stick, SSD, Kingston, 89");
	getline(in, line);
	assert(line == "");
	getline(in, line);
	assert(line == ", , Pret Total:,89");
	try { servCustomer.exportCart("asd", "temporary"); }
	catch (Exception& e) {
		assert(e.getMessage() == "Tip de fisier invalid!\n");
	}
	in.close();
	remove("C:\\Users\\andre\\Desktop\\temporary.csv");
	ServiceInventory servFile{ tempFileRepo };
	servFile.addProduct("da", "nu", "poate", "169");
	ServiceCustomer servCustomerFile{cart, servFile};
	servCustomerFile.addProduct("da");
	servFile.deleteProduct("da", "nu", "poate");
	assert(!servCustomer.getProducts().size());
	servCustomerFile.emptyAll();
	
	MapRepository repoProductsMap;
	ServiceInventory servul(repoProductsMap);
	std::ofstream f;
	f.open("testfile.txt", std::ios::out | std::ios::trunc);
	f.close();
}

void runTests() {
	testDomain();
	testRepo();
	testShoppingCart();
	testValidator();
	testService();
}