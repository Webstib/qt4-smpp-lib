#ifndef SMPP_BIND_TRANSCEIVER_H
#define SMPP_BIND_TRANSCEIVER_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT BindTransceiver : public Header {
  QString system_id;
  QString password;
  QString system_type;
  quint8 interface_version;
  quint8 addr_ton;
  quint8 addr_npi;
  QString address_range;

public:

  BindTransceiver(
    quint32 sequence_number = 0,
    const QString &system_id = QString(),
    const QString &password = QString(),
    const QString &system_type = QString(),
    quint8 interface_version = 0,
    quint8 addr_ton = 0,
    quint8 addr_npi = 0,
    const QString &address_range = QString());

  BindTransceiver(const Header &p);

  BindTransceiver(const BindTransceiver &p);

  void setSystemId(const QString &v);

  void setPassword(const QString &v);

  void setSystemType(const QString &v);

  void setInterfaceVersion(quint8 v);

  void setAddrTon(quint8 v);

  void setAddrNpi(quint8 v);

  void setAddressRange(const QString &v);

  QString getSystemId() const;

  QString getPassword() const;

  QString getSystemType() const;

  quint8 getInterfaceVersion() const;

  quint8 getAddrTon() const;

  quint8 getAddrNpi() const;

  QString getAddressRange() const;

  quint32 size() const;

  BindTransceiver &operator =(const BindTransceiver &p);

  bool operator ==(const BindTransceiver &p) const;

  bool operator !=(const BindTransceiver &p) const;

  static const quint32 MIN_LENGTH = 23;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_BIND_TRANSCEIVER_H
