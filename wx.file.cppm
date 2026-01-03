module;

#define WX_CPPM_FILE
#include "wx_file"

export module wx.file;

import wx.proto;
import wx.resource;

#pragma region Win32 Prototype Includes
namespace WX {
	
#pragma region FileApi.h
#undef FindFirstChangeNotification
inline HANDLE FindFirstChangeNotification(LPCSTR lpPathName, BOOL bWatchSubtree, DWORD dwNotifyFilter)
	assertl_reflect_as(auto h = ::FindFirstChangeNotificationA(lpPathName, bWatchSubtree, dwNotifyFilter); h != INVALID_HANDLE_VALUE, h);
inline HANDLE FindFirstChangeNotification(LPCWSTR lpPathName, BOOL bWatchSubtree, DWORD dwNotifyFilter)
	assertl_reflect_as(auto h = ::FindFirstChangeNotificationW(lpPathName, bWatchSubtree, dwNotifyFilter); h != INVALID_HANDLE_VALUE, h);
#undef FindNextFile
inline void FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
	assertl_reflect_as(::FindNextFileA(hFindFile, lpFindFileData));
inline void FindNextFile(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
	assertl_reflect_as(::FindNextFileW(hFindFile, lpFindFileData));
#undef GetDiskFreeSpace
inline void GetDiskFreeSpace(LPCSTR lpRootPathName, LPDWORD lpSectorsPerCluster, LPDWORD lpBytesPerSector,
							  LPDWORD lpNumberOfFreeClusters, LPDWORD lpTotalNumberOfClusters)
	assertl_reflect_as(::GetDiskFreeSpaceA(lpRootPathName, lpSectorsPerCluster, lpBytesPerSector,
										   lpNumberOfFreeClusters, lpTotalNumberOfClusters));
inline void GetDiskFreeSpace(LPCWSTR lpRootPathName, LPDWORD lpSectorsPerCluster, LPDWORD lpBytesPerSector,
							 LPDWORD lpNumberOfFreeClusters, LPDWORD lpTotalNumberOfClusters)
	assertl_reflect_as(::GetDiskFreeSpaceW(lpRootPathName, lpSectorsPerCluster, lpBytesPerSector,
										   lpNumberOfFreeClusters, lpTotalNumberOfClusters));
#undef GetDiskFreeSpaceEx
inline void GetDiskFreeSpace(LPCSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailable,
							   PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes)
	assertl_reflect_as(::GetDiskFreeSpaceExA(lpDirectoryName, lpFreeBytesAvailable, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes));
inline void GetDiskFreeSpace(LPCWSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailable,
							   PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes)
	assertl_reflect_as(::GetDiskFreeSpaceExW(lpDirectoryName, lpFreeBytesAvailable, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes));
#undef GetDiskSpaceInformation
inline void GetDiskSpaceInformation(LPCSTR rootPath, DISK_SPACE_INFORMATION *diskSpaceInfo)
	assertl_reflect_as(SUCCEEDED(::GetDiskSpaceInformationA(rootPath, diskSpaceInfo)));
inline void GetDiskSpaceInformation(LPCWSTR rootPath, DISK_SPACE_INFORMATION *diskSpaceInfo)
	assertl_reflect_as(SUCCEEDED(::GetDiskSpaceInformationW(rootPath, diskSpaceInfo)));
#undef GetDriveType
inline UINT GetDriveType(LPCSTR lpRootPathName)
	reflect_as(::GetDriveTypeA(lpRootPathName));
inline UINT GetDriveType(LPCWSTR lpRootPathName)
	reflect_as(::GetDriveTypeW(lpRootPathName));
#undef GetFinalPathNameByHandle
inline DWORD GetFinalPathNameByHandle(HANDLE hFile, LPSTR lpszFilePath, DWORD cchFilePath, DWORD dwFlags)
	assertl_reflect_as(auto n = ::GetFinalPathNameByHandleA(hFile, lpszFilePath, cchFilePath, dwFlags), n);
inline DWORD GetFinalPathNameByHandle(HANDLE hFile, LPWSTR lpszFilePath, DWORD cchFilePath, DWORD dwFlags)
	assertl_reflect_as(auto n = ::GetFinalPathNameByHandleW(hFile, lpszFilePath, cchFilePath, dwFlags), n);
#undef GetLongPathName
inline DWORD GetLongPathName(LPCSTR lpszShortPath, LPSTR lpszLongPath, DWORD cchBuffer)
	assertl_reflect_as(auto n = ::GetLongPathNameA(lpszShortPath, lpszLongPath, cchBuffer), n);
inline DWORD GetLongPathName(LPCWSTR lpszShortPath, LPWSTR lpszLongPath, DWORD cchBuffer)
	assertl_reflect_as(auto n = ::GetLongPathNameW(lpszShortPath, lpszLongPath, cchBuffer), n);
#undef GetShortPathName
// from WinBase.h
inline DWORD GetShortPathName(LPCSTR lpszLongPath, LPSTR lpszShortPath, DWORD cchBuffer)
	assertl_reflect_as(auto res = ::GetShortPathNameA(lpszLongPath, lpszShortPath, cchBuffer), res);
inline DWORD GetShortPathName(LPCWSTR lpszLongPath, LPWSTR lpszShortPath, DWORD cchBuffer)
	assertl_reflect_as(auto res = ::GetShortPathNameW(lpszLongPath, lpszShortPath, cchBuffer), res);
#undef GetTempFileName
inline UINT GetTempFileName(LPCSTR lpPathName, LPCSTR lpPrefixString, UINT uUnique, LPSTR lpTempFileName)
	assertl_reflect_as(auto n = ::GetTempFileNameA(lpPathName, lpPrefixString, uUnique, lpTempFileName), n);
inline UINT GetTempFileName(LPCWSTR lpPathName, LPCWSTR lpPrefixString, UINT uUnique, LPWSTR lpTempFileName)
	assertl_reflect_as(auto n = ::GetTempFileNameW(lpPathName, lpPrefixString, uUnique, lpTempFileName), n);
// GetVolumeInformationByHandle
inline void GetVolumeInformationByHandle(HANDLE hFile, LPWSTR lpVolumeNameBuffer, DWORD nVolumeNameSize,
										 LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength,
										 LPDWORD lpFileSystemFlags, LPWSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)
	assertl_reflect_as(::GetVolumeInformationByHandleW(hFile, lpVolumeNameBuffer, nVolumeNameSize,
													   lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags,
													   lpFileSystemNameBuffer, nFileSystemNameSize));
#undef GetVolumeInformation
inline void GetVolumeInformation(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize,
									LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength,
									LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)
	assertl_reflect_as(::GetVolumeInformationA(lpRootPathName, lpVolumeNameBuffer, nVolumeNameSize,
											   lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags,
											   lpFileSystemNameBuffer, nFileSystemNameSize));
inline void GetVolumeInformation(LPCWSTR lpRootPathName, LPWSTR lpVolumeNameBuffer, DWORD nVolumeNameSize,
								 LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength,
								 LPDWORD lpFileSystemFlags, LPWSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)
	assertl_reflect_as(::GetVolumeInformationW(lpRootPathName, lpVolumeNameBuffer, nVolumeNameSize,
											   lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags,
											   lpFileSystemNameBuffer, nFileSystemNameSize));
// FindFirstStream
inline HANDLE FindFirstStream(LPCWSTR lpFileName, STREAM_INFO_LEVELS InfoLevel, LPVOID lpFindStreamData, DWORD dwFlags)
	assertl_reflect_as(auto h = ::FindFirstStreamW(lpFileName, InfoLevel, lpFindStreamData, dwFlags), h);
// FindNextStream
inline void FindNextStream(HANDLE hFindStream, LPVOID lpFindStreamData)
	assertl_reflect_as(::FindNextStreamW(hFindStream, lpFindStreamData));
#undef GetTempPath
inline DWORD GetTempPath(LPSTR lpBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetTempPathA(nSize, lpBuffer), n);
inline DWORD GetTempPath(LPWSTR lpBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetTempPathW(nSize, lpBuffer), n);
#undef FindFirstFileName
inline HANDLE FindFirstFileName(LPCWSTR lpFileName, DWORD dwFlags, LPDWORD StringLength, LPWSTR LinkName)
	assertl_reflect_as(auto h = ::FindFirstFileNameW(lpFileName, dwFlags, StringLength, LinkName); h != INVALID_HANDLE_VALUE, h);
// FindNextFileName
inline void FindNextFileName(HANDLE hFindStream, LPDWORD StringLength, LPWSTR LinkName)
	assertl_reflect_as(::FindNextFileNameW(hFindStream, StringLength, LinkName));
#if (NTDDI_VERSION >= NTDDI_WIN10_FE)
#	undef GetTempPath2
inline DWORD GetTempPath2(LPSTR lpBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetTempPath2A(nSize, lpBuffer), n);
inline DWORD GetTempPath2(LPWSTR lpBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetTempPath2W(nSize, lpBuffer), n);
#endif
#undef CreateFile
inline HANDLE CreateFile(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
						 DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
	assertl_reflect_as(auto h = ::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
											  dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile); h != INVALID_HANDLE_VALUE, h);
inline HANDLE CreateFile(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
						 DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
	assertl_reflect_as(auto h = ::CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
											  dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile); h != INVALID_HANDLE_VALUE, h);
#undef CreateDirectory
inline void CreateDirectory(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateDirectoryA(lpPathName, lpSecurityAttributes));
inline void CreateDirectory(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateDirectoryW(lpPathName, lpSecurityAttributes));
#if defined(NTDDI_WIN11_GE) && (NTDDI_VERSION >= NTDDI_WIN11_GE) && !__GNUC__
#undef CreateDirectory2
inline void CreateDirectory(LPCSTR lpPathName, DWORD dwDesiredAccess, DWORD dwShareMode,
							DIRECTORY_FLAGS DirectoryFlags, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateDirectory2A(lpPathName, dwDesiredAccess, dwShareMode, DirectoryFlags, lpSecurityAttributes));
inline void CreateDirectory(LPCWSTR lpPathName, DWORD dwDesiredAccess, DWORD dwShareMode,
							DIRECTORY_FLAGS DirectoryFlags, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateDirectory2W(lpPathName, dwDesiredAccess, dwShareMode, DirectoryFlags, lpSecurityAttributes));
#undef RemoveDirectory2
inline void RemoveDirectory(LPCSTR lpPathName, DIRECTORY_FLAGS DirectoryFlags)
	assertl_reflect_as(::RemoveDirectory2A(lpPathName, DirectoryFlags));
inline void RemoveDirectory(LPCWSTR lpPathName, DIRECTORY_FLAGS DirectoryFlags)
	assertl_reflect_as(::RemoveDirectory2W(lpPathName, DirectoryFlags));
#undef DeleteFile
// from WinBase.h
inline void DeleteFile(LPCSTR lpFileName)
	assertl_reflect_as(::DeleteFileA(lpFileName));
inline void DeleteFile(LPCWSTR lpFileName)
	assertl_reflect_as(::DeleteFileW(lpFileName));
#undef DeleteFile2
inline void DeleteFile(LPCSTR lpFileName, DWORD Flags)
	assertl_reflect_as(::DeleteFile2A(lpFileName, Flags));
inline void DeleteFile(LPCWSTR lpFileName, DWORD Flags)
	assertl_reflect_as(::DeleteFile2W(lpFileName, Flags));
#endif
#pragma endregion

#pragma region WinBase.h (part)
#pragma endregion

}
#pragma endregion

export namespace WX {

#pragma region File
enum_flags(FileAccess, HandleAccess,
	Default = 0,
	ReadData             = FILE_READ_DATA,        // file & pipe
	ListDirectory        = FILE_LIST_DIRECTORY,   // directory
	WriteData            = FILE_WRITE_DATA,       // file & pipe
	AddFile              = FILE_ADD_FILE,         // directory
	AppendData           = FILE_APPEND_DATA,      // file
	AddSubdirectory      = FILE_ADD_SUBDIRECTORY, // directory
	CreatePipeInstance   = FILE_CREATE_PIPE_INSTANCE, // named pipe
	ReadEA               = FILE_READ_EA,  // file & directory
	WriteEA              = FILE_WRITE_EA, // file & directory
	Execute              = FILE_EXECUTE,  // file
	Traverse             = FILE_TRAVERSE, // directory
	DeleteChild          = FILE_DELETE_CHILD,     // directory
	ReadAttributes       = FILE_READ_ATTRIBUTES,  // all
	WriteAttributes      = FILE_WRITE_ATTRIBUTES, // all
	GenericRead    = FILE_GENERIC_READ,
	GenericWrite   = FILE_GENERIC_WRITE,
	GenericExecute = FILE_GENERIC_EXECUTE,
	All            = FILE_ALL_ACCESS);
enum_flags(FileAttribute, DWORD,
	No = 0,
	ReadOnly              = FILE_ATTRIBUTE_READONLY,
	Hidden                = FILE_ATTRIBUTE_HIDDEN,
	System                = FILE_ATTRIBUTE_SYSTEM,
	Directory             = FILE_ATTRIBUTE_DIRECTORY,
	Archive               = FILE_ATTRIBUTE_ARCHIVE,
	Device                = FILE_ATTRIBUTE_DEVICE,
	Normal                = FILE_ATTRIBUTE_NORMAL,
	Temporary             = FILE_ATTRIBUTE_TEMPORARY,
	SparseFile            = FILE_ATTRIBUTE_SPARSE_FILE,
	ReparsePoint          = FILE_ATTRIBUTE_REPARSE_POINT,
	Compressed            = FILE_ATTRIBUTE_COMPRESSED,
	Offline               = FILE_ATTRIBUTE_OFFLINE,
	NotContentIndexed     = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
	Encrypted             = FILE_ATTRIBUTE_ENCRYPTED,
	IntegrityStream       = FILE_ATTRIBUTE_INTEGRITY_STREAM,
	Virtual               = FILE_ATTRIBUTE_VIRTUAL,
	NoScrubData           = FILE_ATTRIBUTE_NO_SCRUB_DATA,
	EA                    = FILE_ATTRIBUTE_EA,
	Pinned                = FILE_ATTRIBUTE_PINNED,
	Unpinned              = FILE_ATTRIBUTE_UNPINNED,
	RecallOnOpen          = FILE_ATTRIBUTE_RECALL_ON_OPEN,
	RecallOnDataAccess    = FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS);
enum_flags(FileFlag, DWORD,
	WriteThrough          = FILE_FLAG_WRITE_THROUGH,
	Overlapped            = FILE_FLAG_OVERLAPPED,
	NoBuffering           = FILE_FLAG_NO_BUFFERING,
	RandomAccess          = FILE_FLAG_RANDOM_ACCESS,
	SequentialScan        = FILE_FLAG_SEQUENTIAL_SCAN,
	DeleteOnClose         = FILE_FLAG_DELETE_ON_CLOSE,
	BackupSemantics       = FILE_FLAG_BACKUP_SEMANTICS,
	PosixSemantics        = FILE_FLAG_POSIX_SEMANTICS,
	SessionAware          = FILE_FLAG_SESSION_AWARE,
	OpenReparsePoint      = FILE_FLAG_OPEN_REPARSE_POINT,
	OpenNoRecall          = FILE_FLAG_OPEN_NO_RECALL,
	FirstPipeInstance     = FILE_FLAG_FIRST_PIPE_INSTANCE,
	OpenRequiringOplock   = FILE_FLAG_OPEN_REQUIRING_OPLOCK);//,
//	IgnoreImpersonatedDevicemap  = FILE_FLAG_IGNORE_IMPERSONATED_DEVICEMAP);
enum_flags(FileShares, DWORD,
	No = 0,
	Read   = FILE_SHARE_READ,
	Write  = FILE_SHARE_WRITE,
	Delete = FILE_SHARE_DELETE);
enum_class(FileTypes, DWORD, 
	Unknown = FILE_TYPE_UNKNOWN,
	Disk      = FILE_TYPE_DISK,
	Char      = FILE_TYPE_CHAR,
	Pipe      = FILE_TYPE_PIPE,
	Remote    = FILE_TYPE_REMOTE);
enum_flags(PageProtect, DWORD,
	NoAccess           = PAGE_NOACCESS,
	ReadOnly           = PAGE_READONLY,
	ReadWrite          = PAGE_READWRITE,
	WriteCopy          = PAGE_WRITECOPY,
	Execute            = PAGE_EXECUTE,
	ExecuteRead        = PAGE_EXECUTE_READ,
	ExecuteReadWrite   = PAGE_EXECUTE_READWRITE,
	ExecuteWriteCopy   = PAGE_EXECUTE_WRITECOPY);
enum_flags(MapAccess, DWORD,
	Write      = FILE_MAP_WRITE,
	Read       = FILE_MAP_READ,
	All        = FILE_MAP_ALL_ACCESS,
	Execute    = FILE_MAP_EXECUTE,
	Copy       = FILE_MAP_COPY,
	Targets    = FILE_MAP_TARGETS_INVALID,
	LargePages = FILE_MAP_LARGE_PAGES,
	ReadWrite = FILE_MAP_WRITE | FILE_MAP_READ);
//enum_flags(FileDispose)
struct FileTimes { FileTime Creation, LastAccess, LastWrite; };
class FileBaseInfo : public RefStruct<FILE_BASIC_INFO> {
public:
	using super = RefStruct<FILE_BASIC_INFO>;
public:
	FileBaseInfo() {}
	FileBaseInfo(const FILE_BASIC_INFO &fbi) : super(fbi) {}
public: // Property - TimeCreation
	/* W */ inline auto &TimeCreation(FileTime CreationTime) reflect_to_self(this->CreationTime = CreationTime);
	/* R */ inline FileTime TimeCreation() const reflect_as(this->CreationTime);
public: // Property - TimeLastAccess
	/* W */ inline auto &TimeLastAccess(FileTime LastAccessTime) reflect_to_self(this->LastAccessTime = LastAccessTime);
	/* R */ inline FileTime TimeLastAccess() const reflect_as(this->LastAccessTime);
public: // Property - TimeLastWrite
	/* W */ inline auto &TimeLastWrite(FileTime LastWriteTime) reflect_to_self(this->LastWriteTime = LastWriteTime);
	/* R */ inline FileTime TimeLastWrite() const reflect_as(this->LastWriteTime);
public: // Property - TimeChange
	/* W */ inline auto &TimeChange(FileTime ChangeTime) reflect_to_self(this->ChangeTime = ChangeTime);
	/* R */ inline FileTime TimeChange() const reflect_as(this->ChangeTime);
public: // Property - Attributes
	/* W */ inline auto &Attributes(FileAttribute fa) reflect_to_self(this->FileAttributes = fa.yield());
	/* R */ inline FileAttribute Attributes() const reflect_as(reuse_as<FileAttribute>(this->FileAttributes));
};
class BaseOf_Handle(File) {
public:
	using super = HandleBase<File>;
protected:
	File(HANDLE h) : super(h) {}
	File(const File &f) : super(f) {}
public:
	File() {}
	File(Null) {}
	File(File &f) : super(f) {}
	File(File &&f) : super(f) {}
public:
	template<bool IsUnicode = WX::IsUnicode>
	class CreateStruct {
		using LPCTSTR = LPCXSTR<IsUnicode>;
		LPCTSTR lpFileName;
		FileAccess dwDesiredAccess = FileAccess::Default;
		FileShares dwShareMode = FileShares::No;
		LPSECURITY_ATTRIBUTES lpAttributes = O;
		DWORD dwCreationDisposition = 0;
		FileAttribute dwFlagsAndAttributes = FileAttribute::No;
		HANDLE hTemplateFile = O;
	public:
		CreateStruct(LPCTSTR lpFileName) : lpFileName(lpFileName) {}
	public:
		inline auto &Accesses(FileAccess dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Share(FileShares dwShareMode) reflect_to_self(this->dwShareMode = dwShareMode);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpAttributes) reflect_to_self(this->lpAttributes = lpAttributes);
		inline auto &Template(HANDLE hTemplateFile) reflect_to_self(this->hTemplateFile = hTemplateFile);
		inline auto &Attributes(FileAttribute dwAttributes) reflect_to_self(this->dwFlagsAndAttributes = dwAttributes);
		inline auto &Flags(FileFlag dwFlags) reflect_to_self(this->dwFlagsAndAttributes = dwFlags.yield());
	public:
		inline auto &CreateNew() reflect_to_self(this->dwCreationDisposition = CREATE_NEW);
		inline auto &CreateAlways() reflect_to_self(this->dwCreationDisposition = CREATE_ALWAYS);
		inline auto &OpenExisting() reflect_to_self(this->dwCreationDisposition = OPEN_EXISTING);
		inline auto &OpenAlways() reflect_to_self(this->dwCreationDisposition = OPEN_ALWAYS);
		inline auto &TruncateExisting() reflect_to_self(this->dwCreationDisposition = TRUNCATE_EXISTING);
	public:
		inline operator File() reflect_as(WX::CreateFile(lpFileName, dwDesiredAccess.yield(), dwShareMode.yield(), lpAttributes, dwCreationDisposition, dwFlagsAndAttributes.yield(), hTemplateFile));
	};
	static inline CreateStruct<false> Create(LPCSTR lpFileName) reflect_as(lpFileName);
	static inline CreateStruct<true> Create(LPCWSTR lpFileName) reflect_as(lpFileName);
	template<bool IsUnicode = WX::IsUnicode>
	class MappingCreateStruct {
		using LPCTSTR = LPCXSTR<IsUnicode>;
		HANDLE hFile;
		LPSECURITY_ATTRIBUTES lpAttributes = O;
		DWORD flProtect = PageProtect::ReadWrite.yield();
		DWORD dwMaximumSizeHigh = 0;
		DWORD dwMaximumSizeLow = 0;
		LPCTSTR lpName;
	public:
		MappingCreateStruct(HANDLE hFile, LPCTSTR lpName, uint64_t size) :
			hFile(hFile),
			dwMaximumSizeHigh((DWORD)(size >> 32)), dwMaximumSizeLow((DWORD)size),
			lpName(lpName) {}
	public:
		inline auto &Security(LPSECURITY_ATTRIBUTES lpAttributes) reflect_to_self(this->lpAttributes = lpAttributes);
		inline auto &Protect(PageProtect pa) reflect_to_self(this->flProtect = pa.yield());
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator File() assertl_reflect_as(auto h = WX::CreateFileMapping(hFile, lpAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName), h);
	};
	inline MappingCreateStruct<> CreateMapping(uint64_t size) reflect_as({ self, O, size });
	inline MappingCreateStruct<false> CreateMapping(LPCSTR lpName, uint64_t size) reflect_as({ self, lpName, size });
	inline MappingCreateStruct<true> CreateMapping(LPCWSTR lpName, uint64_t size) reflect_as({ self, lpName, size });
	template<bool IsUnicode = WX::IsUnicode>
	class MappingOpenStruct {
		using LPCTSTR = LPCXSTR<IsUnicode>;
		DWORD dwDesiredAccess = MapAccess::ReadWrite.yield();
		bool bInheritHandle = false;
		LPCTSTR lpName;
	public:
		MappingOpenStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &Accesses(MapAccess pa) reflect_to_self(this->dwDesiredAccess = pa.yield());
		inline auto &Inherit(bool bInheritHandle) reflect_to_self(this->bInheritHandle = bInheritHandle);
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator File() assertl_reflect_as(auto h = WX::OpenFileMapping(dwDesiredAccess, bInheritHandle, lpName), h);
	};
	static inline MappingOpenStruct<false> OpenMapping(LPCSTR lpName) reflect_as(lpName);
	static inline MappingOpenStruct<true> OpenMapping(LPCWSTR lpName) reflect_as(lpName);
public:
	static inline void Delete(LPCSTR lpFileName) reflect_as(WX::DeleteFile(lpFileName));
	static inline void Delete(LPCWSTR lpFileName) reflect_as(WX::DeleteFile(lpFileName));
	static inline void Copy(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, bool bFailIfExists = false) reflect_to(WX::CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists));
	static inline void Copy(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, bool bFailIfExists = false) reflect_to(WX::CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists));
	static inline void Move(LPCSTR lpExistingFileName, LPCSTR lpNewFileName) reflect_to(WX::MoveFile(lpExistingFileName, lpNewFileName));
	static inline void Move(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName) reflect_to(WX::MoveFile(lpExistingFileName, lpNewFileName));
public:
	class MapPointer {
		friend class File;
		mutable void *ptr = O;
	protected:
		MapPointer(void *ptr) : ptr(ptr) {}
		MapPointer(const MapPointer &m) : ptr(m.ptr) reflect_to(m.ptr = O);
	public:
		MapPointer() {}
		MapPointer(Null) {}
		MapPointer(MapPointer &p) : ptr(p.ptr) reflect_to(p.ptr = O);
		MapPointer(MapPointer &&p) : ptr(p.ptr) reflect_to(p.ptr = O);
		~MapPointer() {
			if (ptr)
				UnmapViewOfFile(ptr);
			ptr = O;
		}
		template<class AnyType>
		inline operator AnyType *() reflect_as((AnyType *)ptr);
		inline void *operator&() reflect_as(ptr);
		inline auto &operator=(MapPointer &m) reflect_to_self(std::swap(m.ptr, ptr));
		inline auto &operator=(MapPointer &&m) reflect_to_self(std::swap(m.ptr, ptr));
		inline auto &operator=(const MapPointer &m) const reflect_to_self(std::swap(m.ptr, ptr));
	};
	inline MapPointer MapView(MapAccess acs = MapAccess::All, uint64_t offset = 0, size_t size = 0) assertl_reflect_as(auto p = MapViewOfFile(self, acs.yield(), (DWORD)(offset >> 32), (DWORD)offset, size), p);

	inline DWORD Read(LPVOID lpBuffer, DWORD dwNumberOfBytesToRead) assertl_reflect_as(ReadFile(self, lpBuffer, dwNumberOfBytesToRead, &dwNumberOfBytesToRead, O), dwNumberOfBytesToRead);
	inline DWORD Write(LPCVOID lpBuffer, DWORD dwNumberOfBytesToRead) assertl_reflect_as(WriteFile(self, lpBuffer, dwNumberOfBytesToRead, &dwNumberOfBytesToRead, O), dwNumberOfBytesToRead);

	inline void Flush() assertl_reflect_as(FlushFileBuffers(self));

#pragma region Properties
public: // Property - Size
	/* W */ inline uint64_t Size() const assertl_reflect_to(uint64_t size = 0, GetFileSizeEx(self, (PLARGE_INTEGER)&size), size);
public: // Property - Time
	/* W */ inline FileTimes Times() const assertl_reflect_to(FileTimes ts, GetFileTime(self, &ts.Creation, &ts.LastAccess, &ts.LastWrite), ts);
public: // Property - Type
	/* W */ inline FileTypes Type() const nt_assertl_reflect_to(auto type = GetFileType(self), reuse_as<FileTypes>(type));
#pragma endregion

};
using CFile = RefAs<File>;
#pragma endregion

#pragma region Comm
enum_class(Parities, BYTE,
	No        = NOPARITY,
	Odd       = ODDPARITY,
	Even      = EVENPARITY,
	Mark      = MARKPARITY,
	Space     = SPACEPARITY);
enum_class(StopBits, BYTE,
	One  = ONESTOPBIT,
	One5 = ONE5STOPBITS,
	Two  = TWOSTOPBITS);
enum_class(DtrCtrl, DWORD,
	Disable   = DTR_CONTROL_DISABLE,
	Enable    = DTR_CONTROL_ENABLE,
	HandShake = DTR_CONTROL_HANDSHAKE);
enum_class(RtsCtrl, DWORD,
	Disable   = RTS_CONTROL_DISABLE,
	Enable    = RTS_CONTROL_ENABLE,
	HandShake = RTS_CONTROL_HANDSHAKE,
	Toggle    = RTS_CONTROL_TOGGLE);
enum_flags(CommPurge, DWORD,
	TxAbort   = PURGE_TXABORT,
	RxAbort   = PURGE_RXABORT,
	TxClear   = PURGE_TXCLEAR,
	RxClear   = PURGE_RXCLEAR,
	All       = PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
enum_flags(ModemStatus, DWORD,
	CTS       = MS_CTS_ON,
	DSR       = MS_DSR_ON,
	Ring      = MS_RING_ON,
	RLSD      = MS_RLSD_ON);
enum_flags(CommEvent, DWORD,
	RxChar    = EV_RXCHAR,
	RxFlag    = EV_RXFLAG,
	TxEmpty   = EV_TXEMPTY,
	Cts       = EV_CTS,
	Dsr       = EV_DSR,
	Rlsd      = EV_RLSD,
	Break     = EV_BREAK,
	Err       = EV_ERR,
	Ring      = EV_RING,
	PErr      = EV_PERR,
	Rx80Full  = EV_RX80FULL,
	Event1    = EV_EVENT1,
	Event2    = EV_EVENT2);
enum_class(CommSubTypes, DWORD,
	Unspecified      = PST_UNSPECIFIED,
	RS232            = PST_RS232,
	ParallelPort     = PST_PARALLELPORT,
	RS422            = PST_RS422,
	RS423            = PST_RS423,
	RS449            = PST_RS449,
	Modem            = PST_MODEM,
	Fax              = PST_FAX,
	Scanner          = PST_SCANNER,
	NetworkBridge    = PST_NETWORK_BRIDGE,
	Lat              = PST_LAT,
	TcpIpTelnet      = PST_TCPIP_TELNET,
	X25              = PST_X25);
enum_flags(CommCapability, DWORD,
	DTRDSR        = PCF_DTRDSR,
	RTSCTS        = PCF_RTSCTS,
	RLSD          = PCF_RLSD,
	ParityCheck   = PCF_PARITY_CHECK,
	XONXOFF       = PCF_XONXOFF,
	SetXChar      = PCF_SETXCHAR,
	Totaltimeouts = PCF_TOTALTIMEOUTS,
	IntTimeouts   = PCF_INTTIMEOUTS,
	SpecialChars  = PCF_SPECIALCHARS,
	_16BitMode    = PCF_16BITMODE);
enum_flags(CommBaud, DWORD,
	_075             = BAUD_075,
	_110             = BAUD_110,
	_134_5           = BAUD_134_5,
	_150             = BAUD_150,
	_300             = BAUD_300,
	_600             = BAUD_600,
	_1200            = BAUD_1200,
	_1800            = BAUD_1800,
	_2400            = BAUD_2400,
	_4800            = BAUD_4800,
	_7200            = BAUD_7200,
	_9600            = BAUD_9600,
	_14400           = BAUD_14400,
	_19200           = BAUD_19200,
	_38400           = BAUD_38400,
	_56K             = BAUD_56K,
	_128K            = BAUD_128K,
	_115200          = BAUD_115200,
	_57600           = BAUD_57600,
	_User            = BAUD_USER);
enum_flags(CommDataBit, WORD,
	_5               = DATABITS_5,
	_6               = DATABITS_6,
	_7               = DATABITS_7,
	_8               = DATABITS_8,
	_16              = DATABITS_16,
	_16X             = DATABITS_16X);
enum_flags(CommStopParity, WORD,
	_1               = STOPBITS_10,
	_15              = STOPBITS_15,
	_2               = STOPBITS_20,
	None             = PARITY_NONE,
	Odd              = PARITY_ODD,
	Even             = PARITY_EVEN,
	Mark             = PARITY_MARK,
	Space            = PARITY_SPACE);
enum_flags(CommParam, DWORD,
	Parity          = SP_PARITY,
	Baud            = SP_BAUD,
	DataBits        = SP_DATABITS,
	StopBits        = SP_STOPBITS,
	Handshaking     = SP_HANDSHAKING,
	ParityCheck     = SP_PARITY_CHECK,
	RLSD            = SP_RLSD);
struct CommStates : public RefStruct<DCB> {
	using super = RefStruct<DCB>;
public:
	CommStates() reflect_to(self->DCBlength = sizeof(DCB); self->fBinary = 1);
	CommStates(const DCB &dcb) : super(dcb) {}
	CommStates(LPCSTR lpDef) : CommStates() assertl_reflect_as(BuildCommDCBA(lpDef, this));
	CommStates(LPCWSTR lpDef) : CommStates() assertl_reflect_as(BuildCommDCBW(lpDef, this));
public: // Property - BaudRate
	/* W */ inline auto&BaudRate(DWORD baudrate) reflect_to_self(self->BaudRate = baudrate);
	/* R */ inline auto BaudRate() const reflect_as(self->BaudRate);
public: // Property - ByteSize
	/* W */ inline auto&ByteSize(BYTE bytesize) reflect_to_self(self->ByteSize = bytesize);
	/* R */ inline auto ByteSize() const reflect_as(self->ByteSize);
public: // Property - Parity
	/* W */ inline auto&Parity(Parities parity) reflect_to_self(self->Parity = parity.yield(), self->fParity = 1);
	/* R */ inline auto Parity() const reflect_as(reuse_as<Parities>(self->Parity));
public: // Property - StopBit
	/* W */ inline auto&StopBit(WX::StopBits stopbits) reflect_to_self(self->StopBits = stopbits.yield());
	/* R */ inline auto StopBit() const reflect_as(reuse_as<WX::StopBits>(self->StopBits));
public: // Property - OutxCtsFlow
	/* W */ inline auto&OutxCtsFlow(bool bOutxCtsFlow) reflect_to_self(self->fOutxCtsFlow = bOutxCtsFlow);
	/* R */ inline bool OutxCtsFlow() const reflect_as(self->fOutxCtsFlow);
public: // Property - OutxDsrFlow
	/* W */ inline auto&OutxDsrFlow(bool bOutxDsrFlow) reflect_to_self(self->fOutxDsrFlow = bOutxDsrFlow);
	/* R */ inline bool OutxDsrFlow() const reflect_as(self->fOutxDsrFlow);
public: // Property - DtrControl
	/* W */ inline auto&DtrControl(DtrCtrl ctl) reflect_to_self(self->fDtrControl = ctl.yield());
	/* R */ inline auto DtrControl() const reflect_as(reuse_as<DtrCtrl>(self->fDtrControl));
public: // Property - RtsControl
	/* W */ inline auto&RtsControl(RtsCtrl ctl) reflect_to_self(self->fRtsControl = ctl.yield());
	/* R */ inline auto RtsControl() const reflect_as(reuse_as<RtsCtrl>(self->fRtsControl));
public: // Property - DsrSensitivity
	/* W */ inline auto&DsrSensitivity(bool bDsrSensitivity) reflect_to_self(self->fDsrSensitivity = bDsrSensitivity);
	/* R */ inline bool DsrSensitivity() const reflect_as(self->fDsrSensitivity);
public: // Property - TXContinueOnXoff
	/* W */ inline auto&TXContinueOnXoff(bool bTXContinueOnXoff) reflect_to_self(self->fTXContinueOnXoff = bTXContinueOnXoff);
	/* R */ inline bool TXContinueOnXoff() const reflect_as(self->fTXContinueOnXoff);
public: // Property - OutX
	/* W */ inline auto&OutX(bool bOutX) reflect_to_self(self->fOutX = bOutX);
	/* R */ inline bool OutX() const reflect_as(self->fOutX);
public: // Property - InX
	/* W */ inline auto&InX(bool bInX) reflect_to_self(self->fInX = bInX);
	/* R */ inline bool InX() const reflect_as(self->fInX);
public: // Property - Null
	/* W */ inline auto&Null(bool bNull) reflect_to_self(self->fNull = bNull);
	/* R */ inline bool Null() const reflect_as(self->fNull);
public: // Property - AbortOnError
	/* W */ inline auto&AbortOnError(bool bAbortCatch) reflect_to_self(self->fAbortOnError = bAbortCatch);
	/* R */ inline bool AbortOnError() const reflect_as(self->fAbortOnError);
public: // Property - XonLim
	/* W */ inline auto&XonLim(WORD xonlim) reflect_to_self(self->XonLim = xonlim);
	/* R */ inline auto XonLim() const reflect_as(self->XonLim);
public: // Property - XoffLim
	/* W */ inline auto&XoffLim(WORD xofflim) reflect_to_self(self->XoffLim = xofflim);
	/* R */ inline auto XoffLim() const reflect_as(self->XoffLim);
public: // Property - XonChar
	/* W */ inline auto&XonChar(char xonchar) reflect_to_self(self->XonChar = xonchar);
	/* R */ inline char XonChar() const reflect_as(self->XonChar);
public: // Property - XoffChar
	/* W */ inline auto&XoffChar(char xoffchar) reflect_to_self(self->XoffChar = xoffchar);
	/* R */ inline char XoffChar() const reflect_as(self->XoffChar);
public: // Property - ErrorChar
	/* W */ inline auto&ErrorChar(char errorchar) reflect_to_self(self->ErrorChar = errorchar);
	/* R */ inline char ErrorChar() const reflect_as(self->ErrorChar);
public: // Property - EofChar
	/* W */ inline auto&EofChar(char eofchar) reflect_to_self(self->EofChar = eofchar);
	/* R */ inline char EofChar() const reflect_as(self->EofChar);
public: // Property - EvtChar
	/* W */ inline auto&EvtChar(char evtchar) reflect_to_self(self->EvtChar = evtchar);
	/* R */ inline char EvtChar() const reflect_as(self->EvtChar);
};
struct CommProps : public RefStruct<COMMPROP> {
	using super = RefStruct<COMMPROP>;
public:
	CommProps() reflect_to(self->wPacketLength = sizeof(COMMPROP); self->dwProvSpec1 = COMMPROP_INITIALIZED);
	CommProps(const COMMPROP &cp) : super(cp) {}
public: // Property - PacketVersion
	/* W */ inline auto&PacketVersion(WORD wVersion) reflect_to_self(self->wPacketVersion = wVersion);
	/* R */ inline WORD PacketVersion() const reflect_as(self->wPacketVersion);
public: // Property - ServiceMask
public: // Property - MaxTxQueue
	/* R */ inline auto MaxTxQueue() const reflect_as(self->dwMaxTxQueue);
public: // Property - MaxRxQueue
	/* R */ inline auto MaxRxQueue() const reflect_as(self->dwMaxRxQueue);
public: // Property - MaxBaud
	/* R */ inline auto MaxBaud() const reflect_as(reuse_as<CommBaud>(self->dwMaxBaud));
public: // Property - ProviderSubType
	/* R */ inline auto ProviderSubType() const reflect_as(reuse_as<CommSubTypes>(self->dwProvSubType));
public: // Property - ProviderCapabilities
	/* R */ inline auto ProviderCapabilities() const reflect_as(reuse_as<CommCapability>(self->dwProvCapabilities));
public: // Property - SettableParams
	/* R */ inline auto SettableParams() const reflect_as(reuse_as<CommParam>(self->dwSettableParams));
public: // Property - SettableBaud
	/* R */ inline auto SettableBaud() const reflect_as(reuse_as<CommBaud>(self->dwSettableBaud));
public: // Property - SettableData
	/* R */ inline auto SettableData() const reflect_as(reuse_as<CommDataBit>(self->wSettableData));
public: // Property - SettableStopParity
	/* R */ inline auto SettableStopParity() const reflect_as(reuse_as<CommStopParity>(self->wSettableStopParity));
public: // Property - CurrentTxQueue
	/* R */ inline auto CurrentTxQueue() const reflect_as(self->dwCurrentTxQueue);
public: // Property - CurrentRxQueue
	/* R */ inline auto CurrentRxQueue() const reflect_as(self->dwCurrentRxQueue);
	//DWORD dwProvSpec1;
	//DWORD dwProvSpec2;
	//WCHAR wcProvChar[1];
};
class CommConfig : public RefStruct<COMMCONFIG> {
	HeapPointer<COMMCONFIG> lpCC;
public:
	CommConfig() {}
public: // Property - ProviderSubType
	/* W */ inline auto&ProviderSubType(CommSubTypes subType) reflect_to_self(lpCC->dwProviderSubType = subType.yield());
	/* R */ inline auto ProviderSubType() const reflect_as(reuse_as<CommSubTypes>(lpCC->dwProviderSubType));
//public: // Property - ProviderName
//	/* W */ inline auto &ProviderName(LPCTSTR lpName) reflect_to_self(lstrcpyn(self->szProvider, lpName, sizeof(self->szProvider) / sizeof(TCHAR)));
//	/* R */ inline String ProviderName() const reflect_as(String(self->szProvider));
};
struct CommTimeouts : public RefStruct<COMMTIMEOUTS> {
	using super = RefStruct<COMMTIMEOUTS>;
public:
	CommTimeouts() reflect_to(self->ReadIntervalTimeout = MAXDWORD);
	CommTimeouts(const COMMTIMEOUTS &ct) : super(ct) {}
public: // Property - ReadInterval
	/* W */ inline auto &ReadInterval(DWORD dwMillisecond) reflect_to_self(self->ReadIntervalTimeout = dwMillisecond);
	/* R */ inline DWORD ReadInterval() const reflect_as(self->ReadIntervalTimeout);
public: // Property - ReadTotalConst
	/* W */ inline auto &ReadTotalConst(DWORD dwMillisecond) reflect_to_self(self->ReadTotalTimeoutConstant = dwMillisecond);
	/* R */ inline DWORD ReadTotalConst() const reflect_as(self->ReadTotalTimeoutConstant);
public: // Property - ReadTotalMult
	/* W */ inline auto &ReadTotalMult(DWORD dwMillisecond) reflect_to_self(self->ReadTotalTimeoutMultiplier = dwMillisecond);
	/* R */ inline DWORD ReadTotalMult() const reflect_as(self->ReadTotalTimeoutMultiplier);
public: // Property - WriteTotalConst
	/* W */ inline auto &WriteTotalConst(DWORD dwMillisecond) reflect_to_self(self->WriteTotalTimeoutConstant = dwMillisecond);
	/* R */ inline DWORD WriteTotalConst() const reflect_as(self->WriteTotalTimeoutConstant);
public: // Property - WriteTotalMult
	/* W */ inline auto &WriteTotalMult(DWORD dwMillisecond) reflect_to_self(self->WriteTotalTimeoutMultiplier = dwMillisecond);
	/* R */ inline DWORD WriteTotalMult() const reflect_as(self->WriteTotalTimeoutMultiplier);
};
class Comm : public File {
public:
	using super = File;
protected:
	Comm(HANDLE hComm) : super(hComm) {}
public:
	Comm() {}
public:
	inline void ClearBreak() reflect_to(WX::ClearCommBreak(self));
//	inline void ClearErrors(CommClear cc = CommClear::All) reflect_to(WX::ClearCommError(self, &cc.yield(), O));
	inline void Setup(DWORD dwInQueue, DWORD dwOutQueue) reflect_to(WX::SetupComm(self, dwInQueue, dwOutQueue));
	inline void Purge(CommPurge cp = CommPurge::All) reflect_to(WX::PurgeComm(self, cp.yield()));
	inline void Transmit(char ch)  reflect_to(WX::TransmitCommChar(self, ch));
//	inline void WaitEvent(CommEvent ce = CommEvent::RxChar) reflect_to(WX::WaitCommEvent(self, &ce.yield(), O));
	static inline Comm Open(ULONG uPortNumber, FileAccess desiredAccess, DWORD dwFlagsAndAttributes = 0)
		reflect_as(WX::OpenCommPort(uPortNumber, desiredAccess.yield(), dwFlagsAndAttributes));
#pragma region Properties
public: // Property - Mask
	/* W */ inline auto&Mask(CommEvent ev) reflect_to_self(WX::SetCommMask(self, ev.yield()));
	/* R */ inline auto Mask() const reflect_to(DWORD dwMask; WX::GetCommMask(self, &dwMask), reuse_as<CommEvent>(dwMask));
public: // Property - ModemStatus
	/* R */ inline auto ModemStatus() const reflect_to(DWORD dwModemStatus; WX::GetCommModemStatus(self, &dwModemStatus), reuse_as<WX::ModemStatus>(dwModemStatus));
public: // Property - States
	/* W */ inline auto&States(CommStates states) reflect_to_self(WX::SetCommState(self, &states));
	/* R */ inline auto States() const reflect_to(CommStates states; WX::GetCommState(self, &states), states);
public: // Property - Timeout
	/* W */ inline auto&Timeout(COMMTIMEOUTS ct) reflect_to_self(WX::SetCommTimeouts(self, &ct));
	/* R */ inline auto Timeout() const reflect_to(CommTimeouts ct; WX::GetCommTimeouts(self, &ct), ct);
public: // Property - Config
	///* W */ inline auto &Config(CommConfig cc) reflect_to_self(WX::SetCommConfig(self, &cc, cc.dwSize));
	///* R */ inline auto Config() const reflect_to(CommConfig cc; DWORD size = cc.dwSize; WX::GetCommConfig(self, &cc, &size), cc);
public: // Property - Props
	/* R */ inline auto Props() const reflect_to(CommProps cp; WX::GetCommProperties(self, &cp), cp);
#pragma endregion
};
#pragma endregion

}
