-- Including the Advanced NPC System
dofile('data/npc/lib/npcsystem/npcsystem.lua')
dofile("data/npc/lib/revnpcsys/npc.lua")

function msgcontains(message, keyword)
	local message, keyword = message:lower(), keyword:lower()
	if message == keyword then
		return true
	end

	return message:find(keyword) and not message:find('(%w+)' .. keyword)
end


function doNpcSellItem(cid, itemid, amount, subType, ignoreCap, inBackpacks, backpack)
	local amount = amount or 1
	local subType = subType or 0
	local startingAmount = amount
	local result = RETURNVALUE_NOERROR
	local bpSize = 20
	local itemType = ItemType(itemid)

	if itemType:isStackable() then
		local stuff
		local bpsToAdd = math.ceil(amount / itemType:getStackSize() / bpSize)
		if inBackpacks then
			local bps = {}
			for i = 1, bpsToAdd, 1 do
				stuff = Game.createItem(backpack, 1)
				local itemAdded = true
				while startingAmount > 0 and itemAdded do
					local item = stuff:addItem(itemid, math.min(itemType:getStackSize(), startingAmount))
					if item then
						startingAmount = startingAmount - math.min(itemType:getStackSize(), startingAmount)
						itemAdded = true
					else
						itemAdded = false
					end
				end
				bps[i] = stuff
			end
			for i = 1, bpsToAdd, 1 do
				result = result and Player(cid):addItemEx(bps[i], ignoreCap)
			end

			if result ~= RETURNVALUE_NOERROR then
				for i = 1, bpsToAdd, 1 do
					if bps[i] then
						bps[i]:remove()
					end
				end
			end
		else
			while startingAmount > 0 and result == RETURNVALUE_NOERROR do
				stuff = Game.createItem(itemid, math.min(itemType:getStackSize(), startingAmount))
				if result == RETURNVALUE_NOERROR then
					result = Player(cid):addItemEx(stuff, ignoreCap)
					startingAmount = startingAmount - math.min(itemType:getStackSize(), startingAmount)
				end
			end
		end

		return result ~= RETURNVALUE_NOERROR and 0 or amount - startingAmount, 0
	end

	local a = 0
	if inBackpacks then
		local container, b = Game.createItem(backpack, 1), 1
		for i = 1, amount do
			local item = container:addItem(itemid, subType)
			if table.contains({(ItemType(backpack):getCapacity() * b), amount}, i) then
				if Player(cid):addItemEx(container, ignoreCap) ~= RETURNVALUE_NOERROR then
					b = b - 1
					break
				end

				a = i
				if amount > i then
					container = Game.createItem(backpack, 1)
					b = b + 1
				end
			end
		end
		return a, b
	end

	for i = 1, amount do -- normal method for non-stackable items
		local item = Game.createItem(itemid, subType)
		if Player(cid):addItemEx(item, ignoreCap) ~= RETURNVALUE_NOERROR then
			break
		end
		a = i
	end
	return a, 0
end

local func = function(cid, text, type, e, pcid)
	if Player(pcid):isPlayer() then
		local creature = Creature(cid)
		creature:say(text, type, false, pcid, creature:getPosition())
		e.done = true
	end
end

function doCreatureSayWithDelay(cid, text, type, delay, e, pcid)
	if Player(pcid):isPlayer() then
		e.done = false
		e.event = addEvent(func, delay < 1 and 1000 or delay, cid, text, type, e, pcid)
	end
end

function doPlayerSellItem(cid, itemid, count, cost)
	local player = Player(cid)
	if player:removeItem(itemid, count) then
		if not player:addMoney(cost) then
			error('Could not add money to ' .. player:getName() .. '(' .. cost .. 'gp)')
		end
		return true
	end
	return false
end

function doPlayerBuyItemContainer(cid, containerid, itemid, count, cost, charges)
	local player = Player(cid)
	if not player:removeTotalMoney(cost) then
		return false
	end

	for i = 1, count do
		local container = Game.createItem(containerid, 1)
		for x = 1, ItemType(containerid):getCapacity() do
			container:addItem(itemid, charges)
		end

		if player:addItemEx(container, true) ~= RETURNVALUE_NOERROR then
			return false
		end
	end
	return true
end
function getCount(string)
	local b, e = string:find("%d+")
	if not b then
		return -1
	end
	local count = tonumber(string:sub(b, e))
	if count > 2 ^ 32 - 1 then
		print("Warning: Casting value to 32bit to prevent crash\n" .. debug.traceback())
	end
	return b and e and math.min(2 ^ 32 - 1, count) or -1
end


function isValidMoney(money)
	return isNumber(money) and money > 0
end

function getMoneyCount(string)
	local b, e = string:find("%d+")
	if not b then
		return -1
	end
	local count = tonumber(string:sub(b, e))
	if count > 2 ^ 32 - 1 then
		print("Warning: Casting value to 32bit to prevent crash\n" .. debug.traceback())
	end
	local money = b and e and math.min(2 ^ 32 - 1, count) or -1
	if isValidMoney(money) then
		return money
	end
	return -1
end

function getMoneyWeight(money)
	local weight, currencyItems = 0, Game.getCurrencyItems()
	for index = #currencyItems, 1, -1 do
		local currency = currencyItems[index]
		local worth = currency:getWorth()
		local currencyCoins = math.floor(money / worth)
		if currencyCoins > 0 then
			money = money - (currencyCoins * worth)
			weight = weight + currency:getWeight(currencyCoins)
		end
	end
	return weight
end
