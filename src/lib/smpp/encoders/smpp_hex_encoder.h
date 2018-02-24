#ifndef SMPP_HEX_ENCODER_H
#define SMPP_HEX_ENCODER_H

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

class SMPP_EXPORT HexEncoder {
  QString data;
  const static char hex[];

public:
  HexEncoder();

  operator QString() const;

  QString byte_2_str(const char *bytes, quint32 size);

  HexEncoder &operator <<(quint8 p);

  HexEncoder &operator <<(quint16 p);

  HexEncoder &operator <<(quint32 p);

  HexEncoder &operator <<(const QString &p);

  HexEncoder &operator <<(const QByteArray &p);

  HexEncoder &operator <<(const smpp::pdu::MultiDestinationAddresses &p);

  HexEncoder &operator <<(const smpp::pdu::DistributionListAddress &p);

  HexEncoder &operator <<(smpp::pdu::MultiDestinationAddressBase *p);

  HexEncoder &operator <<(const smpp::pdu::SmeMultiAddress &p);

  HexEncoder &operator <<(const smpp::pdu::UnsuccessSme &p);

  HexEncoder &operator <<(const smpp::pdu::Tlv &p);

  HexEncoder &operator <<(const smpp::pdu::TlvFields &p);

  HexEncoder &operator <<(const smpp::pdu::Header &p);

  HexEncoder &operator <<(const smpp::pdu::BindTransmitter &p);

  HexEncoder &operator <<(const smpp::pdu::BindTransmitterResp &p);

  HexEncoder &operator <<(const smpp::pdu::BindReceiver &p);

  HexEncoder &operator <<(const smpp::pdu::BindReceiverResp &p);

  HexEncoder &operator <<(const smpp::pdu::BindTransceiver &p);

  HexEncoder &operator <<(const smpp::pdu::BindTransceiverResp &p);

  HexEncoder &operator <<(const smpp::pdu::Outbind &p);

  HexEncoder &operator <<(const smpp::pdu::Unbind &p);

  HexEncoder &operator <<(const smpp::pdu::UnbindResp &p);

  HexEncoder &operator <<(const smpp::pdu::GenericNack &p);

  HexEncoder &operator <<(const smpp::pdu::SubmitSm &p);

  HexEncoder &operator <<(const smpp::pdu::SubmitSmResp &p);

  HexEncoder &operator <<(const smpp::pdu::SubmitMulti &p);

  HexEncoder &operator <<(const smpp::pdu::SubmitMultiResp &p);

  HexEncoder &operator <<(const smpp::pdu::DeliverSm &p);

  HexEncoder &operator <<(const smpp::pdu::DeliverSmResp &p);

  HexEncoder &operator <<(const smpp::pdu::DataSm &p);

  HexEncoder &operator <<(const smpp::pdu::DataSmResp &p);

  HexEncoder &operator <<(const smpp::pdu::QuerySm &p);

  HexEncoder &operator <<(const smpp::pdu::QuerySmResp &p);

  HexEncoder &operator <<(const smpp::pdu::CancelSm &p);

  HexEncoder &operator <<(const smpp::pdu::CancelSmResp &p);

  HexEncoder &operator <<(const smpp::pdu::ReplaceSm &p);

  HexEncoder &operator <<(const smpp::pdu::ReplaceSmResp &p);

  HexEncoder &operator <<(const smpp::pdu::EnquireLink &p);

  HexEncoder &operator <<(const smpp::pdu::EnquireLinkResp &p);

  HexEncoder &operator <<(const smpp::pdu::AlertNotification &p);
};

} // namespace encoders

} // namespace smpp

#endif // SMPP_HEX_ENCODER_H
