#ifndef SMPP_BIND_RECEIVER_RESP_H
#define SMPP_BIND_RECEIVER_RESP_H

#include "smpp/pdu/smpp_header.h"
#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT BindReceiverResp : public Header, public TlvFields {
  QString system_id;

public:

  BindReceiverResp(quint32 command_status = 0,
                   quint32 sequence_number = 0,
                   const QString &system_id = QString());

  BindReceiverResp(const Header &p);

  BindReceiverResp(const BindReceiverResp &p);

  void setSystemId(const QString &p);

  QString getSystemId() const;

  quint32 size() const;

  BindReceiverResp &operator =(const BindReceiverResp &p);

  bool operator ==(const BindReceiverResp &p) const;

  bool operator !=(const BindReceiverResp &p) const;

  const static quint32 MIN_LENGTH = 17;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_BIND_RECEIVER_RESP_H
