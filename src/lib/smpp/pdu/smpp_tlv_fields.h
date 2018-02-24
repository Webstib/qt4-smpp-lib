#ifndef SMPP_TLV_FIELDS_H
#define SMPP_TLV_FIELDS_H

#include <QtCore/QList>
#include "smpp/pdu/smpp_tlv.h"

namespace smpp {

namespace pdu {

typedef QList<smpp::pdu::Tlv *> TlvList;

class SMPP_EXPORT TlvFields {

  void copy(const TlvList &p);

public:
  TlvFields();

  TlvFields(const TlvFields &p);

  void add(const Tlv &tlv);

  const TlvList &getList() const;

  TlvList find(const quint16 &tag) const;

  void remove(const quint16 &tag);

  void clear();

  quint32 size() const;

  TlvFields &operator =(const TlvFields &p);

  bool operator ==(const TlvFields &p) const;

  bool operator !=(const TlvFields &p) const;

protected:
  TlvList tlv_list;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_TLV_FIELDS_H
