//====================================================================
//  ODMGoblinCoin.h
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMGOBLINCOIN_H_820C8F36F0820D4B04935EEEFBD9DEE4_
#define _ODMGOBLINCOIN_H_820C8F36F0820D4B04935EEEFBD9DEE4_

#include <ODMBase/ODMBase.h>
/**
 * @brief The ODMGoblinCoin struct
 *      !!! 12.22(double) -> 1222(int)
 */
struct ODMGoblinCoin : public ODMBase
{
    enum GoblinState
    {
        SimplePay = 0,
        NormalTransit = 1,
    };
public:
    ODMGoblinCoin();
    ODMGoblinCoin(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    GoblinState _state;
    std::string _goldFrom;
    int _bill;
    std::string _classify;
    std::string _kindFirst;
    std::string _kindSecond;
    int _count;
    std::string _content;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMGoblinCoin> ODMGoblinCoinPtr;

#endif // _ODMGOBLINCOIN_H_820C8F36F0820D4B04935EEEFBD9DEE4_
