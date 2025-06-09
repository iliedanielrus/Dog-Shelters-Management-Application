#include "AdminGUI.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <QDesktopWidget>
#include "Domain/DogValidator.h"
#include <QMessageBox>


AdminGUI::AdminGUI(std::string file_string, AdminService& service, QWidget* parent)
	: QWidget(parent), service(service)
{
	setFocusPolicy(Qt::StrongFocus);
	this->file_string = file_string;
	ui.setupUi(this);
	this->resize(QDesktopWidget().availableGeometry(this).size().width() * 0.8f, QDesktopWidget().availableGeometry(this).size().height() * 0.7f);
	layout = new QGridLayout(this);
	title_label = new QLabel("Admin mode", this);
	breed = new QLabel("Breed:", this);
	name = new QLabel("Name:", this);
	age = new QLabel("Age:", this);
	link = new QLabel("Link:", this);
	new_breed = new QLabel("New breed:", this);
	new_name = new QLabel("New name:", this);
	new_age = new QLabel("New age:", this);
	new_link = new QLabel("New link:", this);
	breed_line = new QLineEdit(this);
	name_line = new QLineEdit(this);
	age_line = new QLineEdit(this);
	link_line = new QLineEdit(this);
	new_breed_line = new QLineEdit(this);
	new_name_line = new QLineEdit(this);
	new_age_line = new QLineEdit(this);
	new_link_line = new QLineEdit(this);
	chart = new QChart();
	series = new QBarSeries();
	bar_set = new QBarSet("Number of dogs", this->chart);
	axisX = new QBarCategoryAxis();
	axisY = new QValueAxis();
	chart->setTitle("Dog Breed numbers");
	chart->setParent(this);
	chart_view = new QChartView(chart);
	chart_view->setRenderHint(QPainter::Antialiasing);
	breed->setBuddy(breed_line);
	name->setBuddy(name_line);
	age->setBuddy(age_line);
	link->setBuddy(link_line);
	new_breed->setBuddy(new_breed_line);
	new_name->setBuddy(new_name_line);
	new_age->setBuddy(new_age_line);
	new_link->setBuddy(new_link_line);
	add_button = new QPushButton("Add", this);
	delete_button = new QPushButton("Delete", this);
	update_button = new QPushButton("Update", this);
	help_button = new QPushButton("Help", this);
	undo_button = new QPushButton("Undo", this);
	redo_button = new QPushButton("Redo", this);
	dog_list = new QListWidget(this);
	this->dog_list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	this->populateDogList();
	title_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	for (int i = 0; i < 6; i++)
		layout->setRowStretch(i, 1);
	for (int i = 0; i < 8; i++)
		layout->setColumnStretch(i, 1);
	layout->setRowStretch(8, 5);
	layout->addWidget(title_label, 0, 0, 1, 8, Qt::AlignHCenter);
	layout->addWidget(breed, 1, 0);
	layout->addWidget(breed_line, 1, 1);
	layout->addWidget(name, 1, 2);
	layout->addWidget(name_line, 1, 3);
	layout->addWidget(age, 1, 4);
	layout->addWidget(age_line, 1, 5);
	layout->addWidget(link, 1, 6);
	layout->addWidget(link_line, 1, 7);
	layout->addWidget(new_breed, 2, 0);
	layout->addWidget(new_breed_line, 2, 1);
	layout->addWidget(new_name, 2, 2);
	layout->addWidget(new_name_line, 2, 3);
	layout->addWidget(new_age, 2, 4);
	layout->addWidget(new_age_line, 2, 5);
	layout->addWidget(new_link, 2, 6);
	layout->addWidget(new_link_line, 2, 7);
	layout->addWidget(add_button, 3, 0, 1, 2);
	layout->addWidget(delete_button, 3, 2, 1, 2);
	layout->addWidget(update_button, 3, 4, 1, 2);
	layout->addWidget(help_button, 3, 6, 1, 2);
	layout->addWidget(undo_button, 4, 0, 1, 4);
	layout->addWidget(redo_button, 4, 4, 1, 4);
	layout->addWidget(dog_list, 5, 0, 1, 8);
	layout->addWidget(chart_view, 6, 0, 4, 8);
	this->setLayout(layout);
	
	QObject::connect(add_button, &QPushButton::clicked, this, &AdminGUI::addDog);
	QObject::connect(delete_button, &QPushButton::clicked, this, &AdminGUI::deleteDog);
	QObject::connect(update_button, &QPushButton::clicked, this, &AdminGUI::updateDog);
	QObject::connect(help_button, &QPushButton::clicked, this, &AdminGUI::showHelp);
	QObject::connect(dog_list, &QListWidget::itemSelectionChanged, this, &AdminGUI::loadSelection);
	QObject::connect(undo_button, &QPushButton::clicked, this, &AdminGUI::undo);
	QObject::connect(redo_button, &QPushButton::clicked, this, &AdminGUI::redo);
	this->populateDogChart();
}

AdminGUI::~AdminGUI()
{
}

void AdminGUI::populateDogList()
{
	this->dog_list->clear();
	for (const Dog& current_dog : this->service.getAllDogs())
	{
		std::stringstream stream;
		stream << current_dog;
		QListWidgetItem* new_item = new QListWidgetItem(QString::fromStdString(stream.str()), this->dog_list);
	}
}

void AdminGUI::populateDogChart()
{
	int maximum = 0;
	dog_breeds.erase(dog_breeds.begin(), dog_breeds.end());
	for (std::string dog_breed : this->service.getDogBreeds())
	{
		int current_dog_number = this->service.getNumberOfDogsWithBreed(dog_breed);
		if (maximum < current_dog_number)
			maximum = current_dog_number;
		*bar_set << current_dog_number;
		dog_breeds << dog_breed.c_str();
	}
	axisX->append(dog_breeds);
	this->chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);
	axisY->setRange(0, maximum);
	axisY->setTickCount(maximum+1);
	this->chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);
	series->append(bar_set);
	this->chart->addSeries(series);
}

void AdminGUI::updateDogChart()
{
	std::set<std::string> breeds = this->service.getDogBreeds();
	QStringList current_breeds = this->axisX->categories();
	for (std::string breed : breeds)
	{
		if (!current_breeds.contains(QString::fromStdString(breed)))
			this->axisX->append(QString::fromStdString(breed));
	}
	for (QString breed : current_breeds)
		if (breeds.find(breed.toStdString()) == breeds.end())
			this->axisX->remove(breed);
	this->series->attachAxis(this->axisX);
	if (series->remove(bar_set))
	{
		this->bar_set = new QBarSet("Number of dogs", this->chart);
		int maximum = 0;
		for (std::string dog_breed : this->service.getDogBreeds())
		{
			int current_dog_number = this->service.getNumberOfDogsWithBreed(dog_breed);
			if (maximum < current_dog_number)
				maximum = current_dog_number;
			*bar_set << current_dog_number;
		}
		this->axisY->setRange(0, maximum);
		this->axisY->setTickCount(maximum + 1);
		this->series->attachAxis(this->axisY);
		this->series->append(this->bar_set);
	}
}

void AdminGUI::clearInputs()
{
	this->breed_line->clear();
	this->name_line->clear();
	this->age_line->clear();
	this->link_line->clear();
	this->new_breed_line->clear();
	this->new_name_line->clear();
	this->new_age_line->clear();
	this->new_link_line->clear();
}


void AdminGUI::addDog()
{
	try
	{
		std::string dog_str = this->breed_line->text().toStdString() + ", " + this->name_line->text().toStdString() + ", " + this->age_line->text().toStdString() + ", " +
			this->link_line->text().toStdString();
		std::stringstream read_stream(dog_str);
		Dog read_dog;
		read_stream >> read_dog;
		this->service.addElement(read_dog);
		this->populateDogList();
		this->updateDogChart();
	}
	catch (DogException de)
	{
		QMessageBox error_box;
		error_box.setText(de.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
	catch (RepoException re)
	{
		QMessageBox error_box;
		error_box.setText(re.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
	this->clearInputs();
}

void AdminGUI::deleteDog()
{
	try
	{
		this->service.removeElement(this->breed_line->text().toStdString(), this->name_line->text().toStdString());
		this->populateDogList();
		this->updateDogChart();
	}
	catch (RepoException re)
	{
		QMessageBox error_box;
		error_box.setText(re.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
	this->clearInputs();

}

void AdminGUI::updateDog()
{
	try
	{
		std::string dog_str = this->new_breed_line->text().toStdString() + ", " + this->new_name_line->text().toStdString() + ", " + this->new_age_line->text().toStdString() + ", "
			+ this->new_link_line->text().toStdString();
		std::stringstream read_stream(dog_str);
		Dog read_dog;
		read_stream >> read_dog;
		this->service.updateElement(this->breed_line->text().toStdString(), this->name_line->text().toStdString(), read_dog);
		this->populateDogList();
		this->updateDogChart();
	}
	catch (DogException de)
	{
		QMessageBox error_box;
		error_box.setText(de.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
	catch (RepoException re)
	{
		QMessageBox error_box;
		error_box.setText(re.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
	this->clearInputs();
}

void AdminGUI::undo()
{
	try
	{
		this->service.undo();
		this->populateDogList();
		this->updateDogChart();
	}
	catch (UndoRedoException ure)
	{
		QMessageBox error_box;
		error_box.setText(ure.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
}

void AdminGUI::redo()
{
	try
	{
		this->service.redo();
		this->populateDogList();
		this->updateDogChart();
	}
	catch (UndoRedoException ure)
	{
		QMessageBox error_box;
		error_box.setText(ure.what());
		error_box.setWindowTitle("Error!");
		error_box.exec();
	}
}

void AdminGUI::showHelp()
{
	QMessageBox help_box;
	help_box.setWindowTitle("Help");
	std::string help_string = "Write the necessary data for the wanted operation before pressing the corresponding button!\n";
	help_string += "For add, the breed, name, age and link are necessary.\n";
	help_string += "For delete, the breed and name are necessary\n";
	help_string += "For update, the breed, name and all of the new attributes are necessary.\n";
	help_string += "The list and the graph update automatically after every operation.";
	help_box.setText(QString::fromStdString(help_string));
	help_box.exec();
}

void AdminGUI::loadSelection()
{
	std::string current_string = this->dog_list->currentItem()->text().toStdString();
	std::stringstream strstream(current_string);
	std::string current_split;
	std::getline(strstream, current_split, ',');
	this->breed_line->setText(QString::fromStdString(current_split));
	std::getline(strstream, current_split, ',');
	current_split.erase(current_split.begin());
	this->name_line->setText(QString::fromStdString(current_split));
	std::getline(strstream, current_split, ',');
	current_split.erase(current_split.begin());
	this->age_line->setText(QString::fromStdString(current_split));
	std::getline(strstream, current_split, ',');
	current_split.erase(current_split.begin());
	this->link_line->setText(QString::fromStdString(current_split));
}

void AdminGUI::keyPressEvent(QKeyEvent* event)
{
	if (event->matches(QKeySequence::Undo))
		this->undo();
	else if (event->matches(QKeySequence::Redo))
		this->redo();
	QWidget::keyPressEvent(event);
}
