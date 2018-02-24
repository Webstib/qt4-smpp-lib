#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_cancel_sm.h"

namespace smpp {

namespace pdu {

CancelSm::CancelSm(quint32 sequence_number,
                   const QString &service_type,
                   const QString &message_id,
                   quint8 source_addr_ton,
                   quint8 source_addr_npi,
                   const QString &source_addr,
                   quint8 dest_addr_ton,
                   quint8 dest_addr_npi,
                   const QString &destination_addr) :
  Header(MIN_LENGTH,
         parameters::command_id::CANCEL_SM,
         parameters::command_status::ESME_ROK,
         sequence_number),
  service_type(service_type),
  message_id(message_id),
  source_addr_ton(source_addr_ton),
  source_addr_npi(source_addr_npi),
  source_addr(source_addr),
  dest_addr_ton(dest_addr_ton),
  dest_addr_npi(dest_addr_npi),
  destination_addr(destination_addr) {

}

CancelSm::CancelSm(const Header &p) :
  Header(p),
  source_addr_ton(0),
  source_addr_npi(0),
  dest_addr_ton(0),
  dest_addr_npi(0) {

}

CancelSm::CancelSm(const CancelSm &p) :
  Header(p),
  service_type(p.service_type),
  message_id(p.message_id),
  source_addr_ton(p.source_addr_ton),
  source_addr_npi(p.source_addr_npi),
  source_addr(p.source_addr),
  dest_addr_ton(p.dest_addr_ton),
  dest_addr_npi(p.dest_addr_npi),
  destination_addr(p.destination_addr) {

}

void CancelSm::setServiceType(const QString &v) {
  service_type = v;
}

void CancelSm::setMessageId(const QString &v) {
  message_id = v;
}

void CancelSm::setSourceAddrTon(quint8 v) {
  source_addr_ton = v;
}

void CancelSm::setSourceAddrNpi(quint8 v) {
  source_addr_npi = v;
}

void CancelSm::setSourceAddr(const QString &v) {
  source_addr = v;
}

void CancelSm::setDestAddrTon(quint8 v) {
  dest_addr_ton = v;
}

void CancelSm::setDestAddrNpi(quint8 v) {
  dest_addr_npi = v;
}

void CancelSm::setDestinationAddr(const QString &v) {
  destination_addr = v;
}

QString CancelSm::getServiceType() const {
  return service_type;
}

QString CancelSm::getMessageId() const {
  return message_id;
}

quint8 CancelSm::getSourceAddrTon() const {
  return source_addr_ton;
}

quint8 CancelSm::getSourceAddrNpi() const {
  return source_addr_npi;
}

QString CancelSm::getSourceAddr() const {
  return source_addr;
}

quint8 CancelSm::getDestAddrTon() const {
  return dest_addr_ton;
}

quint8 CancelSm::getDestAddrNpi() const {
  return dest_addr_npi;
}

QString CancelSm::getDestinationAddr() const {
  return destination_addr;
}

quint32 CancelSm::size() const {
  return MIN_LENGTH +
         service_type.size() +
         message_id.size() +
         source_addr.size() +
         destination_addr.size();
}

CancelSm &CancelSm::operator =(const CancelSm &p) {
  if(this != &p) {
    Header::operator=(p);
    service_type = p.service_type;
    message_id = p.message_id;
    source_addr_ton = p.source_addr_ton;
    source_addr_npi = p.source_addr_npi;
    source_addr = p.source_addr;
    dest_addr_ton = p.dest_addr_ton;
    dest_addr_npi = p.dest_addr_npi;
    destination_addr = p.destination_addr;
  }
  return *this;
}

bool CancelSm::operator ==(const CancelSm &p) const {
  return(Header::operator==(p) &&
         service_type == p.service_type &&
         message_id == p.message_id &&
         source_addr_ton == p.source_addr_ton &&
         source_addr_npi == p.source_addr_npi &&
         source_addr == p.source_addr &&
         dest_addr_ton == p.dest_addr_ton &&
         dest_addr_npi == p.dest_addr_npi &&
         destination_addr == p.destination_addr);
}

bool CancelSm::operator !=(const CancelSm &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
