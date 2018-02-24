#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore/QObject>
#include <QtCore/QDebug>

static const QString host = "127.0.0.1";
static const quint16 port = 55555;
static const int console_update = 1000;
static const int max_iter = 9000;
static const int in_speed = 0;
static const int out_speed = 0;
static const int session_init_time = 1000;
static const int enquire_link_time = 5000;
static const int inactivity_time = 60000;
static const int transaction_time = 20;
static const int max_in_msg = 100000;
static const int max_out_msg = 100000;
static const int max_in_trans = 100000;
static const int max_out_trans = 100000;
static const bool threaded = false;
static const QString src_address = "79123456789"
static const QString dest_address = "79987654321"

#endif // GLOBAL_H
