#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static QMap<QString,std::vector<QString> > collector;

    void RefreshDB();


private slots:
    //void on_actionAdd_Books_triggered();


   // void on_searchButton_clicked();

   // void on_actionEdit_Books_triggered();

    void on_actionaddbook_triggered();

    //void on_booksView_cellClicked(int row, int column);

    void on_booksView_cellDoubleClicked(int row, int column);

    void on_saveButton_clicked();

    //void on_booksView_clicked(const QModelIndex &index);

    void on_deleteButton_clicked();


    void on_refreshDatabase_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
