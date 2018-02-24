#ifndef SMPP_BINARY_ENCODER_H
#define SMPP_BINARY_ENCODER_H

#include "smpp/pdu/smpp_bind_transmitter.h"
#include "smpp/pdu/smpp_bind_transmitter_resp.h"
#include "smpp/pdu/smpp_bind_receiver.h"
#include "smpp/pdu/smpp_bind_receiver_resp.h"
#include "smpp/pdu/smpp_bind_transceiver.h"
#include "smpp/pdu/smpp_bind_transceiver_resp.h"
#include "smpp/pdu/smpp_outbind.h"
#include "smpp/pdu/smpp_unbind.h"
#include "smpp/pdu/smpp_unbind_resp.h"
#include "smpp/pdu/smpp_generic_nack.h"
#include "smpp/pdu/smpp_submit_sm.h"
#include "smpp/pdu/smpp_submit_sm_resp.h"
#include "smpp/pdu/smpp_submit_multi.h"
#include "smpp/pdu/smpp_submit_multi_resp.h"
#include "smpp/pdu/smpp_deliver_sm.h"
#include "smpp/pdu/smpp_deliver_sm_resp.h"
#include "smpp/pdu/smpp_data_sm.h"
#include "smpp/pdu/smpp_data_sm_resp.h"
#include "smpp/pdu/smpp_query_sm.h"
#include "smpp/pdu/smpp_query_sm_resp.h"
#include "smpp/pdu/smpp_cancel_sm.h"
#include "smpp/pdu/smpp_cancel_sm_resp.h"
#include "smpp/pdu/smpp_replace_sm.h"
#include "smpp/pdu/smpp_replace_sm_resp.h"
#include "smpp/pdu/smpp_enquire_link.h"
#include "smpp/pdu/smpp_enquire_link_resp.h"
#include "smpp/pdu/smpp_alert_notification.h"

namespace smpp {

namespace encoders {

class SMPP_EXPORT BinaryEncoder {
  QByteArray data;
  int pos;

public:

  BinaryEncoder();

  void resize(int size);

  operator QByteArray() const;

  const QByteArray &getBuff() const;

  BinaryEncoder &operator <<(const quint8 &p);

  BinaryEncoder &operator <<(const quint16 &p);

  BinaryEncoder &operator <<(const quint32 &p);

  BinaryEncoder &operator <<(const QString &p);

  BinaryEncoder &operator <<(const QByteArray &p);

  BinaryEncoder &operator <<(const smpp::pdu::MultiDestinationAddresses &p);

  BinaryEncoder &operator <<(const smpp::pdu::DistributionListAddress &p);

  BinaryEncoder &operator <<(smpp::pdu::MultiDestinationAddressBase *p);

  BinaryEncoder &operator <<(const smpp::pdu::SmeMultiAddress &p);

  BinaryEncoder &operator <<(const smpp::pdu::UnsuccessSme &p);

  BinaryEncoder &operator <<(const smpp::pdu::Tlv &p);

  BinaryEncoder &operator <<(const smpp::pdu::TlvFields &p);

  BinaryEncoder &operator <<(const smpp::pdu::Header &p);

  BinaryEncoder &operator <<(const smpp::pdu::BindTransmitter &p);

  BinaryEncoder &operator <<(const smpp::pdu::BindTransmitterResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::BindReceiver &p);

  BinaryEncoder &operator <<(const smpp::pdu::BindReceiverResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::BindTransceiver &p);

  BinaryEncoder &operator <<(const smpp::pdu::BindTransceiverResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::Outbind &p);

  BinaryEncoder &operator <<(const smpp::pdu::Unbind &p);

  BinaryEncoder &operator <<(const smpp::pdu::UnbindResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::GenericNack &p);

  BinaryEncoder &operator <<(const smpp::pdu::SubmitSm &p);

  BinaryEncoder &operator <<(const smpp::pdu::SubmitSmResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::SubmitMulti &p);

  BinaryEncoder &operator <<(const smpp::pdu::SubmitMultiResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::DeliverSm &p);

  BinaryEncoder &operator <<(const smpp::pdu::DeliverSmResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::DataSm &p);

  BinaryEncoder &operator <<(const smpp::pdu::DataSmResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::QuerySm &p);

  BinaryEncoder &operator <<(const smpp::pdu::QuerySmResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::CancelSm &p);

  BinaryEncoder &operator <<(const smpp::pdu::CancelSmResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::ReplaceSm &p);

  BinaryEncoder &operator <<(const smpp::pdu::ReplaceSmResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::EnquireLink &p);

  BinaryEncoder &operator <<(const smpp::pdu::EnquireLinkResp &p);

  BinaryEncoder &operator <<(const smpp::pdu::AlertNotification &p);
};

} // namespace encoders

} // namespace smpp

#endif // SMPP_BINARY_ENCODER_H
