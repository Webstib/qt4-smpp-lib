#ifndef SMPP_TLV_H
#define SMPP_TLV_H

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include "smpp/smpp_global.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT Tlv {
  quint16 tag;
  QByteArray value;

public:

  Tlv(quint16 tag = 0, QByteArray value = QByteArray());

  Tlv(const Tlv &p);

  quint16 getTag() const;

  quint16 getLength() const;

  QByteArray getValue() const;

  bool getValue(QString &p) const;

  bool getValue(quint8 &p) const;

  bool getValue(quint16 &p) const;

  bool getValue(quint32 &p) const;

  void setTag(quint16 p);

  void setValue(const QByteArray &p);

  void setValue(const QString &p);

  void setValue(quint8 p);

  void setValue(quint16 p);

  void setValue(quint32 p);

  quint32 size() const;

  Tlv &operator =(const Tlv &p);

  bool operator ==(const Tlv &p) const;

  bool operator !=(const Tlv &p) const;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_TLV_H
