#include "progress.h"

void Progress::setValue(int value)
{
   if (value != m_value) {
     m_value = value;
     emit valueChanged(value);
   }
}

void Progress::setMsg(QString msg)
{
   if (m_msg != msg) {
     m_msg = msg;
     emit msgChanged(msg);
   }
}

void Progress::setModel(myTableModel *model)
{
   if (m_model != model) {
     m_model = model;
     emit modelChanged(model);
   }
}
