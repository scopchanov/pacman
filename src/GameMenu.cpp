#include "GameMenu.h"
#include "Button.h"
#include <QApplication>
#include <QBoxLayout>

GameMenu::GameMenu(QWidget *parent) :
	QWidget(parent)
{
	auto *layoutMain{new QVBoxLayout(this)};
	auto *btnStart{new Button(this)};
	auto *btnSettings{new Button(this)};
	auto *btnExit{new Button(this)};

	btnStart->setText(tr("S&tart"));
	btnSettings->setText(tr("&Settings"));
	btnExit->setText(tr("E&xit"));

	layoutMain->addStretch();
	layoutMain->addWidget(btnStart);
	layoutMain->addWidget(btnSettings);
	layoutMain->addWidget(btnExit);
	layoutMain->addStretch();
	layoutMain->setSpacing(20);
	layoutMain->setAlignment(Qt::AlignCenter);

	setAutoFillBackground(true);

	connect(btnStart, &QPushButton::clicked, this, &GameMenu::newGame);
	connect(btnExit, &QPushButton::clicked, &QApplication::quit);
}
