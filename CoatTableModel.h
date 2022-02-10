//
// Created by Tudor on 5/29/2021.
//

#ifndef A10_912_CAMPEAN_TUDOR_ALEXANDRU_1_COATTABLEMODEL_H
#define A10_912_CAMPEAN_TUDOR_ALEXANDRU_1_COATTABLEMODEL_H

#include <QAbstractTableModel>
#include <WriteRepository.h>

class CoatTableModel: public QAbstractTableModel
{
public:
    WriteRepository shoppingCart;
public:
    CoatTableModel(WriteRepository &shoppingCart, QObject* parent = NULL);
    ~CoatTableModel();
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex &index,int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void update();

};

#endif //A10_912_CAMPEAN_TUDOR_ALEXANDRU_1_COATTABLEMODEL_H
