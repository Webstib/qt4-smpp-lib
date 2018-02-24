#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

Header::Header(quint32 command_length,
               quint32 command_id,
               quint32 command_status,
               quint32 sequence_number) :
  command_length(command_length),
  command_id(command_id),
  command_status(command_status),
  sequence_number(sequence_number) {

}

Header::Header(const Header &p) :
  command_length(p.command_length),
  command_id(p.command_id),
  command_status(p.command_status),
  sequence_number(p.sequence_number) {

}

quint32 Header::getCommandLength() const {
  return command_length;
}

quint32 Header::getCommandId() const {
  return command_id;
}

quint32 Header::getSequenceNumber() const {
  return sequence_number;
}

quint32 Header::getCommandStatus() const{
  return command_status;
}

void Header::setCommandLength(quint32 p) {
  command_length = p;
}

void Header::setCommandId(quint32 p) {
  command_id = p;
}

void Header::setCommandStatus(quint32 p) {
  command_status = p;
}

void Header::setSequenceNumber(quint32 p) {
  sequence_number = p;
}

Header &Header::operator =(const Header &p) {
  if(this != &p) {
    command_length = p.command_length;
    command_id = p.command_id;
    command_status = p.command_status;
    sequence_number = p.sequence_number;
  }
  return *this;
}

bool Header::operator ==(const Header &p) const {
  return (command_length == p.command_length &&
          command_id == p.command_id &&
          command_status == p.command_status &&
          sequence_number == p.sequence_number);
}

bool Header::operator !=(const Header &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
