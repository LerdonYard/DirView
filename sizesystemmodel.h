#ifndef SIZESYSTEMMODEL_H
#define SIZESYSTEMMODEL_H

#include <QObject>
#include <QWidget>
#include <QFileSystemModel>
#include <QMap>

class SizeSystemModel : public QFileSystemModel{
    Q_OBJECT
private:
    QMap<QModelIndex, bool> buttonState;
    public:
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

};

#endif // SIZESYSTEMMODEL_H
