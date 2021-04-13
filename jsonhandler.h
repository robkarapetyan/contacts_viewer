#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <memory>
#include <vector>
#include "contact.h"
#include <QTableWidget>

enum class RWOption {read, write};

class JsonHandler
{
public:
    JsonHandler();
    std::vector<std::unique_ptr<Contact>> deserialize(const QString& path);
    bool serialize(const QTableWidget& tableWidget);
private:
    QString m_path = "";
    QJsonDocument lib_json_doc;
private:
    bool checkPath(const RWOption& opt);
};

#endif // JSONHANDLER_H
