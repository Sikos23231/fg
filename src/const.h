/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2015  Mark Samman <mark.samman@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef FS_CONST_H_0A49B5996F074465BF44B90F4F780E8B
#define FS_CONST_H_0A49B5996F074465BF44B90F4F780E8B

#define NETWORKMESSAGE_MAXSIZE 24590

enum MagicEffectClasses : uint8_t {
	CONST_ME_FIRST = 1,
	CONST_ME_DRAWBLOOD = CONST_ME_FIRST,
	CONST_ME_LOSEENERGY = 2,
	CONST_ME_POFF = 3,
	CONST_ME_BLOCKHIT = 4,
	CONST_ME_EXPLOSIONAREA = 5,
	CONST_ME_EXPLOSIONHIT = 6,
	CONST_ME_FIREAREA = 7,
	CONST_ME_YELLOW_RINGS = 8,
	CONST_ME_GREEN_RINGS = 9,
	CONST_ME_HITAREA = 10,
	CONST_ME_TELEPORT = 11,
	CONST_ME_ENERGYHIT = 12,
	CONST_ME_MAGIC_BLUE = 13,
	CONST_ME_MAGIC_RED = 14,
	CONST_ME_MAGIC_GREEN = 15,
	CONST_ME_HITBYFIRE = 16,
	CONST_ME_HITBYPOISON = 17,
	CONST_ME_MORTAREA = 18,
	CONST_ME_SOUND_GREEN = 19,
	CONST_ME_SOUND_RED = 20,
	CONST_ME_POISONAREA = 21,
	CONST_ME_SOUND_YELLOW = 22,
	CONST_ME_SOUND_PURPLE = 23,
	CONST_ME_SOUND_BLUE = 24,
	CONST_ME_SOUND_WHITE = 25,
	CONST_ME_BUBBLES = 26,
	CONST_ME_CRAPS = 27,
	CONST_ME_GIFT_WRAPS = 28,
	CONST_ME_FIREWORK_YELLOW = 29,
	CONST_ME_FIREWORK_RED = 30,
	CONST_ME_FIREWORK_BLUE = 31,
	CONST_ME_STUN = 32,
	CONST_ME_SLEEP = 33,
	CONST_ME_WATERCREATURE = 34,
	CONST_ME_GROUNDSHAKER = 35,
	CONST_ME_HEARTS = 36,
	CONST_ME_FIREATTACK = 37,
	CONST_ME_ENERGYAREA = 38,
	CONST_ME_SMALLCLOUDS = 39,
	CONST_ME_HOLYDAMAGE = 40,
	CONST_ME_BIGCLOUDS = 41,
	CONST_ME_ICEAREA = 42,
	CONST_ME_ICETORNADO = 43,
	CONST_ME_ICEATTACK = 44,
	CONST_ME_STONES = 45,
	CONST_ME_SMALLPLANTS = 46,
	CONST_ME_CARNIPHILA = 47,
	CONST_ME_PURPLEENERGY = 48,
	CONST_ME_YELLOWENERGY = 49,
	CONST_ME_HOLYAREA = 50,
	CONST_ME_BIGPLANTS = 51,
	CONST_ME_CAKE = 52,
	CONST_ME_GIANTICE = 53,
	CONST_ME_WATERSPLASH = 54,
	CONST_ME_PLANTATTACK = 55,
	CONST_ME_TUTORIALARROW = 56,
	CONST_ME_TUTORIALSQUARE = 57,
	CONST_ME_MIRRORHORIZONTAL = 58,
	CONST_ME_MIRRORVERTICAL = 59,
	CONST_ME_SKULLHORIZONTAL = 60,
	CONST_ME_SKULLVERTICAL = 61,
	CONST_ME_ASSASSIN = 62,
	CONST_ME_STEPSHORIZONTAL = 63,
	CONST_ME_BLOODYSTEPS = 64,
	CONST_ME_STEPSVERTICAL = 65,
	CONST_ME_YALAHARIGHOST = 66,
	CONST_ME_BATS = 67,
	CONST_ME_SMOKE = 68,
	CONST_ME_INSECTS = 69,
	CONST_ME_DRAGONHEAD = 70,
	CONST_ME_ORCSHAMAN = 71,
	CONST_ME_ORCSHAMAN_FIRE = 72,
	CONST_ME_THUNDER = 73,
	CONST_ME_FERUMBRAS = 74,
	CONST_ME_CONFETTI_HORIZONTAL = 75,
	CONST_ME_CONFETTI_VERTICAL = 76,
	// 77-157 are empty
	CONST_ME_BLACKSMOKE = 158,
	// 158-166 are empty
	CONST_ME_REDSMOKE = 167,
	CONST_ME_YELLOWSMOKE = 168,
	CONST_ME_GREENSMOKE = 169,
	CONST_ME_PURPLESMOKE = 170,
	CONST_ME_LAST = CONST_ME_PURPLESMOKE,

	//for internal use, dont send to client
	CONST_ME_NONE             = 0xFF
};

enum ShootType_t : uint8_t {
	CONST_ANI_NONE = 0,
	CONST_ANI_FIRST = 1,
	CONST_ANI_SPEAR = CONST_ANI_FIRST,
	CONST_ANI_BOLT = 2,
	CONST_ANI_ARROW = 3,
	CONST_ANI_FIRE = 4,
	CONST_ANI_ENERGY = 5,
	CONST_ANI_POISONARROW = 6,
	CONST_ANI_BURSTARROW = 7,
	CONST_ANI_THROWINGSTAR = 8,
	CONST_ANI_THROWINGKNIFE = 9,
	CONST_ANI_SMALLSTONE = 10,
	CONST_ANI_DEATH = 11,
	CONST_ANI_LARGEROCK = 12,
	CONST_ANI_SNOWBALL = 13,
	CONST_ANI_POWERBOLT = 14,
	CONST_ANI_POISON = 15,
	CONST_ANI_INFERNALBOLT = 16,
	CONST_ANI_HUNTINGSPEAR = 17,
	CONST_ANI_ENCHANTEDSPEAR = 18,
	CONST_ANI_REDSTAR = 19,
	CONST_ANI_GREENSTAR = 20,
	CONST_ANI_ROYALSPEAR = 21,
	CONST_ANI_SNIPERARROW = 22,
	CONST_ANI_ONYXARROW = 23,
	CONST_ANI_PIERCINGBOLT = 24,
	CONST_ANI_WHIRLWINDSWORD = 25,
	CONST_ANI_WHIRLWINDAXE = 26,
	CONST_ANI_WHIRLWINDCLUB = 27,
	CONST_ANI_ETHEREALSPEAR = 28,
	CONST_ANI_ICE = 29,
	CONST_ANI_EARTH = 30,
	CONST_ANI_HOLY = 31,
	CONST_ANI_SUDDENDEATH = 32,
	CONST_ANI_FLASHARROW = 33,
	CONST_ANI_FLAMMINGARROW = 34,
	CONST_ANI_SHIVERARROW = 35,
	CONST_ANI_ENERGYBALL = 36,
	CONST_ANI_SMALLICE = 37,
	CONST_ANI_SMALLHOLY = 38,
	CONST_ANI_SMALLEARTH = 39,
	CONST_ANI_EARTHARROW = 40,
	CONST_ANI_EXPLOSION = 41,
	CONST_ANI_CAKE = 42,

	CONST_ANI_TARSALARROW = 44,
	CONST_ANI_VORTEXBOLT = 45,

	CONST_ANI_PRISMATICBOLT = 48,
	CONST_ANI_CRYSTALLINEARROW = 49,
	CONST_ANI_DRILLBOLT = 50,
	CONST_ANI_ENVENOMEDARROW = 51,

	CONST_ANI_GLOOTHSPEAR = 53,
	CONST_ANI_SIMPLEARROW = 54,

	//for internal use, dont send to client
	CONST_ANI_WEAPONTYPE = 0xFE //254
};

enum SpeakClasses : uint8_t {
	TALKTYPE_SAY = 1,
	TALKTYPE_WHISPER = 2,
	TALKTYPE_YELL = 3,
	TALKTYPE_PRIVATE_FROM = 4,
	TALKTYPE_PRIVATE_TO = 5,
	TALKTYPE_CHANNEL_MANAGEMENT = 6,
	TALKTYPE_CHANNEL_Y = 7,
	TALKTYPE_CHANNEL_O = 8,
	TALKTYPE_PRIVATE_NP = 10,
	TALKTYPE_PRIVATE_PN = 12,
	TALKTYPE_BROADCAST = 13,
	TALKTYPE_CHANNEL_R1 = 14, //red - #c text
	TALKTYPE_PRIVATE_RED_FROM = 15, //@name@text
	TALKTYPE_PRIVATE_RED_TO = 16, //@name@text
	TALKTYPE_MONSTER_SAY = 36,
	TALKTYPE_MONSTER_YELL = 37,

	TALKTYPE_CHANNEL_R2 = 0xFF //#d
};

enum MessageClasses : uint8_t {
	MESSAGE_STATUS_CONSOLE_BLUE		= 0x04, /*FIXME Blue message in the console*/
	MESSAGE_STATUS_CONSOLE_RED		= 0x0E, /*Red message in the console*/
	MESSAGE_STATUS_DEFAULT			= 0x11, /*White message at the bottom of the game window and in the console*/
	MESSAGE_STATUS_WARNING			= 0x12, /*Red message in game window and in the console*/
	MESSAGE_EVENT_ADVANCE			= 0x13, /*White message in game window and in the console*/
	MESSAGE_GAME_HIGHLIGHT			= 0x14,
	MESSAGE_STATUS_SMALL			= 0x15, /*White message at the bottom of the game window"*/
	MESSAGE_INFO_DESCR				= 0x16, /*Green message in game window and in the console*/
	MESSAGE_DAMAGE_DEALT			= 0x17,
	MESSAGE_DAMAGE_RECEIVED			= 0x18,
	MESSAGE_HEALED					= 0x19,
	MESSAGE_EXPERIENCE				= 0x1A,
	MESSAGE_DAMAGE_OTHERS			= 0x1B,
	MESSAGE_HEALED_OTHERS			= 0x1C,
	MESSAGE_EXPERIENCE_OTHERS		= 0x1D,
	MESSAGE_EVENT_DEFAULT			= 0x1E, /*White message at the bottom of the game window and in the console*/
	MESSAGE_LOOT					= 0x1F,
	MESSAGE_TRADE_NPC				= 0x20,
	MESSAGE_EVENT_GUILD				= 0x21,
	MESSAGE_PARTY_MANAGEMENT		= 0x22,
	MESSAGE_PARTY					= 0x23,
	MESSAGE_EVENT_ORANGE			= 0x24, /*Orange message in the console*/
	MESSAGE_STATUS_CONSOLE_ORANGE	= 0x25,  /*Orange message in the console*/
	MESSAGE_REPORT					= 0x26,
	MESSAGE_HOTKEY_USE				= 0x27,
	MESSAGE_TUTORIAL_HINT			= 0x28,
	MESSAGE_THANK_YOU				= 0x29,
	MESSAGE_MARKET					= 0x30,
	MESSAGE_BEYOND_LAST				= 0x31
};

enum FluidColors_t : uint8_t {
	FLUID_EMPTY = 0x00,
	FLUID_BLUE = 0x01,
	FLUID_RED = 0x02,
	FLUID_BROWN = 0x03,
	FLUID_GREEN = 0x04,
	FLUID_YELLOW = 0x05,
	FLUID_WHITE = 0x06,
	FLUID_PURPLE = 0x07
};

enum FluidTypes_t : uint8_t {
	FLUID_NONE = FLUID_EMPTY,
	FLUID_WATER = FLUID_BLUE,
	FLUID_BLOOD = FLUID_RED,
	FLUID_BEER = FLUID_BROWN,
	FLUID_SLIME = FLUID_GREEN,
	FLUID_LEMONADE = FLUID_YELLOW,
	FLUID_MILK = FLUID_WHITE,
	FLUID_MANA = FLUID_PURPLE,

	FLUID_LIFE = FLUID_RED + 8,
	FLUID_OIL = FLUID_BROWN + 8,
	FLUID_URINE = FLUID_YELLOW + 8,
	FLUID_COCONUTMILK = FLUID_WHITE + 8,
	FLUID_WINE = FLUID_PURPLE + 8,

	FLUID_MUD = FLUID_BROWN + 16,
	FLUID_FRUITJUICE = FLUID_YELLOW + 16,

	FLUID_LAVA = FLUID_RED + 24,
	FLUID_RUM = FLUID_BROWN + 24,
	FLUID_SWAMP = FLUID_GREEN + 24,

	FLUID_TEA = FLUID_BROWN + 32,
	FLUID_MEAD = FLUID_BROWN + 40
};

const uint8_t reverseFluidMap[] = {
	FLUID_EMPTY,
	FLUID_WATER,
	FLUID_MANA,
	FLUID_BEER,
	FLUID_EMPTY,
	FLUID_BLOOD,
	FLUID_SLIME,
	FLUID_EMPTY,
	FLUID_LEMONADE,
	FLUID_MILK
};

const uint8_t clientToServerFluidMap[] = {
	FLUID_EMPTY,
	FLUID_WATER,
	FLUID_MANA,
	FLUID_BEER,
	FLUID_MUD,
	FLUID_BLOOD,
	FLUID_SLIME,
	FLUID_RUM,
	FLUID_LEMONADE,
	FLUID_MILK,
	FLUID_WINE,
	FLUID_LIFE,
	FLUID_URINE,
	FLUID_OIL,
	FLUID_FRUITJUICE,
	FLUID_COCONUTMILK,
	FLUID_TEA,
	FLUID_MEAD
};

enum ClientFluidTypes_t : uint8_t {
	CLIENTFLUID_EMPTY	= 0x00,
	CLIENTFLUID_BLUE	= 0x01,
	CLIENTFLUID_PURPLE	= 0x02,
	CLIENTFLUID_BROWN_1	= 0x03,
	CLIENTFLUID_BROWN_2	= 0x04,
	CLIENTFLUID_RED		= 0x05,
	CLIENTFLUID_GREEN	= 0x06,
	CLIENTFLUID_BROWN	= 0x07,
	CLIENTFLUID_YELLOW	= 0x08,
	CLIENTFLUID_WHITE	= 0x09
};

const uint8_t fluidMap[] = {
	CLIENTFLUID_EMPTY,
	CLIENTFLUID_BLUE,
	CLIENTFLUID_RED,
	CLIENTFLUID_BROWN_1,
	CLIENTFLUID_GREEN,
	CLIENTFLUID_YELLOW,
	CLIENTFLUID_WHITE,
	CLIENTFLUID_PURPLE
};

enum SquareColor_t : uint8_t {
	SQ_COLOR_BLACK = 0
};

enum TextColor_t : uint8_t {
	TEXTCOLOR_BLUE = 5,
	TEXTCOLOR_LIGHTGREEN = 30,
	TEXTCOLOR_LIGHTBLUE = 35,
	TEXTCOLOR_MAYABLUE = 95,
	TEXTCOLOR_DARKRED = 108,
	TEXTCOLOR_LIGHTGREY = 129,
	TEXTCOLOR_SKYBLUE = 143,
	TEXTCOLOR_PURPLE = 154,
	TEXTCOLOR_RED = 180,
	TEXTCOLOR_ORANGE = 198,
	TEXTCOLOR_YELLOW = 210,
	TEXTCOLOR_WHITE_EXP = 215,
	TEXTCOLOR_NONE = 255
};

enum Icons_t {
	ICON_POISON = 1,
	ICON_BURN = 2,
	ICON_ENERGY =  4,
	ICON_DRUNK = 8,
	ICON_MANASHIELD = 16,
	ICON_PARALYZE = 32,
	ICON_HASTE = 64,
	ICON_SWORDS = 128,
	ICON_DROWNING = 256,
	ICON_FREEZING = 512,
	ICON_DAZZLED = 1024,
	ICON_CURSED = 2048,
	ICON_PARTY_BUFF = 4096,
	ICON_REDSWORDS = 8192,
	ICON_PIGEON = 16384,
	ICON_BLEEDING = 32768
};

enum WeaponType_t : uint8_t {
	WEAPON_NONE = 0,
	WEAPON_SWORD = 1,
	WEAPON_CLUB = 2,
	WEAPON_AXE = 3,
	WEAPON_SHIELD = 4,
	WEAPON_DISTANCE = 5,
	WEAPON_WAND = 6,
	WEAPON_AMMO = 7
};

enum Ammo_t : uint8_t {
	AMMO_NONE = 0,
	AMMO_BOLT = 1,
	AMMO_ARROW = 2,
	AMMO_SPEAR = 3,
	AMMO_THROWINGSTAR = 4,
	AMMO_THROWINGKNIFE = 5,
	AMMO_STONE = 6,
	AMMO_SNOWBALL = 7
};

enum WeaponAction_t : uint8_t {
	WEAPONACTION_NONE,
	WEAPONACTION_REMOVECOUNT,
	WEAPONACTION_REMOVECHARGE,
	WEAPONACTION_MOVE
};

enum WieldInfo_t {
	WIELDINFO_LEVEL = 1,
	WIELDINFO_MAGLV = 2,
	WIELDINFO_VOCREQ = 4,
	WIELDINFO_PREMIUM = 8
};

enum Skulls_t : uint8_t {
	SKULL_NONE = 0,
	SKULL_YELLOW = 1,
	SKULL_GREEN = 2,
	SKULL_WHITE = 3,
	SKULL_RED = 4,
	SKULL_BLACK = 5,
	SKULL_ORANGE = 6,
	SKULL_LAST = SKULL_ORANGE
};

enum PartyShields_t : uint8_t {
	SHIELD_NONE = 0,
	SHIELD_WHITEYELLOW = 1,
	SHIELD_WHITEBLUE = 2,
	SHIELD_BLUE = 3,
	SHIELD_YELLOW = 4,
	SHIELD_BLUE_SHAREDEXP = 5,
	SHIELD_YELLOW_SHAREDEXP = 6,
	SHIELD_BLUE_NOSHAREDEXP_BLINK = 7,
	SHIELD_YELLOW_NOSHAREDEXP_BLINK = 8,
	SHIELD_BLUE_NOSHAREDEXP = 9,
	SHIELD_YELLOW_NOSHAREDEXP = 10,
	SHIELD_GRAY = 11
};

enum GuildEmblems_t : uint8_t {
	GUILDEMBLEM_NONE = 0,
	GUILDEMBLEM_ALLY = 1,
	GUILDEMBLEM_ENEMY = 2,
	GUILDEMBLEM_NEUTRAL = 3,
	GUILDEMBLEM_MEMBER = 4,
	GUILDEMBLEM_OTHER = 5
};

enum item_t {
	ITEM_BROWSEFIELD = 460, // for internal use

	ITEM_FIREFIELD_PVP_FULL = 1487,
	ITEM_FIREFIELD_PVP_MEDIUM = 1488,
	ITEM_FIREFIELD_PVP_SMALL = 1489,
	ITEM_FIREFIELD_PERSISTENT_FULL = 1492,
	ITEM_FIREFIELD_PERSISTENT_MEDIUM = 1493,
	ITEM_FIREFIELD_PERSISTENT_SMALL = 1494,
	ITEM_FIREFIELD_NOPVP = 1500,

	ITEM_POISONFIELD_PVP = 1490,
	ITEM_POISONFIELD_PERSISTENT = 1496,
	ITEM_POISONFIELD_NOPVP = 1503,

	ITEM_ENERGYFIELD_PVP = 1491,
	ITEM_ENERGYFIELD_PERSISTENT = 1495,
	ITEM_ENERGYFIELD_NOPVP = 1504,

	ITEM_MAGICWALL = 1497,
	ITEM_MAGICWALL_PERSISTENT = 1498,
	ITEM_MAGICWALL_SAFE = 11098,

	ITEM_WILDGROWTH = 1499,
	ITEM_WILDGROWTH_PERSISTENT = 2721,
	ITEM_WILDGROWTH_SAFE = 11099,

	ITEM_BAG = 1987,

	ITEM_GOLD_COIN = 2148,
	ITEM_PLATINUM_COIN = 2152,
	ITEM_CRYSTAL_COIN = 2160,

	ITEM_DEPOT = 2594,
	ITEM_LOCKER1 = 2589,
	ITEM_INBOX = 14404,
	ITEM_MARKET = 14405,

	ITEM_MALE_CORPSE = 3058,
	ITEM_FEMALE_CORPSE = 3065,

	ITEM_FULLSPLASH = 2016,
	ITEM_SMALLSPLASH = 2019,

	ITEM_PARCEL = 2595,
	ITEM_LETTER = 2597,
	ITEM_LETTER_STAMPED = 2598,
	ITEM_LABEL = 2599,

	ITEM_AMULETOFLOSS = 2173,

	ITEM_DOCUMENT_RO = 1968 //read-only
};

enum PlayerFlags : uint64_t {
	PlayerFlag_CannotUseCombat = 1,
	PlayerFlag_CannotAttackPlayer = 2,
	PlayerFlag_CannotAttackMonster = 4,
	PlayerFlag_CannotBeAttacked = 8,
	PlayerFlag_CanConvinceAll = 16,
	PlayerFlag_CanSummonAll = 32,
	PlayerFlag_CanIllusionAll = 64,
	PlayerFlag_CanSenseInvisibility = 128,
	PlayerFlag_IgnoredByMonsters = 256,
	PlayerFlag_NotGainInFight = 512,
	PlayerFlag_HasInfiniteMana = 1024,
	PlayerFlag_HasInfiniteSoul = 2048,
	PlayerFlag_HasNoExhaustion = 4096,
	PlayerFlag_CannotUseSpells = 8192,
	PlayerFlag_CannotPickupItem = 16384,
	PlayerFlag_CanAlwaysLogin = 32768,
	PlayerFlag_CanBroadcast = 65536,
	PlayerFlag_CanEditHouses = 131072,
	PlayerFlag_CannotBeBanned = 262144,
	PlayerFlag_CannotBePushed = 524288,
	PlayerFlag_HasInfiniteCapacity = 1048576,
	PlayerFlag_CanPushAllCreatures = 2097152,
	PlayerFlag_CanTalkRedPrivate = 4194304,
	PlayerFlag_CanTalkRedChannel = 8388608,
	PlayerFlag_TalkOrangeHelpChannel = 16777216,
	PlayerFlag_NotGainExperience = 33554432,
	PlayerFlag_NotGainMana = 67108864,
	PlayerFlag_NotGainHealth = 134217728,
	PlayerFlag_NotGainSkill = 268435456,
	PlayerFlag_SetMaxSpeed = 536870912,
	PlayerFlag_SpecialVIP = 1073741824,
	PlayerFlag_NotGenerateLoot = 2147483648,
	PlayerFlag_CanTalkRedChannelAnonymous = 4294967296,
	PlayerFlag_IgnoreProtectionZone = 8589934592,
	PlayerFlag_IgnoreSpellCheck = 17179869184,
	PlayerFlag_IgnoreWeaponCheck = 34359738368,
	PlayerFlag_CannotBeMuted = 68719476736,
	PlayerFlag_IsAlwaysPremium = 137438953472
};

#define CHANNEL_GUILD 0x00
#define CHANNEL_PARTY 0x01
#define CHANNEL_TUTOR 0x02
#define CHANNEL_WORLDCHAT 0x03
#define CHANNEL_ENGLISHCHAT 0x04
#define CHANNEL_ADVERTISING 0x05
#define CHANNEL_ADVERTISINGROOKGAARD 0x06
#define CHANNEL_HELP 0x07
#define CHANNEL_GAMEMASTER 0x08
#define CHANNEL_PRIVATE 0xFFFF

//Reserved player storage key ranges
//[10000000 - 20000000]
#define PSTRG_RESERVED_RANGE_START  10000000
#define PSTRG_RESERVED_RANGE_SIZE   10000000
//[1000 - 1500]
#define PSTRG_OUTFITS_RANGE_START   (PSTRG_RESERVED_RANGE_START + 1000)
#define PSTRG_OUTFITS_RANGE_SIZE    500
//[2001 - 2011]
#define PSTRG_MOUNTS_RANGE_START   (PSTRG_RESERVED_RANGE_START + 2001)
#define PSTRG_MOUNTS_RANGE_SIZE    10
#define PSTRG_MOUNTS_CURRENTMOUNT (PSTRG_MOUNTS_RANGE_START + 10)

#define IS_IN_KEYRANGE(key, range) (key >= PSTRG_##range##_START && ((key - PSTRG_##range##_START) <= PSTRG_##range##_SIZE))

#endif
