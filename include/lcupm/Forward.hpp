/*
 * Forward.hpp
 *
 *  Created on: Jul. 12, 2019
 *      Author: chorm
 */

#ifndef INCLUDE_FORWARD_HPP_
#define INCLUDE_FORWARD_HPP_

#include <vector>
#include <functional>

namespace lightningcreations::lcupm{
	class URI;

	class PlatformInfo;

	namespace provider{
		class Provider;
		class ProviderKey;
		class ProviderRef;
		class KeyRef;
		class ProviderList;
		class ProviderCache;
	}

	namespace source{
		class PackageSource;
		class SourceRef;
		class PackageLookup;
		class SourceList;
		class SourceCache;
	}

	namespace package{
		class Package;
		class PackageRef;
		class PackageInfo;
		class PackageTask;
		class PackageList;
		class PackageCache;
	}

	namespace downloaders{
		class Downloader;
		class HTTPDownloader;
		class TorrentDownloader;
		class FTPDownloader;
		class SMBDownloader;
	}

	namespace torrent{
		class MagnetLinkResolver;
	}

	namespace exception{
		class LCUPMException;
		class DownloadException;
		class CorruptCacheException;
		class UnfollowableReferenceException;
		class IncompatiblePackageException;
		class BadReferenceException;
		class BadPackageException;
	}
}




#endif /* INCLUDE_FORWARD_HPP_ */
