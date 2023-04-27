#!/bin/bash

#set app dir
APP_DIR=$(pwd)

#resize and RLE compress the images according to the rescaling_info file
cd ${APP_DIR}/app/2d-wow-cluster-demo/src/image/tga_resize
cat  ../rescaling_info_${1}|  ./resize.awk;:
cd ${APP_DIR}
cr7-image-gen ${APP_DIR}/app/2d-wow-cluster-demo/src/image/tga_resize ${APP_DIR}/app/2d-wow-cluster-demo/src/misc/ 
