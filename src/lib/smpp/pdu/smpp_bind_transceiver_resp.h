#ifndef SMPP_BIND_TRANSCEIVER_RESP_H
#define SMPP_BIND_TRANSCEIVER_RESP_H

#include "smpp/pdu/smpp_header.h"
#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT BindTransceiverResp : public Header, public TlvFields {
  QString system_id;

public:

  BindTransceiverResp(quint32 command_status = 0,
                      quint32 sequence_number = 0,
                      const QString &system_id = QString());

  BindTransceiverResp(const Header &p);

  BindTransceiverResp(const BindTransceiverResp &p);

  void setSystemId(const QString &p);

  QString getSystemId() const;

  quint32 size() const;

  BindTransceiverResp &operator =(const BindTransceiverResp &p);

  bool operator ==(const BindTransceiverResp &p) const;

  bool operator !=(const BindTransceiverResp &p) const;

  const static quint32 MIN_LENGTH = 17;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_BIND_TRANSCEIVER_RESP_H
