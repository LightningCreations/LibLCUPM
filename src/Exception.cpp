/*
 * Exception.cpp
 *
 *  Created on: Jul. 29, 2019
 *      Author: chorm
 */

#include <lcupm/Exceptions.hpp>
#include <lcupm/Downloader.hpp>

namespace lightningcreations::lcupm::exception{
	BadReferenceException::BadReferenceException(const std::string& ref):BadReferenceException(ref,"Bad Reference URI"){}
	BadReferenceException::BadReferenceException(const std::string& ref,const std::string& prefix):LCUPMException(prefix+"->"+ref){}
	UnfollowableReferenceException::UnfollowableReferenceException(const std::string& ref):BadReferenceException(ref,"Unable to follow reference URI"){}
}





