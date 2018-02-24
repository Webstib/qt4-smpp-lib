#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_alert_notification.h"

namespace smpp {

namespace pdu {

AlertNotification::AlertNotification(
  quint32 sequence_number,
  quint8 source_addr_ton,
  quint8 source_addr_npi,
  const QString &source_addr,
  quint8 esme_addr_ton,
  quint8 esme_addr_npi,
  const QString &esme_addr) :
  Header(MIN_LENGTH,
         parameters::command_id::ALERT_NOTIFICATION,
         parameters::command_status::ESME_ROK,
         sequence_number),
  source_addr_ton(source_addr_ton),
  source_addr_npi(source_addr_npi),
  source_addr(source_addr),
  esme_addr_ton(esme_addr_ton),
  esme_addr_npi(esme_addr_npi),
  esme_addr(esme_addr) {

}

AlertNotification::AlertNotification(const Header &p) : Header(p) {

}

AlertNotification::AlertNotification(const AlertNotification &p) :
  Header(p),
  TlvFields(p),
  source_addr_ton(p.source_addr_ton),
  source_addr_npi(p.source_addr_npi),
  source_addr(p.source_addr),
  esme_addr_ton(p.esme_addr_ton),
  esme_addr_npi(p.esme_addr_npi),
  esme_addr(p.esme_addr) {

}

void AlertNotification::setSourceAddrTon(quint8 v) {
  source_addr_ton = v;
}

void AlertNotification::setSourceAddrNpi(quint8 v) {
  source_addr_npi = v;
}

void AlertNotification::setSourceAddr(const QString &v) {
  source_addr = v;
}

void AlertNotification::setEsmeAddrTon(quint8 v) {
  esme_addr_ton = v;
}

void AlertNotification::setEsmeAddrNpi(quint8 v) {
  esme_addr_npi = v;
}

void AlertNotification::setEsmeAddr(const QString &v) {
  esme_addr = v;
}

quint8 AlertNotification::getSourceAddrTon() const {
  return source_addr_ton;
}

quint8 AlertNotification::getSourceAddrNpi() const {
  return source_addr_npi;
}

QString AlertNotification::getSourceAddr() const {
  return source_addr;
}

quint8 AlertNotification::getEsmeAddrTon() const {
  return esme_addr_ton;
}

quint8 AlertNotification::getEsmeAddrNpi() const {
  return esme_addr_npi;
}

QString AlertNotification::getEsmeAddr() const {
  return esme_addr;
}

quint32 AlertNotification::size() const {
  return MIN_LENGTH + source_addr.size() + esme_addr.size() + TlvFields::size();
}

AlertNotification &AlertNotification::operator =(const AlertNotification &p) {
  if(this != &p) {
    Header::operator=(p);
    source_addr_ton = p.source_addr_ton;
    source_addr_npi = p.source_addr_npi;
    source_addr = p.source_addr;
    esme_addr_ton = p.esme_addr_ton;
    esme_addr_npi = p.esme_addr_npi;
    esme_addr = p.esme_addr;
    TlvFields::operator=(p);
  }
  return *this;
}

bool AlertNotification::operator ==(const AlertNotification &p) const {
  return(Header::operator==(p) &&
         source_addr_ton == p.source_addr_ton &&
         source_addr_npi == p.source_addr_npi &&
         source_addr == p.source_addr &&
         esme_addr_ton == p.esme_addr_ton &&
         esme_addr_npi == p.esme_addr_npi &&
         esme_addr == p.esme_addr &&
         TlvFields::operator==(p));
}

bool AlertNotification::operator !=(const AlertNotification &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
