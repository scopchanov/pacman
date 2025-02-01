#include "FileHandler.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QFile>

FileHandler::FileHandler(QObject *parent) :
	QObject(parent)
{

}

QJsonObject FileHandler::readFile(const QString &filename)
{
	QFile file(filename);

	if (!file.open(QFile::ReadOnly | QFile::Text))
		return QJsonObject();

	QJsonParseError err;
	const QJsonDocument &doc{QJsonDocument::fromJson(file.readAll(), &err)};

	file.close();

	if (err.error || !doc.isObject())
		return QJsonObject();

	return doc.object();
}
