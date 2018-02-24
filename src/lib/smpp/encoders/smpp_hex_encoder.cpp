#include "smpp/encoders/smpp_hex_encoder.h"
#include "smpp/smpp_transform_functions.h"

namespace smpp {

namespace encoders {

using namespace pdu;

const char HexEncoder::hex[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F'
};

HexEncoder::HexEncoder() {

}

HexEncoder::operator QString() const {
  return data;
}

QString HexEncoder::byte_2_str(const char *bytes, quint32 size) {
  QString str;
  for(quint32 i = 0; i < size; i++) {
    const char ch = bytes[i];
    str.append(hex[(ch & 0xF0) >> 4]);
    str.append(hex[ch & 0xF]);
  }
  return str;
}

HexEncoder &HexEncoder::operator <<(quint8 p) {
  quint8 v(p);
  char *c_pt(reinterpret_cast<char *>(&v));
  data += byte_2_str(c_pt, 1) + " ";
  return *this;
}

HexEncoder &HexEncoder::operator <<(quint16 p) {
  quint16 v(hton16(p));
  char *c_pt(reinterpret_cast<char *>(&v));
  data += byte_2_str(c_pt, 2) + " ";
  return *this;
}

HexEncoder &HexEncoder::operator <<(quint32 p) {
  quint32 v(hton32(p));
  char *c_pt(reinterpret_cast<char *>(&v));
  data += byte_2_str(c_pt, 4) + " ";
  return *this;
}

HexEncoder &HexEncoder::operator <<(const QString &p) {
  QByteArray ba(p.toUtf8());
  ba += '\0';
  *this << ba;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const QByteArray &p) {
  if(p.size() > 0)
    data += byte_2_str(p.data(), p.size()) + " ";
  return *this;
}

HexEncoder &HexEncoder::operator <<(const MultiDestinationAddresses &p) {
  QList<MultiDestinationAddressBase *> list(p.getAll());

  for(QList<MultiDestinationAddressBase *>::ConstIterator it = list.constBegin();
      it != list.constEnd();
      it++) {
    *this << *it;
  }

  return *this;
}

HexEncoder &HexEncoder::operator <<(const DistributionListAddress &p) {
  *this << p.getDestFlag();
  *this << p.getDlName();
  return *this;
}

HexEncoder &HexEncoder::operator <<(MultiDestinationAddressBase *p) {
  switch(p->getDestFlag()) {
    case 0x02:
      *this << *reinterpret_cast<DistributionListAddress *>(p);
      break;
    case 0x01:
      *this << *reinterpret_cast<SmeMultiAddress *>(p);
      break;
    default:
      break;
  }
  return *this;
}

HexEncoder &HexEncoder::operator <<(const SmeMultiAddress &p) {
  *this << p.getDestFlag();
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const UnsuccessSme &p) {
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  *this << p.getErrorStatusCode();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const Tlv &p) {
  *this << p.getTag();
  *this << p.getLength();
  *this << p.getValue();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const TlvFields &p) {
  TlvList list(p.getList());

  for(TlvList::ConstIterator it = list.constBegin();
      it != list.constEnd();
      it++) {
    *this << **it;
  }

  return *this;
}

HexEncoder &HexEncoder::operator <<(const Header &p) {
  *this << p.getCommandLength();
  *this << p.getCommandId();
  *this << p.getCommandStatus();
  *this << p.getSequenceNumber();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const BindTransmitter &p) {
  *this << (Header)p;
  *this << p.getSystemId();
  *this << p.getPassword();
  *this << p.getSystemType();
  *this << p.getInterfaceVersion();
  *this << p.getAddrTon();
  *this << p.getAddrNpi();
  *this << p.getAddressRange();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const BindTransmitterResp &p) {
  *this << (Header)p;
  *this << p.getSystemId();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const BindReceiver &p) {
  *this << (Header)p;
  *this << p.getSystemId();
  *this << p.getPassword();
  *this << p.getSystemType();
  *this << p.getInterfaceVersion();
  *this << p.getAddrTon();
  *this << p.getAddrNpi();
  *this << p.getAddressRange();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const BindReceiverResp &p) {
  *this << (Header)p;
  *this << p.getSystemId();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const BindTransceiver &p) {
  *this << (Header)p;
  *this << p.getSystemId();
  *this << p.getPassword();
  *this << p.getSystemType();
  *this << p.getInterfaceVersion();
  *this << p.getAddrTon();
  *this << p.getAddrNpi();
  *this << p.getAddressRange();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const BindTransceiverResp &p) {
  *this << (Header)p;
  *this << p.getSystemId();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const Outbind &p) {
  *this << (Header)p;
  *this << p.getSystemId();
  *this << p.getPassword();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const Unbind &p) {
  *this << (Header)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const UnbindResp &p) {
  *this << (Header)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const GenericNack &p) {
  *this << (Header)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const SubmitSm &p) {
  *this << (Header)p;
  *this << p.getServiceType();
  *this << p.getSourceAddrTon();
  *this << p.getSourceAddrNpi();
  *this << p.getSourceAddr();
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  *this << p.getEsmClass();
  *this << p.getProtocolId();
  *this << p.getPriorityFlag();
  *this << p.getScheduleDeliveryTime();
  *this << p.getValidityPeriod();
  *this << p.getRegisteredDelivery();
  *this << p.getReplaceIfPresentFlag();
  *this << p.getDataCoding();
  *this << p.getSmDefaultMsgId();
  *this << p.getSmLength();
  *this << p.getShortMessage();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const SubmitSmResp &p) {
  *this << (Header)p;
  *this << p.getMessageId();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const SubmitMulti &p) {
  *this << (Header)p;
  *this << p.getServiceType();
  *this << p.getSourceAddrTon();
  *this << p.getSourceAddrNpi();
  *this << p.getSourceAddr();
  *this << p.getNumberOfDests();
  *this << p.getDestAddresses();
  *this << p.getEsmClass();
  *this << p.getProtocolId();
  *this << p.getPriorityFlag();
  *this << p.getScheduleDeliveryTime();
  *this << p.getValidityPeriod();
  *this << p.getRegisteredDelivery();
  *this << p.getReplaceIfPresentFlag();
  *this << p.getDataCoding();
  *this << p.getSmDefaultMsgId();
  *this << p.getSmLength();
  *this << p.getShortMessage();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const SubmitMultiResp &p) {
  *this << (Header)p;
  *this << p.getMessageId();
  *this << p.getNoUnsuccess();
  QList<UnsuccessSme> list(p.getUnsuccessSmes());
  for(QList<UnsuccessSme>::ConstIterator it = list.constBegin();
      it != list.constEnd();
      it++) {
    *this << *it;
  }
  return *this;
}

HexEncoder &HexEncoder::operator <<(const DeliverSm &p) {
  *this << (Header)p;
  *this << p.getServiceType();
  *this << p.getSourceAddrTon();
  *this << p.getSourceAddrNpi();
  *this << p.getSourceAddr();
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  *this << p.getEsmClass();
  *this << p.getProtocolId();
  *this << p.getPriorityFlag();
  *this << p.getScheduleDeliveryTime();
  *this << p.getValidityPeriod();
  *this << p.getRegisteredDelivery();
  *this << p.getReplaceIfPresentFlag();
  *this << p.getDataCoding();
  *this << p.getSmDefaultMsgId();
  *this << p.getSmLength();
  *this << p.getShortMessage();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const DeliverSmResp &p) {
  *this << (Header)p;
  *this << p.getMessageId();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const DataSm &p) {
  *this << (Header)p;
  *this << p.getServiceType();
  *this << p.getSourceAddrTon();
  *this << p.getSourceAddrNpi();
  *this << p.getSourceAddr();
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  *this << p.getEsmClass();
  *this << p.getRegisteredDelivery();
  *this << p.getDataCoding();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const DataSmResp &p) {
  *this << (Header)p;
  *this << p.getMessageId();
  *this << (TlvFields)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const QuerySm &p) {
  *this << (Header)p;
  *this << p.getMessageId();
  *this << p.getSourceAddr();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const QuerySmResp &p) {
  *this << (Header)p;
  *this << p.getMessageId();
  *this << p.getFinalDate();
  *this << p.getMessageState();
  *this << p.getErrorCode();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const CancelSm &p) {
  *this << (Header)p;
  *this << p.getServiceType();
  *this << p.getMessageId();
  *this << p.getSourceAddrTon();
  *this << p.getSourceAddrNpi();
  *this << p.getSourceAddr();
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const CancelSmResp &p) {
  *this << (Header)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const ReplaceSm &p) {
  *this << (Header)p;
  *this << p.getMessageId();
  *this << p.getSourceAddrTon();
  *this << p.getSourceAddrNpi();
  *this << p.getSourceAddr();
  *this << p.getScheduleDeliveryTime();
  *this << p.getValidityPeriod();
  *this << p.getRegisteredDelivery();
  *this << p.getSmDefaultMsgId();
  *this << p.getSmLength();
  *this << p.getShortMessage();
  return *this;
}

HexEncoder &HexEncoder::operator <<(const ReplaceSmResp &p) {
  *this << (Header)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const EnquireLink &p) {
  *this << (Header)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const EnquireLinkResp &p) {
  *this << (Header)p;
  return *this;
}

HexEncoder &HexEncoder::operator <<(const AlertNotification &p) {
  *this << (Header)p;
  *this << p.getSourceAddrTon();
  *this << p.getSourceAddrNpi();
  *this << p.getSourceAddr();
  *this << p.getEsmeAddrTon();
  *this << p.getEsmeAddrNpi();
  *this << p.getEsmeAddr();
  *this << (TlvFields)p;
  return *this;
}

} // namespace encoders

} // namespace smpp

