#ifndef TMP_H
#define TMP_H

struct name{};
struct author{};
struct year{};

template <typename T>
struct singleSearchParam;


template <typename T1,typename T2>
struct doubleSearchParam{};

template <>
struct singleSearchParam<name>{
  static const QString text;
};

template <>
struct singleSearchParam<author>{
  static const QString text;
};

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
