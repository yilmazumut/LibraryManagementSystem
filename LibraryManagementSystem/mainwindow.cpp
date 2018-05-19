#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql.h"
#include "addbook.h"
#include "editbook.h"
#include "QDebug"

std::vector<QString> notes;
/**
 * @brief Globally defined current row data.
 */
int current_row;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RefreshDB();
}

/**
 * @brief Calls and draws Database to the screen after each call.
 */
void MainWindow::RefreshDB(){

    //QList<QTableWidgetItem*> widget_item_collector;
    LibMngSys* mngSys = new LibMngSys();

    QList<QList<QString> > bookList =  mngSys->getAllData();
    ui->booksView->setRowCount(bookList.size());
    ui->booksView->setColumnCount(6);
    QStringList label_list;

    label_list.append("Name");
    label_list.append("Author");
    label_list.append("Genre");
    label_list.append("Year");
    label_list.append("Notes");
    label_list.append("Add. Date");


    ui->booksView->setHorizontalHeaderLabels(label_list);


    int index=0;

    for(QList<QList<QString> >::iterator itr = bookList.begin(); itr != bookList.end();itr++) {
        //qDebug() << index << itr->value(0);

        QTableWidgetItem *name = new QTableWidgetItem(itr->value(0));
        QTableWidgetItem *author = new QTableWidgetItem(itr->value(1));
        QTableWidgetItem *genre = new QTableWidgetItem(itr->value(2));
        QTableWidgetItem *year = new QTableWidgetItem(itr->value(3));
        QTableWidgetItem *note = new QTableWidgetItem(itr->value(4));
        QTableWidgetItem *date = new QTableWidgetItem(itr->value(5));


        //notes.push_back(note->text());

        ui->booksView->setItem(index,0,name);
        ui->booksView->setItem(index,1,author);
        ui->booksView->setItem(index,2,genre);
        ui->booksView->setItem(index,3,year);
        ui->booksView->setItem(index,4,note);
        ui->booksView->setItem(index,5,date);


        index++;
    }



}


/**
 * @brief Filters the table based on the word written in the text box on the top, with search criterias under the text box.
 */
void MainWindow::on_searchButton_clicked()
{
    LibMngSys* mngSys = new LibMngSys();
    ui->booksView->setRowCount(0);

    QList<QList<QString> > Results;

    QString searchParam,criteria;
    searchParam = ui->searchInput->text();
    criteria = ui->searchBy_comboBox->currentText();

    if(criteria=="Name"){Results = mngSys->singleSearch<name>(searchParam);}
    if(criteria=="Author"){Results = mngSys->singleSearch<author>(searchParam);}
    if(criteria=="Year"){Results = mngSys->singleSearch<year>(searchParam);}

    ui->booksView->setRowCount(Results.size());


    int index=0;

    for(QList<QList<QString> >::iterator itr = Results.begin(); itr != Results.end();itr++) {

        QTableWidgetItem *item1 = new QTableWidgetItem(itr->value(0));
        QTableWidgetItem *item2 = new QTableWidgetItem(itr->value(1));
        QTableWidgetItem *item3 = new QTableWidgetItem(itr->value(2));
        QTableWidgetItem *item4 = new QTableWidgetItem(itr->value(3));
        QTableWidgetItem *item5 = new QTableWidgetItem(itr->value(4));
        QTableWidgetItem *item6 = new QTableWidgetItem(itr->value(5));

        ui->booksView->setItem(index,0,item1);
        ui->booksView->setItem(index,1,item2);
        ui->booksView->setItem(index,2,item3);
        ui->booksView->setItem(index,3,item4);
        ui->booksView->setItem(index,4,item5);
        ui->booksView->setItem(index,5,item6);


        index++;
    }


}

/**
 * @brief Opens the window "Add Book".
 */
void MainWindow::on_actionaddbook_triggered()
{
    addBook addBook;
    //addBook.setModal(true);
    addBook.exec();
    RefreshDB();
    //qDebug() << "hello";
    //addBook.close();
}

/**
 * @brief Collects the Books's data which is double-clicked cell belongs to and and makes it possible to be edited.
 * @param Current Row
 * @param Current Column
 */
void MainWindow::on_booksView_cellDoubleClicked(int row, int column)
{
    //qDebug() << row << " " << column;

    std::vector<QString> attribute_collector;
    QString attribute_key;

    QTableWidgetItem *selected_item = ui->booksView->item(row,column);
    QTableWidgetItem *label_header = ui->booksView->horizontalHeaderItem(column);



    EditBook<QString,QString,std::vector<QString> > *book_edit = new EditBook<QString,QString,std::vector<QString> >();
    QMap<QString,QString> selected_book_map = book_edit->getBookDetails(label_header,selected_item);


    for( QMap<QString,QString>::iterator itr = selected_book_map.begin(); itr != selected_book_map.end();itr++) {
        attribute_key = itr.key();
    }

    for(int col = 0; col < ui->booksView->columnCount(); col++) {

        QTableWidgetItem *current_item =  ui->booksView->item(row,col);
        //qDebug() << "current_item->text()" << current_item->text() ;
        attribute_collector.push_back(current_item->text());

    }

    QMap<QString,std::vector<QString> > book_entire_details = book_edit->bookDetailsCollect(attribute_key,attribute_collector);
    book_edit->book_entire_details = book_entire_details;
    QMap<QString,std::vector<QString> > current_book_details =  book_edit->book_entire_details;
    Book *book_instance;

    for( QMap<QString,std::vector<QString> >::iterator itr = current_book_details.begin(); itr != current_book_details.end(); itr++) {

        //qDebug()<<itr.key();
        std::vector<QString> current_info_collector = itr.value();
        book_instance = new Book(current_info_collector[0],current_info_collector[1],current_info_collector[2],current_info_collector[3],current_info_collector[4]);

    }


    Book::instance = book_instance;
    current_row = row;
    addBook ab;
    ab.updateBook();
    ab.exec();
    qDebug() << "continue";
    LibMngSys *mng_sys = new LibMngSys();
    mng_sys->saveChanges();
    RefreshDB();
    qDebug()<< "edit success" << " " << Book::instance->getName();

    /*std::vector<QTableWidgetItem*> item_collector;

    for(int i = 0; i < ui->booksView->columnCount(); i++) {

        QTableWidgetItem* current_item = ui->booksView->item(current_row,i);
        item_collector.push_back(current_item);
    }


    Book *curr_book_instance = new Book(item_collector[0]->text(),item_collector[1]->text(),item_collector[2]->text(),item_collector[3]->text(),item_collector[4]->text());
    LibMngSys *mng_sys = new LibMngSys();
    bool edit_success = mng_sys->updateData(Book::instance->getName(),Book::instance->getAuthor(),Book::instance->getYear(),curr_book_instance->getName(),curr_book_instance->getAuthor(),curr_book_instance->getGenre(),curr_book_instance->getYear(),curr_book_instance->getNote());

    if(edit_success) {
        mng_sys->saveChanges();
        RefreshDB();
        qDebug()<< "edit success" << " " << curr_book_instance->getName();


    }*/
}


/**
 * @brief Commits the changed attributes of the book to the database.
 */
void MainWindow::on_saveButton_clicked()
{

  LibMngSys *mng_sys = new LibMngSys();
  mng_sys->saveChanges();
  RefreshDB();
  //qDebug() << "Saved";

}

/**
 * @brief Deletes the row which is clicked on the table.
 */
void MainWindow::on_deleteButton_clicked()
{
    LibMngSys *mng_sys = new LibMngSys();

  std::vector<QTableWidgetItem*> item_collector;

    for(int i = 0; i < ui->booksView->columnCount(); i++) {

        QTableWidgetItem* current_item = ui->booksView->item(ui->booksView->currentRow(),i);
        item_collector.push_back(current_item);
    }

    //notes.erase(notes.begin(),notes.begin()+ui->booksView->currentRow());

    Book *curr_book_instance = new Book(item_collector[0]->text(),item_collector[1]->text(),item_collector[2]->text(),item_collector[3]->text(),item_collector[4]->text());
    mng_sys->deleteData(curr_book_instance->getName(),curr_book_instance->getAuthor(),curr_book_instance->getYear());
    qDebug() << "hello";
    RefreshDB();
}

/**
 * @brief Reloads the database.
 */
void MainWindow::on_refreshDatabase_clicked()
{
    RefreshDB();
}

/**
 * @brief Gets clicked cell's information and brings the note which is associated with it.
 * @param Current Row
 * @param Current Column
 */
void MainWindow::on_booksView_cellClicked(int row)
{
    QTableWidgetItem *current_item =  ui->booksView->item(row,4);
    ui->notesTextEdit->setText(current_item->text());

    //std::vector<QString>::iterator itr = notes.begin();
    //ui->notesTextEdit->setText(notes.at(row));

}

MainWindow::~MainWindow()
{
    delete ui;
    notes.clear();
}
