#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

enum ColorRole : int {
	CR_Background = 0,
	CR_Player,
	CR_PlayerEnergized,
	CR_Blinky,
	CR_Pinky,
	CR_Inky,
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
	ACT_Animate,
	ACT_CalmDownEnemies,
	ACT_Control,
	ACT_DeleteGameObject,
	ACT_DeenergizePlayer,
	ACT_DeactivateDeenergizer,
	ACT_EatDot,
	ACT_EatEnemy,
	ACT_EnergizePlayer,
	ACT_KillPlayer,
	ACT_Move,
	ACT_Orientate,
	ACT_Spawn,
	ACT_Teleport,
	BT_Delaying
};

enum ObjectType : int {
	OBJ_Npc = 0,
	OBJ_Player,
	OBJ_Enemy,
	OBJ_EnemyEye,
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

enum WanderMode : int {
	WM_Scatter = 0,
	WM_Chase
};

#endif // GAMEGLOBALS_H
