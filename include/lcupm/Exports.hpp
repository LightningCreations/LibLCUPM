/*
 * Exports.hpp
 *
 *  Created on: Jul. 17, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_LCUPM_EXPORTS_HPP_
#define INCLUDE_LCUPM_EXPORTS_HPP_

#ifdef _WIN32
#define LCUPM_EXPORT __declspec(dllexport)
#define LCUPM_IMPORT __declspec(dllimport)
#else
#define LCUPM_EXPORT __attribute__((visibility("default")))
#define LCUPM_IMPORT __attribute__((visibility("default")))
#endif

#ifdef LCUPM_BUILD
#define LCUPM_API LCUPM_EXPORT
#else
#define LCUPM_API LCUPM_IMPORT
#endif



#endif /* INCLUDE_LCUPM_EXPORTS_HPP_ */
