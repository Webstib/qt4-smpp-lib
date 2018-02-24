#ifndef SMPP_SERVER_ASYNC_SESSION_H
#define SMPP_SERVER_ASYNC_SESSION_H

#include <QtNetwork/QTcpSocket>
#include "smpp/sessions/smpp_session_global.h"

namespace smpp {

namespace sessions {

class ServerAsyncSessionPrivate;

class SMPP_EXPORT ServerAsyncSession : public QObject {
  Q_OBJECT
public:
  ServerAsyncSession(
    int sock_descriptor,
    int in_speed = MIN_IN_SPEED, // msec
    int out_speed = MIN_OUT_SPEED, // msec
    int session_init_time = MIN_SESSION_INIT_TIME,
    int enquire_link_time = MIN_ENQUIRE_LINK_TIME,
    int inactivity_time = MIN_INACTIVITY_TIME,
    int transaction_time = MIN_TRANSACTION_TIME,
    int max_in_msg = MAX_IN_QUEUE_MSG,
    int max_out_msg = MAX_OUT_QUEUE_MSG,
    int max_in_trans = MAX_IN_TRANSACTIONS,
    int max_out_trans = MAX_OUT_TRANSACTIONS,
    bool threaded = true);

  ~ServerAsyncSession();

  void setInSpeed(int in_speed);

  void setOutSpeed(int out_speed);

  void setSessionInitTime(int session_init_time);

  void setEnquireLinkTime(int enquire_link_time);

  void setInactivityTime(int inactivity_time);

  void setTransactionTime(int transaction_time);

  void setMaxInMsg(int max_in_msg);

  void setMaxOutMsg(int max_out_msg);

  void setMaxInTrans(int max_in_trans);

  void setMaxOutTrans(int max_out_trans);

  smpp::sessions::SessionStates state() const;

  QHostAddress peerAddress() const;

  quint16 peerPort() const;

  QHostAddress localAddress() const;

  quint16 localPort() const;

  int getOpenedInTransaction() const;

  int getOpenedOutTransaction() const;

  int getInQueueSize() const;

  int getOutQueueSize() const;

  smpp::sessions::ErrorCode error() const;

  QString errorString() const;

public slots:

  void closeSession();

  void send(const smpp::pdu::AlertNotification &p);

  void send(const smpp::pdu::BindTransmitterResp &p);

  void send(const smpp::pdu::BindReceiverResp &p);

  void send(const smpp::pdu::BindTransceiverResp &p);

  void send(const smpp::pdu::UnbindResp &p);

  void send(const smpp::pdu::Outbind &p);

  void send(const smpp::pdu::GenericNack &p);

  void send(const smpp::pdu::SubmitSmResp &p);

  void send(const smpp::pdu::SubmitMultiResp &p);

  void send(const smpp::pdu::DeliverSm &p);

  void send(const smpp::pdu::DataSm &p);

  void send(const smpp::pdu::DataSmResp &p);

  void send(const smpp::pdu::QuerySmResp &p);

  void send(const smpp::pdu::ReplaceSmResp &p);

  void send(const smpp::pdu::EnquireLink &p);

  void send(const smpp::pdu::EnquireLinkResp &p);

signals:

  void openedSession();

  void closedSession();

  void error(smpp::sessions::ErrorCode code);

  void receive(smpp::pdu::GenericNack p);

  void receive(smpp::pdu::BindTransmitter p);

  void receive(smpp::pdu::BindReceiver p);

  void receive(smpp::pdu::BindTransceiver p);

  void receive(smpp::pdu::Unbind p);

  void receive(smpp::pdu::SubmitSm p);

  void receive(smpp::pdu::SubmitMulti p);

  void receive(smpp::pdu::DeliverSmResp p);

  void receive(smpp::pdu::DataSm p);

  void receive(smpp::pdu::DataSmResp p);

  void receive(smpp::pdu::QuerySm p);

  void receive(smpp::pdu::ReplaceSm p);

  void receive(smpp::pdu::EnquireLink p);

  void receive(smpp::pdu::EnquireLinkResp p);

  void stateChanged(smpp::sessions::SessionStates state);

  void sessionInitTimeout();

  void enquireLinkTimeout();

  void inactivityTimeout();

private:

  friend class ServerAsyncSessionPrivate;

  ServerAsyncSessionPrivate *p;
};

} // namespace sessions

} // namespace smpp

#endif // SMPP_SERVER_ASYNC_SESSION_H
