#ifndef SMPP_ENQUIRE_LINK_RESP_H
#define SMPP_ENQUIRE_LINK_RESP_H

#include "smpp/pdu/smpp_header.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT EnquireLinkResp : public Header {
public:
  EnquireLinkResp(quint32 command_status = 0,
                  quint32 sequence_number = 0);

  EnquireLinkResp(const Header &p);

  EnquireLinkResp(const EnquireLinkResp &p);
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_ENQUIRE_LINK_RESP_H
