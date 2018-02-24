#include "smpp/decoders/smpp_binary_decoder.h"
#include "smpp/smpp_transform_functions.h"

namespace smpp {

namespace decoders {

using namespace pdu;

BinaryDecoder::BinaryDecoder(const QByteArray &data) : data(data), pos(0) {

}

void BinaryDecoder::addBody(const QByteArray &data) {
  this->data += data;
}

bool BinaryDecoder::decode(quint8 &p) {
  if(pos + 1 > data.size())
    return false;

  p = data[pos++];

  return true;
}

bool BinaryDecoder::decode(quint16 &p) {
  if(pos + 2 > data.size())
    return false;

  quint16 v(0);
  char *c_pt(reinterpret_cast<char *>(&v));
  *(c_pt++) = data[pos++];
  *c_pt = data[pos++];
  p = ntoh16(v);

  return true;
}

bool BinaryDecoder::decode(quint32 &p) {
  if(pos + 4 > data.size()) return false;

  quint32 v(0);
  char *c_pt(reinterpret_cast<char *>(&v));
  *(c_pt++) = data[pos++];
  *(c_pt++) = data[pos++];
  *(c_pt++) = data[pos++];
  *c_pt = data[pos++];
  p = ntoh32(v);

  return true;
}

bool BinaryDecoder::decode(QString &p) {
  int temp_pos(pos);
  int data_size(data.size());
  while(1) {
    if(temp_pos >= data_size)
      return false;
    if(data[temp_pos++] == '\0')
      break;
  }
  p.clear();
  temp_pos -= pos + 1;
  p.resize(temp_pos);
  for(int i = 0; i < temp_pos; i++)
    p[i] = data[pos++];
  pos++;
  return true;
}

bool BinaryDecoder::decode(QByteArray &p, int length) {
  if((pos + length) > data.size())
    return false;

  p.resize(length);

  if(length > 0) {
    p = data.mid(pos, length);
    pos += length;
  }

  return true;
}

bool BinaryDecoder::decode(smpp::pdu::SmeMultiAddress &p) {
  quint8 ton;
  bool ok(decode(ton));
  if(!ok) return ok;

  quint8 npi;
  ok = decode(npi);
  if(!ok) return ok;

  QString addr;
  ok = decode(addr);
  if(!ok) return ok;

  p.setDestAddrTon(ton);
  p.setDestAddrNpi(npi);
  p.setDestinationAddr(addr);

  return ok;
}

bool BinaryDecoder::decode(smpp::pdu::DistributionListAddress &p) {
  QString dl_name;
  if(!decode(dl_name))
    return false;

  p.setDlName(dl_name);

  return true;
}

bool BinaryDecoder::decode(MultiDestinationAddresses &p, int length) {
  bool ok(true);

  for(int i = 0; i < length; i++) {
    quint8 dest_flag;
    bool ok(decode(dest_flag));

    if(!ok) return ok;

    switch(dest_flag) {
      case 0x02: {
        SmeMultiAddress sme_multi_addr;

        ok = decode(sme_multi_addr);

        if(!ok) return ok;

        p.add(sme_multi_addr);
        break;
      }
      case 0x01: {
        DistributionListAddress distrib_addr;

        ok = decode(distrib_addr);

        if(!ok) return ok;

        p.add(distrib_addr);
        break;
      }
      default:
        return false;
    }
  }

  return ok;
}

bool BinaryDecoder::decode(UnsuccessSme &p) {
  quint8 ton;
  bool ok(decode(ton));
  if(!ok) return ok;

  quint8 npi;
  ok = decode(npi);
  if(!ok) return ok;

  QString addr;
  ok = decode(addr);
  if(!ok) return ok;

  quint32 error_status_code;
  ok = decode(error_status_code);
  if(!ok) return ok;

  p.setDestAddrTon(ton);
  p.setDestAddrNpi(npi);
  p.setDestinationAddr(addr);
  p.setErrorStatusCode(error_status_code);

  return ok;
}

bool BinaryDecoder::decode(Tlv &p) {
  quint16 tag;
  bool ok(decode(tag));

  if(!ok) return ok;

  quint16 length;

  ok = decode(length);

  if(!ok) return ok;

  QByteArray value;

  ok = decode(value, length);

  if(!ok) return ok;

  p.setTag(tag);
  p.setValue(value);

  return ok;
}

bool BinaryDecoder::decode(TlvFields &p) {
  bool ok(true);

  p.clear();

  while(pos < data.size()) {
    Tlv tlv;
    ok = decode(tlv);
    if(!ok) return ok;
    p.add(tlv);
  }

  return ok;
}

bool BinaryDecoder::decode(Header &p) {
  quint32 command_length;
  bool ok(decode(command_length));

  if(!ok) return ok;

  quint32 command_id;

  ok = decode(command_id);

  if(!ok) return ok;

  quint32 command_status;

  ok = decode(command_status);

  if(!ok) return ok;

  quint32 sequence_number;

  ok = decode(sequence_number);

  if(!ok) return ok;

  p.setCommandLength(command_length);
  p.setCommandId(command_id);
  p.setCommandStatus(command_status);
  p.setSequenceNumber(sequence_number);

  return ok;
}

bool BinaryDecoder::decode(BindTransmitter &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString system_id;
  ok = decode(system_id);
  if(!ok) return ok;

  QString password;
  ok = decode(password);
  if(!ok) return ok;

  QString system_type;
  ok = decode(system_type);
  if(!ok) return ok;

  quint8 interface_version;
  ok = decode(interface_version);
  if(!ok) return ok;

  quint8 addr_ton;
  ok = decode(addr_ton);
  if(!ok) return ok;

  quint8 addr_npi;
  ok = decode(addr_npi);
  if(!ok) return ok;

  QString address_range;
  ok = decode(address_range);
  if(!ok) return ok;

  p.setSystemId(system_id);
  p.setPassword(password);
  p.setSystemType(system_type);
  p.setInterfaceVersion(interface_version);
  p.setAddrTon(addr_ton);
  p.setAddrNpi(addr_npi);
  p.setAddressRange(address_range);

  return ok;
}

bool BinaryDecoder::decode(BindTransmitterResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString system_id;
  ok = decode(system_id);
  if(!ok) return ok;

  p.setSystemId(system_id);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(BindReceiver &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString system_id;
  ok = decode(system_id);
  if(!ok) return ok;

  QString password;
  ok = decode(password);
  if(!ok) return ok;

  QString system_type;
  ok = decode(system_type);
  if(!ok) return ok;

  quint8 interface_version;
  ok = decode(interface_version);
  if(!ok) return ok;

  quint8 addr_ton;
  ok = decode(addr_ton);
  if(!ok) return ok;

  quint8 addr_npi;
  ok = decode(addr_npi);
  if(!ok) return ok;

  QString address_range;
  ok = decode(address_range);
  if(!ok) return ok;

  p.setSystemId(system_id);
  p.setPassword(password);
  p.setSystemType(system_type);
  p.setInterfaceVersion(interface_version);
  p.setAddrTon(addr_ton);
  p.setAddrNpi(addr_npi);
  p.setAddressRange(address_range);

  return ok;
}

bool BinaryDecoder::decode(BindReceiverResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString system_id;
  ok = decode(system_id);
  if(!ok) return ok;

  p.setSystemId(system_id);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(BindTransceiver &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString system_id;
  ok = decode(system_id);
  if(!ok) return ok;

  QString password;
  ok = decode(password);
  if(!ok) return ok;

  QString system_type;
  ok = decode(system_type);
  if(!ok) return ok;

  quint8 interface_version;
  ok = decode(interface_version);
  if(!ok) return ok;

  quint8 addr_ton;
  ok = decode(addr_ton);
  if(!ok) return ok;

  quint8 addr_npi;
  ok = decode(addr_npi);
  if(!ok) return ok;

  QString address_range;
  ok = decode(address_range);
  if(!ok) return ok;

  p.setSystemId(system_id);
  p.setPassword(password);
  p.setSystemType(system_type);
  p.setInterfaceVersion(interface_version);
  p.setAddrTon(addr_ton);
  p.setAddrNpi(addr_npi);
  p.setAddressRange(address_range);

  return ok;
}

bool BinaryDecoder::decode(BindTransceiverResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString system_id;
  ok = decode(system_id);
  if(!ok) return ok;

  p.setSystemId(system_id);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(SubmitSm &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString service_type;
  ok = decode(service_type);
  if(!ok) return ok;

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  quint8 dest_addr_ton;
  ok = decode(dest_addr_ton);
  if(!ok) return ok;

  quint8 dest_addr_npi;
  ok = decode(dest_addr_npi);
  if(!ok) return ok;

  QString dest_addr;
  ok = decode(dest_addr);
  if(!ok) return ok;

  quint8 esm_class;
  ok = decode(esm_class);
  if(!ok) return ok;

  quint8 protocol_id;
  ok = decode(protocol_id);
  if(!ok) return ok;

  quint8 priority_flag;
  ok = decode(priority_flag);
  if(!ok) return ok;

  QString schedule_delivery_time;
  ok = decode(schedule_delivery_time);
  if(!ok) return ok;

  QString validity_period;
  ok = decode(validity_period);
  if(!ok) return ok;

  quint8 registered_delivery;
  ok = decode(registered_delivery);
  if(!ok) return ok;

  quint8 replace_if_present_flag;
  ok = decode(replace_if_present_flag);
  if(!ok) return ok;

  quint8 data_coding;
  ok = decode(data_coding);
  if(!ok) return ok;

  quint8 sm_default_msg_id;
  ok = decode(sm_default_msg_id);
  if(!ok) return ok;

  quint8 sm_length;
  ok = decode(sm_length);
  if(!ok) return ok;

  QByteArray short_message;
  ok = decode(short_message, sm_length);
  if(!ok) return ok;

  p.setServiceType(service_type);
  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);
  p.setDestAddrTon(dest_addr_ton);
  p.setDestAddrNpi(dest_addr_npi);
  p.setDestinationAddr(dest_addr);
  p.setEsmClass(esm_class);
  p.setProtocolId(protocol_id);
  p.setPriorityFlag(priority_flag);
  p.setScheduleDeliveryTime(schedule_delivery_time);
  p.setValidityPeriod(validity_period);
  p.setRegisteredDelivery(registered_delivery);
  p.setReplaceIfPresentFlag(replace_if_present_flag);
  p.setDataCoding(data_coding);
  p.setSmDefaultMsgId(sm_default_msg_id);
  p.setSmLength(sm_length);
  p.setShortMessage(short_message);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(SubmitSmResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  p.setMessageId(message_id);

  return ok;
}

bool BinaryDecoder::decode(SubmitMulti &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString service_type;
  ok = decode(service_type);
  if(!ok) return ok;

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  quint8 num_of_dests;
  ok = decode(num_of_dests);
  if(!ok) return ok;

  MultiDestinationAddresses destination_addrs;
  ok = decode(destination_addrs, num_of_dests);
  if(!ok) return ok;

  quint8 esm_class;
  ok = decode(esm_class);
  if(!ok) return ok;

  quint8 protocol_id;
  ok = decode(protocol_id);
  if(!ok) return ok;

  quint8 priority_flag;
  ok = decode(priority_flag);
  if(!ok) return ok;

  QString schedule_delivery_time;
  ok = decode(schedule_delivery_time);
  if(!ok) return ok;

  QString validity_period;
  ok = decode(validity_period);
  if(!ok) return ok;

  quint8 registered_delivery;
  ok = decode(registered_delivery);
  if(!ok) return ok;

  quint8 replace_if_present_flag;
  ok = decode(replace_if_present_flag);
  if(!ok) return ok;

  quint8 data_coding;
  ok = decode(data_coding);
  if(!ok) return ok;

  quint8 sm_default_msg_id;
  ok = decode(sm_default_msg_id);
  if(!ok) return ok;

  quint8 sm_length;
  ok = decode(sm_length);
  if(!ok) return ok;

  QByteArray short_message;
  ok = decode(short_message, sm_length);
  if(!ok) return ok;

  p.setServiceType(service_type);
  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);
  p.setNumberOfDests(num_of_dests);
  p.setDestAddresses(destination_addrs);
  p.setEsmClass(esm_class);
  p.setProtocolId(protocol_id);
  p.setPriorityFlag(priority_flag);
  p.setScheduleDeliveryTime(schedule_delivery_time);
  p.setValidityPeriod(validity_period);
  p.setRegisteredDelivery(registered_delivery);
  p.setReplaceIfPresentFlag(replace_if_present_flag);
  p.setDataCoding(data_coding);
  p.setSmDefaultMsgId(sm_default_msg_id);
  p.setSmLength(sm_length);
  p.setShortMessage(short_message);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(SubmitMultiResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  quint8 no_unsuccess;
  ok = decode(no_unsuccess);
  if(!ok) return ok;

  for(int i = 0; i < no_unsuccess; i++) {
    UnsuccessSme unsuccess_sme;
    ok = decode(unsuccess_sme);
    if(!ok) return ok;
    p.add(unsuccess_sme);
  }

  return ok;
}

bool BinaryDecoder::decode(DeliverSm &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString service_type;
  ok = decode(service_type);
  if(!ok) return ok;

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  quint8 dest_addr_ton;
  ok = decode(dest_addr_ton);
  if(!ok) return ok;

  quint8 dest_addr_npi;
  ok = decode(dest_addr_npi);
  if(!ok) return ok;

  QString dest_addr;
  ok = decode(dest_addr);
  if(!ok) return ok;

  quint8 esm_class;
  ok = decode(esm_class);
  if(!ok) return ok;

  quint8 protocol_id;
  ok = decode(protocol_id);
  if(!ok) return ok;

  quint8 priority_flag;
  ok = decode(priority_flag);
  if(!ok) return ok;

  QString schedule_delivery_time;
  ok = decode(schedule_delivery_time);
  if(!ok) return ok;

  QString validity_period;
  ok = decode(validity_period);
  if(!ok) return ok;

  quint8 registered_delivery;
  ok = decode(registered_delivery);
  if(!ok) return ok;

  quint8 replace_if_present_flag;
  ok = decode(replace_if_present_flag);
  if(!ok) return ok;

  quint8 data_coding;
  ok = decode(data_coding);
  if(!ok) return ok;

  quint8 sm_default_msg_id;
  ok = decode(sm_default_msg_id);
  if(!ok) return ok;

  quint8 sm_length;
  ok = decode(sm_length);
  if(!ok) return ok;

  QByteArray short_message;
  ok = decode(short_message, sm_length);
  if(!ok) return ok;

  p.setServiceType(service_type);
  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);
  p.setDestAddrTon(dest_addr_ton);
  p.setDestAddrNpi(dest_addr_npi);
  p.setDestinationAddr(dest_addr);
  p.setEsmClass(esm_class);
  p.setProtocolId(protocol_id);
  p.setPriorityFlag(priority_flag);
  p.setScheduleDeliveryTime(schedule_delivery_time);
  p.setValidityPeriod(validity_period);
  p.setRegisteredDelivery(registered_delivery);
  p.setReplaceIfPresentFlag(replace_if_present_flag);
  p.setDataCoding(data_coding);
  p.setSmDefaultMsgId(sm_default_msg_id);
  p.setSmLength(sm_length);
  p.setShortMessage(short_message);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(DeliverSmResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  p.setMessageId(message_id);

  return ok;
}

bool BinaryDecoder::decode(DataSm &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString service_type;
  ok = decode(service_type);
  if(!ok) return ok;

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  quint8 dest_addr_ton;
  ok = decode(dest_addr_ton);
  if(!ok) return ok;

  quint8 dest_addr_npi;
  ok = decode(dest_addr_npi);
  if(!ok) return ok;

  QString dest_addr;
  ok = decode(dest_addr);
  if(!ok) return ok;

  quint8 esm_class;
  ok = decode(esm_class);
  if(!ok) return ok;

  quint8 registered_delivery;
  ok = decode(registered_delivery);
  if(!ok) return ok;

  quint8 data_coding;
  ok = decode(data_coding);
  if(!ok) return ok;

  p.setServiceType(service_type);
  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);
  p.setDestAddrTon(dest_addr_ton);
  p.setDestAddrNpi(dest_addr_npi);
  p.setDestinationAddr(dest_addr);
  p.setEsmClass(esm_class);
  p.setRegisteredDelivery(registered_delivery);
  p.setDataCoding(data_coding);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(DataSmResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  p.setMessageId(message_id);

  ok = decode((TlvFields &)p);

  return ok;
}

bool BinaryDecoder::decode(QuerySm &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  p.setMessageId(message_id);
  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);

  return ok;
}

bool BinaryDecoder::decode(QuerySmResp &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  QString final_date;
  ok = decode(final_date);
  if(!ok) return ok;

  quint8 message_state;
  ok = decode(message_state);
  if(!ok) return ok;

  quint8 error_code;
  ok = decode(error_code);
  if(!ok) return ok;

  p.setMessageId(message_id);
  p.setFinalDate(final_date);
  p.setMessageState(message_state);
  p.setErrorCode(error_code);

  return ok;
}

bool BinaryDecoder::decode(CancelSm &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString service_type;
  ok = decode(service_type);
  if(!ok) return ok;

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  quint8 dest_addr_ton;
  ok = decode(dest_addr_ton);
  if(!ok) return ok;

  quint8 dest_addr_npi;
  ok = decode(dest_addr_npi);
  if(!ok) return ok;

  QString dest_addr;
  ok = decode(dest_addr);
  if(!ok) return ok;

  p.setServiceType(service_type);
  p.setMessageId(message_id);
  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);
  p.setDestAddrTon(dest_addr_ton);
  p.setDestAddrNpi(dest_addr_npi);
  p.setDestinationAddr(dest_addr);

  return ok;
}

bool BinaryDecoder::decode(ReplaceSm &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  QString message_id;
  ok = decode(message_id);
  if(!ok) return ok;

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  QString schedule_delivery_time;
  ok = decode(schedule_delivery_time);
  if(!ok) return ok;

  QString validity_period;
  ok = decode(validity_period);
  if(!ok) return ok;

  quint8 registered_delivery;
  ok = decode(registered_delivery);
  if(!ok) return ok;

  quint8 sm_default_msg_id;
  ok = decode(sm_default_msg_id);
  if(!ok) return ok;

  quint8 sm_length;
  ok = decode(sm_length);
  if(!ok) return ok;

  QByteArray short_message;
  ok = decode(short_message, sm_length);
  if(!ok) return ok;

  p.setMessageId(message_id);
  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);
  p.setScheduleDeliveryTime(schedule_delivery_time);
  p.setValidityPeriod(validity_period);
  p.setRegisteredDelivery(registered_delivery);
  p.setSmDefaultMsgId(sm_default_msg_id);
  p.setSmLength(sm_length);
  p.setShortMessage(short_message);

  return ok;
}

bool BinaryDecoder::decode(AlertNotification &p, bool decode_header) {
  bool ok(true);
  if(decode_header) {
    ok = decode((Header &)p);
    if(!ok) return ok;
  }

  quint8 source_addr_ton;
  ok = decode(source_addr_ton);
  if(!ok) return ok;

  quint8 source_addr_npi;
  ok = decode(source_addr_npi);
  if(!ok) return ok;

  QString source_addr;
  ok = decode(source_addr);
  if(!ok) return ok;

  quint8 esme_addr_ton;
  ok = decode(esme_addr_ton);
  if(!ok) return ok;

  quint8 esme_addr_npi;
  ok = decode(esme_addr_npi);
  if(!ok) return ok;

  QString esme_addr;
  ok = decode(esme_addr);
  if(!ok) return ok;

  p.setSourceAddrTon(source_addr_ton);
  p.setSourceAddrNpi(source_addr_npi);
  p.setSourceAddr(source_addr);
  p.setEsmeAddrTon(esme_addr_ton);
  p.setEsmeAddrNpi(esme_addr_npi);
  p.setEsmeAddr(esme_addr);

  ok = decode((TlvFields &)p);

  return ok;
}

} // namespace decoders

} // namespace smpp

