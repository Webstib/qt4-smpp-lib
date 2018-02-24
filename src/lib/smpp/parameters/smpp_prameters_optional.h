#ifndef SMPP_PARAMETERS_OPTIONAL_H
#define SMPP_PARAMETERS_OPTIONAL_H

#include "smpp/smpp_global.h"

namespace smpp {

namespace parameters {

namespace tag {
  static const quint16 DEST_ADDR_SUBUNIT           = 0x0005;
  static const quint16 DEST_NETWORK_TYPE           = 0x0006;
  static const quint16 DEST_BEARER_TYPE            = 0x0007;
  static const quint16 DEST_TELEMATICS_ID          = 0x0008;
  static const quint16 SOURCE_ADDRSUBUINIT         = 0x000D;
  static const quint16 SOURCE_NETWORK_TYPE         = 0x000E;
  static const quint16 SOURCE_BEARER_TYPE          = 0x000F;
  static const quint16 SOURCE_TELEMATICS_ID        = 0x0010;
  static const quint16 QOS_TIME_TO_LIVE            = 0x0017;
  static const quint16 PAYLOAD_TYPE                = 0x0019;
  static const quint16 ADDITIONAL_STATUS_INFO_TEXT = 0x001D;
  static const quint16 RECEIPTED_MESSAGE_ID        = 0x001E;
  static const quint16 MS_MSG_WAIT_FACILITIES      = 0x0030;
  static const quint16 PRIVACY_INDICATOR           = 0x0201;
  static const quint16 SOURCE_SUBADDRESS           = 0x0202;
  static const quint16 DEST_SUBADDRESS             = 0x0203;
  static const quint16 USER_MESSAGE_REFERENCE      = 0x0204;
  static const quint16 USER_RESPONSE_CODE          = 0x0205;
  static const quint16 SOURCE_PORT                 = 0x020A;
  static const quint16 DESTINATION_PORT            = 0x020B;
  static const quint16 SAR_MSG_REF_NUM             = 0x020C;
  static const quint16 LANGUAGE_INDICATOR          = 0x020D;
  static const quint16 SAR_TOTAL_SEGMENTS          = 0x020E;
  static const quint16 SAR_SEGMENT_SEQNUM          = 0x020F;
  static const quint16 SC_INTERFACE_VERSION        = 0x0210;
  static const quint16 CALLBACK_NUM_PRES_IND       = 0x0302;
  static const quint16 CALLBACK_NUM_ATAG           = 0x0303;
  static const quint16 NUMBER_OF_MESSAGES          = 0x0304;
  static const quint16 CALLBACK_NUM                = 0x0381;
  static const quint16 DPF_RESULT                  = 0x0420;
  static const quint16 SET_DPF                     = 0x0421;
  static const quint16 MS_AVAILABILITY_STATUS      = 0x0422;
  static const quint16 NETWORK_ERROR_CODE          = 0x0423;
  static const quint16 MESSAGE_PAYLOAD             = 0x0424;
  static const quint16 DELIVERY_FAILURE_REASON     = 0x0425;
  static const quint16 MORE_MESSAGES_TO_SEND       = 0x0426;
  static const quint16 MESSAGE_STATE               = 0x0427;
  static const quint16 CONGESTION_STATE            = 0x0428;
  static const quint16 USSD_SERVICE_OP             = 0x0501;
  static const quint16 DISPLAY_TIME                = 0x1201;
  static const quint16 SMS_SIGNAL                  = 0x1203;
  static const quint16 MS_VALIDITY                 = 0x1204;
  static const quint16 ALERT_ON_MESSAGE_DELIVERY   = 0x130C;
  static const quint16 ITS_REPLY_TYPE              = 0x1380;
  static const quint16 ITS_SESSION_INFO            = 0x1383;
}

namespace additional_status_info_text {
  static const quint32 MAX_LENGTH = 256;
}

namespace callback_num {
  static const quint32 MIN_LENGTH = 4;
  static const quint32 MAX_LENGTH = 19;
}

namespace callback_num_atag {
  static const quint32 MAX_LENGTH = 65;
}

namespace delivery_failure_reason {
  static const quint8 UNAVAILABLE          = 0x00; // Destination unavailable
  static const quint8 INVALID              = 0x01; // Destination Address Invalid (e.g. suspended, no SMS capability, etc.)
  static const quint8 PREMANENT_NET_ERROR  = 0x02; // Permanent network error
  static const quint8 TEMPRORARY_NET_ERROR = 0x03; // Temporary network error
}

namespace addr_subunit {
  static const quint8 UNKNOWN          = 0x00; // Unknown (default)
  static const quint8 MS_DISPLAY       = 0x01; // MS Display
  static const quint8 MODILE_EQUIPMENT = 0x02; // Mobile Equipment
  static const quint8 SMART_CARD_1     = 0x03; // Smart Card 1 (expected to be a SIM exists in the MS)
  static const quint8 EXTERNAL_UNIT_1  = 0x04; // External Unit 1
}

namespace bearer_type {
  static const quint8 UNKNOWN     = 0x00; // Unknown
  static const quint8 SMS         = 0x01; // SMS
  static const quint8 CSD         = 0x02; // Circuit Switched Data (CSD)
  static const quint8 PACKET_DATA = 0x03; // Packet Data
  static const quint8 USSD        = 0x04; // USSD
  static const quint8 CDPD        = 0x05; // CDPD
  static const quint8 DATA_TAC    = 0x06; // DataTAC
  static const quint8 FLEX        = 0x07; // FLEX/ReFLEX
  static const quint8 CELLCAST    = 0x08; // Cell Broadcast (cellcast)
}

namespace network_type {
  static const quint8 UNKNOWN        = 0x00; // Unknown
  static const quint8 GSM            = 0x01; // GSM
  static const quint8 ANSI136        = 0x02; // ANSI-136/TDMA
  static const quint8 IS95           = 0x03; // IS-95/CDMA
  static const quint8 PDC            = 0x04; // PDC
  static const quint8 PHS            = 0x05; // PHS
  static const quint8 IDEN           = 0x06; // iDEN
  static const quint8 AMPS           = 0x07; // AMPS
  static const quint8 PAGING_NETWORK = 0x08; // Paging Network
}

namespace subaddress {
  static const quint32 MIN_LENGTH = 2;
  static const quint32 MAX_LENGTH = 23;
}

namespace display_time {
  static const quint8 TEMPORARY = 0x00; // Temporary
  static const quint8 DEFAULT   = 0x01; // Default (default)
  static const quint8 INVOKE    = 0x02; // Invoke
}

namespace dpf_result {
  static const quint8 DPF_NOT_SET = 0x00; // DPF not set
  static const quint8 DPF_SET     = 0x01; // DPF set
}

namespace its_reply_type {
  static const quint8 DIGIT          = 0x00;
  static const quint8 NUMBER         = 0x01;
  static const quint8 TELEPHONE_NO   = 0x02;
  static const quint8 PASSWORD       = 0x03;
  static const quint8 CHARACTER_LINE = 0x04;
  static const quint8 MENU           = 0x05;
  static const quint8 DATE           = 0x06;
  static const quint8 TIME           = 0x07;
  static const quint8 CONTINUE       = 0x08;
}

namespace language_indicator {
  static const quint8 UNSPECIFIED = 0x00; // unspecified (default)
  static const quint8 ENGLISH     = 0x01; // english
  static const quint8 FRENCH      = 0x02; // french
  static const quint8 SPANISH     = 0x03; // spanish
  static const quint8 GERMAN      = 0x04; // german
  static const quint8 PORTUGUESE  = 0x05; // Portuguese
}

namespace more_messages_to_send {
  static const quint8 NO_MORE = 0x00; // No more messages to follow
  static const quint8 MORE    = 0x01; // More messages to follow (default)
}

namespace ms_availability_status {
  static const quint8 AVAILABLE   = 0x00; // Available (Default)
  static const quint8 DENIED      = 0x01; // Denied (e.g. suspended, no SMS capability, etc.)
  static const quint8 UNAVAILABLE = 0x02; // Unavailable
}

namespace ms_validity {
  static const quint8 STORE_INDEFINITELY = 0x00; // Store Indefinitely (default)
  static const quint8 POWER_DOWN         = 0x01; // Power Down
  static const quint8 SID_BRA            = 0x02; // SID based registration area
  static const quint8 DISPLAY_ONLY       = 0x03; // Display Only
}

namespace network_error_code {
  static const quint8 ANSI136  = 0x00; // ANSI-136
  static const quint8 IS95     = 0x01; // IS-95
  static const quint8 GSM      = 0x02; // GSM
  static const quint8 RESERVED = 0x02; // Reserved
}

namespace payload_type {
  static const quint8 DFAULT = 0x00; // Default. In the case of a WAP
                                     // application, the default higher layer
                                     // message type is a WDP message.
                                     // See [WDP] for details.
  static const quint8 WCMP   = 0x01; // WCMP message. Wireless Control
                                     // Message Protocol formatted data.
                                     // See [WCMP] for details.
}

namespace privacy_indicator {
  static const quint8 LEVEL0 = 0x00; // Privacy Level 0 (Not Restricted) (default)
  static const quint8 LEVEL1 = 0x01; // Privacy Level 1 (Restricted)
  static const quint8 LEVEL2 = 0x02; // Privacy Level 2 (Confidential)
  static const quint8 LEVEL3 = 0x03; // Privacy Level 3 (Secret)
}

namespace set_dpf {
  static const quint8 DPF_NOT_REQUEST = 0x00; // Setting of DPF for delivery failure to MS not requested
  static const quint8 DPF_REQUEST     = 0x01; // Setting of DPF for delivery failure requested (default)
}

namespace ussd_service_op {
  static const quint8 PSSD_IND  = 0x00; // PSSD indication
  static const quint8 PSSR_IND  = 0x01; // PSSR indication
  static const quint8 USSR_REQ  = 0x02; // USSR request
  static const quint8 USSN_REQ  = 0x03; // USSN request
  // 4 to 15  = reserved
  static const quint8 PSSD_RESP = 0x10; // PSSD response
  static const quint8 PSSR_RESP = 0x11; // PSSR response
  static const quint8 USSR_CONF = 0x12; // USSR confirm
  static const quint8 USSN_CONF = 0x13; // USSN confirm
  // 20 to 31  = reserved
  // 32 to 255 = reserved for vendor s USSD operations
}

} // namespace parameters

} // namespace smpp

#endif // SMPP_PARAMETERS_OPTIONAL_H
