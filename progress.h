#ifndef PROGRESS_H
#define PROGRESS_H

#include <QObject>
#include "mytablemodel.h"

class Progress : public QObject
{
   Q_OBJECT

public:
   Progress() { m_value = 0; m_msg = ""; m_model = new myTableModel; }

   int value() const { return m_value; }
   QString msg() const { return m_msg; }
   myTableModel *model() const { return m_model; }

public slots:
   void setValue(int value);
   void setMsg(QString msg);
   void setModel(myTableModel* model);

signals:
   void valueChanged(int newValue);
   void msgChanged(QString msg);
   void modelChanged(myTableModel* model);

private:
   int m_value;
   QString m_msg;
   myTableModel *m_model;
};

#endif // PROGRESS_H
