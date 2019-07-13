/*
 * DistInfo.hpp
 *
 *  Created on: Jul. 12, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_DISTINFO_HPP_
#define INCLUDE_LCUPM_DISTINFO_HPP_

#define OS_NAME_LINUX "linux"
#define OS_NAME_WINDOWS "windows"
#define OS_NAME_WINE "wine"
#define OS_NAME_CYGWIN "cygwin"
#define ARCH_NAME_x86 "x86"
#define ARCH_NAME_x64 "amd64"
#define ARCH_NAME_arm "arm"
#define TK_NAME_X11 "x11"
#define TK_NAME_GTK "gtk"
#define TK_NAME_SDL "sdl"
#define TK_NAME_SFML "sfml"
#define TK_NAME_DX "directx"
#define TK_NAME_WIN32 "win32"

#ifdef __linux__
#define LCUPM_DIST_OS_LINUX 1
#define LCUPM_DIST_OS_WINE 0
#define LCUPM_DIST_POSIX
#define LCUPM_DIST_TK_X11 0
#define LCUPM_DIST_TK_GTK 2
#define LCUPM_DIST_TK_SDL 3
#define LCUPM_DIST_TK_SFML 1
#ifdef __i386__
#define LCUPM_ARCH_x86 0
#endif
#ifdef __amd64__
#define LCUPM_ARCH_x64 1
#define LCUPM_ARCH_x86 0
#endif
#ifdef __arm__
#define LCUPM_ARCH_arm 0
#endif
#elif defined(__WIN32)
#define LCUPM_DIST_OS_WINDOWS 1
#define LCUPM_DIST_OS_CYGWIN 0
#define LCUPM_DIST_TK_DX 2
#define LCUPM_DIST_TK_SFML 1
#define LCUPM_DIST_TK_WIN32 0
#endif



#endif /* INCLUDE_LCUPM_DISTINFO_HPP_ */
