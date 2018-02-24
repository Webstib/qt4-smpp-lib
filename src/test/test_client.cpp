#include "smpp/parameters/smpp_prameters_header.h"
#include "test_client.h"

TestClient::TestClient(QObject *parent) :
  QObject(parent),
  session(0),
  sn(1),
  ok(0),
  timeout(0),
  in_trans(0),
  out_trans(0),
  in_queue(0),
  out_queue(0),
  other_error(0) {

}

void TestClient::start() {
  session = new smpp::sessions::ClientAsyncSession(
    in_speed,
    out_speed,
    session_init_time,
    enquire_link_time,
    inactivity_time,
    transaction_time,
    max_in_msg,
    max_iter + 1,
    max_in_trans,
    max_out_trans,
    threaded);

  connect(session, SIGNAL(openedSession()), SLOT(openSession()));
  connect(session, SIGNAL(closedSession()), SLOT(closeSession()));
  connect(session,
          SIGNAL(error(smpp::sessions::ErrorCode)),
          SLOT(errorSession(smpp::sessions::ErrorCode)));
  connect(session,
          SIGNAL(receive(smpp::pdu::BindTransceiverResp)),
          SLOT(bindResp(smpp::pdu::BindTransceiverResp)));
  connect(session,
          SIGNAL(receive(smpp::pdu::UnbindResp)),
          SLOT(unbindResp(smpp::pdu::UnbindResp)));
  connect(session,
          SIGNAL(receive(smpp::pdu::SubmitSmResp)),
          SLOT(submitSmResp(smpp::pdu::SubmitSmResp)));
  connect(session,
          SIGNAL(receive(smpp::pdu::DeliverSm)),
          SLOT(deliverSm(smpp::pdu::DeliverSm)));

  session->openSession(host, port);
  qDebug() << "start session";
}

void TestClient::openSession() {
  smpp::pdu::BindTransceiver btr(sn++, "test_client", "123");
  btr.setCommandLength(btr.size());
  qDebug() << "send bind";
  session->send(btr);
}

void TestClient::closeSession() {
  qDebug() << "close client session";
  session->deleteLater();
  session = 0;
}

void TestClient::errorSession(smpp::sessions::ErrorCode) {
  qDebug() << "error client session " << session->errorString();
}

void TestClient::bindResp(smpp::pdu::BindTransceiverResp p) {
  qDebug() << "recive BindTransceiverResp " << p.getSequenceNumber();


  smpp::pdu::SubmitSm sm(sn++, "", 0, 1, src_address, 0, 1, dest_address);

  QString text("test");

  sm.setSmLength(text.size());

  sm.setShortMessage(text.toUtf8());

  sm.setCommandLength(sm.size());

  for(int i = 0; i < max_iter; i++) {
    session->send(sm);
    sm.setSequenceNumber(sn++);
  }
}

void TestClient::submitSmResp(smpp::pdu::SubmitSmResp p) {
  qDebug() << "recive SubmitSmResp " << p.getSequenceNumber();
  if(p.getCommandStatus() == smpp::parameters::command_status::ESME_ROK) {
    ok++;
  } else if(p.getCommandStatus() == smpp::parameters::command_status::ESME_INQUEUEFULL) {
    in_queue++;
  } else if(p.getCommandStatus() == smpp::parameters::command_status::ESME_OUTQUEUEFULL) {
    out_queue++;
  } else if(p.getCommandStatus() == smpp::parameters::command_status::ESME_INTRANSFULL) {
    in_trans++;
  } else if(p.getCommandStatus() == smpp::parameters::command_status::ESME_OUTTRANSFULL) {
    out_trans++;
  } else if(p.getCommandStatus() == smpp::parameters::command_status::ESME_TIMEOUTTRANS) {
    timeout++;
  } else {
    other_error++;
  }
  if(ok + timeout + in_queue + out_queue + in_trans + out_trans + other_error == max_iter) {
    smpp::pdu::Unbind ub(sn++);
    qDebug() << "send unbind" << ub.getSequenceNumber();
    session->send(ub);
  }
}

void TestClient::deliverSm(smpp::pdu::DeliverSm p) {
  session->send(smpp::pdu::DeliverSmResp(0, p.getSequenceNumber()));
}

void TestClient::unbindResp(smpp::pdu::UnbindResp p) {
  qDebug() << "recive UnbindResp" << p.getSequenceNumber();
  session->closeSession();
}
