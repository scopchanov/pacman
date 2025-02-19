#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

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
	BT_KillPlayer,
	BT_Orientation,
	BT_PlayerController,
	BT_Teleporting,
	BT_Energizing
};

#endif // GAMEGLOBALS_H
