FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

pkg_postinst_${PN}() {
    # Add aossm to /etc/hosts
    if ! grep -q 'aossm' $D${sysconfdir}/hosts ; then
        echo '127.0.0.1	aossm' >> $D${sysconfdir}/hosts
    fi
}
