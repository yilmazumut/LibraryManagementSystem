#include <book.h>

QString Book::getName() const
{
    return name;
}

QString Book::getAuthor() const
{
return author;
}

QString Book::getGenre() const
{
return genre;
}

QString Book::getYear() const
{
return year;
}

QString Book::getNote() const
{
return note;
}

 Book* Book::instance = NULL;
