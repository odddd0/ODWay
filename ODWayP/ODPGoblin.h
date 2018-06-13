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

    };
    typedef std::shared_ptr<OneGnome> OneGnomePtr;

    struct ExpandData
    {
        ExpandData();
        void clear();

        StringList _goldFromList;
        std::map<std::string, OneGnomePtr> _gnomeMap;
        CKKPtr _ckk;
    };
public:
    static ODPGoblin * Instance();

public:
    // add
    bool AddSimplePay(const ODMGoblinCoinPtr &ptr_);
    void GetCKK(CKKPtr &ckk_);

public:
    // Gnome
    // add
    bool AddGnome(const ODMBasePtr &ptr_);

    // get
    void GetGoldFromList(StringList &list_);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPGoblin();
    ~ODPGoblin();
};

#endif // _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_
