#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_outbind.h"

namespace smpp {

namespace pdu {

Outbind::Outbind(quint32 sequence_number,
                 const QString &system_id,
                 const QString &password) :
  Header(MIN_LENGTH,
         parameters::command_id::OUTBIND,
         parameters::command_status::ESME_ROK,
         sequence_number),
  system_id(system_id),
  password(password) {

}

Outbind::Outbind(const Header &p) : Header(p) {

}

Outbind::Outbind(const Outbind &p) :
  Header(p),
  system_id(p.system_id),
  password(p.password) {

}

void Outbind::setSystemId(const QString &v) {
  system_id = v;
}

void Outbind::setPassword(const QString &v) {
  password = v;
}

QString Outbind::getSystemId() const {
  return system_id;
}

QString Outbind::getPassword() const {
  return password;
}

quint32 Outbind::size() const {
  return MIN_LENGTH + system_id.size() + password.size();
}

Outbind &Outbind::operator =(const Outbind &p) {
  if(this != &p) {
    Header::operator=(p);
    system_id = p.system_id;
    password = p.password;
  }
  return *this;
}

bool Outbind::operator ==(const Outbind &p) const {
  return(Header::operator==(p) &&
         system_id == p.system_id &&
         password == p.password);
}

bool Outbind::operator !=(const Outbind &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
