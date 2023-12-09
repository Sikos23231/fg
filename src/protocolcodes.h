// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_PROTOCOLCODES_H
#define FS_PROTOCOLCODES_H

enum LoginServerOpcodes_t : uint8_t
{
	LOGIN_SERVER_ERROR = 10,
	LOGIN_SERVER_ERROR_NEW = 11,
	LOGIN_SERVER_TOKEN_SUCCESS = 12,
	LOGIN_SERVER_TOKEN_ERROR = 13,
	LOGIN_SERVER_UPDATE = 17,
	LOGIN_SERVER_MOTD = 20,
	LOGIN_SERVER_UPDATE_NEEDED = 30,
	LOGIN_SERVER_SESSION_KEY = 40,
	LOGIN_SERVER_CHARACTER_LIST = 100,
	LOGIN_SERVER_EXTENDED_CHARACTER_LIST = 101,
};

enum ItemOpcodes_t : uint8_t
{
	STATIC_TEXT = 96,
	UNKNOWN_CREATURE = 97,
	OUTDATED_CREATURE = 98,
	CREATURE = 99
};

enum GameServerOpcodes_t : uint8_t
{
	GAME_SERVER_LOGIN_OR_PENDING_STATE = 10,
	GAME_SERVER_GM_ACTIONS = 11,
	GAME_SERVER_ENTER_GAME = 15,
	GAME_SERVER_UPDATE_NEEDED = 17,
	GAME_SERVER_LOGIN_ERROR = 20,
	GAME_SERVER_LOGIN_ADVICE = 21,
	GAME_SERVER_LOGIN_WAIT = 22,
	GAME_SERVER_LOGIN_SUCCESS = 23,
	GAME_SERVER_SESSION_END = 24,
	GAME_SERVER_STORE_BUTTON_INDICATORS = 25,
	GAME_SERVER_BUG_REPORT = 26,
	GAME_SERVER_PING_BACK = 29,
	GAME_SERVER_PING = 30,
	GAME_SERVER_CHALLENGE = 31,
	GAME_SERVER_DEATH = 40,
	GAME_SERVER_SUPPLY_STASH = 41,
	GAME_SERVER_SPECIAL_CONTAINER = 42,
	GAME_SERVER_PARTY_ANALYZER = 43,

	// all in game opcodes must be greater than 50
	GAME_SERVER_FIRST_GAME_OPCODE = 50,

	// otclient ONLY
	GAME_SERVER_EXTENDED_OPCODE = 50,

	// NOTE: add any custom opcodes in this range (51 - 99)
	GAME_SERVER_CHANGE_MAP_AWARE_RANGE = 51,
	GAME_SERVER_ATTCHED_EFFECT = 52,
	GAME_SERVER_DETACH_EFFECT = 53,
	GAME_SERVER_CREATURE_SHADER = 54,
	GAME_SERVER_MAP_SHADER = 55,
	GAME_SERVER_FLOOR_DESCRIPTION = 75,

	// official client ONLY
	GAME_SERVER_PASSIVE_COOLDOWN = 94,
	GAME_SERVER_BOSSTIARY_DATA = 97,
	GAME_SERVER_BOSSTIARY_SLOTS = 98,
	GAME_SERVER_SEND_CLIENT_CHECK = 99,
	GAME_SERVER_FULL_MAP = 100,
	GAME_SERVER_MAP_TOP_ROW = 101,
	GAME_SERVER_MAP_RIGHT_ROW = 102,
	GAME_SERVER_MAP_BOTTOM_ROW = 103,
	GAME_SERVER_MAP_LEFT_ROW = 104,
	GAME_SERVER_UPDATE_TILE = 105,
	GAME_SERVER_CREATE_ON_MAP = 106,
	GAME_SERVER_CHANGE_ON_MAP = 107,
	GAME_SERVER_DELETE_ON_MAP = 108,
	GAME_SERVER_MOVE_CREATURE = 109,
	GAME_SERVER_OPEN_CONTAINER = 110,
	GAME_SERVER_CLOSE_CONTAINER = 111,
	GAME_SERVER_CREATE_CONTAINER = 112,
	GAME_SERVER_CHANGE_IN_CONTAINER = 113,
	GAME_SERVER_DELETE_IN_CONTAINER = 114,
	GAME_SERVER_SET_INVENTORY = 120,
	GAME_SERVER_DELETE_INVENTORY = 121,
	GAME_SERVER_OPEN_NPC_TRADE = 122,
	GAME_SERVER_PLAYER_GOODS = 123,
	GAME_SERVER_CLOSE_NPC_TRADE = 124,
	GAME_SERVER_OWN_TRADE = 125,
	GAME_SERVER_COUNTER_TRADE = 126,
	GAME_SERVER_CLOSE_TRADE = 127,
	GAME_SERVER_AMBIENT = 130,
	GAME_SERVER_GRAPHICAL_EFFECT = 131,
	GAME_SERVER_TEXT_EFFECT = 132,
	GAME_SERVER_MISSLE_EFFECT = 133,
	GAME_SERVER_ITEM_CLASSES = 134,
	GAME_SERVER_TRAPPERS = 135,
	GAME_SERVER_CREATURE_HEALTH = 140,
	GAME_SERVER_CREATURE_LIGHT = 141,
	GAME_SERVER_CREATURE_OUTFIT = 142,
	GAME_SERVER_CREATURE_SPEED = 143,
	GAME_SERVER_CREATURE_SKULL = 144,
	GAME_SERVER_CREATURE_PARTY = 145,
	GAME_SERVER_CREATURE_UNPASS = 146,
	GAME_SERVER_CREATURE_MARKS = 147,
	GAME_SERVER_PLAYER_HELPERS = 148,
	GAME_SERVER_CREATURE_TYPE = 149,
	GAME_SERVER_EDIT_TEXT = 150,
	GAME_SERVER_EDIT_LIST = 151,
	GAME_SERVER_SEND_GAME_NEWS = 152,
	GAME_SERVER_SEND_BLESS_DIALOG = 155,
	GAME_SERVER_BLESSINGS = 156,
	GAME_SERVER_PRESET = 157,
	GAME_SERVER_PREMIUM_TRIGGER = 158,
	GAME_SERVER_PLAYER_DATA_BASIC = 159,
	GAME_SERVER_PLAYER_DATA = 160,
	GAME_SERVER_PLAYER_SKILLS = 161,
	GAME_SERVER_PLAYER_STATE = 162,
	GAME_SERVER_CLEAR_TARGET = 163,
	GAME_SERVER_SPELL_DELAY = 164,
	GAME_SERVER_SPELL_GROUP_DELAY = 165,
	GAME_SERVER_MULTI_USE_DELAY = 166,
	GAME_SERVER_PLAYER_MODES = 167,
	GAME_SERVER_SET_STORE_DEEP_LINK = 168,
	GAME_SERVER_SEND_RESTING_AREA_STATE = 169,
	GAME_SERVER_TALK = 170,
	GAME_SERVER_CHANNELS = 171,
	GAME_SERVER_OPEN_CHANNEL = 172,
	GAME_SERVER_OPEN_PRIVATE_CHANNEL = 173,
	GAME_SERVER_RULE_VIOLATION_CHANNEL = 174,
	GAME_SERVER_RULE_VIOLATION_REMOVE = 175,
	GAME_SERVER_EXPERIENCE_TRACKER = 175,
	GAME_SERVER_RULE_VIOLATION_CANCEL = 176,
	GAME_SERVER_RULE_VIOLATION_LOCK = 177,
	GAME_SERVER_OPEN_OWN_CHANNEL = 178,
	GAME_SERVER_CLOSE_CHANNEL = 179,
	GAME_SERVER_TEXT_MESSAGE = 180,
	GAME_SERVER_CANCEL_WALK = 181,
	GAME_SERVER_WALK_WAIT = 182,
	GAME_SERVER_UNJUSTIFIED_STATS = 183,
	GAME_SERVER_PVP_SITUATIONS = 184,
	GAME_SERVER_REFRESH_BESTIARY_TRACKER = 185,
	GAME_SERVER_TASK_HUNTING_BASIC_DATA = 186,
	GAME_SERVER_TASK_HUNTING_DATA = 187,
	GAME_SERVER_BOSSTIARY_COOLDOWN_TIMER = 189,
	GAME_SERVER_FLOOR_CHANGE_UP = 190,
	GAME_SERVER_FLOOR_CHANGE_DOWN = 191,
	GAME_SERVER_LOOT_CONTAINERS = 192,
	GAME_SERVER_CHOOSE_OUTFIT = 200,
	GAME_SERVER_SEND_UPDATE_IMPACT_TRACKER = 204,
	GAME_SERVER_SEND_ITEMS_PRICE = 205,
	GAME_SERVER_SEND_UPDATE_SUPPLY_TRACKER = 206,
	GAME_SERVER_SEND_UPDATE_LOOT_TRACKER = 207,
	GAME_SERVER_KILL_TRACKER = 209,
	GAME_SERVER_VIP_ADD = 210,
	GAME_SERVER_VIP_STATE = 211,
	GAME_SERVER_VIP_LOGOUT = 212,
	GAME_SERVER_SEND_BESTIARY_ENTRY_CHANGED = 217,
	GAME_SERVER_TUTORIAL_HINT = 220,
	GAME_SERVER_AUTOMAP_FLAG = 221,
	GAME_SERVER_SEND_DAILY_REWARD_COLLECTION_STATE = 222,
	GAME_SERVER_COIN_BALANCE = 223,
	GAME_SERVER_STORE_ERROR = 224,
	GAME_SERVER_REQUEST_PURCHASE_DATA = 225,
	GAME_SERVER_SEND_OPEN_REWARD_WALL = 226,
	GAME_SERVER_SEND_DAILY_REWARD = 228,
	GAME_SERVER_SEND_REWARD_HISTORY = 229,
	GAME_SERVER_SEND_PREY_FREE_REROLLS = 230,
	GAME_SERVER_SEND_BOSSTIARY_ENTRY_CHANGED = 230,
	GAME_SERVER_SEND_PREY_TIME_LEFT = 231,
	GAME_SERVER_SEND_PREY_DATA = 232,
	GAME_SERVER_SEND_PREY_REROLL_PRICE = 233,
	GAME_SERVER_SEND_SHOW_DESCRIPTION = 234,
	GAME_SERVER_SEND_IMBUEMENT_WINDOW = 235,
	GAME_SERVER_SEND_CLOSE_IMBUEMENT_WINDOW = 236,
	GAME_SERVER_SEND_ERROR = 237,
	GAME_SERVER_RESOURCE_BALANCE = 238,
	GAME_SERVER_WORLD_TIME = 239,
	GAME_SERVER_QUEST_LOG = 240,
	GAME_SERVER_QUEST_LINE = 241,
	GAME_SERVER_COIN_BALANCE_UPDATING = 242,
	GAME_SERVER_CHANNEL_EVENT = 243,
	GAME_SERVER_ITEM_INFO = 244,
	GAME_SERVER_PLAYER_INVENTORY = 245,
	GAME_SERVER_MARKET_ENTER = 246,
	GAME_SERVER_MARKET_LEAVE = 247,
	GAME_SERVER_MARKET_DETAIL = 248,
	GAME_SERVER_MARKET_BROWSE = 249,
	GAME_SERVER_MODAL_DIALOG = 250,
	GAME_SERVER_STORE = 251,
	GAME_SERVER_STORE_OFFERS = 252,
	GAME_SERVER_STORE_TRANSACTION_HISTORY = 253,
	GAME_SERVER_STORE_COMPLETE_PURCHASE = 254
};

enum ClientOpcodes : uint8_t
{
	CLIENT_ENTER_ACCOUNT = 1,
	CLIENT_PENDING_GAME = 10,
	CLIENT_ENTER_GAME = 15,
	CLIENT_LEAVE_GAME = 20,
	CLIENT_PING = 29,
	CLIENT_PING_BACK = 30,

	CLIENT_STASH_WITHDRAW = 40,
	CLIENT_RETRIEVE_DEPOT_SEARCH = 41,
	CLIENT_CYCLOPEDIA_MONSTER_TRACKER = 42,
	CLIENT_PARTY_ANALYZER_ACTION = 43,
	CLIENT_LEADER_FINDER_WINDOW = 44,
	CLIENT_MEMBER_FINDER_WINDOW = 45,

	// all in game opcodes must be equal or greater than 50
	CLIENT_FIRST_GAME_OPCODE = 50,

	// otclient ONLY
	CLIENT_EXTENDED_OPCODE = 50,
	CLIENT_CHANGE_MAP_AWARE_RANGE = 51,

	// NOTE: add any custom opcodes in this range (51 - 99)

	// official client ONLY
	CLIENT_AUTO_WALK = 100,
	CLIENT_WALK_NORTH = 101,
	CLIENT_WALK_EAST = 102,
	CLIENT_WALK_SOUTH = 103,
	CLIENT_WALK_WEST = 104,
	CLIENT_STOP = 105,
	CLIENT_WALK_NORTH_EAST = 106,
	CLIENT_WALK_SOUTH_EAST = 107,
	CLIENT_WALK_SOUTH_WEST = 108,
	CLIENT_WALK_NORTH_WEST = 109,
	CLIENT_TURN_NORTH = 111,
	CLIENT_TURN_EAST = 112,
	CLIENT_TURN_SOUTH = 113,
	CLIENT_TURN_WEST = 114,
	CLIENT_MAP_CLICK = 115,
	CLIENT_EQUIP_ITEM = 119,
	CLIENT_MOVE = 120,
	CLIENT_INSPECT_NPC_TRADE = 121,
	CLIENT_BUY_ITEM = 122,
	CLIENT_SELL_ITEM = 123,
	CLIENT_CLOSE_NPC_TRADE = 124,
	CLIENT_REQUEST_TRADE = 125,
	CLIENT_INSPECT_TRADE = 126,
	CLIENT_ACCEPT_TRADE = 127,
	CLIENT_REJECT_TRADE = 128,
	CLIENT_USE_ITEM = 130,
	CLIENT_USE_ITEM_WITH = 131,
	CLIENT_USE_ON_CREATURE = 132,
	CLIENT_ROTATE_ITEM = 133,
	CLIENT_EDIT_PODIUM = 134,
	CLIENT_CLOSE_CONTAINER = 135,
	CLIENT_UP_CONTAINER = 136,
	CLIENT_EDIT_TEXT = 137,
	CLIENT_EDIT_LIST = 138,
	CLIENT_ON_WRAP_ITEM = 139,
	CLIENT_LOOK = 140,
	CLIENT_LOOK_CREATURE = 141,
	CLIENT_JOIN_AGGRESSION = 142,
	CLIENT_QUICK_LOOT = 143,
	CLIENT_LOOT_CONTAINER = 144,
	CLIENT_UPDATE_LOOT_WHITELIST = 145,
	CLIENT_REQUEST_LOCKER_ITEMS = 146,
	CLIENT_TALK = 150,
	CLIENT_REQUEST_CHANNELS = 151,
	CLIENT_JOIN_CHANNEL = 152,
	CLIENT_LEAVE_CHANNEL = 153,
	CLIENT_OPEN_PRIVATE_CHANNEL = 154,
	CLIENT_OPEN_RULE_VIOLATION = 155,
	CLIENT_CLOSE_RULE_VIOLATION = 156,
	CLIENT_CANCEL_RULE_VIOLATION = 157,
	CLIENT_CLOSE_NPC_CHANNEL = 158,
	CLIENT_CHANGE_FIGHT_MODES = 160,
	CLIENT_ATTACK = 161,
	CLIENT_FOLLOW = 162,
	CLIENT_INVITE_TO_PARTY = 163,
	CLIENT_JOIN_PARTY = 164,
	CLIENT_REVOKE_INVITATION = 165,
	CLIENT_PASS_LEADERSHIP = 166,
	CLIENT_LEAVE_PARTY = 167,
	CLIENT_SHARE_EXPERIENCE = 168,
	CLIENT_DISBAND_PARTY = 169,
	CLIENT_OPEN_OWN_CHANNEL = 170,
	CLIENT_INVITE_TO_OWN_CHANNEL = 171,
	CLIENT_EXCLUDE_FROM_OWN_CHANNEL = 172,
	CLIENT_REQUEST_HIGHSCORES = 177,
	CLIENT_CANCEL_ATTACK_AND_FOLLOW = 190,
	CLIENT_REQUEST_TOURNAMENT_LEADERBOARD = 199,
	CLIENT_UPDATE_TILE = 201,
	CLIENT_REFRESH_CONTAINER = 202,
	CLIENT_BROWSE_FIELD = 203,
	CLIENT_SEEK_IN_CONTAINER = 204,
	CLIENT_REQUEST_INSPECT_WINDOW = 205,
	CLIENT_REQUEST_QUEST_TRACKER = 208,
	CLIENT_REQUEST_OUTFIT = 210,
	CLIENT_CHANGE_OUTFIT = 211,
	CLIENT_MOUNT = 212,
	CLIENT_APPLY_IMBUEMENT = 213,
	CLIENT_CLEAR_IMBUEMENT = 214,
	CLIENT_CLOSE_IMBUING_WINDOW = 215,
	CLIENT_ADD_VIP = 220,
	CLIENT_REMOVE_VIP = 221,
	CLIENT_EDIT_VIP = 222,
	CLIENT_PREMIUM_SHOP_UNKNOWN_1 = 223,
	CLIENT_PREMIUM_SHOP_UNKNOWN_2 = 224,
	CLIENT_REQUEST_BESTIARY_CLASSES = 225,
	CLIENT_REQUEST_BESTIARY_MONSTERS = 226,
	CLIENT_REQUEST_BESTIARY_INFO = 227,
	CLIENT_BUY_CHARM_RUNE = 228,
	CLIENT_REQUEST_CYCLOPEDIA_CHARACTER_INFO = 229,
	CLIENT_BUG_REPORT = 230,
	CLIENT_RULE_VIOLATION = 231,
	CLIENT_DEBUG_REPORT = 232,
	CLIENT_PREY_ACTION = 235,
	CLIENT_PREY_REQUEST = 237,
	CLIENT_GREET = 237,
	CLIENT_REQUEST_TRANSFER_COINS = 239,
	CLIENT_REQUEST_QUEST_LOG = 240,
	CLIENT_REQUEST_QUEST_LINE = 241,
	CLIENT_NEW_RULE_VIOLATION = 242,
	CLIENT_REQUEST_ITEM_INFO = 243,
	CLIENT_MARKET_LEAVE = 244,
	CLIENT_MARKET_BROWSE = 245,
	CLIENT_MARKET_CREATE = 246,
	CLIENT_MARKET_CANCEL = 247,
	CLIENT_MARKET_ACCEPT = 248,
	CLIENT_ANSWER_MODAL_DIALOG = 249,
	CLIENT_OPEN_STORE = 250,
	CLIENT_REQUEST_STORE_OFFERS = 251,
	CLIENT_BUY_STORE_OFFER = 252,
	CLIENT_OPEN_TRANSACTION_HISTORY = 253,
	CLIENT_REQUEST_TRANSACTION_HISTORY = 254
};

#endif // FS_PROTOCOLCODES_H
