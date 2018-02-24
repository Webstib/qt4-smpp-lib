#ifndef SMPP_SESSION_GLOBAL_H
#define SMPP_SESSION_GLOBAL_H

#include <QtCore/QObject>
#include "smpp/pdu/smpp_bind_transmitter.h"
#include "smpp/pdu/smpp_bind_transmitter_resp.h"
#include "smpp/pdu/smpp_bind_receiver.h"
#include "smpp/pdu/smpp_bind_receiver_resp.h"
#include "smpp/pdu/smpp_bind_transceiver.h"
#include "smpp/pdu/smpp_bind_transceiver_resp.h"
#include "smpp/pdu/smpp_outbind.h"
#include "smpp/pdu/smpp_unbind.h"
#include "smpp/pdu/smpp_unbind_resp.h"
#include "smpp/pdu/smpp_generic_nack.h"
#include "smpp/pdu/smpp_submit_sm.h"
#include "smpp/pdu/smpp_submit_sm_resp.h"
#include "smpp/pdu/smpp_submit_multi.h"
#include "smpp/pdu/smpp_submit_multi_resp.h"
#include "smpp/pdu/smpp_deliver_sm.h"
#include "smpp/pdu/smpp_deliver_sm_resp.h"
#include "smpp/pdu/smpp_data_sm.h"
#include "smpp/pdu/smpp_data_sm_resp.h"
#include "smpp/pdu/smpp_query_sm.h"
#include "smpp/pdu/smpp_query_sm_resp.h"
#include "smpp/pdu/smpp_cancel_sm.h"
#include "smpp/pdu/smpp_cancel_sm_resp.h"
#include "smpp/pdu/smpp_replace_sm.h"
#include "smpp/pdu/smpp_replace_sm_resp.h"
#include "smpp/pdu/smpp_enquire_link.h"
#include "smpp/pdu/smpp_enquire_link_resp.h"
#include "smpp/pdu/smpp_alert_notification.h"

namespace smpp {

namespace sessions {

enum ErrorCode {
  NET_SOCK_ERR,
  WR_SOCK_ERR,
  RD_SOCK_ERR,
  DEC_HEAD_ERR,
  DEC_BODY_ERR
};

enum SessionStates {
  CLOSED,
  OPEN,
  BOUND_TX,
  BOUND_RX,
  BOUND_TRX,
  UNBOUND,
  OUTBOUND
};

static const int MAX_IN_QUEUE_MSG      = 5000;
static const int MAX_OUT_QUEUE_MSG     = 5000;
static const int MAX_IN_TRANSACTIONS   = 3500;
static const int MAX_OUT_TRANSACTIONS  = 3500;
static const int MIN_IN_SPEED          = 0;    // msec
static const int MIN_OUT_SPEED         = 0;    // msec
static const int MIN_SESSION_INIT_TIME = 10000; // msec
static const int MIN_ENQUIRE_LINK_TIME = 1000; // msec
static const int MIN_INACTIVITY_TIME   = 100;  // msec
static const int MIN_TRANSACTION_TIME  = 1000; // msec

} // namespace sessions

} // namespace smpp

#endif // SMPP_SESSION_GLOBAL_H
