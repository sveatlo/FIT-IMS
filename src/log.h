#ifndef LOG_H
#define LOG_H

#include <netinet/icmp6.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <bitset>
#include <string>

using namespace std;

class Log {
public:
    static void debug(string msg, string end = "\n");
    static void info(string msg, string end = "\n");
    static void warn(string msg, string end = "\n");
    static void error(string msg, string end = "\n");
};

#endif
