#ifndef SMPP_CLIENT_ASYNC_SESSION_P_H
#define SMPP_CLIENT_ASYNC_SESSION_P_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QQueue>
#include <QtCore/QHash>
#include <QtCore/QTimerEvent>
#include <QtCore/QMutex>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include "smpp/sessions/smpp_session_global.h"
#include "smpp/decoders/smpp_binary_decoder.h"

namespace smpp {

namespace sessions {

class ClientAsyncSession;

class ClientAsyncSessionPrivate : public QObject {
  Q_OBJECT
public:
  ClientAsyncSessionPrivate(
    ClientAsyncSession *parent,
    int in_speed,
    int out_speed,
    int session_init_time,
    int enquire_link_time,
    int inactivity_time,
    int transaction_time,
    int max_in_msg,
    int max_out_msg,
    int max_in_trans,
    int max_out_trans,
    bool threaded);

  ~ClientAsyncSessionPrivate();

  QHostAddress peerAddress() const;

  QHostAddress localAddress() const;

  QString errorString() const;

public slots:

  void setInSpeed(int in_speed);

  void setOutSpeed(int out_speed);

  void setSessionInitTime(int session_init_time);

  void setEnquireLinkTime(int enquire_link_time);

  void setInactivityTime(int inactivity_time);

  void send(const smpp::pdu::BindTransmitter &p);

  void send(const smpp::pdu::BindReceiver &p);

  void send(const smpp::pdu::BindTransceiver &p);

  void send(const smpp::pdu::Unbind &p);

  void send(const smpp::pdu::GenericNack &p);

  void send(const smpp::pdu::SubmitSm &p);

  void send(const smpp::pdu::SubmitMulti &p);

  void send(const smpp::pdu::DeliverSmResp &p);

  void send(const smpp::pdu::DataSm &p);

  void send(const smpp::pdu::DataSmResp &p);

  void send(const smpp::pdu::QuerySm &p);

  void send(const smpp::pdu::ReplaceSm &p);

  void send(const smpp::pdu::EnquireLink &p);

  void send(const smpp::pdu::EnquireLinkResp &p);

  void openSession(const QString &host_name, quint16 port);

  void closeSession();

  void socketConnected();

  void socketDisconnected();

  void socketError(QAbstractSocket::SocketError error);

  void socketReadyRead();

signals:

  void sigSetInSpeed(int in_speed);

  void sigSetOutSpeed(int out_speed);

  void sigSetSessionInitTime(int session_init_time);

  void sigSetEnquireLinkTime(int enquire_link_time);

  void sigSetInactivityTime(int inactivity_time);

  void sigOpenSession(const QString &host_name, quint16 port);

  void sigCloseSession();

  void sigSend(const smpp::pdu::BindTransmitter &p);

  void sigSend(const smpp::pdu::BindReceiver &p);

  void sigSend(const smpp::pdu::BindTransceiver &p);

  void sigSend(const smpp::pdu::Unbind &p);

  void sigSend(const smpp::pdu::GenericNack &p);

  void sigSend(const smpp::pdu::SubmitSm &p);

  void sigSend(const smpp::pdu::SubmitMulti &p);

  void sigSend(const smpp::pdu::DeliverSmResp &p);

  void sigSend(const smpp::pdu::DataSm &p);

  void sigSend(const smpp::pdu::DataSmResp &p);

  void sigSend(const smpp::pdu::QuerySm &p);

  void sigSend(const smpp::pdu::ReplaceSm &p);

  void sigSend(const smpp::pdu::EnquireLink &p);

  void sigSend(const smpp::pdu::EnquireLinkResp &p);

protected:

  void setState(SessionStates state);

  void timerEvent(QTimerEvent *event);

private:

  bool addMessageInQueue(smpp::pdu::Header *header);

  bool addMessageOutQueue(smpp::pdu::Header *header);

  void startSessionInitTimer();

  void stopSessionInitTimer();

  void startEnquireLinkTimer();

  void stopEnquireLinkTimer();

  void startInSpeedTimer();

  void stopInSpeedTimer();

  void startOutSpeedTimer();

  void stopOutSpeedTimer();

  void startInactivityTimer();

  void stopInactivityTimer();

  void restartSessionInitTimer();

  void restartEnquireLinkTimer();

  void restartInSpeedTimer();

  void restartOutSpeedTimer();

  void restartInactivityTimer();

  void sessionActivity();

  void removeAllInTransactions();

  void removeAllOutTransactions();

  void clearInQueue();

  void clearOutQueue();

  void clearAllQueue();

  void procError(ErrorCode code, const QString &message);

  void procSessionInitTimeout();

  void procEnquireLinkTimeout();

  void procInactivityTimeout();

  void inError(smpp::pdu::Header *header, quint32 error_code);

  void outError(smpp::pdu::Header *header, quint32 error_code);

  void processInQueue();

  void processOutQueue();

  void writeSocketData(const QByteArray &bytes);

  void send(smpp::pdu::Header *header);

  void receive(smpp::pdu::Header *header);

  bool startInTransaction(smpp::pdu::Header *header);

  bool stopInTransactions(smpp::pdu::Header *header);

  bool startOutTransaction(smpp::pdu::Header *header);

  bool stopOutTransactions(smpp::pdu::Header *header);

  int in_speed; // msec
  int out_speed; // msec

  int session_init_time;
  int enquire_link_time;
  int inactivity_time;
  int transaction_time;

  int in_speed_timer_id;
  int out_speed_timer_id;

  int session_init_timer_id;
  int enquire_link_timer_id;
  int inactivity_timer_id;

  QString error_message;
  ErrorCode error_code;

  QHash<int, smpp::pdu::Header *> in_transactions;
  QHash<int, smpp::pdu::Header *> out_transactions;
  QQueue<smpp::pdu::Header *> in_queue;
  QQueue<smpp::pdu::Header *> out_queue;

  int max_in_msg;
  int max_out_msg;
  int max_in_trans;
  int max_out_trans;

  SessionStates now_state;

  QTcpSocket *socket;

  QHostAddress peer_address;
  QHostAddress local_address;
  quint16 peer_port;
  quint16 local_port;

  QThread *thread;

  mutable QMutex mutex;

  friend class ClientAsyncSession;

  ClientAsyncSession *parent;
};

} // namespace sessions

} // namespace smpp

#endif // SMPP_CLIENT_ASYNC_SESSION_P_H
