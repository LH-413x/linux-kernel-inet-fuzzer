//
// Created by liuhao on 2019/9/9.
//

#ifndef ROUTE_TUNNEL_H
#define ROUTE_TUNNEL_H

#include <linux/ip6_tunnel.h>
#include <linux/if_tunnel.h>
#include <linux/in6.h>
#include <utils.h>

#define DEFAULT_TNL_HOP_LIMIT	(64)

struct tnl_print_nlmsg_info {
    const struct ifinfomsg *ifi;
    const void *p1;
    void *p2;

    void (*init)(const struct tnl_print_nlmsg_info *info);
    bool (*match)(const struct tnl_print_nlmsg_info *info);
    void (*print)(const void *t);
};

class tunnel {
private:
    int preferred_family;
public:
    explicit tunnel(int family):preferred_family(family){}
    tunnel();
    int rand_do_add();
    int do_add(int cmd);
    int tnl_add_ioctl(int cmd, const char *basedev, const char *name, void *p);

private:
    static void ip6_tnl_parm_init(ip6_tnl_parm2 *p, int apply_default);
};


#endif //ROUTE_TUNNEL_H
