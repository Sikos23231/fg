/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2019  Mark Samman <mark.samman@gmail.com>
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

#include <fmt/format.h>

#include "teleport.h"
#include "game.h"

extern Game g_game;

Attr_ReadValue Teleport::readAttr(AttrTypes_t attr, PropStream& propStream)
{
	if (attr == ATTR_TELE_DEST) {
		if (!propStream.read<uint16_t>(destPos.x) || !propStream.read<uint16_t>(destPos.y) || !propStream.read<uint8_t>(destPos.z)) {
			return ATTR_READ_ERROR;
		}
		return ATTR_READ_CONTINUE;
	}
	return Item::readAttr(attr, propStream);
}

void Teleport::serializeAttr(PropWriteStream& propWriteStream) const
{
	Item::serializeAttr(propWriteStream);

	propWriteStream.write<uint8_t>(ATTR_TELE_DEST);
	propWriteStream.write<uint16_t>(destPos.x);
	propWriteStream.write<uint16_t>(destPos.y);
	propWriteStream.write<uint8_t>(destPos.z);
}

ReturnValue Teleport::queryAdd(int32_t, const Thing&, uint32_t, uint32_t, Creature*) const
{
	return RETURNVALUE_NOTPOSSIBLE;
}

ReturnValue Teleport::queryMaxCount(int32_t, const Thing&, uint32_t, uint32_t&, uint32_t) const
{
	return RETURNVALUE_NOTPOSSIBLE;
}

ReturnValue Teleport::queryRemove(const Thing&, uint32_t, uint32_t, Creature* /*= nullptr */) const
{
	return RETURNVALUE_NOERROR;
}

Cylinder* Teleport::queryDestination(int32_t&, const Thing&, Item**, uint32_t&)
{
	return this;
}

void Teleport::addThing(Thing* thing)
{
	return addThing(0, thing);
}

bool Teleport::checkInfinityLoop(Tile* destTile)
{
	if (!destTile) {
		return false;
	}

	if (Teleport* teleport = destTile->getTeleportItem()) {
		const Position& nextDestPos = teleport->getDestPos();
		if (getPosition() == nextDestPos) {
			return true;
		}
		return checkInfinityLoop(g_game.map.getTile(nextDestPos));
	}
	return false;
}

void Teleport::addThing(int32_t, Thing* thing)
{
	Tile* destTile = g_game.map.getTile(destPos);
	if (!destTile) {
		return;
	}

	// Destination may be non-walkable on purpose ..
	if (!destTile->isWalkable()) {
		// .. but make sure players won't get stuck
		bool pathExists = false;
		for (uint16_t x = destPos.x - 1; x <= destPos.x + 1; ++x) {
			for (uint16_t y = destPos.y - 1; y <= destPos.y + 1; ++y) {
				if (x == destPos.x && y == destPos.y) {
					continue;
				}

				if (g_game.map.getTile(x, y, destPos.z)->isWalkable()) {
					pathExists = true;
					break;
				}
			}

			if (pathExists) {
				break;
			}
		}

		if (!pathExists) {
			Creature* creature = thing->getCreature();
			std::string msg = "";

			if (creature) {

				msg = "[Warning - Teleport::addThing] Invalid teleport at position ({0} / {1} / {2}) with destination ({3} / {4} / {5})\n";
				fmt::print(stdout, msg, creaturePos.x, creaturePos.y, creaturePos.z, destPos.x, destPos.y, destPos.z);

				Player* player = creature->getPlayer();
				msg = "Invalid Destination at Position({:d} / {:d} / {:d}). Please notify staff members.";
				player->sendTextMessage(MESSAGE_STATUS_SMALL, fmt::format(msg, destPos.x, destPos.y, destPos.z));
			} else {
				msg = "[Warning - Teleport::addThing] Invalid teleport with destination ({} / {} / {})\n";
				fmt::print(stdout, msg, destPos.x, destPos.y, destPos.z);
			}
			return;
		}
	}

	// Prevent infinity loop
	if (checkInfinityLoop(destTile)) {
		const Position& pos = getPosition();
		std::cout << "Warning: infinity loop teleport. " << pos << std::endl;
		return;
	}

	const MagicEffectClasses effect = Item::items[id].magicEffect;

	if (Creature* creature = thing->getCreature()) {
		Position origPos = creature->getPosition();
		g_game.internalCreatureTurn(creature, origPos.x > destPos.x ? DIRECTION_WEST : DIRECTION_EAST);
		g_game.map.moveCreature(*creature, *destTile);
		if (effect != CONST_ME_NONE) {
			g_game.addMagicEffect(origPos, effect);
			g_game.addMagicEffect(destTile->getPosition(), effect);
		}
	} else if (Item* item = thing->getItem()) {
		if (effect != CONST_ME_NONE) {
			g_game.addMagicEffect(destTile->getPosition(), effect);
			g_game.addMagicEffect(item->getPosition(), effect);
		}
		g_game.internalMoveItem(getTile(), destTile, INDEX_WHEREEVER, item, item->getItemCount(), nullptr, FLAG_NOLIMIT);
	}
}

void Teleport::updateThing(Thing*, uint16_t, uint32_t)
{
	//
}

void Teleport::replaceThing(uint32_t, Thing*)
{
	//
}

void Teleport::removeThing(Thing*, uint32_t)
{
	//
}

void Teleport::postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t)
{
	getParent()->postAddNotification(thing, oldParent, index, LINK_PARENT);
}

void Teleport::postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, cylinderlink_t)
{
	getParent()->postRemoveNotification(thing, newParent, index, LINK_PARENT);
}
