#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_deliver_sm.h"

namespace smpp {

namespace pdu {

DeliverSm::DeliverSm(quint32 sequence_number,
                     const QString &service_type,
                     quint8 source_addr_ton,
                     quint8 source_addr_npi,
                     const QString &source_addr,
                     quint8 dest_addr_ton,
                     quint8 dest_addr_npi,
                     const QString &destination_addr,
                     quint8 esm_class,
                     quint8 protocol_id,
                     quint8 priority_flag,
                     const QString &schedule_delivery_time,
                     const QString &validity_period,
                     quint8 registered_delivery,
                     quint8 replace_if_present_flag,
                     quint8 data_coding,
                     quint8 sm_default_msg_id,
                     quint8 sm_length,
                     const QByteArray &short_message) :
  Header(MIN_LENGTH,
         parameters::command_id::DELIVER_SM,
         parameters::command_status::ESME_ROK,
         sequence_number),
  service_type(service_type),
  source_addr_ton(source_addr_ton),
  source_addr_npi(source_addr_npi),
  source_addr(source_addr),
  dest_addr_ton(dest_addr_ton),
  dest_addr_npi(dest_addr_npi),
  destination_addr(destination_addr),
  esm_class(esm_class),
  protocol_id(protocol_id),
  priority_flag(priority_flag),
  schedule_delivery_time(schedule_delivery_time),
  validity_period(validity_period),
  registered_delivery(registered_delivery),
  replace_if_present_flag(replace_if_present_flag),
  data_coding(data_coding),
  sm_default_msg_id(sm_default_msg_id),
  sm_length(sm_length),
  short_message(short_message) {

}

DeliverSm::DeliverSm(const Header &p) :
  Header(p),
  source_addr_ton(0),
  source_addr_npi(0),
  dest_addr_ton(0),
  dest_addr_npi(0),
  esm_class(0),
  protocol_id(0),
  priority_flag(0),
  registered_delivery(0),
  replace_if_present_flag(0),
  data_coding(0),
  sm_default_msg_id(0),
  sm_length(0) {

}

DeliverSm::DeliverSm(const DeliverSm &p) :
  Header(p),
  TlvFields(p),
  service_type(p.service_type),
  source_addr_ton(p.source_addr_ton),
  source_addr_npi(p.source_addr_npi),
  source_addr(p.source_addr),
  dest_addr_ton(p.dest_addr_ton),
  dest_addr_npi(p.dest_addr_npi),
  destination_addr(p.destination_addr),
  esm_class(p.esm_class),
  protocol_id(p.protocol_id),
  priority_flag(p.priority_flag),
  schedule_delivery_time(p.schedule_delivery_time),
  validity_period(p.validity_period),
  registered_delivery(p.registered_delivery),
  replace_if_present_flag(p.replace_if_present_flag),
  data_coding(p.data_coding),
  sm_default_msg_id(p.sm_default_msg_id),
  sm_length(p.sm_length),
  short_message(p.short_message) {

}

void DeliverSm::setServiceType(const QString &v) {
  service_type = v;
}

void DeliverSm::setSourceAddrTon(quint8 v) {
  source_addr_ton = v;
}

void DeliverSm::setSourceAddrNpi(quint8 v) {
  source_addr_npi = v;
}

void DeliverSm::setSourceAddr(const QString &v) {
  source_addr = v;
}

void DeliverSm::setDestAddrTon(quint8 v) {
  dest_addr_ton = v;
}

void DeliverSm::setDestAddrNpi(quint8 v) {
  dest_addr_npi = v;
}

void DeliverSm::setDestinationAddr(const QString &v) {
  destination_addr = v;
}

void DeliverSm::setEsmClass(quint8 v) {
  esm_class = v;
}

void DeliverSm::setProtocolId(quint8 v) {
  protocol_id = v;
}

void DeliverSm::setPriorityFlag(quint8 v) {
  priority_flag = v;
}

void DeliverSm::setScheduleDeliveryTime(const QString &v) {
  schedule_delivery_time = v;
}

void DeliverSm::setValidityPeriod(const QString &v) {
  validity_period = v;
}

void DeliverSm::setRegisteredDelivery(quint8 v) {
  registered_delivery = v;
}

void DeliverSm::setReplaceIfPresentFlag(quint8 v) {
  replace_if_present_flag = v;
}

void DeliverSm::setDataCoding(quint8 v) {
  data_coding = v;
}

void DeliverSm::setSmDefaultMsgId(quint8 v) {
  sm_default_msg_id = v;
}

void DeliverSm::setSmLength(quint8 v) {
  sm_length = v;
}

void DeliverSm::setShortMessage(const QByteArray &v) {
  short_message = v;
}

QString DeliverSm::getServiceType() const {
  return service_type;
}

quint8 DeliverSm::getSourceAddrTon() const {
  return source_addr_ton;
}

quint8 DeliverSm::getSourceAddrNpi() const {
  return source_addr_npi;
}

QString DeliverSm::getSourceAddr() const {
  return source_addr;
}

quint8 DeliverSm::getDestAddrTon() const {
  return dest_addr_ton;
}

quint8 DeliverSm::getDestAddrNpi() const {
  return dest_addr_npi;
}

QString DeliverSm::getDestinationAddr() const {
  return destination_addr;
}

quint8 DeliverSm::getEsmClass() const {
  return esm_class;
}

quint8 DeliverSm::getProtocolId() const {
  return protocol_id;
}

quint8 DeliverSm::getPriorityFlag() const {
  return priority_flag;
}

QString DeliverSm::getScheduleDeliveryTime() const {
  return schedule_delivery_time;
}

QString DeliverSm::getValidityPeriod() const {
  return validity_period;
}

quint8 DeliverSm::getRegisteredDelivery() const {
  return registered_delivery;
}

quint8 DeliverSm::getReplaceIfPresentFlag() const {
  return replace_if_present_flag;
}

quint8 DeliverSm::getDataCoding() const {
  return data_coding;
}

quint8 DeliverSm::getSmDefaultMsgId() const {
  return sm_default_msg_id;
}

quint8 DeliverSm::getSmLength() const {
  return sm_length;
}

QByteArray DeliverSm::getShortMessage() const {
  return short_message;
}

quint32 DeliverSm::size() const {
  return MIN_LENGTH +
         service_type.size() +
         source_addr.size() +
         destination_addr.size() +
         schedule_delivery_time.size() +
         validity_period.size() +
         short_message.size() +
         TlvFields::size();
}

DeliverSm &DeliverSm::operator =(const DeliverSm &p) {
  if(this != &p) {
    Header::operator=(p);
    service_type = p.service_type;
    source_addr_ton = p.source_addr_ton;
    source_addr_npi = p.source_addr_npi;
    source_addr = p.source_addr;
    dest_addr_ton = p.dest_addr_ton;
    dest_addr_npi = p.dest_addr_npi;
    destination_addr = p.destination_addr;
    esm_class = p.esm_class;
    protocol_id = p.protocol_id;
    priority_flag = p.priority_flag;
    schedule_delivery_time = p.schedule_delivery_time;
    validity_period = p.validity_period;
    registered_delivery = p.registered_delivery;
    replace_if_present_flag = p.replace_if_present_flag;
    data_coding = p.data_coding;
    sm_default_msg_id = p.sm_default_msg_id;
    sm_length = p.sm_length;
    short_message = p.short_message;
    TlvFields::operator=(p);
  }
  return *this;
}

bool DeliverSm::operator ==(const DeliverSm &p) const {
  return(Header::operator==(p) &&
         service_type == p.service_type &&
         source_addr_ton == p.source_addr_ton &&
         source_addr_npi == p.source_addr_npi &&
         source_addr == p.source_addr &&
         dest_addr_ton == p.dest_addr_ton &&
         dest_addr_npi == p.dest_addr_npi &&
         destination_addr == p.destination_addr &&
         esm_class == p.esm_class &&
         protocol_id == p.protocol_id &&
         priority_flag == p.priority_flag &&
         schedule_delivery_time == p.schedule_delivery_time &&
         validity_period == p.validity_period &&
         registered_delivery == p.registered_delivery &&
         replace_if_present_flag == p.replace_if_present_flag &&
         data_coding == p.data_coding &&
         sm_default_msg_id == p.sm_default_msg_id &&
         sm_length == p.sm_length &&
         short_message == p.short_message &&
         TlvFields::operator==(p));
}

bool DeliverSm::operator !=(const DeliverSm &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
