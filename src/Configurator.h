#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QObject>

class AbstractGameObject;
class AbstractPersonality;
class GameLevel;
class Palette;
class Grid;

class Configurator : public QObject
{
	Q_OBJECT
public:
	explicit Configurator(QObject *parent = nullptr);
	
	void configure(const QJsonObject &json);

private:
	void configureLevelState(const QJsonArray &jsonStepDurations);
	void configurePalette(const QJsonObject &json);
	void configureGrid(const QJsonObject &json);
	void configureWalls(const QJsonArray &jsonWalls);
	void configureDots(const QJsonArray &jsonDots);
	void configureDeenergizer(const QJsonObject &json);
	void configurePlayer(const QJsonObject &json);
	void createEnemies(const QJsonArray &enemies);
	void createEnemy(const QJsonObject &json);
	void createEye(AbstractGameObject *parent, const QPointF &pos);
	AbstractPersonality *createPersonality(const QJsonObject &json);
	void createDoors(const QJsonArray &doors);
	void createDoor(const QJsonObject &json);
	void createEnergizers(const QJsonArray &energizers);
	void createEnergizer(const QJsonObject &json);
	void createTeleporters(const QJsonArray &teleporters);
	void createTeleporter(const QJsonObject &json);
	int key2role(const QString &key) const;
	QPointF gridPosition(int row, int column) const;
	GameLevel *level() const;
	Palette *palette() const;
	Grid *grid() const;
};

#endif // CONFIGURATOR_H
