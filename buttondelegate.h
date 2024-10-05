#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>


class ButtonDelegate : public QStyledItemDelegate

{
Q_OBJECT
private:
    qint64 recursiveDirSize(QString root_dir) const;
    QString formatSize(qint64 size) const;
public:

 ButtonDelegate(QObject *parent) : QStyledItemDelegate(parent){}

 void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

 void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

 bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;


};

#endif // BUTTONDELEGATE_H
