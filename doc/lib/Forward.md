# Forward Declarations of LCUPM Definitions

In Header `<lcupm/Forward.hpp>`

Contains forward declarations of all class types which are defined by the public API of LibLCUPM. 
No definitions or descriptions of these classes will be given here, they will be given in the appropriate documentation file.

## Header Synopsis lcupm/Forward.hpp

```

namespace lightningcreations{
	class Version;
	namespace lcupm{
		class URI;
		class PlatformInfo;
		namespace downloaders{
			class Downloader;
		}
		namespace exception{
			class LCUPMException;
			class DownloadException;
			class CorruptCacheException;
			class BadPackageExcepton;
			class BadReferenceException;
			class UnfollowableReferenceException;
			class IncompatiblePackageException;
		}
		namespace package{
			class Package;
			class PackageCache;
			class PackageInfo;
			class PackageList;
			class PackageRef;
			class PackageTask;
		}
		namespace provider{
			class KeyRef;
			class Provider;
			class ProviderCache;
			class ProviderKey;
			class ProviderList;
			class ProviderRef;
		}
		namespace source{
			class PackageLookup;
			class PackageSource;
			class SourceCache;
			class SourceList;
			class SourceRef;
		}
		namespace torrent{
			class MagnetLinkResolver;
		}
	}
}
```
