
#include <QDebug>
#include <stdint.h>
#include <linux/rpmsg.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#ifndef UNIT_TEST
#include <linux/r_taurus_cluster_protocol.h>
#endif
#include "ActivatedEvent.h"

ActivatedEvent::ActivatedEvent()
{
#ifndef UNIT_TEST
    file = open("/dev/cluster-taurus", O_WRONLY);

    if(file < 0)
    {
        throw std::invalid_argument("No device /dev/cluster-taurus");
    }
    ioctl(file, CLUSTER_ACTIVE, 1);
#endif
}
ActivatedEvent::~ActivatedEvent()
{
#ifndef UNIT_TEST
    close(file);
#endif
}

