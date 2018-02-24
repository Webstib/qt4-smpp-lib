#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

#include "global.h"
#include "smpp/sessions/smpp_client_async_session.h"

class TestClient : public QObject {
Q_OBJECT
public:

  smpp::sessions::ClientAsyncSession *session;

  explicit TestClient(QObject *parent = 0);

  int sn;
  int ok;
  int timeout;
  int in_trans;
  int out_trans;
  int in_queue;
  int out_queue;
  int other_error;

public slots:
  void start();
  void openSession();
  void closeSession();
  void errorSession(smpp::sessions::ErrorCode code);
  void bindResp(smpp::pdu::BindTransceiverResp p);
  void unbindResp(smpp::pdu::UnbindResp p);
  void submitSmResp(smpp::pdu::SubmitSmResp p);
  void deliverSm(smpp::pdu::DeliverSm p);
};

#endif // TEST_CLIENT_H
