//
// Created by liuhao on 2019/9/9.
//

#include <tunnel.h>

#include <cstdio>
#include <sys/ioctl.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

const int familys[]={
        AF_INET6,
};

const int add_tunnel_cmd_types[]={
        SIOCADDTUNNEL,
        SIOCCHGTUNNEL,
};

tunnel::tunnel(){
    preferred_family=RAND_FROM(familys);
}

void tunnel::ip6_tnl_parm_init(ip6_tnl_parm2 *p, int apply_default)
{
    p->proto = IPPROTO_IPV6;
    if (apply_default) {
        p->hop_limit = DEFAULT_TNL_HOP_LIMIT;
        p->encap_limit = IPV6_DEFAULT_TNL_ENCAP_LIMIT;
    }
}


int tunnel::rand_do_add() {
    int cmd=RAND_FROM(add_tunnel_cmd_types);
    do_add(cmd);
}

const int i_or_o_flags[]={
        GRE_CSUM	,
        GRE_ROUTING	,
        GRE_KEY		,
        GRE_SEQ		,
        GRE_STRICT	,
        GRE_REC		,
        GRE_ACK		,
        GRE_FLAGS	,
        GRE_VERSION	,
};

const int protos[]={
        IPPROTO_IPIP,
        IPPROTO_IPV6,
        IPPROTO_GRE,
};

const int flagss[]={
        IP6_TNL_F_RCV_DSCP_COPY,
        IP6_TNL_F_ALLOW_LOCAL_REMOTE,
};

#define IP6_FLOWINFO_TCLASS	htonl(0x0FF00000)
#define IP6_FLOWINFO_FLOWLABEL	htonl(0x000FFFFF)

const uint32_t flow_infos[]={
        IP6_FLOWINFO_TCLASS,
        IP6_FLOWINFO_FLOWLABEL,
};
const char name[16]="hme0";

void rand_ip6_tnl_parm2(ip6_tnl_parm2 & parm){
    parm.i_flags=RAND_FROM(i_or_o_flags);
    parm.o_flags=RAND_FROM(i_or_o_flags);
    parm.proto=RAND_FROM(protos);
    parm.flags=RAND_FROM(flagss);
    parm.i_key=getRand(INT32_MAX,0);
    parm.i_key=getRand(INT32_MAX,0);
    parm.flowinfo=RAND_FROM(flow_infos);

    memcpy(parm.name,name,strlen(name));
}

int tunnel::do_add(int cmd)
{
    ip6_tnl_parm2 p={0};
    const char *basedev = "ip6tnl0";

    ip6_tnl_parm_init(&p, 1);

    p.proto = IPPROTO_IPV6;
    rand_ip6_tnl_parm2(p);
    if (p.proto == IPPROTO_GRE)
        basedev = "ip6gre0";
    else if (p.i_flags & VTI_ISVTI)
        basedev = "ip6_vti0";
    return tnl_add_ioctl(cmd, basedev, p.name, &p);
}

int tunnel::tnl_add_ioctl(int cmd, const char *basedev, const char *name, void *p) {
    ifreq ifr={};
    int fd;
    int err;

    if (cmd == SIOCCHGTUNNEL && name[0])
        strncpy(ifr.ifr_name, name, IFNAMSIZ);
    else
        strncpy(ifr.ifr_name, basedev, IFNAMSIZ);
    ifr.ifr_ifru.ifru_data = p;

    fd = socket(preferred_family, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("add socket failed: ");
        return -1;
    }

    err = ioctl(fd, cmd, &ifr);
    if (err){
        perror("add tunnel failed: ");
    }

    close(fd);
    return err;
}