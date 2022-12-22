#!/bin/bash
systemctl stop cluster-view
cp /tmp/cluster-view.service /lib/systemd/system/cluster-view.service
systemctl daemon-reload
systemctl start cluster-view
