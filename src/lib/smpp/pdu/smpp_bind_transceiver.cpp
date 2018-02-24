#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_bind_transceiver.h"

namespace smpp {

namespace pdu {

BindTransceiver::BindTransceiver(
  quint32 sequence_number,
  const QString &system_id,
  const QString &password,
  const QString &system_type,
  quint8 interface_version,
  quint8 addr_ton,
  quint8 addr_npi,
  const QString &address_range) :
    Header(MIN_LENGTH,
           parameters::command_id::BIND_TRANSCEIVER,
           parameters::command_status::ESME_ROK,
           sequence_number),
    system_id(system_id),
    password(password),
    system_type(system_type),
    interface_version(interface_version),
    addr_ton(addr_ton),
    addr_npi(addr_npi),
    address_range(address_range) {

}

BindTransceiver::BindTransceiver(const Header &p) : Header(p) {

}

BindTransceiver::BindTransceiver(const BindTransceiver &p) :
  Header(p),
  system_id(p.system_id),
  password(p.password),
  system_type(p.system_type),
  interface_version(p.interface_version),
  addr_ton(p.addr_ton),
  addr_npi(p.addr_npi),
  address_range(p.address_range) {

}

void BindTransceiver::setSystemId(const QString &p) {
  system_id = p;
}

void BindTransceiver::setPassword(const QString &p) {
  password = p;
}

void BindTransceiver::setSystemType(const QString &p) {
  system_type = p;
}

void BindTransceiver::setInterfaceVersion(quint8 p) {
  interface_version = p;
}

void BindTransceiver::setAddrTon(quint8 p) {
  addr_ton = p;
}

void BindTransceiver::setAddrNpi(quint8 p) {
  addr_npi = p;
}

void BindTransceiver::setAddressRange(const QString &p) {
  address_range = p;
}

QString BindTransceiver::getSystemId() const {
  return system_id;
}

QString BindTransceiver::getPassword() const {
  return password;
}

QString BindTransceiver::getSystemType() const {
  return system_type;
}

quint8 BindTransceiver::getInterfaceVersion() const {
  return interface_version;
}

quint8 BindTransceiver::getAddrTon() const {
  return addr_ton;
}

quint8 BindTransceiver::getAddrNpi() const {
  return addr_npi;
}

QString BindTransceiver::getAddressRange() const {
  return address_range;
}

quint32 BindTransceiver::size() const {
  return MIN_LENGTH +
         system_id.size() +
         password.size() +
         system_type.size() +
         address_range.size();
}

BindTransceiver &BindTransceiver::operator =(const BindTransceiver &p) {
  if(this != &p) {
    Header::operator=(p);
    system_id = p.system_id;
    password = p.password;
    system_type = p.system_type;
    interface_version = p.interface_version;
    addr_ton = p.addr_ton;
    addr_npi = p.addr_npi;
    address_range = p.address_range;
  }
  return *this;
}

bool BindTransceiver::operator ==(const BindTransceiver &p) const {
  return(Header::operator==(p) &&
         system_id == p.system_id &&
         password == p.password &&
         system_type == p.system_type &&
         interface_version == p.interface_version &&
         addr_ton == p.addr_ton &&
         addr_npi == p.addr_npi &&
         address_range == p.address_range);
}

bool BindTransceiver::operator !=(const BindTransceiver &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
