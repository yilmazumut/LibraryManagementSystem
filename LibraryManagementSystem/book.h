#ifndef BOOK_H
#define BOOK_H
#include <QString>

/**
 * @brief The Book class that contains all the methods and attributes declared.
 */
class Book {
public:

    static Book* instance;

    Book(QString name,QString author,QString genre,QString year,QString note): name(name),author(author),genre(genre),year(year),note(note){}

    QString getName() const;

    QString getAuthor() const;

    QString getGenre() const;

    QString getYear() const;

    QString getNote() const;

    void setBookInstance(Book*);

private:
    QString name;
    QString author;
    QString genre;
    QString year;
    QString note;



};



#endif // BOOK_H
