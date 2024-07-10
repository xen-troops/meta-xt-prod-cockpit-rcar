# Intel renamed 'master' branch to 'main' so we
# have to overwrite SRC_URI with proper branch
SRC_URI = "git://github.com/intel/${BPN};branch=main;protocol=https"
SRCREV = "db7087b883bf52cbff063ad17a41cc1cbb85104d"
