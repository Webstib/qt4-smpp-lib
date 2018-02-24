#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_bind_transmitter_resp.h"

namespace smpp {

namespace pdu {

BindTransmitterResp::BindTransmitterResp(
  quint32 command_status,
  quint32 sequence_number,
  const QString &system_id) :
  Header(MIN_LENGTH,
         parameters::command_id::BIND_TRANSMITTER_RESP,
         command_status,
         sequence_number),
  system_id(system_id) {

}

BindTransmitterResp::BindTransmitterResp(const Header &p) : Header(p) {

}

BindTransmitterResp::BindTransmitterResp(const BindTransmitterResp &p) :
  Header(p),
  TlvFields(p),
  system_id(p.system_id) {

}

void BindTransmitterResp::setSystemId(const QString &v) {
  system_id = v;
}

QString BindTransmitterResp::getSystemId() const {
  return system_id;
}

quint32 BindTransmitterResp::size() const {
  return MIN_LENGTH + system_id.size() + TlvFields::size();
}

BindTransmitterResp &BindTransmitterResp::operator =(const BindTransmitterResp &p) {
  if(this != &p) {
    Header::operator=(p);
    system_id = p.system_id;
    TlvFields::operator=(p);
  }
  return *this;
}

bool BindTransmitterResp::operator ==(const BindTransmitterResp &p) const {
  return(Header::operator==(p) &&
         system_id == p.system_id &&
         TlvFields::operator==(p));
}

bool BindTransmitterResp::operator !=(const BindTransmitterResp &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
