#ifndef SMPP_SUBMIT_SM_RESP_H
#define SMPP_SUBMIT_SM_RESP_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT SubmitSmResp : public Header {
  QString message_id;

public:

  SubmitSmResp(quint32 command_status = 0,
               quint32 sequence_number = 0,
               const QString &message_id = QString());

  SubmitSmResp(const Header &p);

  SubmitSmResp(const SubmitSmResp &p);

  void setMessageId(const QString &p);

  QString getMessageId() const;

  quint32 size() const;

  SubmitSmResp &operator =(const SubmitSmResp &p);

  bool operator ==(const SubmitSmResp &p) const;

  bool operator !=(const SubmitSmResp &p) const;

  const static quint32 MIN_LENGTH = 17;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_SUBMIT_SM_RESP_H
