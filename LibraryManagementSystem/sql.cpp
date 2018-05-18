// version 1.2  15/05/2018

#include "sql.h"
#include <QDebug>
#include <QDate>
#include <QSqlError>

/**
 * @brief singleSearchParam<name>::text is QString.
 */
QString const singleSearchParam<name>::text = QString("SELECT * FROM book WHERE name=:key");
/**
 * @brief singleSearchParam<author>::text is QString.
 */
QString const singleSearchParam<author>::text = QString("SELECT * FROM book WHERE author=:key");
/**
 * @brief singleSearchParam<name>::text is QString.
 */
QString const singleSearchParam<year>::text = QString("SELECT * FROM book WHERE year=:key");

/*QString const doubleSearchParam<name,author>::text = QString("SELECT * FROM book WHERE name=:key1 AND author=:key2");
QString const doubleSearchParam<name,year>::text = QString("SELECT * FROM book WHERE name=:key1 AND year=:key2");
QString const doubleSearchParam<author,year>::text = QString("SELECT * FROM book WHERE author=:key1 AND year=:key2");*/

/**
 * @brief LibMngSys::LibMngSys is constructor.
 * @details The function checks whether creating database is valid or not, if true then it sets the database name and try to open it.
 * If there is no problem then define the tables will be used in database for the firt time.
 */
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

/**
 * @brief LibMngSys::~LibMngSys is destruction.
 * @details When object deleted then it's database connection closed.
 */
LibMngSys::~LibMngSys(){
  db.close();
  qDebug() << "Connection closed!";
}

/**
 * @brief LibMngSys::createTable creates all tables which will be used for database.
 * @return boolen value.
 */
bool LibMngSys::createTable(){
  return query.exec("CREATE TABLE IF NOT EXISTS book("
                "name text,"
                "author text,"
                "genre text,"
                "year text,"
                "note text,"
                "date text,"
                "PRIMARY KEY (name,author,year) );");
}

/**
 * @brief LibMngSys::insertBook inserts new books into database.
 * @param book is type of Book.
 * @return boolen value.
 */
 bool LibMngSys::insertBook(Book* book){
  query.prepare("INSERT INTO book(name, author, genre, year, note, date) VALUES (:name, :author,:genre, :year, :note, :date)");
  query.bindValue(":name",book->getName());
  query.bindValue(":author",book->getAuthor());
  query.bindValue(":genre",book->getGenre());
  query.bindValue(":year",book->getYear());
  query.bindValue(":note",book->getNote());
  QDate date =QDate::currentDate();
  query.bindValue(":date",date);
  return query.exec();
}

/**
 * @brief LibMngSys::getAllData gets all rows of information from database.
 * @details Function returns list of list of QString of data in the given order book name, author name, book genre, printed year, note and when it is added.
 * @return QList<QList<QString> >.
 */
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
      list.append(query.value(5).toString());
      stringList.append(list);
    }
  return stringList;
}

/**
 * @brief LibMngSys::getData gets single row of information from database which row match the given paramters.
 * @param key1 is name of the book
 * @param key2 is author of the book
 * @param key3 is printed year of the book.
 * @details Data are returned by given order: book name, author name, book genre, printed year, note and date (when the book is added).
 * @return QList<QList<QString> >.
 */
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
          list.append(query.value(5).toString());
          stringList.append(list);
        }
      return stringList;
    }
  else{
      qDebug() << "Error getting data from database!";
      return stringList;
    }

}

/**
 * @brief LibMngSys::deleteData delete one row of information.
 * @param name is book name.
 * @param author is author name.
 * @param year is printed year of the book.
 * @details Removes books which matchs given parameters.
 * @return boolen value
 */
bool LibMngSys::deleteData(QString name, QString author, QString year){
  query.prepare("DELETE FROM book WHERE name=:name AND author=:author AND year=:year");
  query.bindValue(":name",name);
  query.bindValue(":author",author);
  query.bindValue(":year",year);
  return query.exec();
}

/**
 * @brief LibMngSys::updateData updates database to change row of information which match with given parameters.
 * @param name is book name.
 * @param author is author name.
 * @param year is printed year of the book.
 * @param nameNew is new name(if it is changed).
 * @param authorNew is new author(if it is changed).
 * @param genreNew is new genre(if it is changed).
 * @param yearNew is new year(if it is changed).
 * @param noteNew is new note(if it is changed).
 * @return boolen value.
 */
bool LibMngSys::updateData(QString name, QString author, QString year,
                           QString nameNew, QString authorNew, QString genreNew, QString yearNew, QString noteNew){
  query.prepare("UPDATE book SET name=:nameNew, author=:authorNew, genre=:genreNew, year=:yearNew, note=:noteNew, date=:date WHERE name=:name AND author=:author AND year=:year");
  query.bindValue(":nameNew",nameNew);
  query.bindValue(":authorNew",authorNew);
  query.bindValue(":genreNew",genreNew);
  query.bindValue(":yearNew",yearNew);
  query.bindValue(":noteNew",noteNew);
  QDate date =QDate::currentDate();
  query.bindValue(":date",date);
  query.bindValue(":name",name);
  query.bindValue(":author",author);
  query.bindValue(":year",year);
  return query.exec();
}

/**
 * @brief LibMngSys::saveChanges saves current status of database.
 * @return boolen value.
 */
bool LibMngSys::saveChanges(){
  if(!query.isActive()){
      qDebug() <<"unsaved";
      return db.commit();}
  else{
      qDebug() <<"saved";
      query.finish();
      return db.commit();
    }
}

/**
 * @brief LibMngSys::isOpen checks whether database is open or not.
 * @return
 */
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
