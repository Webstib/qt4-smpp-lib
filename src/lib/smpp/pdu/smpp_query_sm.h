#ifndef SMPP_QUERY_SM_H
#define SMPP_QUERY_SM_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT QuerySm : public Header {
  QString message_id;
  quint8 source_addr_ton;
  quint8 source_addr_npi;
  QString source_addr;

public:

  QuerySm(quint32 sequence_number = 0,
          const QString &message_id = QString(),
          quint8 source_addr_ton = 0,
          quint8 source_addr_npi = 0,
          const QString &source_addr = QString());

  QuerySm(const Header &p);

  QuerySm(const QuerySm &p);

  void setMessageId(const QString &p);

  void setSourceAddrTon(quint8 v);

  void setSourceAddrNpi(quint8 v);

  void setSourceAddr(const QString &v);

  QString getMessageId() const;

  quint8 getSourceAddrTon() const;

  quint8 getSourceAddrNpi() const;

  QString getSourceAddr() const;

  quint32 size() const;

  QuerySm &operator =(const QuerySm &p);

  bool operator ==(const QuerySm &p) const;

  bool operator !=(const QuerySm &p) const;

  const static quint32 MIN_LENGTH = 20;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_QUERY_SM_H
