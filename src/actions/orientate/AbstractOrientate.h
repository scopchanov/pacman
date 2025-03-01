#ifndef ABSTRACTORIENTATE_H
#define ABSTRACTORIENTATE_H

#include "AbstractAction.h"

class Move;

class AbstractOrientate : public AbstractAction
{
public:
	explicit AbstractOrientate(AbstractComponent *parent = nullptr);

	Move *move() const;
	void setMove(Move *move);
	int type() const override final;

protected:
	void performTasks() override final;
	virtual void orientate() = 0;

private:
	Move *_move;
};

#endif // ABSTRACTORIENTATE_H
