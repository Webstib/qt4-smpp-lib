#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_replace_sm.h"

namespace smpp {

namespace pdu {

ReplaceSm::ReplaceSm(quint32 sequence_number,
                     const QString &message_id,
                     quint8 source_addr_ton,
                     quint8 source_addr_npi,
                     const QString &source_addr,
                     const QString &schedule_delivery_time,
                     const QString &validity_period,
                     quint8 registered_delivery,
                     quint8 sm_default_msg_id,
                     quint8 sm_length,
                     const QByteArray &short_message) :
  Header(MIN_LENGTH,
         parameters::command_id::REPLACE_SM,
         parameters::command_status::ESME_ROK,
         sequence_number),
  message_id(message_id),
  source_addr_ton(source_addr_ton),
  source_addr_npi(source_addr_npi),
  source_addr(source_addr),
  schedule_delivery_time(schedule_delivery_time),
  validity_period(validity_period),
  registered_delivery(registered_delivery),
  sm_default_msg_id(sm_default_msg_id),
  sm_length(sm_length),
  short_message(short_message) {

}

ReplaceSm::ReplaceSm(const Header &p) :
  Header(p),
  source_addr_ton(0),
  source_addr_npi(0),
  registered_delivery(0),
  sm_default_msg_id(0),
  sm_length(0) {

}

ReplaceSm::ReplaceSm(const ReplaceSm &p) :
  Header(p),
  message_id(p.message_id),
  source_addr_ton(p.source_addr_ton),
  source_addr_npi(p.source_addr_npi),
  source_addr(p.source_addr),
  schedule_delivery_time(p.schedule_delivery_time),
  validity_period(p.validity_period),
  registered_delivery(p.registered_delivery),
  sm_default_msg_id(p.sm_default_msg_id),
  sm_length(p.sm_length),
  short_message(p.short_message) {

}

void ReplaceSm::setMessageId(const QString &v) {
  message_id = v;
}

void ReplaceSm::setSourceAddrTon(quint8 v) {
  source_addr_ton = v;
}

void ReplaceSm::setSourceAddrNpi(quint8 v) {
  source_addr_npi = v;
}

void ReplaceSm::setSourceAddr(const QString &v) {
  source_addr = v;
}

void ReplaceSm::setScheduleDeliveryTime(const QString &v) {
  schedule_delivery_time = v;
}

void ReplaceSm::setValidityPeriod(const QString &v) {
  validity_period = v;
}

void ReplaceSm::setRegisteredDelivery(quint8 v) {
  registered_delivery = v;
}

void ReplaceSm::setSmDefaultMsgId(quint8 v) {
  sm_default_msg_id = v;
}

void ReplaceSm::setSmLength(quint8 v) {
  sm_length = v;
}

void ReplaceSm::setShortMessage(const QByteArray &v) {
  short_message = v;
}

QString ReplaceSm::getMessageId() const {
  return message_id;
}

quint8 ReplaceSm::getSourceAddrTon() const {
  return source_addr_ton;
}

quint8 ReplaceSm::getSourceAddrNpi() const {
  return source_addr_npi;
}

QString ReplaceSm::getSourceAddr() const {
  return source_addr;
}

QString ReplaceSm::getScheduleDeliveryTime() const {
  return schedule_delivery_time;
}

QString ReplaceSm::getValidityPeriod() const {
  return validity_period;
}

quint8 ReplaceSm::getRegisteredDelivery() const {
  return registered_delivery;
}

quint8 ReplaceSm::getSmDefaultMsgId() const {
  return sm_default_msg_id;
}

quint8 ReplaceSm::getSmLength() const {
  return sm_length;
}

QByteArray ReplaceSm::getShortMessage() const {
  return short_message;
}

quint32 ReplaceSm::size() const {
  return MIN_LENGTH +
         message_id.size() +
         source_addr.size() +
         schedule_delivery_time.size() +
         validity_period.size() +
         short_message.size();
}

ReplaceSm &ReplaceSm::operator =(const ReplaceSm &p) {
  if(this != &p) {
    Header::operator=(p);
    message_id = p.message_id;
    source_addr_ton = p.source_addr_ton;
    source_addr_npi = p.source_addr_npi;
    source_addr = p.source_addr;
    schedule_delivery_time = p.schedule_delivery_time;
    validity_period = p.validity_period;
    registered_delivery = p.registered_delivery;
    sm_default_msg_id = p.sm_default_msg_id;
    sm_length = p.sm_length;
    short_message = p.short_message;
  }
  return *this;
}

bool ReplaceSm::operator ==(const ReplaceSm &p) const {
  return(Header::operator==(p) &&
         message_id == p.message_id &&
         source_addr_ton == p.source_addr_ton &&
         source_addr_npi == p.source_addr_npi &&
         source_addr == p.source_addr &&
         schedule_delivery_time == p.schedule_delivery_time &&
         validity_period == p.validity_period &&
         registered_delivery == p.registered_delivery &&
         sm_default_msg_id == p.sm_default_msg_id &&
         sm_length == p.sm_length &&
         short_message == p.short_message);
}

bool ReplaceSm::operator !=(const ReplaceSm &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
