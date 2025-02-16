#ifndef ABSTRACTBEHAVIOR_H
#define ABSTRACTBEHAVIOR_H

#include <QList>

class GameObject;
class AbstractAction;

class AbstractBehavior
{
public:
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

	explicit AbstractBehavior(GameObject *parent = nullptr);
	virtual ~AbstractBehavior() = default;

	GameObject *parent() const;
	void setParent(GameObject *parent);
	bool isEnabled() const;
	void setEnabled(bool enabled);
	virtual int type() const = 0;

	void addAction(AbstractAction *action);
	AbstractAction *findAction(int type) const;
	virtual void reset();
	void execute();

private:
	virtual void performActions();

	GameObject *_parent;
	bool _enabled;
	QList<AbstractAction *> _actions;
};

#endif // ABSTRACTBEHAVIOR_H
