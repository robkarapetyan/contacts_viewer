#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->setLayout(&m_layout);
    this->layout()->setContentsMargins(0, 0, 0, 0);
    initToolbar();
    resetTable();
    this->resize(400, 400);
}

void MainWidget::fileOpen()
{
    QString newPath = QFileDialog::getOpenFileName(this, "Open Json",
                                                   QString(),
                                                   tr("JSON files (*.JSON)"));
    if (newPath.isEmpty())
        return;

    /*
     * none of these are able to reset sorting order
     * wich is causing empty cells when trying to
     * open another file after sort order changed in
     * current
        m_tableWidget.clearContents();
        m_tableWidget.clear();
        m_tableWidget.reset();
    */
    resetTable();
    m_label.clear();

    m_label.setText(newPath.split("/", QString::KeepEmptyParts,
                                  Qt::CaseSensitivity::CaseInsensitive).last());

    std::vector<std::unique_ptr<Contact>> tmp = jsonHandler.deserialize(newPath);

    m_tableWidget->setRowCount(tmp.size());

    for (int i = 0; i < m_tableWidget->rowCount(); ++i) {
        QTableWidgetItem* nameItem;
        QTableWidgetItem* snameItem;
        QTableWidgetItem* numberItem;

        nameItem = new QTableWidgetItem();
        snameItem = new QTableWidgetItem();
        numberItem = new QTableWidgetItem();

        nameItem->setData(Qt::ItemDataRole::DisplayRole,tmp[i]->getName());
        snameItem->setData(Qt::ItemDataRole::DisplayRole,tmp[i]->getSurname());
        numberItem->setData(Qt::ItemDataRole::DisplayRole,tmp[i]->getNumber());

        m_tableWidget->setItem( i, 0, nameItem);
        m_tableWidget->setItem( i, 1, snameItem);
        m_tableWidget->setItem( i, 2, numberItem);
    }
}

void MainWidget::fileSave()
{
    jsonHandler.serialize(*m_tableWidget);
}

void MainWidget::initToolbar()
{
    QPushButton* openButton = new QPushButton("Open", this);
    connect(openButton, SIGNAL(clicked()), this, SLOT(fileOpen()));
    QPushButton* saveButton = new QPushButton("Save", this);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(fileSave()));


    m_toolbar.addWidget(openButton);
    m_toolbar.addWidget(saveButton);

    m_toolbar.layout()->setContentsMargins(0,0,20,0);
    m_layout.addWidget(&m_toolbar, 0,0);

    m_label.setParent(this);
    m_toolbar.addSeparator();
    m_toolbar.addWidget(&m_label);
}

void MainWidget::resetTable()
{
    if (m_tableWidget != nullptr)
    m_tableWidget.reset(nullptr);

    m_tableWidget = std::make_unique<QTableWidget>(this);
    m_layout.addWidget(m_tableWidget.get());
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setSortingEnabled(true);
    m_tableWidget->setAlternatingRowColors(true);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);
    m_tableWidget->setHorizontalHeaderLabels({"Name", "Surname", "Number"});
}
