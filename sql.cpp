// version 1.2  15/05/2018

#include "sql.h"
#include <QDebug>
#include <QDate>
#include <QSqlError>

QString const singleSearchParam<name>::text = QString("SELECT * FROM book WHERE name=:key");
QString const singleSearchParam<author>::text = QString("SELECT * FROM book WHERE author=:key");
QString const singleSearchParam<year>::text = QString("SELECT * FROM book WHERE year=:key");

QString const doubleSearchParam<name,author>::text = QString("SELECT * FROM book WHERE name=:key1 AND author=:key2");
QString const doubleSearchParam<name,year>::text = QString("SELECT * FROM book WHERE name=:key1 AND year=:key2");
QString const doubleSearchParam<author,year>::text = QString("SELECT * FROM book WHERE author=:key1 AND year=:key2");

LibMngSys::LibMngSys(){
  if(db.isValid()){
      qDebug() << "Database is valid.";
      db.setDatabaseName("lms.db");
      if(isOpen()){
          if(!createTable()){
              qDebug() << "Error while creating table.";
            }
          else{
              qDebug() << "Tables created successfully.";
            }
        }
    }
  else{
      qDebug() << db.connectionName() << " is not available";
    }

}

LibMngSys::~LibMngSys(){
  db.close();
  qDebug() << "Connection closed!";
}

bool LibMngSys::createTable(){
  return query.exec("CREATE TABLE IF NOT EXISTS book("
                "name text,"
                "author text,"
                "year text,"
                "note text,"
                "date text,"
                "PRIMARY KEY (name,author,year) );");
}

bool LibMngSys::insertData(QString name, QString author, QString year, QString note){
  query.prepare("INSERT INTO book(name, author, year, note, date) VALUES (:name, :author, :year, :note, :date)");
  query.bindValue(":name",name);
  query.bindValue(":author",author);
  query.bindValue(":year",year);
  query.bindValue(":note",note);
  QDate date =QDate::currentDate();
  query.bindValue(":date",date);
  return query.exec();
}

QList<QList<QString> > LibMngSys::getAllData(){
  QList<QList<QString> > stringList;
  query.exec("SELECT * FROM book");
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

QList<QList<QString> > LibMngSys::getData(QString key1, QString key2, QString key3){
  QList<QList<QString> > stringList;
  query.prepare("SELECT * FROM book WHERE name=:key1 AND author=:key2 AND year=:key3");
  query.bindValue(":key1",key1);
  query.bindValue(":key2",key2);
  query.bindValue(":key3",key3);
  if (query.exec()){
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
      qDebug() << "Error getting data from database!";
      return stringList;
    }

}

bool LibMngSys::deleteData(QString name, QString author, QString year){
  query.prepare("DELETE FROM book WHERE name=:name AND author=:author AND year=:year");
  query.bindValue(":name",name);
  query.bindValue(":author",author);
  query.bindValue(":year",year);
  return query.exec();
}

bool LibMngSys::updateData(QString name, QString author, QString year,
                           QString nameNew, QString authorNew, QString yearNew, QString noteNew){
  query.prepare("UPDATE book SET name=:nameNew, author=:authorNew, year=:yearNew, note=:noteNew, date=:date WHERE name=:name AND author=:author AND year=:year");
  query.bindValue(":nameNew",nameNew);
  query.bindValue(":authorNew",authorNew);
  query.bindValue(":yearNew",yearNew);
  query.bindValue(":noteNew",noteNew);
  QDate date =QDate::currentDate();
  query.bindValue(":date",date);
  query.bindValue(":name",name);
  query.bindValue(":author",author);
  query.bindValue(":year",year);
  return query.exec();
}

bool LibMngSys::saveChanges(){
  if(!query.isActive())
      return db.commit();
  else{
      query.finish();
      return db.commit();
    }
}

bool LibMngSys::isOpen(){
  if(!db.open()){
      qDebug() << "Connection Error!..";
      return false;
    }
  else{
      qDebug() << "Connection established successfully.";
      query = QSqlQuery(db);
      return true;
    }

}
