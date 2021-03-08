#ifndef TLOGGING_H
#define TLOGGING_H

#include <QDebug>
#define LOGT(TAG,fmt)    qDebug() <<  TAG << ':' <<  __FUNCTION__ << "Line:"<<  __LINE__ << fmt <<endl;

#define PR(...) printf(__VA_ARGS__)
#endif // TLOGGING_H
