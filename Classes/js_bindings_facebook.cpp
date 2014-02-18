#include "ScriptingCore.h"
#include "FacebookInterface.h"

JSBool JSB_Facebook_login(JSContext *cx, uint32_t argc, jsval *vp)
{
	int cbIndex;
	JSString * str = NULL;
	
	if (argc == 1)
		JS_ConvertArguments(cx,1,JS_ARGV(cx,vp),"i",&cbIndex);
	else
		JS_ConvertArguments(cx,2,JS_ARGV(cx,vp),"iS",&cbIndex,&str);
	
	if (str)
	{
		JSStringWrapper wrapper(str);
		FacebookInterface::login(cbIndex,wrapper);
	} 
	else
		FacebookInterface::login(cbIndex,NULL);

	return JS_TRUE;
}



void register_facebook_js(JSContext* cx, JSObject* global)
{
	jsval nsval;
	JSObject *facebookJsbObject;

	JS_GetProperty(cx, global, "FacebookJsb", &nsval);
	if (nsval == JSVAL_VOID) {
		facebookJsbObject = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(facebookJsbObject);
		JS_SetProperty(cx, global, "FacebookJsb", &nsval);
	} else 
		JS_ValueToObject(cx, nsval, &facebookJsbObject);

	JS_DefineFunction(cx, facebookJsbObject, "login", JSB_Facebook_login, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}