/*************************************************************************************
*	irrlamb - http://irrlamb.googlecode.com
*	Copyright (C) 2011  Alan Witkowski
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************************/
#ifndef SCRIPTING_H
#define SCRIPTING_H

// Libraries
#include "singleton.h"
#include <lua.hpp>
#include <map>
#include <list>
#include <string>

// Structures
struct TimedCallbackStruct {
	float TimeStamp;
	std::string Function;
};

// Forward Declarations
class ObjectClass;

// Classes
class ScriptingClass {

	public:

		ScriptingClass();
		~ScriptingClass() { }

		int Init();
		int Close();

		void Reset();
		int LoadFile(const std::string &FilePath);

		void DefineLuaVariable(const char *VariableName, const char *Value);

		void CallFunction(const std::string &FunctionName);
		void CallCollisionHandler(const std::string &FunctionName, ObjectClass *BaseObject, ObjectClass *OtherObject);
		void CallZoneHandler(const std::string &FunctionName, int Type, ObjectClass *Zone, ObjectClass *Object);

		bool HandleKeyPress(int Key);
		void HandleMousePress(int Button, int MouseX, int MouseY);
		void UpdateTimedCallbacks();

	private:

		static luaL_reg CameraFunctions[], ObjectFunctions[], OrbFunctions[], TimerFunctions[], LevelFunctions[],
						GUIFunctions[], RandomFunctions[], ZoneFunctions[];

		static bool CheckArguments(lua_State *LuaObject, int Required);

		static int CameraSetYaw(lua_State *LuaObject);
		static int CameraSetPitch(lua_State *LuaObject);

		static int ObjectGetPointer(lua_State *LuaObject);
		static int ObjectGetName(lua_State *LuaObject);
		static int ObjectSetPosition(lua_State *LuaObject);
		static int ObjectGetPosition(lua_State *LuaObject);
		static int ObjectStop(lua_State *LuaObject);
		static int ObjectSetAngularVelocity(lua_State *LuaObject);
		static int ObjectSetLifetime(lua_State *LuaObject);
		static int ObjectDelete(lua_State *LuaObject);

		static int OrbDeactivate(lua_State *LuaObject);

		static int TimerDelayedFunction(lua_State *LuaObject);
		static int TimerStamp(lua_State *LuaObject);

		static int LevelLose(lua_State *LuaObject);
		static int LevelWin(lua_State *LuaObject);
		static int LevelGetTemplate(lua_State *LuaObject);
		static int LevelCreateObject(lua_State *LuaObject);
		static int LevelCreateConstraint(lua_State *LuaObject);
		static int LevelCreateSpring(lua_State *LuaObject);

		static int GUITutorialText(lua_State *LuaObject);

		static int RandomSeed(lua_State *LuaObject);
		static int RandomGetFloat(lua_State *LuaObject);
		static int RandomGetInt(lua_State *LuaObject);
		
		void AddTimedCallback(const std::string &FunctionName, float Time);
		void AttachKeyToFunction(int Key, const std::string &FunctionName);
		
		std::list<TimedCallbackStruct> TimedCallbacks;

		std::map<int, std::string> KeyCallbacks;
		std::map<int, std::string>::iterator KeyCallbacksIterator;

		lua_State *LuaObject;

};

// Singletons
typedef SingletonClass<ScriptingClass> Scripting;

#endif