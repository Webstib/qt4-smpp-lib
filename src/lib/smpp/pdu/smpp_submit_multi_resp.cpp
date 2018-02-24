#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_submit_multi_resp.h"

namespace smpp {

namespace pdu {

SubmitMultiResp::SubmitMultiResp(
  quint32 command_status,
  quint32 sequence_number,
  const QString &message_id,
  quint8 no_unsuccess,
  const QList<UnsuccessSme> &unsuccess_smes) :
  Header(MIN_LENGTH,
         parameters::command_id::SUBMIT_MULTI_RESP,
         command_status,
         sequence_number),
  message_id(message_id),
  no_unsuccess(no_unsuccess),
  unsuccess_smes(unsuccess_smes) {

}

SubmitMultiResp::SubmitMultiResp(const Header &p) : Header(p), no_unsuccess(0) {

}

SubmitMultiResp::SubmitMultiResp(const SubmitMultiResp &p) :
  Header(p),
  message_id(p.message_id),
  no_unsuccess(p.no_unsuccess),
  unsuccess_smes(p.unsuccess_smes) {

}

void SubmitMultiResp::setMessageId(const QString &v) {
  message_id = v;
}

void SubmitMultiResp::setNoUnsuccess(quint8 v) {
  no_unsuccess = v;
}

void SubmitMultiResp::add(const UnsuccessSme &p) {
  unsuccess_smes.push_back(p);
}

QString SubmitMultiResp::getMessageId() const {
  return message_id;
}

quint8 SubmitMultiResp::getNoUnsuccess() const {
  return no_unsuccess;
}

const QList<UnsuccessSme> &SubmitMultiResp::getUnsuccessSmes() const {
  return unsuccess_smes;
}

void SubmitMultiResp::remove(const UnsuccessSme &p) {
  unsuccess_smes.removeAll(p);
}

quint32 SubmitMultiResp::size() const {
  quint32 v(MIN_LENGTH + message_id.size());
  foreach(UnsuccessSme sme, unsuccess_smes) {
    v += sme.size();
  }
  return v;
}

SubmitMultiResp &SubmitMultiResp::operator =(const SubmitMultiResp &p) {
  if(*this != p) {
    Header::operator=(p);
    message_id = p.message_id;
    no_unsuccess = p.no_unsuccess;
    unsuccess_smes = p.unsuccess_smes;
  }
  return *this;
}

bool SubmitMultiResp::operator ==(const SubmitMultiResp &p) const {
  return(Header::operator==(p) &&
         message_id == p.message_id &&
         no_unsuccess == p.no_unsuccess &&
         unsuccess_smes == p.unsuccess_smes);
}

bool SubmitMultiResp::operator !=(const SubmitMultiResp &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
