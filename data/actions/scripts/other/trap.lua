function onUse(player, item, fromPosition, targetEx, toPosition, isHotkey)
	item:transform(item:getId() - 1)
	fromPosition:sendMagicEffect(CONST_ME_POFF)
	return true
end
