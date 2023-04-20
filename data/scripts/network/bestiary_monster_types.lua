local handler = PacketHandler(0xE2)

function handler.onReceive(player, msg)
	local monsterTypes = {}
	local className = ""
	if msg:getByte() == 1 then -- Search Mode
		for i = 1, msg:getU16() do
			local raceId = msg:getU16()
			local monsterType = MonsterType(raceId)
			if monsterType and player:getBestiaryKills(raceId) > 0 then
				monsterTypes[#monsterTypes + 1] = monsterType
			end
		end
	else
		className = msg:getString()
		for _, class in pairs(Game.getBestiaryClasses()) do
			if class.name == className then
				monsterTypes = class.monsterTypes
				break
			end
		end
	end

	if #monsterTypes == 0 then
		return
	end

	local response = NetworkMessage()
	response:addByte(0xD6)
	response:addString(className)
	response:addU16(#monsterTypes)

	for _, monsterType in pairs(monsterTypes) do
		local info = monsterType:getBestiaryInfo()
		response:addU16(info.raceId)
		local kills = player:getBestiaryKills(info.raceId)
		if kills == 0 then
			response:addByte(0)
		else
			local step = 0
			for i, amount in pairs({0, unpack(monsterType:getBestiaryKills())}) do
				step = kills >= amount and i or step
			end
			response:addU16(step)
		end
	end

	response:sendToPlayer(player)
	response:delete()
end

handler:register()
