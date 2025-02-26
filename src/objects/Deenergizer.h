#ifndef DEENERGIZER_H
#define DEENERGIZER_H

#include "AbstractGameObject.h"

class Deenergizer : public AbstractGameObject
{
public:
	enum ModificationType : int {
		MOD_Activate = 0,
		MOD_Deactivate,
		MOD_Reset
	};

	explicit Deenergizer(AbstractGameObject *parent = nullptr);

	void activate();
	void deactivate();
	void reset() override ;

	int objectType() const override final;

private:
	void modifyComponent(int t);
	void updatePath(qreal value);
};

#endif // DEENERGIZER_H
