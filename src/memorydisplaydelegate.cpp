#include "memorydisplaydelegate.h"

MemoryDisplayDelegate::MemoryDisplayDelegate(QWidget *parent)
    : QStyledItemDelegate(parent) {}

QString MemoryDisplayDelegate::displayText(const QVariant &value,
                                           const QLocale & /*locale*/) const {

  // check for invalid memory - hacky solution. Check for values that can
  // be converted to a qstring larger than any valid value could be
  QString ret = qvariant_cast<QString>(value);
  if (ret.size() > 4) {
    return "---";
  }

  QString retVal;
  switch (m_displayType) {
  case displayTypeN::Hex:
    retVal.setNum(value.toUInt(), 16);
    break;
  case displayTypeN::Unsigned:
    retVal.setNum(value.toUInt());
    break;
  case displayTypeN::Decimal:
    retVal.setNum(value.toInt());
    break;
  case displayTypeN::ASCII:
    retVal = QChar(value.toInt());
    break;
  case displayTypeN::Binary:
    retVal.setNum(value.toUInt(), 2);
  }
  return retVal;
}

void MemoryDisplayDelegate::setDisplayType(const QString &type) {
  // Given a display type "type", sets validators for the input.
  auto iter = displayTypes.find(type);
  if (iter != displayTypes.end()) {
    m_displayType = iter.value();
  }
}
