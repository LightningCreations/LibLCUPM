/*
 * Utilities.cpp
 *
 *  Created on: Jul. 23, 2019
 *      Author: chorm
 */

#include <lcupm/Utilities.hpp>

#include <cstdio>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace lightningcreations::lcupm::utilities{
	FileLock::FileLock(std::filesystem::path lockfile):lockfile(std::filesystem::absolute(lockfile)){}
	void FileLock::lock(){
		while((f = std::fopen(lockfile.u8string().c_str(),"wx")))
			while(std::filesystem::exists(lockfile))
				std::this_thread::sleep_for(50ms);
	}
	void FileLock::unlock(){
		std::fclose(f);
	}
	bool FileLock::try_lock(){
		return f = std::fopen(lockfile.u8string().c_str(),"wx");
	}
}


