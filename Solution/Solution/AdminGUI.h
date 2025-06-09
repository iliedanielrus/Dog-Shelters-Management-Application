#pragma once

#include <QWidget>
#include "ui_AdminGUI.h"
#include <QLabel>
#include <QtWidgets/QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QtCharts>
#include "Service/AdminService.h"


class AdminGUI : public QWidget
{
	Q_OBJECT

public:
	AdminGUI(std::string file_string, AdminService& service, QWidget* parent = Q_NULLPTR);
	~AdminGUI();

private:
	std::string file_string;
	AdminService& service;
	QLabel* title_label, * breed, * name, * age, * link, * new_breed, * new_name, * new_age, * new_link;
	QLineEdit* breed_line, * name_line, * age_line, * link_line, * new_breed_line, * new_name_line, * new_age_line, * new_link_line;
	QPushButton* add_button, * delete_button, * update_button, * help_button, * undo_button, * redo_button;
	QListWidget* dog_list;
	QGridLayout* layout;
	QChart* chart;
	QChartView* chart_view;
	QBarSeries* series;
	QStringList dog_breeds;
	QBarSet* bar_set;
	QBarCategoryAxis* axisX;
	QValueAxis* axisY;
	Ui::AdminGUI ui;

private:
	void populateDogList();
	void populateDogChart();
	void updateDogChart();
	void clearInputs();
	void addDog();
	void deleteDog();
	void updateDog();
	void undo();
	void redo();
	void showHelp();
	void loadSelection();
	void keyPressEvent(QKeyEvent* event) override;
};
