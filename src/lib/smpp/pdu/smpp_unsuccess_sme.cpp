#include "smpp/pdu/smpp_unsuccess_sme.h"

namespace smpp {

namespace pdu {

UnsuccessSme::UnsuccessSme(quint8 dest_addr_ton,
                           quint8 dest_addr_npi,
                           const QString &destination_addr,
                           quint32 error_status_code) :
  dest_addr_ton(dest_addr_ton),
  dest_addr_npi(dest_addr_npi),
  destination_addr(destination_addr),
  error_status_code(error_status_code) {

}

UnsuccessSme::UnsuccessSme(const UnsuccessSme &p) :
  dest_addr_ton(p.dest_addr_ton),
  dest_addr_npi(p.dest_addr_npi),
  destination_addr(p.destination_addr),
  error_status_code(p.error_status_code) {

}

void UnsuccessSme::setDestAddrTon(quint8 v) {
  dest_addr_ton = v;
}

void UnsuccessSme::setDestAddrNpi(quint8 v) {
  dest_addr_npi = v;
}

void UnsuccessSme::setDestinationAddr(const QString &v) {
  destination_addr = v;
}

void UnsuccessSme::setErrorStatusCode(quint32 v) {
  error_status_code = v;
}

quint8 UnsuccessSme::getDestAddrTon() const {
  return dest_addr_ton;
}

quint8 UnsuccessSme::getDestAddrNpi() const {
  return dest_addr_npi;
}

QString UnsuccessSme::getDestinationAddr() const {
  return destination_addr;
}

quint32 UnsuccessSme::getErrorStatusCode() const {
  return error_status_code;
}

quint32 UnsuccessSme::size() const {
  return 6 + destination_addr.size();
}

UnsuccessSme &UnsuccessSme::operator =(const UnsuccessSme &p) {
  if(this != &p) {
    dest_addr_ton = p.dest_addr_ton;
    dest_addr_npi = p.dest_addr_npi;
    destination_addr = p.destination_addr;
    error_status_code = p.error_status_code;
  }
  return *this;
}

bool UnsuccessSme::operator ==(const UnsuccessSme &p) const {
  return(dest_addr_ton == p.dest_addr_ton &&
         dest_addr_npi == p.dest_addr_npi &&
         destination_addr == p.destination_addr &&
         error_status_code == p.error_status_code);
}

bool UnsuccessSme::operator !=(const UnsuccessSme &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
