#include "GameMenu.h"
#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>

GameMenu::GameMenu(QWidget *parent) :
	QWidget(parent)
{
	auto *layoutMain{new QVBoxLayout(this)};
	auto *btnStart{new QPushButton(tr("S&tart"), this)};
	auto *btnSettings{new QPushButton(tr("&Settings"), this)};
	auto *btnExit{new QPushButton(tr("E&xit"), this)};

	btnStart->setMinimumHeight(48);
	btnStart->setMinimumWidth(250);
	btnSettings->setMinimumHeight(48);
	btnSettings->setMinimumWidth(250);
	btnExit->setMinimumHeight(48);
	btnExit->setMinimumWidth(250);

	layoutMain->addStretch();
	layoutMain->addWidget(btnStart);
	layoutMain->addWidget(btnSettings);
	layoutMain->addWidget(btnExit);
	layoutMain->addStretch();
	layoutMain->setSpacing(20);
	layoutMain->setAlignment(Qt::AlignCenter);

	connect(btnStart, &QPushButton::clicked, this, &GameMenu::newGame);
	connect(btnExit, &QPushButton::clicked, &QApplication::quit);
}
