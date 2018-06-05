#ifndef _ODMBASE_H_2ECF0B1817956EF0747B103CD8300A09_
#define _ODMBASE_H_2ECF0B1817956EF0747B103CD8300A09_

#include "ODBaseTypes.h"

struct ODMBase
{
public:
    ODMBase(const int &id_);
    ODMBase(const std::string &type_);
    ODMBase(const std::string &type_, const int &id_);

public:
    virtual void GetSqlInsert(std::string &sql_) = 0;
    virtual void GetSqlUpdate(std::string &sql_) = 0;

public:
    int _preId;
    int _id;
    std::string _type;
};
typedef std::shared_ptr<ODMBase> ODMBasePtr;
typedef std::vector<ODMBasePtr> ODMBaseList;

#endif // _ODMBASE_H_2ECF0B1817956EF0747B103CD8300A09_
