SECTION = "console/utils"
DESCRIPTION = "gnupg - GNU privacy guard"
HOMEPAGE = "http://www.gnupg.org/"
LICENSE = "GPLv2"
DEPENDS = "zlib bzip2"

inherit autotools gettext

MIRRORS_prepend () {
ftp://ftp.gnupg.org/gcrypt	http://mirrors.rootmode.com/ftp.gnupg.org
}
SRC_URI = "ftp://ftp.gnupg.org/gcrypt/gnupg/gnupg-${PV}.tar.bz2;name=src"
S = "${WORKDIR}/gnupg-${PV}"

#   --with-egd-socket=NAME  use NAME for the EGD socket
#   --with-photo-viewer=FIXED_VIEWER  set a fixed photo ID viewer
#   --with-included-zlib    use the zlib code included here
#   --with-capabilities     use linux capabilities default=no
#   --with-mailprog=NAME    use "NAME -t" for mail transport
#   --with-libiconv-prefix[=DIR]  search for libiconv in DIR/include and DIR/lib
#   --without-libiconv-prefix     don't search for libiconv in includedir and libdir
#   --with-included-gettext use the GNU gettext library included here
#   --with-libintl-prefix[=DIR]  search for libintl in DIR/include and DIR/lib
#   --without-libintl-prefix     don't search for libintl in includedir and libdir
#   --with-included-regex   use the included GNU regex library
#   --with-zlib=DIR         use libz in DIR
#   --with-bzip2=DIR        look for bzip2 in DIR
#   --enable-static-rnd=egd|unix|linux|auto
#   --disable-dev-random    disable the use of dev random
#   --disable-asm           do not use assembler modules
#   --enable-m-guard        enable memory guard facility
#   --enable-selinux-support
#                           enable SELinux support
#   --disable-card-support  disable OpenPGP card support
#   --disable-gnupg-iconv   disable the new iconv code
#   --enable-backsigs       enable the experimental backsigs code
#   --enable-minimal        build the smallest gpg binary possible
#   --disable-rsa           disable the RSA public key algorithm
#   --disable-idea          disable the IDEA cipher
#   --disable-cast5         disable the CAST5 cipher
#   --disable-blowfish      disable the BLOWFISH cipher
#   --disable-aes           disable the AES, AES192, and AES256 ciphers
#   --disable-twofish       disable the TWOFISH cipher
#   --disable-sha256        disable the SHA-256 digest
#   --disable-sha512        disable the SHA-384 and SHA-512 digests
#   --disable-bzip2         disable the BZIP2 compression algorithm
#   --disable-exec          disable all external program execution
#   --disable-photo-viewers disable photo ID viewers
#   --disable-keyserver-helpers  disable all external keyserver support
#   --disable-ldap          disable LDAP keyserver interface
#   --disable-hkp           disable HKP keyserver interface
#   --disable-http          disable HTTP key fetching interface
#   --disable-finger        disable Finger key fetching interface
#   --disable-mailto        disable email keyserver interface
#   --disable-keyserver-path disable the exec-path option for keyserver helpers
#   --enable-key-cache=SIZE Set key cache to SIZE (default 4096)
#   --disable-largefile     omit support for large files
#   --disable-dns-srv       disable the use of DNS SRV in HKP and HTTP
#   --disable-nls           do not use Native Language Support
#   --disable-regex         do not handle regular expressions in trust sigs

EXTRA_OECONF = "--disable-ldap \
		--with-zlib=${STAGING_LIBDIR}/.. \
		--with-bzip2=${STAGING_LIBDIR}/.. \
		--disable-selinux-support"

do_install () {
	autotools_do_install
	install -d ${D}${docdir}/${PN}
	mv ${D}${datadir}/${PN}/* ${D}/${docdir}/${PN}/ || :
	mv ${D}${prefix}/doc/* ${D}/${docdir}/${PN}/ || :
}

# split out gpgv from main package
RDEPENDS_gnupg = "gpgv"
PACKAGES =+ "gpgv"
FILES_gpgv = "${bindir}/gpgv"

# Exclude debug files from the main packages
FILES_${PN} = "${bindir}/* ${datadir}/${PN} ${libexecdir}/${PN}/*"
FILES_${PN}-dbg += "${libexecdir}/${PN}/.debug"
