#ifndef ADDRESSVALIDATOR_H
#define ADDRESSVALIDATOR_H

#include <QValidator>

class AddressValidator : public QValidator
{
public:
    AddressValidator();
    State validate(QString &input, int &pos) const;
    static bool isFull(QString const& input);
};

class PortValidator : public QValidator
{
public:
    PortValidator();
    State validate(QString &input, int &pos) const;
};

#endif // ADDRESSVALIDATOR_H
