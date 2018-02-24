#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_submit_multi.h"

namespace smpp {

namespace pdu {

SubmitMulti::SubmitMulti(quint32 sequence_number,
                         const QString &service_type,
                         quint8 source_addr_ton,
                         quint8 source_addr_npi,
                         const QString &source_addr,
                         quint8 number_of_dests,
                         const MultiDestinationAddresses &dest_addresses,
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
         parameters::command_id::SUBMIT_SM,
         parameters::command_status::ESME_ROK,
         sequence_number),
  service_type(service_type),
  source_addr_ton(source_addr_ton),
  source_addr_npi(source_addr_npi),
  source_addr(source_addr),
  number_of_dests(number_of_dests),
  dest_addresses(dest_addresses),
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

SubmitMulti::SubmitMulti(const Header &p) :
  Header(p),
  source_addr_ton(0),
  source_addr_npi(0),
  number_of_dests(0),
  esm_class(0),
  protocol_id(0),
  priority_flag(0),
  registered_delivery(0),
  replace_if_present_flag(0),
  data_coding(0),
  sm_default_msg_id(0),
  sm_length(0) {

}

SubmitMulti::SubmitMulti(const SubmitMulti &p) :
  Header(p),
  TlvFields(p),
  service_type(p.service_type),
  source_addr_ton(p.source_addr_ton),
  source_addr_npi(p.source_addr_npi),
  source_addr(p.source_addr),
  number_of_dests(p.number_of_dests),
  dest_addresses(p.dest_addresses),
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

void SubmitMulti::setServiceType(const QString &v) {
  service_type = v;
}

void SubmitMulti::setSourceAddrTon(quint8 v) {
  source_addr_ton = v;
}

void SubmitMulti::setSourceAddrNpi(quint8 v) {
  source_addr_npi = v;
}

void SubmitMulti::setSourceAddr(const QString &v) {
  source_addr = v;
}

void SubmitMulti::setNumberOfDests(quint8 v) {
  number_of_dests = v;
}

void SubmitMulti::setDestAddresses(const MultiDestinationAddresses &v) {
  dest_addresses = v;
}

void SubmitMulti::setEsmClass(quint8 v) {
  esm_class = v;
}

void SubmitMulti::setProtocolId(quint8 v) {
  protocol_id = v;
}

void SubmitMulti::setPriorityFlag(quint8 v) {
  priority_flag = v;
}

void SubmitMulti::setScheduleDeliveryTime(const QString &v) {
  schedule_delivery_time = v;
}

void SubmitMulti::setValidityPeriod(const QString &v) {
  validity_period = v;
}

void SubmitMulti::setRegisteredDelivery(quint8 v) {
  registered_delivery = v;
}

void SubmitMulti::setReplaceIfPresentFlag(quint8 v) {
  replace_if_present_flag = v;
}

void SubmitMulti::setDataCoding(quint8 v) {
  data_coding = v;
}

void SubmitMulti::setSmDefaultMsgId(quint8 v) {
  sm_default_msg_id = v;
}

void SubmitMulti::setSmLength(quint8 v) {
  sm_length = v;
}

void SubmitMulti::setShortMessage(const QByteArray &v) {
  short_message = v;
}

QString SubmitMulti::getServiceType() const {
  return service_type;
}

quint8 SubmitMulti::getSourceAddrTon() const {
  return source_addr_ton;
}

quint8 SubmitMulti::getSourceAddrNpi() const {
  return source_addr_npi;
}

QString SubmitMulti::getSourceAddr() const {
  return source_addr;
}

quint8 SubmitMulti::getNumberOfDests() const {
  return number_of_dests;
}

const MultiDestinationAddresses &SubmitMulti::getDestAddresses() const {
  return dest_addresses;
}

quint8 SubmitMulti::getEsmClass() const {
  return esm_class;
}

quint8 SubmitMulti::getProtocolId() const {
  return protocol_id;
}

quint8 SubmitMulti::getPriorityFlag() const {
  return priority_flag;
}

QString SubmitMulti::getScheduleDeliveryTime() const {
  return schedule_delivery_time;
}

QString SubmitMulti::getValidityPeriod() const {
  return validity_period;
}

quint8 SubmitMulti::getRegisteredDelivery() const {
  return registered_delivery;
}

quint8 SubmitMulti::getReplaceIfPresentFlag() const {
  return replace_if_present_flag;
}

quint8 SubmitMulti::getDataCoding() const {
  return data_coding;
}

quint8 SubmitMulti::getSmDefaultMsgId() const {
  return sm_default_msg_id;
}

quint8 SubmitMulti::getSmLength() const {
  return sm_length;
}

QByteArray SubmitMulti::getShortMessage() const {
  return short_message;
}

quint32 SubmitMulti::size() const {
  return MIN_LENGTH +
         service_type.size() +
         source_addr.size() +
         dest_addresses.size() +
         schedule_delivery_time.size() +
         validity_period.size() +
         short_message.size() +
         TlvFields::size();
}

SubmitMulti &SubmitMulti::operator =(const SubmitMulti &p) {
  if(this != &p) {
    Header::operator=(p);
    service_type = p.service_type;
    source_addr_ton = p.source_addr_ton;
    source_addr_npi = p.source_addr_npi;
    source_addr = p.source_addr;
    number_of_dests = p.number_of_dests;
    dest_addresses = p.dest_addresses;
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

bool SubmitMulti::operator ==(const SubmitMulti &p) const {
  return(Header::operator==(p) &&
         service_type == p.service_type &&
         source_addr_ton == p.source_addr_ton &&
         source_addr_npi == p.source_addr_npi &&
         source_addr == p.source_addr &&
         number_of_dests == p.number_of_dests &&
         dest_addresses == p.dest_addresses &&
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

bool SubmitMulti::operator !=(const SubmitMulti &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
