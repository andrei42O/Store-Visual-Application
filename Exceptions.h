#pragma once
#include "Includes.h"
class Exception {
protected:
	string msg;

public:
	Exception() = default;
	Exception(const string);
	const string getMessage();
};

class RepoException: public Exception{
public:
	RepoException() noexcept: Exception() {}
	RepoException(const string msg): Exception(msg) {}
	RepoException(RepoException&&) = default;
	RepoException (const RepoException&) = default;
	RepoException& operator=(RepoException&) = default;
	RepoException& operator=(RepoException&&) = default;
	~RepoException() noexcept{}
};

class ValidateException: public Exception {
public:
	ValidateException() noexcept: Exception(){}
	ValidateException(const string msg) : Exception(msg) {}
	ValidateException(ValidateException&&) = default;
	ValidateException& operator=(const ValidateException&) = default;
	ValidateException& operator=(ValidateException&&) = default;
	ValidateException (const ValidateException&) = default;
	~ValidateException() noexcept{}
	
};

class VectorException: public Exception{
public:
	VectorException() noexcept: Exception(){}
	VectorException(const string msg) : Exception(msg) {}
	VectorException(VectorException&&) = default;
	VectorException (const VectorException&) = default;
	VectorException& operator=(const VectorException&) = default;
	VectorException& operator=(VectorException&&) = default;
	~VectorException() noexcept{}
};