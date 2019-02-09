#include "addressvalidator.h"

AddressValidator::AddressValidator()    {}

QValidator::State AddressValidator::validate(QString & input, int & pos)   const   {
    if (input.isEmpty())
        return QValidator::Intermediate;
    if (input.length() > 15)
        return QValidator::Invalid;
    bool result = true;
    for (int i = 0; i < 4; i++) {
        QString section = input.section('.', i, i);
        if (!section.isEmpty()) {
            result &= (section.length() <= 3);
            bool isNumber = false;
            section.toInt(&isNumber);
            result &= isNumber;
        }
    }

    if (result)
        return QValidator::Acceptable;
    else
        return QValidator::Invalid;
}

bool AddressValidator::isFull(const QString &input) {
    for (int i = 0; i < 4; i++) {
        if (input.section('.', i, i).isEmpty())
            return false;
    }
    return true;
}

PortValidator::PortValidator()  {}

QValidator::State PortValidator::validate(QString &input, int &pos) const   {
    if (input.isEmpty())
        return QValidator::Intermediate;
    bool isNumber = false;
    while (input.endsWith(' '))
        input.chop(1);
    input.toInt(&isNumber);
    if (isNumber)
        return Acceptable;
    else
        return Invalid;
}
