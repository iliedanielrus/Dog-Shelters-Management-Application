#include "UserGUI.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <QKeyEvent>

UserGUI::UserGUI(UserService& service, QWidget *parent)
	: QWidget(parent), service{ service }
{
	setFocusPolicy(Qt::StrongFocus);
	ui.setupUi(this);
	this->resize(QDesktopWidget().availableGeometry(this).size().width() * 0.28f, QDesktopWidget().availableGeometry(this).size().height() * 0.5f);
	adopt_button = new QPushButton("Adopt the dog", this);
	dont_adopt_button = new QPushButton("Don't adopt the dog", this);
	adopt_button->setDisabled(true);
	dont_adopt_button->setDisabled(true);
	see_all_button = new QPushButton("See all dogs", this);
	see_filtered_button = new QPushButton("See dogs with the specified breed and with age less than the given age", this);
	open_adoption_list_file_button = new QPushButton("Open the adoption file", this);
	current_dog_label = new QLabel("", this);
	user_mode_label = new QLabel("User mode", this);
	breed_label = new QLabel("Breed:", this);
	age_label = new QLabel("Age:", this);
	adoption_model = new AdoptionListModel(this->service);
	picture_delegate = new PictureDelegate(this);
	adoption_list_widget = new QTableView(this);
	adoption_list_widget->setModel(adoption_model);
	adoption_list_widget->setItemDelegate(picture_delegate);
	breed_line = new QLineEdit(this); 
	age_line = new QLineEdit(this);
	undo_button = new QPushButton("Undo", this);
	redo_button = new QPushButton("Redo", this);
	layout = new QGridLayout(this);
	layout->addWidget(user_mode_label, 0, 0, 1, 4, Qt::AlignHCenter);
	layout->addWidget(current_dog_label, 1, 0, 1, 4, Qt::AlignHCenter);
	layout->addWidget(adopt_button, 2, 0, 1, 4);
	layout->addWidget(dont_adopt_button, 3, 0, 1, 4);
	layout->addWidget(see_all_button, 4, 0, 1, 4);
	layout->addWidget(breed_label, 5, 0);
	layout->addWidget(breed_line, 5, 1);
	layout->addWidget(age_label, 5, 2);
	layout->addWidget(age_line, 5, 3);
	layout->addWidget(see_filtered_button, 6, 0, 1, 4);
	layout->addWidget(open_adoption_list_file_button, 7, 0, 1, 4);
	layout->addWidget(undo_button, 8, 0, 1, 2);
	layout->addWidget(redo_button, 8, 2, 1, 2);
	layout->addWidget(adoption_list_widget, 9, 0, 1, 4);
	this->setLayout(layout);
	QObject::connect(adopt_button, &QPushButton::clicked, this, &UserGUI::adoptDog);
	QObject::connect(dont_adopt_button, &QPushButton::clicked, this, &UserGUI::moveToNextDog);
	QObject::connect(see_all_button, &QPushButton::clicked, this, &UserGUI::seeAllDogs);
	QObject::connect(see_filtered_button, &QPushButton::clicked, this, &UserGUI::seeFilteredDogs);
	QObject::connect(open_adoption_list_file_button, &QPushButton::clicked, this, &UserGUI::openAdoptionFile);
	QObject::connect(undo_button, &QPushButton::clicked, this, &UserGUI::undo);
	QObject::connect(redo_button, &QPushButton::clicked, this, &UserGUI::redo);

}

UserGUI::~UserGUI()
{
}

void UserGUI::showCurrentDog()
{
	try
	{
		Dog current_dog = this->service.getCurrentDog();
		this->current_dog_label->setText(QString::fromStdString("Breed: " + current_dog.getBreed() + ", Name: " + current_dog.getName() + ", Age: ") + QString::number(current_dog.getAge()));
		std::string photograph = current_dog.getPhotograph();
		std::string op = std::string("start ").append(photograph);
		system(op.c_str());
	}
	catch (RepoException& re)
	{
		this->current_dog_label->setText("There are no more dogs to be shown!");
		this->adopt_button->setDisabled(true);
		this->dont_adopt_button->setDisabled(true);
	}
}

void UserGUI::adoptDog()
{
	this->service.adoptDog(this->service.getCurrentDog());
	this->adoption_model->update();
	this->adoption_list_widget->resizeRowsToContents();
	showCurrentDog();
}

void UserGUI::moveToNextDog()
{
	this->service.moveToNextDog();
	showCurrentDog();
}

void UserGUI::seeAllDogs()
{
	this->service.filterList();
	this->adopt_button->setDisabled(false);
	this->dont_adopt_button->setDisabled(false);
	showCurrentDog();
}

void UserGUI::seeFilteredDogs()
{
	bool ok;
	int age = this->age_line->text().toInt(&ok);
	if (!ok)
	{
		this->current_dog_label->setText("The value you inputed in the age field is not a number!");
		return;
	}
	this->service.filterList(age, this->breed_line->text().toStdString());
	this->adopt_button->setDisabled(false);
	this->dont_adopt_button->setDisabled(false);
	showCurrentDog();
}

void UserGUI::openAdoptionFile()
{
	this->current_dog_label->setText("");
	this->adopt_button->setDisabled(true);
	this->dont_adopt_button->setDisabled(true);
	std::string op = std::string("start ").append(this->service.getAdoptionListFile());
	system(op.c_str());
}

void UserGUI::undo()
{
	try {
		this->service.undo();
		this->adoption_model->update();
		this->adoption_list_widget->resizeRowsToContents();
	}
	catch (UndoRedoException ure)
	{
		QMessageBox error_box;
		error_box.setText(ure.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
}

void UserGUI::redo()
{
	try {
		this->service.redo();
		this->adoption_model->update();
		this->adoption_list_widget->resizeRowsToContents();
		showCurrentDog();
	}
	catch (UndoRedoException ure)
	{
		QMessageBox error_box;
		error_box.setText(ure.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
}

void UserGUI::keyPressEvent(QKeyEvent* event)
{
	if (event->matches(QKeySequence::Undo))
		this->undo();
	else if (event->matches(QKeySequence::Redo))
		this->redo();
	QWidget::keyPressEvent(event);
}

