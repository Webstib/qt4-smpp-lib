#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_generic_nack.h"

namespace smpp {

namespace pdu {

GenericNack::GenericNack(quint32 command_status,
                         quint32 sequence_number) :
  Header(HEADER_LENGTH,
         parameters::command_id::GENERIC_NACK,
         command_status,
         sequence_number) {

}

GenericNack::GenericNack(const Header &p) : Header(p) {

}

GenericNack::GenericNack(const GenericNack &p) : Header(p) {

}

} // namespace pdu

} // namespace smpp
