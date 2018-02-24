#ifndef BINARY_DECODER_H
#define BINARY_DECODER_H

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

namespace decoders {

class SMPP_EXPORT BinaryDecoder {
  QByteArray data;
  int pos;

public:

  BinaryDecoder(const QByteArray &data);

  void addBody(const QByteArray &data);

  bool decode(quint8 &p);

  bool decode(quint16 &p);

  bool decode(quint32 &p);

  bool decode(QString &p);

  bool decode(QByteArray &p, int length);

  bool decode(smpp::pdu::SmeMultiAddress &p);

  bool decode(smpp::pdu::DistributionListAddress &p);

  bool decode(smpp::pdu::MultiDestinationAddresses &p, int length);

  bool decode(smpp::pdu::UnsuccessSme &p);

  bool decode(smpp::pdu::Tlv &p);

  bool decode(smpp::pdu::TlvFields &p);

  bool decode(smpp::pdu::Header &p);

  bool decode(smpp::pdu::BindTransmitter &p, bool decode_header = false);

  bool decode(smpp::pdu::BindTransmitterResp &p, bool decode_header = false);

  bool decode(smpp::pdu::BindReceiver &p, bool decode_header = false);

  bool decode(smpp::pdu::BindReceiverResp &p, bool decode_header = false);

  bool decode(smpp::pdu::BindTransceiver &p, bool decode_header = false);

  bool decode(smpp::pdu::BindTransceiverResp &p, bool decode_header = false);

  bool decode(smpp::pdu::SubmitSm &p, bool decode_header = false);

  bool decode(smpp::pdu::SubmitSmResp &p, bool decode_header = false);

  bool decode(smpp::pdu::SubmitMulti &p, bool decode_header = false);

  bool decode(smpp::pdu::SubmitMultiResp &p, bool decode_header = false);

  bool decode(smpp::pdu::DeliverSm &p, bool decode_header = false);

  bool decode(smpp::pdu::DeliverSmResp &p, bool decode_header = false);

  bool decode(smpp::pdu::DataSm &p, bool decode_header = false);

  bool decode(smpp::pdu::DataSmResp &p, bool decode_header = false);

  bool decode(smpp::pdu::QuerySm &p, bool decode_header = false);

  bool decode(smpp::pdu::QuerySmResp &p, bool decode_header = false);

  bool decode(smpp::pdu::CancelSm &p, bool decode_header = false);

  bool decode(smpp::pdu::ReplaceSm &p, bool decode_header = false);

  bool decode(smpp::pdu::AlertNotification &p, bool decode_header = false);
};

} // namespace decoders

} // namespace smpp


#endif // BINARY_DECODER_H
