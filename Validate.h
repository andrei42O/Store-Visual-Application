#pragma once
#include "Includes.h"
class Validator {
public:
	Validator() = default;
	/*
	* The function checks if the data provided is logic
	* Input data:	name - string
	*				type - string
	*				producer - string
	*				price - string
	* Output data: -
	* Exceptions thrown: ValidateException (if any of the data given doesn't correspond to the standards)
	*/
	void check(string, string, string, string);
};