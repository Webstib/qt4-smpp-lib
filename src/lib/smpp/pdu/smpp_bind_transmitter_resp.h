#ifndef SMPP_BIND_TRANSMITTER_RESP_H
#define SMPP_BIND_TRANSMITTER_RESP_H

#include "smpp/pdu/smpp_header.h"
#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT BindTransmitterResp : public Header, public TlvFields {
  QString system_id;

public:

  BindTransmitterResp(quint32 command_status = 0,
                      quint32 sequence_number = 0,
                      const QString &system_id = QString());

  BindTransmitterResp(const Header &p);

  BindTransmitterResp(const BindTransmitterResp &p);

  void setSystemId(const QString &p);

  QString getSystemId() const;

  quint32 size() const;

  BindTransmitterResp &operator =(const BindTransmitterResp &p);

  bool operator ==(const BindTransmitterResp &p) const;

  bool operator !=(const BindTransmitterResp &p) const;

  const static quint32 MIN_LENGTH = 17;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_BIND_TRANSMITTER_RESP_H
