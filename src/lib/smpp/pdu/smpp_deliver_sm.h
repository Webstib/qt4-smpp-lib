#ifndef SMPP_DELIVER_SM_H
#define SMPP_DELIVER_SM_H

#include "smpp/pdu/smpp_header.h"
#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT DeliverSm : public Header, public TlvFields {
  QString service_type;
  quint8 source_addr_ton;
  quint8 source_addr_npi;
  QString source_addr;
  quint8 dest_addr_ton;
  quint8 dest_addr_npi;
  QString destination_addr;
  quint8 esm_class;
  quint8 protocol_id;
  quint8 priority_flag;
  QString schedule_delivery_time;
  QString validity_period;
  quint8 registered_delivery;
  quint8 replace_if_present_flag;
  quint8 data_coding;
  quint8 sm_default_msg_id;
  quint8 sm_length;
  QByteArray short_message;

public:

  DeliverSm(quint32 sequence_number = 0,
            const QString &service_type = QString(),
            quint8 source_addr_ton = 0,
            quint8 source_addr_npi = 0,
            const QString &source_addr = QString(),
            quint8 dest_addr_ton = 0,
            quint8 dest_addr_npi = 0,
            const QString &destination_addr = QString(),
            quint8 esm_class = 0,
            quint8 protocol_id = 0,
            quint8 priority_flag = 0,
            const QString &schedule_delivery_time = QString(),
            const QString &validity_period = QString(),
            quint8 registered_delivery = 0,
            quint8 replace_if_present_flag = 0,
            quint8 data_coding = 0,
            quint8 sm_default_msg_id = 0,
            quint8 sm_length = 0,
            const QByteArray &short_message = QByteArray());

  DeliverSm(const Header &p);

  DeliverSm(const DeliverSm &p);

  void setServiceType(const QString &v);

  void setSourceAddrTon(quint8 v);

  void setSourceAddrNpi(quint8 v);

  void setSourceAddr(const QString &v);

  void setDestAddrTon(quint8 v);

  void setDestAddrNpi(quint8 v);

  void setDestinationAddr(const QString &v);

  void setEsmClass(quint8 v);

  void setProtocolId(quint8 v);

  void setPriorityFlag(quint8 v);

  void setScheduleDeliveryTime(const QString &v);

  void setValidityPeriod(const QString &v);

  void setRegisteredDelivery(quint8 v);

  void setReplaceIfPresentFlag(quint8 v);

  void setDataCoding(quint8 v);

  void setSmDefaultMsgId(quint8 v);

  void setSmLength(quint8 v);

  void setShortMessage(const QByteArray &v);

  QString getServiceType() const;

  quint8 getSourceAddrTon() const;

  quint8 getSourceAddrNpi() const;

  QString getSourceAddr() const;

  quint8 getDestAddrTon() const;

  quint8 getDestAddrNpi() const;

  QString getDestinationAddr() const;

  quint8 getEsmClass() const;

  quint8 getProtocolId() const;

  quint8 getPriorityFlag() const;

  QString getScheduleDeliveryTime() const;

  QString getValidityPeriod() const;

  quint8 getRegisteredDelivery() const;

  quint8 getReplaceIfPresentFlag() const;

  quint8 getDataCoding() const;

  quint8 getSmDefaultMsgId() const;

  quint8 getSmLength() const;

  QByteArray getShortMessage() const;

  quint32 size() const;

  DeliverSm &operator =(const DeliverSm &p);

  bool operator ==(const DeliverSm &p) const;

  bool operator !=(const DeliverSm &p) const;

  static const quint32 MIN_LENGTH = 33;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_DELIVER_SM_H
