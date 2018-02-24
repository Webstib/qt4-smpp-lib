#ifndef SMPP_QUERY_SM_RESP_H
#define SMPP_QUERY_SM_RESP_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT QuerySmResp : public Header {
  QString message_id;
  QString final_date;
  quint8 message_state;
  quint8 error_code;

public:

  QuerySmResp(quint32 command_status = 0,
              quint32 sequence_number = 0,
              const QString &message_id = QString(),
              const QString &final_date = QString(),
              quint8 message_state = 0,
              quint8 error_code = 0);

  QuerySmResp(const Header &p);

  QuerySmResp(const QuerySmResp &p);

  void setMessageId(const QString &v);

  void setFinalDate(const QString &v);

  void setMessageState(quint8 v);

  void setErrorCode(quint8 v);

  QString getMessageId() const;

  QString getFinalDate() const;

  quint8 getMessageState() const;

  quint8 getErrorCode() const;

  quint32 size() const;

  QuerySmResp &operator =(const QuerySmResp &p);

  bool operator ==(const QuerySmResp &p) const;

  bool operator !=(const QuerySmResp &p) const;

  const static quint32 MIN_LENGTH = 20;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_QUERY_SM_RESP_H
