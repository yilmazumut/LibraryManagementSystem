#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql.h"
#include "addbook.h"
#include "editbook.h"

int current_row;

void MainWindow::RefreshDB(){

    QList<QTableWidgetItem*> widget_item_collector;
    LibMngSys* mngSys = new LibMngSys();

    QList<QList<QString> > bookList =  mngSys->getAllData();
    ui->booksView->setRowCount(bookList.size());
    ui->booksView->setColumnCount(bookList.size());
    QStringList label_list;

    label_list.append("Name");
    label_list.append("Author");
    label_list.append("Genre");
    label_list.append("Year");

    ui->booksView->setHorizontalHeaderLabels(label_list);


    int index=0;

    for(QList<QList<QString> >::iterator itr = bookList.begin(); itr != bookList.end();itr++) {

        QTableWidgetItem *item1 = new QTableWidgetItem(itr->value(0));
        QTableWidgetItem *item2 = new QTableWidgetItem(itr->value(1));
        QTableWidgetItem *item3 = new QTableWidgetItem(itr->value(2));
        QTableWidgetItem *item4 = new QTableWidgetItem(itr->value(3));


        ui->booksView->setItem(index,0,item1);
        ui->booksView->setItem(index,1,item2);
        ui->booksView->setItem(index,2,item3);
        ui->booksView->setItem(index,3,item4);


        index++;
    }



}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RefreshDB();
}

//Problem with search query(line 70)

/*void MainWindow::on_searchButton_clicked()
{

    QString searchParam, criteria;
    searchParam = ui->searchInput->text();
    criteria = ui->searchBy_comboBox->currentText();

    LibMngSys* mngSys = new LibMngSys();

    mngSys->singleSearch(searchParam);

}
*/

void MainWindow::on_actionaddbook_triggered()
{
    addBook addBook;
    addBook.setModal(true);
    addBook.exec();
}

void MainWindow::on_booksView_cellDoubleClicked(int row, int column)
{

    qDebug() << row << " " << column;

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
        attribute_collector.push_back(current_item->text());

    }

    QMap<QString,std::vector<QString> > book_entire_details = book_edit->bookDetailsCollect(attribute_key,attribute_collector);
    book_edit->book_entire_details = book_entire_details;
    QMap<QString,std::vector<QString> > current_book_details =  book_edit->book_entire_details;
    Book *book_instance;

    for( QMap<QString,std::vector<QString> >::iterator itr = current_book_details.begin(); itr != current_book_details.end(); itr++) {

        qDebug()<<itr.key();
        std::vector<QString> current_info_collector = itr.value();
        book_instance = new Book(current_info_collector[0],current_info_collector[1],current_info_collector[2],current_info_collector[3],"");

    }


    Book::instance = book_instance;
    current_row = row;
}



void MainWindow::on_saveButton_clicked()
{

    qDebug()<<Book::instance->getName() << " " << current_row;
    std::vector<QTableWidgetItem*> item_collector;

    for(int i = 0; i < ui->booksView->columnCount(); i++) {

        QTableWidgetItem* current_item = ui->booksView->item(current_row,i);
        item_collector.push_back(current_item);
    }

    Book *curr_book_instance = new Book(item_collector[0]->text(),item_collector[1]->text(),item_collector[2]->text(),item_collector[3]->text(),"");
    LibMngSys *mng_sys = new LibMngSys();
    bool edit_success = mng_sys->updateData(Book::instance->getName(),Book::instance->getAuthor(),Book::instance->getAuthor(),curr_book_instance->getName(),curr_book_instance->getAuthor(),curr_book_instance->getGenre(),curr_book_instance->getYear(),"");
    if(edit_success) {

        qDebug()<< "editsuccess" << " " << curr_book_instance->getName();
    }

}

void MainWindow::on_deleteButton_clicked()
{
    LibMngSys *mng_sys = new LibMngSys();

  std::vector<QTableWidgetItem*> item_collector;

    for(int i = 0; i < ui->booksView->columnCount(); i++) {

        QTableWidgetItem* current_item = ui->booksView->item(ui->booksView->currentRow(),i);
        item_collector.push_back(current_item);
    }




    Book *curr_book_instance = new Book(item_collector[0]->text(),item_collector[1]->text(),item_collector[2]->text(),item_collector[3]->text(),"");
    mng_sys->deleteData(curr_book_instance->getName(),curr_book_instance->getAuthor(),curr_book_instance->getYear());

    RefreshDB();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshDatabase_clicked()
{
    RefreshDB();
}
