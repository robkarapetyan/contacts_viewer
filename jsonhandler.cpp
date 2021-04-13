#include "jsonhandler.h"


JsonHandler::JsonHandler()
{

}

std::vector<std::unique_ptr<Contact>> JsonHandler::deserialize(const QString& path)
{
    m_path = path;

    if (checkPath(RWOption::read) == false) {
        return {};
    }
    std::vector<std::unique_ptr<Contact>> contactsFromJson = {};
    QJsonObject mainObj = lib_json_doc.object();
    QJsonArray contacts = mainObj["Contacts"].toArray();

    for (const auto& v : contacts) {
        QJsonObject element = v.toObject();

        long long number = element["number"].toVariant().toLongLong();
        QString name = element["name"].toString();
        QString sname = element["sname"].toString();

        Contact tmpContact(name, sname, number);
        contactsFromJson.push_back(std::make_unique<Contact>(name, sname, number));
    }
    return contactsFromJson;
}

bool JsonHandler::serialize(const QTableWidget &tableWidget)
{

    if (checkPath(RWOption::write) == false) {
        return false;
    }

    QJsonObject mainObj;
    QJsonArray contacts;

    for (int i = 0; i < tableWidget.rowCount(); ++i) {
        QTableWidgetItem* nameItem;
        QTableWidgetItem* snameItem;
        QTableWidgetItem* numberItem;

        nameItem = tableWidget.item(i,0);
        snameItem = tableWidget.item(i,1);
        numberItem = tableWidget.item(i,2);

        QJsonObject currentObject;
        currentObject.insert("name", nameItem->data(Qt::ItemDataRole::DisplayRole).toString());
        currentObject.insert("sname", snameItem->data(Qt::ItemDataRole::DisplayRole).toString());
        currentObject.insert("number", numberItem->data(Qt::ItemDataRole::DisplayRole).toLongLong());

        contacts.append(currentObject);
    }

    mainObj["Contacts"] = contacts;

    QFile outFile (m_path);
    if (!outFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qWarning ("Failed to open file for writing." );
        return false;
    }
    QJsonDocument doc (mainObj);
    outFile.write (doc.toJson());
    outFile.close();

    return true;
}

bool JsonHandler::checkPath(const RWOption& opt)
{
    QFile saveFile(m_path);
    if(opt == RWOption::read){
        if (!saveFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open file for reading.");
            return false;
        }
        lib_json_doc = QJsonDocument( QJsonDocument::fromJson(saveFile.readAll()));
    } else if (opt == RWOption::write){
        if( !saveFile.open( QIODevice::WriteOnly) )
        {
            qWarning( "Failed to open the file for writing." );
            return false;
        }
    }

    saveFile.close();
    return true;
}
