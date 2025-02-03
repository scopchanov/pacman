#ifndef ABSTRACTBEHAVIOR_H
#define ABSTRACTBEHAVIOR_H

class GameObject;

class AbstractBehavior
{
public:
	enum BehaviorType : int {
		BT_Animation = 0,
		BT_CameraFollow,
		BT_CharacterMovement,
		BT_Debug,
		BT_DotsEating,
		BT_EnemyController,
		BT_KillPlayer,
		BT_PlayerAnimation,
		BT_PlayerController,
		BT_PlayerOrientation,
		BT_Teleporting
	};

	explicit AbstractBehavior(GameObject *parent = nullptr);
	virtual ~AbstractBehavior() = default;

	GameObject *parent() const;
	virtual void setParent(GameObject *parent);

	void execute();

	virtual int type() const = 0;

private:
	virtual void performActions() = 0;

	GameObject *m_parent;
};

#endif // ABSTRACTBEHAVIOR_H
