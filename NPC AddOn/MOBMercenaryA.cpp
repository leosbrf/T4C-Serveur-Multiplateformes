#pragma hdrstop
#include "MOBMercenaryA.h"

MOBMercenaryA::MOBMercenaryA()
{}

MOBMercenaryA::~MOBMercenaryA()
{}

extern NPCstructure::NPC MOBMercenaryNPC;

void MOBMercenaryA::Create(){
   npc = MOBMercenaryNPC;
   SET_NPC_NAME( "[12748]Mercenary" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void MOBMercenaryA::OnAttacked( UNIT_FUNC_PROTOTYPE ){
   if( target != NULL )
   {
	IF (rnd.roll(dice(1,30)) == 1) 
		IF (rnd.roll(dice(1,2)) == 1) 
			SHOUT(INTL( 12413, "You're no match for me!")) 
		ELSE 
			SHOUT(INTL( 12414, "Ow! You'll pay in blood!"))
		ENDIF 
	ENDIF    
   }
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBMercenaryA::OnDeath( UNIT_FUNC_PROTOTYPE ){
  INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{            
            GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_A_KILLED_COUNTER, CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_A_KILLED_COUNTER)+1 )
            IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_A_KILLED_COUNTER)>=15) 
              IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_A_SPAWNED)==0)
                SUMMON("MOBMERCENARYLIEUTENANTA",2675,1069)
                GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_A_KILLED_COUNTER, 0)
              ENDIF 
            ENDIF 
	}

    CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

