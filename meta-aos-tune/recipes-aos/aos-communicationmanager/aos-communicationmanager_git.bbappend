FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

pkg_postinst_${PN}() {
    # Add aoscm to /etc/hosts
    if ! grep -q 'aoscm' $D${sysconfdir}/hosts ; then
        echo '127.0.0.1	aoscm' >> $D${sysconfdir}/hosts
    fi
}
