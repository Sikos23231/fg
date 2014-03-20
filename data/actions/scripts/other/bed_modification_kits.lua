local BEDS = {
	[7904] = {{7811, 7812}, {7813, 7814}}, -- green kit
	[7905] = {{7819, 7820}, {7821, 7822}}, -- yellow kit
	[7906] = {{7815, 7816}, {7817, 7818}}, -- red kit
	[7907] = {{1754, 1755}, {1760, 1761}},  -- removal kit
	[20252] = {{20197, 20198}, {20199, 20200}} -- canopy kit
}

local function internalBedTransform(item, itemEx, fromPosition, toPosition, ids)
	toPosition:getTile():getItemByType(ITEM_TYPE_BED):transform(ids[2])
	Item(itemEx.uid):transform(ids[1])

	fromPosition:sendMagicEffect(CONST_ME_POFF)
	toPosition:sendMagicEffect(CONST_ME_POFF)
	Item(item.uid):remove()
end

function onUse(cid, item, fromPosition, itemEx, toPosition)
	local newBed = BEDS[item.itemid]
	if not newBed or not toPosition:getTile():getHouse() then
		return false
	end

	if itemEx.itemid == newBed[1][1] or itemEx.itemid == newBed[2][1] then
		Player(cid):sendTextMessage(MESSAGE_STATUS_SMALL, "You already have this bed modification.")
		return true
	end

	for kit, bed in pairs(BEDS) do
		if bed[1][1] == itemEx.itemid then
			toPosition.y = toPosition.y + 1
			internalBedTransform(item, itemEx, fromPosition, toPosition, newBed[1])
			break
		elseif bed[2][1] == itemEx.itemid then
			toPosition.x = toPosition.x + 1
			internalBedTransform(item, itemEx, fromPosition, toPosition, newBed[2])
			break
		end
	end

	return true
end
