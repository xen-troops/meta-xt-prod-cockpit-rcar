#!/bin/bash
tar -cvjSf update-mode.tar.bz2 ./cluster-view.service update-cluster.sh
tar cvf ic-update.tar ./metadata.json ./update-mode.tar.bz2
