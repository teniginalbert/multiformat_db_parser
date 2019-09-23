#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QObject>
#include <QVariant>
#include <QAbstractTableModel>

class myTableModel : public QAbstractTableModel
{
public:
    myTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void appendRecord(const QString& name,
                      const QString& texteditor,
                      const QString& fileformats,
                      const QString& encoding,
                      const bool& hasintellisense,
                      const bool& hasplugins,
                      const bool& cancompile);
public slots:
    void removeSelected(int row);

private:
    enum Column {
        NAME,
        TEXTEDITOR,
        FILEFORMATS,
        ENCODING,
        HASINTELLISENSE,
        HASPLUGINS,
        CANCOMPILE
    };

    typedef QHash <Column, QVariant> XmlData;
    typedef QList <XmlData> Xmls;
    Xmls xmls;
};

#endif // MYTABLEMODEL_H
