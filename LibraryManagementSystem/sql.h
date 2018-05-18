// version 1.2  15/05/2018

#ifndef SQL_H
#define SQL_H

#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "tmp.h"
#include <book.h>


class LibMngSys{
private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","LibMngSysDB");
    QSqlQuery query;

public:
    LibMngSys();
    ~LibMngSys();

    bool isOpen();

    bool  createTable();
    bool  insertBook (Book* book);
    bool  deleteData (QString name, QString author, QString year);
    bool  updateData (QString name, QString author, QString year,
                      QString nameNew, QString authorNew, QString genreNew,QString yearNew, QString noteNew);
    bool  saveChanges();

    QList<QList<QString> >  getData      (QString key1, QString key2, QString key3);

    template <typename T>
    QList<QList<QString> >  singleSearch (QString key);

    template <typename T1,typename T2>
    QList<QList<QString> >  doubleSearch (QString key1, QString key2);

    QList<QList<QString> >  getAllData   ();
};

template <typename T>
QList<QList<QString> > LibMngSys::singleSearch(QString key){
    query.prepare( singleSearchParam<T>::text );
    query.bindValue(":key",key);
    QList<QList<QString> > stringList;
    if(query.exec()){
        while(query.next()){
            QList<QString> list;
            list.append(query.value(0).toString());
            list.append(query.value(1).toString());
            list.append(query.value(2).toString());
            list.append(query.value(3).toString());
            list.append(query.value(4).toString());
            stringList.append(list);
        }
        return stringList;
    }
    else{
        qDebug() << "Query execution error.";
        return stringList;
    }
}

template <typename T1, typename T2>
QList<QList<QString> > LibMngSys::doubleSearch(QString key1, QString key2){
    query.prepare( doubleSearchParam<T1,T2>::text );
    query.bindValue(":key1",key1);
    query.bindValue(":key2",key2);
    QList<QList<QString> > stringList;
    if(query.exec()){
        while(query.next()){
            QList<QString> list;
            list.append(query.value(0).toString());
            list.append(query.value(1).toString());
            list.append(query.value(2).toString());
            list.append(query.value(3).toString());
            list.append(query.value(4).toString());
            stringList.append(list);
        }
        return stringList;
    }
    else{
        qDebug() << "Query execution error.";
        return stringList;
    }
}

#endif // SQL_H
