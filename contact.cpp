#include "contact.h"

Contact::Contact(const QString& name, const QString& sname, long long number):
    m_name(name), m_surname(sname), m_number(number) {}

const QString& Contact::getName() const
{
    return m_name;
}

void Contact::setName(const QString &value)
{
    m_name = value;
}

const QString& Contact::getSurname() const
{
    return m_surname;
}

void Contact::setSurname(const QString &value)
{
    m_surname = value;
}

long long Contact::getNumber() const
{
    return m_number;
}

void Contact::setNumber(int value)
{
    m_number = value;
}
