AC_INIT(liblcupm,1.0)

AC_SUBST_FILE(Makefile)

AC_DEFUN(LIBLCUPM_DOWNLOADER_SWITCH,[
	AC_ARG_ENABLE([downloader-$1],[--disable-downloader-$1 -> Prevents the export of the downloader for the $1 protocol. --enable-$1 has the opposite effect. By default this is $2. $4],
	[
		downloader_$1=$enableval
	],
	[
		downloader_$1=$3
	])
	AC_SUBST([downloader_$1])
])

AC_DEFUN(LIBLCUPM_TOOLKIT_SWITCH,[
	AC_ARG_ENABLE([toolkit-$1],[--disable-download-$1 -> Prevents the generation of the toolkit $1. By default this is enabled if the required library exists.],
	[
		toolkit_$1=$enableval
	],[
		toolkit_$1=maybe
	])
	AC_SUBST([toolkit_$1])
])

AC_PROG_CC(gcc gcc-8 cc)
AC_PROG_CPP
AC_PROG_CXX(g++ g++-8 c++)
AC_PROG_CXXCPP


AC_ARG_ENABLE([shared],[--disable-shared -> prevents implicit generation of dyanmic/shared build and install targets],[
	shared=$enableval
],
[
	shared=yes
])
AC_SUBST(shared)

AC_ARG_ENABLE([static],[--disable-static -> prevents implicity generation of static build and install targets],[	share
	static=$enableval
],
[
	static=yes
])
AC_SUBST(static)

LIBLCUPM_DOWNLOADER_SWITCH(http,enabled,yes,[HTTP (Hypertext Transfer Protocol) is a primary method of fetching packages and is usually neccessary unless building for specialized environments. It is not recommened to disable this switch. HTTP includes HTTPS])
LIBLCUPM_DOWNLOADER_SWITCH(ftp,enabled,yes,[FTP (File Transfer Protocol) is a primary method of fetching packages, and allows a backup for servers that do not want to release files via http. It is optional to disable this switch. FTP includes SFTP (FTP/TLS) and FTPS (FTP/SSH))])
LIBLCUPM_DOWNLOADER_SWITCH(torrent,disabled,no, [Bittorrent is a specialized method of fetching packages. It is optional to enable, but can improve download times.])
LIBLCUPM_DOWNLOADER_SWITCH(smb,disabled,no, [SMB is a a specialized method of fetching packages usually only used for organizations which want to control the available packages, or supply organization specific packages. In most cases, this switch can be left off])

AC_ARG_WITH([package-name],[--with-package-name=<name> The name of the lcupm package being created (default is liblcupm)],[
	packagename=$withval
],[
	packagename=liblcupm
])
AC_SUBST([packagename])

AC_ARG_WITH([package-provider],[--with-package-provider=<name> The name of the provider that is creating this package],[
	packageprovider=$withval
],[
	packageprovider=lcroot
])


AC_ARG_ENABLE([arch-i386],[--enable-arch-i386 -> Builds support for 32-bit distributions on linux. This is default for windows builds and 32-bit linux],[
	forcei386=$withval
],[
	forcei386=no
])

AC_ARG_ENABLE([arch-amd64],[--enable-arch-amd64 -> Builds support for 64-bit distributions. This is default for all 64-bit builds],[
	forceamd64=$withval
],[
	forceamd64=no
])

AC_ARG_ENABLE([arch-arm],[--enable-arch-arm -> Builds support for arm. This is default when the package is being built on arm],[
	forcearm=$withval
],[
	forcearm=no
])


AC_SUBST([packageprovider])
AC_SUBST([forcei386])
AC_SUBST([forceamd64])
AC_SUBST([forcearm])

LIBLCUPM_TOOLKIT_SWITCH(sfml)
LIBLCUPM_TOOLKIT_SWITCH(sdl)
LIBLCUPM_TOOLKIT_SWITCH(gtk)
LIBLCUPM_TOOLKIT_SWITCH(x11)

AC_CONFIG_FILES([Makefile package/liblcupm.json])

AC_OUTPUT
