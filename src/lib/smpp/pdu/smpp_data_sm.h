#ifndef SMPP_DATA_SM_H
#define SMPP_DATA_SM_H

#include "smpp/pdu/smpp_header.h"
#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT DataSm : public Header, public TlvFields {
  QString service_type;
  quint8 source_addr_ton;
  quint8 source_addr_npi;
  QString source_addr;
  quint8 dest_addr_ton;
  quint8 dest_addr_npi;
  QString destination_addr;
  quint8 esm_class;
  quint8 registered_delivery;
  quint8 data_coding;

public:

  DataSm(quint32 sequence_number = 0,
         const QString &service_type = QString(),
         quint8 source_addr_ton = 0,
         quint8 source_addr_npi = 0,
         const QString &source_addr = QString(),
         quint8 dest_addr_ton = 0,
         quint8 dest_addr_npi = 0,
         const QString &destination_addr = QString(),
         quint8 esm_class = 0,
         quint8 registered_delivery = 0,
         quint8 data_coding = 0);

  DataSm(const Header &p);

  DataSm(const DataSm &p);

  void setServiceType(const QString &v);

  void setSourceAddrTon(quint8 v);

  void setSourceAddrNpi(quint8 v);

  void setSourceAddr(const QString &v);

  void setDestAddrTon(quint8 v);

  void setDestAddrNpi(quint8 v);

  void setDestinationAddr(const QString &v);

  void setEsmClass(quint8 v);

  void setRegisteredDelivery(quint8 v);

  void setDataCoding(quint8 v);

  QString getServiceType() const;

  quint8 getSourceAddrTon() const;

  quint8 getSourceAddrNpi() const;

  QString getSourceAddr() const;

  quint8 getDestAddrTon() const;

  quint8 getDestAddrNpi() const;

  QString getDestinationAddr() const;

  quint8 getEsmClass() const;

  quint8 getRegisteredDelivery() const;

  quint8 getDataCoding() const;

  quint32 size() const;

  DataSm &operator =(const DataSm &p);

  bool operator ==(const DataSm &p) const;

  bool operator !=(const DataSm &p) const;

  static const quint32 MIN_LENGTH = 26;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_DATA_SM_H
