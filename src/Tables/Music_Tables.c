#include "../config.h"
#include "../../include/global.h"
#include "../../include/trainer_classes.h"
#include "../../include/songs.h"
#include "../../include/constants/species.h"

//Finish Wild Songs for Unbound

#ifndef UNBOUND

//Modify These

#ifdef ENCOUNTER_MUSIC_BY_CLASS
const u16 gClassBasedTrainerEncounterBGM[NUM_TRAINER_CLASSES] =
{
	[CLASS_YOUNGSTER] = BGM_EYE_BOY,
	[CLASS_BUG_CATCHER] = BGM_EYE_BOY,
	[CLASS_LASS] =  BGM_EYE_GIRL,
	[CLASS_SAILOR] = BGM_EYE_BOY,
	[CLASS_CAMPER] = BGM_EYE_BOY,
	[CLASS_PICNICKER] =  BGM_EYE_GIRL,
	[CLASS_POKEMANIAC] = BGM_EYE_CREEPY,
	[CLASS_SUPER_NERD] = BGM_EYE_CREEPY,
	[CLASS_HIKER] = BGM_EYE_BOY,
	[CLASS_BIKER] = BGM_EYE_BOY,
	[CLASS_BURGLAR] = BGM_EYE_CREEPY,
	[CLASS_ENGINEER] = BGM_EYE_BOY,
	[CLASS_FISHERMAN] = BGM_EYE_BOY,
	[CLASS_SWIMMER_M] = BGM_EYE_BOY,
	[CLASS_CUE_BALL] = BGM_EYE_BOY,
	[CLASS_GAMBLER] = BGM_EYE_BOY,
	[CLASS_BEAUTY] =  BGM_EYE_GIRL,
	[CLASS_SWIMMER_F] =  BGM_EYE_GIRL,
	[CLASS_PSYCHIC] = BGM_EYE_BOY,
	[CLASS_ROCKER] = BGM_EYE_BOY,
	[CLASS_JUGGLER] = BGM_EYE_BOY,
	[CLASS_TAMER] = BGM_EYE_BOY,
	[CLASS_BIRD_KEEPER] = BGM_EYE_BOY,
	[CLASS_BLACK_BELT] = BGM_EYE_BOY,
	[CLASS_RIVAL] = BGM_EYE_BOY,
	[CLASS_SCIENTIST] = BGM_EYE_BOY,
	[CLASS_BOSS] = BGM_EYE_BOY,
	[CLASS_LEADER] = BGM_EYE_BOY,
	[CLASS_TEAM_ROCKET] = BGM_EYE_CREEPY,
	[CLASS_COOLTRAINER] = BGM_EYE_BOY,
	[CLASS_ELITE_4] = BGM_EYE_BOY,
	[CLASS_GENTLEMAN] = BGM_EYE_BOY,
	[CLASS_RIVAL_2] = BGM_EYE_BOY,
	[CLASS_CHAMPION] = BGM_EYE_BOY,
	[CLASS_CHANNELER] = BGM_EYE_CREEPY,
	[CLASS_TWINS] =  BGM_EYE_GIRL,
	[CLASS_COOL_COUPLE] = BGM_EYE_BOY,
	[CLASS_YOUNG_COUPLE] = BGM_EYE_BOY,
	[CLASS_CRUSH_KIN] = BGM_EYE_BOY,
	[CLASS_SIS_AND_BRO] =  BGM_EYE_GIRL,
	[CLASS_PKMN_PROF] = BGM_EYE_BOY,
	[CLASS_PLAYER] = BGM_EYE_BOY,
	[CLASS_CRUSH_GIRL] =  BGM_EYE_GIRL,
	[CLASS_TUBER] = BGM_EYE_BOY,
	[CLASS_PKMN_BREEDER] = BGM_EYE_BOY,
	[CLASS_PKMN_RANGER] = BGM_EYE_BOY,
	[CLASS_AROMA_LADY] =  BGM_EYE_GIRL,
	[CLASS_RUIN_MANIAC] = BGM_EYE_BOY,
	[CLASS_LADY] =  BGM_EYE_GIRL,
	[CLASS_PAINTER] =  BGM_EYE_GIRL,
};
#endif

const u16 gClassBasedBattleBGM[NUM_TRAINER_CLASSES] =
{
	[CLASS_CHAMPION] = BGM_BATTLE_CHAMPION,
	[CLASS_LEADER] = BGM_BATTLE_GYM_LEADER,
	[CLASS_ELITE_4] = BGM_BATTLE_GYM_LEADER,
};

const u16 gWildSpeciesBasedBattleBGM[MAX_NUM_POKEMON] =
{
	[SPECIES_ARTICUNO] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_ZAPDOS] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_MOLTRES] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_MEWTWO] = BGM_BATTLE_MEWTWO,
	[SPECIES_MEW] = BGM_BATTLE_MEWTWO,
	[SPECIES_ENTEI] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_RAIKOU] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_SUICUNE] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_HOOH] = BGM_BATTLE_MEWTWO,
	[SPECIES_LUGIA] = BGM_BATTLE_MEWTWO,
	[SPECIES_CELEBI] = BGM_BATTLE_MEWTWO,
	[SPECIES_LATIOS] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_LATIAS] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_GROUDON] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_KYOGRE] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_RAYQUAZA] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_JIRACHI] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_DEOXYS] = BGM_BATTLE_DEOXYS,
};

#else //For Pokemon Unbound

const u16 gClassBasedTrainerEncounterBGM[NUM_TRAINER_CLASSES] =
{
	[CLASS_WAITRESS] = BGM_EYE_ARTIST,
	[CLASS_CYCLIST] = BGM_EYE_BIRD_KEEPER,
	[CLASS_NURSE] = BGM_EYE_AROMA_LADY_BEAUTY,
	[CLASS_TERROR_GRANBULL] = BGM_EYE_BLACK_BELT,
	[CLASS_CAMPING_DUO] = BGM_EYE_BOY,
	[CLASS_SKIIER] = BGM_EYE_BIRD_KEEPER,
	[CLASS_GUITARIST] = BGM_EYE_BLACK_BELT,
	[CLASS_KINDLER] = BGM_EYE_BIRD_KEEPER, 
	[CLASS_SHOCKER] = BGM_EYE_BLACK_BELT,
	[CLASS_BUG_MANIAC] = BGM_EYE_MYSTERIOUS,
	[CLASS_POLICEMAN] = BGM_EYE_BLACK_BELT,
	[CLASS_BLACK_FERROTHORN] = BGM_EYE_BLACK_BELT,
	[CLASS_SCHOOL_KID] = BGM_EYE_BOY,
	[CLASS_EXPERT] = BGM_EYE_ACE,
	[CLASS_RANCHER] = BGM_EYE_HIKER,
	[CLASS_JOGGER] = BGM_EYE_BIRD_KEEPER,
	[CLASS_DRAGON_TAMER] = BGM_EYE_BOY,
	[CLASS_NINJA_BOY] = BGM_EYE_BOY,
	[CLASS_BOARDER] = BGM_EYE_BIRD_KEEPER,
	[CLASS_COLLECTOR] = BGM_EYE_MYSTERIOUS,
	[CLASS_LOR]	= BGM_EYE_GALACTIC,

	[CLASS_YOUNGSTER] = BGM_EYE_BOY,
	[CLASS_BUG_CATCHER] = BGM_EYE_BOY,
	[CLASS_LASS] = BGM_EYE_GIRL,
	[CLASS_SAILOR] = BGM_EYE_SAILOR,
	[CLASS_CAMPER] = BGM_EYE_BOY,
	[CLASS_PICNICKER] = BGM_EYE_GIRL,
	[CLASS_POKEMANIAC] = BGM_EYE_MYSTERIOUS,
	[CLASS_SUPER_NERD] = BGM_EYE_MYSTERIOUS,
	[CLASS_HIKER] = BGM_EYE_HIKER,
	[CLASS_BIKER] = BGM_EYE_BLACK_BELT,
	[CLASS_BURGLAR] = BGM_EYE_MYSTERIOUS,
	[CLASS_WORKER] = BGM_EYE_ARTIST,
	[CLASS_FISHERMAN] = BGM_EYE_SAILOR,
	[CLASS_SWIMMER_M] = BGM_EYE_BIRD_KEEPER, 
	[CLASS_CUE_BALL] = BGM_EYE_BLACK_BELT,
	[CLASS_GAMBLER] = BGM_EYE_GAMBLER,
	[CLASS_BEAUTY] = BGM_EYE_AROMA_LADY_BEAUTY,
	[CLASS_SWIMMER_F] = BGM_EYE_AROMA_LADY_BEAUTY,
	[CLASS_PSYCHIC] = BGM_EYE_BLACK_BELT,
	[CLASS_ROCKER] = BGM_EYE_BLACK_BELT,
	[CLASS_JUGGLER] = BGM_EYE_MYSTERIOUS,
	[CLASS_TAMER] = BGM_EYE_ACE,
	[CLASS_BIRD_KEEPER] = BGM_EYE_BIRD_KEEPER, 
	[CLASS_BLACK_BELT] = BGM_EYE_BLACK_BELT,
	//[CLASS_RIVAL] = 
	[CLASS_SCIENTIST] = BGM_EYE_MYSTERIOUS,
	//[CLASS_BOSS] = 
	//[CLASS_LEADER] = 
	[CLASS_SHADOW] = BGM_EYE_NEO_PLASMA,
	[CLASS_ACE_TRAINER] = BGM_EYE_ACE,
	[CLASS_ELITE_4] = BGM_EYE_ELITE_4,
	[CLASS_GENTLEMAN] = BGM_EYE_GAMBLER,
	//[CLASS_RIVAL_2] = 
	//[CLASS_CHAMPION] = 
	[CLASS_CHANNELER] = BGM_EYE_MYSTERIOUS,
	[CLASS_TWINS] = BGM_EYE_TWINS,
	[CLASS_COOL_COUPLE] = BGM_EYE_ACE,
	[CLASS_YOUNG_COUPLE] = BGM_EYE_ARTIST,
	[CLASS_CRUSH_KIN] = BGM_EYE_BLACK_BELT,
	[CLASS_SIS_AND_BRO] = BGM_EYE_AROMA_LADY_BEAUTY,
	//[CLASS_SPECIES_PROF] = 
	//[CLASS_PLAYER] = 
	[CLASS_CRUSH_GIRL] = BGM_EYE_BLACK_BELT,
	[CLASS_TUBER] = BGM_EYE_TWINS,
	[CLASS_PKMN_BREEDER] = BGM_EYE_AROMA_LADY_BEAUTY, //Just for F?
	[CLASS_PKMN_RANGER] = BGM_EYE_ACE,
	[CLASS_AROMA_LADY] = BGM_EYE_AROMA_LADY_BEAUTY,
	[CLASS_RUIN_MANIAC] = BGM_EYE_HIKER,
	[CLASS_LADY] = BGM_EYE_AROMA_LADY_BEAUTY,
	[CLASS_PAINTER] = BGM_EYE_ARTIST,
};

const u16 gClassBasedBattleBGM[NUM_TRAINER_CLASSES] =
{
	[CLASS_RIVAL] = BGM_BATTLE_RIVAL,
	[CLASS_CHAMPION] = BGM_BATTLE_CHAMPION,
	[CLASS_LEADER] = BGM_BATTLE_GYM_LEADER,
	[CLASS_ELITE_4] = BGM_BATTLE_ELITE_4,
	//[CLASS_SHADOW] = BGM_BATTLE_PLASMA_GRUNT,
	[CLASS_SHADOW_ADMIN] = BGM_BATTLE_NEO_PLASMA_GRUNT,
	[CLASS_BOSS] = BGM_BATTLE_SHADOW_BOSS,
	[CLASS_LOR] = BGM_BATTLE_GALACTIC_GRUNT,
	[CLASS_LOR_ADMIN] = BGM_BATTLE_GALACTIC_ADMIN,
	[CLASS_LOR_LEADER] = BGM_BATTLE_LOR_BOSS,
	[CLASS_SUCCESSOR] = BGM_BATTLE_KALOS_GYM_LEADER,
	[CLASS_TERROR_GRANBULL] = BGM_BATTLE_TEAM_ROCKET_GRUNT,
	[CLASS_BLACK_FERROTHORN] = BGM_BATTLE_TEAM_ROCKET_GRUNT,
};

const u16 gWildSpeciesBasedBattleBGM[MAX_NUM_POKEMON] =
{
	[SPECIES_ARTICUNO] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_ZAPDOS] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_MOLTRES] = BGM_BATTLE_LEGENDARY_BIRDS,
	[SPECIES_MEWTWO] = BGM_BATTLE_MEWTWO,
	[SPECIES_MEW] = BGM_BATTLE_MEWTWO,
	[SPECIES_ENTEI] = BGM_BATTLE_ENTEI,
	[SPECIES_RAIKOU] = BGM_BATTLE_RAIKOU,
	[SPECIES_SUICUNE] = BGM_BATTLE_SUICUNE,
	[SPECIES_HOOH] = BGM_BATTLE_HOOH,
	[SPECIES_LUGIA] = BGM_BATTLE_LUGIA,
	[SPECIES_CELEBI] = BGM_BATTLE_MEWTWO,
	[SPECIES_LATIOS] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_LATIAS] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_GROUDON] = BGM_BATTLE_GROUDON_KYOGRE_RAYQUAZA,
	[SPECIES_KYOGRE] = BGM_BATTLE_GROUDON_KYOGRE_RAYQUAZA,
	[SPECIES_RAYQUAZA] = BGM_BATTLE_GROUDON_KYOGRE_RAYQUAZA,
	[SPECIES_JIRACHI] = BGM_BATTLE_RSE_GYM_LEADER,
	[SPECIES_DEOXYS] = BGM_BATTLE_DEOXYS,
	//TODO
};

#endif