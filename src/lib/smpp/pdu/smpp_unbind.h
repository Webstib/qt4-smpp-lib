#ifndef SMPP_UNBIND_H
#define SMPP_UNBIND_H

#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT Unbind : public Header {
public:
  Unbind(quint32 sequence_number = 0);

  Unbind(const Header &p);

  Unbind(const Unbind &p);
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_UNBIND_H
