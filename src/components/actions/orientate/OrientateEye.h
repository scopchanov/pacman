#ifndef ORIENTATEEYE_H
#define ORIENTATEEYE_H

#include "AbstractOrientate.h"

class EnemyEye;
class Vector2;

class OrientateEye : public AbstractOrientate
{
public:
	explicit OrientateEye(AbstractComponent *parent = nullptr);

	void reset() override;

protected:
	void orientate() override;

private:
	Vector2 currentDirection();
	EnemyEye *enemyEye() const;
};

#endif // ORIENTATEEYE_H
