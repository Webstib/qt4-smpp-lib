#ifndef SMPP_HEADER_H
#define SMPP_HEADER_H

#include "smpp/smpp_global.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT Header {
public:
  Header(quint32 command_length = 0,
         quint32 command_id = 0,
         quint32 command_status = 0,
         quint32 sequence_number = 0);

  Header(const Header &p);

  quint32 getCommandLength() const;

  quint32 getCommandId() const;

  quint32 getSequenceNumber() const;

  quint32 getCommandStatus() const;

  void setCommandLength(quint32 p);

  void setCommandId(quint32 p);

  void setCommandStatus(quint32 p);

  void setSequenceNumber(quint32 p);

  Header &operator =(const Header &p);

  bool operator ==(const Header &p) const;

  bool operator !=(const Header &p) const;

  static const quint32 HEADER_LENGTH = 16;

protected:

  quint32 command_length;
  quint32 command_id;
  quint32 command_status;
  quint32 sequence_number;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_HEADER_H
