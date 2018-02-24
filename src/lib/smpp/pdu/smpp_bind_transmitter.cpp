#include "smpp_bind_transmitter.h"
#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_bind_transmitter.h"

namespace smpp {

namespace pdu {

BindTransmitter::BindTransmitter(
  quint32 sequence_number,
  const QString &system_id,
  const QString &password,
  const QString &system_type,
  quint8 interface_version,
  quint8 addr_ton,
  quint8 addr_npi,
  const QString &address_range) :
    Header(MIN_LENGTH,
           parameters::command_id::BIND_TRANSMITTER,
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

BindTransmitter::BindTransmitter(const Header &p) : Header(p) {

}

BindTransmitter::BindTransmitter(const BindTransmitter &p) :
  Header(p),
  system_id(p.system_id),
  password(p.password),
  system_type(p.system_type),
  interface_version(p.interface_version),
  addr_ton(p.addr_ton),
  addr_npi(p.addr_npi),
  address_range(p.address_range) {

}

void BindTransmitter::setSystemId(const QString &p) {
  system_id = p;
}

void BindTransmitter::setPassword(const QString &p) {
  password = p;
}

void BindTransmitter::setSystemType(const QString &p) {
  system_type = p;
}

void BindTransmitter::setInterfaceVersion(quint8 p) {
  interface_version = p;
}

void BindTransmitter::setAddrTon(quint8 p) {
  addr_ton = p;
}

void BindTransmitter::setAddrNpi(quint8 p) {
  addr_npi = p;
}

void BindTransmitter::setAddressRange(const QString &p) {
  address_range = p;
}

QString BindTransmitter::getSystemId() const {
  return system_id;
}

QString BindTransmitter::getPassword() const {
  return password;
}

QString BindTransmitter::getSystemType() const {
  return system_type;
}

quint8 BindTransmitter::getInterfaceVersion() const {
  return interface_version;
}

quint8 BindTransmitter::getAddrTon() const {
  return addr_ton;
}

quint8 BindTransmitter::getAddrNpi() const {
  return addr_npi;
}

QString BindTransmitter::getAddressRange() const {
  return address_range;
}

quint32 BindTransmitter::size() const {
  return MIN_LENGTH +
         system_id.size() +
         password.size() +
         system_type.size() +
         address_range.size();
}

BindTransmitter &BindTransmitter::operator =(const BindTransmitter &p) {
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

bool BindTransmitter::operator ==(const BindTransmitter &p) const {
  return(Header::operator==(p) &&
         system_id == p.system_id &&
         password == p.password &&
         system_type == p.system_type &&
         interface_version == p.interface_version &&
         addr_ton == p.addr_ton &&
         addr_npi == p.addr_npi &&
         address_range == p.address_range);
}

bool BindTransmitter::operator !=(const BindTransmitter &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
