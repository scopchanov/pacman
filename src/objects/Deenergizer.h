#ifndef DEENERGIZER_H
#define DEENERGIZER_H

#include "AbstractGameObject.h"

class Deenergizer : public AbstractGameObject
{
	enum ModificationType : int {
		MOD_Activate = 0,
		MOD_Deactivate,
		MOD_Reset
	};

public:
	explicit Deenergizer(AbstractGameObject *parent = nullptr);

	void activate();
	void deactivate();
	void reset() override ;

	int objectType() const override final;

private:
	void modifyComponent(int type);
};

#endif // DEENERGIZER_H
