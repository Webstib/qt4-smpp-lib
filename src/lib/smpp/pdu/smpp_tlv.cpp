#include "smpp/smpp_transform_functions.h"
#include "smpp/pdu/smpp_tlv.h"

namespace smpp {

namespace pdu {

Tlv::Tlv(quint16 tag, QByteArray value) :
  tag(tag), value(value) {

}

Tlv::Tlv(const Tlv &p) : tag(p.tag), value(p.value) {

}

quint16 Tlv::getTag() const {
  return tag;
}

quint16 Tlv::getLength() const {
  return value.size();
}

QByteArray Tlv::getValue() const {
  return value;
}

bool Tlv::getValue(QString &p) const {
  int pos(0);
  int size(value.size());
  while(1) {
    if(pos >= size)
      return false;
    if(value[pos++] == '\0')
      break;
  }
  if(pos != size)
    return false;
  p.clear();
  p.resize(size - 1);
  for(int i = 0; i < size - 1; i++)
    p[i] = value[i];
  return true;
}

bool Tlv::getValue(quint8 &p) const {
  if(value.size() != 1)
    return false;

  p = value[0];

  return true;
}

bool Tlv::getValue(quint16 &p) const {
  if(value.size() != 2)
    return false;

  quint16 v(0);
  char *c_pt(reinterpret_cast<char *>(&v));
  *(c_pt++) = value[0];
  *c_pt = value[1];

  p = ntoh16(v);

  return true;
}

bool Tlv::getValue(quint32 &p) const {
  if(value.size() != 4)
    return false;

  quint32 v(0);
  char *c_pt(reinterpret_cast<char *>(&v));
  *(c_pt++) = value[0];
  *(c_pt++) = value[1];
  *(c_pt++) = value[2];
  *c_pt = value[3];

  p = ntoh32(v);

  return true;
}

void Tlv::setTag(quint16 p) {
  tag = p;
}

void Tlv::setValue(const QByteArray &p) {
  value = p;
}

void Tlv::setValue(const QString &p) {
  value = p.toUtf8();
}

void Tlv::setValue(quint8 p) {
  value.resize(1);
  value[0] = p;
}

void Tlv::setValue(quint16 p) {
  value.resize(2);
  quint16 v(hton16(p));
  char *c_pt(reinterpret_cast<char *>(&v));
  value[0] = *(c_pt++);
  value[1] = *c_pt;
}

void Tlv::setValue(quint32 p) {
  value.resize(4);
  quint32 v(hton32(p));
  char *c_pt(reinterpret_cast<char *>(&v));
  value[0] = *(c_pt++);
  value[1] = *(c_pt++);
  value[2] = *(c_pt++);
  value[3] = *c_pt;
}

quint32 Tlv::size() const {
  return 4 + value.size();
}

Tlv &Tlv::operator =(const Tlv &p) {
  if(*this != p) {
    tag = p.tag;
    value = p.value;
  }
  return *this;
}

bool Tlv::operator ==(const Tlv &p) const {
  return (tag == p.tag && value == p.value);
}

bool Tlv::operator !=(const Tlv &p) const {
  return !(*this == p);
}

} // namespace pdu

} // namespace smpp
