#ifndef SMPP_REPLACE_SM_H
#define SMPP_REPLACE_SM_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT ReplaceSm : public Header {
  QString message_id;
  quint8 source_addr_ton;
  quint8 source_addr_npi;
  QString source_addr;
  QString schedule_delivery_time;
  QString validity_period;
  quint8 registered_delivery;
  quint8 sm_default_msg_id;
  quint8 sm_length;
  QByteArray short_message;

public:

  ReplaceSm(quint32 sequence_number = 0,
            const QString &message_id = QString(),
            quint8 source_addr_ton = 0,
            quint8 source_addr_npi = 0,
            const QString &source_addr = QString(),
            const QString &schedule_delivery_time = QString(),
            const QString &validity_period = QString(),
            quint8 registered_delivery = 0,
            quint8 sm_default_msg_id = 0,
            quint8 sm_length = 0,
            const QByteArray &short_message = QByteArray());

  ReplaceSm(const Header &p);

  ReplaceSm(const ReplaceSm &p);

  void setMessageId(const QString &v);

  void setSourceAddrTon(quint8 v);

  void setSourceAddrNpi(quint8 v);

  void setSourceAddr(const QString &v);

  void setScheduleDeliveryTime(const QString &v);

  void setValidityPeriod(const QString &v);

  void setRegisteredDelivery(quint8 v);

  void setSmDefaultMsgId(quint8 v);

  void setSmLength(quint8 v);

  void setShortMessage(const QByteArray &v);

  QString getMessageId() const;

  quint8 getSourceAddrTon() const;

  quint8 getSourceAddrNpi() const;

  QString getSourceAddr() const;

  QString getScheduleDeliveryTime() const;

  QString getValidityPeriod() const;

  quint8 getRegisteredDelivery() const;

  quint8 getSmDefaultMsgId() const;

  quint8 getSmLength() const;

  QByteArray getShortMessage() const;

  quint32 size() const;

  ReplaceSm &operator =(const ReplaceSm &p);

  bool operator ==(const ReplaceSm &p) const;

  bool operator !=(const ReplaceSm &p) const;

  static const quint32 MIN_LENGTH = 26;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_REPLACE_SM_H
