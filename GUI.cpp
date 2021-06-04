#include "GUI.h"

std::string GUI::getAsString() {
    std::string nameToStr = textName->text().toStdString();
    std::string typeToStr = textType->text().toStdString();
    std::string producerToStr = textProducer->text().toStdString();
    std::string priceToStr = textPrice->text().toStdString();
    return nameToStr + "," + typeToStr + "," + producerToStr + "," + priceToStr;
}

void GUI::clearInput() {
    textName->setText("");
    textType->setText("");
    textProducer->setText("");
    textPrice->setText("");
}

void GUI::loadList()
{
    products = new QListWidget;
    products->setStyleSheet("background-color: rgb(241, 255, 250)");
    listAndFiltersLayout->addWidget(products);
    refreshList();
}

void GUI::refreshList() {
    products->clear();
    const std::vector<Product>& currentProducts = serv->getProducts();
    for (const auto& it : currentProducts) {
        std::string Line = it.getName() + "," + it.getType() + "," + it.getProducer() + "," + it.getPriceAsString();
        products->addItem(new QListWidgetItem(QString::fromStdString(Line)));
    }
    refreshTable();
    if (currentProducts.size())
        products->setCurrentItem(products->item(0));
    //refreshComboBoxes();
}

void GUI::refreshTable() {
    return;
    table->clear();
    const std::vector<Product>& v = serv->getProducts();
    table->setRowCount(v.size() + 1);
    table->setColumnCount(4);
    QTableWidgetItem* nameCol = new QTableWidgetItem("Name");
    QTableWidgetItem* typeCol = new QTableWidgetItem("Type");
    QTableWidgetItem* producerCol = new QTableWidgetItem("Producer");
    QTableWidgetItem* priceCol = new QTableWidgetItem("Price");
    table->setItem(0, 0, nameCol);
    table->setItem(0, 1, typeCol);
    table->setItem(0, 2, producerCol);
    table->setItem(0, 3, priceCol);
    int row = 1;
    for (const auto& it : v) {
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(it.getName())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(it.getType())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(it.getProducer())));
        table->setItem(row++, 3, new QTableWidgetItem(QString::fromStdString(it.getPriceAsString())));
    }
}

void GUI::loadTable()
{
    tableLayout = new QVBoxLayout;
    table = new QTableWidget;
    tableLayout->addWidget(table);
    table->setMaximumWidth(500);
    layout->addLayout(tableLayout);
    refreshTable();
}

void GUI::loadAdministrationGUI()
{
    mainWindow = new QWidget;
    mainWindowlayout = new QHBoxLayout;
    mainWindow->setLayout(mainWindowlayout);
    mainWindow->setStyleSheet("background-color: rgb(102, 255, 201)");
    widget->resize(828, 629);

    //loadTable();
    listAndFiltersLayout = new QVBoxLayout;
    loadList();
    loadFiltersAndSortersGUI();
    layout->addLayout(listAndFiltersLayout);
    loadPhotoAndTextInput();
    loadButtons();
}

void GUI::displayVectorInTable(const std::vector<Product>& v) {
    table->clear();
    table->setRowCount(v.size() + 1);
    table->setColumnCount(4);
    QTableWidgetItem* nameCol = new QTableWidgetItem("Name");
    QTableWidgetItem* typeCol = new QTableWidgetItem("Type");
    QTableWidgetItem* producerCol = new QTableWidgetItem("Producer");
    QTableWidgetItem* priceCol = new QTableWidgetItem("Price");
    table->setItem(0, 0, nameCol);
    table->setItem(0, 1, typeCol);
    table->setItem(0, 2, producerCol);
    table->setItem(0, 3, priceCol);
    int row = 1;
    for (const auto& it : v) {
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(it.getName())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(it.getType())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(it.getProducer())));
        table->setItem(row++, 3, new QTableWidgetItem(QString::fromStdString(it.getPriceAsString())));
    }
}

void GUI::loadFilters() {

    startFilters = new QPushButton("FILTER");
    startFilters->setStyleSheet("background-color: rgb(255, 150, 0)");
    clearFiltersButton = new QPushButton("CLEAR FILTER");
    clearFiltersButton->setStyleSheet("background-color: rgb(255, 150, 0)");

    nameFilter = new QWidget;
    typeFilter = new QWidget;
    producerFilter = new QWidget;
    priceFilter = new QWidget;

    nameFilterLayout = new QHBoxLayout;
    typeFilterLayout = new QHBoxLayout;
    producerFilterLayout = new QHBoxLayout;
    priceFilterLayout = new QHBoxLayout;

    checkName = new QCheckBox(QString::fromStdString("Name"));
    checkType = new QCheckBox(QString::fromStdString("Type"));
    checkProducer = new QCheckBox(QString::fromStdString("Producer"));
    checkPrice = new QCheckBox(QString::fromStdString("Price"));

    selectName = new QComboBox;
    selectType = new QComboBox;
    selectProducer = new QComboBox;
    selectPrice = new QComboBox;

    nameFilter->setLayout(nameFilterLayout);
    typeFilter->setLayout(typeFilterLayout);
    producerFilter->setLayout(producerFilterLayout);
    priceFilter->setLayout(priceFilterLayout);

    nameFilterLayout->addWidget(checkName);
    nameFilterLayout->addWidget(selectName);

    typeFilterLayout->addWidget(checkType);
    typeFilterLayout->addWidget(selectType);

    producerFilterLayout->addWidget(checkProducer);
    producerFilterLayout->addWidget(selectProducer);

    priceFilterLayout->addWidget(checkPrice);
    priceFilterLayout->addWidget(selectPrice);

    filtersLayout->addWidget(nameFilter);
    filtersLayout->addWidget(typeFilter);
    filtersLayout->addWidget(producerFilter);
    filtersLayout->addWidget(priceFilter);

    listAndFiltersLayout->addWidget(startFilters);
    listAndFiltersLayout->addWidget(clearFiltersButton);
    layout->addWidget(filtersWidget);
    refreshComboBoxes();
}

std::set<std::string> GUI::getCurrentNames() {
    std::set<std::string> ret;
    for (int i = 0; i < selectName->count(); i++) {
        ret.insert(selectName->currentText().toStdString());
    }
    return ret;
}

std::set<std::string> GUI::getCurrentTypes() {
    std::set<std::string> ret;
    for (int i = 0; i < selectType->count(); i++) {
        ret.insert(selectType->currentText().toStdString());
    }
    return ret;
}

std::set<std::string> GUI::getCurrentProducers() {
    std::set<std::string> ret;
    for (int i = 0; i < selectProducer->count(); i++) {
        ret.insert(selectProducer->currentText().toStdString());
    }
    return ret;
}

std::set<std::string> GUI::getCurrentPrices() {
    std::set<std::string> ret;
    for (int i = 0; i < selectPrice->count(); i++) {
        ret.insert(selectPrice->currentText().toStdString());
    }
    return ret;
}

void GUI::clearFilters()
{
    checkName->setCheckState(Qt::Unchecked);
    checkType->setCheckState(Qt::Unchecked);
    checkProducer->setCheckState(Qt::Unchecked);
    checkPrice->setCheckState(Qt::Unchecked);
    refreshComboBoxes();
    refreshList();
}

void GUI::refreshComboBoxes() {
    const std::vector<Product>& v = serv->getProducts();
    std::set<std::string> names;
    std::set<std::string> types;
    std::set<std::string> producers;
    std::set<std::string> prices;
    for (const auto& it : v) {
        names.insert(it.getName());
        types.insert(it.getType());
        producers.insert(it.getProducer());
        prices.insert(it.getPriceAsString());
    }
    if (names != getCurrentNames()) {
        selectName->clear();
        for (const auto& it : names)
            selectName->addItem(QString::fromStdString(it));
    }
    if (types != getCurrentTypes()) {
        selectType->clear();
        for (const auto& it : types)
            selectType->addItem(QString::fromStdString(it));
    }
    if (producers != getCurrentProducers()) {
        selectProducer->clear();
        for (const auto& it : producers)
            selectProducer->addItem(QString::fromStdString(it));
    }
    if (prices != getCurrentPrices()) {
        selectPrice->clear();
        for (const auto& it : prices)
            selectPrice->addItem(QString::fromStdString(it));
    }
}

void GUI::applyFilters() {
    if (!activeFilters()) {
        refreshList();
        return;
    }
    if (checkName->isChecked()) {
        updateDisplayList(serv->filterProducts(&Product::getName, getCurrentNameSelection()));
        checkType->setCheckState(Qt::Unchecked);
        checkProducer->setCheckState(Qt::Unchecked);
        checkPrice->setCheckState(Qt::Unchecked);
        return;
    }
    if (checkType->isChecked()) {
        updateDisplayList(serv->filterProducts(&Product::getType, getCurrentTypeSelection()));
        checkName->setCheckState(Qt::Unchecked);
        checkProducer->setCheckState(Qt::Unchecked);
        checkPrice->setCheckState(Qt::Unchecked);
        return;
    }
    if (checkProducer->isChecked()) {
        updateDisplayList(serv->filterProducts(&Product::getProducer, getCurrentProducerSelection()));
        checkName->setCheckState(Qt::Unchecked);
        checkType->setCheckState(Qt::Unchecked);
        checkPrice->setCheckState(Qt::Unchecked);
        return;
    }
    if (checkPrice->isChecked()) {
        updateDisplayList(serv->filterProducts(&Product::getPriceAsString, getCurrentPriceSelection()));
        checkName->setCheckState(Qt::Unchecked);
        checkType->setCheckState(Qt::Unchecked);
        checkProducer->setCheckState(Qt::Unchecked);
        return;
    }
}

Product GUI::createProductFromString(std::string content) {
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
    Validator Inspektor;
    Inspektor.check(v.at(0), v.at(1), v.at(2), v.at(3));
    return Product{ v.at(0), v.at(1), v.at(2), stod(v.at(3)) };
}

std::vector<Product> GUI::getCurrentItemsDisplayed() {
    std::vector<Product> ret;
    for (int i = 0; i < products->count(); i++) {
        std::string s = products->item(i)->text().toStdString();
        ret.push_back(createProductFromString(s));
    }
    return ret;
}

void GUI::assignFiltersAndSortersSignals() {
    QObject::connect(byName, &QPushButton::clicked, this, [&]() {
        std::vector<Product> v;
        if (!activeFilters())
            v = serv->sortBy(&ServiceInventory::compareByName);
        else
            v = serv->sortVectorByCriteria(getCurrentItemsDisplayed(), &ServiceInventory::compareByName);
        if (v.size()) {
            updateDisplayList(v);
        }
        }, Qt::UniqueConnection);

    QObject::connect(byPrice, &QPushButton::clicked, this, [&]() {
        std::vector<Product> v;
        if (!activeFilters())
            v = serv->sortBy(&ServiceInventory::compareByPrice);
        else
            v = serv->sortVectorByCriteria(getCurrentItemsDisplayed(), &ServiceInventory::compareByPrice);
        if (v.size()) {
            updateDisplayList(v);
        }
        }, Qt::UniqueConnection);

    QObject::connect(byNameAndType, &QPushButton::clicked, this, [&]() {
        std::vector<Product> v;
        if (!activeFilters())
            v = serv->sortBy(&ServiceInventory::compareByNameAndType);
        else
            v = serv->sortVectorByCriteria(getCurrentItemsDisplayed(), &ServiceInventory::compareByNameAndType);
        if (v.size()) {
            updateDisplayList(v);
        }
        }, Qt::UniqueConnection);

    QObject::connect(startFilters, &QPushButton::clicked, this, [&]() {
        applyFilters();
        });

    QObject::connect(clearFiltersButton, &QPushButton::clicked, this, [&]() {
        clearFilters();
        });
}

void GUI::loadPhoto()
{
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene);
    item = new QGraphicsPixmapItem(QPixmap("ogeastbull.jpg"));
    scene->addItem(item);
    textInputAndPhotoLayout->addWidget(view);
}

void GUI::loadTextInput()
{
    textInputlayout = new QFormLayout;

    nameLabel = new QLabel("Name:");
    typeLabel = new QLabel("Type:");
    producerLabel = new QLabel("Producer:");
    priceLabel = new QLabel("Price:");

    textName = new QLineEdit();
    textType = new QLineEdit();
    textProducer = new QLineEdit();
    textPrice = new QLineEdit();
    textPrice->setValidator(new QDoubleValidator(0, 10000000, 4, textPrice));

    textName->setStyleSheet("background-color:rgb(255, 255, 153)");
    textType->setStyleSheet("background-color:rgb(255, 255, 153)");
    textProducer->setStyleSheet("background-color:rgb(255, 255, 153)");
    textPrice->setStyleSheet("background-color:rgb(255, 255, 153)");

    textInputlayout->addRow(nameLabel, textName);
    textInputlayout->addRow(typeLabel, textType);
    textInputlayout->addRow(producerLabel, textProducer);
    textInputlayout->addRow(priceLabel, textPrice);

    textInputAndPhotoLayout->addLayout(textInputlayout);

}

void GUI::loadPhotoAndTextInput()
{
    textInputAndPhotoLayout = new QVBoxLayout;
    loadTextInput();
    loadPhoto();
    layout->addLayout(textInputAndPhotoLayout);
}

void GUI::updateDisplayList(const std::vector<Product>& v){
    products->clear();
    for (const auto& it : v) {
        std::string line = it.getName() + "," + it.getType() + "," + it.getProducer() + "," + it.getPriceAsString();
        products->addItem(new QListWidgetItem(QString::fromStdString(line)));
    }
    displayVectorInTable(v);
    if (v.size()) {
        products->setCurrentItem(products->item(0));
    }
}

void GUI::addItem(QString line){
    std::string content = line.toStdString();
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
    serv->addProduct(v.at(0), v.at(1), v.at(2), v.at(3));
    refreshList();
    clearFilters();
}

void GUI::modifyItem(std::string oldProduct, std::string newProduct){
    
    int start = 0, finish = 0;
    std::vector<std::string> v;
    for (const auto& it : oldProduct) {
        if (it == ',') {
            v.push_back(oldProduct.substr(start, (long long)finish - (int)start));
            start = finish + 1;
        }
        finish++;
    }
    start = finish = 0;
    for (const auto& it : newProduct) {
        if (it == ',') {
            v.push_back(newProduct.substr(start, (long long)finish - (int)start));
            start = finish + 1;
        }
        finish++;
    }
    v.push_back(newProduct.substr(start, (long long)finish - (int)start));
    serv->modifyProduct(v.at(0), v.at(1), v.at(2), v.at(3), v.at(4), v.at(5), v.at(6));
    refreshList();
    clearFilters();
}

void GUI::removeItem(std::string strProduct){
    int start = 0, finish = 0;
    std::vector<std::string> v;
    for (const auto& it : strProduct) {
        if (it == ',') {
            v.push_back(strProduct.substr(start, (long long)finish - (int)start));
            start = finish + 1;
        }
        finish++;
    }
    serv->deleteProduct(v.at(0), v.at(1), v.at(2));
    refreshList();
    clearFilters();
}

void GUI::searchProduct(const std::string& line){
    int start = 0, finish = 0;
    std::vector<std::string> v;
    for (const auto& it : line) {
        if (it == ',') {
            v.push_back(line.substr(start, (long long)finish - (int)start));
            start = finish + 1;
        }
        finish++;
    }
    const int index = serv->searchProductIndex(v.at(0), v.at(1), v.at(2));
    refreshList();
    products->setCurrentItem(products->item(index));
}

void GUI::undoAction(){
    serv->undoAction();
    refreshList();
    clearFilters();
}

bool GUI::checkIfEmpty(){
    if (!products->count()) {
        QMessageBox box;
        box.setText(QString::fromStdString("No products found!"));
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle("Inventory Warning!");
        box.exec();
        return true;
    }
    return false;
}

void GUI::loadButtons()
{

    buttonsServLayout = new QVBoxLayout;
    store = new QPushButton("&Store");
    modify = new QPushButton("&Modify");
    remove = new QPushButton("&Remove");
    close = new QPushButton("&Close");
    shoppingWindowButton = new QPushButton("&Shopping!");
    stonks = new QPushButton("Cos Visualizer");
    shoppingWindowButton->setStyleSheet("background-color: rgb(133, 187, 101)");
    stonks->setStyleSheet("background-color: rgb(51,122,183)");
    close->setStyleSheet("background-color: red; color: white");
    undo = new QPushButton("&Undo");
    search = new QPushButton("&Search");
    buttonsServLayout->addWidget(store);
    buttonsServLayout->addWidget(modify);
    buttonsServLayout->addWidget(remove);
    buttonsServLayout->addWidget(search);
    buttonsServLayout->addWidget(undo);
    buttonsServLayout->addWidget(stonks);
    buttonsServLayout->addWidget(shoppingWindowButton);
    buttonsServLayout->addWidget(close);
    layout->addLayout(buttonsServLayout);
}

void GUI::loadFiltersAndSortersGUI()
{
    filtersAndSortersLayout = new QVBoxLayout;
    filtersWidget = new QWidget;
    filtersLayout = new QVBoxLayout;
    filtersWidget->setLayout(filtersLayout);
    loadFilters();
    buttonsWidget = new QWidget;
    buttonsLayout = new QHBoxLayout;
    buttonsWidget->setLayout(buttonsLayout);
    loadSortButtons();
    listAndFiltersLayout->addWidget(filtersWidget);
    listAndFiltersLayout->addWidget(buttonsWidget);
    assignFiltersAndSortersSignals();
}

void GUI::loadSortButtons()
{
    byName = new QPushButton("&NAME");
    byPrice = new QPushButton("&PRICE");
    byNameAndType = new QPushButton("&NAME AND TYPE");
    buttonsLayout->addWidget(byName);
    buttonsLayout->addWidget(byPrice);
    buttonsLayout->addWidget(byNameAndType);
    layout->addWidget(buttonsWidget);
}

void CosChart::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    const int l = servCustomer->getProducts().size();
    if (!l)
        return;
    int x = 0, y = 0;
    std::string source = "images\\stonks (";
    const int w = QWidget::width() - 50;
    const int h = QWidget::height() - 50;
    srand(time(NULL));
    for (int i = 0; i < l; i++) {
        x = rand() % w;
        y = rand() % h;
        QPixmap img(QString::fromStdString(source + std::to_string(rand() % 13 + 1) + ").png"));
        img.scaled(50, 50, Qt::KeepAspectRatio);
        painter.drawPixmap(x, y, img);
    }
}

void CosChart::repaint()
{
    QWidget::repaint();
}

Product ProductListDisplay::createProductFromString(std::string content)
{
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
    Validator Inspektor;
    Inspektor.check(v.at(0), v.at(1), v.at(2), v.at(3));
    return Product{ v.at(0), v.at(1), v.at(2), stod(v.at(3)) };
}

void ProductListDisplay::refreshCustomerList()
{

    customerList->clear();
    std::string content;
    std::vector<Product> temp = servCustomer->getProducts();
    for (const auto& it : temp) {
        QListWidgetItem* item = new QListWidgetItem();
        content = it.getName() + "," + it.getType() + "," + it.getProducer() + "," + it.getPriceAsString();
        item->setText(QString::fromStdString(content));
        customerList->addItem(item);
    }
    refreshPrice();
    if (customerList->count())
        customerList->setCurrentRow(0);
}

void ProductListDisplay::refreshList()
{

    products->clear();
    std::string content;
    for (const auto& it : serv->getProducts()) {
        QListWidgetItem* item = new QListWidgetItem();
        content = it.getName() + "," + it.getType() + "," + it.getProducer() + "," + it.getPriceAsString();
        item->setText(QString::fromStdString(content));
        products->addItem(item);
    }
    refreshPrice();
    if (products->count())
        products->setCurrentRow(0);
}

void ProductListDisplay::loadCustomerList()
{
    customerListButtonsLayout = new QVBoxLayout;
    currentPrice = new QLabel;
    customerList = new QListWidget;
    customerListButtonsLayout->addWidget(currentPrice);
    customerListButtonsLayout->addWidget(customerList);
    refreshCustomerList();
}

void ProductListDisplay::loadButtons()
{
    // MIDDLE
    buttonsLayout = new QVBoxLayout;
    layout->addLayout(buttonsLayout);
    buyButton = new QPushButton("BUY");
    buyButton->setStyleSheet("background-color:     ");
    randomBullshitGo = new QPushButton("GENERATE A RANDOM CART");
    howMany = new QSpinBox;
    buttonsLayout->addWidget(buyButton);
    buttonsLayout->addWidget(randomBullshitGo);
    buttonsLayout->addWidget(howMany);

    // RIGHT SIDE

    layout->addLayout(customerListButtonsLayout);
    removeButton = new QPushButton("REMOVE");
    clearCart = new QPushButton("CLEAR CART");
    exportFile = new QPushButton("EXPORT");
    customerListButtonsLayout->addWidget(removeButton);
    customerListButtonsLayout->addWidget(clearCart);
    customerListButtonsLayout->addWidget(exportFile);
    assignSignals();
}

void ProductListDisplay::loadGUI()
{
    layout = new QHBoxLayout;
    this->setLayout(layout);
    loadList();
    loadCustomerList();
    loadButtons();
    //layout->addLayout(customerListButtonsLayout);
    howMany->setMaximum(serv->getProducts().size());
}

void ProductListDisplay::loadList()
{
    products = new QListWidget;
    layout->addWidget(products);
    products->setStyleSheet("background-color: rgb(241, 255, 250)");
    products->clear();
    const std::vector<Product>& currentProducts = serv->getProducts();
    for (const auto& it : currentProducts) {
        std::string Line = it.getName() + "," + it.getType() + "," + it.getProducer() + "," + it.getPriceAsString();
        products->addItem(new QListWidgetItem(QString::fromStdString(Line)));
    }
    if (currentProducts.size())
        products->setCurrentItem(products->item(0));
}

void ProductListDisplay::assignSignals()
{
    QObject::connect(buyButton, &QPushButton::clicked, this, [&]() {
        std::string currentItem = products->currentItem()->text().toStdString();
        servCustomer->addProduct(createProductFromString(currentItem).getName());
        refreshCustomerList();
        }, Qt::UniqueConnection);

    QObject::connect(randomBullshitGo, &QPushButton::clicked, this, [&]() {
        qDebug("%s", QString::fromStdString(std::to_string(howMany->value())));
        try {
            servCustomer->generateCart(std::to_string(howMany->value()));
            refreshCustomerList();
        }
        catch (Exception& e) {
            QMessageBox box;
            box.setText(QString::fromStdString(e.getMessage()));
            box.exec();
        }
        }, Qt::UniqueConnection);

    QObject::connect(removeButton, &QPushButton::clicked, this, [&]() {

        if (!servCustomer->getCurrentPrice()) {
            QMessageBox box;
            box.setText(QString::fromStdString("Nu exista produse in cos!\n"));
            box.exec();
            return;
        }

        servCustomer->deleteProduct(createProductFromString(customerList->currentItem()->text().toStdString()).getName());
        refreshCustomerList();
        }, Qt::UniqueConnection);
    QObject::connect(clearCart, &QPushButton::clicked, this, [&]() {
        servCustomer->emptyAll();
        refreshCustomerList();
        }, Qt::UniqueConnection);
    QObject::connect(exportFile, &QPushButton::clicked, this, [&]() {
        if (!servCustomer->getCurrentPrice()) {
            QMessageBox box;
            box.setText(QString::fromStdString("Nu exista produse in cos!\n"));
            box.exec();
            return;
        }
        std::string fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("(Collumn Separated (*.csv);;HTML(.html)")).toStdString();
        if (!fileName.size()) {
            QFile file(QString::fromStdString(fileName));
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox msg;
                msg.setText(file.errorString());
                msg.exec();
                return;
            }
        }
        std::string extension;
        std::string name;
        int start = 0, poz = 0, length = 0;
        for (const auto& it : fileName) {
            if (it == '/')
                start = poz + 1;
            if (it == '.')
                break;
            poz++;
        }
        name = fileName.substr(start);
        while (1) {
            if (name.back() != '.') {
                extension.push_back(name.back());
                name.pop_back();
            }
            else {
                name.pop_back();
                break;
            }
        }
        std::reverse(extension.begin(), extension.end());
        servCustomer->exportCart(extension, name);
        QMessageBox box;
        box.setText("Bonul a fost emis cu succes!");
        box.exec();
        refreshList();
        }, Qt::UniqueConnection);
}

std::vector<Product> ProductListDisplay::getCurrentItemsDisplayed()
{
    std::vector<Product> ret;
    for (int i = 0; i < products->count(); i++) {
        std::string s = products->item(i)->text().toStdString();
        ret.push_back(createProductFromString(s));
    }
    return ret;
}
