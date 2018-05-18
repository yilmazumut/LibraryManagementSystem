#ifndef EDITBOOK_H
#define EDITBOOK_H


#include <QTableWidgetItem>
#include <book.h>


template<class T,class T1,class T2>

class EditBook {

public:

    static QMap<T1,T2> book_entire_details;

    QMap<T,T> getBookDetails(QTableWidgetItem *item,QTableWidgetItem *header){
        QMap<T,T> current_map;
        current_map.insert (item->text(),header->text());
        return current_map;
    }



    QMap<T1,T2> bookDetailsCollect(QString key,std::vector<QString> val) {

        QMap<T1,T2> book_details_collector;
        book_details_collector.insert(key,val);

        return book_details_collector;
    }




};

template<typename T,typename T1, typename T2>

QMap<T1,T2 > EditBook<T,T1,T2>::book_entire_details;

#endif // EDITBOOK_H
