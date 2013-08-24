/**
 * The Forgotten Server - a server application for the MMORPG Tibia
 * Copyright (C) 2013  Mark Samman <mark.samman@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __OTSERV_LUASCRIPT_H__
#define __OTSERV_LUASCRIPT_H__

#include <string>
#include <map>
#include <list>
#include <vector>
#include <unordered_map>
#include <stack>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#if LUA_VERSION_NUM >= 502
// NOTE: Define LUA_COMPAT_ALL as a workaround if this doesn't work
#ifndef LUA_COMPAT_ALL
#ifndef LUA_COMPAT_MODULE
#define luaL_register(L, libname, l) (luaL_newlib(L, l), lua_pushvalue(L, -1), lua_setglobal(L, libname))
#endif
#define lua_equal(L, i1, i2) lua_compare(L, (i1), (i2), LUA_OPEQ)
#endif
#endif

#include "position.h"
#include "definitions.h"
#include "database.h"
#include "enums.h"

class Thing;
class Creature;
class Player;
class Item;
class Container;
class AreaCombat;
class Combat;
class Condition;
class Npc;
class Monster;

enum LuaVariantType_t {
	VARIANT_NONE = 0,
	VARIANT_NUMBER,
	VARIANT_POSITION,
	VARIANT_TARGETPOSITION,
	VARIANT_STRING,
};

struct LuaVariant {
	LuaVariant() {
		type = VARIANT_NONE;
		text = "";
		pos.x = 0;
		pos.y = 0;
		pos.z = 0;
		pos.stackpos = 0;
		number = 0;
	}

	LuaVariantType_t type;
	std::string text;
	PositionEx pos;
	uint32_t number;
};

struct LuaTimerEventDesc {
	int32_t scriptId;
	int32_t function;
	std::list<int32_t> parameters;
	uint32_t eventId;
};

class LuaScriptInterface;
class Game;
class Npc;

class ScriptEnvironment
{
	public:
		ScriptEnvironment();
		~ScriptEnvironment();

		void resetEnv();

		static bool saveGameState();
		static bool loadGameState();

		void setScriptId(int32_t scriptId, LuaScriptInterface* scriptInterface) {
			m_scriptId = scriptId;
			m_interface = scriptInterface;
		}
		bool setCallbackId(int32_t callbackId, LuaScriptInterface* scriptInterface);
		void setEventDesc(const std::string& desc) {
			m_eventdesc = desc;
		}

		std::string getEventDesc() const {
			return m_eventdesc;
		}
		int32_t getScriptId() const {
			return m_scriptId;
		}
		int32_t getCallbackId() const {
			return m_callbackId;
		}
		LuaScriptInterface* getScriptInterface() {
			return m_interface;
		}

		void setTimerEvent() {
			m_timerEvent = true;
		}
		void resetTimerEvent() {
			m_timerEvent = false;
		}

		void getEventInfo(int32_t& scriptId, std::string& desc, LuaScriptInterface*& scriptInterface, int32_t& callbackId, bool& timerEvent) const;

		static void addTempItem(ScriptEnvironment* env, Item* item);
		static void removeTempItem(ScriptEnvironment* env, Item* item);
		static void removeTempItem(Item* item);
		static void addUniqueThing(Thing* thing);
		static void removeUniqueThing(Thing* thing);
		uint32_t addThing(Thing* thing);
		void insertThing(uint32_t uid, Thing* thing);

		DBResult* getResultByID(uint32_t id);
		uint32_t addResult(DBResult* res);
		bool removeResult(uint32_t id);

		void addGlobalStorageValue(const uint32_t key, const int32_t value);
		bool getGlobalStorageValue(const uint32_t key, int32_t& value) const;

		void setNpc(Npc* npc) {
			m_curNpc = npc;
		}
		Npc* getNpc() const {
			return m_curNpc;
		}

		Thing* getThingByUID(uint32_t uid);
		Item* getItemByUID(uint32_t uid);
		Container* getContainerByUID(uint32_t uid);
		void removeItemByUID(uint32_t uid);

		static uint32_t addCombatArea(AreaCombat* area);
		static AreaCombat* getCombatArea(uint32_t areaId);

		static uint32_t addCombatObject(Combat* combat);
		static Combat* getCombatObject(uint32_t combatId);

		static uint32_t addConditionObject(Condition* condition);
		static Condition* getConditionObject(uint32_t conditionId);

		static uint32_t getLastCombatId() {
			return m_lastCombatId;
		}

	private:
		typedef std::unordered_map<uint32_t, Thing*> ThingMap;
		typedef std::vector<const LuaVariant*> VariantVector;
		typedef std::map<uint32_t, AreaCombat*> AreaMap;
		typedef std::map<uint32_t, Combat*> CombatMap;
		typedef std::map<uint32_t, Condition*> ConditionMap;
		typedef std::map<uint32_t, int32_t> StorageMap;
		typedef std::map<uint32_t, DBResult*> DBResultMap;
		typedef std::list<Item*> ItemList;

		//script file id
		int32_t m_scriptId;
		int32_t m_callbackId;
		bool m_timerEvent;
		LuaScriptInterface* m_interface;
		//script event desc
		std::string m_eventdesc;

		static StorageMap m_globalStorageMap;
		//unique id map
		static ThingMap m_globalMap;

		//item/creature map
		int32_t m_lastUID;
		ThingMap m_localMap;

		//temporary item list
		typedef std::map<ScriptEnvironment*, ItemList> TempItemListMap;
		static TempItemListMap m_tempItems;

		//area map
		static uint32_t m_lastAreaId;
		static AreaMap m_areaMap;

		//combat map
		static uint32_t m_lastCombatId;
		static CombatMap m_combatMap;

		//condition map
		static uint32_t m_lastConditionId;
		static ConditionMap m_conditionMap;

		//result map
		static uint32_t m_lastResultId;
		static DBResultMap m_tempResults;

		//for npc scripts
		Npc* m_curNpc;
};

struct Position;

enum PlayerInfo_t {
	PlayerInfoFood,
	PlayerInfoPzLock,
	PlayerInfoGhostStatus
};

#define reportErrorFunc(a)  reportError(__FUNCTION__, a, true)

enum ErrorCode_t {
	LUA_ERROR_PLAYER_NOT_FOUND,
	LUA_ERROR_CREATURE_NOT_FOUND,
	LUA_ERROR_ITEM_NOT_FOUND,
	LUA_ERROR_THING_NOT_FOUND,
	LUA_ERROR_TILE_NOT_FOUND,
	LUA_ERROR_HOUSE_NOT_FOUND,
	LUA_ERROR_COMBAT_NOT_FOUND,
	LUA_ERROR_CONDITION_NOT_FOUND,
	LUA_ERROR_AREA_NOT_FOUND,
	LUA_ERROR_CONTAINER_NOT_FOUND,
	LUA_ERROR_VARIANT_NOT_FOUND,
	LUA_ERROR_VARIANT_UNKNOWN,
	LUA_ERROR_SPELL_NOT_FOUND
};

class LuaScriptInterface
{
	public:
		LuaScriptInterface(const std::string& interfaceName);
		virtual ~LuaScriptInterface();

		virtual bool initState();
		bool reInitState();

		int32_t loadFile(const std::string& file, Npc* npc = NULL);

		const std::string& getFileById(int32_t scriptId);
		int32_t getEvent(const std::string& eventName);

		static ScriptEnvironment* getScriptEnv() {
			assert(m_scriptEnvIndex >= 0 && m_scriptEnvIndex < 17);
			return &m_scriptEnv[m_scriptEnvIndex];
		}

		static bool reserveScriptEnv() {
			if (++m_scriptEnvIndex < 16) {
				return true;
			} else {
				--m_scriptEnvIndex;
				return false;
			}
		}

		static void resetScriptEnv() {
			if (m_scriptEnvIndex >= 0) {
				m_scriptEnv[m_scriptEnvIndex].resetEnv();
				--m_scriptEnvIndex;
			}
		}

		static void reportError(const char* function, const std::string& error_desc, bool stack_trace = false);

		const std::string& getInterfaceName() const {
			return m_interfaceName;
		}
		const std::string& getLastLuaError() const {
			return m_lastLuaError;
		}

		lua_State* getLuaState() const {
			return m_luaState;
		}

		bool pushFunction(int32_t functionId);

		static int32_t luaErrorHandler(lua_State* L);
		bool callFunction(uint32_t nParams);

		//push/pop common structures
		static void pushThing(lua_State* L, Thing* thing, uint32_t thingid);
		static void pushVariant(lua_State* L, const LuaVariant& var);
		static void pushPosition(lua_State* L, const PositionEx& position);
		static void pushPosition(lua_State* L, const Position& position, uint32_t stackpos);
		static void pushString(lua_State* L, const std::string& value);
		static void pushCallback(lua_State* L, int32_t callback);

		static LuaVariant popVariant(lua_State* L);
		static void popPosition(lua_State* L, PositionEx& position);
		static void popPosition(lua_State* L, Position& position, uint32_t& stackpos);
		static uint32_t popNumber(lua_State* L);
		static double popFloatNumber(lua_State* L);
		static std::string popString(lua_State* L);
		static int32_t popCallback(lua_State* L);
		static bool popBoolean(lua_State* L);
		
		// Userdata
		template<class T>
		static void pushUserdata(lua_State* L, T* value)
		{
			T** userdata = static_cast<T**>(lua_newuserdata(L, sizeof(T*)));
			*userdata = value;
		}
		template<class T>
		static T* popUserdata(lua_State* L)
		{
			T* userdata = *static_cast<T**>(lua_touserdata(L, -1));
			lua_pop(L, 1);
			return userdata;
		}

		// Metatables
		static void setMetatable(lua_State* L, int32_t index, const std::string& string);
		static void setItemMetatable(lua_State* L, int32_t index, Item* item);
		static void setCreatureMetatable(lua_State* L, int32_t index, Creature* creature);

		// Get
		template<typename T>
		static T getNumber(lua_State* L, int32_t arg)
		{
			return static_cast<T>(lua_tonumber(L, arg));
		}
		template<class T>
		static T* getUserdata(lua_State* L, int32_t arg)
		{
			T** userdata = getRawUserdata<T>(L, arg);
			if (!userdata) {
				return NULL;
			}
			return *userdata;
		}
		template<class T>
		static T** getRawUserdata(lua_State* L, int32_t arg)
		{
			return static_cast<T**>(lua_touserdata(L, arg));
		}

		static std::string getString(lua_State* L, int32_t arg);
		static bool getBoolean(lua_State* L, int32_t arg);
		static Position getPosition(lua_State* L, int32_t arg, uint32_t& stackpos);
		static Position getPosition(lua_State* L, int32_t arg);

		static Creature* getCreature(lua_State* L, int32_t arg);
		static Player* getPlayer(lua_State* L, int32_t arg);

		template<typename T>
		static T getField(lua_State* L, int32_t arg, const std::string& key)
		{
			lua_getfield(L, arg, key.c_str());
			return getNumber<T>(L, -1);
		}

		static std::string getFieldString(lua_State* L, const std::string& key);
		static bool getFieldBoolean(lua_State* L, const std::string& key);

		// Other
		static int32_t getStackTop(lua_State* L);

		// Is
		static bool isNil(lua_State* L, int32_t arg);
		static bool isNumber(lua_State* L, int32_t arg);
		static bool isString(lua_State* L, int32_t arg);
		static bool isBoolean(lua_State* L, int32_t arg);
		static bool isTable(lua_State* L, int32_t arg);
		static bool isFunction(lua_State* L, int32_t arg);
		static bool isUserdata(lua_State* L, int32_t arg);

		// Pop
		template<typename T>
		static T popNumber(lua_State* L) {
			if (lua_gettop(L) == 0) {
				return static_cast<T>(0);
			}

			T ret = static_cast<T>(lua_tonumber(L, -1));
			lua_pop(L, 1);
			return ret;
		}
		static Outfit_t popOutfit(lua_State* L);

		// Push
		template<typename T>
		static void pushNumber(lua_State* L, T number) {
			lua_pushnumber(L, number);
		}

		static void pushBoolean(lua_State* L, bool value);
		static void pushNil(lua_State* L);
		static void pushMetaPosition(lua_State* L, const PositionEx& position);
		static void pushMetaPosition(lua_State* L, const Position& position, uint32_t stackpos);
		static void pushOutfit(lua_State* L, const Outfit_t& outfit);

		//
		template<typename T>
		static T popField(lua_State* L, const std::string& key)
		{
			lua_getfield(L, -1, key.c_str());
			return popNumber<T>(L);
		}

		static std::string popFieldString(lua_State* L, const std::string& key);
		static bool popFieldBoolean(lua_State* L, const std::string& key);

		static void setField(lua_State* L, const char* index, double val);
		static void setField(lua_State* L, const char* index, const std::string& val);
		static void setFieldBool(lua_State* L, const char* index, bool val);
		static std::string escapeString(const std::string& string);

#ifndef __LUAJIT__
		static const luaL_Reg luaBitReg[13];
#endif
		static const luaL_Reg luaDatabaseTable[8];
		static const luaL_Reg luaResultTable[7];

		static int32_t protectedCall(lua_State* L, int32_t nargs, int32_t nresults);

	protected:
		virtual bool closeState();

		void registerFunctions();
		
		void registerClass(const std::string& className, const std::string& baseClass, lua_CFunction newFunction = NULL);
		void registerClassMethod(const std::string& className, const std::string& methodName, lua_CFunction func);
		void registerMetaMethod(const std::string& className, const std::string& methodName, lua_CFunction func);
		void registerGlobalMethod(const std::string& functionName, lua_CFunction func);

		std::string getStackTrace(const std::string& error_desc);

		static std::string getErrorDesc(ErrorCode_t code);
		static bool getArea(lua_State* L, std::list<uint32_t>& list, uint32_t& rows);

		//lua functions
		static int32_t luaDoRemoveItem(lua_State* L);
		static int32_t luaDoFeedPlayer(lua_State* L);
		static int32_t luaDoPlayerSendCancel(lua_State* L);
		static int32_t luaDoSendDefaultCancel(lua_State* L);
		static int32_t luaDoTeleportThing(lua_State* L);
		static int32_t luaDoChangeTypeItem(lua_State* L);
		static int32_t luaDoSendAnimatedText(lua_State* L);
		static int32_t luaDoShowTextWindow(lua_State* L);
		static int32_t luaDoDecayItem(lua_State* L);
		static int32_t luaDoCreateItem(lua_State* L);
		static int32_t luaDoCreateItemEx(lua_State* L);
		static int32_t luaDoCreateTeleport(lua_State* L);
		static int32_t luaDoCreateNpc(lua_State* L);
		static int32_t luaDoSummonCreature(lua_State* L);
		static int32_t luaDoConvinceCreature(lua_State* L);
		static int32_t luaGetMonsterTargetList(lua_State* L);
		static int32_t luaGetMonsterFriendList(lua_State* L);
		static int32_t luaDoSetMonsterTarget(lua_State* L);
		static int32_t luaDoMonsterChangeTarget(lua_State* L);
		static int32_t luaDoAddCondition(lua_State* L);
		static int32_t luaDoRemoveCondition(lua_State* L);
		static int32_t luaDoMoveCreature(lua_State* L);
		static int32_t luaGetHouseTilesSize(lua_State* L);
		static int32_t luaGetTileInfo(lua_State* L);

		static int32_t luaDoPlayerAddSkillTry(lua_State* L);
		static int32_t luaDoPlayerAddMana(lua_State* L);
		static int32_t luaDoPlayerAddManaSpent(lua_State* L);
		static int32_t luaDoPlayerAddItem(lua_State* L);
		static int32_t luaDoTileAddItemEx(lua_State* L);
		static int32_t luaDoAddContainerItemEx(lua_State* L);
		static int32_t luaDoRelocate(lua_State* L);
		static int32_t luaDoPlayerSendTextMessage(lua_State* L);
		static int32_t luaDoPlayerRemoveItem(lua_State* L);
		static int32_t luaDoPlayerAddExp(lua_State* L);
		static int32_t luaDoPlayerSetGuildLevel(lua_State* L);
		static int32_t luaDoPlayerSetGuildNick(lua_State* L);
		static int32_t luaDoPlayerChangeName(lua_State* L);
		static int32_t luaDoSetCreatureLight(lua_State* L);
		static int32_t luaDoSetCreatureDropLoot(lua_State* L);

		//queries
		static int32_t luaGetPlayerGUIDByName(lua_State* L);
		static int32_t luaGetAccountNumberByPlayerName(lua_State* L);
		static int32_t luaGetPlayersByAccountNumber(lua_State* L);
		static int32_t luaGetPlayersByIPAddress(lua_State* L);

		//get item info
		static int32_t luaGetItemRWInfo(lua_State* L);
		static int32_t luaGetThingfromPos(lua_State* L);
		static int32_t luaGetThing(lua_State* L);
		static int32_t luaGetThingPos(lua_State* L);
		static int32_t luaGetTileItemById(lua_State* L);
		static int32_t luaGetTileItemByType(lua_State* L);
		static int32_t luaGetTileThingByPos(lua_State* L);
		static int32_t luaGetTileThingByTopOrder(lua_State* L);
		static int32_t luaGetTopCreature(lua_State* L);
		static int32_t luaHasProperty(lua_State* L);
		static int32_t luaGetDepotId(lua_State* L);

		//set item
		static int32_t luaDoSetItemText(lua_State* L);
		static int32_t luaDoSetItemSpecialDescription(lua_State* L);

		//get tile info
		static int32_t luaGetTilePzInfo(lua_State* L);
		static int32_t luaGetTileHouseInfo(lua_State* L);
		static int32_t luaQueryTileAddThing(lua_State* L);

		//houses
		static int32_t luaGetHouseOwner(lua_State* L);
		static int32_t luaGetHouseName(lua_State* L);
		static int32_t luaGetHouseEntry(lua_State* L);
		static int32_t luaGetHouseRent(lua_State* L);
		static int32_t luaGetHouseTown(lua_State* L);
		static int32_t luaGetHouseAccessList(lua_State* L);
		static int32_t luaGetHouseByPlayerGUID(lua_State* L);
		static int32_t luaSetHouseOwner(lua_State* L);
		static int32_t luaSetHouseAccessList(lua_State* L);

		//get creature info functions
		static int32_t luaGetPlayerFood(lua_State* L);
		static int32_t luaGetCreatureMaster(lua_State* L);
		static int32_t luaGetCreatureSummons(lua_State* L);
		static int32_t luaGetSpectators(lua_State* L);
		static int32_t luaGetCreatureSpeed(lua_State* L);
		static int32_t luaGetCreatureBaseSpeed(lua_State* L);
		static int32_t luaGetCreatureTarget(lua_State* L);
		static int32_t luaGetPlayerSlotItem(lua_State* L);
		static int32_t luaGetPlayerItemById(lua_State* L);

		static int32_t luaGetPlayerFlagValue(lua_State* L);
		static int32_t luaGetCreatureCondition(lua_State* L);

		static int32_t luaPlayerLearnInstantSpell(lua_State* L);
		static int32_t luaCanPlayerLearnInstantSpell(lua_State* L);
		static int32_t luaGetPlayerLearnedInstantSpell(lua_State* L);
		static int32_t luaGetPlayerInstantSpellInfo(lua_State* L);
		static int32_t luaGetPlayerInstantSpellCount(lua_State* L);
		static int32_t luaGetInstantSpellInfoByName(lua_State* L);
		static int32_t luaGetInstantSpellWords(lua_State* L);

		static int32_t luaGetGlobalStorageValue(lua_State* L);
		static int32_t luaSetGlobalStorageValue(lua_State* L);

		static int32_t luaDoPlayerAddOutfit(lua_State* L);
		static int32_t luaDoPlayerRemOutfit(lua_State* L);
		static int32_t luaCanPlayerWearOutfit(lua_State* L);

		static int32_t luaDoPlayerAddMount(lua_State* L);
		static int32_t luaDoPlayerRemoveMount(lua_State* L);

		static int32_t luaGetWorldType(lua_State* L);
		static int32_t luaGetWorldTime(lua_State* L);
		static int32_t luaGetWorldLight(lua_State* L);
		static int32_t luaGetWorldCreatures(lua_State* L);
		static int32_t luaGetWorldUpTime(lua_State* L);
		static int32_t luaBroadcastMessage(lua_State* L);

		//type validation
		static int32_t luaIsPlayerPzLocked(lua_State* L);
		static int32_t luaIsPlayerGhost(lua_State* L);
		static int32_t luaIsDepot(lua_State* L);
		static int32_t luaIsCorpse(lua_State* L);
		static int32_t luaIsMoveable(lua_State* L);
		static int32_t luaIsValidUID(lua_State* L);

		//container
		static int32_t luaGetContainerCapById(lua_State* L);
		static int32_t luaGetContainerItem(lua_State* L);
		static int32_t luaDoAddContainerItem(lua_State* L);

		//
		static int32_t luaCreateCombatObject(lua_State* L);
		static int32_t luaCreateCombatArea(lua_State* L);
		static int32_t luaSetCombatArea(lua_State* L);
		static int32_t luaSetCombatCondition(lua_State* L);
		static int32_t luaSetCombatParam(lua_State* L);
		static int32_t luaCreateConditionObject(lua_State* L);
		static int32_t luaSetConditionParam(lua_State* L);
		static int32_t luaAddDamageCondition(lua_State* L);
		static int32_t luaAddOutfitCondition(lua_State* L);

		static int32_t luaSetCombatCallBack(lua_State* L);
		static int32_t luaSetCombatFormula(lua_State* L);
		static int32_t luaSetConditionFormula(lua_State* L);
		static int32_t luaDoCombat(lua_State* L);

		static int32_t luaDoAreaCombatHealth(lua_State* L);
		static int32_t luaDoTargetCombatHealth(lua_State* L);

		//
		static int32_t luaDoAreaCombatMana(lua_State* L);
		static int32_t luaDoTargetCombatMana(lua_State* L);

		static int32_t luaDoAreaCombatCondition(lua_State* L);
		static int32_t luaDoTargetCombatCondition(lua_State* L);

		static int32_t luaDoAreaCombatDispel(lua_State* L);
		static int32_t luaDoTargetCombatDispel(lua_State* L);

		static int32_t luaDoChallengeCreature(lua_State* L);

		static int32_t luaNumberToVariant(lua_State* L);
		static int32_t luaStringToVariant(lua_State* L);
		static int32_t luaPositionToVariant(lua_State* L);
		static int32_t luaTargetPositionToVariant(lua_State* L);

		static int32_t luaVariantToNumber(lua_State* L);
		static int32_t luaVariantToString(lua_State* L);
		static int32_t luaVariantToPosition(lua_State* L);

		static int32_t luaDoChangeSpeed(lua_State* L);

		static int32_t luaDoCreatureChangeOutfit(lua_State* L);
		static int32_t luaSetCreatureOutfit(lua_State* L);
		static int32_t luaGetCreatureOutfit(lua_State* L);
		static int32_t luaSetMonsterOutfit(lua_State* L);
		static int32_t luaSetItemOutfit(lua_State* L);

		static int32_t luaIsItemStackable(lua_State* L);
		static int32_t luaIsItemRune(lua_State* L);
		static int32_t luaIsItemDoor(lua_State* L);
		static int32_t luaIsItemContainer(lua_State* L);
		static int32_t luaIsItemFluidContainer(lua_State* L);
		static int32_t luaIsItemMoveable(lua_State* L);
		static int32_t luaGetItemName(lua_State* L);
		static int32_t luaGetItemDescriptions(lua_State* L);
		static int32_t luaGetItemWeight(lua_State* L);
		static int32_t luaGetItemWeightByUID(lua_State* L);
		static int32_t luaGetItemIdByName(lua_State* L);

		static int32_t luaDebugPrint(lua_State* L);
		static int32_t luaIsInArray(lua_State* L);
		static int32_t luaGetFluidSourceType(lua_State* L);
		static int32_t luaAddEvent(lua_State* L);
		static int32_t luaStopEvent(lua_State* L);

		static int32_t luaDoPlayerPopupFYI(lua_State* L);
		static int32_t luaMayNotMove(lua_State* L);

		static int32_t luaGetOnlinePlayers(lua_State* L);
		static int32_t luaSaveServer(lua_State* L);
		static int32_t luaRefreshMap(lua_State* L);
		static int32_t luaCleanMap(lua_State* L);

		static int32_t luaDoSendTutorial(lua_State* L);
		static int32_t luaDoAddMark(lua_State* L);

		static int32_t luaIsInWar(lua_State* L);
		static int32_t luaDoPlayerSetOfflineTrainingSkill(lua_State* L);

		static int32_t luaGetWaypointPosition(lua_State* L);
		static int32_t luaDoWaypointAddTemporial(lua_State* L);

		static int32_t luaSendChannelMessage(lua_State* L);
		static int32_t luaSendGuildChannelMessage(lua_State* L);

		static int32_t luaGetPlayerParty(lua_State* L);
		static int32_t luaDoPlayerJoinParty(lua_State* L);
		static int32_t luaGetPartyMembers(lua_State* L);

		//

		static int32_t internalGetPlayerInfo(lua_State* L, PlayerInfo_t info);

#ifndef __LUAJIT__
		static int32_t luaBitNot(lua_State* L);
		static int32_t luaBitAnd(lua_State* L);
		static int32_t luaBitOr(lua_State* L);
		static int32_t luaBitXor(lua_State* L);
		static int32_t luaBitLeftShift(lua_State* L);
		static int32_t luaBitRightShift(lua_State* L);
		static int32_t luaBitUNot(lua_State* L);
		static int32_t luaBitUAnd(lua_State* L);
		static int32_t luaBitUOr(lua_State* L);
		static int32_t luaBitUXor(lua_State* L);
		static int32_t luaBitULeftShift(lua_State* L);
		static int32_t luaBitURightShift(lua_State* L);
#endif

		static int32_t luaDatabaseExecute(lua_State* L);
		static int32_t luaDatabaseStoreQuery(lua_State* L);
		static int32_t luaDatabaseEscapeString(lua_State* L);
		static int32_t luaDatabaseEscapeBlob(lua_State* L);
		static int32_t luaDatabaseLastInsertId(lua_State* L);
		static int32_t luaDatabaseConnected(lua_State* L);
		static int32_t luaDatabaseTableExists(lua_State* L);

		static int32_t luaResultGetDataInt(lua_State* L);
		static int32_t luaResultGetDataLong(lua_State* L);
		static int32_t luaResultGetDataString(lua_State* L);
		static int32_t luaResultGetDataStream(lua_State* L);
		static int32_t luaResultNext(lua_State* L);
		static int32_t luaResultFree(lua_State* L);
		
		// _G
		static int32_t luaIsType(lua_State* L);

		// Position
		static int32_t luaPositionCreate(lua_State* L);
		static int32_t luaPositionAdd(lua_State* L);
		static int32_t luaPositionSub(lua_State* L);
		static int32_t luaPositionCompare(lua_State* L);

		static int32_t luaPositionGetDistance(lua_State* L);
		static int32_t luaPositionIsSightClear(lua_State* L);

		static int32_t luaPositionSendMagicEffect(lua_State* L);
		static int32_t luaPositionSendDistanceEffect(lua_State* L);

		// NetworkMessage
		static int32_t luaNetworkMessageCreate(lua_State* L);
		static int32_t luaNetworkMessageDelete(lua_State* L);

		static int32_t luaNetworkMessageGetByte(lua_State* L);
		static int32_t luaNetworkMessageGetU16(lua_State* L);
		static int32_t luaNetworkMessageGetU32(lua_State* L);
		static int32_t luaNetworkMessageGetU64(lua_State* L);
		static int32_t luaNetworkMessageGetString(lua_State* L);
		static int32_t luaNetworkMessageGetPosition(lua_State* L);

		static int32_t luaNetworkMessageAddByte(lua_State* L);
		static int32_t luaNetworkMessageAddU16(lua_State* L);
		static int32_t luaNetworkMessageAddU32(lua_State* L);
		static int32_t luaNetworkMessageAddU64(lua_State* L);
		static int32_t luaNetworkMessageAddString(lua_State* L);
		static int32_t luaNetworkMessageAddPosition(lua_State* L);
		static int32_t luaNetworkMessageAddDouble(lua_State* L);
		static int32_t luaNetworkMessageAddItem(lua_State* L);
		static int32_t luaNetworkMessageAddItemId(lua_State* L);

		static int32_t luaNetworkMessageReset(lua_State* L);
		static int32_t luaNetworkMessageSkipBytes(lua_State* L);
		static int32_t luaNetworkMessageSendToPlayer(lua_State* L);

		// ModalWindow
		static int32_t luaModalWindowCreate(lua_State* L);
		static int32_t luaModalWindowDelete(lua_State* L);

		static int32_t luaModalWindowGetId(lua_State* L);
		static int32_t luaModalWindowGetTitle(lua_State* L);
		static int32_t luaModalWindowGetMessage(lua_State* L);

		static int32_t luaModalWindowGetButtonCount(lua_State* L);
		static int32_t luaModalWindowGetChoiceCount(lua_State* L);

		static int32_t luaModalWindowAddButton(lua_State* L);
		static int32_t luaModalWindowAddChoice(lua_State* L);

		static int32_t luaModalWindowGetDefaultEnterButton(lua_State* L);
		static int32_t luaModalWindowSetDefaultEnterButton(lua_State* L);

		static int32_t luaModalWindowGetDefaultEscapeButton(lua_State* L);
		static int32_t luaModalWindowSetDefaultEscapeButton(lua_State* L);

		static int32_t luaModalWindowHasPriority(lua_State* L);
		static int32_t luaModalWindowSetPriority(lua_State* L);

		static int32_t luaModalWindowSendToPlayer(lua_State* L);

		// Item
		static int32_t luaItemCreate(lua_State* L);

		static int32_t luaItemGetId(lua_State* L);

		static int32_t luaItemClone(lua_State* L);
		static int32_t luaItemSplit(lua_State* L);
		static int32_t luaItemRemove(lua_State* L);

		static int32_t luaItemGetUniqueId(lua_State* L);
		static int32_t luaItemGetActionId(lua_State* L);
		static int32_t luaItemSetActionId(lua_State* L);

		static int32_t luaItemGetCount(lua_State* L);
		static int32_t luaItemGetCharges(lua_State* L);
		static int32_t luaItemGetFluidType(lua_State* L);
		static int32_t luaItemGetSubType(lua_State* L);

		static int32_t luaItemGetName(lua_State* L);
		static int32_t luaItemGetPluralName(lua_State* L);
		static int32_t luaItemGetArticle(lua_State* L);

		static int32_t luaItemGetPosition(lua_State* L);

		static int32_t luaItemGetAttribute(lua_State* L);
		static int32_t luaItemSetAttribute(lua_State* L);
		static int32_t luaItemRemoveAttribute(lua_State* L);

		static int32_t luaItemMoveTo(lua_State* L);
		static int32_t luaItemTransform(lua_State* L);

		// Container
		static int32_t luaContainerCreate(lua_State* L);

		static int32_t luaContainerGetSize(lua_State* L);
		static int32_t luaContainerGetCapacity(lua_State* L);
		static int32_t luaContainerGetEmptySlots(lua_State* L);

		static int32_t luaContainerGetItem(lua_State* L);
		static int32_t luaContainerHasItem(lua_State* L);
		static int32_t luaContainerAddItem(lua_State* L);
		static int32_t luaContainerAddItemEx(lua_State* L);

		// Creature
		static int32_t luaCreatureCreate(lua_State* L);
		
		static int32_t luaCreatureRegisterEvent(lua_State* L);
		static int32_t luaCreatureUnregisterEvent(lua_State* L);

		static int32_t luaCreatureIsCreature(lua_State* L);
		static int32_t luaCreatureIsPlayer(lua_State* L);
		static int32_t luaCreatureIsMonster(lua_State* L);
		static int32_t luaCreatureIsNpc(lua_State* L);

		static int32_t luaCreatureGetId(lua_State* L);
		static int32_t luaCreatureGetName(lua_State* L);
		
		static int32_t luaCreatureGetLight(lua_State* L);
		static int32_t luaCreatureSetLight(lua_State* L);

		static int32_t luaCreatureGetPosition(lua_State* L);
		static int32_t luaCreatureGetDirection(lua_State* L);
		static int32_t luaCreatureSetDirection(lua_State* L);

		static int32_t luaCreatureGetHealth(lua_State* L);
		static int32_t luaCreatureAddHealth(lua_State* L);
		static int32_t luaCreatureGetMaxHealth(lua_State* L);
		static int32_t luaCreatureSetMaxHealth(lua_State* L);

		static int32_t luaCreatureGetMana(lua_State* L);
		static int32_t luaCreatureAddMana(lua_State* L);
		static int32_t luaCreatureGetMaxMana(lua_State* L);
		static int32_t luaCreatureSetMaxMana(lua_State* L);

		static int32_t luaCreatureGetOutfit(lua_State* L);

		static int32_t luaCreatureRemove(lua_State* L);
		static int32_t luaCreatureTeleportTo(lua_State* L);
		static int32_t luaCreatureSay(lua_State* L);

		// Player
		static int32_t luaPlayerCreate(lua_State* L);

		static int32_t luaPlayerGetGuid(lua_State* L);
		static int32_t luaPlayerGetIp(lua_State* L);
		static int32_t luaPlayerGetAccountType(lua_State* L);
		static int32_t luaPlayerGetLastLoginSaved(lua_State* L);

		static int32_t luaPlayerGetFreeCapacity(lua_State* L);
		static int32_t luaPlayerGetDepotItems(lua_State* L);

		static int32_t luaPlayerGetSkull(lua_State* L);
		static int32_t luaPlayerSetSkull(lua_State* L);
		static int32_t luaPlayerGetDeathPenalty(lua_State* L);

		static int32_t luaPlayerGetExperience(lua_State* L);
		static int32_t luaPlayerAddExperience(lua_State* L);
		static int32_t luaPlayerGetLevel(lua_State* L);

		static int32_t luaPlayerGetMagicLevel(lua_State* L);
		static int32_t luaPlayerGetManaSpent(lua_State* L);
		static int32_t luaPlayerAddManaSpent(lua_State* L);

		static int32_t luaPlayerGetSkillLevel(lua_State* L);
		static int32_t luaPlayerGetSkillPercent(lua_State* L);
		static int32_t luaPlayerGetSkillTries(lua_State* L);
		static int32_t luaPlayerAddSkillTries(lua_State* L);

		static int32_t luaPlayerGetItemCount(lua_State* L);
		static int32_t luaPlayerGetItemById(lua_State* L);

		static int32_t luaPlayerGetVocation(lua_State* L);
		static int32_t luaPlayerSetVocation(lua_State* L);

		static int32_t luaPlayerGetSex(lua_State* L);
		static int32_t luaPlayerSetSex(lua_State* L);

		static int32_t luaPlayerGetTown(lua_State* L);
		static int32_t luaPlayerSetTown(lua_State* L);

		static int32_t luaPlayerGetGuild(lua_State* L);
		static int32_t luaPlayerSetGuild(lua_State* L);

		static int32_t luaPlayerGetGuildLevel(lua_State* L);
		static int32_t luaPlayerGetGuildNick(lua_State* L);

		static int32_t luaPlayerGetGroup(lua_State* L);
		static int32_t luaPlayerSetGroup(lua_State* L);

		static int32_t luaPlayerGetStamina(lua_State* L);

		static int32_t luaPlayerGetSoul(lua_State* L);
		static int32_t luaPlayerAddSoul(lua_State* L);
		static int32_t luaPlayerGetMaxSoul(lua_State* L);

		static int32_t luaPlayerGetBankBalance(lua_State* L);
		static int32_t luaPlayerSetBankBalance(lua_State* L);

		static int32_t luaPlayerGetStorageValue(lua_State* L);
		static int32_t luaPlayerSetStorageValue(lua_State* L);

		static int32_t luaPlayerAddItem(lua_State* L);
		static int32_t luaPlayerAddItemEx(lua_State* L);
		static int32_t luaPlayerRemoveItem(lua_State* L);

		static int32_t luaPlayerGetMoney(lua_State* L);
		static int32_t luaPlayerAddMoney(lua_State* L);
		static int32_t luaPlayerRemoveMoney(lua_State* L);

		static int32_t luaPlayerShowTextDialog(lua_State* L);

		static int32_t luaPlayerSendTextMessage(lua_State* L);
		static int32_t luaPlayerSendChannelMessage(lua_State* L);
		static int32_t luaPlayerChannelSay(lua_State* L);
		static int32_t luaPlayerOpenChannel(lua_State* L);

		static int32_t luaPlayerGetSlotItem(lua_State* L);
		
		static int32_t luaPlayerHasMount(lua_State* L);
		
		static int32_t luaPlayerGetPremiumDays(lua_State* L);
		static int32_t luaPlayerAddPremiumDays(lua_State* L);
		static int32_t luaPlayerRemovePremiumDays(lua_State* L);

		static int32_t luaPlayerHasBlessing(lua_State* L);
		static int32_t luaPlayerAddBlessing(lua_State* L);
		static int32_t luaPlayerRemoveBlessing(lua_State* L);

		// Monster
		static int32_t luaMonsterCreate(lua_State* L);

		// Npc
		static int32_t luaNpcCreate(lua_State* L);

		// Guild
		static int32_t luaGuildCreate(lua_State* L);

		static int32_t luaGuildGetId(lua_State* L);
		static int32_t luaGuildGetName(lua_State* L);
		static int32_t luaGuildGetMembersOnline(lua_State* L);

		static int32_t luaGuildAddMember(lua_State* L);
		static int32_t luaGuildRemoveMember(lua_State* L);

		static int32_t luaGuildAddRank(lua_State* L);
		static int32_t luaGuildGetRankById(lua_State* L);
		static int32_t luaGuildGetRankByLevel(lua_State* L);
	
		static int32_t luaGuildGetMotd(lua_State* L);
		static int32_t luaGuildSetMotd(lua_State* L);

		// Group
		static int32_t luaGroupCreate(lua_State* L);

		static int32_t luaGroupGetId(lua_State* L);
		static int32_t luaGroupGetName(lua_State* L);
		static int32_t luaGroupGetFlags(lua_State* L);
		static int32_t luaGroupGetAccess(lua_State* L);
		static int32_t luaGroupGetMaxDepotItems(lua_State* L);
		static int32_t luaGroupGetMaxVipEntries(lua_State* L);

		// Vocation
		static int32_t luaVocationCreate(lua_State* L);
		
		static int32_t luaVocationGetId(lua_State* L);
		static int32_t luaVocationGetClientId(lua_State* L);
		static int32_t luaVocationGetName(lua_State* L);
		static int32_t luaVocationGetDescription(lua_State* L);
		
		static int32_t luaVocationGetRequiredSkillTries(lua_State* L);
		static int32_t luaVocationGetRequiredManaSpent(lua_State* L);

		static int32_t luaVocationGetCapacityGain(lua_State* L);
		
		static int32_t luaVocationGetHealthGain(lua_State* L);
		static int32_t luaVocationGetHealthGainTicks(lua_State* L);
		static int32_t luaVocationGetHealthGainAmount(lua_State* L);

		static int32_t luaVocationGetManaGain(lua_State* L);
		static int32_t luaVocationGetManaGainTicks(lua_State* L);
		static int32_t luaVocationGetManaGainAmount(lua_State* L);

		static int32_t luaVocationGetMaxSoul(lua_State* L);
		static int32_t luaVocationGetSoulGainTicks(lua_State* L);
		
		static int32_t luaVocationGetAttackSpeed(lua_State* L);
		static int32_t luaVocationGetBaseSpeed(lua_State* L);
		
		static int32_t luaVocationGetDemotion(lua_State* L);
		static int32_t luaVocationGetPromotion(lua_State* L);

		// Town
		static int32_t luaTownCreate(lua_State* L);

		static int32_t luaTownGetId(lua_State* L);
		static int32_t luaTownGetName(lua_State* L);
		static int32_t luaTownGetTemplePosition(lua_State* L);

		//
		lua_State* m_luaState;
		std::string m_lastLuaError;

		std::string m_interfaceName;
		int32_t m_eventTableRef;

		static ScriptEnvironment m_scriptEnv[16];
		static int32_t m_scriptEnvIndex;

		int32_t m_runningEventId;
		std::string m_loadingFile;

		//script file cache
		std::map<int32_t, std::string> m_cacheFiles;
};

class LuaEnvironment : public LuaScriptInterface
{
	public:
		LuaEnvironment();
		~LuaEnvironment();

		bool initState();
		bool reInitState();

	protected:
		bool closeState();

	private:
		uint32_t m_lastEventTimerId;
		std::map<uint32_t, LuaTimerEventDesc> m_timerEvents;

		void executeTimerEvent(uint32_t eventIndex);

		friend class LuaScriptInterface;
};

#endif
