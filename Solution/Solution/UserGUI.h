#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QTableView>
#include "ui_UserGUI.h"
#include "Service/UserService.h"
#include "AdoptionListModel.h"
#include "PictureDelegate.h"

class UserGUI : public QWidget
{
	Q_OBJECT

public:
	UserGUI(UserService& service, QWidget *parent = Q_NULLPTR);
	~UserGUI();

private:
	UserService& service;
	Ui::UserGUI ui;
	QPushButton* adopt_button, * dont_adopt_button, * see_all_button, * see_filtered_button, * open_adoption_list_file_button, * undo_button, * redo_button;
	QLabel* current_dog_label, * user_mode_label, * breed_label, * age_label;
	AdoptionListModel* adoption_model;
	PictureDelegate* picture_delegate;
	QTableView* adoption_list_widget;
	QLineEdit * breed_line, * age_line;
	QGridLayout* layout;

private:
	void showCurrentDog();
	void adoptDog();
	void moveToNextDog();
	void seeAllDogs();
	void seeFilteredDogs();
	void openAdoptionFile();
	void undo();
	void redo();
	void keyPressEvent(QKeyEvent* event);
};
