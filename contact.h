#ifndef CONTACT_H
#define CONTACT_H
#include <QString>

class Contact
{
public:
    Contact() = default;
    Contact(const QString& _name, const QString& _sname, long long _number);
    ~Contact() = default;

    const QString& getName() const;
    void setName(const QString &value);

    const QString& getSurname() const;
    void setSurname(const QString &value);

    long long getNumber() const;
    void setNumber(int value);

private:
    QString m_name = "";
    QString m_surname = "";
    long long m_number = 0;
};

#endif // CONTACT_H
