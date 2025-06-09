#include "Main_GUI.h"
#include <QDebug>
#include <QtWidgets/QApplication>
#include "Repository/TextFileRepo.h"
#include "Service/AdminService.h"
#include "Repository/CSVRepo.h"
#include "Repository/HTMLRepo.h"
#include "Service/UserService.h"

int main(int argc, char *argv[])
{
    TextFileRepository admin_repo("dog_list.txt");
    try 
    {
        admin_repo.loadFromFile();
    }
    catch (TextFileRepoException tfre)
    {
        qDebug() << tfre.what();
    }
    UndoRedoController undo_redo_controller;
    AdminService admin_service(admin_repo, undo_redo_controller);
    CSVRepository csv_repo("adoption_list.csv");
    HTMLRepository html_repo("adoption_list.html");
    FilterIterationRepo filter_repo;
    filter_repo.filterRepo(admin_repo);
    UserService html_service(admin_repo, html_repo, filter_repo, undo_redo_controller), csv_service(admin_repo, csv_repo, filter_repo, undo_redo_controller);
    QApplication a(argc, argv);
    Main_GUI w(admin_service, csv_service, html_service);
    w.show();
    return a.exec();
}
