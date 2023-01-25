local transformSeeds = MoveEvent()

function transformSeeds.onAddItem(moveitem, tileitem, position)
	if moveitem:getId() == 7732 then -- seeds
		tileitem:transform(7665) -- flower pot
		tileitem:decay()
		moveitem:remove(1)
		position:sendMagicEffect(CONST_ME_MAGIC_GREEN)
	elseif moveitem:getId() == 15271 then -- ice flower seeds
		tileitem:transform(15442) -- flower pot
		tileitem:decay()
		moveitem:remove(1)
		position:sendMagicEffect(CONST_ME_MAGIC_BLUE)
	end
	return true
end

transformSeeds:type("additem")
transformSeeds:id(7655) -- empty flower pot
transformSeeds:register()
