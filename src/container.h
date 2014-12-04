/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2014  Mark Samman <mark.samman@gmail.com>
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

#ifndef FS_CONTAINER_H_5590165FD8A2451B98D71F13CD3ED8DC
#define FS_CONTAINER_H_5590165FD8A2451B98D71F13CD3ED8DC

#include <queue>

#include "cylinder.h"
#include "item.h"

class Container;
class DepotChest;
class DepotLocker;

class ContainerIterator
{
	public:
		ContainerIterator();
		ContainerIterator(const ContainerIterator& rhs);
		~ContainerIterator();

		ContainerIterator& operator=(const ContainerIterator& rhs);
		bool operator==(const ContainerIterator& rhs) const;
		bool operator!=(const ContainerIterator& rhs) const;
		ContainerIterator& operator++();
		ContainerIterator operator++(int);
		Item* operator*();
		Item* operator->();

	protected:
		ContainerIterator(Container* super);

		Container* super;
		std::queue<Container*> over;
		ItemDeque::iterator cur;

		friend class Container;
};

class Container : public Item, public Cylinder
{
	public:
		Container(uint16_t _type);
		Container(Tile* tile);
		~Container();
		Item* clone() const final;

		Container* getContainer() final {
			return this;
		}
		const Container* getContainer() const final {
			return this;
		}

		virtual DepotLocker* getDepotLocker() {
			return nullptr;
		}
		virtual const DepotLocker* getDepotLocker() const {
			return nullptr;
		}

		Attr_ReadValue readAttr(AttrTypes_t attr, PropStream& propStream) override;
		bool unserializeItemNode(FileLoader& f, NODE node, PropStream& propStream) override;

		uint32_t size() const {
			return static_cast<uint32_t>(itemlist.size());
		}
		bool empty() const {
			return itemlist.empty();
		}
		uint32_t capacity() const {
			return maxSize;
		}

		ContainerIterator begin();
		ContainerIterator end();
		ContainerIterator begin() const;
		ContainerIterator end() const;

		const ItemDeque& getItemList() const {
			return itemlist;
		}

		ItemDeque::const_reverse_iterator getReversedItems() const {
			return itemlist.rbegin();
		}
		ItemDeque::const_reverse_iterator getReversedEnd() const {
			return itemlist.rend();
		}

		bool hasParent() const;
		void addItem(Item* item);
		Item* getItemByIndex(uint32_t index) const;
		bool isHoldingItem(const Item* item) const;

		uint32_t getItemHoldingCount() const;
		uint32_t getWeight() const final;

		bool isUnlocked() const {
			return unlocked;
		}
		bool hasPagination() const {
			return pagination;
		}

		//cylinder implementations
		virtual ReturnValue __queryAdd(int32_t index, const Thing* thing, uint32_t count,
		                               uint32_t flags, Creature* actor = nullptr) const override;
		ReturnValue __queryMaxCount(int32_t index, const Thing* thing, uint32_t count, uint32_t& maxQueryCount,
		                                    uint32_t flags) const final;
		ReturnValue __queryRemove(const Thing* thing, uint32_t count, uint32_t flags) const final;
		Cylinder* __queryDestination(int32_t& index, const Thing* thing, Item** destItem,
		                                     uint32_t& flags) final;

		void __addThing(Thing* thing) final;
		void __addThing(int32_t index, Thing* thing) final;
		void __addThingBack(Thing* thing);

		void __updateThing(Thing* thing, uint16_t itemId, uint32_t count) final;
		void __replaceThing(uint32_t index, Thing* thing) final;

		void __removeThing(Thing* thing, uint32_t count) final;

		int32_t __getIndexOfThing(const Thing* thing) const final;
		int32_t __getFirstIndex() const final;
		int32_t __getLastIndex() const final;
		uint32_t __getItemTypeCount(uint16_t itemId, int32_t subType = -1) const final;
		std::map<uint32_t, uint32_t>& __getAllItemTypeCount(std::map<uint32_t, uint32_t>& countMap) const final;
		Thing* __getThing(size_t index) const final;

		void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, cylinderlink_t link = LINK_OWNER) override;
		void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, bool isCompleteRemoval, cylinderlink_t link = LINK_OWNER) override;

		void __internalAddThing(Thing* thing) final;
		void __internalAddThing(uint32_t index, Thing* thing) final;
		void __startDecaying() final;

	private:
		void onAddContainerItem(Item* item);
		void onUpdateContainerItem(uint32_t index, Item* oldItem, Item* newItem);
		void onRemoveContainerItem(uint32_t index, Item* item);

		Container* getParentContainer();
		void updateItemWeight(int32_t diff);

	protected:
		uint32_t maxSize;
		uint32_t totalWeight;
		ItemDeque itemlist;
		uint32_t serializationCount;

		bool unlocked;
		bool pagination;

		friend class ContainerIterator;
		friend class IOMapSerialize;
};

#endif
