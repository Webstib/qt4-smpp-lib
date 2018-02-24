#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_query_sm.h"

namespace smpp {

namespace pdu {

QuerySm::QuerySm(quint32 sequence_number,
                 const QString &message_id,
                 quint8 source_addr_ton,
                 quint8 source_addr_npi,
                 const QString &source_addr) :
  Header(MIN_LENGTH,
         parameters::command_id::QUERY_SM,
         parameters::command_status::ESME_ROK,
         sequence_number),
  message_id(message_id),
  source_addr_ton(source_addr_ton),
  source_addr_npi(source_addr_npi),
  source_addr(source_addr) {

}

QuerySm::QuerySm(const Header &p) :
  Header(p),
  source_addr_ton(0),
  source_addr_npi(0) {

}

QuerySm::QuerySm(const QuerySm &p) :
  Header(p),
  message_id(p.message_id),
  source_addr_ton(p.source_addr_ton),
  source_addr_npi(p.source_addr_npi),
  source_addr(p.source_addr) {

}

void QuerySm::setMessageId(const QString &v) {
  message_id = v;
}

void QuerySm::setSourceAddrTon(quint8 v) {
  source_addr_ton = v;
}

void QuerySm::setSourceAddrNpi(quint8 v) {
  source_addr_npi = v;
}

void QuerySm::setSourceAddr(const QString &v) {
  source_addr = v;
}

QString QuerySm::getMessageId() const {
  return message_id;
}

quint8 QuerySm::getSourceAddrTon() const {
  return source_addr_ton;
}

quint8 QuerySm::getSourceAddrNpi() const {
  return source_addr_npi;
}

QString QuerySm::getSourceAddr() const {
  return source_addr;
}

quint32 QuerySm::size() const {
  return MIN_LENGTH + message_id.size() + source_addr.size();
}

QuerySm &QuerySm::operator =(const QuerySm &p) {
  if(this != &p) {
    Header::operator=(p);
    message_id = p.message_id;
    source_addr_ton = p.source_addr_ton;
    source_addr_npi = p.source_addr_npi;
    source_addr = p.source_addr;
  }
  return *this;
}

bool QuerySm::operator ==(const QuerySm &p) const {
  return(Header::operator==(p) &&
         message_id == p.message_id &&
         source_addr_ton == p.source_addr_ton &&
         source_addr_npi == p.source_addr_npi &&
         source_addr == p.source_addr);
}

bool QuerySm::operator !=(const QuerySm &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
