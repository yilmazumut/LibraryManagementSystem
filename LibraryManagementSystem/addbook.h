#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include <QLineEdit>


namespace Ui {
class addBook;
}

class addBook : public QDialog
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = 0);
    void updateBook();
    ~addBook();

private slots:
    void on_addButton_clicked();


private:
    Ui::addBook *ui;
    bool status;
};

#endif // ADDBOOK_H
