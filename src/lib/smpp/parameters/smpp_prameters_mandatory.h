#ifndef SMPP_PARAMETERS_MANDATORY_H
#define SMPP_PARAMETERS_MANDATORY_H

#include "smpp/smpp_global.h"

namespace smpp {

namespace parameters {

namespace address {
  static const quint32 MAX_LENGTH_NORMAL = 21;
  static const quint32 MAX_LENGTH_DATA_SM = 65;
}

namespace address_range {
  static const quint32 MAX_LENGTH = 41;
}

namespace data_coding {
  static const quint8 SMSC_DEFAULT = 0x00; // SMSC Default Alphabet
  static const quint8 ASCII        = 0x01; // IA5 (CCITT T.50)/ASCII (ANSI X3.4)
  static const quint8 BIT8_2       = 0x02; // Octet unspecified (8-bit bin binary)
  static const quint8 LATIN_1      = 0x03; // Latin 1 (ISO-8859-1)
  static const quint8 BIT8_4       = 0x04; // Octet unspecified (8-bit bin binary)
  static const quint8 JIS          = 0x05; // JIS (X 0208-1990)
  static const quint8 CYRLLIC      = 0x06; // Cyrllic (ISO-8859-5)
  static const quint8 HUBREW       = 0x07; // Latin/Hebrew (ISO-8859-8)
  static const quint8 UCS2         = 0x08; // UCS2 (ISO/IEC-10646)
  static const quint8 PICTOGRAM    = 0x09; // Pictogram Encoding
  static const quint8 MUSIC        = 0x0A; // ISO-2022-JP (Music Codes)
}

namespace dest_flag {
  static const quint8 SME_ADDRESS       = 0x01;
  static const quint8 DISTRIBUTION_LIST = 0x02;
}

namespace dl_name {
  static const quint32 MAX_LENGTH = 21;
}

namespace interface_version {
  static const quint8 V33 = 0x33; // SMPP version 3.3
  static const quint8 V34 = 0x33; // SMPP version 3.4
}

namespace message_id {
  static const quint32 MAX_LENGTH = 65;
}

namespace message_state {
  static const quint8 SCHEDULED     = 0x00;
  static const quint8 ENROUTE       = 0x01;
  static const quint8 DELIVERED     = 0x02;
  static const quint8 EXPIRED       = 0x03;
  static const quint8 DELETED       = 0x04;
  static const quint8 UNDELIVERABLE = 0x05;
  static const quint8 ACCEPTED      = 0x06;
  static const quint8 UNKNOWN       = 0x07;
  static const quint8 REJECTED      = 0x08;
  static const quint8 SKIPPED       = 0x09;
}

namespace ton {
  static const quint8 UNKNOWN           = 0x00;
  static const quint8 INTERNATIONAL     = 0x01;
  static const quint8 NATIONAL          = 0x02;
  static const quint8 NETWORK_SPECIFIC  = 0x03;
  static const quint8 SUBSCRIBER_NUMBER = 0x04;
  static const quint8 ALPHANUMERIC      = 0x05;
  static const quint8 ABBREVIATED       = 0x06;
}

namespace npi {
  static const quint8 UNKNOWN           = 0x00; // Unknown
  static const quint8 ISDN              = 0x01; // ISDN (E163/E164)
  static const quint8 DATA              = 0x02; // Data (X.121)
  static const quint8 TELEX             = 0x03; // Telex (F.69)
  static const quint8 LAND_MOBILE       = 0x06; // Land Mobile (E.212)
  static const quint8 NATIONAL          = 0x08; // National
  static const quint8 PRIVATE           = 0x09; // Private
  static const quint8 ERMES             = 0x0A; // ERMES
  static const quint8 INTERNET_IP       = 0x0E; // Internet (IP)
  static const quint8 WAP_CLIENT_ID     = 0x12; // WAP Client Id (to be defined by WAP Forum)
}

namespace number_of_dests {
  static const quint8 MAX = 0xFE;
}

namespace password {
  static const quint32 MAX_LENGTH = 9;
}

namespace priority_flag {
  static const quint8 LEVEL_0 = 0x00;
  static const quint8 LEVEL_1 = 0x01;
  static const quint8 LEVEL_2 = 0x02;
  static const quint8 LEVEL_3 = 0x03;
}

namespace registered_delivery {
  static const quint8 DEFAULT = 0x00;
}

namespace replace_if_present_flag {
  static const quint8 NO_REPLACE = 0x00;
  static const quint8 REPLACE    = 0x01;
}

namespace service_type {
  static const quint32 MAX_LENGTH = 6;
}

namespace short_message {
  static const quint32 MAX_LENGTH = 254;
  static const quint32 MAX_LENGTH_GSM = 140;
}

namespace sm_default_msg_id {
  static const quint8 UNUSED = 0x00;
}

namespace system_id {
  static const quint32 MAX_LENGTH = 16;
}

namespace system_type {
  static const quint32 MAX_LENGTH = 13;
}

namespace time {
  static const quint32 MAX_LENGTH = 17;
}

} // namespace parameters

} // namespace smpp

#endif // SMPP_PARAMETERS_MANDATORY_H
