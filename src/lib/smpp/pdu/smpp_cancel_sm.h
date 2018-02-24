#ifndef SMPP_CANCEL_SM_H
#define SMPP_CANCEL_SM_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT CancelSm : public Header {
  QString service_type;
  QString message_id;
  quint8 source_addr_ton;
  quint8 source_addr_npi;
  QString source_addr;
  quint8 dest_addr_ton;
  quint8 dest_addr_npi;
  QString destination_addr;

public:

  CancelSm(quint32 sequence_number = 0,
           const QString &service_type = QString(),
           const QString &message_id = QString(),
           quint8 source_addr_ton = 0,
           quint8 source_addr_npi = 0,
           const QString &source_addr = QString(),
           quint8 dest_addr_ton = 0,
           quint8 dest_addr_npi = 0,
           const QString &destination_addr = QString());

  CancelSm(const Header &p);

  CancelSm(const CancelSm &p);

  void setServiceType(const QString &v);

  void setMessageId(const QString &v);

  void setSourceAddrTon(quint8 v);

  void setSourceAddrNpi(quint8 v);

  void setSourceAddr(const QString &v);

  void setDestAddrTon(quint8 v);

  void setDestAddrNpi(quint8 v);

  void setDestinationAddr(const QString &v);

  QString getServiceType() const;

  QString getMessageId() const;

  quint8 getSourceAddrTon() const;

  quint8 getSourceAddrNpi() const;

  QString getSourceAddr() const;

  quint8 getDestAddrTon() const;

  quint8 getDestAddrNpi() const;

  QString getDestinationAddr() const;

  quint32 size() const;

  CancelSm &operator =(const CancelSm &p);

  bool operator ==(const CancelSm &p) const;

  bool operator !=(const CancelSm &p) const;

  static const quint32 MIN_LENGTH = 24;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_CANCEL_SM_H
