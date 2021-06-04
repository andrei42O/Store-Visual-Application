#include "Includes.h"

Console::Console(ServiceInventory& serv, ServiceCustomer& servCustomer, Validator& Palermo) noexcept : serv{ serv }, servCustomer{ servCustomer }, Inspektor{ Palermo }{
}

void Console::showProducts() const{
	system("cls");
	const std::vector<Product>& temp = serv.getProducts();
	if (!temp.size()) {
		cout << "Nu sunt produse in stock!\n";
		return;
	}
	for (const auto& it : temp) {
		cout << "-----------------------------------------------\n";
		cout << it;
	}
	cout << "-----------------------------------------------\n";
}

void Console::add() {
	string name, type, producer, price;
	cout << "Introduceti numele produsului:\n>>> ";
	getline(cin, name);
	cout << "Introduceti tipul produsului:\n>>> ";
	getline(cin, type);
	cout << "Introduceti producatorul:\n>>> ";
	getline(cin, producer);
	cout << "Introduceti pretul produsului:\n>>> ";
	getline(cin, price);
	serv.addProduct(name, type, producer, price);
}

void Console::remove() {
	if (serv.empty())
		return;
	showProducts();
	string name, type, producer;
	cout << "Pentru a sterge un produs va rog sa introduceti:\nNumele produsului | Tipul produsului | Producatorul\n";
	cout << "Introduceti numele produsului:\n>>> ";
	getline(cin, name);
	cout << "Introduceti tipul produsului:\n>>> ";
	getline(cin, type);
	cout << "Introduceti producatorul:\n>>> ";
	getline(cin, producer);
	serv.deleteProduct(name, type, producer); 
}

void Console::modify() {
	showProducts();
	string oldName, oldType, oldProducer, name, type, producer, price;
	cout << "Pentru a modifica un produs trebuie sa introduceti:\nNumele produsului | Tipul produsului | Producatorul\n";
	cout << "Introduceti numele produsului:\n>>> ";
	getline(cin, oldName);
	cout << "Introduceti tipul produsului:\n>>> ";
	getline(cin, oldType);
	cout << "Introduceti producatorul:\n>>> ";
	getline(cin, oldProducer);
	const Product& temp = serv.searchProduct(oldName, oldType, oldProducer);
	system("cls");
	cout << "Produsul este in stock!\n\n" << temp << "\nAcum va rog sa introduceti noile date ale produsului:\n>>> ";
	cout << "Introduceti noul nume al produsului:\n>>> ";
	getline(cin, name);
	cout << "Introduceti noul tip al produsului:\n>>> ";
	getline(cin, type);
	cout << "Introduceti noul producator al produsului:\n>>> ";
	getline(cin, producer);
	cout << "Introduceti noul pret al produsului:\n>>> ";
	getline(cin, price);
	serv.modifyProduct(oldName, oldType, oldProducer, name, type, producer, price);
}


void Console::search() const {
	string name, type, producer;
	cout << "Pentru a cauta un produs va rog sa introduceti:\nNumele produsului | Tipul produsului | Producatorul\n";
	cout << "Introduceti numele produsului:\n>>> ";
	getline(cin, name);
	cout << "Introduceti tipul produsului:\n>>> ";
	getline(cin, type);
	cout << "Introduceti producatorul:\n>>> ";
	getline(cin, producer);
	Product p;
	p = serv.searchProduct(name, type, producer); 
	system("cls");
	cout << p;
}

void Console::sortMethod() const {
	while (1) {
		showSortMenu();
		string cmd;
		cout << "\nIntroduceti o comanda:\n>>> ";
		getline(cin, cmd);
		if (cmd.size() != 1) {
			system("cls");
			cout << "Comanda invalida!\n\n";
			continue;
		}
		if (cmd == "4" || cmd == "x") {
			system("cls");
			break;
		}
		system("cls");
		try {
			switch (stoi(cmd))
			{
			case 1: {
				std::vector<Product> tempVec = serv.sortBy(&ServiceInventory::compareByName);
				for (const auto &it : tempVec) {
					cout << "-----------------------------------------------\n";
					cout << it;
				}
				cout << "-----------------------------------------------\n";
				string temp;
				cout << "Press ENTER to continue...\n";
				getline(cin, temp);
				system("cls");
				break;
			}
			case 2: {
				std::vector<Product> tempVec = serv.sortBy(&ServiceInventory::compareByPrice);
				for (const auto& it : tempVec) {
					cout << "-----------------------------------------------\n";
					cout << it;
				}
				cout << "-----------------------------------------------\n";
				string temp;
				cout << "Press ENTER to continue...\n";
				getline(cin, temp);
				system("cls");
				break;
			}
			case 3: {
				std::vector<Product> tempVec = serv.sortBy(&ServiceInventory::compareByNameAndType);
				for (const auto& it : tempVec) {
					cout << "-----------------------------------------------\n";
					cout << it;
				}
				cout << "-----------------------------------------------\n";
				string temp;
				cout << "Press ENTER to continue...\n";
				getline(cin, temp);
				system("cls");
				break;
			}
			default: {
				system("cls");
				cout << "Comanda invalida!\n\n";
				break;
			}
			}
		}
		catch (std::invalid_argument) {
			system("cls");
			cout << "Comanda invalida!\n\n";
		}
	}
}

void Console::filterMethod() const {
	while (1) {
		filterMenu();
		string cmd;
		getline(cin, cmd);
		if (cmd.size() != 1) {
			system("cls");
			cout << "Comanda invalida!\n\n";
			continue;
		}
		if (cmd == "x" || cmd == "4") {
			system("cls");
			break;
		}
		try {
			switch (std::stoi(cmd))
			{
			case 1: {
				system("cls");
				string name;
				bool found = 0;
				cout << "Introduceti numele produsului:\n>>> ";
				getline(cin, name);
				Inspektor.check(name, "da", "da", "1");
				system("cls");
				std::vector<Product> tempVec = serv.filterProducts(&Product::getName, name);
				for (const auto& it : tempVec) {
					found = true;
					cout << "-----------------------------------------------\n";
					cout << it;
				}
				if (!found) {
					system("cls");
					cout << "Nu exista produse cu acest nume!\n\n";
					break;
				}
				cout << "-----------------------------------------------\n";
				string temp;
				cout << "Press ENTER to continue...";
				getline(cin, temp);
				system("cls");
				break;
			}
			case 2: {
				system("cls");
				string price;
				bool found = 0;
				cout << "\nIntroduceti pretul:\n>>> ";
				getline(cin, price);
				Inspektor.check("da", "da", "da", price);
				system("cls");
				std::vector<Product> tempVec = serv.filterProducts(&Product::getPriceAsString, price);
				for (const auto& it : tempVec) {
					found = true;
					cout << "-----------------------------------------------\n";
					cout << it;
				}
				if (!found) {
					system("cls");
					cout << "Nu exista produse cu acest pret!\n\n";
					break;
				}
				cout << "-----------------------------------------------\n";
				string temp;
				cout << "Press ENTER to continue...";
				getline(cin, temp);
				system("cls");
				break;
			}
			case 3: {
				system("cls");
				string producer;
				bool found = 0;
				cout << "Introduceti producatorul dupa care doriti sa filtrati produsele:\n>>> ";
				getline(cin, producer);
				Inspektor.check("da", "da", producer, "1");
				system("cls");
				std::vector<Product> tempVec = serv.filterProducts(&Product::getProducer, producer);
				for (const auto& it : tempVec) {
					found = true;
					cout << "-----------------------------------------------\n";
					cout << it;
				}
				if (!found) {
					system("cls");
					cout << "Nu exista produse de la acest producator!\n\n";
					break;
				}
				cout << "-----------------------------------------------\n";
				string temp;
				cout << "Press ENTER to continue...";
				getline(cin, temp);
				system("cls");
				break;
			}
			default: {
				system("cls");
				cout << "Comanda invalida!\n\n";
				break;
			}
			}
		}
		catch (ValidateException& e) {
			system("cls");
			cout << "EROARE!!!\n" << e.getMessage() << '\n';
		}
		catch (std::invalid_argument) {
			system("cls");
			cout << "EROARE!!!\nComanda invalida!\n\n";
		}
	}
}

void Console::shopping() {
	while (true) {
		shoppingMenu();
		string cmd;
		cout << "Introduceti comanda:\n>>> ";
		getline(cin, cmd);
		if (cmd.size() != 1) {
			system("cls");
			cout << "Eroare!!!\nComanda invalida!\n\n";
			continue;
		}
		try {
			switch (stoi(cmd)) {
			case 1: {
				string name;
				system("cls");
				cout << "Introduceti numele unui produs:\n>>> ";
				getline(cin, name);
				servCustomer.addProduct(name);
				system("cls");
				cout << "Produs adaugat cu succes!\n";
				break;
			}
			case 2: {
				servCustomer.emptyAll();
				system("cls");
				cout << "Cosul a fost golit!\n\n";
				break;
			}
			case 3: {
				const std::vector<Product>& temp = servCustomer.getProducts();
				system("cls");
				bool found = false;
				for (const auto& it : temp) {
					found = true;
					cout << "-----------------------------------------------\n";
					cout << it;
				}
				if (!found) {
					system("cls");
					cout << "Nu aveti produse in cos!\n\n";
					break;
				}
				cout << "-----------------------------------------------\n";
				string tempC;
				cout << "Press ENTER to continue...";
				getline(cin, tempC);
				system("cls");
				break;
			}
			case 4: {
				string howMuch;
				system("cls");
				cout << "Cate produse doriti sa contina cosul?\n>>> ";
				getline(cin, howMuch);
				servCustomer.generateCart(howMuch);
				system("cls");
				cout << "Cos de cumparaturi generat cu succes!\n\n";
				break;
			}
			case 5: {
				string type, fileName;
				cout << "Introduceti tipul fisierului (CSV or HTML)\n>>> ";
				getline(cin, type);
				cout << "Introduceti numle fisierului in care doriti sa il exportati\n>>> ";
				getline(cin, fileName);
				servCustomer.exportCart(type, fileName);
				system("cls");
				cout << "Bon fiscal generat cu succes!\nCosul a fost golit!\n";
				break;
			}
			case 6: {
				system("cls");
				return;
			}
			default: {
				system("cls");
				cout << "Eroare!!!\nComanda invalida!\n\n";
				break;
			}
			}
		}
		catch (Exception& e) {
			system("cls");
			cout << "Eroare!!!\n" << e.getMessage() << "\n";
		}
		catch (std::invalid_argument) {
			system("cls");
			cout << "Eroare!!!\nNumar invalid!\n\n";
		}
	}
}

void Console::report() const {
	const std::map < std::string, int> temp = serv.report();
	for (const auto& it : temp)
		cout << "Sunt " << it.second << ' ' << "produse de tipul " << it.first << '\n';
	cout << "\n";
}

void Console::undo() {
	serv.undoAction();
	std::cout << "Undo realizat cu succes!\n";
}

void Console::shoppingMenu() const{
	cout << "~~~~~~~~~~~~~~~~~~~ MENIU ~~~~~~~~~~~~~~~~~~~\n";
	cout << "~ 1 - Adauga produs in cos                  ~\n";
	cout << "~ 2 - Goleste cosul                         ~\n";
	cout << "~ 3 - Afiseaza produsele din cos            ~  Costul curent: " << servCustomer.getCurrentPrice() << "\n";
	cout << "~ 4 - Ai ramas fara idei? Genereaza un cos! ~\n";
	cout << "~ 5 - Exporteaza bonul fiscal               ~\n";
	cout << "~ 6 - Back                                  ~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void Console::showMenu() const {
	cout << "--------~ MENIU ~-------\n";
	cout << "1 - Adauga un produs nou\n";
	cout << "2 - Sterge un produs\n";
	cout << "3 - Modifica un produs\n";
	cout << "4 - Cauta un produs\n";
	cout << "5 - Afiseaza produsele\n";
	cout << "6 - Sorteaza dupa\n";
	cout << "7 - Filtreaza dupa\n";
	cout << "8 - Go to shopping!\n";
	cout << "9 - Raport in functie de tip\n";
	cout << "10 - Undo\n";
	cout << "x - Exit\n";
}

void Console::showSortMenu() const{
	cout << "------~ MENIU ~------\n";
	cout << "1 - Dupa nume\n";
	cout << "2 - Dupa pret\n";
	cout << "3 - Dupa nume si tip\n";
	cout << "4 - Back\n";
}

void Console::filterMenu() const {
	cout << "-----------~ Meniu ~-------------\n";
	cout << "1 - Dupa un anumit nume de produs\n";
	cout << "2 - Dupa un anumit pret\n";
	cout << "3 - Dupa un anumit producator\n";
	cout << "4 - Back\n";
}

void Console::run() {
	//serv.addProduct("da", "nu", "poate", "10");
	//serv.modifyProduct("da", "nu", "poate", "nu", "ab", "asd", "100");
	//serv.deleteProduct("nu", "ab", "asd");
	while (1) {
		showMenu();
		string cmd;
		cout << "\nIntroduceti comanda:\n>>> ";
		getline(cin, cmd);
		if (cmd == "fuckoff" || cmd == "x" || cmd == "X") {
			system("cls");
			cout << "Shutting down...\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|";
			break;
		}
		if (cmd.size() > 2) {
			system("cls");
			cout << "EROARE!!!\nComanda invalida!\n\n";
			continue;
		}
		try {
			switch (std::stoi(cmd)){
				case 1: {
					system("cls");
					add();
					system("cls");
					cout << "Produs adaugat cu succes!\n";
					break;
				}
				case 2: {
					system("cls");
					if (serv.empty()) {
						cout << "Nu exista produse in stock!\n";
						break;
					}
					remove();
					system("cls");
					cout << "Produs sters cu succes!\n";
					break;
				}
				case 3: {
					system("cls");
					modify();
					system("cls");
					cout << "Produs modificat cu succes!\n";
					break;
				}
				case 4: {
					system("cls");
					search();
					break;
				}
				case 5: {
					system("cls");
					showProducts();
					cout << "Press ENTER to continue...\n";
					string temp;
					getline(cin, temp);
					system("cls");
					break;
				}
				case 6:{
					system("cls");
					sortMethod();
					break;
				}
				case 7: {
					system("cls");
					filterMethod();
					break;
				}
				case 8: {
					system("cls");
					shopping();
					break;
				}
				case 9: {
					system("cls");
					report();
					break;
				}
				case 10: {
					system("cls");
					undo();
					break;
				}
				default: {
					system("cls");
					cout << "EROARE!!!\nComanda invalida!\n\n";
					break;
				}
			}
		}
		catch (Exception& e) {
			system("cls");
			cout << "EROARE!!!\n" << e.getMessage() << '\n';
		}
		catch (std::invalid_argument) {
			system("cls");
			cout << "EROARE!!!\nComanda invalida!\n\n";
		}
	}
}