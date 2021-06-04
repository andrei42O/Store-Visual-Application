#include "Includes.h"

UndoAdd::UndoAdd(const Product& p, DefaultRepository* repo) : p{ p }, repo{ repo }, UndoAction("add"){
}

void UndoAdd::doUndo() {
	repo->remove(p);
}

const std::vector<Product> UndoAdd::getArguments() noexcept
{
	return std::vector<Product>(1, p);
}

UndoModify::UndoModify(const Product& p, const Product& oldP, DefaultRepository* repo) : p{ p }, oldP{ oldP }, repo{ repo }, UndoAction("modify"){
}

void UndoModify::doUndo() {
	repo->modify(oldP, repo->search(p));
}

const std::vector<Product> UndoModify::getArguments() noexcept
{
	std::vector<Product> temp;
	temp.push_back(p);
	temp.push_back(oldP);
	return temp;
}


UndoRemove::UndoRemove(const Product& p, DefaultRepository* repo) : p{ p }, repo{ repo }, UndoAction("remove"){
}

void UndoRemove::doUndo() {
	repo->store(p);
}

const std::vector<Product> UndoRemove::getArguments() noexcept
{
	return std::vector<Product>(1, p);
}

UndoAction::UndoAction(const std::string& undoType) : undoType{ undoType }{
}

const string& UndoAction::getType() const noexcept{
	return undoType;
}
