#include "sizesystemmodel.h"

Qt::ItemFlags SizeSystemModel::flags(const QModelIndex &index) const {
    if(this->isDir(index) && index.column() == 1 && index.isValid() && buttonState[index] != true)
    return QFileSystemModel::flags(index) | Qt::ItemIsEditable;
    return QFileSystemModel::flags(index);
}

bool SizeSystemModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(role == Qt::UserRole && value.toBool() == true) {
        buttonState[index] = true;
        return true;
    }

    return QFileSystemModel::setData(index, value, role);
}

QVariant SizeSystemModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()) return QFileSystemModel::data(index, role);
    if(buttonState.contains(index))return buttonState[index];
    return QFileSystemModel::data(index, role);
}
