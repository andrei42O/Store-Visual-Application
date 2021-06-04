#include "Includes.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    runTests();
    QApplication a(argc, argv);
    RepositoryInFile repo("test.txt");
    ServiceInventory serv(repo);
    ShoppingCart shoppingCartEntity;
    ServiceCustomer servCustomer(shoppingCartEntity, serv);
    GUI app(a, serv, servCustomer);
    app.run();
    return a.exec();
}
