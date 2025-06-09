#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Main_GUI.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "Service/AdminService.h"
#include "Service/UserService.h"

class Main_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Main_GUI(AdminService& admin, UserService& csv, UserService& html, QWidget* parent = Q_NULLPTR);
    ~Main_GUI();
    void setMainWidget(QWidget* new_main);
private:

	AdminService& admin_service;
	UserService& csv_service;
	UserService& html_service;
    QWidget* main_widget;
	QGridLayout* layout;
	QLabel* select_label;
	QPushButton* admin_button;
	QPushButton* user_html_button;
	QPushButton* user_csv_button;
	Ui::Main_GUIClass ui;

private:
	void changeToAdmin();
	void changeToCSVUser();
	void changeToHTMLUser();
};