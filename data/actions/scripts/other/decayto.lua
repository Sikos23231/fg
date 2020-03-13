-- keep in sync with actions.xml
local decayItems = {
	[1479] = 1480, [1480] = 1479, [1634] = 1635, [1635] = 1634, [1636] = 1637,
	[1637] = 1636, [1638] = 1639, [1639] = 1638, [1640] = 1641, [1641] = 1640,
	[1786] = 1787, [1787] = 1786, [1788] = 1789, [1789] = 1788, [1790] = 1791,
	[1791] = 1790, [1792] = 1793, [1793] = 1792, [1873] = 1874, [1874] = 1873,
	[1875] = 1876, [1876] = 1875, [1945] = 1946, [1946] = 1945, [2037] = 2038,
	[2038] = 2037, [2039] = 2040, [2040] = 2039, [2041] = 2042, [2042] = 2041,
	[2044] = 2045, [2045] = 2044, [2047] = 2048, [2048] = 2047, [2050] = 2051,
	[2051] = 2050, [2052] = 2053, [2053] = 2052, [2054] = 2055, [2055] = 2054,
	[2058] = 2059, [2059] = 2058, [2060] = 2061, [2061] = 2060, [2064] = 2065,
	[2065] = 2064, [2066] = 2067, [2067] = 2066, [2068] = 2069, [2069] = 2068,
	[2096] = 2097, [2097] = 2096, [2162] = 2163, [2163] = 2162, [2578] = 2579,
	[3947] = 3948, [3948] = 3947, [5812] = 5813, [5813] = 5812, [6489] = 6490,
	[6490] = 6489, [7058] = 7059, [7059] = 7058, [8684] = 8685, [8685] = 8684,
	[8686] = 8687, [8687] = 8686, [8688] = 8689, [8689] = 8688, [8690] = 8691,
	[8691] = 8690, [9575] = 9576, [9576] = 9575, [9577] = 9578, [9578] = 9577,
	[9579] = 9580, [9580] = 9579, [9581] = 9582, [9582] = 9581, [9747] = 9748,
	[9748] = 9747, [9749] = 9750, [9750] = 9749, [19691] = 19692, [19692] = 19691,
	[7183] = 7184, [6572] = 6573, [10719] = 10720, [11401] = 11402, [25545] = 25546,
	[26098] = 26099
}

function onUse(player, item, fromPosition, target, toPosition, isHotkey)
	item:transform(decayItems[item.itemid])
	item:decay()
	return true
end
