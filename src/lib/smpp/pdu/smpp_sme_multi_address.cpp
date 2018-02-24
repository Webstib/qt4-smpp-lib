#include "smpp/pdu/smpp_sme_multi_address.h"

namespace smpp {

namespace pdu {

SmeMultiAddress::SmeMultiAddress(quint8 dest_addr_ton,
                                 quint8 dest_addr_npi,
                                 const QString &destination_addr) :
  dest_addr_ton(dest_addr_ton),
  dest_addr_npi(dest_addr_npi),
  destination_addr(destination_addr) {

}

SmeMultiAddress::SmeMultiAddress(const SmeMultiAddress &p) :
  MultiDestinationAddressBase(p),
  dest_addr_ton(p.dest_addr_ton),
  dest_addr_npi(p.dest_addr_npi),
  destination_addr(p.destination_addr) {

}

void SmeMultiAddress::setDestAddrTon(quint8 v) {
  dest_addr_ton = v;
}

void SmeMultiAddress::setDestAddrNpi(quint8 v) {
  dest_addr_npi = v;
}

void SmeMultiAddress::setDestinationAddr(const QString &v){
  destination_addr = v;
}

quint8 SmeMultiAddress::getDestAddrTon() const {
  return dest_addr_ton;
}

quint8 SmeMultiAddress::getDestAddrNpi() const {
  return dest_addr_npi;
}

QString SmeMultiAddress::getDestinationAddr() const {
  return destination_addr;
}

quint8 SmeMultiAddress::getDestFlag() const {
  return 0x01;
}

quint32 SmeMultiAddress::size() const {
  return 4 + destination_addr.size();
}

SmeMultiAddress &SmeMultiAddress::operator =(const SmeMultiAddress &p) {
  if(this != &p) {
    dest_addr_ton = p.dest_addr_ton;
    dest_addr_npi = p.dest_addr_npi;
    destination_addr = p.destination_addr;
  }
  return *this;
}

bool SmeMultiAddress::operator ==(const SmeMultiAddress &p) const {
  return (dest_addr_ton == p.dest_addr_ton &&
          dest_addr_npi == p.dest_addr_npi &&
          destination_addr == p.destination_addr);
}

bool SmeMultiAddress::operator !=(const SmeMultiAddress &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
