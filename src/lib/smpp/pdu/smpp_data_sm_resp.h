#ifndef SMPP_DATA_SM_RESP_H
#define SMPP_DATA_SM_RESP_H

#include "smpp/pdu/smpp_header.h"
#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT DataSmResp : public Header, public TlvFields {
  QString message_id;

public:

  DataSmResp(quint32 command_status = 0,
             quint32 sequence_number = 0,
             const QString &message_id = QString());

  DataSmResp(const Header &p);

  DataSmResp(const DataSmResp &p);

  void setMessageId(const QString &p);

  QString getMessageId() const;

  quint32 size() const;

  DataSmResp &operator =(const DataSmResp &p);

  bool operator ==(const DataSmResp &p) const;

  bool operator !=(const DataSmResp &p) const;

  const static quint32 MIN_LENGTH = 17;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_DATA_SM_RESP_H
