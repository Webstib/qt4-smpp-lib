#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_bind_receiver.h"

namespace smpp {

namespace pdu {

BindReceiver::BindReceiver(
  quint32 sequence_number,
  const QString &system_id,
  const QString &password,
  const QString &system_type,
  quint8 interface_version,
  quint8 addr_ton,
  quint8 addr_npi,
  const QString &address_range) :
    Header(MIN_LENGTH,
           parameters::command_id::BIND_RECEIVER,
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

BindReceiver::BindReceiver(const Header &p) : Header(p) {

}

BindReceiver::BindReceiver(const BindReceiver &p) :
  Header(p),
  system_id(p.system_id),
  password(p.password),
  system_type(p.system_type),
  interface_version(p.interface_version),
  addr_ton(p.addr_ton),
  addr_npi(p.addr_npi),
  address_range(p.address_range) {

}

void BindReceiver::setSystemId(const QString &p) {
  system_id = p;
}

void BindReceiver::setPassword(const QString &p) {
  password = p;
}

void BindReceiver::setSystemType(const QString &p) {
  system_type = p;
}

void BindReceiver::setInterfaceVersion(quint8 p) {
  interface_version = p;
}

void BindReceiver::setAddrTon(quint8 p) {
  addr_ton = p;
}

void BindReceiver::setAddrNpi(quint8 p) {
  addr_npi = p;
}

void BindReceiver::setAddressRange(const QString &p) {
  address_range = p;
}

QString BindReceiver::getSystemId() const {
  return system_id;
}

QString BindReceiver::getPassword() const {
  return password;
}

QString BindReceiver::getSystemType() const {
  return system_type;
}

quint8 BindReceiver::getInterfaceVersion() const {
  return interface_version;
}

quint8 BindReceiver::getAddrTon() const {
  return addr_ton;
}

quint8 BindReceiver::getAddrNpi() const {
  return addr_npi;
}

QString BindReceiver::getAddressRange() const {
  return address_range;
}

quint32 BindReceiver::size() const {
  return MIN_LENGTH +
         system_id.size() +
         password.size() +
         system_type.size() +
         address_range.size();
}

BindReceiver &BindReceiver::operator =(const BindReceiver &p) {
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

bool BindReceiver::operator ==(const BindReceiver &p) const {
  return(Header::operator==(p) &&
         system_id == p.system_id &&
         password == p.password &&
         system_type == p.system_type &&
         interface_version == p.interface_version &&
         addr_ton == p.addr_ton &&
         addr_npi == p.addr_npi &&
         address_range == p.address_range);
}

bool BindReceiver::operator !=(const BindReceiver &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
