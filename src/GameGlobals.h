#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

enum ColorRole : int {
	CR_Player = 0,
	CR_PlayerEnergized,
	CR_Blinky,
	CR_Inky,
	CR_Pinky,
	CR_Clyde,
	CR_EnemyFrightened,
	CR_Wall,
	CR_Door,
	CR_Dot,
	CR_Energizer
};

enum ActionType : int {
	ACT_CalmDownEnemies = 0,
	ACT_DeleteGameObject,
	ACT_DeenergizePlayer,
	ACT_EnergizePlayer,
	ACT_ScareEnemies
};

enum BehaviorType : int {
	BT_Animation = 0,
	BT_CameraFollow,
	BT_Coloring,
	BT_CharacterMovement,
	BT_Delaying,
	BT_DotsEating,
	BT_EnemyController,
	BT_EnemyEating,
	BT_Energizing,
	BT_KillPlayer,
	BT_Orientation,
	BT_PlayerController,
	BT_Spawning,
	BT_Teleporting
};

enum ObjectType : int {
	OBJ_Npc = 0,
	OBJ_Player,
	OBJ_Enemy,
	OBJ_Energizer,
	OBJ_Teleporter
};

#endif // GAMEGLOBALS_H
