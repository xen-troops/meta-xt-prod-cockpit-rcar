FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

AOS_IAM_IDENT_MODULES = "\
    identhandler/modules/visidentifier \
"

pkg_postinst_${PN}() {
    # Add aosiam to /etc/hosts
    if ! grep -q 'aosiam' $D${sysconfdir}/hosts ; then
        echo '127.0.0.1	aosiam' >> $D${sysconfdir}/hosts
    fi
}
