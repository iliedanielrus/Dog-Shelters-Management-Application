#pragma once
#include <QAbstractTableModel>
#include "Service/UserService.h"
class AdoptionListModel : public QAbstractTableModel
{
private:
	UserService& service;

public:

	AdoptionListModel(UserService& service);
	// Inherited via QAbstractTableModel
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void update();
};

