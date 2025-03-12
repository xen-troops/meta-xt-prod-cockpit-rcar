do_install:append () {
        echo "if [ -z \$SSH_CONNECTION ]; then" >> ${D}${sysconfdir}/profile
	echo "	shopt -s checkwinsize" >> ${D}${sysconfdir}/profile
	echo "	resize 1> /dev/null" >> ${D}${sysconfdir}/profile
	echo "fi" >> ${D}${sysconfdir}/profile
}
