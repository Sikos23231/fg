function onUse(player, item, fromPosition, targetEx, toPosition, isHotkey)
	item:transform(2786)
	item:decay()
	Game.createItem(2677, 3, fromPosition)
	return true
end
