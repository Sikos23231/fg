function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if player:getStorageValue(PlayerStorageKeys.delayLargeSeaShell) > os.time() then
		player:say("You have already opened a shell today.", TALKTYPE_MONSTER_SAY, false, player, item:getPosition())
		return true
	end

	local msg = ""
	local chance = math.random(100)
	if chance <= 16 then
		doTargetCombat(0, player, COMBAT_PHYSICALDAMAGE, -200, -200, CONST_ME_NONE)
		msg = "Ouch! You squeezed your fingers."
	elseif chance > 16 and chance <= 64 then
		Game.createItem(math.random(7632, 7633), 1, player:getPosition())
		msg = "You found a beautiful pearl."
		player:addAchievementProgress("Shell Seeker", 100)
	else
		msg = "Nothing is inside."
	end

	player:say(msg, TALKTYPE_MONSTER_SAY, false, player, item:getPosition())
	item:transform(7553) -- large seashell
	item:decay()
	item:getPosition():sendMagicEffect(CONST_ME_BUBBLES)
	player:setStorageValue(PlayerStorageKeys.delayLargeSeaShell, os.time() + (20 * 60 * 60))
	return true
end
