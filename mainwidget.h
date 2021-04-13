#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QToolBar>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QFileDialog>
#include "jsonhandler.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

private slots:
    void fileOpen();
    void fileSave();
public:
    std::unique_ptr<QTableWidget> m_tableWidget = nullptr;
    QToolBar m_toolbar;
    QGridLayout m_layout;
    QLabel m_label;
private:
    void initView();
    void initToolbar();
    JsonHandler jsonHandler;
    void resetTable();
};

#endif // MAINWIDGET_H
