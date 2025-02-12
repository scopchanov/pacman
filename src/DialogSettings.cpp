#include "DialogSettings.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QLabel>

DialogSettings::DialogSettings(QWidget *parent) :
	QWidget{parent}
{
	auto *layoutMain(new QVBoxLayout(this));
	auto *sliderMusikVolume{new QSlider(Qt::Horizontal, this)};
	auto *chkShowGrid{new QCheckBox(tr("Show grid"), this)};


	layoutMain->addWidget(sliderMusikVolume);
	layoutMain->addWidget(chkShowGrid);
	layoutMain->addStretch();
}
