#include "AdoptionListModel.h"
#include <QFont>

AdoptionListModel::AdoptionListModel(UserService& service): service{service}
{
}

int AdoptionListModel::rowCount(const QModelIndex& parent) const
{
    return this->service.getAdoptedDogs().size();
}

int AdoptionListModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant AdoptionListModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();
    Dog current_dog = this->service.getAdoptedDogs()[row];
    if(role == Qt::DisplayRole || role == Qt::EditRole)
        switch (column)
        {
        case 0:
            return QString::fromStdString(current_dog.getBreed());
        case 1:
            return QString::fromStdString(current_dog.getName());
        case 2:
            return QString::number(current_dog.getAge());
        case 3:
            return QString::fromStdString(current_dog.getPhotograph());
        default:
            break;
        }
    if (role == Qt::FontRole)
    {
        QFont font("Helvetica");
        font.setItalic(false);
        return font;
    }
    return QVariant();
}

QVariant AdoptionListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
        if(orientation == Qt::Horizontal)
            switch (section)
            {
            case 0:
                return QString("Breed");
            case 1:
                return QString("Name");
            case 2:
                return QString("Age");
            case 3:
                return QString("Photography");
            default:
                break;
            }
    if (role == Qt::FontRole)
    {
        QFont font("Helvetica");
        font.setItalic(false);
        return font;
    }
    return QVariant();
}

void AdoptionListModel::update()
{
    beginResetModel();
    endResetModel();
}
