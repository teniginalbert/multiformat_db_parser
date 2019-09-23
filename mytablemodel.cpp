#include "mytablemodel.h"

int myTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return xmls.count();
}

int myTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 7;
}

QVariant myTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Vertical) {
        return section;
    }

    switch (section) {
    case NAME:
        return "name";
    case TEXTEDITOR:
        return "texteditor";
    case FILEFORMATS:
        return "fileformats";
    case ENCODING:
        return "encoding";
    case HASINTELLISENSE:
        return "hasintellisense";
    case HASPLUGINS:
        return "hasplugins";
    case CANCOMPILE:
        return "cancompile";
    }

    return QVariant();
}

QVariant myTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() ||
            xmls.count() <= index.row() ||
           (role != Qt::DisplayRole && role != Qt::EditRole)
       ) {
           return QVariant();
       }

       return xmls[index.row()][Column(index.column())];
}

Qt::ItemFlags myTableModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if(index.isValid()) {
            flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void myTableModel::appendRecord(const QString& name,
                                const QString& texteditor,
                                const QString& fileformats,
                                const QString& encoding,
                                const bool& hasintellisense,
                                const bool& hasplugins,
                                const bool& cancompile) {
    XmlData xml;
    xml[NAME] = name;
    xml[TEXTEDITOR] = texteditor;
    xml[FILEFORMATS] = fileformats;
    xml[ENCODING] = encoding;
    xml[HASINTELLISENSE] = hasintellisense;
    xml[HASPLUGINS] = hasplugins;
    xml[CANCOMPILE] = cancompile;

    int row = xmls.count();
    beginInsertRows(QModelIndex(), row, row);
    xmls.append(xml);
    endInsertRows();
}

bool myTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if(!index.isValid() || role != Qt::EditRole || xmls.count() <= index.row()) {
        return false;
    }

    xmls[index.row() ][Column( index.column() )] = value;
    emit dataChanged(index, index);

    return true;
}

void myTableModel::removeSelected(int row) {
    int i = 0;
    Xmls::iterator j = xmls.begin();
    while(j != xmls.end()) {
        if(i == row) {
            beginRemoveRows(QModelIndex(), i, i);
            j = xmls.erase(j);
            endRemoveRows();
            ++i;
        } else {
            ++i;
            ++j;
        }
    }
}

myTableModel::myTableModel(QObject* parent) : QAbstractTableModel(parent)  {

}
