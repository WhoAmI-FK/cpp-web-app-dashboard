#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>
#include <Wt/WProgressBar.h>
#include <Wt/WPushbutton.h>
#include "DashboardData.h"


class Dashboard : public Wt::WApplication
{
public:
	Dashboard(const Wt::WEnvironment& env)
		: WApplication(env)
	{
		setTitle("Dashboard");
		messageResourceBundle().use(appRoot() + "dashboard");
		instance()->useStyleSheet("resources/dashboard.css");
		_title = root()->addWidget(Wt::cpp14::make_unique<Wt::WText>("Manufacturing Process Status"));
		_title->setStyleClass("title");

		auto container = root()->addWidget(Wt::cpp14::make_unique < Wt::WContainerWidget>());
		auto vbox = container->setLayout(Wt::cpp14::make_unique<Wt::WVBoxLayout>());
		_time = vbox->addWidget(Wt::cpp14::make_unique<Wt::WText>("Time: "));
		_time->setStyleClass("process");

		// meters
		_pulsometer = vbox->addWidget(Wt::cpp14::make_unique<Wt::WText>("Pulsometer Readout: "));
		_pulsometer->setStyleClass("process");

		auto containerEngine = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
		auto hbox = containerEngine->setLayout(Wt::cpp14::make_unique<Wt::WHBoxLayout>());
		_engineText = hbox->addWidget(Wt::cpp14::make_unique<Wt::WText>("Engine Efficiency:"));
		_engine = hbox->addWidget(Wt::cpp14::make_unique<Wt::WProgressBar>());
		_engine->setStyleClass("Wt-progressbar");

		// color Status
		auto containerColor = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
		auto colorBox = containerColor->setLayout(Wt::cpp14::make_unique<Wt::WVBoxLayout>());

		_red = colorBox->addWidget(Wt::cpp14::make_unique<Wt::WText>("Red"));
		_red->setStyleClass("red-box");

		_blue = colorBox->addWidget(Wt::cpp14::make_unique<Wt::WText>("Blue"));
		_blue->setStyleClass("blue-box");

		_green = colorBox->addWidget(Wt::cpp14::make_unique<Wt::WText>("Green"));
		_green->setStyleClass("green-box");
		auto button = root()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Update"));
		button->setMargin(5, Wt::Side::Left);
		root()->addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
		_dbData.loadData();
		updateBoard();
	
		button->clicked().connect(this,&Dashboard::updateBoard);
		button->clicked().connect([=]() {
			std::cerr << "Update " << std::endl;
			});
	}
private:
	Wt::WText* _title;
	Wt::WText* _time;
	Wt::WText* _pulsometer;
	Wt::WText* _engineText;
	Wt::WProgressBar* _engine;
	Wt::WText* _green;
	Wt::WText* _red;
	Wt::WText* _blue;
	DashboardData _dbData;
	void updateBoard();
};

void Dashboard::updateBoard()
{
	_dbData.getData();
	_time->setText("Time: " + _dbData.getTime());
	_pulsometer->setText("Pulsometer Readout: " + std::to_string(_dbData.getPulsometer()));
	_engine->setValue(_dbData.getEngine());

	_red->setText("Red Value: " + std::to_string(_dbData.getRed())); -
		_blue->setText("Blue Value: " + std::to_string(_dbData.getBlue()));
	_green->setText("Green Value: " + std::to_string(_dbData.getGreen()));
}