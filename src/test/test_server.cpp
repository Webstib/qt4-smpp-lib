#include "test_server.h"

TestServer::TestServer(QObject *parent) :
  QTcpServer(parent),
  timer_id(-1),
  session(0),
  test_client(0) {

}

void TestServer::start() {
  if(this->listen(QHostAddress(host), port)) {
    test_client = new TestClient();
    test_client->start();
  }
}

void TestServer::timerEvent(QTimerEvent *) {
#ifdef unix
  std::system("clear");
#else
  std::system("CLS");
#endif
  QTextStream out(stdout);
  out <<
    "Server " << session->localAddress().toString() << ":"
              << session->localPort() << "\n" <<
    "Server In Queue Size " << session->getInQueueSize() << "\n" <<
    "Server Out Queue Size " << session->getOutQueueSize() << "\n" <<
    "Server Opened In Transaction " << session->getOpenedInTransaction() << "\n" <<
    "Server Opened Out Transaction " << session->getOpenedOutTransaction() << "\n" <<
    "Client " << test_client->session->localAddress().toString() << ":"
              << test_client->session->localPort() << "\n" <<
    "Client In Queue Size " << test_client->session->getInQueueSize() << "\n" <<
    "Client Out Queue Size " << test_client->session->getOutQueueSize() << "\n" <<
    "Client Opened In Transaction " << test_client->session->getOpenedInTransaction() << "\n" <<
    "Client Opened Out Transaction " << test_client->session->getOpenedOutTransaction() << "\n" <<
    "ok sms " << test_client->ok << "\n" <<
    "timeout sms " << test_client->timeout << "\n"
    "in queue full sms " << test_client->in_queue << "\n" <<
    "out queue full sms " << test_client->out_queue << "\n"
    "in transaction full sms " << test_client->in_trans << "\n" <<
    "out transaction full sms " << test_client->out_trans << "\n" <<
    "other error sms " << test_client->other_error << "\n";
}

void TestServer::incomingConnection(int sock) {
  session = new smpp::sessions::ServerAsyncSession(
    sock,
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
    threaded);
  connect(session, SIGNAL(openedSession()), SLOT(openSession()));
  connect(session, SIGNAL(closedSession()), SLOT(closeSession()));
  connect(session,
          SIGNAL(error(smpp::sessions::ErrorCode)),
          SLOT(errorSession(smpp::sessions::ErrorCode)));
  connect(session,
          SIGNAL(receive(smpp::pdu::BindTransceiver)),
          SLOT(bind(smpp::pdu::BindTransceiver)));
  connect(session,
          SIGNAL(receive(smpp::pdu::Unbind)),
          SLOT(unbind(smpp::pdu::Unbind)));
  connect(session,
          SIGNAL(receive(smpp::pdu::SubmitSm)),
          SLOT(submitSm(smpp::pdu::SubmitSm)));
  connect(session,
          SIGNAL(receive(smpp::pdu::DeliverSmResp)),
          SLOT(deliverSmResp(smpp::pdu::DeliverSmResp)));
}

void TestServer::openSession() {
  qDebug() << "open server session";
}

void TestServer::closeSession() {
  qDebug() << "close server session";
  session->deleteLater();
  session = 0;
  test_client->deleteLater();
  test_client = 0;
  if(timer_id != -1)
    killTimer(timer_id);
  timerEvent(0);
}

void TestServer::errorSession(smpp::sessions::ErrorCode) {
  if(timer_id != -1)
    killTimer(timer_id);
  qDebug() << "error server session " << session->errorString();
}

void TestServer::bind(smpp::pdu::BindTransceiver p) {
  smpp::pdu::BindTransceiverResp bt(0, p.getSequenceNumber());
  qDebug() << "send BindTransceiverResp" << bt.getSequenceNumber();
  bt.setCommandLength(bt.size());
  session->send(bt);
  timer_id = startTimer(console_update);
}

void TestServer::submitSm(smpp::pdu::SubmitSm p) {
  smpp::pdu::SubmitSmResp sm_resp(0, p.getSequenceNumber());
  sm_resp.setCommandLength(sm_resp.size());
  session->send(sm_resp);
  session->send(smpp::pdu::DeliverSm(p.getSequenceNumber()));
}

void TestServer::deliverSmResp(smpp::pdu::DeliverSmResp) {

}

void TestServer::unbind(smpp::pdu::Unbind p) {
  smpp::pdu::UnbindResp ub(p.getSequenceNumber());
  qDebug() << "send UnbindResp" << ub.getSequenceNumber();
  session->send(ub);
  if(timer_id != -1)
    killTimer(timer_id);
  timerEvent(0);
}
