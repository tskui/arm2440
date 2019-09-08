#ifndef START_CPU_H
#define START_CPU_H
#include <QCoreApplication>
#include <QFile>
#include <QDataStream>

quint32 loadbin();
quint32 loadcode();
void fetch_instruction();
void Analysis_instruction();

#endif // START_CPU_H
