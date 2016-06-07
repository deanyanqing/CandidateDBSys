#ifndef COMMON_H
#define COMMON_H

#include <exception>
#include <QString>
#include <map>
const static int MAX_ROWS_IN_TABLE=100;

struct Person
{
    QString chinseName;
    QString englisthName;
    QString gender;
    QString label;
    QString company;
    QString orgnazation;
    QString title;
    QString mobile;
    QString email;
    QString location;
    QString generalInfo;
    QString timeStamp;
};

enum ATTRIBUTES_DEF
{
    ATTR_CHINDES_NAME =0,
    ATTR_ENGLISH_NAME,
    ATTR_GENDER,
    ATTR_LABEL,
    ATTR_COMPANY,
    ATTR_ORGNAZATION,
    ATTR_TITLE,
    ATTR_MOBILE,
    ATTR_EMAIL,
    ATTR_LOCATION,
    ATTR_GENERAL_INFO,
    ATTR_TIME_STAMP,


    ATTR_MAX
};
typedef std::map<ATTRIBUTES_DEF,QString> QueryInput;
class MyException:public std::exception
{
 public:
    virtual const char* what() const throw()
      {
        return description.toStdString().c_str();
      }

    MyException(QString description){this->description =  description;}

private:
    QString description;
};



#endif // COMMON_H
