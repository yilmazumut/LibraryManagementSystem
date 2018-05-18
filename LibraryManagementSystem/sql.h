// version 1.2  15/05/2018

#ifndef SQL_H
#define SQL_H

#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "tmp.h"
#include <book.h>

/**
 * @class LibMngSys
 * @brief The LibMngSys class manages database functions for library easily.
 * @details The class can handle connection to database, inserting, deleting, updating, searching elements and pulling them from database.
 */
class LibMngSys{
private:
  /**
   * @brief db is the database
   * @details db uses QSQLITE for database server and LibMngSysDB for database connection name
   */
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","LibMngSysDB");
    
  /**
   * @brief query is the function to use all insert, delete, search and update functions to database.
   */
    QSqlQuery query;

public:
  /**
   * @brief LibMngSys constructor.
   */
    LibMngSys();
    
 /**
  * @brief ~LibMngSys destructor.
  */
    ~LibMngSys();
  /**
   * @brief isOpen is member function to control whether database is open(true) or not(false).
   * @return boolen value, when function successfull return true, otherwise false.
   */
    bool isOpen();
  /**
   * @brief createTable is member function to create needed tables.
   * @return boolen value, when function successfull return true, otherwise false.
   */
    bool  createTable();
    
  /**
   * @brief insertBook is member function to insert new data to database.
   * @param book is type of Book
   * @return boolen value, when function successfull return true, otherwise false.
   */    
    bool  insertBook (Book* book);
    
  /**
   * @brief deleteData is member function to delete data from database
   * @param name is type of QString
   * @param author is type of QString
   * @param year is type of QString
   * @return boolen value, when function successfull return true, otherwise false.
   */    
    bool  deleteData (QString name, QString author, QString year);
    
  /**
   * @brief updateData is member function to update data in database.
   * @param name is type of QString
   * @param author is type of QString
   * @param year is type of QString
   * @param nameNew is type of QString
   * @param authorNew is type of QString
   * @param genreNew is type of QString
   * @param yearNew is type of QString
   * @param noteNew is type of QString
   * @return boolen value, when function successfull return true, otherwise false.
   */
    bool  updateData (QString name, QString author, QString year,
                      QString nameNew, QString authorNew, QString genreNew,QString yearNew, QString noteNew);
    
  /**
   * @brief saveChanges to save current database.
   * @return boolen value, when function successfull return true, otherwise false.
   */    
    bool  saveChanges();

  /**
   * @brief getData pull data from database which match the given parameters.
   * @param key1 name is type of QStinrg.
   * @param key2 name is type of QStinrg.
   * @param key3 name is type of QStinrg.
   * @return QList<QList<QString> >, all data in the row which match with given parameters.
   */   
    QList<QList<QString> >  getData      (QString key1, QString key2, QString key3);

  /**
   * @brief singleSearch is template member function.
   * @details These functions can be used for any search (e.g name search). To use them give the search paramater with describing what kind of search
   * wanted.
   * @example for example to search author with name A, singleSearch<author>("A").
   */
    template <typename T>
    QList<QList<QString> >  singleSearch (QString key);

    template <typename T1,typename T2>
    QList<QList<QString> >  doubleSearch (QString key1, QString key2);
    
  /**
   * @brief getAllData is member function which gets all of data from database.
   * @return QList<QList<QString> >.
   */
    QList<QList<QString> >  getAllData   ();
};
/**
 * @brief Implementation of singleSearch function.
 * @param key is key to search elements.
 * @details singleSearch is template search function. To use it, first describe what will be looked for and what will be searched. Data
 * are returned by given order: book name, author name, book genre, printed year, note and date (when the book is added).
 * @example To search A which is name of the book then use singleSearch<name>(A).
 * @return QList<QList<QString> >.
 */
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
