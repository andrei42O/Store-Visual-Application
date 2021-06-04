#pragma once
#include "Includes.h"
class UndoAction {
protected:
	std::string undoType;
public:
	UndoAction() = delete;
	UndoAction(const std::string&);
	virtual void doUndo() = 0;
	UndoAction(const UndoAction&) = default;
	UndoAction(UndoAction&&) = default;
	UndoAction& operator=(UndoAction&) = default;
	UndoAction& operator=(UndoAction&&) = default;
	virtual const string& getType() const noexcept;
	virtual const std::vector<Product> getArguments() noexcept = 0;
	virtual ~UndoAction() {};
};

class UndoAdd : public UndoAction {
private:
	Product p;
	DefaultRepository* repo;
public:
	UndoAdd(const Product&, DefaultRepository*);
	/*
	* The function removes a element added
	* Input data: -
	* Output data:-
	* Exceptions thrown: -
	*/
	void doUndo() override;
	virtual const std::vector<Product> getArguments() noexcept override;
};

class UndoModify : public UndoAction {
private:
	Product p, oldP;
	DefaultRepository* repo;
public:
	UndoModify(const Product&, const Product&, DefaultRepository*);
	/*
	* The function modifies element to it's old values
	* Input data: -
	* Output data:-
	* Exceptions thrown: -
	*/
	void doUndo() override;
	virtual const std::vector<Product> getArguments() noexcept override;
};

class UndoRemove : public UndoAction {
private: 
	Product p;
	DefaultRepository* repo;
public:
	UndoRemove(const Product&, DefaultRepository*);	
	/*
	* The function adds an element which was deleted
	* Input data: -
	* Output data:-
	* Exceptions thrown: -
	*/
	void doUndo() override;
	virtual const std::vector<Product> getArguments() noexcept override;
};
