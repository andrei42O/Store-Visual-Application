#include "Includes.h"

void Validator::check(string name, string type, string producer, string price) {
	string error = "";

	if (!name.size())
		error += "Nume invalid!\n";
	else {
		for (unsigned int i = 0; i < name.size(); i++)
			if (isalpha(name.at(i)) || name.at(i) == ' ')
				continue;
			else {
				error += "Nume invalid!\n";
				break;}
	}
	if (!type.size())
		error += "Tip invalid!\n";
	else {
		for (unsigned int i = 0; i < type.size(); i++)
			if (isalpha(type.at(i)) || type.at(i) == ' ')
				continue;
			else {
				error += "Tip invalid!\n";
				break;}
	}
	if (!producer.size())
		error += "Producator invalid!\n";
	else {
		for (unsigned int i = 0; i < producer.size(); i++)
			if (isalpha(producer.at(i)) || producer.at(i) == ' ')
				continue;
			else {
				error += "Producator invalid!\n";
				break;}
	}
	if (!price.size())
		error += "Pret invalid!\n";
	else {
		int puncte = 0, before = 0;
		for(unsigned int i = 0; i < price.size(); i++) {
			if (price.at(i) == '.' || price.at(i) == ',')
				puncte++;
			else {
				if (!isdigit(price.at(i))) {
					error += "Pret invalid!\n";
					break;}
				if (!puncte)
					before = 1;
			}
			if (puncte > 1) {
				error += "Pret invalid!\n";
				break;}
			if (puncte && !before) {
				error += "Pret invalid!\n";
				break;}
		}
	}

	if (error.size())
		throw ValidateException(error);}