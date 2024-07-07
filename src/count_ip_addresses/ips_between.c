#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * https://www.codewars.com/kata/526989a41034285187000de4/train/c
 */
uint32_t ips_between(const char *start, const char *end);

struct ip {
    int a;
    int b;
    int c;
    int d;
};

typedef struct ip ip_t;

static bool parse_ip(const char *ip, ip_t *result) {
    int n = sscanf(ip, "%d.%d.%d.%d", &result->a, &result->b, &result->c, &result->d);

    if (n != 4) {
        fprintf(stderr, "Invalid IP address: %s\n", ip);
        return false;
    }

    return true;
}

static uint32_t ip_to_int(const ip_t *ip) {
    return (ip->a << 24) | (ip->b << 16) | (ip->c << 8) | ip->d;
}

uint32_t ips_between(const char *start, const char *end) {
    ip_t start_ip, end_ip;
    parse_ip(start, &start_ip);
    parse_ip(end, &end_ip);

    return ip_to_int(&end_ip) - ip_to_int(&start_ip);
}

/*
 * #againwhatlearned
 * Use `inet_addr` to convert an IP address to a 32-bit integer:
 *
 * ```
 * #include <arpa/inet.h>
 *
 * uint32_t ips_between(const char *start, const char *end) {
 *    return ntohl(inet_addr(end)) - ntohl(inet_addr(start));
 * }
 * ```
 */
