#ifndef AZEROTHCORE_ENCOUNTERLOGDEFINES_H
#define AZEROTHCORE_ENCOUNTERLOGDEFINES_H

enum EncounterLogDebugValues
{
    ENCOUNTER_LOG_DEBUG_TYPE = 0,
    ENCOUNTER_LOG_DEBUG_RESULT = 255,
    ENCOUNTER_LOG_DEBUG_GUID = 123456789,
};

enum EncounterLogScope
{
    ENCOUNTER_LOG_SCOPE_DUNGEON = 1,
    ENCOUNTER_LOG_SCOPE_RAID = 2,
    ENCOUNTER_LOG_SCOPE_EVERYTHING = 3
};

enum EncounterLogState
{
    ENCOUNTER_LOG_STATE_START = 1,
    ENCOUNTER_LOG_STATE_END = 2,
};

enum EncounterLogUnitType
{
    ENCOUNTER_LOG_UNIT_EMPTY = 0,
    ENCOUNTER_LOG_UNIT_PLAYER = 1,
    ENCOUNTER_LOG_UNIT_CREATURE = 2,
    ENCOUNTER_LOG_UNIT_PET = 3,
    ENCOUNTER_LOG_UNIT_TOTEM = 4,
    ENCOUNTER_LOG_UNIT_SUMMON = 5,
    ENCOUNTER_LOG_UNIT_VEHICLE = 6,
    ENCOUNTER_LOG_UNIT_OBJECT = 7,
};

enum EncounterLogSpellResult
{
    ENCOUNTER_LOG_SPELL_RESULT_EMPTY = 0,
    ENCOUNTER_LOG_SPELL_RESULT_NONE = 1, // hit
    ENCOUNTER_LOG_SPELL_RESULT_MISS = 2,
    ENCOUNTER_LOG_SPELL_RESULT_RESIST = 3,
    ENCOUNTER_LOG_SPELL_RESULT_DODGE = 4,
    ENCOUNTER_LOG_SPELL_RESULT_PARRY = 5,
    ENCOUNTER_LOG_SPELL_RESULT_BLOCK = 6,
    ENCOUNTER_LOG_SPELL_RESULT_EVADE = 7,
    ENCOUNTER_LOG_SPELL_RESULT_IMMUNE = 8,
    ENCOUNTER_LOG_SPELL_RESULT_DEFLECT = 9,
    ENCOUNTER_LOG_SPELL_RESULT_ABSORB = 10,
    ENCOUNTER_LOG_SPELL_RESULT_REFLECT = 11,
    ENCOUNTER_LOG_SPELL_RESULT_CRIT = 12,
    ENCOUNTER_LOG_SPELL_RESULT_GLANCING = 13,
    ENCOUNTER_LOG_SPELL_RESULT_CRUSHING = 14,
};

enum EncounterLogSpellFlag
{
    ENCOUNTER_LOG_FLAG_EMPTY = 0,
    ENCOUNTER_LOG_FLAG_BASE_ATTACK = 1,
    ENCOUNTER_LOG_FLAG_OFF_ATTACK = 2,
    ENCOUNTER_LOG_FLAG_RANGED_ATTACK = 3,
    ENCOUNTER_LOG_FLAG_MAX_ATTACK = 4,
    ENCOUNTER_LOG_FLAG_POWER_MANA = 5,
    ENCOUNTER_LOG_FLAG_POWER_RAGE = 6,
    ENCOUNTER_LOG_FLAG_POWER_FOCUS = 7,
    ENCOUNTER_LOG_FLAG_POWER_ENERGY = 8,
    ENCOUNTER_LOG_FLAG_POWER_HAPPINESS = 9,
    ENCOUNTER_LOG_FLAG_POWER_RUNE = 10,
    ENCOUNTER_LOG_FLAG_POWER_RUNIC_POWER = 11,
    ENCOUNTER_LOG_FLAG_MAX_POWERS = 12,
    ENCOUNTER_LOG_FLAG_POWER_ALL = 13,
    ENCOUNTER_LOG_FLAG_POWER_HEALTH = 14,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_NONE = 15,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_NORMAL = 16,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_HOLY = 17,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_FIRE = 18,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_NATURE = 19,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_FROST = 20,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_SHADOW = 21,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_ARCANE = 22,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_SPELL = 23,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_MAGIC = 24,
    ENCOUNTER_LOG_FLAG_SPELL_SCHOOL_MASK_ALL = 25,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_NONE = 26,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_BIND_SIGHT = 27,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POSSESS = 28,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_DAMAGE = 29,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_DUMMY = 30,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CONFUSE = 31,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CHARM = 32,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FEAR = 33,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_HEAL = 34,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKSPEED = 35,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_THREAT = 36,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TAUNT = 37,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STUN = 38,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE = 39,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_TAKEN = 40,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_DAMAGE_SHIELD = 41,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STEALTH = 42,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STEALTH_DETECT = 43,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INVISIBILITY = 44,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INVISIBILITY_DETECT = 45,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_OBS_MOD_HEALTH = 46,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_OBS_MOD_POWER = 47,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE = 48,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_TRIGGER_SPELL = 49,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_ENERGIZE = 50,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PACIFY = 51,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ROOT = 52,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SILENCE = 53,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_REFLECT_SPELLS = 54,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STAT = 55,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SKILL = 56,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_SPEED = 57,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED = 58,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DECREASE_SPEED = 59,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_HEALTH = 60,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_ENERGY = 61,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SHAPESHIFT = 62,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_EFFECT_IMMUNITY = 63,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_STATE_IMMUNITY = 64,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SCHOOL_IMMUNITY = 65,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_DAMAGE_IMMUNITY = 66,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_DISPEL_IMMUNITY = 67,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PROC_TRIGGER_SPELL = 68,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PROC_TRIGGER_DAMAGE = 69,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_TRACK_CREATURES = 70,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_TRACK_RESOURCES = 71,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_46 = 72,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PARRY_PERCENT = 73,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_TRIGGER_SPELL_FROM_CLIENT = 74,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DODGE_PERCENT = 75,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT = 76,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BLOCK_PERCENT = 77,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_WEAPON_CRIT_PERCENT = 78,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_LEECH = 79,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HIT_CHANCE = 80,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_HIT_CHANCE = 81,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_TRANSFORM = 82,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_CRIT_CHANCE = 83,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_SWIM_SPEED = 84,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_CREATURE = 85,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PACIFY_SILENCE = 86,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SCALE = 87,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_HEALTH_FUNNEL = 88,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_63 = 89,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_MANA_LEECH = 90,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK = 91,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_FEIGN_DEATH = 92,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISARM = 93,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STALKED = 94,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SCHOOL_ABSORB = 95,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_EXTRA_ATTACKS = 96,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL = 97,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT = 98,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_COST_SCHOOL = 99,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_REFLECT_SPELLS_SCHOOL = 100,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_LANGUAGE = 101,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_FAR_SIGHT = 102,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_IMMUNITY = 103,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOUNTED = 104,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_PERCENT_DONE = 105,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PERCENT_STAT = 106,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SPLIT_DAMAGE_PCT = 107,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_WATER_BREATHING = 108,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BASE_RESISTANCE = 109,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_REGEN = 110,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_REGEN = 111,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_CHANNEL_DEATH_ITEM = 112,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN = 113,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALTH_REGEN_PERCENT = 114,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_DAMAGE_PERCENT = 115,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_90 = 116,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DETECT_RANGE = 117,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENTS_FLEEING = 118,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_UNATTACKABLE = 119,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_INTERRUPT_REGEN = 120,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_GHOST = 121,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SPELL_MAGNET = 122,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MANA_SHIELD = 123,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SKILL_TALENT = 124,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER = 125,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_AURAS_VISIBLE = 126,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE_PCT = 127,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS = 128,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TOTAL_THREAT = 129,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_WATER_WALK = 130,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_FEATHER_FALL = 131,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_HOVER = 132,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_FLAT_MODIFIER = 133,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_PCT_MODIFIER = 134,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_TARGET_TRIGGER = 135,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POWER_REGEN_PERCENT = 136,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ADD_CASTER_HIT_TRIGGER = 137,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_OVERRIDE_CLASS_SCRIPTS = 138,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN = 139,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT = 140,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING = 141,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_REGEN_DURING_COMBAT = 142,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MECHANIC_RESISTANCE = 143,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_PCT = 144,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_119 = 145,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_UNTRACKABLE = 146,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_EMPATHY = 147,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT = 148,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_RESISTANCE = 149,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER = 150,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN = 151,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT = 152,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS = 153,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_POSSESS_PET = 154,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPEED_ALWAYS = 155,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS = 156,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS = 157,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT = 158,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT = 159,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MANA_REGEN_INTERRUPT = 160,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_DONE = 161,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_DONE_PERCENT = 162,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE = 163,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_HASTE = 164,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_FORCE_REACTION = 165,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_HASTE = 166,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_AMMO_HASTE = 167,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BASE_RESISTANCE_PCT = 168,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE = 169,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SAFE_FALL = 170,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_PET_TALENT_POINTS = 171,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ALLOW_TAME_PET_TYPE = 172,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_IMMUNITY_MASK = 173,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_RETAIN_COMBO_POINTS = 174,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_REDUCE_PUSHBACK = 175,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT = 176,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_TRACK_STEALTHED = 177,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DETECTED_RANGE = 178,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SPLIT_DAMAGE_FLAT = 179,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_STEALTH_LEVEL = 180,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_WATER_BREATHING = 181,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_REPUTATION_GAIN = 182,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PET_DAMAGE_MULTI = 183,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SHIELD_BLOCKVALUE = 184,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_NO_PVP_CREDIT = 185,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AOE_AVOIDANCE = 186,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT = 187,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_POWER_BURN = 188,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_DAMAGE_BONUS = 189,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_164 = 190,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS = 191,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER_PCT = 192,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT = 193,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_VERSUS = 194,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_PERCENT_VERSUS = 195,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_DETECT_AMORE = 196,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPEED_NOT_STACK = 197,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK = 198,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_173 = 199,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT = 200,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT = 201,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SPIRIT_OF_REDEMPTION = 202,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_AOE_CHARM = 203,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DEBUFF_RESISTANCE = 204,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE = 205,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS = 206,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_181 = 207,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT = 208,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRITICAL_THREAT = 209,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE = 210,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE = 211,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE = 212,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE = 213,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE = 214,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RATING = 215,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FACTION_REPUTATION_GAIN = 216,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED = 217,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_RANGED_HASTE = 218,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MELEE_SLOW = 219,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_ABSORB_SCHOOL = 220,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_ABILITY_ABSORB_SCHOOL = 221,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_COOLDOWN = 222,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE = 223,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_198 = 224,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT = 225,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_XP_PCT = 226,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_FLY = 227,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORE_COMBAT_RESULT = 228,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE = 229,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE = 230,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SCHOOL_CRIT_DMG_TAKEN = 231,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED = 232,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED = 233,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED = 234,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS = 235,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS = 236,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK = 237,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT = 238,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT = 239,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_214 = 240,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ARENA_PREPARATION = 241,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_HASTE_SPELLS = 242,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MELEE_HASTE_2 = 243,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_HASTE_RANGED = 244,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MANA_REGEN_FROM_STAT = 245,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_RATING_FROM_STAT = 246,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORED = 247,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_222 = 248,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_RAID_PROC_FROM_CHARGE = 249,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_224 = 250,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_RAID_PROC_FROM_CHARGE_WITH_VALUE = 251,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_DUMMY = 252,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE = 253,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_DETECT_STEALTH = 254,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE = 255,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_230 = 256,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE = 257,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_DURATION_MOD = 258,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_CHANGE_MODEL_FOR_ALL_HUMANOIDS = 259,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK = 260,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISPEL_RESIST = 261,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_CONTROL_VEHICLE = 262,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER = 263,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER = 264,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SCALE_2 = 265,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_EXPERTISE = 266,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_FORCE_MOVE_FORWARD = 267,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING = 268,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FACTION = 269,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_COMPREHEND_LANGUAGE = 270,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL = 271,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL_NOT_STACK = 272,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_CLONE_CASTER = 273,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_COMBAT_RESULT_CHANCE = 274,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_CONVERT_RUNE = 275,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_INCREASE_HEALTH_2 = 276,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ENEMY_DODGE = 277,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_SPEED_SLOW_ALL = 278,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BLOCK_CRIT_CHANCE = 279,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISARM_OFFHAND = 280,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT = 281,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_NO_REAGENT_USE = 282,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS = 283,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_258 = 284,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HOT_PCT = 285,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SCREEN_EFFECT = 286,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PHASE = 287,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ABILITY_IGNORE_AURASTATE = 288,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ALLOW_ONLY_ABILITY = 289,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_264 = 290,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_265 = 291,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_266 = 292,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL = 293,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT = 294,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_IGNORE_TARGET_RESIST = 295,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ABILITY_IGNORE_TARGET_RESIST = 296,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_FROM_CASTER = 297,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORE_MELEE_RESET = 298,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_X_RAY = 299,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ABILITY_CONSUME_NO_AMMO = 300,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_IGNORE_SHAPESHIFT = 301,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_FOR_MECHANIC = 302,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MAX_AFFECTED_TARGETS = 303,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DISARM_RANGED = 304,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_INITIALIZE_IMAGES = 305,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ARMOR_PENETRATION_PCT = 306,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HONOR_GAIN_PCT = 307,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_BASE_HEALTH_PCT = 308,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_HEALING_RECEIVED = 309,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_LINKED = 310,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR = 311,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_ABILITY_PERIODIC_CRIT = 312,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_DEFLECT_SPELLS = 313,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_IGNORE_HIT_DIRECTION = 314,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENT_DURABILITY_LOSS = 315,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_PCT = 316,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_XP_QUEST_PCT = 317,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_OPEN_STABLE = 318,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_OVERRIDE_SPELLS = 319,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENT_REGENERATE_POWER = 320,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_295 = 321,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SET_VEHICLE_ID = 322,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_BLOCK_SPELL_FAMILY = 323,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_STRANGULATE = 324,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_299 = 325,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SHARE_DAMAGE_PCT = 326,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_SCHOOL_HEAL_ABSORB = 327,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_302 = 328,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_DAMAGE_DONE_VERSUS_AURASTATE = 329,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_FAKE_INEBRIATE = 330,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_MINIMUM_SPEED = 331,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_306 = 332,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_HEAL_ABSORB_TEST = 333,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CRIT_CHANCE_FOR_CASTER = 334,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_309 = 335,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_MOD_CREATURE_AOE_DAMAGE_AVOIDANCE = 336,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_311 = 337,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_312 = 338,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_313 = 339,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PREVENT_RESURRECTION = 340,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_UNDERWATER_WALKING = 341,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_PERIODIC_HASTE = 342,
    ENCOUNTER_LOG_FLAG_SPELL_AURA_TOTAL_AURAS = 343,
    ENCOUNTER_LOG_FLAG_DAMAGE_EXHAUSTED = 344,
    ENCOUNTER_LOG_FLAG_DAMAGE_DROWNING = 345,
    ENCOUNTER_LOG_FLAG_DAMAGE_FALL = 346,
    ENCOUNTER_LOG_FLAG_DAMAGE_LAVA = 347,
    ENCOUNTER_LOG_FLAG_DAMAGE_SLIME = 348,
    ENCOUNTER_LOG_FLAG_DAMAGE_FIRE = 349,
    ENCOUNTER_LOG_FLAG_DAMAGE_FALL_TO_VOID = 350,
};

enum EncounterLogArbitraryFlag
{
    ENCOUNTER_LOG_ARBITRARY_FLAG_EMPTY = 0,
    ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_APPLY = 1,
    ENCOUNTER_LOG_ARBITRARY_FLAG_AURA_REMOVE = 2,
    ENCOUNTER_LOG_ARBITRARY_FLAG_ENVIRONMENTAL = 3,
    ENCOUNTER_LOG_ARBITRARY_FLAG_PERIODICAL = 4,
    ENCOUNTER_LOG_ARBITRARY_FLAG_ENERGIZE = 5,
    ENCOUNTER_LOG_ARBITRARY_FLAG_MELEE = 6,
    ENCOUNTER_LOG_ARBITRARY_FLAG_DAMAGE_SHIELD = 7,
};

#endif //AZEROTHCORE_ENCOUNTERLOGDEFINES_H
