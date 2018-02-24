#ifndef SMPP_DISTRIBUTION_LIST_ADDRESS_H
#define SMPP_DISTRIBUTION_LIST_ADDRESS_H

#include <QtCore/QString>
#include "smpp/pdu/smpp_multi_destination_address_base.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT DistributionListAddress : public MultiDestinationAddressBase {
  QString destrinution_list_name;

public:

  DistributionListAddress(const QString &destrinution_list_name = QString());

  DistributionListAddress(const DistributionListAddress &p);

  void setDlName(const QString &v);

  QString getDlName() const;

  quint8 getDestFlag() const;

  quint32 size() const;

  DistributionListAddress &operator =(const DistributionListAddress &p);

  bool operator ==(const DistributionListAddress &p) const;

  bool operator !=(const DistributionListAddress &p) const;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_DISTRIBUTION_LIST_ADDRESS_H
