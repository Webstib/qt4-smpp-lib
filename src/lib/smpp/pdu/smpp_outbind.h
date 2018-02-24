#ifndef SMPP_OUTBIND_H
#define SMPP_OUTBIND_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT Outbind : public Header {
  QString system_id;
  QString password;

public:

  Outbind(quint32 sequence_number = 0,
          const QString &system_id = QString(),
          const QString &password = QString());

  Outbind(const Header &p);

  Outbind(const Outbind &p);

  void setSystemId(const QString &v);

  void setPassword(const QString &v);

  QString getSystemId() const;

  QString getPassword() const;

  quint32 size() const;

  Outbind &operator =(const Outbind &p);

  bool operator ==(const Outbind &p) const;

  bool operator !=(const Outbind &p) const;

  static const quint32 MIN_LENGTH = 18;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_OUTBIND_H
