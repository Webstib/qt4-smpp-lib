#ifndef SMPP_SUBMIT_MULTI_RESP_H
#define SMPP_SUBMIT_MULTI_RESP_H

#include <QtCore/QList>
#include "smpp/pdu/smpp_unsuccess_sme.h"
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT SubmitMultiResp : public Header {
  QString message_id;
  quint8 no_unsuccess;
  QList<UnsuccessSme> unsuccess_smes;

public:

  SubmitMultiResp(
    quint32 command_status = 0,
    quint32 sequence_number = 0,
    const QString &message_id = QString(),
    quint8 no_unsuccess = 0,
    const QList<UnsuccessSme> &unsuccess_smes = QList<UnsuccessSme>());

  SubmitMultiResp(const Header &p);

  SubmitMultiResp(const SubmitMultiResp &p);

  void setMessageId(const QString &v);

  void setNoUnsuccess(quint8 v);

  void add(const UnsuccessSme &p);

  QString getMessageId() const;

  quint8 getNoUnsuccess() const;

  const QList<UnsuccessSme> &getUnsuccessSmes() const;

  void remove(const UnsuccessSme &p);

  quint32 size() const;

  SubmitMultiResp &operator =(const SubmitMultiResp &p);

  bool operator ==(const SubmitMultiResp &p) const;

  bool operator !=(const SubmitMultiResp &p) const;

  const static quint32 MIN_LENGTH = 18;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_SUBMIT_MULTI_RESP_H
