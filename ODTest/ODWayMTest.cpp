
#include <gtest/gtest.h>
#include <ODWayM/ODMTime.h>
#include <ODWayM/ODWayM.h>

TEST(ODWayM, GetList)
{
    ODWayM::Instance("/Users/ine/test.db")->ReadDB();

    ODMBaseList tmpList;
    ODWayM::Instance()->GetList("ODMTime", tmpList);
}
