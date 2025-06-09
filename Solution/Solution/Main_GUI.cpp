#include "Main_GUI.h"
#include <QtWidgets/qlabel.h>
#include <QGridLayout>
#include <QDesktopWidget>
#include "AdminGUI.h"
#include "UserGUI.h"

Main_GUI::Main_GUI(AdminService& admin, UserService& csv, UserService& html, QWidget* parent)
    : QMainWindow(parent), admin_service{ admin }, csv_service{ csv }, html_service{ html }
{
    
    ui.setupUi(this);
    this->setWindowTitle("Keep calm and adopt a pet");
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.25);
    main_widget = new QWidget();
    select_label = new QLabel("Select the mode you want to start the aplication in:", this);
    admin_button = new QPushButton("Admin mode", this);
    user_csv_button = new QPushButton("User mode, CSV file", this);
    user_html_button = new QPushButton("User mode, HTML file", this);
    layout = new QGridLayout(this);
    layout->addWidget(select_label, 0, 0, 1, 3, Qt::AlignHCenter);
    layout->addWidget(admin_button, 1, 0);
    layout->addWidget(user_csv_button, 1, 2);
    layout->addWidget(user_html_button, 1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    main_widget->setLayout(layout);
    this->setCentralWidget(main_widget);
    QObject::connect(admin_button, &QPushButton::clicked, this, &Main_GUI::changeToAdmin);
    QObject::connect(user_csv_button, &QPushButton::clicked, this, &Main_GUI::changeToCSVUser);
    QObject::connect(user_html_button, &QPushButton::clicked, this, &Main_GUI::changeToHTMLUser);
}

Main_GUI::~Main_GUI(){}

void Main_GUI::setMainWidget(QWidget* new_main)
{
    this->resize(new_main->size());
    this->main_widget = new_main;
    this->setCentralWidget(this->main_widget);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

void Main_GUI::changeToAdmin()
{
    AdminGUI* admin_gui = new AdminGUI{ "dog_list.txt", this->admin_service, this };
    this->setMainWidget(admin_gui);
}

void Main_GUI::changeToCSVUser()
{
    UserGUI* user_gui = new UserGUI{ this->csv_service, this };
    this->setMainWidget(user_gui);
}

void Main_GUI::changeToHTMLUser()
{
    UserGUI* user_gui = new UserGUI{ this->html_service, this };
    this->setMainWidget(user_gui);
}
