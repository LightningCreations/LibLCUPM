/*
 * Exceptions.hpp
 *
 *  Created on: Jul. 29, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_EXCEPTIONS_HPP_
#define INCLUDE_LCUPM_EXCEPTIONS_HPP_

#include <lcupm/Forward.hpp>

#include <exception>
#include <stdexcept>

namespace lightningcreations::lcupm::exception{
	class LCUPMException:public std::runtime_error{
	public:
		using runtime_error::runtime_error;
	};

	class BadReferenceException:public LCUPMException{
	protected:
		BadReferenceException(const std::string& ref,const std::string& prefix);
	public:
		BadReferenceException(const std::string& ref);
	};

	class UnfollowableReferenceException:public BadReferenceException{
	public:
		UnfollowableReferenceException(const std::string&);
	};
}



#endif /* INCLUDE_LCUPM_EXCEPTIONS_HPP_ */
