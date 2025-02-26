#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

enum ColorRole : int {
	CR_Background = 0,
	CR_Player,
	CR_PlayerEnergized,
	CR_Blinky,
	CR_Inky,
	CR_Pinky,
	CR_Clyde,
	CR_EnemyFrightened,
	CR_Wall,
	CR_Door,
	CR_Dot,
	CR_Energizer,
	CR_Teleporter
};

enum ComponentType : int {
	ACT_ActivateDeenergizer = 0,
	ACT_CalmDownEnemies ,
	ACT_DeleteGameObject,
	ACT_DeenergizePlayer,
	ACT_DeactivateDeenergizer,
	ACT_EnergizePlayer,
	ACT_KillPlayer,
	ACT_ScareEnemies,
	ACT_Teleport,
	ACT_UpdateDeenergizer,
	BT_Animating,
	BT_Coloring,
	BT_Controlling,
	BT_Delaying,
	BT_DotsEating,
	BT_EnemyEating,
	BT_Energizing,
	BT_Moving,
	BT_Orientating,
	BT_Spawning
};

enum ObjectType : int {
	OBJ_Npc = 0,
	OBJ_Player,
	OBJ_Enemy,
	OBJ_Energizer,
	OBJ_Deenergizer,
	OBJ_Teleporter
};

enum PersonalityType : int {
	PT_Shadowing = 0,
	PT_Speeding,
	PT_Shying,
	PT_Poking
};

#endif // GAMEGLOBALS_H
