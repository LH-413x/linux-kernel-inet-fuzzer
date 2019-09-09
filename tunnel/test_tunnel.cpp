//
// Created by liuhao on 2019/9/9.
//

#include <tunnel.h>

int main(){
    //unshare(CLONE_NEWUSER);
    //unshare(CLONE_NEWNET);
    tunnel t;
    t.rand_do_add();
}