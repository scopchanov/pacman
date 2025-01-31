#ifndef ABSTRACTBEHAVIOR_H
#define ABSTRACTBEHAVIOR_H

class AbstractBehavior
{
public:
	explicit AbstractBehavior();
	virtual ~AbstractBehavior() = default;

	virtual void execute() = 0;
};

#endif // ABSTRACTBEHAVIOR_H
