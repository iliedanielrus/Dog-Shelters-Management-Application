#include "PictureDelegate.h"
#include <QPainter>

PictureDelegate::PictureDelegate(QWidget *parent): QStyledItemDelegate{parent} {}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() != 3)
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    QString dog_picture = index.model()->data(index.siblingAtColumn(0), Qt::EditRole).toString() + "-" + index.model()->data(index.siblingAtColumn(1), Qt::EditRole).toString();
    QPixmap picture("Pictures/" + dog_picture);
    if(!picture.isNull())
        painter->drawPixmap(option.rect, picture);
    else
        QStyledItemDelegate::paint(painter, option, index);
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() == 3)
        return QSize(32, 100);
    return QStyledItemDelegate::sizeHint(option, index);
}
