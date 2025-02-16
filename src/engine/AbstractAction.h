#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

class AbstractBehavior;
class Game;

class AbstractAction
{
public:
	enum ActionType : int {
		ACT_EnergizePlayer = 0,
		ACT_FrightenEnemies
	};

	explicit AbstractAction(AbstractBehavior *parent = nullptr);
	virtual ~AbstractAction() = default;

	AbstractBehavior *parent() const;
	void setParent(AbstractBehavior *parent);
	Game *game() const;
	void setGame(Game *game);
	virtual int type() const = 0;

	void trigger();

private:
	virtual void performTask() = 0;

	AbstractBehavior *_parent;
	Game *_game;
};

#endif // ABSTRACTACTION_H
