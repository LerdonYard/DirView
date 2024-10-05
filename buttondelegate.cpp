#include "buttondelegate.h"
#include <QPainter>
#include <QEvent>
#include <sizesystemmodel.h>
#include <QApplication>
#include <QPushButton>

void ButtonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}

void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        bool isPressed = index.data(Qt::UserRole).toBool();
        if((static_cast<const SizeSystemModel*>(index.model()))->isDir(index)){
            if(!isPressed){
            QPushButton button;
           button.setText("Обновить");
            button.resize(option.rect.size());
            QPixmap pixmap(button.size());
            button.render(&pixmap);
            painter->drawPixmap(option.rect, pixmap);
            } else painter->drawText(option.rect, Qt::AlignCenter, formatSize(recursiveDirSize((static_cast<const SizeSystemModel*>(index.model()))->filePath(index))));
        }
        else{
            QStyledItemDelegate::paint(painter, option, index);
        }
}

bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index){
    if(event->type() == QEvent::MouseButtonRelease && static_cast<SizeSystemModel*>(model)->isDir(index) && !model->data(index, Qt::UserRole).toBool()){
        return model->setData(index, true, Qt::UserRole);
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

qint64 ButtonDelegate::recursiveDirSize(QString root_dir) const {
    qint64 size = 0;
    QDir dir(root_dir);
    QDir::Filters fileFilters = QDir::Files|QDir::System|QDir::Hidden;
    for(QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        size+= fi.size();
    }
    QDir::Filters dirFilters = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;
    for(QString childDirPath : dir.entryList(dirFilters))
        size+= recursiveDirSize(root_dir + QDir::separator() + childDirPath);
    return size;
}

QString ButtonDelegate::formatSize(qint64 size) const{
    QStringList units = {"байт", "KiB", "MiB", "GiB", "TiB"};
    int i;
    double outputSize = size;
    for(i=0; i<units.size()-1; i++) {
        if(outputSize<1024) break;
        outputSize= outputSize/1024;
    }
    return QString("%0 %1").arg(outputSize, 0, 'f', 2).arg(units[i]);
}
