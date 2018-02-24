#ifndef SMPP_ALERT_NOTIFICATION_H
#define SMPP_ALERT_NOTIFICATION_H

#include "smpp/pdu/smpp_header.h"
#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT AlertNotification : public Header, public TlvFields {
  quint8 source_addr_ton;
  quint8 source_addr_npi;
  QString source_addr;
  quint8 esme_addr_ton;
  quint8 esme_addr_npi;
  QString esme_addr;

public:

  AlertNotification(quint32 sequence_number = 0,
                    quint8 source_addr_ton = 0,
                    quint8 source_addr_npi = 0,
                    const QString &source_addr = QString(),
                    quint8 esme_addr_ton = 0,
                    quint8 esme_addr_npi = 0,
                    const QString &esme_addr = QString());

  AlertNotification(const Header &p);

  AlertNotification(const AlertNotification &p);

  void setSourceAddrTon(quint8 v);

  void setSourceAddrNpi(quint8 v);

  void setSourceAddr(const QString &v);

  void setEsmeAddrTon(quint8 v);

  void setEsmeAddrNpi(quint8 v);

  void setEsmeAddr(const QString &v);

  quint8 getSourceAddrTon() const;

  quint8 getSourceAddrNpi() const;

  QString getSourceAddr() const;

  quint8 getEsmeAddrTon() const;

  quint8 getEsmeAddrNpi() const;

  QString getEsmeAddr() const;

  quint32 size() const;

  AlertNotification &operator =(const AlertNotification &p);

  bool operator ==(const AlertNotification &p) const;

  bool operator !=(const AlertNotification &p) const;

  static const quint32 MIN_LENGTH = 22;
};

} // namespace pdu

} // namespace smpp

#endif // ALERT_NOTIFICATION_H
