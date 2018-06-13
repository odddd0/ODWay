//====================================================================
//  ODPGoblin.h
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_
#define _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_

#include <ODMBase/ODBaseTypes.h>
#include <ODUtil/ODCKK.h>
#include <ODWayM/ODMGoblin.h>
#include <ODWayM/ODMGoblinCoin.h>
#include <ODWayM/ODMGnome.h>

class ODPGoblin
{
    struct OneGnome
    {
        OneGnome();

        int _balance;
        int _creditLimits;
        int _billDates;
        int _dueDay;
        std::vector<int> _billList;
    };
    typedef std::shared_ptr<OneGnome> OneGnomePtr;

    struct ExpandData
    {
        ExpandData();
        void clear();
        bool appendGnome(const ODMBasePtr &ptr_);
        bool appendCoin(const ODMBasePtr &ptr_);

        StringList _goldFromList;
        std::map<std::string, OneGnomePtr> _gnomeMap;
        CKKPtr _ckk;
    };
public:
    static ODPGoblin * Instance();

public:
    // add
    bool AddGoblin(const ODMBasePtr &ptr_);
    void GetCKK(CKKPtr &ckk_);

public:
    // Gnome
    // get
    void GetGoldFromList(StringList &list_);
    void GetGnomeList(StringList &list_);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPGoblin();
    ~ODPGoblin();
};

#endif // _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_
