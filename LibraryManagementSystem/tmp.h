// version 1.0 15/05/2018

#ifndef TMP_H
#define TMP_H

/**
 * @brief The name struct is used for singleSearch<param>.
 */
struct name{};
/**
 * @brief The author struct is used for singleSearch<param>.
 */
struct author{};
/**
 * @brief The year struct is used for singleSearch<param>
 */
struct year{};
/**
 * @brief The singleSerachParam is strcut template.
 * @details For each type of name, author and year there is a unique text. Although each unique text have some comman text, according to
 * name, author or year there is a little differences among them. Hoever, singleSerachParam is seperate these text and makes them unique.
 * @example For example singleSearchParam<name> hold "name text", but singleSearchParam<author> hold "author text".
 */
template <typename T>
struct singleSearchParam;


template <typename T1,typename T2>
struct doubleSearchParam{};
/**
 * @brief singleSearchParam<name> hold a text for name.
 * @param text is type of static const QString.
 */
template <>
struct singleSearchParam<name>{
  static const QString text;
};
/**
 * @brief singleSearchParam<author> hold a text for author.
 * @param text is type of static const QString.
 */
template <>
struct singleSearchParam<author>{
  static const QString text;
};
/**
 * @brief singleSearchParam<year> hold a text for year.
 * @param text is type of static const QString.
 */
template <>
struct singleSearchParam<year>{
  static const QString text;
};

template <>
struct doubleSearchParam<name,author>{
  static const QString text;
};

template <>
struct doubleSearchParam<name,year>{
  static const QString text;
};

template <>
struct doubleSearchParam<author,year>{
  static const QString text;
};


#endif // TMP_H
