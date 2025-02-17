#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

class AbstractBehavior;

class AbstractAction
{
public:
	enum ActionType : int {
		ACT_CalmDownEnemies = 0,
		ACT_DeleteGameObject,
		ACT_DeenergizePlayer,
		ACT_EnergizePlayer,
		ACT_ScareEnemies
	};

	explicit AbstractAction(AbstractBehavior *parent = nullptr);
	virtual ~AbstractAction() = default;

	AbstractBehavior *parent() const;
	void setParent(AbstractBehavior *parent);
	virtual int type() const = 0;

	void trigger();

private:
	virtual void performTask() = 0;

	AbstractBehavior *_parent;
};

#endif // ABSTRACTACTION_H
