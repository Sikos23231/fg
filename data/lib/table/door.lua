-- Note: The closedDoorUnlocked transform the door closed (only with onUse of the player) to the door locked (with onUse of the key), only need add the id of closedDoor and the lockedDoor.
-- The rest of the variables are self-explanatory, create more variables within the table and add the door ids in their variables.
-- Be careful, do not add quest door inside the level door table or contrariwise, this will lock the doors.

-- Keys doors start.
-- Doors locked. This is the doors with the description "It is locked".
keyLockedDoor = {
	{ closedDoor = 1628, openDoor = 1630},
	{ closedDoor = 1631, openDoor = 1633},
	{ closedDoor = 1650, openDoor = 1652},
	{ closedDoor = 1653, openDoor = 1655},
	{ closedDoor = 1668, openDoor = 1670},
	{ closedDoor = 1671, openDoor = 1673},
	{ closedDoor = 1682, openDoor = 1684},
	{ closedDoor = 1691, openDoor = 1693},
	{ closedDoor = 4912, openDoor = 4911},
	{ closedDoor = 4913, openDoor = 4914 },
	{ closedDoor = 5097, openDoor = 5099 },
	{ closedDoor = 5106, openDoor = 5108 },
	{ closedDoor = 5115, openDoor = 5117 },
	{ closedDoor = 5124, openDoor = 5126 },
	{ closedDoor = 5133, openDoor = 5135 },
	{ closedDoor = 5136, openDoor = 5138 },
	{ closedDoor = 5139, openDoor = 5141 },
	{ closedDoor = 5142, openDoor = 5144 },
	{ closedDoor = 5277, openDoor = 5279 },
	{ closedDoor = 5280, openDoor = 5282 },
	{ closedDoor = 5732, openDoor = 5734 },
	{ closedDoor = 5735, openDoor = 5737 },
	{ closedDoor = 6191, openDoor = 6193 },
	{ closedDoor = 6194, openDoor = 6196 },
	{ closedDoor = 6248, openDoor = 6250 },
	{ closedDoor = 6251, openDoor = 6253 },
	{ closedDoor = 6799, openDoor = 6796 },
	{ closedDoor = 6801, openDoor = 6798 },
	{ closedDoor = 7033, openDoor = 7035 },
	{ closedDoor = 7042, openDoor = 7044 },
	{ closedDoor = 7711, openDoor = 7713 },
	{ closedDoor = 7714, openDoor = 7716 },
	{ closedDoor = 8249, openDoor = 8251 },
	{ closedDoor = 8252, openDoor = 8254 },
	{ closedDoor = 9351, openDoor = 9353 },
	{ closedDoor = 9354, openDoor = 9356 },
	{ closedDoor = 9551, openDoor = 9553 },
	{ closedDoor = 9560, openDoor = 9562 },
	{ closedDoor = 9858, openDoor = 9860 },
	{ closedDoor = 9867, openDoor = 9869 },
	{ closedDoor = 11136, openDoor = 11138 },
	{ closedDoor = 11143, openDoor = 11145 },
	{ closedDoor = 11232, openDoor = 11234 },
	{ closedDoor = 11241, openDoor = 11243 },
	{ closedDoor = 13135, openDoor = 13137 },
	{ closedDoor = 17560, openDoor = 17562 },
	{ closedDoor = 17569, openDoor = 17571 },
	{ closedDoor = 17700, openDoor = 17702 },
	{ closedDoor = 17709, openDoor = 17711 },
	{ closedDoor = 17993, openDoor = 17995 },
	{ closedDoor = 18002, openDoor = 18004 },
	{ closedDoor = 20443, openDoor = 20445 },
	{ closedDoor = 20452, openDoor = 20454 }
}
	
-- This is the commons doors usually used in the keys, are opened just by using.
keyUnlockedDoor = {
	{ closedDoor = 1629, openDoor = 1630 },
	{ closedDoor = 1632, openDoor = 1633 },
	{ closedDoor = 1651, openDoor = 1652 },
	{ closedDoor = 1654, openDoor = 1655 },
	{ closedDoor = 1669, openDoor = 1670 },
	{ closedDoor = 1672, openDoor = 1673 },
	{ closedDoor = 1683, openDoor = 1684 },
	{ closedDoor = 1692, openDoor = 1693 },
	{ closedDoor = 5006, openDoor = 4914 },
	{ closedDoor = 5007, openDoor = 4911 },
	{ closedDoor = 5098, openDoor = 5099 },
	{ closedDoor = 5107, openDoor = 5108 },
	{ closedDoor = 5116, openDoor = 5117 },
	{ closedDoor = 5125, openDoor = 5126 },
	{ closedDoor = 5134, openDoor = 5135 },
	{ closedDoor = 5137, openDoor = 5138 },
	{ closedDoor = 5140, openDoor = 5141 },
	{ closedDoor = 5143, openDoor = 5144 },
	{ closedDoor = 5278, openDoor = 5279 },
	{ closedDoor = 5281, openDoor = 5282 },
	{ closedDoor = 5733, openDoor = 5734 },
	{ closedDoor = 5736, openDoor = 5737 },
	{ closedDoor = 6192, openDoor = 6193 },
	{ closedDoor = 6195, openDoor = 6196 },
	{ closedDoor = 6249, openDoor = 6250 },
	{ closedDoor = 6252, openDoor = 6253 },
	{ closedDoor = 6795, openDoor = 6796 },
	{ closedDoor = 7034, openDoor = 7035 },
	{ closedDoor = 7043, openDoor = 7044 },
	{ closedDoor = 7712, openDoor = 7713 },
	{ closedDoor = 7715, openDoor = 7716 },
	{ closedDoor = 8250, openDoor = 8251 },
	{ closedDoor = 8253, openDoor = 8254 },
	{ closedDoor = 9352, openDoor = 9353 },
	{ closedDoor = 9355, openDoor = 9356 },
	{ closedDoor = 9552, openDoor = 9553 },
	{ closedDoor = 9561, openDoor = 9562 },
	{ closedDoor = 9859, openDoor = 9860 },
	{ closedDoor = 9868, openDoor = 9869 },
	{ closedDoor = 11137, openDoor = 11138 },
	{ closedDoor = 11144, openDoor = 11145 },
	{ closedDoor = 11233, openDoor = 11234 },
	{ closedDoor = 11242, openDoor = 11243 },
	{ closedDoor = 13136, openDoor = 13137 },
	{ closedDoor = 17561, openDoor = 17562 },
	{ closedDoor = 17570, openDoor = 17571 },
	{ closedDoor = 17701, openDoor = 17702 },
	{ closedDoor = 17710, openDoor = 17711 },
	{ closedDoor = 17994, openDoor = 17995 },
	{ closedDoor = 18003, openDoor = 18004 },
	{ closedDoor = 20444, openDoor = 20445 },
	{ closedDoor = 20453, openDoor = 20454 },
}
-- Keys doors end. 
	
-- These are the common doors, the ones that just open and close without any special requirements.
customDoor = {
	{ closedDoor = 1638, openDoor = 1639 },
	{ closedDoor = 1640, openDoor = 1641 },
	{ closedDoor = 1656, openDoor = 1657 },
	{ closedDoor = 1658, openDoor = 1659 },
	{ closedDoor = 1685, openDoor = 1686 },
	{ closedDoor = 1694, openDoor = 1695 },
	{ closedDoor = 2177, openDoor = 2178 },
	{ closedDoor = 2179, openDoor = 2180 },
	{ closedDoor = 5082, openDoor = 5083 },
	{ closedDoor = 5084, openDoor = 5085 },
	{ closedDoor = 5100, openDoor = 5101 },
	{ closedDoor = 5109, openDoor = 5110 },
	{ closedDoor = 5118, openDoor = 5119 },
	{ closedDoor = 5127, openDoor = 5128 },
	{ closedDoor = 5283, openDoor = 5284 },
	{ closedDoor = 5285, openDoor = 5286 },
	{ closedDoor = 5514, openDoor = 5515 },
	{ closedDoor = 5516, openDoor = 5517 },
	{ closedDoor = 6197, openDoor = 6198 },
	{ closedDoor = 6199, openDoor = 6200 },
	{ closedDoor = 6254, openDoor = 6255 },
	{ closedDoor = 6256, openDoor = 6257 },
	{ closedDoor = 6797, openDoor = 6798 },
	{ closedDoor = 7036, openDoor = 7037 },
	{ closedDoor = 7045, openDoor = 7046 },
	{ closedDoor = 7054, openDoor = 7055 },
	{ closedDoor = 7056, openDoor = 7057 },
	{ closedDoor = 7717, openDoor = 7718 },
	{ closedDoor = 7719, openDoor = 7720 },
	{ closedDoor = 8255, openDoor = 8256 },
	{ closedDoor = 8257, openDoor = 8258 },
	{ closedDoor = 9357, openDoor = 9358 },
	{ closedDoor = 9359, openDoor = 9360 },
	{ closedDoor = 9554, openDoor = 9555 },
	{ closedDoor = 9563, openDoor = 9564 },
	{ closedDoor = 11705, openDoor = 11708 },
	{ closedDoor = 11714, openDoor = 11716 },
	{ closedDoor = 12249, openDoor = 12250 },
	{ closedDoor = 15687, openDoor = 15688 },
	{ closedDoor = 17563, openDoor = 17564 },
	{ closedDoor = 17572, openDoor = 17573 },
	{ closedDoor = 17703, openDoor = 17704 },
	{ closedDoor = 17712, openDoor = 17713 },
	{ closedDoor = 17996, openDoor = 17997 },
	{ closedDoor = 18005, openDoor = 18006 },
	{ closedDoor = 18025, openDoor = 18026 },
	{ closedDoor = 20446, openDoor = 20447 },
}

-- These are the doors for missions, they need access from some mission (storage) to be able to enter. Put the storage value in the action id of the door and it will open only to the player who has the storage value.
questDoor = {
	{ closedDoor = 1642, openDoor = 1643 },
	{ closedDoor = 1644, openDoor = 1645 },
	{ closedDoor = 1660, openDoor = 1661 },
	{ closedDoor = 1662, openDoor = 1663 },
	{ closedDoor = 1674, openDoor = 1675 },
	{ closedDoor = 1676, openDoor = 1677 },
	{ closedDoor = 1689, openDoor = 1690 },
	{ closedDoor = 1698, openDoor = 1699 },
	{ closedDoor = 5104, openDoor = 5105 },
	{ closedDoor = 5113, openDoor = 5114 },
	{ closedDoor = 5122, openDoor = 5123 },
	{ closedDoor = 5131, openDoor = 5132 },
	{ closedDoor = 5287, openDoor = 5288 },
	{ closedDoor = 5289, openDoor = 5290 },
	{ closedDoor = 6201, openDoor = 6202 },
	{ closedDoor = 6203, openDoor = 6204 },
	{ closedDoor = 6258, openDoor = 6259 },
	{ closedDoor = 6260, openDoor = 6261 },
	{ closedDoor = 7040, openDoor = 7041 },
	{ closedDoor = 7049, openDoor = 7050 },
	{ closedDoor = 7721, openDoor = 7722 },
	{ closedDoor = 7723, openDoor = 7724 },
	{ closedDoor = 8259, openDoor = 8260 },
	{ closedDoor = 8261, openDoor = 8262 },
	{ closedDoor = 9361, openDoor = 9362 },
	{ closedDoor = 9363, openDoor = 9364 },
	{ closedDoor = 9558, openDoor = 9559 },
	{ closedDoor = 9567, openDoor = 9568 },
	{ closedDoor = 9865, openDoor = 9866 },
	{ closedDoor = 9874, openDoor = 9875 },
	{ closedDoor = 11148, openDoor = 11149 },
	{ closedDoor = 11248, openDoor = 11249 },
	{ closedDoor = 12035, openDoor = 12036 },
	{ closedDoor = 17567, openDoor = 17568 },
	{ closedDoor = 17576, openDoor = 17577 },
	{ closedDoor = 17707, openDoor = 17708 },
	{ closedDoor = 17716, openDoor = 17717 },
	{ closedDoor = 18000, openDoor = 18001 },
	{ closedDoor = 18009, openDoor = 18010 },
	{ closedDoor = 20450, openDoor = 20451 },
	{ closedDoor = 20459, openDoor = 20460 },
	{ closedDoor = 22506, openDoor = 22507 },
	{ closedDoor = 22508, openDoor = 22509 },
}
	
-- Level doors.
-- It's simple, just add a 1 followed by the amount of levels the player needs to be able to pass.
-- For example:
-- Level 10 put the action id: 1010 on the door.
-- Level 100 put the action id: 1100 on the door. And so on.
levelDoor = {
	{ closedDoor = 1646, openDoor = 1647 },
	{ closedDoor = 1648, openDoor = 1649 },
	{ closedDoor = 1664, openDoor = 1665 },
	{ closedDoor = 1666, openDoor = 1667 },
	{ closedDoor = 1678, openDoor = 1679 },
	{ closedDoor = 1680, openDoor = 1681 },
	{ closedDoor = 1687, openDoor = 1688 },
	{ closedDoor = 1696, openDoor = 1697 },
	{ closedDoor = 5102, openDoor = 5103 },
	{ closedDoor = 5111, openDoor = 5112 },
	{ closedDoor = 5120, openDoor = 5121 },
	{ closedDoor = 5129, openDoor = 5130 },
	{ closedDoor = 5291, openDoor = 5292 },
	{ closedDoor = 5293, openDoor = 5294 },
	{ closedDoor = 6205, openDoor = 6206 },
	{ closedDoor = 6207, openDoor = 6208 },
	{ closedDoor = 6262, openDoor = 6263 },
	{ closedDoor = 6264, openDoor = 6265 },
	{ closedDoor = 7038, openDoor = 7039 },
	{ closedDoor = 7047, openDoor = 7048 },
	{ closedDoor = 7725, openDoor = 7726 },
	{ closedDoor = 7727, openDoor = 7728 },
	{ closedDoor = 8263, openDoor = 8264 },
	{ closedDoor = 8265, openDoor = 8266 },
	{ closedDoor = 9365, openDoor = 9366 },
	{ closedDoor = 9367, openDoor = 9368 },
	{ closedDoor = 9556, openDoor = 9557 },
	{ closedDoor = 9565, openDoor = 9566 },
	{ closedDoor = 9863, openDoor = 9864 },
	{ closedDoor = 9872, openDoor = 9873 },
	{ closedDoor = 11139, openDoor = 11140 },
	{ closedDoor = 11146, openDoor = 11147 },
	{ closedDoor = 11237, openDoor = 11238 },
	{ closedDoor = 11246, openDoor = 11247 },
	{ closedDoor = 12033, openDoor = 12034 },
	{ closedDoor = 15890, openDoor = 15891 },
	{ closedDoor = 15892, openDoor = 15893 },
	{ closedDoor = 17565, openDoor = 17566 },
	{ closedDoor = 17574, openDoor = 17575 },
	{ closedDoor = 17705, openDoor = 17706 },
	{ closedDoor = 17714, openDoor = 17715 },
	{ closedDoor = 17998, openDoor = 17999 },
	{ closedDoor = 18007, openDoor = 18008 },
	{ closedDoor = 20448, openDoor = 20449 },
	{ closedDoor = 20457, openDoor = 20458 },
	{ closedDoor = 22502, openDoor = 22503 },
	{ closedDoor = 22504, openDoor = 22505 },
}