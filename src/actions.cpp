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

#include "otpch.h"

#include "const.h"
#include "player.h"
#include "monster.h"
#include "npc.h"
#include "game.h"
#include "item.h"
#include "container.h"
#include "combat.h"
#include "house.h"
#include "tasks.h"
#include "tools.h"
#include "spells.h"
#include "configmanager.h"
#include "beds.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "actions.h"

extern Game g_game;
extern Spells* g_spells;
extern Actions* g_actions;
extern ConfigManager g_config;

Actions::Actions() :
	m_scriptInterface("Action Interface")
{
	m_scriptInterface.initState();
}

Actions::~Actions()
{
	clear();
}

inline void Actions::clearMap(ActionUseMap& map)
{
	for (ActionUseMap::const_iterator it = map.begin(), end = map.end(); it != end; ++it) {
		delete it->second;
	}

	map.clear();
}

void Actions::clear()
{
	clearMap(useItemMap);
	clearMap(uniqueItemMap);
	clearMap(actionItemMap);

	m_scriptInterface.reInitState();
}

LuaScriptInterface& Actions::getScriptInterface()
{
	return m_scriptInterface;
}

std::string Actions::getScriptBaseName()
{
	return "actions";
}

Event* Actions::getEvent(const std::string& nodeName)
{
	if (asLowerCaseString(nodeName) == "action") {
		return new Action(&m_scriptInterface);
	} else {
		return NULL;
	}
}

bool Actions::registerEvent(Event* event, xmlNodePtr p)
{
	Action* action = dynamic_cast<Action*>(event);

	if (!action) {
		return false;
	}

	int32_t id, id2, from;
	bool success = true;

	if (readXMLInteger(p, "itemid", id)) {
		if (useItemMap.find(id) != useItemMap.end()) {
			std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with id: " << id << std::endl;
			return false;
		}

		useItemMap[id] = action;
	} else if (readXMLInteger(p, "fromid", id) && readXMLInteger(p, "toid", id2)) {
		from = id;

		if (useItemMap.find(id) != useItemMap.end()) {
			std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with id: " << id << " in fromid: " << from << ", toid: " << id2 << std::endl;
			success = false;
		} else {
			useItemMap[id] = action;
		}

		while (id < id2) {
			id++;

			if (useItemMap.find(id) != useItemMap.end()) {
				std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with id: " << id << " in fromid: " << from << ", toid: " << id2 << std::endl;
				continue;
			}

			useItemMap[id] = new Action(action);
		}
	} else if (readXMLInteger(p, "uniqueid", id)) {
		if (uniqueItemMap.find(id) != uniqueItemMap.end()) {
			std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with uniqueid: " << id << std::endl;
			return false;
		}

		uniqueItemMap[id] = action;
	} else if (readXMLInteger(p, "fromuid", id) && readXMLInteger(p, "touid", id2)) {
		from = id;

		if (uniqueItemMap.find(id) != uniqueItemMap.end()) {
			std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with uniqueid: " << id << " in fromuid: " << from << ", touid: " << id2 << std::endl;
			success = false;
		} else {
			uniqueItemMap[id] = action;
		}

		while (id < id2) {
			id++;

			if (uniqueItemMap.find(id) != uniqueItemMap.end()) {
				std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with uniqueid: " << id << " in fromuid: " << from << ", touid: " << id2 << std::endl;
				continue;
			}

			uniqueItemMap[id] = new Action(action);
		}
	} else if (readXMLInteger(p, "actionid", id) || readXMLInteger(p, "aid", id)) {
		if (actionItemMap.find(id) != actionItemMap.end()) {
			std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with actionid: " << id << std::endl;
			return false;
		}

		actionItemMap[id] = action;
	} else if (readXMLInteger(p, "fromaid", id) && readXMLInteger(p, "toaid", id2)) {
		from = id;

		if (actionItemMap.find(id) != actionItemMap.end()) {
			std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with actionid: " << id << " in fromaid: " << from << ", toaid: " << id2 << std::endl;
			success = false;
		} else {
			actionItemMap[id] = action;
		}

		while (id < id2) {
			id++;

			if (actionItemMap.find(id) != actionItemMap.end()) {
				std::cout << "[Warning - Actions::registerEvent] Duplicate registered item with actionid: " << id << " in fromaid: " << from << ", toaid: " << id2 << std::endl;
				continue;
			}

			actionItemMap[id] = new Action(action);
		}
	} else {
		success = false;
	}

	return success;
}

ReturnValue Actions::canUse(const Player* player, const Position& pos)
{
	if (pos.x != 0xFFFF) {
		const Position& playerPos = player->getPosition();

		if (playerPos.z > pos.z) {
			return RET_FIRSTGOUPSTAIRS;
		} else if (playerPos.z < pos.z) {
			return RET_FIRSTGODOWNSTAIRS;
		} else if (!Position::areInRange<1, 1, 0>(playerPos, pos)) {
			return RET_TOOFARAWAY;
		}
	}
	return RET_NOERROR;
}

ReturnValue Actions::canUse(const Player* player, const Position& pos, const Item* item)
{
	Action* action = getAction(item);

	if (action) {
		return action->canExecuteAction(player, pos);
	}

	return RET_NOERROR;
}

ReturnValue Actions::canUseFar(const Creature* creature, const Position& toPos, bool checkLineOfSight)
{
	if (toPos.x == 0xFFFF) {
		return RET_NOERROR;
	}

	const Position& creaturePos = creature->getPosition();

	if (creaturePos.z > toPos.z) {
		return RET_FIRSTGOUPSTAIRS;
	} else if (creaturePos.z < toPos.z) {
		return RET_FIRSTGODOWNSTAIRS;
	} else if (!Position::areInRange<7, 5, 0>(toPos, creaturePos)) {
		return RET_TOOFARAWAY;
	}

	if (checkLineOfSight && !g_game.canThrowObjectTo(creaturePos, toPos)) {
		return RET_CANNOTTHROW;
	}

	return RET_NOERROR;
}

Action* Actions::getAction(const Item* item)
{
	if (item->getUniqueId() != 0) {
		ActionUseMap::const_iterator it = uniqueItemMap.find(item->getUniqueId());

		if (it != uniqueItemMap.end()) {
			return it->second;
		}
	}

	if (item->getActionId() != 0) {
		ActionUseMap::const_iterator it = actionItemMap.find(item->getActionId());

		if (it != actionItemMap.end()) {
			return it->second;
		}
	}

	ActionUseMap::const_iterator it = useItemMap.find(item->getID());

	if (it != useItemMap.end()) {
		return it->second;
	}

	//rune items
	Action* runeSpell = g_spells->getRuneSpell(item->getID());

	if (runeSpell) {
		return runeSpell;
	}

	return NULL;
}

ReturnValue Actions::internalUseItem(Player* player, const Position& pos,
	uint8_t index, Item* item, uint32_t creatureId)
{
	if (Door* door = item->getDoor()) {
		if (!door->canUse(player)) {
			return RET_CANNOTUSETHISOBJECT;
		}
	}

	Action* action = getAction(item);

	if (action) {
		int32_t stack = item->getParent()->__getIndexOfThing(item);
		PositionEx posEx(pos, stack);

		if (action->isScripted()) {
			if (action->executeUse(player, item, posEx, posEx, false, creatureId)) {
				return RET_NOERROR;
			}
		} else if (action->function) {
			if (action->function(player, item, posEx, posEx, false, creatureId)) {
				return RET_NOERROR;
			}
		}
	}

	if (BedItem* bed = item->getBed()) {
		if (!bed->canUse(player)) {
			return RET_CANNOTUSETHISOBJECT;
		}

		if (bed->trySleep(player)) {
			player->setBedItem(bed);
			g_game.sendOfflineTrainingDialog(player);
		}

		return RET_NOERROR;
	}

	if (Container* container = item->getContainer()) {
		Container* openContainer = NULL;

		//depot container
		if (DepotLocker* depot = container->getDepotLocker()) {
			DepotLocker* myDepotLocker = player->getDepotLocker(depot->getDepotId());
			myDepotLocker->setParent(depot->getParent()->getTile());
			openContainer = myDepotLocker;
			player->setLastDepotId(depot->getDepotId());
		} else {
			openContainer = container;
		}

		if (container->getCorpseOwner() != 0 && !player->canOpenCorpse(container->getCorpseOwner())) {
			return RET_YOUARENOTTHEOWNER;
		}

		//open/close container
		int32_t oldContainerId = player->getContainerID(openContainer);
		if (oldContainerId != -1) {
			player->onCloseContainer(openContainer);
			player->closeContainer(oldContainerId);
		} else {
			player->addContainer(index, openContainer);
			player->onSendContainer(openContainer);
		}

		return RET_NOERROR;
	}

	if (item->isReadable()) {
		if (item->canWriteText()) {
			player->setWriteItem(item, item->getMaxWriteLength());
			player->sendTextWindow(item, item->getMaxWriteLength(), true);
		} else {
			player->setWriteItem(NULL);
			player->sendTextWindow(item, 0, false);
		}

		return RET_NOERROR;
	}

	return RET_CANNOTUSETHISOBJECT;
}

bool Actions::useItem(Player* player, const Position& pos, uint8_t index, Item* item, bool isHotkey)
{
	if (!player->canDoAction()) {
		return false;
	}

	player->setNextActionTask(NULL);
	player->setNextAction(OTSYS_TIME() + g_config.getNumber(ConfigManager::ACTIONS_DELAY_INTERVAL));
	player->stopWalk();

	if (isHotkey) {
		showUseHotkeyMessage(player, item->getID(), player->__getItemTypeCount(item->getID(), -1));
	}

	ReturnValue ret = internalUseItem(player, pos, index, item, 0);

	if (ret != RET_NOERROR) {
		player->sendCancelMessage(ret);
		return false;
	}

	return true;
}

bool Actions::useItemEx(Player* player, const Position& fromPos, const Position& toPos,
	uint8_t toStackPos, Item* item, bool isHotkey, uint32_t creatureId /* = 0*/)
{
	if (!player->canDoAction()) {
		return false;
	}

	player->setNextActionTask(NULL);
	player->setNextAction(OTSYS_TIME() + g_config.getNumber(ConfigManager::EX_ACTIONS_DELAY_INTERVAL));
	player->stopWalk();

	Action* action = getAction(item);

	if (!action) {
		player->sendCancelMessage(RET_CANNOTUSETHISOBJECT);
		return false;
	}

	ReturnValue ret = action->canExecuteAction(player, toPos);

	if (ret != RET_NOERROR) {
		player->sendCancelMessage(ret);
		return false;
	}

	if (isHotkey) {
		showUseHotkeyMessage(player, item->getID(), player->__getItemTypeCount(item->getID(), -1));
	}

	int32_t fromStackPos = item->getParent()->__getIndexOfThing(item);
	PositionEx fromPosEx(fromPos, fromStackPos);
	PositionEx toPosEx(toPos, toStackPos);

	if (!action->executeUse(player, item, fromPosEx, toPosEx, true, creatureId)) {
		if (!action->hasOwnErrorHandler()) {
			player->sendCancelMessage(RET_CANNOTUSETHISOBJECT);
		}

		return false;
	}

	return true;
}

void Actions::showUseHotkeyMessage(Player* player, int32_t id, uint32_t count)
{
	const ItemType& it = Item::items[id];
	std::ostringstream ss;

	if (!it.showCount) {
		ss << "Using one of " << it.name << "...";
	} else if (count == 1) {
		ss << "Using the last " << it.name << "...";
	} else {
		ss << "Using one of " << count << " " << it.getPluralName() << "...";
	}

	player->sendTextMessage(MSG_INFO_DESCR, ss.str());
}

bool Actions::hasAction(const Item* item)
{
	return getAction(item) != NULL;
}

Action::Action(LuaScriptInterface* _interface) :
	Event(_interface)
{
	allowFarUse = false;
	checkLineOfSight = true;
	function = NULL;
}

Action::Action(const Action* copy) :
	Event(copy)
{
	allowFarUse = copy->allowFarUse;
	checkLineOfSight = copy->checkLineOfSight;
	function = copy->function;
}

Action::~Action()
{
	//
}

bool Action::configureEvent(xmlNodePtr p)
{
	int32_t intValue;

	if (readXMLInteger(p, "allowfaruse", intValue)) {
		if (intValue != 0) {
			setAllowFarUse(true);
		}
	}

	if (readXMLInteger(p, "blockwalls", intValue)) {
		if (intValue == 0) {
			setCheckLineOfSight(false);
		}
	}

	return true;
}

bool Action::loadFunction(const std::string& functionName)
{
	const std::string& tmpFunctionName = asLowerCaseString(functionName);

	if (tmpFunctionName == "increaseitemid") {
		function = increaseItemId;
	} else if (tmpFunctionName == "decreaseitemid") {
		function = decreaseItemId;
	} else if (tmpFunctionName == "market") {
		function = enterMarket;
	} else {
		std::cout << "[Warning - Action::loadFunction] Function \"" << functionName << "\" does not exist." << std::endl;
		return false;
	}

	m_scripted = false;
	return true;
}

bool Action::increaseItemId(Player* player, Item* item, const PositionEx& posFrom, const PositionEx& posTo, bool extendedUse, uint32_t creatureId)
{
	Item* newItem = g_game.transformItem(item, item->getID() + 1);
	g_game.startDecay(newItem);
	return true;
}

bool Action::decreaseItemId(Player* player, Item* item, const PositionEx& posFrom, const PositionEx& posTo, bool extendedUse, uint32_t creatureId)
{
	Item* newItem = g_game.transformItem(item, item->getID() - 1);
	g_game.startDecay(newItem);
	return true;
}

bool Action::enterMarket(Player* player, Item* item, const PositionEx& posFrom, const PositionEx& posTo, bool extendedUse, uint32_t creatureId)
{
	if (!g_config.getBoolean(ConfigManager::MARKET_ENABLED)) {
		player->sendTextMessage(MSG_INFO_DESCR, "The market is disabled.");
		return false;
	}

	if (player->getLastDepotId() == -1) {
		return false;
	}

	player->sendMarketEnter(player->getLastDepotId());
	return true;
}

std::string Action::getScriptEventName()
{
	return "onUse";
}

ReturnValue Action::canExecuteAction(const Player* player, const Position& toPos)
{
	if (!getAllowFarUse()) {
		return g_actions->canUse(player, toPos);
	} else {
		return g_actions->canUseFar(player, toPos, getCheckLineOfSight());
	}
}

bool Action::executeUse(Player* player, Item* item, const PositionEx& fromPos, const PositionEx& toPos, bool extendedUse, uint32_t creatureId)
{
	//onUse(cid, item, fromPosition, itemEx, toPosition)
	if (!m_scriptInterface->reserveScriptEnv()) {
		std::cout << "[Error - Action::executeUse] Call stack overflow" << std::endl;
		return false;
	}

	ScriptEnvironment* env = m_scriptInterface->getScriptEnv();
	env->setScriptId(m_scriptId, m_scriptInterface);

	lua_State* L = m_scriptInterface->getLuaState();

	m_scriptInterface->pushFunction(m_scriptId);
	lua_pushnumber(L, player->getID());
	LuaScriptInterface::pushThing(L, item, env->addThing(item));
	LuaScriptInterface::pushPosition(L, fromPos, fromPos.stackpos);
	Thing* thing = g_game.internalGetThing(player, toPos, toPos.stackpos);
	if (thing && (!extendedUse || thing != item)) {
		LuaScriptInterface::pushThing(L, thing, env->addThing(thing));
		LuaScriptInterface::pushPosition(L, toPos, toPos.stackpos);
	} else {
		LuaScriptInterface::pushThing(L, NULL, 0);
		Position posEx;
		LuaScriptInterface::pushPosition(L, posEx, 0);
	}
	return m_scriptInterface->callFunction(5);
}
