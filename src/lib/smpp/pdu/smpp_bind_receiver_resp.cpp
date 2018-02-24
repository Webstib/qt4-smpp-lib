#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_bind_receiver_resp.h"

namespace smpp {

namespace pdu {

BindReceiverResp::BindReceiverResp(
  quint32 command_status,
  quint32 sequence_number,
  const QString &system_id) :
  Header(MIN_LENGTH,
         parameters::command_id::BIND_RECEIVER_RESP,
         command_status,
         sequence_number),
  system_id(system_id) {

}

BindReceiverResp::BindReceiverResp(const Header &p) : Header(p) {

}

BindReceiverResp::BindReceiverResp(const BindReceiverResp &p) :
  Header(p),
  TlvFields(p),
  system_id(p.system_id) {

}

void BindReceiverResp::setSystemId(const QString &v) {
  system_id = v;
}

QString BindReceiverResp::getSystemId() const {
  return system_id;
}

quint32 BindReceiverResp::size() const {
  return MIN_LENGTH + system_id.size() + TlvFields::size();
}

BindReceiverResp &BindReceiverResp::operator =(const BindReceiverResp &p) {
  if(this != &p) {
    Header::operator=(p);
    system_id = p.system_id;
    TlvFields::operator=(p);
  }
  return *this;
}

bool BindReceiverResp::operator ==(const BindReceiverResp &p) const {
  return(Header::operator==(p) &&
         system_id == p.system_id &&
         TlvFields::operator==(p));
}

bool BindReceiverResp::operator !=(const BindReceiverResp &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
