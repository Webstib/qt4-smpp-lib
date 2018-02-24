#ifndef SMPP_SME_MULTI_ADDRESS_H
#define SMPP_SME_MULTI_ADDRESS_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_multi_destination_address_base.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT SmeMultiAddress : public MultiDestinationAddressBase {
  quint8 dest_addr_ton;
  quint8 dest_addr_npi;
  QString destination_addr;

public:

  SmeMultiAddress(quint8 dest_addr_ton = 0,
                  quint8 dest_addr_npi = 0,
                  const QString &destination_addr = QString());

  SmeMultiAddress(const SmeMultiAddress &p);

  void setDestAddrTon(quint8 v);

  void setDestAddrNpi(quint8 v);

  void setDestinationAddr(const QString &v);

  quint8 getDestAddrTon() const;

  quint8 getDestAddrNpi() const;

  QString getDestinationAddr() const;

  quint8 getDestFlag() const;

  quint32 size() const;

  SmeMultiAddress &operator =(const SmeMultiAddress &p);

  bool operator ==(const SmeMultiAddress &p) const;

  bool operator !=(const SmeMultiAddress &p) const;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_SME_MULTI_ADDRESS_H
