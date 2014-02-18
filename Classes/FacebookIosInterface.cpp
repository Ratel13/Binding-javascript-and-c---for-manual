//
//  FacebookIosInterface.cpp
//  tojs
//
//  Created by lyy on 13-8-20.
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "FacebookInterface.h"
#include "ScriptingCore.h"
using namespace std;

void FacebookInterface::login(int cbIndex,const char* scope)
{
    CCLOG("logIn.....");
	FacebookInterface::callbackJs(10000, "longINCallBack");
}


extern jsval anonEvaluate(JSContext *cx, JSObject *thisObj, const char* string);
JSObject *fbObject = NULL;
void FacebookInterface::callbackJs(int cbIndex, const char* params)
{
    CCLOG("111");
	ScriptingCore* sc = ScriptingCore::getInstance();
	JSContext *cx = sc->getGlobalContext();
	
	if (fbObject == NULL)
		fbObject = JSVAL_TO_OBJECT(anonEvaluate(cx, sc->getGlobalObject(), "(function () { return FB; })()"));
	
	jsval res;
    if (fbObject) {
        CCLOG("SDFSD");
    }
	
    CCLOG("222");
	if (params != NULL)
	{
		jsval argv[2];
		argv[0] = INT_TO_JSVAL(cbIndex);
		std::string tstr = params;
		argv[1] = std_string_to_jsval(cx,tstr);
        JS_AddValueRoot(cx, argv);
        CCLOG("333, %s", tstr.c_str());
		JS_CallFunctionName(cx, fbObject, "callback", 2, argv, &res);
        CCLOG("call fb,");
        JS_RemoveValueRoot(cx, argv);
	}
	else
	{
        CCLOG("444");
		jsval argv[1];
		argv[0] = INT_TO_JSVAL(cbIndex);
        
		JS_CallFunctionName(cx, fbObject, "callback", 1, argv, &res);
	}
    CCLOG("555");
}

#endif
