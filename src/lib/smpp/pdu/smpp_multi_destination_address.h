#ifndef SMPP_MULTI_DESTINATION_ADDRESS_H
#define SMPP_MULTI_DESTINATION_ADDRESS_H

#include <QtCore/QList>
#include "smpp/pdu/smpp_sme_multi_address.h"
#include "smpp/pdu/smpp_distribution_list_address.h"

namespace smpp {

namespace pdu {

class SMPP_EXPORT MultiDestinationAddresses {
  QList<MultiDestinationAddressBase *> addrs;

  void copy(const QList<MultiDestinationAddressBase *> &p);

public:

  MultiDestinationAddresses();

  MultiDestinationAddresses(const MultiDestinationAddresses &p);

  ~MultiDestinationAddresses();

  void add(const SmeMultiAddress &p);

  void add(const DistributionListAddress &p);

  const QList<MultiDestinationAddressBase *> &getAll() const;

  QList<SmeMultiAddress> getSmeMultiAddress() const;

  QList<DistributionListAddress> getDistributionListAddress() const;

  void remove(const SmeMultiAddress &p);

  void remove(const DistributionListAddress &p);

  void removeSmeMultiAddress();

  void removeDistributionListAddress();

  void clear();

  quint32 size() const;

  MultiDestinationAddresses &operator =(const MultiDestinationAddresses &p);

  bool operator ==(const MultiDestinationAddresses &p) const;

  bool operator !=(const MultiDestinationAddresses &p) const;
};

} // namespace pdu

} // namespace smpp

#endif // SMPP_MULTI_DESTINATION_ADDRESS_H
