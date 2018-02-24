#include "smpp/pdu/smpp_multi_destination_address.h"

namespace smpp {

namespace pdu {

MultiDestinationAddresses::MultiDestinationAddresses() {

}

MultiDestinationAddresses::MultiDestinationAddresses(
  const MultiDestinationAddresses &p) {
  copy(p.addrs);
}

MultiDestinationAddresses::~MultiDestinationAddresses() {
  clear();
}

void MultiDestinationAddresses::copy(
  const QList<MultiDestinationAddressBase *> &p) {
  clear();
  for(QList<MultiDestinationAddressBase *>::ConstIterator it = p.constBegin();
      it != p.constEnd();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x01) {
      add(*reinterpret_cast<SmeMultiAddress *>(addr));
    } else if(addr->getDestFlag() == 0x02) {
      add(*reinterpret_cast<DistributionListAddress *>(addr));
    }
  }
}

void MultiDestinationAddresses::add(const SmeMultiAddress &p) {
  addrs.push_back(new SmeMultiAddress(p));
}

void MultiDestinationAddresses::add(const DistributionListAddress &p) {
  addrs.push_back(new DistributionListAddress(p));
}

const QList<MultiDestinationAddressBase *> &
MultiDestinationAddresses::getAll() const {
  return addrs;
}

QList<SmeMultiAddress> MultiDestinationAddresses::getSmeMultiAddress() const {
  QList<SmeMultiAddress> list;
  for(QList<MultiDestinationAddressBase *>::ConstIterator it = addrs.constBegin();
      it != addrs.constEnd();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x01) {
      list.push_back(*reinterpret_cast<SmeMultiAddress *>(addr));
    }
  }
  return list;
}

QList<DistributionListAddress>
MultiDestinationAddresses::getDistributionListAddress() const {
  QList<DistributionListAddress> list;
  for(QList<MultiDestinationAddressBase *>::ConstIterator it = addrs.constBegin();
      it != addrs.constEnd();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x02) {
      list.push_back(*reinterpret_cast<DistributionListAddress *>(addr));
    }
  }
  return list;
}

void MultiDestinationAddresses::remove(const SmeMultiAddress &p) {
  for(QList<MultiDestinationAddressBase *>::Iterator it = addrs.begin();
      it != addrs.end();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x01) {
      SmeMultiAddress *pt(
        reinterpret_cast<SmeMultiAddress *>(addr));
      if(p == *pt) {
        it = addrs.erase(it);
        delete pt;
      }
    }
  }
}

void MultiDestinationAddresses::remove(const DistributionListAddress &p) {
  for(QList<MultiDestinationAddressBase *>::Iterator it = addrs.begin();
      it != addrs.end();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x02) {
      DistributionListAddress *pt(
        reinterpret_cast<DistributionListAddress *>(addr));
      if(p == *pt) {
        it = addrs.erase(it);
        delete pt;
      }
    }
  }
}

void MultiDestinationAddresses::removeSmeMultiAddress() {
  for(QList<MultiDestinationAddressBase *>::Iterator it = addrs.begin();
      it != addrs.end();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x01) {
      it = addrs.erase(it);
      delete reinterpret_cast<SmeMultiAddress *>(addr);
    }
  }
}

void MultiDestinationAddresses::removeDistributionListAddress() {
  for(QList<MultiDestinationAddressBase *>::Iterator it = addrs.begin();
      it != addrs.end();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x02) {
      it = addrs.erase(it);
      delete reinterpret_cast<DistributionListAddress *>(addr);
    }
  }
}

void MultiDestinationAddresses::clear() {
  while(!addrs.isEmpty()) {
    MultiDestinationAddressBase *addr(addrs.takeFirst());
    if(addr->getDestFlag() == 0x01) {
      delete reinterpret_cast<SmeMultiAddress *>(addr);
    } else if(addr->getDestFlag() == 0x02) {
      delete reinterpret_cast<DistributionListAddress *>(addr);
    }
  }
}

quint32 MultiDestinationAddresses::size() const {
  quint32 v(0);
  for(QList<MultiDestinationAddressBase *>::ConstIterator it = addrs.constBegin();
      it != addrs.constEnd();
      it++) {
    MultiDestinationAddressBase *addr(*it);
    if(addr->getDestFlag() == 0x01) {
      v += reinterpret_cast<SmeMultiAddress *>(addr)->size();
    } else if(addr->getDestFlag() == 0x02) {
      v += reinterpret_cast<DistributionListAddress *>(addr)->size();
    }
  }
  return v;
}

MultiDestinationAddresses &MultiDestinationAddresses::operator =(
  const MultiDestinationAddresses &p) {
  if(*this != p) {
    copy(p.addrs);
  }
  return *this;
}

bool MultiDestinationAddresses::operator ==(
  const MultiDestinationAddresses &p) const {
  if(addrs.size() == p.addrs.size()) {
    for(QList<MultiDestinationAddressBase *>::ConstIterator it1 = addrs.constBegin(),
        it2 = p.addrs.constBegin();
        it1 != addrs.constEnd(), it2 != p.addrs.constEnd();
        it1++, it2++) {
      MultiDestinationAddressBase *addr1(*it1);
      MultiDestinationAddressBase *addr2(*it1);
      quint8 flag1(addr1->getDestFlag());
      quint8 flag2(addr2->getDestFlag());
      if(flag1 == flag2 && flag1 == 0x01) {
        if(*reinterpret_cast<SmeMultiAddress *>(addr1) !=
           *reinterpret_cast<SmeMultiAddress *>(addr2))
          return false;
      } else if(flag1 == flag2 && flag1 == 0x02) {
        if(*reinterpret_cast<DistributionListAddress *>(addr1) !=
           *reinterpret_cast<DistributionListAddress *>(addr2))
          return false;
      }
    }
    return true;
  }
  return false;
}

bool MultiDestinationAddresses::operator !=(
  const MultiDestinationAddresses &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
