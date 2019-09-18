#include "defines.h"
#include "defines_battle.h"
#include "../include/random.h"
#include "../include/constants/items.h"

#include "../include/new/battle_start_turn_start.h"
#include "../include/new/battle_util.h"
#include "../include/new/end_turn.h"
#include "../include/new/end_turn_battle_scripts.h"
#include "../include/new/form_change.h"
#include "../include/new/Helper_Functions.h"
#include "../include/new/switching.h"

enum EndTurnEffects
{
	ET_Order,
	ET_General_Counter_Decrement,
	ET_Rain,
	ET_Sun,
	ET_Sandstorm,
	ET_Hail,
	ET_Air_Current,
	ET_Fog,
	ET_Weather_Health_Abilities,
	ET_Future_Sight,
	ET_Wish,
	ET_Block_A,
	ET_Aqua_Ring,
	ET_Ingrain,
	ET_Leech_Seed,
	ET_Item_Effects2,
	ET_Poison,
	ET_Item_Effects3,
	ET_Toxic,
	ET_Item_Effects4,
	ET_Burn,
	ET_Item_Effects5,
	ET_Nightmare,
	ET_Item_Effects6,
	ET_Curse,
	ET_Item_Effects7,
	ET_Trap_Damage,
	ET_Item_Effects8,
	ET_Taunt_Timer,
	ET_Encore_Timer,
	ET_Disable_Timer,
	ET_Lock_On_Timer,
	ET_Charge_Timer,
	ET_Magnet_Rise_Timer,
	ET_Telekinesis_Timer,
	ET_Heal_Block_Timer,
	ET_Embargo_Timer,
	ET_Yawn,
	ET_Item_Effects9,
	ET_Perish_Song,
	ET_Roost,
	ET_Reflect,
	ET_Light_Screen,
	ET_Aurora_Veil,
	ET_Safeguard,
	ET_Mist,
	ET_Tailwind_Timer,
	ET_Lucky_Chant_Timer,
	ET_Rainbow_Timer,
	ET_Sea_Of_Fire_Timer,
	ET_Swamp_Timer,
	ET_Trick_Room_Timer,
	ET_Water_Sport_Timer,
	ET_Mud_Sport_Timer,
	ET_Wonder_Room_Timer,
	ET_Magic_Room_Timer,
	ET_Gravity_Timer,
	ET_Seeds,
	ET_Terrain_Timer,
	ET_Block_B,
	ET_Form_Change,
	ET_End
};

enum Block_A 
{
	ET_Sea_Of_Fire,
	ET_Grassy_Terrain,
	ET_Hydration_ShedSkin,
	ET_Item_Effects,
	ET_Healer
};

#define MAX_CASES_BLOCK_A 5

enum Block_B
{
	ET_Uproar,
	ET_SpeedBoost_Moody_BadDreams,
	ET_Orbz,
	ET_Harvest_Pickup,
};

#define MAX_CASES_BLOCK_B 4

#define TURNBASED_MAX_CASE ET_End

u8 TurnBasedEffects(void)
{
	int i, j;
	u8 effect = 0;
	
	if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
		return 0;

	gHitMarker |= (HITMARKER_GRUDGE | HITMARKER_x20);
	while (gBattleStruct->turnEffectsTracker <= TURNBASED_MAX_CASE)
	{
		u8 sideBank;
		gActiveBattler = gBankAttacker = gBankTarget = gBanksByTurnOrder[gBattleStruct->turnEffectsBank];
		
		switch (gBattleStruct->turnEffectsTracker) {
			case(ET_Order):
				for (i = 0; i < gBattlersCount; ++i)
				{
					gBanksByTurnOrder[i] = i;
				}
				for (i = 0; i < gBattlersCount - 1; ++i)
				{
					for (j = i + 1; j < gBattlersCount; ++j)
					{
						if (GetWhoStrikesFirst(gBanksByTurnOrder[i], gBanksByTurnOrder[j], TRUE))
							SwapTurnOrder(i, j);
					}
				}
				++gBattleStruct->turnEffectsTracker;
			__attribute__ ((fallthrough));
			
			case(ET_General_Counter_Decrement):
				for (i = 0; i < MAX_BATTLERS_COUNT; ++i) 
				{
					if(gNewBS->LaserFocusTimers[i])
						--gNewBS->LaserFocusTimers[i];
					
					if(gNewBS->ThroatChopTimers[i])
						--gNewBS->ThroatChopTimers[i];
						
					if(gNewBS->StompingTantrumTimers[i])
						--gNewBS->StompingTantrumTimers[i];
						
					if (gNewBS->StakeoutCounters[i])
						--gNewBS->StakeoutCounters[i];
						
					if (gNewBS->DestinyBondCounters[i])
						--gNewBS->DestinyBondCounters[i];
						
					gNewBS->synchronizeTarget[i] = 0;
					gBattleMons[i].status2 &= ~(STATUS2_FLINCHED);
				}

				//These should be cleared earlier on, but just in case they aren't
				gNewBS->PowderByte = 0;
				gNewBS->BeakBlastByte = 0;
				gNewBS->playedFocusPunchMessage = 0;
				gNewBS->playedShellTrapMessage = 0;
				gNewBS->CustapQuickClawIndicator = 0;
				gNewBS->activatedCustapQuickClaw = 0;
				gNewBS->criticalCapture = 0;
				gNewBS->devolveForgotMove = 0;
				
				if (gNewBS->RetaliateCounters[0])
					--gNewBS->RetaliateCounters[0];
					
				if (gNewBS->RetaliateCounters[1])
					--gNewBS->RetaliateCounters[1];
					
				if (gNewBS->IonDelugeTimer)
					--gNewBS->IonDelugeTimer;
					
				if (gNewBS->FairyLockTimer)
					--gNewBS->FairyLockTimer;

				if (gNewBS->EchoedVoiceCounter)
					--gNewBS->EchoedVoiceCounter;
					
				if (gNewBS->EchoedVoiceCounter == 0)
					gNewBS->EchoedVoiceDamageScale = 0;
					
				gSideAffecting[B_SIDE_PLAYER] &= ~(SIDE_STATUS_CRAFTY_SHIELD | SIDE_STATUS_MAT_BLOCK | SIDE_STATUS_QUICK_GUARD | SIDE_STATUS_WIDE_GUARD);
				gSideAffecting[B_SIDE_OPPONENT] &= ~(SIDE_STATUS_CRAFTY_SHIELD | SIDE_STATUS_MAT_BLOCK | SIDE_STATUS_QUICK_GUARD | SIDE_STATUS_WIDE_GUARD);
					
				gNewBS->NoMoreMovingThisTurn = 0;
				gNewBS->fusionFlareUsedPrior = FALSE;
				gNewBS->fusionBoltUsedPrior = FALSE;
				gNewBS->roundUsed = FALSE;
					
				++gBattleStruct->turnEffectsTracker;
			__attribute__ ((fallthrough));

			case(ET_Rain):
				if (gBattleWeather & WEATHER_RAIN_ANY)
				{
					if (!(gBattleWeather & WEATHER_RAIN_PERMANENT)
					&& --gWishFutureKnock->weatherDuration == 0)
					{
						gBattleWeather &= ~WEATHER_RAIN_ANY;
						gBattleCommunication[MULTISTRING_CHOOSER] = 2;
					}
					else if (gBattleWeather & WEATHER_RAIN_DOWNPOUR)
					{
						gBattleCommunication[MULTISTRING_CHOOSER] = 1;
					}
					else
					{
						gBattleCommunication[MULTISTRING_CHOOSER] = 0;
					}

					BattleScriptExecute(BattleScript_RainContinuesOrEnds);
					effect++;
				}
				gBattleStruct->turnEffectsBank = gBattlersCount;
				break;
			
			case(ET_Sun):
				if (gBattleWeather & WEATHER_SUN_ANY)
				{
					if (!(gBattleWeather & WEATHER_SUN_PERMANENT) 
					&& --gWishFutureKnock->weatherDuration == 0)
					{
						gBattleWeather &= ~WEATHER_SUN_ANY;
						gBattlescriptCurrInstr = BattleScript_SunlightFaded;
					}
					else
					{
						gBattlescriptCurrInstr = BattleScript_SunlightContinues;
					}
					BattleScriptExecute(gBattlescriptCurrInstr);
					effect++;
				}
				gBattleStruct->turnEffectsBank = gBattlersCount;
				break;
			
			case(ET_Sandstorm):
				if (gBattleWeather & WEATHER_SANDSTORM_ANY)
				{
					if (!(gBattleWeather & WEATHER_SANDSTORM_PERMANENT) 
					&& --gWishFutureKnock->weatherDuration == 0)
					{
						gBattleWeather &= ~WEATHER_SANDSTORM_ANY;
						gBattlescriptCurrInstr = BattleScript_SandStormHailEnds;
					}
					else
					{
						gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
					}

					gBattleScripting->animArg1 = B_ANIM_SANDSTORM_CONTINUES;
					gBattleCommunication[MULTISTRING_CHOOSER] = 0;
					BattleScriptExecute(gBattlescriptCurrInstr);
					effect++;
				}
				gBattleStruct->turnEffectsBank = gBattlersCount;
				break;
			
			case(ET_Hail):
				if (gBattleWeather & WEATHER_HAIL_ANY)
				{
					if (!(gBattleWeather & WEATHER_HAIL_PERMANENT)
					&& --gWishFutureKnock->weatherDuration == 0)
					{
						gBattleWeather &= ~WEATHER_HAIL_ANY;
						gBattlescriptCurrInstr = BattleScript_SandStormHailEnds;
					}
					else
					{
						gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
					}

					gBattleScripting->animArg1 = B_ANIM_HAIL_CONTINUES;
					gBattleCommunication[MULTISTRING_CHOOSER] = 1;
					BattleScriptExecute(gBattlescriptCurrInstr);
					effect++;
				}
				gBattleStruct->turnEffectsBank = gBattlersCount;
				break;
			
			case(ET_Air_Current):
				if (gBattleWeather & WEATHER_AIR_CURRENT_PRIMAL)
				{
					BattleScriptExecute(BattleScript_MysteriousAirCurrentContinues);
					effect++;
				}
				gBattleStruct->turnEffectsBank = gBattlersCount;
				break;
			
			case(ET_Fog):
				if (gBattleWeather & WEATHER_FOG_ANY)
				{
					if (!(gBattleWeather & WEATHER_FOG_PERMANENT) 
					&& --gWishFutureKnock->weatherDuration == 0)
					{
						gBattleWeather &= ~WEATHER_FOG_ANY;
						gBattlescriptCurrInstr = BattleScript_FogEnded;
					}
					else
					{
						gBattlescriptCurrInstr = BattleScript_FogContinues;
					}
					BattleScriptExecute(gBattlescriptCurrInstr);
					effect++;
				}
				gBattleStruct->turnEffectsBank = gBattlersCount;
				break;

			case(ET_Weather_Health_Abilities):
				if (gBattleMons[gActiveBattler].hp) 
				{
					gLastUsedAbility = ABILITY(gActiveBattler);
					switch(gLastUsedAbility) {
						case ABILITY_RAINDISH:
						case ABILITY_DRYSKIN:
						case ABILITY_ICEBODY:
						case ABILITY_SOLARPOWER:
							if (AbilityBattleEffects(ABILITYEFFECT_ENDTURN, gActiveBattler, 0, 0, 0))
								effect++;
							break;
						case ABILITY_FORECAST:
							if (AbilityBattleEffects(ABILITYEFFECT_ON_SWITCHIN, gActiveBattler, 0, 0, 0))
								effect++;
					}
				}
				break;
			
			case(ET_Future_Sight):
				if (gWishFutureKnock->futureSightCounter[gActiveBattler] 
				&& --gWishFutureKnock->futureSightCounter[gActiveBattler] == 0 
				&& gBattleMons[gActiveBattler].hp) 
				{
					if (gWishFutureKnock->futureSightMove[gActiveBattler] == MOVE_FUTURESIGHT)
						gBattleCommunication[MULTISTRING_CHOOSER] = 0;
					else //Doom Desire
						gBattleCommunication[MULTISTRING_CHOOSER] = 1;
						
					gCurrentMove = gWishFutureKnock->futureSightMove[gActiveBattler];
					
					gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
					gBattleTextBuff1[1] = B_TXT_COPY_VAR_1;
					gBattleTextBuff1[2] = gWishFutureKnock->futureSightMove[gActiveBattler];
					gBattleTextBuff1[3] = gWishFutureKnock->futureSightMove[gActiveBattler] >> 8;
					gBattleTextBuff1[4] = 0xFF;
					gBankAttacker = gWishFutureKnock->futureSightAttacker[gActiveBattler];
					gSpecialStatuses[gBankTarget].moveturnLostHP = 0xFFFF;
					BattleScriptExecute(BattleScript_MonTookFutureAttack);
					effect++;
				}
				break;
	
			case(ET_Wish):
				if(gNewBS->ElectrifyTimers[gActiveBattler]) //Cleared down here because necessary for Future Sight
					--gNewBS->ElectrifyTimers[gActiveBattler]; 
				
				if (gWishFutureKnock->wishCounter[gActiveBattler] 
				&& --gWishFutureKnock->wishCounter[gActiveBattler] == 0 
				&& gBattleMons[gActiveBattler].hp) 
				{
					BattleScriptExecute(BattleScript_WishComesTrue);
					effect++;
				}
				gNewBS->blockTracker = 0; //For later
				break;
				
			case(ET_Block_A):
				switch(gNewBS->blockTracker) {
					case(ET_Sea_Of_Fire):
						if (BATTLER_ALIVE(gActiveBattler)
						&&  BankSideHasSeaOfFire(gActiveBattler)
						&&	ABILITY(gActiveBattler) != ABILITY_MAGICGUARD
						&&	!IsOfType(gActiveBattler, TYPE_FIRE))
						{
							gBattleMoveDamage = GetSeaOfFireDamage(gActiveBattler);
							BattleScriptExecute(BattleScript_SeaOfFireDamage);
							effect++;
						}
						break;
						
					case(ET_Grassy_Terrain):
						if (TerrainType == GRASSY_TERRAIN && CheckGrounding(gActiveBattler)
						&&  gBattleMons[gActiveBattler].hp != 0
						&&  gBattleMons[gActiveBattler].hp < gBattleMons[gActiveBattler].maxHP
						&& !IsHealBlocked(gActiveBattler)) 
						{
							BattleScriptExecute(BattleScript_GrassyTerrainHeal);
							effect++;
						}
						break;
						
					case(ET_Item_Effects):
						if (gBattleMons[gActiveBattler].hp)
						{
							if (ItemBattleEffects(ItemEffects_EndTurn, gActiveBattler, FALSE, FALSE))
								effect++;
						}
						break;
						
					case(ET_Hydration_ShedSkin):
						if (gBattleMons[gActiveBattler].hp)
						{
							switch(ABILITY(gActiveBattler)) {
								case ABILITY_SHEDSKIN:
								case ABILITY_HYDRATION:
									if (AbilityBattleEffects(ABILITYEFFECT_ENDTURN, gActiveBattler, 0, 0, 0))
										effect++;
							}
						}
						break;
						
					case(ET_Healer):
						if (gBattleMons[gActiveBattler].hp)
						{
							switch(ABILITY(gActiveBattler)) {
								case ABILITY_HEALER:
									if (AbilityBattleEffects(ABILITYEFFECT_ENDTURN, gActiveBattler, 0, 0, 0))
										effect++;
							}
						}
				}
				
				++gNewBS->blockTracker;
				if (gNewBS->blockTracker < MAX_CASES_BLOCK_A)
					goto SkipBankIncrement;
				
				gNewBS->blockTracker = 0;
				break;
					
			case(ET_Aqua_Ring):
				if (gStatuses3[gActiveBattler] & STATUS3_AQUA_RING
				&& gBattleMons[gActiveBattler].hp != 0
				&& gBattleMons[gActiveBattler].hp < gBattleMons[gActiveBattler].maxHP
				&& !IsHealBlocked(gActiveBattler))
				{	 
					gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
					if (ITEM_EFFECT(gActiveBattler) == ITEM_EFFECT_BIG_ROOT)
						gBattleMoveDamage = (gBattleMoveDamage * 130) / 100;
					if (gBattleMoveDamage == 0)
						gBattleMoveDamage = 1;
					
					gBattleMoveDamage *= -1;
					BattleScriptExecute(BattleScript_AquaRing);
					effect++;
				}
				break;
				
			case(ET_Ingrain):
				if (gStatuses3[gActiveBattler] & STATUS3_ROOTED
				&& gBattleMons[gActiveBattler].hp != 0
				&& gBattleMons[gActiveBattler].hp < gBattleMons[gActiveBattler].maxHP
				&& !IsHealBlocked(gActiveBattler))
				{	 
					gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
					if (ITEM_EFFECT(gActiveBattler) == ITEM_EFFECT_BIG_ROOT)
						gBattleMoveDamage = (gBattleMoveDamage * 130) / 100;
					if (gBattleMoveDamage == 0)
						gBattleMoveDamage = 1;
					
					gBattleMoveDamage *= -1;
					BattleScriptExecute(BattleScript_IngrainTurnHeal);
					effect++;
				}
				break;
				
			case(ET_Leech_Seed):
				if (gStatuses3[gActiveBattler] & STATUS3_LEECHSEED
				&& gBattleMons[gActiveBattler].hp != 0
				&& ABILITY(gActiveBattler) != ABILITY_MAGICGUARD
				&& gBattleMons[gStatuses3[gActiveBattler] & STATUS3_LEECHSEED_BATTLER].hp != 0) 
				{	
					gBankTarget = gStatuses3[gActiveBattler] & STATUS3_LEECHSEED_BATTLER; //funny how the 'target' is actually the bank that receives HP
					gBattleMoveDamage = GetLeechSeedDamage(gActiveBattler);
					gBattleScripting->animArg1 = gBankTarget;
					gBattleScripting->animArg2 = gBankAttacker;
					BattleScriptExecute(BattleScript_LeechSeedTurnDrain);
					effect++;
				}
				break;
			
			//One item effect checked is done after each time the Pokemon receives damage
			case ET_Item_Effects2:
			case ET_Item_Effects3:
			case ET_Item_Effects4:
			case ET_Item_Effects5:
			case ET_Item_Effects6:
			case ET_Item_Effects7:
			case ET_Item_Effects8:
			case ET_Item_Effects9:
				if (BATTLER_ALIVE(gActiveBattler))
				{
					if (ItemBattleEffects(ItemEffects_EndTurn, gActiveBattler, FALSE, FALSE))
						effect++;
				}
				break;
			
			case(ET_Poison):
				if (gBattleMons[gActiveBattler].status1 & STATUS_POISON
				&& gBattleMons[gActiveBattler].hp != 0
				&& ABILITY(gActiveBattler) != ABILITY_MAGICGUARD) 
				{
					gBattleMoveDamage = GetPoisonDamage(gActiveBattler);
					
					if (ABILITY(gActiveBattler) == ABILITY_POISONHEAL) 
					{
						if (!BATTLER_MAX_HP(gActiveBattler) && !IsHealBlocked(gActiveBattler))
						{
							gBattleMoveDamage *= -1;
							gBattleScripting->bank = gActiveBattler;
							BattleScriptExecute(BattleScript_PoisonHeal);
						}
					}
					else
						BattleScriptExecute(BattleScript_PoisonTurnDmg);
					++effect;
				}
				break;
				
			case(ET_Toxic):
				if (gBattleMons[gActiveBattler].status1 & STATUS_TOXIC_POISON
				&& gBattleMons[gActiveBattler].hp != 0
				&& ABILITY(gActiveBattler) != ABILITY_MAGICGUARD) 
				{
					if ((gBattleMons[gActiveBattler].status1 & 0xF00) != 0xF00) //not 16 turns
						gBattleMons[gActiveBattler].status1 += 0x100;
					
					gBattleMoveDamage = GetPoisonDamage(gActiveBattler);
						
					if (ABILITY(gActiveBattler) == ABILITY_POISONHEAL) 
					{
						if (!BATTLER_MAX_HP(gActiveBattler) && !IsHealBlocked(gActiveBattler))
						{
							gBattleMoveDamage *= -1;
							gBattleScripting->bank = gActiveBattler;
							BattleScriptExecute(BattleScript_PoisonHeal);
						}
					}
					else
						BattleScriptExecute(BattleScript_PoisonTurnDmg);
					effect++;
				}
				break;
				
			case(ET_Burn):
				if (gBattleMons[gActiveBattler].status1 & STATUS_BURN
				&& gBattleMons[gActiveBattler].hp != 0
				&& ABILITY(gActiveBattler) != ABILITY_MAGICGUARD) 
				{
					gBattleMoveDamage = GetBurnDamage(gActiveBattler);
					
					BattleScriptExecute(BattleScript_BurnTurnDmg);
					effect++;
				}
				break;
				
			case(ET_Nightmare):
				if (gBattleMons[gActiveBattler].status2 & STATUS2_NIGHTMARE)
				{
					if (gBattleMons[gActiveBattler].status1 & STATUS_SLEEP)
					{
						if (gBattleMons[gActiveBattler].hp != 0
						&&  ABILITY(gActiveBattler) != ABILITY_MAGICGUARD)
						{
							gBattleMoveDamage = GetNightmareDamage(gActiveBattler);
							BattleScriptExecute(BattleScript_NightmareTurnDmg);
							effect++;
						}
					}
					else
						gBattleMons[gActiveBattler].status2 &= ~STATUS2_NIGHTMARE;
				}
				break;
				
			case(ET_Curse):
				if (gBattleMons[gActiveBattler].status2 & STATUS2_CURSED
				&&  gBattleMons[gActiveBattler].hp != 0
				&&  ABILITY(gActiveBattler) != ABILITY_MAGICGUARD)
				{
					gBattleMoveDamage = GetCurseDamage(gActiveBattler);
					BattleScriptExecute(BattleScript_CurseTurnDmg);
					effect++;
				}
				break;
				
			case(ET_Trap_Damage):
				if (gNewBS->brokeFreeMessage & gBitTable[gActiveBattler]
				&& gBattleMons[gActiveBattler].hp != 0) 
				{
					//Broke free
					gBattleMons[gActiveBattler].status2 &= ~(STATUS2_WRAPPED);
					gNewBS->brokeFreeMessage &= ~(gBitTable[gActiveBattler]);
					
					gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
					gBattleTextBuff1[1] = B_TXT_COPY_VAR_1;
					gBattleTextBuff1[2] = gBattleStruct->wrappedMove[gActiveBattler];
					gBattleTextBuff1[3] = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
					gBattleTextBuff1[4] = EOS;
					gBattlescriptCurrInstr = BattleScript_WrapEnds;
					BattleScriptExecute(gBattlescriptCurrInstr);
					effect++;
				}
				else if ((gBattleMons[gActiveBattler].status2 & STATUS2_WRAPPED)
				&& gBattleMons[gActiveBattler].hp) 
				{
					gBattleMons[gActiveBattler].status2 -= 0x2000;
					
					if (ABILITY(gActiveBattler) != ABILITY_MAGICGUARD)
					{
						//Damaged by wrap
						gBattleScripting->animArg1 = gBattleStruct->wrappedMove[gActiveBattler];
						gBattleScripting->animArg2 = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
						gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
						gBattleTextBuff1[1] = B_TXT_COPY_VAR_1;
						gBattleTextBuff1[2] = gBattleStruct->wrappedMove[gActiveBattler];
						gBattleTextBuff1[3] = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
						gBattleTextBuff1[4] = EOS;
						gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
						
						gBattleMoveDamage = GetTrapDamage(gActiveBattler);

						BattleScriptExecute(gBattlescriptCurrInstr);
						effect++;
					}
					
					if (!(gBattleMons[gActiveBattler].status2 & STATUS2_WRAPPED))
					{
						gBattleMons[gActiveBattler].status2 |= STATUS2_WRAPPED; //Reactivate temporarily
						gNewBS->brokeFreeMessage |= gBitTable[gActiveBattler]; //Will play next turn
					}
				}
				break;
				
			case(ET_Taunt_Timer):
				if (gDisableStructs[gActiveBattler].tauntTimer > 0 && --gDisableStructs[gActiveBattler].tauntTimer == 0)
				{
					gBattleScripting->bank = gActiveBattler;
					BattleStringLoader = gText_TauntWoreOff;
					BattleScriptExecute(BattleScript_PrintCustomStringEnd2);
					effect++;
				}
				break;
				
			case(ET_Encore_Timer):
				if (gDisableStructs[gActiveBattler].encoreTimer && gBattleMons[gActiveBattler].hp != 0) 
				{
					if (gBattleMons[gActiveBattler].moves[gDisableStructs[gActiveBattler].encoredMovePos] != gDisableStructs[gActiveBattler].encoredMove)
					{  // pokemon does not have the encored move anymore
						gDisableStructs[gActiveBattler].encoredMove = 0;
						gDisableStructs[gActiveBattler].encoreTimer = 0;
					}
					else if (--gDisableStructs[gActiveBattler].encoreTimer == 0
						  || gBattleMons[gActiveBattler].pp[gDisableStructs[gActiveBattler].encoredMovePos] == 0) 
					{
						gDisableStructs[gActiveBattler].encoredMove = 0;
						gDisableStructs[gActiveBattler].encoreTimer = 0;
						BattleScriptExecute(BattleScript_EncoredNoMore);
						effect++;
					}
				}
				break;
				
			case(ET_Disable_Timer):
				if (gDisableStructs[gActiveBattler].disableTimer1 && gBattleMons[gActiveBattler].hp)
				{
					int movenum;
					
					for (movenum = 0; movenum < 4; movenum++)
					{
						if (gDisableStructs[gActiveBattler].disabledMove == gBattleMons[gActiveBattler].moves[movenum])
							break;
					}
					
					if (movenum == 4)
					{ // pokemon does not have the disabled move anymore
						gDisableStructs[gActiveBattler].disabledMove = 0;
						gDisableStructs[gActiveBattler].disableTimer1 = 0;
					}
					else if (--gDisableStructs[gActiveBattler].disableTimer1 == 0)
					{  // disable ends
						gDisableStructs[gActiveBattler].disabledMove = 0;
						BattleScriptExecute(BattleScript_DisabledNoMore);
						effect++;
					}
				}
				break;
			
			case(ET_Lock_On_Timer):
				if (gStatuses3[gActiveBattler] & STATUS3_LOCKON)
					gStatuses3[gActiveBattler] -= 0x8;
				break;
				
			case(ET_Charge_Timer):
				if (gDisableStructs[gActiveBattler].chargeTimer && --gDisableStructs[gActiveBattler].chargeTimer == 0)
					gStatuses3[gActiveBattler] &= ~STATUS3_CHARGED_UP;
				break;
				
			case(ET_Magnet_Rise_Timer):
				if (gNewBS->MagnetRiseTimers[gActiveBattler] > 0
				&& BATTLER_ALIVE(gActiveBattler)
				&& --gNewBS->MagnetRiseTimers[gActiveBattler] == 0)
				{
					BattleScriptExecute(BattleScript_MagnetRiseEnd);
					effect++;
				}
				break;
					
			case(ET_Telekinesis_Timer):
				if (gNewBS->TelekinesisTimers[gActiveBattler] > 0
				&& BATTLER_ALIVE(gActiveBattler)
				&& --gNewBS->TelekinesisTimers[gActiveBattler] == 0)
				{
					BattleScriptExecute(BattleScript_TelekinesisEnd);
					effect++;
				}
				break;
					
			case(ET_Heal_Block_Timer):
				if (gNewBS->HealBlockTimers[gActiveBattler] > 0
				&& BATTLER_ALIVE(gActiveBattler)
				&& --gNewBS->HealBlockTimers[gActiveBattler] == 0)
				{
					BattleScriptExecute(BattleScript_HealBlockEnd);
					effect++;
				}
				break;
					
			case(ET_Embargo_Timer):
				if (gNewBS->EmbargoTimers[gActiveBattler] > 0
				&& BATTLER_ALIVE(gActiveBattler)
				&& --gNewBS->EmbargoTimers[gActiveBattler] == 0)
				{
					BattleScriptExecute(BattleScript_EmbargoEnd);
					effect++;
				}
				break;
					
			case(ET_Yawn):
				if (gStatuses3[gActiveBattler] & STATUS3_YAWN && BATTLER_ALIVE(gActiveBattler))
				{
					gStatuses3[gActiveBattler] -= 0x800;
					
					if (!(gStatuses3[gActiveBattler] & STATUS3_YAWN) && CanBePutToSleep(gActiveBattler, FALSE))  
					{
						CancelMultiTurnMoves(gActiveBattler);
						gBattleMons[gActiveBattler].status1 |= (Random() & 3) + 2;
						EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
						MarkBufferBankForExecution(gActiveBattler);
						gEffectBank = gActiveBattler;
						BattleScriptExecute(BattleScript_YawnMakesAsleep);
						effect++;
					}
				}
				break;
			
			case(ET_Perish_Song):
				if (gStatuses3[gActiveBattler] & STATUS3_PERISH_SONG && gBattleMons[gActiveBattler].hp != 0)
				{
					gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
					gBattleTextBuff1[1] = B_TXT_BUFF2;
					gBattleTextBuff1[2] = 1;
					gBattleTextBuff1[3] = 1;
					gBattleTextBuff1[4] = gDisableStructs[gActiveBattler].perishSongTimer;
					gBattleTextBuff1[5] = 0xFF;
					
					if (gDisableStructs[gActiveBattler].perishSongTimer == 0)
					{
						gStatuses3[gActiveBattler] &= ~(STATUS3_PERISH_SONG);
						gBattleMoveDamage = gBattleMons[gActiveBattler].hp;
						gBattlescriptCurrInstr = BattleScript_PerishSongHits;
					}
					else
					{
						gDisableStructs[gActiveBattler].perishSongTimer--;
						gBattlescriptCurrInstr = BattleScript_PerishSongTimerGoesDown;
					}
					
					BattleScriptExecute(gBattlescriptCurrInstr);
					effect++;
				}
				break;
			
			case(ET_Roost):
				if (gNewBS->RoostCounter & gBitTable[gActiveBattler])
				{
					gNewBS->RoostCounter &= ~(gBitTable[gActiveBattler]);
					if (gBattleMons[gActiveBattler].type1 == TYPE_NORMAL)
						gBattleMons[gActiveBattler].type1 = TYPE_FLYING;
					if (gBattleMons[gActiveBattler].type2 == TYPE_NORMAL)
						gBattleMons[gActiveBattler].type2 = TYPE_FLYING;
					if (gBattleMons[gActiveBattler].type3 == TYPE_ROOSTLESS)
						gBattleMons[gActiveBattler].type3 = TYPE_FLYING;
				}
				else 
				{
					if (gBattleMons[gActiveBattler].type1 == TYPE_ROOSTLESS)
						gBattleMons[gActiveBattler].type1 = TYPE_FLYING;
					if (gBattleMons[gActiveBattler].type2 == TYPE_ROOSTLESS)
						gBattleMons[gActiveBattler].type2 = TYPE_FLYING;
					if (gBattleMons[gActiveBattler].type3 == TYPE_ROOSTLESS)
						gBattleMons[gActiveBattler].type3 = TYPE_FLYING;
				}
				break;

//These Timers all fall through to eachother for quicker game speed
			case(ET_Reflect): 
				if (gBattleStruct->turnEffectsBank < 2)
				{
					sideBank = gBattleStruct->turnEffectsBank;
					if (gSideAffecting[sideBank] & SIDE_STATUS_REFLECT && --gSideTimers[sideBank].reflectTimer == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = sideBank;
						gSideAffecting[sideBank] &= ~SIDE_STATUS_REFLECT;
						BattleStringLoader = gText_SideStatusWoreOff;
						BattleScriptExecute(BattleScript_PrintCustomStringEnd2);
						gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
						gBattleTextBuff1[1] = B_TXT_COPY_VAR_1;
						gBattleTextBuff1[2] = MOVE_REFLECT;
						gBattleTextBuff1[3] = MOVE_REFLECT >> 8;
						gBattleTextBuff1[4] = EOS;
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Light_Screen):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					sideBank = gBattleStruct->turnEffectsBank;
					if (gSideAffecting[sideBank] & SIDE_STATUS_LIGHTSCREEN && --gSideTimers[sideBank].lightscreenTimer == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = sideBank;
						gSideAffecting[sideBank] &= ~SIDE_STATUS_LIGHTSCREEN;
						BattleStringLoader = gText_SideStatusWoreOff;
						BattleScriptExecute(BattleScript_PrintCustomStringEnd2);
						gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
						gBattleTextBuff1[1] = B_TXT_COPY_VAR_1;
						gBattleTextBuff1[2] = MOVE_LIGHTSCREEN;
						gBattleTextBuff1[3] = MOVE_LIGHTSCREEN >> 8;
						gBattleTextBuff1[4] = EOS;
						effect++;
					}
					break;
				}
				else

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Aurora_Veil):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					if (gNewBS->AuroraVeilTimers[gBattleStruct->turnEffectsBank] 
					&& --gNewBS->AuroraVeilTimers[gBattleStruct->turnEffectsBank] == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = gBattleStruct->turnEffectsBank;
						BattleScriptExecute(BattleScript_AuroraVeilEnd);
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Safeguard):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					sideBank = gBattleStruct->turnEffectsBank;
					if (gSideAffecting[sideBank] & SIDE_STATUS_SAFEGUARD && --gSideTimers[sideBank].safeguardTimer == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = sideBank;
						gSideAffecting[sideBank] &= ~SIDE_STATUS_SAFEGUARD;
						BattleScriptExecute(BattleScript_SafeguardEnds);
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Mist):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					sideBank = gBattleStruct->turnEffectsBank;
					if ((gSideAffecting[sideBank] & SIDE_STATUS_MIST) && --gSideTimers[sideBank].mistTimer == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = sideBank;
						gSideAffecting[sideBank] &= ~SIDE_STATUS_MIST;
						BattleStringLoader = gText_SideStatusWoreOff;
						BattleScriptExecute(BattleScript_PrintCustomStringEnd2);
						gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
						gBattleTextBuff1[1] = B_TXT_COPY_VAR_1;
						gBattleTextBuff1[2] = MOVE_MIST;
						gBattleTextBuff1[3] = MOVE_MIST >> 8;
						gBattleTextBuff1[4] = EOS;
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Tailwind_Timer):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					if (gNewBS->TailwindTimers[gBattleStruct->turnEffectsBank]
					&& --gNewBS->TailwindTimers[gBattleStruct->turnEffectsBank] == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = gBattleStruct->turnEffectsBank;
						BattleScriptExecute(BattleScript_TailwindEnd);
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Lucky_Chant_Timer):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					if (gNewBS->LuckyChantTimers[gBattleStruct->turnEffectsBank]
					&& --gNewBS->LuckyChantTimers[gBattleStruct->turnEffectsBank] == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = gBattleStruct->turnEffectsBank;
						BattleScriptExecute(BattleScript_LuckyChantEnd);
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Rainbow_Timer):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					if (gNewBS->RainbowTimers[gBattleStruct->turnEffectsBank] > 0
					&& --gNewBS->RainbowTimers[gBattleStruct->turnEffectsBank] == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = gBattleStruct->turnEffectsBank;
						BattleScriptExecute(BattleScript_RainbowEnd);
						effect++;
					}
					break;
				}
	
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Sea_Of_Fire_Timer):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					if (gNewBS->SeaOfFireTimers[gBattleStruct->turnEffectsBank] > 0
					&& --gNewBS->SeaOfFireTimers[gBattleStruct->turnEffectsBank] == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = gBattleStruct->turnEffectsBank;
						BattleScriptExecute(BattleScript_SeaOfFireEnd);
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Swamp_Timer):
				if (gBattleStruct->turnEffectsBank < 2)
				{
					if (gNewBS->SwampTimers[gBattleStruct->turnEffectsBank] > 0
					&& --gNewBS->SwampTimers[gBattleStruct->turnEffectsBank] == 0)
					{
						gBankAttacker = gBankTarget = gActiveBattler = gBattleStruct->turnEffectsBank;
						BattleScriptExecute(BattleScript_SwampEnd);
						effect++;
					}
					break;
				}

				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;

				__attribute__ ((fallthrough));
			case(ET_Trick_Room_Timer):
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;
				if (gNewBS->TrickRoomTimer > 0 && --gNewBS->TrickRoomTimer == 0)
				{
					BattleScriptExecute(BattleScript_TrickRoomEnd);
					return ++effect;
				}
				__attribute__ ((fallthrough));
			case(ET_Water_Sport_Timer):
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;
				if (gNewBS->WaterSportTimer > 0 && --gNewBS->WaterSportTimer == 0)
				{
					BattleScriptExecute(BattleScript_WaterSportEnd);
					return ++effect;
				}
				__attribute__ ((fallthrough));
			case(ET_Mud_Sport_Timer):
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;
				if (gNewBS->MudSportTimer > 0 && --gNewBS->MudSportTimer == 0)
				{
					BattleScriptExecute(BattleScript_MudSportEnd);
					return ++effect;
				}
				__attribute__ ((fallthrough));
			case(ET_Wonder_Room_Timer):
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;
				if (gNewBS->WonderRoomTimer > 0 && --gNewBS->WonderRoomTimer == 0)
				{
					BattleScriptExecute(BattleScript_WonderRoomEnd);
					return ++effect;
				}
				__attribute__ ((fallthrough));
			case(ET_Magic_Room_Timer):
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;
				if (gNewBS->MagicRoomTimer > 0 && --gNewBS->MagicRoomTimer == 0)
				{
					BattleScriptExecute(BattleScript_MagicRoomEnd);
					return ++effect;
				}
				__attribute__ ((fallthrough));
			case(ET_Gravity_Timer):
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;
				if (gNewBS->GravityTimer > 0 && --gNewBS->GravityTimer == 0)
				{
					BattleScriptExecute(BattleScript_GravityEnd);
					return ++effect;
				}
				__attribute__ ((fallthrough));
			case(ET_Seeds): ;
				if (ITEM_EFFECT(gActiveBattler) == ITEM_EFFECT_SEEDS)
				{
					if (ItemBattleEffects(ItemEffects_SwitchIn, gActiveBattler, FALSE, FALSE))
						++effect;
				}
				break;

			case(ET_Terrain_Timer):
				gNewBS->blockTracker = 0; //For later
				++gBattleStruct->turnEffectsTracker;
				gBattleStruct->turnEffectsBank = 0;
				if (gNewBS->TerrainTimer && --gNewBS->TerrainTimer == 0)
				{
					BattleScriptExecute(BattleScript_TerrainEnd);
					return ++effect;
				}
				__attribute__ ((fallthrough));
			case(ET_Block_B):
				switch(gNewBS->blockTracker) {
					case(ET_Uproar):
						if (gBattleMons[gActiveBattler].status2 & STATUS2_UPROAR
						&& gBattleMons[gActiveBattler].hp != 0)
						{
							gBattleMons[gActiveBattler].status2 -= 0x10;  // uproar timer goes down
							if (WasUnableToUseMove(gActiveBattler))
							{
								CancelMultiTurnMoves(gActiveBattler);
								gBattleCommunication[MULTISTRING_CHOOSER] = 1;
							}
							else if (gBattleMons[gActiveBattler].status2 & STATUS2_UPROAR)
							{
								gBattleCommunication[MULTISTRING_CHOOSER] = 0;
								gBattleMons[gActiveBattler].status2 |= STATUS2_MULTIPLETURNS;
							}
							else
							{
								gBattleCommunication[MULTISTRING_CHOOSER] = 1;
								CancelMultiTurnMoves(gActiveBattler);
							}
							
							BattleScriptExecute(BattleScript_PrintUproarOverTurns);
							++effect;
						}
						break;
						
					case(ET_SpeedBoost_Moody_BadDreams):
						if (gBattleMons[gActiveBattler].hp != 0)
						{
							gLastUsedAbility = ABILITY(gActiveBattler);
							switch(gLastUsedAbility) {
								case ABILITY_SPEEDBOOST:
								case ABILITY_TRUANT:
								case ABILITY_MOODY:
								case ABILITY_BADDREAMS:
									if (AbilityBattleEffects(ABILITYEFFECT_ENDTURN, gActiveBattler, 0, 0, 0))
										effect++;
									break;
							}
						}
						break;
						
					case(ET_Orbz):
						if (gBattleMons[gActiveBattler].hp != 0
						&&  gBattleMons[gActiveBattler].status1 == STATUS1_NONE)
						{
							u8 itemEffect = ITEM_EFFECT(gActiveBattler);
							if (itemEffect == ITEM_EFFECT_TOXIC_ORB
							&& CanBePoisoned(gActiveBattler, gActiveBattler, FALSE))
							{
								gLastUsedItem = ITEM(gActiveBattler);
								RecordItemEffectBattle(gActiveBattler, itemEffect);
								gBattleMons[gActiveBattler].status1 |= STATUS1_TOXIC_POISON;
								EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
								MarkBufferBankForExecution(gActiveBattler);
								
								gEffectBank = gActiveBattler;
								BattleScriptExecute(BattleScript_ToxicOrb);
								++effect;
							}
							else if (itemEffect == ITEM_EFFECT_FLAME_ORB
							&& CanBeBurned(gActiveBattler, FALSE))
							{
								gLastUsedItem = ITEM(gActiveBattler);
								RecordItemEffectBattle(gActiveBattler, itemEffect);
								gBattleMons[gActiveBattler].status1 |= STATUS1_BURN;
								EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
								MarkBufferBankForExecution(gActiveBattler);
								
								gEffectBank = gActiveBattler;
								BattleScriptExecute(BattleScript_FlameOrb);
								++effect;
							}
						}
						break;
						
					case(ET_Harvest_Pickup):
						if (gBattleMons[gActiveBattler].hp != 0
						&& (gBattleMons[gActiveBattler].item == ITEM_NONE || ABILITY(gActiveBattler) == ABILITY_SLOWSTART)) 
						{
							switch(ABILITY(gActiveBattler)) {
							case ABILITY_HARVEST:
							case ABILITY_PICKUP:
							case ABILITY_SLOWSTART:
								if (AbilityBattleEffects(ABILITYEFFECT_ENDTURN, gActiveBattler, 0, 0, 0))
									effect++;
							}
						}
						break;
				}
				
				++gNewBS->blockTracker;
				if (gNewBS->blockTracker < MAX_CASES_BLOCK_B)
					goto SkipBankIncrement;
				else
				{
					gNewBS->blockTracker = 0;
					break;
				}
					
			case(ET_Form_Change):
				if (gBattleMons[gActiveBattler].hp != 0 && !IS_TRANSFORMED(gActiveBattler)) 
				{
					struct Pokemon* mon = GetBankPartyData(gActiveBattler);
					u16 species = mon->species;
					u16 newSpecies = 0;
					u8 ability = ABILITY(gActiveBattler);
					bool8 changedForm = FALSE; 
					bool8 reloadType = FALSE;
					bool8 reloadStats = FALSE;
					bool8 reloadAbility = FALSE;
					const u8* battleScript = NULL;

					switch(ability) {
						case ABILITY_ZENMODE:
							if (species == SPECIES_DARMANITAN
							&& gBattleMons[gActiveBattler].hp <= gBattleMons[gActiveBattler].maxHP / 2)
							{
								newSpecies = SPECIES_DARMANITANZEN;
								changedForm = TRUE;
								reloadType = TRUE;
								reloadStats = TRUE;
								battleScript = BattleScript_TransformedEnd2;
							}
							break;

						case ABILITY_POWERCONSTRUCT:
							if ((species == SPECIES_ZYGARDE || species == SPECIES_ZYGARDE_10)
							&& gBattleMons[gActiveBattler].hp <= gBattleMons[gActiveBattler].maxHP / 2)
							{
								newSpecies = SPECIES_ZYGARDE_COMPLETE;
								changedForm = TRUE;
								reloadType = TRUE;
								reloadStats = TRUE;
								battleScript = BattleScript_PowerConstruct;
							}
							break;

						case ABILITY_SCHOOLING:
							if (species == SPECIES_WISHIWASHI && gBattleMons[gActiveBattler].level >= 20
							&& gBattleMons[gActiveBattler].hp > gBattleMons[gActiveBattler].maxHP / 4)
							{
								newSpecies = SPECIES_WISHIWASHI_S;
								changedForm = TRUE;
								reloadStats = TRUE;
								battleScript = BattleScript_StartedSchooling;
							}
							else if (species == SPECIES_WISHIWASHI_S
								&&  (gBattleMons[gActiveBattler].level < 20
								  || gBattleMons[gActiveBattler].hp <= gBattleMons[gActiveBattler].maxHP / 4)) 
							{
								newSpecies = SPECIES_WISHIWASHI;
								changedForm = TRUE;
								reloadStats = TRUE;
								battleScript = BattleScript_StoppedSchooling;
							}
							break;

						case ABILITY_SHIELDSDOWN:
							if (species == SPECIES_MINIOR_SHIELD 
							&& gBattleMons[gActiveBattler].hp <= gBattleMons[gActiveBattler].maxHP / 2)
							{
								newSpecies = GetMiniorCoreSpecies(mon);
								changedForm = TRUE;
								reloadStats = TRUE;
								battleScript = BattleScript_ShieldsDownToCore;
							}
							else if (CheckTableForSpecies(species, gMiniorCores)
							&& gBattleMons[gActiveBattler].hp > (gBattleMons[gActiveBattler].maxHP / 2)) 
							{
								newSpecies = SPECIES_MINIOR_SHIELD;
								changedForm = TRUE;
								reloadStats = TRUE;
								battleScript = BattleScript_ShieldsDownToMeteor;
							}
							break;
							
						case ABILITY_FLOWERGIFT:
							if (species == SPECIES_CHERRIM_SUN
							&& (!WEATHER_HAS_EFFECT || !(gBattleWeather & WEATHER_SUN_ANY) || ability != ABILITY_FLOWERGIFT))
							{
								newSpecies = SPECIES_CHERRIM;
								changedForm = TRUE;
								battleScript = BattleScript_FlowerGiftEnd2;
							}
					}
					
					if (changedForm) 
					{
						gBattleScripting->bank = gActiveBattler;
						DoFormChange(gActiveBattler, newSpecies, reloadType, reloadStats, reloadAbility);
						BattleScriptExecute(battleScript);
						++effect;
					}
				}
				break;
						
			case(ET_End):
				gBattleStruct->turnEffectsBank = gBattlersCount;
				gNewBS->endTurnDone = TRUE;
				gNewBS->MegaData->state = 0;
				gNewBS->calculatedAIPredictions = FALSE;
				gNewBS->batonPassing = FALSE;
				
				for (int i = 0; i < gBattlersCount; ++i)
				{
					gNewBS->pickupStack[i] = 0xFF;
					gNewBS->leftoverHealingDone[i] = FALSE;
					gNewBS->calculatedAISwitchings[i] = FALSE;
					gNewBS->recalculatedBestDoublesKillingScores[i] = FALSE;
					gNewBS->aiMegaPotential[i] = NULL;
				}
		}
		gBattleStruct->turnEffectsBank++;
		
		SkipBankIncrement:
			if (gBattleStruct->turnEffectsBank >= gBattlersCount)
			{
				gBattleStruct->turnEffectsTracker++;
				gBattleStruct->turnEffectsBank = 0;
			}
			if (effect)
				return effect;
	}
	
	gHitMarker &= ~(HITMARKER_GRUDGE | HITMARKER_x20);
	return 0;
}

u32 GetLeechSeedDamage(u8 bank)
{
	u32 damage = 0;

	if (gStatuses3[bank] & STATUS3_LEECHSEED
	&& ABILITY(bank) != ABILITY_MAGICGUARD)
		damage = MathMax(1, gBattleMons[bank].maxHP / 8);
	
	return damage;
}

u32 GetPoisonDamage(u8 bank)
{
	u32 damage = 0;
	u8 ability = ABILITY(bank);
	
	if (ability != ABILITY_MAGICGUARD
	&& ability != ABILITY_POISONHEAL)
	{
		if (gBattleMons[bank].status1 & STATUS_POISON)
		{
			damage = MathMax(1, gBattleMons[bank].maxHP / 8);
		}
		else if (gBattleMons[bank].status1 & STATUS_TOXIC_POISON)
		{
			damage = MathMax(1, gBattleMons[gActiveBattler].maxHP / 16);
			damage *= (gBattleMons[gActiveBattler].status1 & 0xF00) >> 8;
		}
	}
	else if (ability == ABILITY_POISONHEAL)
		damage = MathMax(1, gBattleMons[bank].maxHP / 8);
	
	return damage;
}

u32 GetBurnDamage(u8 bank)
{
	u32 damage = 0;
	u8 ability = ABILITY(bank);

	if (gBattleMons[bank].status1 & STATUS_BURN
	&& ability != ABILITY_MAGICGUARD) 
	{
		if (ability == ABILITY_HEATPROOF)
		{
			#ifdef OLD_BURN_DAMAGE
				damage = MathMax(1, gBattleMons[bank].maxHP / 16);
			#else
				damage = MathMax(1, gBattleMons[bank].maxHP / 32);
			#endif
		}
		else 
		{
			#ifdef OLD_BURN_DAMAGE
				damage = MathMax(1, gBattleMons[bank].maxHP / 8);
			#else
				damage = MathMax(1, gBattleMons[bank].maxHP / 16);
			#endif
		}
	}
	
	return damage;
}

u32 GetNightmareDamage(u8 bank)
{
	u32 damage = 0;

	if (gBattleMons[bank].status2 & STATUS2_NIGHTMARE
	&& gBattleMons[bank].status1 & STATUS_SLEEP
	&& ABILITY(bank) != ABILITY_MAGICGUARD)
	{
		damage = MathMax(1, gBattleMons[bank].maxHP / 4);
	}
	
	return damage;
}

u32 GetCurseDamage(u8 bank)
{
	u32 damage = 0;

	if (gBattleMons[bank].status2 & STATUS2_CURSED
	&& ABILITY(bank) != ABILITY_MAGICGUARD)
	{
		damage = MathMax(1, gBattleMons[bank].maxHP / 4);
	}

	return damage;
}

u32 GetTrapDamage(u8 bank)
{
	u32 damage = 0;

	if (gBattleMons[bank].status2 & STATUS2_WRAPPED
	&& ABILITY(bank) != ABILITY_MAGICGUARD)
	{
		if (ITEM_EFFECT(gBattleStruct->wrappedBy[bank]) == ITEM_EFFECT_BINDING_BAND)
			damage = MathMax(1, gBattleMons[bank].maxHP / 6);
		else
			damage = MathMax(1, gBattleMons[bank].maxHP / 8);
	}

	return damage;
}

u32 GetSeaOfFireDamage(u8 bank)
{
	u32 damage = 0;

	if (BankSideHasSeaOfFire(bank)
	&& !IsOfType(bank, TYPE_FIRE)
	&& ABILITY(bank) != ABILITY_MAGICGUARD)
	{
		damage = MathMax(1, gBattleMons[bank].maxHP / 8);
	}

	return damage;
}

#define FAINTED_ACTIONS_MAX_CASE 11

bool8 HandleFaintedMonActions(void)
{
	int i, j;
	
	if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
		return FALSE;
	
	do
	{
		switch (gBattleStruct->faintedActionsState) {
			case 0:
				gBattleStruct->faintedActionsBank = 0;
				gBattleStruct->faintedActionsState++;
				for (i = 0; i < gBattlersCount; i++)
				{
					if (gAbsentBattlerFlags & gBitTable[i] && !HasNoMonsToSwitch(i))
						gAbsentBattlerFlags &= ~(gBitTable[i]);
				}
				__attribute__ ((fallthrough));
			
			case 1:
				do
				{
					gBankFainted = gBankTarget = gBattleStruct->faintedActionsBank;
					if (gBattleMons[gBattleStruct->faintedActionsBank].hp == 0
					&& !(gBattleStruct->givenExpMons & gBitTable[gBattlerPartyIndexes[gBattleStruct->faintedActionsBank]])
					&& !(gAbsentBattlerFlags & gBitTable[gBattleStruct->faintedActionsBank]))
					{
						BattleScriptExecute(BattleScript_GiveExp);
						gBattleStruct->faintedActionsState = 2;
						return TRUE;
					}
				} while (++gBattleStruct->faintedActionsBank != gBattlersCount);
				
				gBattleStruct->faintedActionsState = 3;
				break;
			
			case 2:
				sub_8017434(gBankFainted);
				if (++gBattleStruct->faintedActionsBank >= gBattlersCount)
					gBattleStruct->faintedActionsState = 3;
				else
					gBattleStruct->faintedActionsState = 1;
				break;
			
			case 3:
				gBattleStruct->faintedActionsBank = 0;
				gBattleStruct->faintedActionsState++;
				__attribute__ ((fallthrough));
			
			case 4:
				do
				{
					gBankFainted = gBankTarget = gBattleStruct->faintedActionsBank;

					if (gBattleMons[gBattleStruct->faintedActionsBank].hp == 0)
					{
						if (!(gAbsentBattlerFlags & gBitTable[gBattleStruct->faintedActionsBank])) //Bank was just emptied
						{
							gAbsentBattlerFlags |= gBitTable[gBattleStruct->faintedActionsBank]; //Makes the game realize the target is dead for now, so no attacking it
							gNewBS->AbsentBattlerHelper |= gBitTable[gBattleStruct->faintedActionsBank]; //Record which Pokemon need replacements
						}

						if (gNewBS->AbsentBattlerHelper & gBitTable[gBattleStruct->faintedActionsBank])
						{
							if (gNewBS->endTurnDone
							||  ViableMonCountFromBank(gBattleStruct->faintedActionsBank) == 0)
							{
								gAbsentBattlerFlags &= ~(gBitTable[gBattleStruct->faintedActionsBank]);

								//Not wild battle
								//In a double or frontier battle, the player is not asked if they want to switch Pokemon
								if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && gBattleTypeFlags & (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_LINK))
								{
									gNewBS->handleSetSwitchIns |= gBitTable[gBattleStruct->faintedActionsBank];
									BattleScriptExecute(BattleScript_HandleFaintedMonDoublesInitial);
								}
								else
								{
									BattleScriptExecute(BattleScript_HandleFaintedMon);
									gNewBS->doSwitchInEffects |= gBitTable[gBattleStruct->faintedActionsBank];

									for (i = 0; i < gBattlersCount; ++i)
									{
										if (gNewBS->AbsentBattlerHelper & gBitTable[i]
										&&  !(gNewBS->doSwitchInEffects & gBitTable[i])
										&&  HITMARKER_FAINTED(i))
										{
											if (++gBattleStruct->faintedActionsBank >= gBattlersCount)
												gBattleStruct->faintedActionsState = 7;
											return TRUE; //Still more Pokemon that need to switch in (eg after Explosion)
										}
									}

									gBattleStruct->faintedActionsState = 7;
									return TRUE;
								}
								
								gBattleStruct->faintedActionsState = 5;
								return TRUE;
							}
						}
					}
				} while (++gBattleStruct->faintedActionsBank < gBattlersCount);

				if (gNewBS->handleSetSwitchIns)
				{
					gBattleStruct->faintedActionsBank = 0;
					gBattleStruct->faintedActionsState = 6;
				}
				else if (gNewBS->doSwitchInEffects)
					gBattleStruct->faintedActionsState = 7;
				else
					gBattleStruct->faintedActionsState = FAINTED_ACTIONS_MAX_CASE - 1;
				break;
			
			case 5:
				if (++gBattleStruct->faintedActionsBank >= gBattlersCount)
				{
					if (gNewBS->handleSetSwitchIns)
					{
						gBattleStruct->faintedActionsBank = 0;
						gBattleStruct->faintedActionsState = 6;
					}
					else if (gNewBS->doSwitchInEffects)
						gBattleStruct->faintedActionsState = 7;
					else
						gBattleStruct->faintedActionsState = FAINTED_ACTIONS_MAX_CASE - 1;
				}
				else
					gBattleStruct->faintedActionsState = 4;
				break;
			
			case 6:
				do
				{
					gBankFainted = gBankTarget = gBattleStruct->faintedActionsBank;
					if (gNewBS->handleSetSwitchIns & gBitTable[gBattleStruct->faintedActionsBank])
					{
						++gBattleStruct->faintedActionsBank;
						gAbsentBattlerFlags &= ~(gBitTable[gBattleStruct->faintedActionsBank]);
						BattleScriptExecute(BattleScript_HandleFaintedMonDoublesPart2);
						return TRUE;
					}
				} while (++gBattleStruct->faintedActionsBank < gBattlersCount);
				__attribute__ ((fallthrough));

			case 7:
				//Recalc turn order for switch-in abilities
				for (i = 0; i < gBattlersCount; ++i)
				{
					if (gNewBS->doSwitchInEffects & gBitTable[i])
						gNewBS->handleSetSwitchIns |= gBitTable[i];
	
					if (!BATTLER_ALIVE(i))
						gAbsentBattlerFlags |= gBitTable[i];

					gBanksByTurnOrder[i] = i;
				}
				gNewBS->doSwitchInEffects = FALSE;
				
				for (i = 0; i < gBattlersCount - 1; ++i) 
				{
					for (j = i + 1; j < gBattlersCount; ++j) 
					{
						if (GetWhoStrikesFirst(gBanksByTurnOrder[i], gBanksByTurnOrder[j], 1))
							SwapTurnOrder(i, j);
					}
				}
				
				gBattleStruct->faintedActionsBank = 0;
				gBattleStruct->faintedActionsState++;
				__attribute__ ((fallthrough));
			
			case 8:
				do
					{
						gBankFainted = gBankTarget = gBattleStruct->faintedActionsBank;
						if (gNewBS->handleSetSwitchIns & gBitTable[gBankFainted])
						{
							if (ABILITY(gBankFainted) == ABILITY_TRUANT)
								gDisableStructs[gBankFainted].truantCounter = 1; //So it gets unset during the switch in effects
				
							gNewBS->handleSetSwitchIns &= ~(gBitTable[gBankFainted]);
							BattleScriptExecute(BattleScript_HandleFaintedMonDoublesSwitchInEffects);
							return TRUE;
						}
					} while (++gBattleStruct->faintedActionsBank < gBattlersCount);
				gBattleStruct->faintedActionsState++;
				__attribute__ ((fallthrough));
			
			case 9: 
				if (gNewBS->restartEndTurnSwitching) //Died from entry hazards
				{	
					gNewBS->restartEndTurnSwitching = FALSE;
					gBattleStruct->faintedActionsState = 0;
				}
				else
					gBattleStruct->faintedActionsState++;
				break;
			
			case 10:
				gNewBS->endTurnDone = FALSE;
				gBattleStruct->faintedActionsState++;
				break;
			
			case FAINTED_ACTIONS_MAX_CASE:
				break;
		}
	} while (gBattleStruct->faintedActionsState != FAINTED_ACTIONS_MAX_CASE);
	
	return FALSE;
}

u8 CountAliveMonsOnField(void)
{
	u8 count = 0;
	
	for (int i = 0; i < gBattlersCount; ++i)
	{
		if (gBattleMons[i].hp)
			++count;
	}
	return count;
}

void RemoveSwitchInForFaintedBank(void)
{
	gNewBS->handleSetSwitchIns &= ~(gBitTable[gBankFainted]);
}

bool8 IsInMiddleOfEndTurnSwitchIn(u8 bank)
{
	if (gNewBS->handleSetSwitchIns & gBitTable[bank])
		return TRUE;
		
	return FALSE;
}
