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
}

addBook::~addBook()
{
    delete ui;

}

void addBook::on_addButton_clicked()
{
    LibMngSys *mng_instance = new LibMngSys();



    QString name = ui->nameInput->text();
    QString author = ui->authorInput->text();
    QString genre = ui->genreInput->currentText();
    QString year = ui->yearInput->text();

    QString note= ui->noteInput->toPlainText();
    Book* book = new Book(name,author,genre,year,note);

    mng_instance->insertBook(book);
            qDebug()<<"Book Inserted!";

}
