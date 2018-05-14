#include "sql.h"
#include <QDebug>
#include <QDate>
#include <QSqlError>

LibMngSys::LibMngSys(){
  if(db.isValid()){
      qDebug() << "Database is valid.";
      db.setDatabaseName(":memory:");
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
  return query.exec("CREATE TABLE book("
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
      //list.append(query.value(5).toString());
      stringList.append(list);
    }
  return stringList;
}

bool LibMngSys::deleteData(QString name, QString author, QString year){
  query.prepare("DELETE FROM book WHERE name=:name AND author=:author AND year=:year");
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
