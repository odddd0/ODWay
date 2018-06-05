#ifndef ODVECTORUTIL_H
#define ODVECTORUTIL_H

#include <ODMBase/ODBaseTypes.h>

class ODVectorUtil
{
public:
    ODVectorUtil();

public:
    template<typename T>
    static bool RefreshInsert(std::vector<T> &list_, const T &val_)
    {
        bool Result = true;
        for (auto pos = list_.begin(); pos != list_.end(); ++pos)
        {
            if ((*pos) == val_)
            {
                list_.erase(pos);
                Result = false;
                break;
            }
        }
        list_.insert(list_.begin(), val_);
        return Result;
    }
};

#endif // ODVECTORUTIL_H
