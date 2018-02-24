#include "smpp/parameters/smpp_prameters_header.h"
#include "smpp/pdu/smpp_data_sm.h"

namespace smpp {

namespace pdu {

DataSm::DataSm(quint32 sequence_number,
               const QString &service_type,
               quint8 source_addr_ton,
               quint8 source_addr_npi,
               const QString &source_addr,
               quint8 dest_addr_ton,
               quint8 dest_addr_npi,
               const QString &destination_addr,
               quint8 esm_class,
               quint8 registered_delivery,
               quint8 data_coding) :
  Header(MIN_LENGTH,
         parameters::command_id::DATA_SM,
         parameters::command_status::ESME_ROK,
         sequence_number),
  service_type(service_type),
  source_addr_ton(source_addr_ton),
  source_addr_npi(source_addr_npi),
  source_addr(source_addr),
  dest_addr_ton(dest_addr_ton),
  dest_addr_npi(dest_addr_npi),
  destination_addr(destination_addr),
  esm_class(esm_class),
  registered_delivery(registered_delivery),
  data_coding(data_coding) {

}

DataSm::DataSm(const Header &p) :
  Header(p),
  source_addr_ton(0),
  source_addr_npi(0),
  dest_addr_ton(0),
  dest_addr_npi(0),
  esm_class(0),
  registered_delivery(0),
  data_coding(0) {

}

DataSm::DataSm(const DataSm &p) :
  Header(p),
  TlvFields(p),
  service_type(p.service_type),
  source_addr_ton(p.source_addr_ton),
  source_addr_npi(p.source_addr_npi),
  source_addr(p.source_addr),
  dest_addr_ton(p.dest_addr_ton),
  dest_addr_npi(p.dest_addr_npi),
  destination_addr(p.destination_addr),
  esm_class(p.esm_class),
  registered_delivery(p.registered_delivery),
  data_coding(p.data_coding) {

}

void DataSm::setServiceType(const QString &v) {
  service_type = v;
}

void DataSm::setSourceAddrTon(quint8 v) {
  source_addr_ton = v;
}

void DataSm::setSourceAddrNpi(quint8 v) {
  source_addr_npi = v;
}

void DataSm::setSourceAddr(const QString &v) {
  source_addr = v;
}

void DataSm::setDestAddrTon(quint8 v) {
  dest_addr_ton = v;
}

void DataSm::setDestAddrNpi(quint8 v) {
  dest_addr_npi = v;
}

void DataSm::setDestinationAddr(const QString &v) {
  destination_addr = v;
}

void DataSm::setEsmClass(quint8 v) {
  esm_class = v;
}

void DataSm::setRegisteredDelivery(quint8 v) {
  registered_delivery = v;
}

void DataSm::setDataCoding(quint8 v) {
  data_coding = v;
}

QString DataSm::getServiceType() const {
  return service_type;
}

quint8 DataSm::getSourceAddrTon() const {
  return source_addr_ton;
}

quint8 DataSm::getSourceAddrNpi() const {
  return source_addr_npi;
}

QString DataSm::getSourceAddr() const {
  return source_addr;
}

quint8 DataSm::getDestAddrTon() const {
  return dest_addr_ton;
}

quint8 DataSm::getDestAddrNpi() const {
  return dest_addr_npi;
}

QString DataSm::getDestinationAddr() const {
  return destination_addr;
}

quint8 DataSm::getEsmClass() const {
  return esm_class;
}

quint8 DataSm::getRegisteredDelivery() const {
  return registered_delivery;
}

quint8 DataSm::getDataCoding() const {
  return data_coding;
}

quint32 DataSm::size() const {
  return MIN_LENGTH +
         service_type.size() +
         source_addr.size() +
         destination_addr.size() +
         TlvFields::size();
}

DataSm &DataSm::operator =(const DataSm &p) {
  if(this != &p) {
    Header::operator=(p);
    service_type = p.service_type;
    source_addr_ton = p.source_addr_ton;
    source_addr_npi = p.source_addr_npi;
    source_addr = p.source_addr;
    dest_addr_ton = p.dest_addr_ton;
    dest_addr_npi = p.dest_addr_npi;
    destination_addr = p.destination_addr;
    esm_class = p.esm_class;
    registered_delivery = p.registered_delivery;
    data_coding = p.data_coding;
    TlvFields::operator=(p);
  }
  return *this;
}

bool DataSm::operator ==(const DataSm &p) const {
  return(Header::operator==(p) &&
         service_type == p.service_type &&
         source_addr_ton == p.source_addr_ton &&
         source_addr_npi == p.source_addr_npi &&
         source_addr == p.source_addr &&
         dest_addr_ton == p.dest_addr_ton &&
         dest_addr_npi == p.dest_addr_npi &&
         destination_addr == p.destination_addr &&
         esm_class == p.esm_class &&
         registered_delivery == p.registered_delivery &&
         data_coding == p.data_coding &&
         TlvFields::operator==(p));
}

bool DataSm::operator !=(const DataSm &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
