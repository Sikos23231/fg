local condition = Condition(CONDITION_DROWN)
condition:setParameter(CONDITION_PARAM_PERIODICDAMAGE, -20)
condition:setParameter(CONDITION_PARAM_TICKS, -1)
condition:setParameter(CONDITION_PARAM_TICKINTERVAL, 2000)

local drowningStepIn = MoveEvent()

function drowningStepIn.onStepIn(creature, item, position, fromPosition)
	local player = creature:getPlayer()
	if not player then
		return true
	end

	if math.random(1, 10) == 1 then
		position:sendMagicEffect(CONST_ME_BUBBLES)
	end
	creature:addCondition(condition)
	return true
end

drowningStepIn:id(5404,5405,5406,5407,5408,5409,9291)
drowningStepIn:register()
