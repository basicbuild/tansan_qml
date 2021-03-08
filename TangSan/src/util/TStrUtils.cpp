#include "TStrUtils.h"
#include <QString>
#include <QCryptographicHash>

QString StrUtils::getMD5(const QByteArray& data)
{
    QByteArray ba = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    QString result;
    result.append(ba.toHex());
    return result;
}
