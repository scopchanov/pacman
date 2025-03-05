#include "DialogGame.h"
#include "Button.h"
#include <QBoxLayout>
#include <QLabel>

DialogGame::DialogGame(QWidget *parent) :
	QDialog{parent}
{
	auto *layoutMain{new QVBoxLayout(this)};
	auto *btnResume{new Button(this)};
	auto *btnMainMenu{new Button(this)};
	QPalette p{palette()};

	btnResume->setText(tr("&Resume game"));
	btnMainMenu->setText(tr("&Main Menu"));

	layoutMain->addStretch();
	layoutMain->addWidget(btnResume);
	layoutMain->addWidget(btnMainMenu);
	layoutMain->addStretch();
	layoutMain->setSpacing(20);
	layoutMain->setAlignment(Qt::AlignCenter);

	p.setBrush(QPalette::Window, Qt::black);

	setPalette(p);
	setAutoFillBackground(true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	resize(300, 200);

	connect(btnResume, &QPushButton::clicked, this, &DialogGame::reject);
	connect(btnMainMenu, &QPushButton::clicked, this, &DialogGame::accept);
}
