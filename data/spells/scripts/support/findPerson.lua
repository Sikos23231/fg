local LEVEL_LOWER = 1
local LEVEL_SAME = 2
local LEVEL_HIGHER = 3

local DISTANCE_BESIDE = 1
local DISTANCE_CLOSE = 2
local DISTANCE_FAR = 3
local DISTANCE_VERYFAR = 4

local directionNames = {
	[DIRECTION_NORTH] = "north",
	[DIRECTION_SOUTH] = "south",
	[DIRECTION_EAST] = "east",
	[DIRECTION_WEST] = "west",
	[DIRECTION_NORTHEAST] = "north-east",
	[DIRECTION_NORTHWEST] = "north-west",
	[DIRECTION_SOUTHEAST] = "south-east",
	[DIRECTION_SOUTHWEST] = "south-west"
}

local inShortRangeStrings = {
	[LEVEL_LOWER] = " is on a lower level to the ",
	[LEVEL_SAME] = " is to the ",
	[LEVEL_HIGHER] = " is on a higher level to the "
}

local isCloseStrings = {
	[LEVEL_LOWER] = " is below you",
	[LEVEL_SAME] = " is standing next to you",
	[LEVEL_HIGHER] = " is above you"
}

function onCastSpell(creature, variant)
	if not creature:getPlayer() then
		return false
	end

	local targetPlayer = Player(variant:getString())
	if not targetPlayer then
		return false
	end

	if targetPlayer:getGroup():getAccess() and not creature:getGroup():getAccess() then
		creature:sendCancelMessage(RETURNVALUE_PLAYERWITHTHISNAMEISNOTONLINE)
		creature:getPosition():sendMagicEffect(CONST_ME_POFF)
		return false
	end

	local playerPosition = creature:getPosition()
	local targetPosition = targetPlayer:getPosition()
	local offset = {
		x = playerPosition.x - targetPosition.x,
		y = playerPosition.y - targetPosition.y,
		z = playerPosition.z - targetPosition.z
	}

	local level = LEVEL_SAME
	if offset.z > 0 then
		level = LEVEL_HIGHER
	elseif offset.z < 0 then
		level = LEVEL_LOWER
	end

	local distanceOutput = DISTANCE_VERYFAR
	if math.abs(offset.x) < 4 and math.abs(offset.y) < 4 then
		distanceOutput = DISTANCE_BESIDE
	else
		local distanceFormula = ((offset.x * offset.x) + (offset.y * offset.y))
		if distanceFormula < 1000 then
			distanceOutput = DISTANCE_CLOSE
		elseif distanceFormula < 274 * 274 then
			distanceOutput = DISTANCE_FAR
		end
	end

	local direction
	local distanceValue = offset.x ~= 0 and (offset.y / offset.x) or 10
	local absValue = math.abs(distanceValue)
	if absValue < 0.4142 then
		direction = offset.x > 0 and DIRECTION_WEST or DIRECTION_EAST
	elseif absValue < 2.4142 then
		if distanceValue > 0 then
			direction = offset.y > 0 and DIRECTION_NORTHWEST or DIRECTION_SOUTHEAST
		elseif offset.x > 0 then
			direction = DIRECTION_SOUTHWEST
		else
			direction = DIRECTION_NORTHEAST
		end
	else
		direction = offset.y > 0 and DIRECTION_NORTH or DIRECTION_SOUTH
	end

	local returnMessage = targetPlayer:getName()
	if distanceOutput == DISTANCE_BESIDE then
		returnMessage = returnMessage .. isCloseStrings[level] .. "."
	elseif distanceOutput == DISTANCE_CLOSE then
		returnMessage = returnMessage .. inShortRangeStrings[level] .. directionNames[direction] .. "."
	elseif distanceOutput == DISTANCE_FAR then
		returnMessage = returnMessage .. " is far to the " .. directionNames[direction] .. "."
	elseif distanceOutput == DISTANCE_VERYFAR then
		returnMessage = returnMessage .. " is very far to the " .. directionNames[direction] .. "."
	end

	creature:sendTextMessage(MESSAGE_INFO_DESCR, returnMessage)
	playerPosition:sendMagicEffect(CONST_ME_MAGIC_BLUE)
	return true
end
