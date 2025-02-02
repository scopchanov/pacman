#ifndef ABSTRACTBEHAVIOR_H
#define ABSTRACTBEHAVIOR_H

class GameObject;

class AbstractBehavior
{
public:
	explicit AbstractBehavior(GameObject *parent = nullptr);
	virtual ~AbstractBehavior() = default;

	GameObject *parent() const;
	virtual void setParent(GameObject *parent);

	virtual void execute() = 0;

private:
	GameObject *m_parent;
};

#endif // ABSTRACTBEHAVIOR_H
