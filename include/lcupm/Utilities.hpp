/*
 * Utilities.hpp
 *
 *  Created on: Jul. 23, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_UTILITIES_HPP_
#define INCLUDE_LCUPM_UTILITIES_HPP_

#include <filesystem>
#include <atomic>

namespace lightningcreations::lcupm::utilities{
	struct FileLock{
	private:
		std::filesystem::path lockfile;
		FILE* f;
		FileLock(const FileLock&)=delete;
		FileLock& operator=(const FileLock&)=delete;
	public:
		FileLock(std::filesystem::path lockfile);
		void lock();
		void unlock();
		bool try_lock();
	};
}




#endif /* INCLUDE_LCUPM_UTILITIES_HPP_ */
