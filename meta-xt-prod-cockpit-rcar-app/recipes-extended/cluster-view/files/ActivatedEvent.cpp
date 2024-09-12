
#include <QDebug>
#include <stdint.h>
#include <linux/rpmsg.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/r_taurus_cluster_protocol.h>
#include "ActivatedEvent.h"

ActivatedEvent::ActivatedEvent()
{
    file = open("/dev/cluster-taurus", O_WRONLY);

    if(file < 0)
    {
        throw std::invalid_argument("No device /dev/cluster-taurus");
    }
    ioctl(file, CLUSTER_ACTIVE, 1);
}
ActivatedEvent::~ActivatedEvent()
{
    close(file);
}

