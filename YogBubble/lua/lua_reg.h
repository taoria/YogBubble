#pragma once
#include "../stdafx.h"
class lua_State;
int YOG_DLL_EXPORT LuaCreateNewEntity(lua_State* l);
int YOG_DLL_EXPORT LuaSetTransformPos(lua_State* l);
int YOG_DLL_EXPORT LuaGetTransformPos(lua_State* l);
int YOG_DLL_EXPORT LuaGetTransformRot(lua_State* l);
int LuaSettTransformRot(lua_State* l);
int LuaAddComponent(lua_State* l);
int YOG_DLL_EXPORT LuaRegisterModel(lua_State *l);
int LuaLinkToModel(lua_State *l);
int YOG_DLL_EXPORT LuaDestroyEntity(lua_State *l);

int luaopen_entity_libs(lua_State* L);