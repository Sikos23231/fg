function onCastSpell(creature, var)
	local monsterName = Variant.getString(var)
	local monsterType = MonsterType(monsterName)

	if monsterType then
		creature:sendTextMessage(MESSAGE_STATUS_SMALL, RETURNVALUE_NOTPOSSIBLE)
		creature:getPosition():sendMagicEffect(CONST_ME_POFF)
		return false
	end

	if not getPlayerFlagValue(creature, PlayerFlag_CanSummonAll) then
		if not monsterType:isSummonable() then
			creature:sendTextMessage(MESSAGE_STATUS_SMALL, RETURNVALUE_NOTPOSSIBLE)
			creature:getPosition():sendMagicEffect(CONST_ME_POFF)
			return false
		end

		if creature:getMana() < monsterType:getManaCost() then
			creature:sendTextMessage(MESSAGE_STATUS_SMALL, RETURNVALUE_NOTENOUGHMANA)
			creature:getPosition():sendMagicEffect(CONST_ME_POFF)
			return false
		end

		if #creature:getSummons() >= 3 then
			creature:sendTextMessage(MESSAGE_STATUS_SMALL, "You cannot summon more creatures.")
			creature:getPosition():sendMagicEffect(CONST_ME_POFF)
			return false
		end
	end

	local position = creature:getPosition()
	local summon = Game.createMonster(monsterName, position, true)
	if not summon then
		creature:sendTextMessage(MESSAGE_STATUS_SMALL, RETURNVALUE_NOTENOUGHROOM)
		position:sendMagicEffect(CONST_ME_POFF)
		return false
	end

	summon:setMaster(creature)
	position:sendMagicEffect(CONST_ME_MAGIC_BLUE)
	summon:getPosition():sendMagicEffect(CONST_ME_TELEPORT)
	return true
end
