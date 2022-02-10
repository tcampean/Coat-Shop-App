//
// Created by Tudor on 5/29/2021.
//

#include "CoatTableModel.h"
#include <QFont>
#include <QBrush>

CoatTableModel::CoatTableModel(WriteRepository &shoppingCart, QObject *parent) : QAbstractTableModel{parent},shoppingCart {shoppingCart} {

}
CoatTableModel::~CoatTableModel() {

}

int CoatTableModel::rowCount(const QModelIndex &parent) const {
    int coats = this->shoppingCart.coats.size();
    return coats;
}

int CoatTableModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant CoatTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    std::vector<Coat> coats = this->shoppingCart.coats;
    if(row == coats.size())
        return QVariant();
    Coat c = coats[row];
    if(role == Qt::DisplayRole) {
        switch (column) {
            case 0:
                return QString::fromStdString(c.getSize());
            case 1:
                return QString::fromStdString(c.getColour());
            case 2:
                return QString::fromStdString(to_string(c.getPrice()));
            case 3:
                return QString::fromStdString(to_string(c.getQuantity()));
            case 4:
                return QString::fromStdString(c.getPhoto());
            default:
                break;
        }
    }
        if(role == Qt::FontRole)
        {
            QFont font("Times",15,10,true);
            font.setItalic(false);
            return font;
        }
        if(role == Qt::BackgroundRole)
        {
            if(row%2==1)
            {
                return QBrush{QColor{0,250,154}};

            }
        }
    return QVariant();
}

QVariant CoatTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section) {
                case 0:
                    return QString{"Size"};
                case 1:
                    return QString{"Colour"};
                case 2:
                    return QString{"Price"};
                case 3:
                    return QString{"Quantity"};
                case 4:
                    return QString{"Link"};
                default:
                    break;

            }
        }
    }
    if(role == Qt::FontRole)
    {
        QFont font("Times",15,10,true);
        font.setItalic(false);
        font.setBold(true);
        return font;
    }
    return QVariant();
}

void CoatTableModel::update() {
    emit dataChanged(index(0,0),index(rowCount()-1,columnCount()-1));
    this->beginResetModel();
    this->endResetModel();
}