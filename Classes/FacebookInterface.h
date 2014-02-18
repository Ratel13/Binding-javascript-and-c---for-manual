#ifndef  __INTERFACE_FACEBOOK_H_
#define  __INTERFACE_FACEBOOK_H_

#include "string"

class FacebookInterface
{
public:
    static void login(int cbIndex,const char* scope);

    //for callback
    static void callbackJs(int cbIndex, const char* params);
};

#endif  //__INTERFACE_FACEBOOK_H_