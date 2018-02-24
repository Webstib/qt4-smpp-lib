#include "smpp/encoders/smpp_binary_encoder.h"
#include "smpp/smpp_transform_functions.h"

namespace smpp {

namespace encoders {

using namespace pdu;

BinaryEncoder::BinaryEncoder() : pos(-1) {

}

void BinaryEncoder::resize(int size) {
  data.clear();
  if(size > 0) {
    data.resize(size);
  }
  pos = 0;
}

BinaryEncoder::operator QByteArray() const {
  return data;
}

const QByteArray &BinaryEncoder::getBuff() const {
  return data;
}

BinaryEncoder &BinaryEncoder::operator <<(const quint8 &p) {
  data[pos++] = p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const quint16 &p) {
  quint16 v(hton16(p));
  char *c_pt(reinterpret_cast<char *>(&v));
  data[pos++] = *(c_pt++);
  data[pos++] = *c_pt;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const quint32 &p) {
  quint32 v(hton32(p));
  char *c_pt(reinterpret_cast<char *>(&v));
  data[pos++] = *(c_pt++);
  data[pos++] = *(c_pt++);
  data[pos++] = *(c_pt++);
  data[pos++] = *c_pt;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const QString &p) {
  *this << (p.toUtf8() + '\0');
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const QByteArray &p) {
  for(int i = 0; i < p.size(); i++)
    data[pos++] = p[i];
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const MultiDestinationAddresses &p) {
  QList<MultiDestinationAddressBase *> list(p.getAll());

  for(QList<MultiDestinationAddressBase *>::ConstIterator it = list.constBegin();
      it != list.constEnd();
      it++) {
    *this << *it;
  }

  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const DistributionListAddress &p) {
  *this << p.getDestFlag();
  *this << p.getDlName();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(MultiDestinationAddressBase *p) {
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

BinaryEncoder &BinaryEncoder::operator <<(const SmeMultiAddress &p) {
  *this << p.getDestFlag();
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const UnsuccessSme &p) {
  *this << p.getDestAddrTon();
  *this << p.getDestAddrNpi();
  *this << p.getDestinationAddr();
  *this << p.getErrorStatusCode();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const Tlv &p) {
  *this << p.getTag();
  *this << p.getLength();
  *this << p.getValue();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const TlvFields &p) {
  TlvList list(p.getList());

  for(TlvList::ConstIterator it = list.constBegin();
      it != list.constEnd();
      it++) {
    *this << **it;
  }

  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const Header &p) {
  *this << p.getCommandLength();
  *this << p.getCommandId();
  *this << p.getCommandStatus();
  *this << p.getSequenceNumber();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const BindTransmitter &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const BindTransmitterResp &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getSystemId();
  *this << (TlvFields)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const BindReceiver &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const BindReceiverResp &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getSystemId();
  *this << (TlvFields)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const BindTransceiver &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const BindTransceiverResp &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getSystemId();
  *this << (TlvFields)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const Outbind &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getSystemId();
  *this << p.getPassword();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const Unbind &p) {
  resize(Header::HEADER_LENGTH);
  *this << (Header)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const UnbindResp &p) {
  resize(Header::HEADER_LENGTH);
  *this << (Header)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const GenericNack &p) {
  resize(Header::HEADER_LENGTH);
  *this << (Header)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const SubmitSm &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const SubmitSmResp &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getMessageId();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const SubmitMulti &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const SubmitMultiResp &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const DeliverSm &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const DeliverSmResp &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getMessageId();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const DataSm &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const DataSmResp &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getMessageId();
  *this << (TlvFields)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const QuerySm &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getMessageId();
  *this << p.getSourceAddr();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const QuerySmResp &p) {
  resize(p.size());
  *this << (Header)p;
  *this << p.getMessageId();
  *this << p.getFinalDate();
  *this << p.getMessageState();
  *this << p.getErrorCode();
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const CancelSm &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const CancelSmResp &p) {
  resize(Header::HEADER_LENGTH);
  *this << (Header)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const ReplaceSm &p) {
  resize(p.size());
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

BinaryEncoder &BinaryEncoder::operator <<(const ReplaceSmResp &p) {
  resize(Header::HEADER_LENGTH);
  *this << (Header)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const EnquireLink &p) {
  resize(Header::HEADER_LENGTH);
  *this << (Header)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const EnquireLinkResp &p) {
  resize(Header::HEADER_LENGTH);
  *this << (Header)p;
  return *this;
}

BinaryEncoder &BinaryEncoder::operator <<(const AlertNotification &p) {
  resize(p.size());
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
