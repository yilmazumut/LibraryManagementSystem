# version 1.0  14/05/2018

#ifndef SQL_H
#define SQL_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class LibMngSys{
private:
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","LibMngSysDB");
  QSqlQuery query;

public:
  LibMngSys();
  ~LibMngSys();

  bool isOpen();

  bool  createTable();
  bool  insertData (QString name, QString author, QString year, QString note);
  bool  deleteData (QString name, QString author, QString year);
  bool  saveChanges();

  QList<QList<QString> >  getAllData   ();
};

#endif // SQL_H
