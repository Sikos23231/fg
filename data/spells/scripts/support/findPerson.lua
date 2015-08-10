local directionNames = {
	["DIRECTION_NORTH"] = "north.",
	["DIRECTION_SOUTH"] = "south.",
	["DIRECTION_EAST"] = "east.",
	["DIRECTION_WEST"] = "west.",
	["DIRECTION_NORTHEAST"] = "north-east.",
	["DIRECTION_NORTHWEST"] = "north-west.",
	["DIRECTION_SOUTHEAST"] = "south-east.",
	["DIRECTION_SOUTHWEST"] = "south-west."
}

function onCastSpell(creature, var)
	if not creature:getPlayer() then
		return false
	end

	local targetPlayer = Player(Variant.getString(var))
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
	local distance = {
		x = playerPosition.x - targetPosition.x,
		y = playerPosition.y - targetPosition.y,
		z = playerPosition.z - targetPosition.z
	}

	local level = LEVEL_SAME
	if distance.z > 0 then
		level = LEVEL_HIGHER
	elseif distance.z < 0 then
		level = LEVEL_LOWER
	end

	local distanceOutput = DISTANCE_VERYFAR
	if math.abs(distance.x) < 4 and math.abs(distance.y) < 4 then
		distanceOutput = DISTANCE_BESIDE
	else
		local distanceFormula = ((distance.x * distance.x) + (distance.y * distance.y))
		if distanceFormula < 1000 then
			distanceOutput = DISTANCE_CLOSE
		elseif distanceFormula < 75076 then
			distanceOutput = DISTANCE_FAR
		end
	end

	local distanceValue = 10
	if distance.x ~= 0 then
		distanceValue = distance.y / distance.x
	end

	local absValue = math.abs(distanceValue)
	if absValue < 0.4142 then
		if distance.x > 0 then
			direction = DIRECTION_WEST
		else
			direction = DIRECTION_EAST
		end
	elseif absValue < 2.4142 then
		if distanceValue > 0 then
			if distance.y > 0 then
				direction = DIRECTION_NORTHWEST
			else
				direction = DIRECTION_SOUTHEAST
			end
		else
			if distance.x > 0 then
				direction = DIRECTION_SOUTHWEST
			else
				direction = DIRECTION_NORTHEAST
			end
		end
	else
		if distance.y > 0 then
			direction = DIRECTION_NORTH
		else
			direction = DIRECTION_SOUTH
		end
	end

	local returnMessage = targetPlayer:getName()
	if distanceOutput == DISTANCE_BESIDE then
		if level == LEVEL_SAME then
			returnMessage = returnMessage .. " is standing next to you."
		elseif level == LEVEL_HIGHER then
			returnMessage = returnMessage .. " is above you."
		elseif level == LEVEL_LOWER then
			returnMessage = returnMessage .. " is below you."
		end
	else
		if distanceOutput == DISTANCE_CLOSE then
			if level == LEVEL_SAME then
				returnMessage = returnMessage .. " is to the "
			elseif level == LEVEL_HIGHER then
				returnMessage = returnMessage .. " is on a higher level to the "
			elseif level == LEVEL_LOWER then
				returnMessage = returnMessage .. " is on a lower level to the "
			end
		elseif distanceOutput == DISTANCE_FAR then
			returnMessage = returnMessage .. " is far to the "
		elseif distanceOutput == DISTANCE_VERYFAR then
			returnMessage = returnMessage .. " is very far to the "
		end
	end

	returnMessage = returnMessage .. directionNames[direction]

	creature:sendTextMessage(MESSAGE_INFO_DESCR, returnMessage)
	playerPosition:sendMagicEffect(CONST_ME_MAGIC_BLUE)
	return true
end
