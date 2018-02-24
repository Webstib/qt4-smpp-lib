#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_submit_sm_resp.h"

namespace smpp {

namespace pdu {

SubmitSmResp::SubmitSmResp(quint32 command_status,
                           quint32 sequence_number,
                           const QString &message_id) :
  Header(MIN_LENGTH,
         parameters::command_id::SUBMIT_SM_RESP,
         command_status,
         sequence_number),
  message_id(message_id) {

}

SubmitSmResp::SubmitSmResp(const Header &p) : Header(p) {

}

SubmitSmResp::SubmitSmResp(const SubmitSmResp &p) :
  Header(p),
  message_id(p.message_id) {

}

void SubmitSmResp::setMessageId(const QString &v) {
  message_id = v;
}

QString SubmitSmResp::getMessageId() const {
  return message_id;
}

quint32 SubmitSmResp::size() const {
  return MIN_LENGTH + message_id.size();
}

SubmitSmResp &SubmitSmResp::operator =(const SubmitSmResp &p) {
  if(this != &p) {
    Header::operator=(p);
    message_id = p.message_id;
  }
  return *this;
}

bool SubmitSmResp::operator ==(const SubmitSmResp &p) const {
  return(Header::operator==(p) && message_id == p.message_id);
}

bool SubmitSmResp::operator !=(const SubmitSmResp &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
