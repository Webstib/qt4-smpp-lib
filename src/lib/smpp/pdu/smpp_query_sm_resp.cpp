#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_query_sm_resp.h"

namespace smpp {

namespace pdu {

QuerySmResp::QuerySmResp(quint32 command_status,
                         quint32 sequence_number,
                         const QString &message_id,
                         const QString &final_date,
                         quint8 message_state,
                         quint8 error_code) :
  Header(MIN_LENGTH,
         parameters::command_id::QUERY_SM_RESP,
         command_status,
         sequence_number),
  message_id(message_id),
  final_date(final_date),
  message_state(message_state),
  error_code(error_code) {

}

QuerySmResp::QuerySmResp(const Header &p) :
  Header(p),
  message_state(0),
  error_code(0) {

}

QuerySmResp::QuerySmResp(const QuerySmResp &p) :
  Header(p),
  message_id(p.message_id),
  final_date(p.final_date),
  message_state(p.message_state),
  error_code(p.error_code) {

}

void QuerySmResp::setMessageId(const QString &v) {
  message_id = v;
}

void QuerySmResp::setFinalDate(const QString &v) {
  final_date = v;
}

void QuerySmResp::setMessageState(quint8 v) {
  message_state = v;
}

void QuerySmResp::setErrorCode(quint8 v) {
  error_code = v;
}

QString QuerySmResp::getMessageId() const {
  return message_id;
}

QString QuerySmResp::getFinalDate() const {
  return final_date;
}

quint8 QuerySmResp::getMessageState() const {
  return message_state;
}

quint8 QuerySmResp::getErrorCode() const {
  return error_code;
}

quint32 QuerySmResp::size() const {
  return MIN_LENGTH + message_id.size() + final_date.size();
}

QuerySmResp &QuerySmResp::operator =(const QuerySmResp &p) {
  if(this != &p) {
    Header::operator=(p);
    message_id = p.message_id;
    final_date = p.final_date;
    message_state = p.message_state;
    error_code = p.error_code;
  }
  return *this;
}

bool QuerySmResp::operator ==(const QuerySmResp &p) const {
  return(Header::operator==(p) &&
         message_id == p.message_id &&
         final_date == p.final_date &&
         message_state == p.message_state &&
         error_code == p.error_code);
}

bool QuerySmResp::operator !=(const QuerySmResp &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
