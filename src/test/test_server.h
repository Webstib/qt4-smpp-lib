#ifndef TEST_SERVER_H
#define TEST_SERVER_H

#include <QtNetwork/QTcpServer>
#include "smpp/sessions/smpp_server_async_session.h"
#include "test_client.h"

class TestServer : public QTcpServer {
Q_OBJECT
public:
explicit TestServer(QObject *parent = 0);

public slots:

  void start();
  void openSession();
  void closeSession();
  void errorSession(smpp::sessions::ErrorCode code);
  void bind(smpp::pdu::BindTransceiver p);
  void unbind(smpp::pdu::Unbind p);
  void submitSm(smpp::pdu::SubmitSm p);
  void deliverSmResp(smpp::pdu::DeliverSmResp p);

protected:

  void incomingConnection(int sock);

  void timerEvent(QTimerEvent *event);

private:

  int timer_id;
  smpp::sessions::ServerAsyncSession *session;
  TestClient *test_client;
};

#endif // TEST_SERVER_H
