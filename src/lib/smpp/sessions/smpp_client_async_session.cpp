#include <QtNetwork/QHostAddress>
#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/encoders/smpp_binary_encoder.h"
#include "smpp/sessions/smpp_client_async_session.h"
#include "smpp/sessions/smpp_client_async_session_p.h"

namespace smpp {

namespace sessions {

using namespace pdu;
using namespace decoders;
using namespace encoders;

ClientAsyncSessionPrivate::ClientAsyncSessionPrivate(
  ClientAsyncSession *parent,
  int in_speed, // msec
  int out_speed, // msec
  int session_init_time,
  int enquire_link_time,
  int inactivity_time,
  int transaction_time,
  int max_in_msg,
  int max_out_msg,
  int max_in_trans,
  int max_out_trans,
  bool threaded) :
  QObject(parent),
  in_speed(in_speed),
  out_speed(out_speed),
  session_init_time(session_init_time),
  enquire_link_time(enquire_link_time),
  inactivity_time(inactivity_time),
  transaction_time(transaction_time),
  in_speed_timer_id(-1),
  out_speed_timer_id(-1),
  session_init_timer_id(-1),
  enquire_link_timer_id(-1),
  inactivity_timer_id(-1),
  max_in_msg(max_in_msg),
  max_out_msg(max_out_msg),
  max_in_trans(max_in_trans),
  max_out_trans(max_out_trans),
  now_state(CLOSED),
  socket(new QTcpSocket(this)),
  peer_port(0),
  local_port(0),
  thread(0),
  parent(parent) {

  if(threaded) {
    if(QMetaType::type("smpp::sessions::ErrorCode") == 0)
      qRegisterMetaType<smpp::sessions::ErrorCode>("smpp::sessions::ErrorCode");
    if(QMetaType::type("QAbstractSocket::SocketError") == 0)
      qRegisterMetaType<QAbstractSocket::SocketError>(
        "QAbstractSocket::SocketError");
    if(QMetaType::type("SessionStates") == 0)
      qRegisterMetaType<smpp::sessions::SessionStates>("SessionStates");
    if(QMetaType::type("smpp::pdu::AlertNotification") == 0)
      qRegisterMetaType<smpp::pdu::AlertNotification>(
        "smpp::pdu::AlertNotification");
    if(QMetaType::type("smpp::pdu::BindTransmitter") == 0)
      qRegisterMetaType<smpp::pdu::BindTransmitter>(
        "smpp::pdu::BindTransmitter");
    if(QMetaType::type("smpp::pdu::BindTransmitterResp") == 0)
      qRegisterMetaType<smpp::pdu::BindTransmitterResp>(
        "smpp::pdu::BindTransmitterResp");
    if(QMetaType::type("smpp::pdu::BindReceiver") == 0)
      qRegisterMetaType<smpp::pdu::BindReceiver>("smpp::pdu::BindReceiver");
    if(QMetaType::type("smpp::pdu::BindReceiverResp") == 0)
      qRegisterMetaType<smpp::pdu::BindReceiverResp>(
        "smpp::pdu::BindReceiverResp");
    if(QMetaType::type("smpp::pdu::BindTransceiver") == 0)
      qRegisterMetaType<smpp::pdu::BindTransceiver>(
        "smpp::pdu::BindTransceiver");
    if(QMetaType::type("smpp::pdu::BindTransceiverResp") == 0)
      qRegisterMetaType<smpp::pdu::BindTransceiverResp>(
        "smpp::pdu::BindTransceiverResp");
    if(QMetaType::type("smpp::pdu::Unbind") == 0)
      qRegisterMetaType<smpp::pdu::Unbind>("smpp::pdu::Unbind");
    if(QMetaType::type("smpp::pdu::UnbindResp") == 0)
      qRegisterMetaType<smpp::pdu::UnbindResp>("smpp::pdu::UnbindResp");
    if(QMetaType::type("smpp::pdu::Outbind") == 0)
      qRegisterMetaType<smpp::pdu::Outbind>("smpp::pdu::Outbind");
    if(QMetaType::type("smpp::pdu::GenericNack") == 0)
      qRegisterMetaType<smpp::pdu::GenericNack>("smpp::pdu::GenericNack");
    if(QMetaType::type("smpp::pdu::SubmitSm") == 0)
      qRegisterMetaType<smpp::pdu::SubmitSm>("smpp::pdu::SubmitSm");
    if(QMetaType::type("smpp::pdu::SubmitSmResp") == 0)
      qRegisterMetaType<smpp::pdu::SubmitSmResp>("smpp::pdu::SubmitSmResp");
    if(QMetaType::type("smpp::pdu::SubmitMulti") == 0)
      qRegisterMetaType<smpp::pdu::SubmitMulti>("smpp::pdu::SubmitMulti");
    if(QMetaType::type("smpp::pdu::SubmitMultiResp") == 0)
      qRegisterMetaType<smpp::pdu::SubmitMultiResp>(
        "smpp::pdu::SubmitMultiResp");
    if(QMetaType::type("smpp::pdu::DeliverSm") == 0)
      qRegisterMetaType<smpp::pdu::DeliverSm>("smpp::pdu::DeliverSm");
    if(QMetaType::type("smpp::pdu::DeliverSmResp") == 0)
      qRegisterMetaType<smpp::pdu::DeliverSmResp>("smpp::pdu::DeliverSmResp");
    if(QMetaType::type("smpp::pdu::DataSm") == 0)
      qRegisterMetaType<smpp::pdu::DataSm>("smpp::pdu::DataSm");
    if(QMetaType::type("smpp::pdu::DataSmResp") == 0)
      qRegisterMetaType<smpp::pdu::DataSmResp>("smpp::pdu::DataSmResp");
    if(QMetaType::type("smpp::pdu::QuerySm") == 0)
      qRegisterMetaType<smpp::pdu::QuerySm>("smpp::pdu::QuerySm");
    if(QMetaType::type("smpp::pdu::QuerySmResp") == 0)
      qRegisterMetaType<smpp::pdu::QuerySmResp>("smpp::pdu::QuerySmResp");
    if(QMetaType::type("smpp::pdu::ReplaceSm") == 0)
      qRegisterMetaType<smpp::pdu::ReplaceSm>("smpp::pdu::ReplaceSm");
    if(QMetaType::type("smpp::pdu::ReplaceSmResp") == 0)
      qRegisterMetaType<smpp::pdu::ReplaceSmResp>("smpp::pdu::ReplaceSmResp");
    if(QMetaType::type("smpp::pdu::EnquireLink") == 0)
      qRegisterMetaType<smpp::pdu::EnquireLink>("smpp::pdu::EnquireLink");
    if(QMetaType::type("smpp::pdu::EnquireLinkResp") == 0)
      qRegisterMetaType<smpp::pdu::EnquireLinkResp>(
        "smpp::pdu::EnquireLinkResp");

    thread = new QThread(this);
  }

  if(in_speed != -1 && in_speed < MIN_IN_SPEED) {
    this->in_speed = MIN_IN_SPEED;
  }
  if(out_speed != -1 && out_speed < MIN_OUT_SPEED) {
    this->out_speed = MIN_OUT_SPEED;
  }
  if(session_init_time != -1 && session_init_time < MIN_SESSION_INIT_TIME) {
    this->session_init_time = MIN_SESSION_INIT_TIME;
  }
  if(enquire_link_time != -1 && enquire_link_time < MIN_ENQUIRE_LINK_TIME) {
    this->enquire_link_time = MIN_ENQUIRE_LINK_TIME;
  }
  if(inactivity_time != -1 && inactivity_time < MIN_INACTIVITY_TIME) {
    this->inactivity_time = MIN_INACTIVITY_TIME;
  }
  if(transaction_time != -1 && transaction_time < MIN_TRANSACTION_TIME) {
    this->transaction_time = MIN_TRANSACTION_TIME;
  }

  connect(this, SIGNAL(sigSetInSpeed(int)),
          this, SLOT(setInSpeed(int)));
  connect(this, SIGNAL(sigSetOutSpeed(int)),
          this, SLOT(setOutSpeed(int)));
  connect(this, SIGNAL(sigSetSessionInitTime(int)),
          this, SLOT(setSessionInitTime(int)));
  connect(this, SIGNAL(sigSetEnquireLinkTime(int)),
          this, SLOT(setEnquireLinkTime(int)));
  connect(this, SIGNAL(sigSetInactivityTime(int)),
          this, SLOT(setInactivityTime(int)));
  connect(this, SIGNAL(sigOpenSession(const QString &, quint16)),
          this, SLOT(openSession(const QString &, quint16)));
  connect(this, SIGNAL(sigCloseSession()),
          this, SLOT(closeSession()));
  connect(this, SIGNAL(sigSend(const smpp::pdu::BindTransmitter &)),
          this, SLOT(send(const smpp::pdu::BindTransmitter &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::BindReceiver &)),
          this, SLOT(send(const smpp::pdu::BindReceiver &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::BindTransceiver &)),
          this, SLOT(send(const smpp::pdu::BindTransceiver &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::Unbind &)),
          this, SLOT(send(const smpp::pdu::Unbind &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::GenericNack &)),
          this, SLOT(send(const smpp::pdu::GenericNack &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::SubmitSm &)),
          this, SLOT(send(const smpp::pdu::SubmitSm &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::SubmitMulti &)),
          this, SLOT(send(const smpp::pdu::SubmitMulti &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::DeliverSmResp &)),
          this, SLOT(send(const smpp::pdu::DeliverSmResp &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::DataSm &)),
          this, SLOT(send(const smpp::pdu::DataSm &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::DataSmResp &)),
          this, SLOT(send(const smpp::pdu::DataSmResp &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::QuerySm &)),
          this, SLOT(send(const smpp::pdu::QuerySm &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::ReplaceSm &)),
          this, SLOT(send(const smpp::pdu::ReplaceSm &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::EnquireLink &)),
          this, SLOT(send(const smpp::pdu::EnquireLink &)));
  connect(this, SIGNAL(sigSend(const smpp::pdu::EnquireLinkResp &)),
          this, SLOT(send(const smpp::pdu::EnquireLinkResp &)));

  connect(socket, SIGNAL(connected()),
          this, SLOT(socketConnected()));
  connect(socket, SIGNAL(disconnected()),
          this, SLOT(socketDisconnected()));
  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(socketError(QAbstractSocket::SocketError)));
  connect(socket, SIGNAL(readyRead()),
          this, SLOT(socketReadyRead()));
}

ClientAsyncSessionPrivate::~ClientAsyncSessionPrivate() {
  clearAllQueue();
  if(socket) {
    socket = 0;
  }
  if(thread) {
    thread = 0;
  }
}

QHostAddress ClientAsyncSessionPrivate::peerAddress() const {
  QMutexLocker locker(&mutex);
  return peer_address;
}

QHostAddress ClientAsyncSessionPrivate::localAddress() const {
  QMutexLocker locker(&mutex);
  return local_address;
}

QString ClientAsyncSessionPrivate::errorString() const {
  QMutexLocker locker(&mutex);
  return error_message;
}

void ClientAsyncSessionPrivate::setInSpeed(int in_speed) {
  this->in_speed = in_speed;
  restartInSpeedTimer();
}

void ClientAsyncSessionPrivate::setOutSpeed(int out_speed) {
  this->out_speed = out_speed;
  restartOutSpeedTimer();
}

void ClientAsyncSessionPrivate::setSessionInitTime(int session_init_time) {
  this->session_init_time = session_init_time;
  restartSessionInitTimer();
}

void ClientAsyncSessionPrivate::setEnquireLinkTime(int enquire_link_time) {
  this->enquire_link_time = enquire_link_time;
  restartEnquireLinkTimer();
}

void ClientAsyncSessionPrivate::setInactivityTime(int inactivity_time) {
  this->inactivity_time = inactivity_time;
  restartInactivityTimer();
}

void ClientAsyncSessionPrivate::send(const BindTransmitter &p) {
  BindTransmitter *pt(new BindTransmitter(p));
  if(p.getCommandId() == parameters::command_id::BIND_TRANSMITTER) {
    send(pt);
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const BindReceiver &p) {
  BindReceiver *pt(new BindReceiver(p));
  if(p.getCommandId() == parameters::command_id::BIND_RECEIVER) {
    send(pt);
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const BindTransceiver &p) {
  BindTransceiver *pt(new BindTransceiver(p));
  if(p.getCommandId() == parameters::command_id::BIND_TRANSCEIVER) {
    send(pt);
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const Unbind &p) {
  Unbind *pt(new Unbind(p));
  if(p.getCommandId() == parameters::command_id::UNBIND) {
    send(pt);
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const GenericNack &p) {
  if(p.getCommandId() == parameters::command_id::GENERIC_NACK) {
    send(new GenericNack(p));
  }
}

void ClientAsyncSessionPrivate::send(const SubmitSm &p) {
  SubmitSm *pt(new SubmitSm(p));
  if(p.getCommandId() == parameters::command_id::SUBMIT_SM) {
    if(out_speed > 0) {
      if(!addMessageOutQueue(pt))
        outError(pt, parameters::command_status::ESME_OUTQUEUEFULL);
    } else {
      send(pt);
    }
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const SubmitMulti &p) {
  SubmitMulti *pt(new SubmitMulti(p));
  if(p.getCommandId() == parameters::command_id::SUBMIT_MULTI) {
    if(out_speed > 0) {
      if(!addMessageOutQueue(pt))
        outError(pt, parameters::command_status::ESME_OUTQUEUEFULL);
    } else {
      send(pt);
    }
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const DeliverSmResp &p) {
  if(p.getCommandId() == parameters::command_id::DELIVER_SM_RESP) {
    send(new DeliverSmResp(p));
  }
}

void ClientAsyncSessionPrivate::send(const DataSm &p) {
  DataSm *pt(new DataSm(p));
  if(p.getCommandId() == parameters::command_id::DATA_SM) {
    if(out_speed > 0) {
      if(!addMessageOutQueue(pt))
        outError(pt, parameters::command_status::ESME_OUTQUEUEFULL);
    } else {
      send(pt);
    }
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const DataSmResp &p) {
  if(p.getCommandId() == parameters::command_id::DATA_SM_RESP) {
    send(new DataSmResp(p));
  }
}

void ClientAsyncSessionPrivate::send(const QuerySm &p) {
  QuerySm *pt(new QuerySm(p));
  if(p.getCommandId() == parameters::command_id::QUERY_SM) {
    if(out_speed > 0) {
      if(!addMessageOutQueue(pt))
        outError(pt, parameters::command_status::ESME_OUTQUEUEFULL);
    } else {
      send(pt);
    }
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const ReplaceSm &p) {
  ReplaceSm *pt(new ReplaceSm(p));
  if(p.getCommandId() == parameters::command_id::REPLACE_SM) {
    if(out_speed > 0) {
      if(!addMessageOutQueue(pt))
        outError(pt, parameters::command_status::ESME_OUTQUEUEFULL);
    } else {
      send(pt);
    }
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const EnquireLink &p) {
  EnquireLink *pt(new EnquireLink(p));
  if(p.getCommandId() == parameters::command_id::ENQUIRE_LINK) {
    send(pt);
  } else {
    outError(pt, parameters::command_status::ESME_RINVCMDID);
  }
}

void ClientAsyncSessionPrivate::send(const EnquireLinkResp &p) {
  if(p.getCommandId() == parameters::command_id::ENQUIRE_LINK_RESP) {
    send(new EnquireLinkResp(p));
  }
}

void ClientAsyncSessionPrivate::openSession(
  const QString &host_name, quint16 port) {
  if(now_state == CLOSED &&
     socket &&
     socket->state() == QAbstractSocket::UnconnectedState) {
    socket->connectToHost(host_name, port);
  }
}

void ClientAsyncSessionPrivate::closeSession() {
  if(socket && socket->state() == QAbstractSocket::ConnectedState) {
    socket->disconnectFromHost();
  }
}

void ClientAsyncSessionPrivate::socketConnected() {
  mutex.lock();
  peer_address = socket->peerAddress();
  local_address = socket->localAddress();
  mutex.unlock();
  peer_port = socket->peerPort();
  local_port = socket->localPort();

  setState(OPEN);
}

void ClientAsyncSessionPrivate::socketDisconnected() {
  setState(CLOSED);
}

void ClientAsyncSessionPrivate::socketError(
  QAbstractSocket::SocketError error) {
  if(error == QAbstractSocket::RemoteHostClosedError &&
     (now_state == OPEN || now_state == UNBOUND || now_state == OUTBOUND)) {
    setState(CLOSED);
  } else {
    procError(NET_SOCK_ERR, socket->errorString());
  }
}

void ClientAsyncSessionPrivate::socketReadyRead() {
  while(socket->bytesAvailable() > 0) {
    QByteArray bytes;
    quint32 read_bytes(0);

    while(read_bytes != Header::HEADER_LENGTH) {
      bytes += socket->read(Header::HEADER_LENGTH - read_bytes);

      read_bytes = bytes.count();

      if(read_bytes != Header::HEADER_LENGTH) {
        if(!socket->waitForReadyRead()) {
          return procError(RD_SOCK_ERR, "Not read bytes for decode header");
        }
      }
    }

    BinaryDecoder decoder(bytes);

    bytes.clear();
    read_bytes = 0;

    Header header;

    bool res(decoder.decode(header));

    if(!res) {
      return procError(DEC_HEAD_ERR, "Decode error header");
    }

    if(header.getCommandLength() < Header::HEADER_LENGTH) {
      return procError(DEC_HEAD_ERR, "CommandLength less header length");
    }

    quint32 body_length(header.getCommandLength() - Header::HEADER_LENGTH);

    while(read_bytes != body_length) {
      bytes += socket->read(body_length - read_bytes);

      read_bytes = bytes.count();

      if(read_bytes != body_length) {
        if(!socket->waitForReadyRead()) {
          return procError(RD_SOCK_ERR, "Not read bytes for decode body");
          return;
        }
      }
    }

    if(read_bytes > 0) {
      decoder.addBody(bytes);
      bytes.clear();
    }

    switch(header.getCommandId()) {
      case parameters::command_id::BIND_TRANSMITTER_RESP: {
        BindTransmitterResp *p(new BindTransmitterResp(header));
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR,
                           "Decode error BindTransmitterResp body");
        }
        break;
      }
      case parameters::command_id::BIND_RECEIVER_RESP: {
        BindReceiverResp *p(new BindReceiverResp(header));
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR,
                           "Decode error BindReceiverResp body");
        }
        break;
      }
      case parameters::command_id::BIND_TRANSCEIVER_RESP: {
        BindTransceiverResp *p(new BindTransceiverResp(header));
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR,
                           "Decode error BindTransceiverResp body");
        }
        break;
      }
      case parameters::command_id::OUTBIND: {
        receive(new Outbind(header));
        break;
      }
      case parameters::command_id::UNBIND_RESP: {
        receive(new UnbindResp(header));
        break;
      }
      case parameters::command_id::GENERIC_NACK: {
        receive(new GenericNack(header));
        break;
      }
      case parameters::command_id::SUBMIT_SM_RESP: {
        SubmitSmResp *p = new SubmitSmResp(header);
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error SubmitSmResp body");
        }
        break;
      }
      case parameters::command_id::SUBMIT_MULTI_RESP: {
        SubmitMultiResp *p = new SubmitMultiResp(header);
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error SubmitMultiResp body");
        }
        break;
      }
      case parameters::command_id::DELIVER_SM: {
        DeliverSm *p(new DeliverSm(header));
        res = decoder.decode(*p);
        if(res) {
          if(in_speed > 0) {
            if(!addMessageInQueue(p))
              inError(p, parameters::command_status::ESME_INQUEUEFULL);
          } else {
            receive(p);
          }
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error DeliverSm body");
        }
        break;
      }
      case parameters::command_id::DATA_SM: {
        DataSm *p(new DataSm(header));
        res = decoder.decode(*p);
        if(res) {
          if(in_speed > 0) {
            if(!addMessageInQueue(p))
              inError(p, parameters::command_status::ESME_INQUEUEFULL);
          } else {
            receive(p);
          }
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error DataSm body");
        }
        break;
      }
      case parameters::command_id::DATA_SM_RESP: {
        DataSmResp *p(new DataSmResp(header));
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error DataSmResp body");
        }
        break;
      }
      case parameters::command_id::QUERY_SM_RESP: {
        QuerySmResp *p(new QuerySmResp(header));
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error QuerySmResp body");
        }
        break;
      }
      case parameters::command_id::REPLACE_SM_RESP: {
        ReplaceSmResp *p(new ReplaceSmResp(header));
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error ReplaceSmResp body");
        }
        break;
      }
      case parameters::command_id::ENQUIRE_LINK: {
        receive(new EnquireLink(header));
        break;
      }
      case parameters::command_id::ENQUIRE_LINK_RESP: {
        receive(new EnquireLinkResp(header));
        break;
      }
      case parameters::command_id::ALERT_NOTIFICATION:  {
        AlertNotification *p(new AlertNotification(header));
        res = decoder.decode(*p);
        if(res) {
          receive(p);
        } else {
          delete p;
          return procError(DEC_BODY_ERR, "Decode error AlertNotification body");
        }
        break;
      }
      default:
        return procError(DEC_BODY_ERR, "Unknown CommandId");
    }
    sessionActivity();
  }
}

void ClientAsyncSessionPrivate::setState(SessionStates state) {
  if(now_state == state)
    return;

  switch(state) {
    case CLOSED: {
      if(now_state == OPEN || now_state == UNBOUND || now_state == OUTBOUND) {
        stopSessionInitTimer();
        stopEnquireLinkTimer();
        stopInSpeedTimer();
        stopOutSpeedTimer();
        stopInactivityTimer();
        removeAllInTransactions();
        removeAllOutTransactions();
      }
      break;
    }
    case OPEN: {
      if(now_state == CLOSED ||
         now_state == UNBOUND ||
         now_state == OUTBOUND) {
        startSessionInitTimer();
        startEnquireLinkTimer();
        stopInSpeedTimer();
        stopOutSpeedTimer();
        stopInactivityTimer();
      }
      break;
    }
    case BOUND_TX:
    case BOUND_RX:
    case BOUND_TRX: {
      if(now_state == OPEN || now_state == OUTBOUND) {
        stopSessionInitTimer();
        startEnquireLinkTimer();
        startInSpeedTimer();
        startOutSpeedTimer();
        startInactivityTimer();
      }
      break;
    }
    case UNBOUND: {
      if(now_state == BOUND_TX ||
         now_state == BOUND_RX ||
         now_state == BOUND_TRX) {
        stopSessionInitTimer();
        startEnquireLinkTimer();
        stopInSpeedTimer();
        stopOutSpeedTimer();
        stopInactivityTimer();
      }
      break;
    }
    case OUTBOUND: {
      if(now_state == OPEN) {
        startSessionInitTimer();
        startEnquireLinkTimer();
        stopInSpeedTimer();
        stopOutSpeedTimer();
        stopInactivityTimer();
      }
      break;
    }
  }

  now_state = state;

  clearInQueue();
  clearOutQueue();

  emit parent->stateChanged(now_state);

  if(now_state == CLOSED) {
    emit parent->closedSession();
  } else if(now_state == OPEN) {
    emit parent->openedSession();
  }
}

void ClientAsyncSessionPrivate::timerEvent(QTimerEvent *event) {
  int timer_id = event->timerId();

  if(timer_id == in_speed_timer_id) {
    processInQueue();
  } else if(timer_id == out_speed_timer_id) {
    processOutQueue();
  } else if(timer_id == session_init_timer_id) {
    procSessionInitTimeout();
  } else if(timer_id == enquire_link_timer_id) {
    procEnquireLinkTimeout();
  } else if(timer_id == inactivity_timer_id) {
    procInactivityTimeout();
  } else if(in_transactions.contains(timer_id)) {
    killTimer(timer_id);
    inError(in_transactions.take(timer_id),
            parameters::command_status::ESME_TIMEOUTTRANS);
  } else if(out_transactions.contains(timer_id)) {
    killTimer(timer_id);
    inError(out_transactions.take(timer_id),
            parameters::command_status::ESME_TIMEOUTTRANS);
  }
}

bool ClientAsyncSessionPrivate::addMessageInQueue(Header *header) {
  if(in_queue.size() < max_in_msg) {
    in_queue.enqueue(header);
    return true;
  } else {
    return false;
  }
}

bool ClientAsyncSessionPrivate::addMessageOutQueue(Header *header) {
  if(out_queue.size() < max_out_msg) {
    out_queue.enqueue(header);
    return true;
  } else {
    return false;
  }
}

void ClientAsyncSessionPrivate::startSessionInitTimer() {
  if(session_init_time > 0 && session_init_timer_id == -1) {
    session_init_timer_id = startTimer(session_init_time);
  }
}

void ClientAsyncSessionPrivate::stopSessionInitTimer() {
  if(session_init_timer_id != -1) {
    killTimer(session_init_timer_id);
    session_init_timer_id = -1;
  }
}

void ClientAsyncSessionPrivate::startEnquireLinkTimer() {
  if(enquire_link_time > 0 && enquire_link_timer_id == -1) {
    enquire_link_timer_id = startTimer(enquire_link_time);
  }
}

void ClientAsyncSessionPrivate::stopEnquireLinkTimer() {
  if(enquire_link_timer_id != -1) {
    killTimer(enquire_link_timer_id);
    enquire_link_timer_id = -1;
  }
}

void ClientAsyncSessionPrivate::startInSpeedTimer() {
  if(in_speed > 0 && in_speed_timer_id == -1) {
    in_speed_timer_id = startTimer(in_speed);
  }
}

void ClientAsyncSessionPrivate::stopInSpeedTimer() {
  if(in_speed_timer_id != -1) {
    killTimer(in_speed_timer_id);
    in_speed_timer_id = -1;
  }
}

void ClientAsyncSessionPrivate::startOutSpeedTimer() {
  if(out_speed > 0 && out_speed_timer_id == -1) {
    out_speed_timer_id = startTimer(out_speed);
  }
}

void ClientAsyncSessionPrivate::stopOutSpeedTimer() {
  if(out_speed_timer_id != -1) {
    killTimer(out_speed_timer_id);
    out_speed_timer_id = -1;
  }
}

void ClientAsyncSessionPrivate::startInactivityTimer() {
  if(inactivity_time > 0 && inactivity_timer_id == -1) {
    inactivity_timer_id = startTimer(inactivity_time);
  }
}

void ClientAsyncSessionPrivate::stopInactivityTimer() {
  if(inactivity_timer_id != -1) {
    killTimer(inactivity_timer_id);
    inactivity_timer_id = -1;
  }
}

void ClientAsyncSessionPrivate::restartSessionInitTimer() {
  if(session_init_timer_id != -1) {
    killTimer(session_init_timer_id);
    if(session_init_time > 0) {
      session_init_timer_id = startTimer(session_init_time);
    }
  }
}

void ClientAsyncSessionPrivate::restartEnquireLinkTimer() {
  if(enquire_link_timer_id != -1) {
    killTimer(enquire_link_timer_id);
    if(enquire_link_time > 0) {
      enquire_link_timer_id = startTimer(enquire_link_time);
    }
  }
}

void ClientAsyncSessionPrivate::restartInSpeedTimer() {
  if(in_speed_timer_id != -1) {
    killTimer(in_speed_timer_id);
    if(in_speed > 0) {
      in_speed_timer_id = startTimer(in_speed);
    }
  }
}

void ClientAsyncSessionPrivate::restartOutSpeedTimer() {
  if(out_speed_timer_id != -1) {
    killTimer(out_speed_timer_id);
    if(out_speed > 0) {
      out_speed_timer_id = startTimer(out_speed);
    }
  }
}

void ClientAsyncSessionPrivate::restartInactivityTimer() {
  if(inactivity_timer_id != -1) {
    killTimer(inactivity_timer_id);
    if(inactivity_time > 0) {
      inactivity_timer_id = startTimer(inactivity_time);
    }
  }
}

void ClientAsyncSessionPrivate::sessionActivity() {
  if(now_state == BOUND_TX ||
     now_state == BOUND_RX ||
     now_state == BOUND_TRX) {
    stopInactivityTimer();
    startInactivityTimer();
  }
}

void ClientAsyncSessionPrivate::removeAllInTransactions() {
  while(!in_transactions.isEmpty()) {
    QHash<int, Header *>::iterator it = in_transactions.begin();
    killTimer(it.key());
    inError(it.value(), parameters::command_status::ESME_RSYSERR);
    in_transactions.erase(it);
  }
  in_transactions.clear();
}

void ClientAsyncSessionPrivate::removeAllOutTransactions() {
  while(!out_transactions.isEmpty()) {
    QHash<int, Header *>::iterator it = out_transactions.begin();
    killTimer(it.key());
    outError(it.value(), parameters::command_status::ESME_RSYSERR);
    out_transactions.erase(it);
  }
  out_transactions.clear();
}

void ClientAsyncSessionPrivate::clearInQueue() {
  while(!in_queue.isEmpty()) {
    inError(in_queue.dequeue(), parameters::command_status::ESME_RSYSERR);
  }
  in_queue.clear();
}

void ClientAsyncSessionPrivate::clearOutQueue() {
  while(!out_queue.isEmpty()) {
    outError(out_queue.dequeue(), parameters::command_status::ESME_RSYSERR);
  }
  out_queue.clear();
}

void ClientAsyncSessionPrivate::clearAllQueue() {
  removeAllInTransactions();
  removeAllOutTransactions();
  clearInQueue();
  clearOutQueue();
}

void ClientAsyncSessionPrivate::procError(ErrorCode code,
                                          const QString &message) {
  error_code = code;

  mutex.lock();
  error_message = message;
  mutex.unlock();

  stopSessionInitTimer();
  stopEnquireLinkTimer();
  stopInactivityTimer();
  stopInSpeedTimer();
  stopOutSpeedTimer();

  clearAllQueue();

  emit parent->error(code);

  if(socket->state() == QAbstractSocket::ConnectedState) {
    socket->disconnectFromHost();
  } else {
    now_state = CLOSED;
    emit parent->stateChanged(now_state);
    emit parent->closedSession();
  }
}

void ClientAsyncSessionPrivate::procSessionInitTimeout() {
  if(now_state == OPEN || now_state == OUTBOUND) {
    stopSessionInitTimer();
    emit parent->sessionInitTimeout();
  }
}

void ClientAsyncSessionPrivate::procEnquireLinkTimeout() {
  if(now_state != CLOSED) {
    emit parent->enquireLinkTimeout();
  }
}

void ClientAsyncSessionPrivate::procInactivityTimeout() {
  if(now_state != CLOSED) {
    stopInactivityTimer();
    emit parent->inactivityTimeout();
  }
}

void ClientAsyncSessionPrivate::inError(Header *header, quint32 error_code) {
  BinaryEncoder encoder;

  switch(header->getCommandId()) {
    case parameters::command_id::DATA_SM: {
      DataSm *pt(reinterpret_cast<DataSm *>(header));
      DataSmResp resp(error_code, pt->getSequenceNumber());
      encoder << resp;
      delete pt;
      break;
    }
    case parameters::command_id::DELIVER_SM: {
      DeliverSm *pt(reinterpret_cast<DeliverSm *>(header));
      DeliverSmResp resp(error_code, pt->getSequenceNumber());
      encoder << resp;
      delete pt;
      break;
    }
    case parameters::command_id::ENQUIRE_LINK: {
      EnquireLink *pt(reinterpret_cast<EnquireLink *>(header));
      EnquireLinkResp resp(error_code, pt->getSequenceNumber());
      encoder << resp;
      delete pt;
      break;
    }
  }

  writeSocketData(encoder);
}

void ClientAsyncSessionPrivate::outError(Header *header, quint32 error_code) {
  switch(header->getCommandId()) {
    case parameters::command_id::BIND_RECEIVER: {
      BindReceiver *pt(reinterpret_cast<BindReceiver *>(header));
      BindReceiverResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::BIND_TRANSMITTER: {
      BindTransmitter *pt(reinterpret_cast<BindTransmitter *>(header));
      BindTransmitterResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::BIND_TRANSCEIVER: {
      BindTransceiver *pt(reinterpret_cast<BindTransceiver *>(header));
      BindTransceiverResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::UNBIND: {
      Unbind *pt(reinterpret_cast<Unbind *>(header));
      UnbindResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::SUBMIT_SM: {
      SubmitSm *pt(reinterpret_cast<SubmitSm *>(header));
      SubmitSmResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::SUBMIT_MULTI: {
      SubmitMulti *pt(reinterpret_cast<SubmitMulti *>(header));
      SubmitMultiResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::DATA_SM: {
      DataSm *pt(reinterpret_cast<DataSm *>(header));
      DataSmResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::QUERY_SM: {
      QuerySm *pt(reinterpret_cast<QuerySm *>(header));
      QuerySmResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::REPLACE_SM: {
      ReplaceSm *pt(reinterpret_cast<ReplaceSm *>(header));
      ReplaceSmResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
    case parameters::command_id::ENQUIRE_LINK: {
      EnquireLink *pt(reinterpret_cast<EnquireLink *>(header));
      EnquireLinkResp resp(error_code, pt->getSequenceNumber());
      emit parent->receive(resp);
      delete pt;
      break;
    }
  }
}

void ClientAsyncSessionPrivate::writeSocketData(const QByteArray &bytes) {
  if(socket &&
     socket->state() == QAbstractSocket::ConnectedState &&
     socket->isValid()) {

    qint64 write_bytes(socket->write(bytes));
    socket->flush();

    if(write_bytes < bytes.size()) {
      if(!socket->waitForBytesWritten()) {
        procError(WR_SOCK_ERR, "Not written bytes for send");
      }
    }
  } else {
    procError(WR_SOCK_ERR, "Not written bytes for send");
  }
}

void ClientAsyncSessionPrivate::send(Header *header) {
  sessionActivity();

  BinaryEncoder encoder;

  switch(header->getCommandId()) {
    case parameters::command_id::BIND_TRANSMITTER:
      if(now_state == OPEN || now_state == OUTBOUND) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<BindTransmitter *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::BIND_RECEIVER:
      if(now_state == OPEN || now_state == OUTBOUND) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<BindReceiver *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::BIND_TRANSCEIVER:
      if(now_state == OPEN || now_state == OUTBOUND) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<BindTransceiver *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::UNBIND:
      if(now_state == BOUND_TX ||
         now_state == BOUND_RX ||
         now_state == BOUND_TRX) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<Unbind *>(header);
        if(header->getCommandStatus() == parameters::command_status::ESME_ROK) {
          setState(UNBOUND);
        }
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::GENERIC_NACK: {
      GenericNack *pt(reinterpret_cast<GenericNack *>(header));
      if(now_state != CLOSED) {
        encoder << *pt;
        delete pt;
      } else {
        delete pt;
        return;
      }
      break;
    }
    case parameters::command_id::SUBMIT_SM:
      if(now_state == BOUND_TX || now_state == BOUND_TRX) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<SubmitSm *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::SUBMIT_MULTI:
      if(now_state == BOUND_TX || now_state == BOUND_TRX) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<SubmitMulti *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::DELIVER_SM_RESP: {
      DeliverSmResp *pt(reinterpret_cast<DeliverSmResp *>(header));
      if((now_state == BOUND_RX || now_state == BOUND_TRX) &&
         stopInTransactions(header)) {
        encoder << *pt;
        delete pt;
      } else {
        delete pt;
        return;
      }
      break;
    }
    case parameters::command_id::DATA_SM:
      if(now_state == BOUND_TX || now_state == BOUND_TRX) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<DataSm *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::DATA_SM_RESP: {
      DataSmResp *pt(reinterpret_cast<DataSmResp *>(header));
      if((now_state == BOUND_RX || now_state == BOUND_TRX) &&
         stopInTransactions(header)) {
        encoder << *pt;
        delete pt;
      } else {
        delete pt;
        return;
      }
      break;
    }
    case parameters::command_id::QUERY_SM:
      if(now_state == BOUND_TX || now_state == BOUND_TRX) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<QuerySm *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::REPLACE_SM:
      if(now_state == BOUND_TX || now_state == BOUND_TRX) {
        if(!startOutTransaction(header)) {
          outError(header, parameters::command_status::ESME_OUTTRANSFULL);
          return;
        }
        encoder << *reinterpret_cast<ReplaceSm *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::ENQUIRE_LINK:
      if(now_state != CLOSED) {
        encoder << *reinterpret_cast<EnquireLink *>(header);
      } else {
        return outError(header, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    case parameters::command_id::ENQUIRE_LINK_RESP: {
      EnquireLinkResp *pt(reinterpret_cast<EnquireLinkResp *>(header));
      if(now_state != CLOSED && stopOutTransactions(header)) {
        encoder << *pt;
        delete pt;
      } else {
        delete pt;
        return;
      }
      break;
    }
  }

  writeSocketData(encoder);
}

void ClientAsyncSessionPrivate::receive(Header *header) {
  sessionActivity();

  switch(header->getCommandId()) {
    case parameters::command_id::ALERT_NOTIFICATION:  {
      AlertNotification *p(reinterpret_cast<AlertNotification *>(header));
      if(now_state == BOUND_RX || now_state == BOUND_TRX) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::BIND_TRANSMITTER_RESP: {
      BindTransmitterResp *p(reinterpret_cast<BindTransmitterResp *>(header));
      if((now_state == OPEN || now_state == OUTBOUND) &&
         stopOutTransactions(p)) {
        if(p->getCommandStatus() == parameters::command_status::ESME_ROK) {
          setState(BOUND_TX);
        }
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::BIND_RECEIVER_RESP: {
      BindReceiverResp *p(reinterpret_cast<BindReceiverResp *>(header));
      if((now_state == OPEN || now_state == OUTBOUND) &&
         stopOutTransactions(p)) {
        if(p->getCommandStatus() == parameters::command_status::ESME_ROK) {
          setState(BOUND_RX);
        }
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::BIND_TRANSCEIVER_RESP: {
      BindTransceiverResp *p(reinterpret_cast<BindTransceiverResp *>(header));
      if((now_state == OPEN || now_state == OUTBOUND) &&
         stopOutTransactions(p)) {
        if(p->getCommandStatus() == parameters::command_status::ESME_ROK) {
          setState(BOUND_TRX);
        }
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::OUTBIND: {
      Outbind *p(reinterpret_cast<Outbind *>(header));
      if(now_state == OPEN) {
        if(p->getCommandStatus() == parameters::command_status::ESME_ROK) {
          setState(OUTBOUND);
        }
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::UNBIND_RESP: {
      UnbindResp *p(reinterpret_cast<UnbindResp *>(header));
      if(now_state == UNBOUND && stopOutTransactions(p)) {
        emit parent->receive(*p);
        if(p->getCommandStatus() == parameters::command_status::ESME_ROK) {
          closeSession();
        }
      }
      delete p;
      break;
    }
    case parameters::command_id::GENERIC_NACK: {
      GenericNack *p(reinterpret_cast<GenericNack *>(header));
      if(now_state != CLOSED) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::SUBMIT_SM_RESP: {
      SubmitSmResp *p(reinterpret_cast<SubmitSmResp *>(header));
      if((now_state == BOUND_TX || now_state == BOUND_TRX) &&
         stopOutTransactions(p)) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::SUBMIT_MULTI_RESP: {
      SubmitMultiResp *p(reinterpret_cast<SubmitMultiResp *>(header));
      if((now_state == BOUND_TX || now_state == BOUND_TRX) &&
         stopOutTransactions(p)) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::DELIVER_SM: {
      DeliverSm *p(reinterpret_cast<DeliverSm *>(header));
      if(now_state == BOUND_RX || now_state == BOUND_TRX) {
        if(startInTransaction(p)) {
          emit parent->receive(*p);
        } else {
          inError(p, parameters::command_status::ESME_INTRANSFULL);
        }
      } else {
        inError(p, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    }
    case parameters::command_id::DATA_SM: {
      DataSm *p(reinterpret_cast<DataSm *>(header));
      if(now_state == BOUND_RX || now_state == BOUND_TRX) {
        if(startInTransaction(p)) {
          emit parent->receive(*p);
        } else {
          inError(p, parameters::command_status::ESME_INTRANSFULL);
        }
      } else {
        inError(p, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    }
    case parameters::command_id::DATA_SM_RESP: {
      DataSmResp *p(reinterpret_cast<DataSmResp *>(header));
      if((now_state == BOUND_TX || now_state == BOUND_TRX) &&
         stopOutTransactions(p)) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::QUERY_SM_RESP: {
      QuerySmResp *p(reinterpret_cast<QuerySmResp *>(header));
      if((now_state == BOUND_TX || now_state == BOUND_TRX) &&
         stopOutTransactions(p)) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::REPLACE_SM_RESP: {
      ReplaceSmResp *p(reinterpret_cast<ReplaceSmResp *>(header));
      if((now_state == BOUND_TX || now_state == BOUND_TRX) &&
         stopOutTransactions(p)) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
    case parameters::command_id::ENQUIRE_LINK: {
      EnquireLink *p(reinterpret_cast<EnquireLink *>(header));
      if(now_state != CLOSED) {
        if(startInTransaction(p)) {
          emit parent->receive(*p);
        } else {
          inError(p, parameters::command_status::ESME_INTRANSFULL);
        }
      } else {
        inError(p, parameters::command_status::ESME_RINVBNDSTS);
      }
      break;
    }
    case parameters::command_id::ENQUIRE_LINK_RESP: {
      EnquireLinkResp *p(reinterpret_cast<EnquireLinkResp *>(header));
      if(now_state != CLOSED && stopOutTransactions(p)) {
        emit parent->receive(*p);
      }
      delete p;
      break;
    }
  }
}

bool ClientAsyncSessionPrivate::startOutTransaction(Header *header) {
  if(out_transactions.size() < max_out_trans) {
    out_transactions.insert(startTimer(transaction_time), header);
    return true;
  } else {
    return false;
  }
}

bool ClientAsyncSessionPrivate::stopOutTransactions(Header *h) {
  bool res(false);

  quint32 command_id(h->getCommandId()),
          sequence_number(h->getSequenceNumber());

  if(command_id != parameters::command_id::BIND_RECEIVER_RESP &&
     command_id != parameters::command_id::BIND_TRANSMITTER_RESP &&
     command_id != parameters::command_id::BIND_TRANSCEIVER_RESP &&
     command_id != parameters::command_id::UNBIND_RESP &&
     command_id != parameters::command_id::SUBMIT_SM_RESP &&
     command_id != parameters::command_id::SUBMIT_MULTI_RESP &&
     command_id != parameters::command_id::DATA_SM_RESP &&
     command_id != parameters::command_id::QUERY_SM_RESP &&
     command_id != parameters::command_id::REPLACE_SM_RESP &&
     command_id != parameters::command_id::ENQUIRE_LINK_RESP) {
    return res;
  }

  for(QHash<int, Header *>::iterator it = out_transactions.begin();
      it != out_transactions.end();) {

    Header *header(it.value());

    if(header->getSequenceNumber() == sequence_number) {
      bool exists(false);
      switch(header->getCommandId()) {
        case parameters::command_id::BIND_RECEIVER:
          if(command_id == parameters::command_id::BIND_RECEIVER_RESP) {
            delete reinterpret_cast<BindReceiver *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::BIND_TRANSMITTER:
          if(command_id == parameters::command_id::BIND_TRANSMITTER_RESP) {
            delete reinterpret_cast<BindTransmitter *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::BIND_TRANSCEIVER:
          if(command_id == parameters::command_id::BIND_TRANSCEIVER_RESP) {
            delete reinterpret_cast<BindTransceiver *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::UNBIND:
          if(command_id == parameters::command_id::UNBIND_RESP) {
            delete reinterpret_cast<UnbindResp *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::SUBMIT_SM:
          if(command_id == parameters::command_id::SUBMIT_SM_RESP) {
            delete reinterpret_cast<SubmitSm *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::SUBMIT_MULTI:
          if(command_id == parameters::command_id::SUBMIT_MULTI_RESP) {
            delete reinterpret_cast<SubmitMulti *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::DATA_SM:
          if(command_id == parameters::command_id::DATA_SM_RESP) {
            delete reinterpret_cast<DataSm *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::QUERY_SM:
          if(command_id == parameters::command_id::QUERY_SM_RESP) {
            delete reinterpret_cast<QuerySm *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::REPLACE_SM:
          if(command_id == parameters::command_id::REPLACE_SM_RESP) {
            delete reinterpret_cast<ReplaceSm *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::ENQUIRE_LINK:
          if(command_id == parameters::command_id::ENQUIRE_LINK_RESP) {
            delete reinterpret_cast<EnquireLink *>(header);
            exists = true;
          }
          break;
      }

      if(exists) {
        res = exists;
        killTimer(it.key());
        it = out_transactions.erase(it);
        continue;
      }
    }
    it++;
  }

  return res;
}

bool ClientAsyncSessionPrivate::startInTransaction(Header *header) {
  if(in_transactions.size() < max_in_trans) {
    in_transactions.insert(startTimer(transaction_time), header);
    return true;
  } else {
    return false;
  }
}

bool ClientAsyncSessionPrivate::stopInTransactions(Header *h) {
  bool res(false);

  quint32 command_id(h->getCommandId()),
          sequence_number(h->getSequenceNumber());

  if(command_id != parameters::command_id::DELIVER_SM_RESP &&
     command_id != parameters::command_id::DATA_SM_RESP &&
     command_id != parameters::command_id::ENQUIRE_LINK_RESP) {
    return res;
  }

  for(QHash<int, Header *>::iterator it = in_transactions.begin();
      it != in_transactions.end();) {

    Header *header(it.value());

    if(header->getSequenceNumber() == sequence_number) {
      bool exists(false);
      switch(header->getCommandId()) {
        case parameters::command_id::DELIVER_SM:
          if(command_id == parameters::command_id::DELIVER_SM_RESP) {
            delete reinterpret_cast<SubmitSm *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::DATA_SM:
          if(command_id == parameters::command_id::DATA_SM_RESP) {
            delete reinterpret_cast<DataSm *>(header);
            exists = true;
          }
          break;
        case parameters::command_id::ENQUIRE_LINK:
          if(command_id == parameters::command_id::ENQUIRE_LINK_RESP) {
            delete reinterpret_cast<EnquireLink *>(header);
            exists = true;
          }
          break;
      }

      if(exists) {
        res = exists;
        killTimer(it.key());
        it = in_transactions.erase(it);
        continue;
      }
    }
    it++;
  }

  return res;
}

void ClientAsyncSessionPrivate::processInQueue() {
  if(!in_queue.isEmpty()) {
    receive(in_queue.dequeue());
  }
}

void ClientAsyncSessionPrivate::processOutQueue() {
  if(!out_queue.isEmpty()) {
    send(out_queue.dequeue());
  }
}

ClientAsyncSession::ClientAsyncSession(
  int in_speed, // msec
  int out_speed, // msec
  int session_init_time,
  int enquire_link_time,
  int inactivity_time,
  int transaction_time,
  int max_in_msg,
  int max_out_msg,
  int max_in_trans,
  int max_out_trans,
  bool threaded) :
  p(new ClientAsyncSessionPrivate(this,
                                  in_speed,
                                  out_speed,
                                  session_init_time,
                                  enquire_link_time,
                                  inactivity_time,
                                  transaction_time,
                                  max_in_msg,
                                  max_out_msg,
                                  max_in_trans,
                                  max_out_trans,
                                  threaded)) {
  if(threaded) {
    connect(p->thread, SIGNAL(terminated()), p, SLOT(deleteLater()));
    moveToThread(p->thread);
    p->thread->start();
  }
}

ClientAsyncSession::~ClientAsyncSession() {
  if(p) {
    if(p->thread) {
      if(p->thread->isRunning()) {
        p->thread->terminate();
      }
    }
  }
}

void ClientAsyncSession::setInSpeed(int in_speed) {
  emit p->sigSetInSpeed(in_speed);
}

void ClientAsyncSession::setOutSpeed(int out_speed) {
  emit p->sigSetOutSpeed(out_speed);
}

void ClientAsyncSession::setSessionInitTime(int session_init_time) {
  emit p->sigSetSessionInitTime(session_init_time);
}

void ClientAsyncSession::setEnquireLinkTime(int enquire_link_time) {
  emit p->sigSetEnquireLinkTime(enquire_link_time);
}

void ClientAsyncSession::setInactivityTime(int inactivity_time) {
  emit p->sigSetInactivityTime(inactivity_time);
}

void ClientAsyncSession::setTransactionTime(int transaction_time) {
  p->transaction_time = transaction_time;
}

void ClientAsyncSession::setMaxInMsg(int max_in_msg) {
  p->max_in_msg = max_in_msg;
}

void ClientAsyncSession::setMaxOutMsg(int max_out_msg) {
  p->max_out_msg = max_out_msg;
}

void ClientAsyncSession::setMaxInTrans(int max_in_trans) {
  p->max_in_trans = max_in_trans;
}

void ClientAsyncSession::setMaxOutTrans(int max_out_trans) {
  p->max_out_trans = max_out_trans;
}

SessionStates ClientAsyncSession::state() const {
  return p->now_state;
}

QHostAddress ClientAsyncSession::peerAddress() const {
  return p->peerAddress();
}

quint16 ClientAsyncSession::peerPort() const {
  return p->peer_port;
}

QHostAddress ClientAsyncSession::localAddress() const {
  return p->localAddress();
}

quint16 ClientAsyncSession::localPort() const {
  return p->local_port;
}

int ClientAsyncSession::getOpenedInTransaction() const {
  return p->in_transactions.size();
}

int ClientAsyncSession::getOpenedOutTransaction() const {
  return p->out_transactions.size();
}

int ClientAsyncSession::getInQueueSize() const {
  return p->in_queue.size();
}

int ClientAsyncSession::getOutQueueSize() const {
  return p->out_queue.size();
}

ErrorCode ClientAsyncSession::error() const {
  return p->error_code;
}

QString ClientAsyncSession::errorString() const {
  return p->errorString();
}

void ClientAsyncSession::openSession(const QString &host_name, quint16 port) {
  emit p->sigOpenSession(host_name, port);
}

void ClientAsyncSession::closeSession() {
  emit p->sigCloseSession();
}

void ClientAsyncSession::send(const BindTransmitter &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const BindReceiver &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const BindTransceiver &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const Unbind &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const GenericNack &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const SubmitSm &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const SubmitMulti &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const DeliverSmResp &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const DataSm &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const DataSmResp &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const QuerySm &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const ReplaceSm &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const EnquireLink &packet) {
  emit p->sigSend(packet);
}

void ClientAsyncSession::send(const EnquireLinkResp &packet) {
  emit p->sigSend(packet);
}

} // namespace sessions

} // namespace smpp
