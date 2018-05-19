#include "addbook.h"
#include "ui_addbook.h"
#include "sql.h"
#include "QDebug"
#include <book.h>
#include "mainwindow.h"




addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
    status=false;
}

void addBook::updateBook(){
  qDebug() << Book::instance->getName();
  ui->nameInput->insert(Book::instance->getName());
  ui->authorInput->insert(Book::instance->getAuthor());
  ui->genreInput->setEditText(Book::instance->getGenre());
  ui->noteInput->setPlainText(Book::instance->getNote());
  ui->yearInput->setValue(Book::instance->getYear().toInt());
  status=true;
}

addBook::~addBook()
{
    delete this->ui;

}
/**
 * @brief The method that takes all the values on text inputs, creates a book and commits to the database.
 */
void addBook::on_addButton_clicked()
{
    LibMngSys *mng_instance = new LibMngSys();

    QString name = ui->nameInput->text();
    QString author = ui->authorInput->text();
    QString genre = ui->genreInput->currentText();
    QString year = ui->yearInput->text();
    QString note= ui->noteInput->toPlainText();

    Book* book = new Book(name,author,genre,year,note);
    if(!status){
        mng_instance->insertBook(book);
        qDebug()<<"New book Inserted!";
    }
    else{
        qDebug() << book->getNote();
        mng_instance->updateData(Book::instance->getName(),Book::instance->getAuthor(),Book::instance->getYear(),book->getName(),book->getAuthor(),book->getGenre(),book->getYear(),book->getNote());
        qDebug() << "Updated";
      }
    this->hide();

}
