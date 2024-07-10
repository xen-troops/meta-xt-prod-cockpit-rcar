# Avoid redundant runtime dependency on python3-core
RDEPENDS:${PN}:remove:class-target = " ${PYTHON_PN}-core" 
RRECOMMENDS:${PN}:remove = " qemu"
