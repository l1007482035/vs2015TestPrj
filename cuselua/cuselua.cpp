// cuselua.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>  
#include <string>  

extern "C"
{
#include <lua.h>  
#include <lualib.h>  
#include <lauxlib.h>  
};
#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "lua51.lib")
using namespace std;

// 初始化Lua环境.  
lua_State* initLuaEnv()
{
	lua_State* luaEnv = lua_open();
	luaopen_base(luaEnv);
	luaL_openlibs(luaEnv);

	return luaEnv;
}

// 加载Lua文件到Lua运行时环境中
bool loadLuaFile(lua_State* luaEnv, const string& fileName)
{
	int result = luaL_loadfile(luaEnv, fileName.c_str());
	if (result)
	{
		return false;
	}

	result = lua_pcall(luaEnv, 0, 0, 0);
	return result == 0;

	//这里可以用luaL_dofile代替
}

// 获取全局函数
lua_CFunction getGlobalProc(lua_State* luaEnv, const string& procName)
{
	lua_getglobal(luaEnv, procName.c_str());
	if (!lua_iscfunction(luaEnv, 1))
	{
		printf("==========1\n");
		return 0;
	}
	else
	{
		printf("==========2\n");
	}
	

	return lua_tocfunction(luaEnv, 1);
}

int main()
{
	lua_State *luaEnv = luaL_newstate();
	if (!luaEnv)
	{
		printf("!!main,1,luaEnv is null\n");
		return -1;
	}
	luaL_openlibs(luaEnv);
	if (luaL_dofile(luaEnv, ".\\luaforc.lua"))
	{
		printf("!!main,2,luaL_dofile fail,err=%s\n",lua_tostring(luaEnv,-1));
		return -1;
	}
	lua_getglobal(luaEnv, "add");
	if (!lua_isfunction(luaEnv, -1))
	{
		printf("!!main,3,add is not function\n");
		return -1;
	}
	lua_pushnumber(luaEnv,10);
	lua_pushnumber(luaEnv,20);
	lua_pcall(luaEnv, 2, 1, 0);
	int nRet = lua_tointeger(luaEnv, -1);
	printf("main,4,res,nRet=%d\n", nRet);
	// 释放Lua运行时环境.  
	lua_close(luaEnv);


#if 0
	// 初始化Lua运行时环境.  
	//lua_State* luaEnv = initLuaEnv();

	lua_State* luaEnv = lua_open();
	luaopen_base(luaEnv);
	luaL_openlibs(luaEnv);

	if (!luaEnv)
	{
		printf("!!luaEnv is null,err=%s\n", lua_tostring(luaEnv, -1));
		return -1;
	}

	// 加载脚本到Lua环境中.  
// 	if (!loadLuaFile(luaEnv, ".\\luaforc.lua"))
// 	{
// 		cout << "Load Lua File FAILED!" << endl;
// 		return -1;
// 	}

#if 0
	int result = luaL_loadfile(luaEnv, ".\\luaforc.lua");
	if (result)
	{
		printf("!!luaL_dofile fail,ddddd,err=%s\n", lua_tostring(luaEnv, -1));
		return -1;
	}

	result = lua_pcall(luaEnv, 0, 0, 0);

#endif

#if 1
	//luaL_dofile 正确返回false 错误返回true
	if (luaL_dofile(luaEnv,".\\luaforc.lua"))
	{
		printf("!!luaL_dofile fail,err=%s\n", lua_tostring(luaEnv, -1));
		return -1;
	}
#endif
	


	int x = 10, y = 30;

	//getGlobalProc(luaEnv,"add");

	// 将要调用的函数和函数调用参数入栈.  
	//lua_getglobal(luaEnv, "add");


	lua_getglobal(luaEnv, "add");//将add压栈，放在栈顶
#if 0 //测试获取lua中全局变量fff的值
	lua_getglobal(luaEnv, "fff");//测试全局变量fff
	int nRet = luaL_checknumber(luaEnv, -1);

	printf("=============nRet=%d\n", nRet);
#endif

	bool bIsFunction = lua_isfunction(luaEnv, -1);

	printf("call lua,bIsFunction=%d\n", bIsFunction);



	lua_pushnumber(luaEnv, x);
	lua_pushnumber(luaEnv, y);
	lua_pushstring
	//lua_pushstring(luaEnv, fromName.c_str());
	//lua_pushstring(luaEnv, toName.c_str());
	//lua_pushstring(luaEnv, msgContent.c_str());

	// 调用Lua函数（1表示入参个数,1表示返回值个数）.  
	lua_pcall(luaEnv, 2, 1, 0);


#if 0
	// 获取返回值.  
	if (lua_isboolean(luaEnv, -1))
	{
		int success = lua_toboolean(luaEnv, -1);
		if (success)
		{
			cout << "\nGenerate Note File Successful!" << endl;
		}
	}
#endif

	// 将返回值出栈.  
	lua_pop(luaEnv, 1);

	// 释放Lua运行时环境.  
	lua_close(luaEnv);

	//system("pause");
	return 0;
#endif
	return 0;
}

