// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

extern "C" {
#include "lua.h"  
#include "lualib.h"  
#include "lauxlib.h"
};
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "lua51.lib")
//; lua51.lib;
#include <iostream>  
using namespace std;
extern "C" int ShowMsg(lua_State* luaEnv) 
{
	int nParamCount = lua_gettop(luaEnv);//获取栈顶元素即参数个数
	printf("ShowMsg,0,nParamCount=%d\n", nParamCount);
	//下面通过正负索引的方式打印栈元素

	printf("=======正索引遍历栈元素\n");
	//正索引 1到nParamCount  从栈底到栈顶
	for (int i = 1;i <= nParamCount;i++)
	{
		int nType = lua_type(luaEnv, i);
		if (LUA_TNUMBER == nType)
		{
			printf("ShowMsg,nType[%d]=%f\n", i, luaL_checknumber(luaEnv, i));
		}
		else if (LUA_TSTRING == nType)
		{
			printf("ShowMsg,nType[%d]=%s\n", i, luaL_checkstring(luaEnv, i));
		}
	}
#if 1

	printf("=======负索引遍历栈元素\n");

	//负索引-1到-1-nParamCount  从栈栈顶到栈底
	for (int i = -1; i >= 0-nParamCount; i--)
	{
		int nType = lua_type(luaEnv, i);
		if (LUA_TNUMBER == nType)
		{
			printf("ShowMsg,nType[%d]=%f\n", i, luaL_checknumber(luaEnv, i));
		}
		else if (LUA_TSTRING == nType)
		{
			printf("ShowMsg,nType[%d]=%s\n", i, luaL_checkstring(luaEnv, i));
		}
	}
#endif
	lua_pushnumber(luaEnv,100);
	lua_pushstring(luaEnv,"returnV1");
	return 2; // 返回值个数为0个.  
}

// part one: 要导出的函数列表
static luaL_Reg luaLibs[] = {
	{ "ShowMsg", ShowMsg },
	{ NULL, NULL }
};

// part two: DLL入口函数，Lua调用此DLL的入口函数.  
extern "C" __declspec(dllexport) int luaopen_cforlua(lua_State* luaEnv)
{   //WinFeature是modole名, 将来require这个名字
	const char* const LIBRARY_NAME = "cforlua"; //这里也写WinFeature
	luaL_register(luaEnv, LIBRARY_NAME, luaLibs);  //关键一行, 在luaState上注册好这个lib
	return 1;
}
