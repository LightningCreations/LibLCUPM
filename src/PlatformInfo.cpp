/*
 * PlatformInfo.cpp
 *
 *  Created on: Jul. 12, 2019
 *      Author: chorm
 */

#include <lcupm/DistInfo.hpp>
#include <lcupm/PlatformInfo.hpp>

#include <array>
#include <mutex>
#include <algorithm>

#define PRECEEDING

namespace lightningcreations::lcupm{
	struct dist_part{
		int priority;
		const char* name;

		bool operator<(const dist_part& other)const{
			return priority<other.priority;
		}
	};

	struct dist_info{
		int totalPriority;
		dist_part dist_os;
		dist_part dist_arch;
		dist_part dist_tk;
		dist_info(dist_part os,dist_part arch,dist_part tk):dist_os{os},dist_arch{arch},dist_tk{tk}{
			totalPriority = os.priority+arch.priority+tk.priority;
		}
		bool operator<(const dist_info& other){
			return totalPriority<other.totalPriority;
		}
	};


	static const auto& getOsNames(){
		static std::once_flag initOnce;
		static dist_part osNames[]{
#ifdef LCUPM_DIST_OS_LINUX
			PRECEEDING dist_part{LCUPM_DIST_OS_LINUX,OS_NAME_LINUX}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_OS_WINE
			PRECEEDING dist_part{LCUPM_DIST_OS_WINE,OS_NAME_WINE}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_OS_WINDOWS
			PRECEEDING dist_part{LCUPM_DIST_OS_WINDOWS,OS_NAME_WINDOWS}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_OS_CYGWIN
			PRECEEDING dist_part{LCUPM_DIST_OS_CYGWIN,OS_NAME_CYGWIN}
#undef PRECEEDING
#define PRECEEDING ,
#endif
		};
		std::call_once(initOnce,[&](){
			std::sort(std::begin(osNames),std::end(osNames));
		});
		return osNames;
	}
#undef PRECEEDING
#define PRECEEDING
	static const auto& getArchNames(){
		static std::once_flag initOnce;
		static dist_part archNames[]{
#ifdef LCUPM_ARCH_x64
		PRECEEDING dist_part{LCUPM_ARCH_x64,ARCH_NAME_x64}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_ARCH_x86
		PRECEEDING dist_part{LCUPM_ARCH_x86,ARCH_NAME_x86}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_ARCH_arm
		PRECEEDING dist_part{LCUPM_ARCH_arm,ARCH_NAME_arm}
#undef PRECEEDING
#define PRECEEDING ,
#endif
		};
		std::call_once(initOnce,[&](){
			std::sort(std::begin(archNames),std::end(archNames));
		});
		return archNames;
	}
#undef PRECEEDING
#define PRECEEDING
	static const auto& getToolkitNames(){
		static std::once_flag initOnce;
		static dist_part toolkitNames[]{
#ifdef LCUPM_DIST_TK_GTK
		PRECEEDING dist_part{LCUPM_DIST_TK_GTK,TK_NAME_GTK}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_TK_SFML
		PRECEEDING dist_part{LCUPM_DIST_TK_SFML,TK_NAME_SFML}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_TK_SDL
		PRECEEDING dist_part{LCUPM_DIST_TK_SDL,TK_NAME_SDL}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_TK_X11
		PRECEEDING dist_part{LCUPM_DIST_TK_X11,TK_NAME_X11}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_TK_DX
		PRECEEDING dist_part{LCUPM_DIST_TK_DX,TK_NAME_DX}
#undef PRECEEDING
#define PRECEEDING ,
#endif
#ifdef LCUPM_DIST_TK_WIN32
		PRECEEDING dist_part{LCUPM_DIST_TK_WIN32,TK_NAME_WIN32}
#undef PRECEEDING
#define PRECEEDING ,
#endif
		};
		std::call_once(initOnce,[&](){
			std::sort(std::begin(toolkitNames),std::end(toolkitNames));
		});
		return toolkitNames;
	}
#undef PRECEEDING

	static std::vector<dist_info> getDists(){
		std::vector<dist_info> dists;
		for(auto&& os:getOsNames())
			for(auto&& tk:getToolkitNames())
				for(auto&& arch:getArchNames())
					dists.emplace_back(os,tk,arch);
		std::sort(std::begin(dists),std::end(dists));
		return std::move(dists);
	}

	const std::vector<PlatformInfo>& getAvailablePlatforms(){
		static std::vector<dist_info> dists = getDists();
		static std::vector<PlatformInfo> platforms{};
		static std::once_flag initOnce;
		std::call_once(initOnce,[&](){
			platforms.reserve(dists.size());
			for(dist_info dist:dists)
				platforms.push_back(PlatformInfo{dist.dist_os.name,dist.dist_tk.name,dist.dist_arch.name});
		});
		return platforms;
	}
	const PlatformInfo& getCurrentPlatform(){
		return getAvailablePlatforms()[0];
	}

	PlatformInfo::PlatformInfo(const char* os,const char* tk,const char* arch):os(os),toolkit(tk),arch(arch){}
	const char* PlatformInfo::getOSName()const{
		return this->os;
	}
	const char* PlatformInfo::getArchName()const{
		return this->arch;
	}
	const char* PlatformInfo::getToolkitName()const{
		return this->toolkit;
	}

}



