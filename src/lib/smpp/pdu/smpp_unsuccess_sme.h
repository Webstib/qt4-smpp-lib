#ifndef SMPP_UNSUCCESS_SME_H
#define SMPP_UNSUCCESS_SME_H

#include <QtCore/QString>
#include "smpp/smpp_global.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT UnsuccessSme {
  quint8 dest_addr_ton;
  quint8 dest_addr_npi;
  QString destination_addr;
  quint32 error_status_code;

public:

  UnsuccessSme(quint8 dest_addr_ton = 0,
               quint8 dest_addr_npi = 0,
               const QString &destination_addr = QString(),
               quint32 error_status_code = 0);

  UnsuccessSme(const UnsuccessSme &p);

  void setDestAddrTon(quint8 v);

  void setDestAddrNpi(quint8 v);

  void setDestinationAddr(const QString &v);

  void setErrorStatusCode(quint32 v);

  quint8 getDestAddrTon() const;

  quint8 getDestAddrNpi() const;

  QString getDestinationAddr() const;

  quint32 getErrorStatusCode() const;

  quint32 size() const;

  UnsuccessSme &operator =(const UnsuccessSme &p);

  bool operator ==(const UnsuccessSme &p) const;

  bool operator !=(const UnsuccessSme &p) const;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_UNSUCCESS_SME_H
