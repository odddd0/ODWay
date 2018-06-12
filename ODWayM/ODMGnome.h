//====================================================================
//  ODMGnome.h
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMGNOME_H_DA216B92D6FEE843BA89FA27434D1BB9_
#define _ODMGNOME_H_DA216B92D6FEE843BA89FA27434D1BB9_

#include <ODMBase/ODMBase.h>
/**
 * @brief The ODMGnome struct
 *      !!! 12.22(double) -> 1222(int)
 */
struct ODMGnome : public ODMBase
{
public:
    ODMGnome();
    ODMGnome(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    std::string _name;
    int _balance;
    int _availableCreditLimits;
    int _creditLimits;
    int _billDates;
    int _dueDay;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMGnome> ODMGnomePtr;

#endif // _ODMGNOME_H_DA216B92D6FEE843BA89FA27434D1BB9_
