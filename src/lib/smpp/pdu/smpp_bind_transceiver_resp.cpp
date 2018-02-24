#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_bind_transceiver_resp.h"

namespace smpp {

namespace pdu {

BindTransceiverResp::BindTransceiverResp(
  quint32 command_status,
  quint32 sequence_number,
  const QString &system_id) :
  Header(MIN_LENGTH,
         parameters::command_id::BIND_TRANSCEIVER_RESP,
         command_status,
         sequence_number),
  system_id(system_id) {

}

BindTransceiverResp::BindTransceiverResp(const Header &p) : Header(p) {

}

BindTransceiverResp::BindTransceiverResp(const BindTransceiverResp &p) :
  Header(p),
  TlvFields(p),
  system_id(p.system_id) {

}

void BindTransceiverResp::setSystemId(const QString &v) {
  system_id = v;
}

QString BindTransceiverResp::getSystemId() const {
  return system_id;
}

quint32 BindTransceiverResp::size() const {
  return MIN_LENGTH + system_id.size() + TlvFields::size();
}

BindTransceiverResp &BindTransceiverResp::operator =(const BindTransceiverResp &p) {
  if(this != &p) {
    Header::operator=(p);
    system_id = p.system_id;
    TlvFields::operator=(p);
  }
  return *this;
}

bool BindTransceiverResp::operator ==(const BindTransceiverResp &p) const {
  return(Header::operator==(p) &&
         system_id == p.system_id &&
         TlvFields::operator==(p));
}

bool BindTransceiverResp::operator !=(const BindTransceiverResp &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
