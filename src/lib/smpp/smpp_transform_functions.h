#ifndef SMPP_TRANSFORM_FUNCTIONS_H
#define SMPP_TRANSFORM_FUNCTIONS_H

#include "smpp/smpp_global.h"

namespace smpp {

inline bool is_big_endian() {
  const long x = 1;
  return *(const char *) & x ? false : true;
}

inline quint32 ntoh32(quint32 n) {
  if (is_big_endian())
    return n;
  return (n & 0x000000ff) << 24 |
         (n & 0x0000ff00) << 8 |
         (n & 0x00ff0000) >> 8 |
         (n & 0xff000000) >> 24;
}

inline quint32 hton32(quint32 n) {
  if (is_big_endian())
    return n;
  return (n & 0x000000ff) << 24 |
         (n & 0x0000ff00) << 8 |
         (n & 0x00ff0000) >> 8 |
         (n & 0xff000000) >> 24;
}

inline quint16 ntoh16(quint16 n) {
  if (is_big_endian())
    return n;
  return (n & 0x00ff) << 8 | (n & 0xff00) >> 8;
}

inline quint16 hton16(quint16 n) {
  if(is_big_endian())
    return n;
  return (n & 0x00ff) << 8 | (n & 0xff00) >> 8;
}

} // namespace smpp

#endif // SMPP_TRANSFORM_FUNCTIONS_H
