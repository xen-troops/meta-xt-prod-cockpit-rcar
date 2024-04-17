# Intel renamed 'master' branch to 'main' so we
# have to overwrite SRC_URI with proper branch
SRC_URI = "git://github.com/intel/${BPN};branch=main;protocol=https"
