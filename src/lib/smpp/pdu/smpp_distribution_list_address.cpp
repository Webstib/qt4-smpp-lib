#include "smpp_distribution_list_address.h"

namespace smpp {

namespace pdu {

DistributionListAddress::DistributionListAddress(const QString &v) :
  destrinution_list_name(v) {

}

DistributionListAddress::DistributionListAddress(
    const DistributionListAddress &p) :
  MultiDestinationAddressBase(p),
  destrinution_list_name(p.destrinution_list_name) {

}

void DistributionListAddress::setDlName(const QString &v) {
  destrinution_list_name = v;
}

QString DistributionListAddress::getDlName() const {
  return destrinution_list_name;
}

quint8 DistributionListAddress::getDestFlag() const {
  return 0x02;
}

quint32 DistributionListAddress::size() const {
  return 2 + destrinution_list_name.size();
}

DistributionListAddress &DistributionListAddress::operator =(
  const DistributionListAddress &p) {
  if(this != &p) {
    destrinution_list_name = p.destrinution_list_name;
  }
  return *this;
}

bool DistributionListAddress::operator ==(
  const DistributionListAddress &p) const {
  return (destrinution_list_name == p.destrinution_list_name);
}

bool DistributionListAddress::operator !=(
  const DistributionListAddress &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
