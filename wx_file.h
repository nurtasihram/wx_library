#pragma once

#include "wx_resource.h"
#include "wx_security.h"

namespace WX {

#pragma region File
enum_flags(FileAccess, HandleAccess,
	enum_default No      = 0,
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
	enum_complex GenericRead    = FILE_GENERIC_READ,
	enum_complex GenericWrite   = FILE_GENERIC_WRITE,
	enum_complex GenericExecute = FILE_GENERIC_EXECUTE,
	enum_complex All            = FILE_ALL_ACCESS);
enum_flags(FileAttribute, DWORD,
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
	enum_default No = 0,
	Read   = FILE_SHARE_READ,
	Write  = FILE_SHARE_WRITE,
	Delete = FILE_SHARE_DELETE);
enum_class(FileTypes, DWORD, 
	enum_default Unknown = FILE_TYPE_UNKNOWN,
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
	enum_complex ReadWrite = FILE_MAP_WRITE | FILE_MAP_READ);
struct FileTimes { FileTime Creation, LastAccess, LastWrite; };
struct FileBaseInfo : protected FILE_BASIC_INFO {
	FileBaseInfo() {}
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
public:
	inline FILE_BASIC_INFO *operator &() reflect_as(this);
	inline const FILE_BASIC_INFO *operator &() const reflect_as(this);
};
class BaseOf_Handle(File) {
public:
	using super = HandleBase<File>;
	using Access = FileAccess;
	using Shares = FileShares;
	using Attributes = FileAttribute;
	using Flag = FileFlag;
	using Types = FileTypes;
protected:
	File(HANDLE h) : super(h) {}
	File(const File &f) : super(f) {}
public:
	File() {}
	File(Null) {}
	File(File &f) : super(f) {}
	File(File &&f) : super(f) {}

	using super::operator=;

	class CreateStruct {
		LPCTSTR lpFileName;
		Access dwDesiredAccess = Access::No;
		Shares dwShareMode = Shares::No;
		LPSECURITY_ATTRIBUTES lpAttributes = O;
		DWORD dwCreationDisposition = 0;
		DWORD dwFlagsAndAttributes = 0;
		HANDLE hTemplateFile = O;
	public:
		CreateStruct(LPCTSTR lpFileName) : lpFileName(lpFileName) {}
	public:
		inline auto &Accesses(Access dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Share(Shares dwShareMode) reflect_to_self(this->dwShareMode = dwShareMode);
		inline auto &Security(const SecAttr &SA) reflect_to_self(this->lpAttributes = &SA);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpAttributes) reflect_to_self(this->lpAttributes = lpAttributes);
		inline auto &Template(HANDLE hTemplateFile) reflect_to_self(this->hTemplateFile = hTemplateFile);
		inline auto &Attributes(Attributes dwAttributes) reflect_to_self(this->dwFlagsAndAttributes = dwAttributes.yield());
		inline auto &Flags(Flag dwFlags) reflect_to_self(this->dwFlagsAndAttributes = dwFlags.yield());
	public:
		inline auto &CreateNew() reflect_to_self(this->dwCreationDisposition = CREATE_NEW);
		inline auto &CreateAlways() reflect_to_self(this->dwCreationDisposition = CREATE_ALWAYS);
		inline auto &OpenExisting() reflect_to_self(this->dwCreationDisposition = OPEN_EXISTING);
		inline auto &OpenAlways() reflect_to_self(this->dwCreationDisposition = OPEN_ALWAYS);
		inline auto &TruncateExisting() reflect_to_self(this->dwCreationDisposition = TRUNCATE_EXISTING);
	public:
		inline operator File() assertl_reflect_as(auto h = CreateFile(lpFileName, dwDesiredAccess.yield(), dwShareMode.yield(), lpAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile), h);
	};
	static inline CreateStruct Create(LPCTSTR lpFileName) reflect_as(lpFileName);

	class MappingCreateStruct {
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
		inline auto &Security(const SecAttr &SA) reflect_to_self(this->lpAttributes = &SA);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpAttributes) reflect_to_self(this->lpAttributes = lpAttributes);
		inline auto &Protect(PageProtect pa) reflect_to_self(this->flProtect = pa.yield());
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator File() assertl_reflect_as(auto h = CreateFileMapping(hFile, lpAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName), h);
	};
	inline MappingCreateStruct CreateMapping(LPCTSTR lpName, uint64_t size) reflect_as({ self, lpName, size });
	inline MappingCreateStruct CreateMapping(uint64_t size) reflect_as({ self, O, size });

	class MappingOpenStruct {
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
		inline operator File() assertl_reflect_as(auto h = OpenFileMapping(dwDesiredAccess, bInheritHandle, lpName), h);
	};
	inline MappingOpenStruct OpenMapping(LPCTSTR lpName) reflect_as(lpName);

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

	static inline bool Delete(LPCTSTR lpFileName) reflect_as(DeleteFile(lpFileName));
	static inline bool Copy(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, bool bFailIfExists = false) reflect_as(CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists));

	inline DWORD Read(LPVOID lpBuffer, DWORD dwNumberOfBytesToRead) assertl_reflect_as(ReadFile(self, lpBuffer, dwNumberOfBytesToRead, &dwNumberOfBytesToRead, O), dwNumberOfBytesToRead);
	inline DWORD Write(LPCVOID lpBuffer, DWORD dwNumberOfBytesToRead) assertl_reflect_as(WriteFile(self, lpBuffer, dwNumberOfBytesToRead, &dwNumberOfBytesToRead, O), dwNumberOfBytesToRead);
	
	inline void Flush() assertl_reflect_as(FlushFileBuffers(self));

#pragma region Properties
public: // Property - Size
	/* W */ inline uint64_t Size() const assertl_reflect_to(uint64_t size = 0, GetFileSizeEx(self, (PLARGE_INTEGER)&size), size);
public: // Property - Time
	/* W */ inline FileTimes Times() const assertl_reflect_to(FileTimes ts, GetFileTime(self, &ts.Creation, &ts.LastAccess, &ts.LastWrite), ts);
public: // Property - Type
	/* W */ inline Types Type() const nt_assertl_reflect_to(auto type = GetFileType(self), reuse_as<Types>(type));
#pragma endregion

};
using CFile = RefAs<File>;
#pragma endregion

#pragma region Comm
enum_class(Parities, BYTE,
	enum_default No = NOPARITY,
	Odd       = ODDPARITY,
	Even      = EVENPARITY,
	Mark      = MARKPARITY,
	Space     = SPACEPARITY);
enum_class(StopBit, BYTE,
	enum_default One = ONESTOPBIT,
	One5      = ONE5STOPBITS,
	Two       = TWOSTOPBITS);
enum_class(DtrCtrl, DWORD,
	enum_default Disable = DTR_CONTROL_DISABLE,
	Enable    = DTR_CONTROL_ENABLE,
	HandShake = DTR_CONTROL_HANDSHAKE);
enum_class(RtsCtrl, DWORD,
	enum_default Disable = RTS_CONTROL_DISABLE,
	Enable    = RTS_CONTROL_ENABLE,
	HandShake = RTS_CONTROL_HANDSHAKE,
	Toggle    = RTS_CONTROL_TOGGLE);
enum_class(CommClear, DWORD,
	TxAbort   = PURGE_TXABORT,
	RxAbort   = PURGE_RXABORT,
	TxClear   = PURGE_TXCLEAR,
	RxClear   = PURGE_RXCLEAR,
	enum_complex All = PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
enum_class(CommEvent, DWORD,
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
struct CommStates : protected DCB {
	CommStates() : DCB{ 0 } reflect_to(DCBlength = sizeof(DCB); fBinary = 1);
	CommStates(const DCB &dcb) : DCB{ dcb } {}
	CommStates(LPCTSTR lpDef) : DCB{ 0 } assertl_reflect_as(BuildCommDCB(lpDef, this));
public: // Property - BaudRate
	/* W */ inline auto &BaudRate(DWORD baudrate) reflect_to_self(DCB::BaudRate = baudrate);
	/* R */ inline DWORD BaudRate() const reflect_as(DCB::BaudRate);
public: // Property - ByteSize
	/* W */ inline auto &ByteSize(BYTE bytesize) reflect_to_self(DCB::ByteSize = bytesize);
	/* R */ inline BYTE  ByteSize() const reflect_as(DCB::ByteSize);
public: // Property - Parity
	/* W */ inline auto    &Parity(Parities parity) reflect_to_self(DCB::Parity = parity.yield(), DCB::fParity = 1);
	/* R */ inline Parities Parity() const reflect_as(reuse_as<Parities>(DCB::Parity));
public: // Property - StopBits
	/* W */ inline auto   &StopBits(StopBit stopbits) reflect_to_self(DCB::StopBits = stopbits.yield());
	/* R */ inline StopBit StopBits() const reflect_as(reuse_as<StopBit>(DCB::StopBits));
public: // Property - OutxCtsFlow
	/* W */ inline auto &OutxCtsFlow(bool bOutxCtsFlow) reflect_to_self(DCB::fOutxCtsFlow = bOutxCtsFlow);
	/* R */ inline bool  OutxCtsFlow() const reflect_as(DCB::fOutxCtsFlow);
public: // Property - OutxDsrFlow
	/* W */ inline auto &OutxDsrFlow(bool bOutxDsrFlow) reflect_to_self(DCB::fOutxDsrFlow = bOutxDsrFlow);
	/* R */ inline bool  OutxDsrFlow() const reflect_as(DCB::fOutxDsrFlow);
public: // Property - DtrControl
	/* W */ inline auto   &DtrControl(DtrCtrl ctl) reflect_to_self(DCB::fDtrControl = ctl.yield());
	/* R */ inline DtrCtrl DtrControl() const reflect_as(reuse_as<DtrCtrl>(DCB::fDtrControl));
public: // Property - RtsControl
	/* W */ inline auto   &RtsControl(RtsCtrl ctl) reflect_to_self(DCB::fRtsControl = ctl.yield());
	/* R */ inline RtsCtrl RtsControl() const reflect_as(reuse_as<RtsCtrl>(DCB::fRtsControl));
public: // Property - DsrSensitivity
	/* W */ inline auto &DsrSensitivity(bool bDsrSensitivity) reflect_to_self(DCB::fDsrSensitivity = bDsrSensitivity);
	/* R */ inline bool  DsrSensitivity() const reflect_as(DCB::fDsrSensitivity);
public: // Property - TXContinueOnXoff
	/* W */ inline auto &TXContinueOnXoff(bool bTXContinueOnXoff) reflect_to_self(DCB::fTXContinueOnXoff = bTXContinueOnXoff);
	/* R */ inline bool  TXContinueOnXoff() const reflect_as(DCB::fTXContinueOnXoff);
public: // Property - OutX
	/* W */ inline auto &OutX(bool bOutX) reflect_to_self(DCB::fOutX = bOutX);
	/* R */ inline bool  OutX() const reflect_as(DCB::fOutX);
public: // Property - InX
	/* W */ inline auto &InX(bool bInX) reflect_to_self(DCB::fInX = bInX);
	/* R */ inline bool  InX() const reflect_as(DCB::fInX);
public: // Property - Null
	/* W */ inline auto &Null(bool bNull) reflect_to_self(DCB::fNull = bNull);
	/* R */ inline bool  Null() const reflect_as(DCB::fNull);
public: // Property - AbortOnError
	/* W */ inline auto &AbortOnError(bool bAbortCatch) reflect_to_self(DCB::fAbortOnError = bAbortCatch);
	/* R */ inline bool  AbortOnError() const reflect_as(DCB::fAbortOnError);
public: // Property - XonLim
	/* W */ inline auto &XonLim(WORD xonlim) reflect_to_self(DCB::XonLim = xonlim);
	/* R */ inline WORD  XonLim() const reflect_as(DCB::XonLim);
public: // Property - XoffLim
	/* W */ inline auto &XoffLim(WORD xofflim) reflect_to_self(DCB::XoffLim = xofflim);
	/* R */ inline WORD  XoffLim() const reflect_as(DCB::XoffLim);
public: // Property - XonChar
	/* W */ inline auto &XonChar(char xonchar) reflect_to_self(DCB::XonChar = xonchar);
	/* R */ inline char  XonChar() const reflect_as(DCB::XonChar);
public: // Property - XoffChar
	/* W */ inline auto &XoffChar(char xoffchar) reflect_to_self(DCB::XoffChar = xoffchar);
	/* R */ inline char  XoffChar() const reflect_as(DCB::XoffChar);
public: // Property - ErrorChar
	/* W */ inline auto &ErrorChar(char errorchar) reflect_to_self(DCB::ErrorChar = errorchar);
	/* R */ inline char  ErrorChar() const reflect_as(DCB::ErrorChar);
public: // Property - EofChar
	/* W */ inline auto &EofChar(char eofchar) reflect_to_self(DCB::EofChar = eofchar);
	/* R */ inline char  EofChar() const reflect_as(DCB::EofChar);
public: // Property - EvtChar
	/* W */ inline auto &EvtChar(char evtchar) reflect_to_self(DCB::EvtChar = evtchar);
	/* R */ inline char  EvtChar() const reflect_as(DCB::EvtChar);
public:
	inline DCB *operator &() reflect_as(this);
	inline const DCB *operator &() const reflect_as(this);
};
struct CommTimeout : protected COMMTIMEOUTS {
	CommTimeout() : COMMTIMEOUTS{ 0 } {}
public: // Property - ReadInterval
	/* W */ inline auto &ReadInterval(DWORD ms) reflect_as(this->ReadIntervalTimeout = ms);
	/* R */ inline DWORD ReadInterval() const reflect_as(this->ReadIntervalTimeout);
public: // Property - ReadTotal
	struct Time { DWORD msMultiplier, msConstant; };
	/* W */ inline auto &ReadTotal(Time t) reflect_to_self(this->ReadTotalTimeoutMultiplier = t.msMultiplier, this->ReadTotalTimeoutConstant = t.msConstant);
	/* R */ inline Time  ReadTotal() const reflect_as({ this->ReadTotalTimeoutMultiplier, this->ReadTotalTimeoutConstant });
public: // Property - WriteTotal
	/* W */ inline auto &WriteTotal(Time t) reflect_to_self(this->WriteTotalTimeoutMultiplier = t.msMultiplier, this->WriteTotalTimeoutConstant = t.msConstant);
	/* R */ inline Time  WriteTotal() const reflect_as({ this->WriteTotalTimeoutMultiplier, this->WriteTotalTimeoutConstant });
public:
	inline COMMTIMEOUTS *operator&() reflect_as(this);
	inline const COMMTIMEOUTS *operator&() const reflect_as(this);
};
class Comm {
	File fCom;
public:
	using States = CommStates;
	using Timeout = CommTimeout;
	using Event = CommEvent;
protected:
public:
	Comm() {}
	Comm(File fCom) : fCom(fCom) {}
	Comm(File::CreateStruct &fc) : fCom(fc) {}
	Comm(ULONG id) : fCom(File::Create(Cats(_T("\\\\.\\COM"), id))
						  .OpenExisting()
						  .Accesses(FileAccess::GenericRead | FileAccess::GenericWrite)
						  .Flags(FileFlag::Overlapped)
						  .Attributes(FileAttribute::Normal)) {}

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3) // NTDDI_WIN10_RS4NTDDI_WIN10_RS4

	static inline std::vector<ULONG> Ports() {
		ULONG count = 0;
		GetCommPorts(O, 0, &count);
		if (!count) return {};
		std::vector<ULONG> ports(count);
		assertl(GetCommPorts(ports.data(), count, &count) == ERROR_SUCCESS);
		return ports;
	}

#else



#endif

	inline auto &Purge(CommClear clr) assertl_reflect_as_self(PurgeComm(fCom, clr.yield()));
	inline auto &Setup(DWORD dwInQueue, DWORD dwOutQueue) assertl_reflect_as_self(SetupComm(fCom, dwInQueue, dwOutQueue));

	inline auto &TransmitChar(char cChar) assertl_reflect_as_self(TransmitCommChar(fCom, cChar));
	inline Event WaitEvents(LPOVERLAPPED lpOverlapped = O) assertl_reflect_to(DWORD evt, WaitCommEvent(fCom, &evt, lpOverlapped), reuse_as<Event>(evt));

#pragma region Properties
public: // Property - State
	/* W */ inline auto  &State(States status) assertl_reflect_as_self(SetCommState(fCom, &status));
	/* R */ inline States State() const assertl_reflect_to(States dcb, GetCommState(fCom, &dcb), dcb);
public: // Property - Timeouts
	/* W */ inline auto   &Timeouts(Timeout to) assertl_reflect_as_self(SetCommTimeouts(fCom, &to));
	/* R */ inline Timeout Timeouts() const assertl_reflect_to(Timeout to, GetCommTimeouts(fCom, &to), to);
public: // Property - Events
	/* W */ inline auto &Events(Event evt) assertl_reflect_as_self(SetCommMask(fCom, evt.yield()));
	/* R */ inline Event Events() const assertl_reflect_to(DWORD evt, GetCommMask(fCom, &evt), reuse_as<Event>(evt));
public: // Property - Config
#pragma endregion

};
#pragma endregion

}
