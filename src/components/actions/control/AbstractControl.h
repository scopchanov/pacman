#ifndef ABSTRACTCONTROL_H
#define ABSTRACTCONTROL_H

#include <AbstractAction.h>

class Move;

class AbstractControl : public AbstractAction
{
public:
	explicit AbstractControl(AbstractComponent *parent = nullptr);
	
	Move *move() const;
	void setMove(Move *move);

	int type() const override final;

protected:
	void performTasks() override;
	virtual void control() = 0;

private:
	Move *_move;
};

#endif // ABSTRACTCONTROL_H
