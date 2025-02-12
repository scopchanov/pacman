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
		BT_DotsEating,
		BT_EnemyController,
		BT_EnemyEating,
		BT_KillPlayer,
		BT_Orientation,
		BT_PlayerController,
		BT_Teleporting,
		BT_PoweringUp
	};

	explicit AbstractBehavior(GameObject *parent = nullptr);
	virtual ~AbstractBehavior() = default;

	GameObject *parent() const;
	void setParent(GameObject *parent);
	bool isDisabled() const;
	void setDisabled(bool value);

	virtual void reset();
	void execute();

	virtual int type() const = 0;

private:
	virtual void performActions() = 0;

	GameObject *_parent;
	bool _disabled;
};

#endif // ABSTRACTBEHAVIOR_H
