AC_INIT(liblcupm,1.0)

AC_SUBST_FILE(Makefile)

AC_DEFUN(LIBLCUPM_DOWNLOADER_SWITCH,[
	AC_ARG_ENABLE([downloader-$1],[--disable-downloader-$1 -> Prevents the export of the downloader for the $1 protocol. --enable-$1 has the opposite effect. By default this is $2. $4],
	[
		downloader-$1=$enableval
	],
	[
		downloader-$1=$3
	])
	AC_SUBST([downloader-$1])
])

AC_DEFUN(LIBLCUPM_TOOLKIT_SWITCH,[
	AC_ARG_ENABLE([toolkit-$1],[--disable-download-$1 -> Prevents the generation of the toolkit $1. By default this is enabled if the required library exists.],
	[
		toolkit-$1 = $enableval
	],[
		toolkit-$1 = maybe
	])
	AC_SUBST([toolkit-$1])
])

AC_PROG_CC(gcc-8 gcc cc)
AC_PROG_CPP
AC_PROG_CXX(g++-8 g++ c++)
AC_PROG_CXXCPP

AC_ARG_WITH([prefix],[--with-prefix=<dir> override the default installation prefix to dir. This causes headers to be installed in <prefix>/include, and libraries to be installed in <prefix>/lib. By default this is /usr],[
	prefix=$withval
],
[
	prefix=/usr
])

AC_ARG_ENABLE([shared],[--disable-shared -> prevents implicit generation of dyanmic/shared build and install targets],[
	shared=$enableval
],
[
	shared=yes
])

AC_ARG_ENABLE([static],[--disable-static -> prevents implicity generation of static build and install targets],[	share
	static=$enableval
],
[
	static=yes
])

LIBLCUPM_DOWNLOADER_SWITCH(http,enabled,yes,[HTTP (Hypertext Transfer Protocol) is a primary method of fetching packages and is usually neccessary unless building for specialized environments. It is not recommened to disable this switch. HTTP includes HTTPS])
LIBLCUPM_DOWNLOADER_SWITCH(ftp,enabled,yes,[FTP (File Transfer Protocol) is a primary method of fetching packages, and allows a backup for servers that do not want to release files via http. It is optional to disable this switch. FTP includes SFTP (FTP/TLS) and FTPS (FTP/SSH))])
LIBLCUPM_DOWNLOADER_SWITCH(torrent,disabled,no, [Bittorrent is a specialized method of fetching packages. It is optional to enable, but can improve download times.])
LIBLCUPM_DOWNLOADER_SWITCH(smb,disabled,no, [SMB is a a specialized method of fetching packages usually only used for organizations which want to control the available packages, or supply organization specific packages. In most cases, this switch can be left off])
	
LIBLCUPM_TOOLKIT_SWITCH(sfml)
LIBLCUPM_TOOLKIT_SWITCH(sdl)
LIBLCUPM_TOOLKIT_SWITCH(gtk)
LIBLCUPM_TOOLKIT_SWITCH(x11)





AC_OUTPUT
