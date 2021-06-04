#include "Includes.h"

Exception::Exception(const string msg) : msg{ msg } {
}

const string Exception::getMessage() {
	return msg;
}
