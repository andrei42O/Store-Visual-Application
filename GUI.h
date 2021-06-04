#pragma once
#pragma once
#include "Includes.h"
#include "Observers.h"

class CosChart : public QWidget, public Observer {
private:
    ServiceCustomer* servCustomer;

protected:
    void paintEvent(QPaintEvent* event) override;
    void repaint();
public:
    CosChart(ServiceCustomer* servCustomer) : servCustomer{ servCustomer } {
        this->setStyleSheet("background-color: rgb(162,199,229)");
        servCustomer->addObeserv(this);
    }

    void update() override {
        repaint();
    }
};

class ProductListDisplay : public QWidget, public Observer {
    Q_OBJECT
private:
    ServiceInventory* serv;
    ServiceCustomer* servCustomer;

    QVBoxLayout* buttonsLayout;
    QPushButton* buyButton;
    QPushButton* randomBullshitGo;
    QSpinBox* howMany;

    QHBoxLayout* layout;
    QListWidget* products;

    // Right side (customer list)
    QListWidget* customerList;

    QVBoxLayout* customerListButtonsLayout;
    QPushButton* removeButton;
    QPushButton* clearCart;
    QPushButton* exportFile;
    QLabel* currentPrice;

    /*
    * The function creates a product from a string displayed in the products list
    * Input data: -
    * Output data: Product()
    */
    Product createProductFromString(std::string content);

    void refreshPrice() {
        currentPrice->setText(QString::fromStdString("Price: " + std::to_string(servCustomer->getCurrentPrice())));
    }

    void refreshCustomerList();

    /*
    * The function refreshes the product list in the shoppingCart
    * Input data: -
    * Output data: -
    */
    void refreshList();

    void loadCustomerList();

    void loadButtons();

    void loadGUI();
    /*
    * The functions loads all the elements from the repository in the list
    * Input data: -
    * Output data: -
    */
    void loadList();
    /*
    * The functions assigns the signals to certain slots
    * Input data: -
    * Output data: -
    */
    void assignSignals();

    std::vector<Product> getCurrentItemsDisplayed();


public:
    ProductListDisplay(ServiceInventory* serv, ServiceCustomer* servCustomer) :serv{ serv }, servCustomer{ servCustomer }{
        servCustomer->addObeserv(this);
        loadGUI();
    }
    void update() override {
        refreshList();
        refreshCustomerList();
    }
};

/*
* 
* --------------------------------------------------------------------------------------------------
* 
*/

class GUI : public QMainWindow {
private:

    QApplication& app;
    ServiceInventory* serv;
    ServiceCustomer& servCustomer;

    //ProductListDisplay* productsList;

    //QHBoxLayout* shoppingWindowLayout;
    QWidget* mainWindow;
    QHBoxLayout* mainWindowlayout;

    // TABLE
    QVBoxLayout* tableLayout;
    QTableWidget* table;

    QVBoxLayout* textInputAndPhotoLayout;
    /// Text Input
    QFormLayout* textInputlayout;
    QLabel* nameLabel;
    QLabel* typeLabel;
    QLabel* producerLabel;
    QLabel* priceLabel;
    QLineEdit* textName;
    QLineEdit* textType;
    QLineEdit* textProducer;
    QLineEdit* textPrice;

    /// Photo
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* item;

    /// FILTERS AND SORTERS
    QVBoxLayout* listAndFiltersLayout;
    QWidget* widget;
    QHBoxLayout* layout;
    QListWidget* products;
    QWidget* buttonsWidget;
    QVBoxLayout* filtersAndSortersLayout;
    QWidget* filtersWidget;
    QHBoxLayout* buttonsLayout;
    QVBoxLayout* filtersLayout;
    QPushButton* startFilters; // de implementat
    QPushButton* clearFiltersButton;
    QPushButton* byName;
    QPushButton* byPrice;
    QPushButton* byNameAndType;
    QWidget* nameFilter;
    QWidget* typeFilter;
    QWidget* producerFilter;
    QWidget* priceFilter;
    QHBoxLayout* nameFilterLayout;
    QHBoxLayout* typeFilterLayout;
    QHBoxLayout* producerFilterLayout;
    QHBoxLayout* priceFilterLayout;
    QCheckBox* checkName;
    QCheckBox* checkType;
    QCheckBox* checkProducer;
    QCheckBox* checkPrice;
    QComboBox* selectName;
    QComboBox* selectType;
    QComboBox* selectProducer;
    QComboBox* selectPrice;


    /// BUTTONS
    QVBoxLayout* buttonsServLayout;
    QPushButton* close;
    QPushButton* store;
    QPushButton* modify;
    QPushButton* remove;
    QPushButton* undo;
    QPushButton* search;
    QPushButton* shoppingWindowButton;
    QPushButton* stonks;

    bool checkIfEmpty();

    void loadButtons();


    /*
    * The function loads the filters and sorters interface
    * Input data: -
    * Output data: -
    */
    void loadFiltersAndSortersGUI();
    /*
    * The function loads the sort buttons
    * Input data: -
    * Output data: -
    */
    void loadSortButtons();
    /*
    * The function loads the filters interface
    * Input data: -
    * Output data: =-
    */
    void loadFilters();
    /*
    * The function get the current product names
    * Input data: -
    * Output data: std::set<std::string>  which containts the names
    */
    std::set<std::string> getCurrentNames();
    /*
    * The function get the current product types
    * Input data: -
    * Output data: std::set<std::string>  which containts the types
    */
    std::set<std::string> getCurrentTypes();
    /*
    * The function get the current product producers
    * Input data: -
    * Output data: std::set<std::string>  which containts the producers
    */
    std::set<std::string> getCurrentProducers();
    /*
    * The function get the current product prices
    * Input data: -
    * Output data: std::set<std::string>  which containts the prices
    */
    std::set<std::string> getCurrentPrices();
    /*
    * The function clears the current filters
    * Input data: -
    * Output data:-
    */
    void clearFilters();
    /*
    * The function refreshes the combo boxex (unchecking them all)
    * Input data: -
    * Output data: -
    */
    void refreshComboBoxes();

    std::string getCurrentNameSelection() {
        return selectName->currentText().toStdString();
    }

    std::string getCurrentTypeSelection() {
        return selectType->currentText().toStdString();
    }

    std::string getCurrentProducerSelection() {
        return selectProducer->currentText().toStdString();
    }

    std::string getCurrentPriceSelection() {
        return selectPrice->currentText().toStdString();
    }
    /*
    * The function checks if there are any active filters
    * Input data: -
    * Output data: true or false
    */
    bool activeFilters() {
        return checkName->isChecked() || checkType->isChecked() || checkProducer->isChecked() || checkPrice->isChecked();
    }
    /*
    * The function applies the current filters
    * Input data: -
    * Output data: -
    */
    void applyFilters();

    /*
    * The function recieves a string from the product display and converts it to a product
    * Input data: -
    * Output data: Product
    */
    Product createProductFromString(std::string content);

   
    /*
    * The functions loads all the elements from the repository in the list
    * Input data: -
    * Output data: -
    */
    void loadList();
    /*
    * The functions refreshes the list items
    * Input data: -
    * Output data:-
    */
    void refreshList();
    /*
    * The function returns the current items displayd in the list
    * Input data: -
    * Output data: std::vector<Product>
    */
    std::vector<Product> getCurrentItemsDisplayed();

    void assignFiltersAndSortersSignals();

    void loadPhoto();
    /*
    * The functions loads the input boxes and the corespondent type of each one
    * Input data: -
    * Output data: -
    */
    void loadTextInput();

    void loadPhotoAndTextInput();

    void refreshTable();

    void displayVectorInTable(const std::vector<Product>& v);

    void loadTable();

    void loadAdministrationGUI();

    void loadShoppingGUI() {
        QWidget* shoppingWindow = new QWidget;
        QHBoxLayout* shoppingWindowLayout = new QHBoxLayout;
        shoppingWindow->setLayout(shoppingWindowLayout);
        ProductListDisplay* productsList = new ProductListDisplay(serv, &servCustomer);
        //servCustomer.addObeserv(productsList);
        // Fereastra pentru cos
        shoppingWindowLayout->addWidget(productsList);
        shoppingWindow->show();
        // CosChart
    }

    void loadCosChart() {
        CosChart* c = new CosChart(&servCustomer);
        c->show();
    }

    /*
    * The functions fills the name box with the given name
    * Input data: nameLabel - const std::string&
    * Output data: -
    */
    void setName(const std::string& nameLabel) {
        textName->setText(QString::fromStdString(nameLabel));
    }
    /*
    * The functions fills the type box with the given type
    * Input data: const std::string&
    * Output data: -
    */
    void setType(const std::string& typeLabel) {
        textType->setText(QString::fromStdString(typeLabel));
    }
    /*
    * The functions fills the producer box with the given producer
    * Input data: nameLabel - const std::string&
    * Output data: -
    */
    void setProducer(const std::string& producerLabel) {
        textProducer->setText(QString::fromStdString(producerLabel));
    }
    /*
    * The functions fills the price box with the given price
    * Input data: nameLabel - const std::string&
    * Output data: -
    */
    void setPrice(const std::string& priceLabel) {
        textPrice->setText(QString::fromStdString(priceLabel));
    }
    /*
    * The functions concatenates the text form all input boxes
    * Input data: -
    * Output data: string
    */
    std::string getAsString();


    void clearInput();

    void assignSignals() {
        QObject::connect(store, &QPushButton::clicked, this, [&]() {
            try {
                addItem(QString::fromStdString(getAsString()));
                clearInput();
            }
            catch (Exception& e) {
                QMessageBox box;
                box.setIcon(QMessageBox::Warning);
                box.setWindowTitle("Invetory Warning!");
                box.setText(QString::fromStdString(e.getMessage()));
                box.exec();
            }
            }, Qt::UniqueConnection);

        QObject::connect(modify, &QPushButton::clicked, this, [&]() {
            if (checkIfEmpty())
                return;
            std::string selectedProduct = products->currentItem()->text().toStdString();
            std::string newProduct = getAsString();
            try {
                modifyItem(selectedProduct, newProduct);
                clearInput();
            }
            catch (Exception& e) {
                QMessageBox box;
                box.setText(QString::fromStdString(e.getMessage()));
                box.setIcon(QMessageBox::Warning);
                box.setWindowTitle("Inventory Warning!");
                box.exec();
            }

            }, Qt::UniqueConnection);

        QObject::connect(remove, &QPushButton::clicked, this, [&]() {
            if (checkIfEmpty())
                return;
            try {
                removeItem(products->currentItem()->text().toStdString());
                clearInput();
            }
            catch (Exception& e) {
                QMessageBox box;
                box.setText(QString::fromStdString(e.getMessage()));
                box.setIcon(QMessageBox::Warning);
                box.setWindowTitle("Inventory Warning!");
                box.exec();
            }
            });

        QObject::connect(search, &QPushButton::clicked, this, [&]() {
            if (checkIfEmpty())
                return;
            std::string line = getAsString();
            try {
                searchProduct(line);
            }
            catch (Exception& e) {
                QMessageBox box;
                box.setText(QString::fromStdString(e.getMessage()));
                box.setIcon(QMessageBox::Warning);
                box.setWindowTitle("Inventory Warning!");
                box.exec();
            }
            }, Qt::UniqueConnection);

        QObject::connect(undo, &QPushButton::clicked, this, [&]() {
            try {
                undoAction();
            }
            catch (Exception& e) {
                QMessageBox box;
                box.setText(QString::fromStdString(e.getMessage()));
                box.setIcon(QMessageBox::Warning);
                box.setWindowTitle("Inventory Warning!");
                box.exec();
            }
            }, Qt::UniqueConnection);

        QObject::connect(close, &QPushButton::clicked, &app, &QApplication::quit);
        QObject::connect(products, &QListWidget::itemClicked, this, [&]() {
            std::string content = products->currentItem()->text().toStdString();
            std::vector<std::string> v;
            int start = 0, finish = 0;
            for (const auto& it : content) {
                if (it == ',') {
                    v.push_back(content.substr(start, (long long)finish - (int)start));
                    start = finish + 1;
                }
                finish++;
            }
            v.push_back(content.substr(start, finish));
            setName(v.at(0));
            setType(v.at(1));
            setProducer(v.at(2));
            setPrice(v.at(3));
            });
        QObject::connect(shoppingWindowButton, &QPushButton::clicked, this, [&]() {
            loadShoppingGUI();
            });
        QObject::connect(stonks, &QPushButton::clicked, this, [&]() {
            loadCosChart();
            });
    }

    void loadGUI() {
        widget = new QWidget;
        layout = new QHBoxLayout;
        widget->setLayout(layout);
        widget->setStyleSheet("background-color: rgb(241, 250, 238)");
        loadAdministrationGUI();
        layout->addLayout(filtersAndSortersLayout);
        assignSignals();
    }

public:
    GUI(QApplication& app, ServiceInventory& serv, ServiceCustomer& servCustomer) :app{ app }, serv{ &serv },servCustomer{ servCustomer }{
        loadGUI();
    }

    /*
    * The functions displays a certain vector of elements
    * Input data: const vector<Product>&
    * Output data: -
    */
    void updateDisplayList(const std::vector<Product>& v);
    /*
    * The functions adds an item to the repository and refreshes the list
    * Input data: Qstring
    * Output data: -
    */
    void addItem(QString line);
    /*
    * The functions modifies an item in the repository and refreshes the list
    * Input data: Qstring oldProd, Qstring newProd
    * Output data: -
    */
    void modifyItem(std::string oldProduct, std::string newProduct);
    /*
    * The functions removes an item from the repository and refreshes the list
    * Input data: string strProduct
    * Output data: -
    */
    void removeItem(std::string strProduct);
    /*
    * The functions searchs for an item in the repository, refreshes the list and selects it
    * Input data: const std::string& strProd
    * Output data: -
    */
    void searchProduct(const std::string& line);
    /*
    * The functions undo the last operation
    * Input data: -
    * Output data: -
    */
    void undoAction();

    void run() {
        widget->show();
    }

};