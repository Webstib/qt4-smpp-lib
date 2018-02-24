#ifndef SMPP_DELIVER_SM_RESP_H
#define SMPP_DELIVER_SM_RESP_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT DeliverSmResp : public Header {
  QString message_id;

public:

  DeliverSmResp(quint32 command_status = 0,
                quint32 sequence_number = 0,
                const QString &message_id = QString());

  DeliverSmResp(const Header &p);

  DeliverSmResp(const DeliverSmResp &p);

  void setMessageId(const QString &p);

  QString getMessageId() const;

  quint32 size() const;

  DeliverSmResp &operator =(const DeliverSmResp &p);

  bool operator ==(const DeliverSmResp &p) const;

  bool operator !=(const DeliverSmResp &p) const;

  const static quint32 MIN_LENGTH = 17;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_DELIVER_SM_RESP_H
