pkg_postinst_ontarget:${PN} () {
     ;
}

pkg_postinst:${PN} () {
#!/bin/sh
# should run online
if [ "x$D" != "x" ]; then
    exit 1
fi
echo "export QT_IM_MODULE=Maliit" >> /etc/xprofile
ln -s /usr/share/applications/maliit-server.desktop /etc/xdg/autostart/maliit-server.desktop
}

pkg_postrm:${PN} () {
#!/bin/sh
# should run online
if [ "x$D" = "x" ]; then
    if [ -e "/etc/xprofile" ]; then
        sed -i -e "g|export QT_IM_MODULE=Maliit|d" /etc/xprofile
    fi
    rm -f /etc/xdg/autostart/maliit-server.desktop
    exit 1
fi
if [ -e "/etc/xprofile" ]; then
    sed -i -e "g|export QT_IM_MODULE=Maliit|d" /etc/xprofile
fi
rm -f /etc/xdg/autostart/maliit-server.desktop
}
