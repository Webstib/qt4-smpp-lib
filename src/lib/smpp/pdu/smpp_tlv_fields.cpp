#include "smpp/pdu/smpp_tlv_fields.h"

namespace smpp {

namespace pdu {

TlvFields::TlvFields() {

}

TlvFields::TlvFields(const TlvFields &p) {
  copy(p.tlv_list);
}

void TlvFields::copy(const TlvList &p) {
  clear();
  for(TlvList::ConstIterator it = p.constBegin(); it != p.constEnd(); it++)
    add(**it);
}

void TlvFields::add(const Tlv &tlv) {
  tlv_list.push_back(new Tlv(tlv));
}

const TlvList &TlvFields::getList() const {
  return tlv_list;
}

TlvList TlvFields::find(const quint16 &tag) const {
  TlvList list;
  for(TlvList::ConstIterator it = tlv_list.constBegin();
      it != tlv_list.constEnd();
      it++) {
    if((*it)->getTag() == tag)
      list.push_back(*it);
  }
  return list;
}

void TlvFields::remove(const quint16 &tag) {
  for(TlvList::Iterator it = tlv_list.begin(); it != tlv_list.end();) {
    if((*it)->getTag() == tag) {
      delete *it;
      it = tlv_list.erase(it);
    } else {
      it++;
    }
  }
}

void TlvFields::clear() {
  qDeleteAll(tlv_list);
  tlv_list.clear();
}

quint32 TlvFields::size() const {
  quint32 v(0);
  for(TlvList::ConstIterator it = tlv_list.constBegin();
      it != tlv_list.constEnd();
      it++) {
    v += (*it)->size();
  }
  return v;
}

TlvFields &TlvFields::operator =(const TlvFields &p) {
  if(p != *this) {
    copy(p.tlv_list);
  }
  return *this;
}

bool TlvFields::operator ==(const TlvFields &p) const {
  if(tlv_list.size() == p.tlv_list.size()) {
    for(TlvList::ConstIterator it1 = tlv_list.constBegin(),
        it2 = p.tlv_list.constBegin();
        it1 != tlv_list.constEnd(), it2 != p.tlv_list.constEnd();
        it1++, it2++) {
      if(**it1 != **it2)
        return false;
    }
    return true;
  }
  return false;
}

bool TlvFields::operator !=(const TlvFields &p) const {
  return *this != p;
}

} // namespace pdu

} // namespace smpp
