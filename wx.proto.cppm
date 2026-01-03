module;

#include <Windows.h>

#include "wx__nt.h"

#include "wx"

export module wx.proto;

export namespace WX {

#pragma region WinBase.h
// GlobalAlloc
// GlobalReAlloc
// GlobalSize
// GlobalUnlock
// GlobalLock
// GlobalFlags
// GlobalHandle
// GlobalFree
// GlobalMemoryStatus
// LocalAlloc
// LocalReAlloc
// LocalLock
// LocalHandle
// LocalUnlock
// LocalSize
// LocalFlags
// LocalFree
// GetBinaryType
inline void GetBinaryType(LPCSTR lpApplicationName, LPDWORD lpBinaryType)
	assertl_reflect_as(::GetBinaryTypeA(lpApplicationName, lpBinaryType));
inline void GetBinaryType(LPCWSTR lpApplicationName, LPDWORD lpBinaryType)
	assertl_reflect_as(::GetBinaryTypeW(lpApplicationName, lpBinaryType));
// GetLongPathNameTransacted
inline DWORD GetLongPathNameTransacted(LPCSTR lpszShortPath, LPSTR lpszLongPath, DWORD cchBuffer, HANDLE hTransaction)
	assertl_reflect_as(auto res = ::GetLongPathNameTransactedA(lpszShortPath, lpszLongPath, cchBuffer, hTransaction), res);
inline DWORD GetLongPathNameTransacted(LPCWSTR lpszShortPath, LPWSTR lpszLongPath, DWORD cchBuffer, HANDLE hTransaction)
	assertl_reflect_as(auto res = ::GetLongPathNameTransactedW(lpszShortPath, lpszLongPath, cchBuffer, hTransaction), res);
// GetProcessAffinityMask
// SetProcessAffinityMask
// GetProcessIoCounters
// FatalExit
// SwitchToFiber
// DeleteFiber
// ConvertFiberToThread
// CreateFiberEx
// ConvertThreadToFiberEx
// CreateFiber
// ConvertThreadToFiber
// CreateUmsCompletionList
// DequeueUmsCompletionListItems
// GetUmsCompletionListEvent
// ExecuteUmsThread
// UmsThreadYield
// DeleteUmsCompletionList
// GetCurrentUmsThread
// GetNextUmsListItem
// QueryUmsThreadInformation
// SetUmsThreadInformation
// DeleteUmsThreadContext
// CreateUmsThreadContext
// EnterUmsSchedulingMode
// GetUmsSystemThreadInformation
// SetThreadAffinityMask
// SetProcessDEPPolicy
// GetProcessDEPPolicy
// RequestWakeupLatency
// IsSystemResumeAutomatic
// GetThreadSelectorEntry
// SetThreadExecutionState
// PowerCreateRequest
// PowerSetRequest
// PowerClearRequest
// SetFileCompletionNotificationModes
// Wow64GetThreadSelectorEntry
// DebugSetProcessKillOnExit
// DebugBreakProcess
// PulseEvent
inline void PulseEvent(HANDLE hEvent)
	assertl_reflect_as(::PulseEvent(hEvent));
// GlobalDeleteAtom
inline void GlobalDeleteAtom(ATOM nAtom)
	assertl_reflect_as(::GlobalDeleteAtom(nAtom));
// InitAtomTable
// DeleteAtom
inline void DeleteAtom(ATOM nAtom)
	assertl_reflect_as(::DeleteAtom(nAtom));
// SetHandleCount
// GetDevicePowerState
// SetFileShortName
inline void SetFileShortName(HANDLE hFile, LPCSTR lpShortName)
	assertl_reflect_as(::SetFileShortNameA(hFile, lpShortName));
inline void SetFileShortName(HANDLE hFile, LPCWSTR lpShortName)
	assertl_reflect_as(::SetFileShortNameW(hFile, lpShortName));
// LoadModule
// WinExec
// ClearCommBreak
inline void ClearCommBreak(HANDLE hFile)
	assertl_reflect_as(::ClearCommBreak(hFile));
// ClearCommError
inline void ClearCommError(HANDLE hFile, LPDWORD lpErrors, LPCOMSTAT lpStat)
	assertl_reflect_as(::ClearCommError(hFile, lpErrors, lpStat));
// SetupComm
inline void SetupComm(HANDLE hFile, DWORD dwInQueue, DWORD dwOutQueue)
	assertl_reflect_as(::SetupComm(hFile, dwInQueue, dwOutQueue));
// EscapeCommFunction
inline void EscapeCommFunction(HANDLE hFile, DWORD dwFunc)
	assertl_reflect_as(::EscapeCommFunction(hFile, dwFunc));
// GetCommConfig
inline void GetCommConfig(HANDLE hFile, LPCOMMCONFIG lpCC, LPDWORD lpdwSize)
	assertl_reflect_as(::GetCommConfig(hFile, lpCC, lpdwSize));
// GetCommMask
inline void GetCommMask(HANDLE hFile, LPDWORD lpModemState)
	assertl_reflect_as(::GetCommMask(hFile, lpModemState));
// GetCommProperties
inline void GetCommProperties(HANDLE hFile, LPCOMMPROP lpCommProp)
	assertl_reflect_as(::GetCommProperties(hFile, lpCommProp));
// GetCommModemStatus
inline void GetCommModemStatus(HANDLE hFile, LPDWORD lpModemState)
	assertl_reflect_as(::GetCommModemStatus(hFile, lpModemState));
// GetCommState
inline void GetCommState(HANDLE hFile, LPDCB lpDCB)
	assertl_reflect_as(::GetCommState(hFile, lpDCB));
// GetCommTimeouts
inline void GetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts)
	assertl_reflect_as(::GetCommTimeouts(hFile, lpCommTimeouts));
// PurgeComm
inline void PurgeComm(HANDLE hFile, DWORD dwFlags)
	assertl_reflect_as(::PurgeComm(hFile, dwFlags));
// SetCommBreak
inline void SetCommBreak(HANDLE hFile)
	assertl_reflect_as(::SetCommBreak(hFile));
// SetCommConfig
inline void SetCommConfig(HANDLE hFile, LPCOMMCONFIG lpCC, DWORD dwSize)
	assertl_reflect_as(::SetCommConfig(hFile, lpCC, dwSize));
// SetCommMask
inline void SetCommMask(HANDLE hFile, DWORD dwModemState)
	assertl_reflect_as(::SetCommMask(hFile, dwModemState));
// SetCommState
inline void SetCommState(HANDLE hFile, LPDCB lpDCB)
	assertl_reflect_as(::SetCommState(hFile, lpDCB));
// SetCommTimeouts
inline void SetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts)
	assertl_reflect_as(::SetCommTimeouts(hFile, lpCommTimeouts));
// TransmitCommChar
inline void TransmitCommChar(HANDLE hFile, char cChar)
	assertl_reflect_as(::TransmitCommChar(hFile, cChar));
// WaitCommEvent
inline void WaitCommEvent(HANDLE hFile, LPDWORD lpEvtMask, LPOVERLAPPED lpOverlapped)
	assertl_reflect_as(::WaitCommEvent(hFile, lpEvtMask, lpOverlapped));
#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// OpenCommPort
inline HANDLE OpenCommPort(ULONG uPortNumber, DWORD dwDesiredAccess, DWORD dwFlagsAndAttributes)
	assertl_reflect_as(auto h = ::OpenCommPort(uPortNumber, dwDesiredAccess, dwFlagsAndAttributes); h != INVALID_HANDLE_VALUE, h);
// GetCommPorts
inline void GetCommPorts(PULONG lpPortNumbers, ULONG uPortNumbersCount, PULONG puPortNumbersFound)
	assertl_reflect_as(SUCCEEDED(::GetCommPorts(lpPortNumbers, uPortNumbersCount, puPortNumbersFound)));
#endif
// SetTapePosition
// GetTapePosition
// PrepareTape
// EraseTape
// CreateTapePartition
// WriteTapemark
// GetTapeStatus
// GetTapeParameters
// SetTapeParameters
// GetSystemDEPPolicy
// GetSystemRegistryQuota
// FileTimeToDosDateTime
// DosDateTimeToFileTime
// FormatMessage
inline DWORD FormatMessage(
	DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId,
	LPSTR lpBuffer, DWORD nSize, va_list *Arguments)
	assertl_reflect_as(auto res = ::FormatMessageA(dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments), res);
inline DWORD FormatMessage(
	DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId,
	LPWSTR lpBuffer, DWORD nSize, va_list *Arguments)
	assertl_reflect_as(auto res = ::FormatMessageW(dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments), res);
// CreateMailslot
inline HANDLE CreateMailslot(LPCSTR lpName, DWORD nMaxMessageSize, DWORD lReadTimeout, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(auto h = ::CreateMailslotA(lpName, nMaxMessageSize, lReadTimeout, lpSecurityAttributes), h);
inline HANDLE CreateMailslot(LPCWSTR lpName, DWORD nMaxMessageSize, DWORD lReadTimeout, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(auto h = ::CreateMailslotW(lpName, nMaxMessageSize, lReadTimeout, lpSecurityAttributes), h);
// GetMailslotInfo
// SetMailslotInfo
// EncryptFile
inline void EncryptFile(LPCSTR lpFileName)
	assertl_reflect_as(::EncryptFileA(lpFileName));
inline void EncryptFile(LPCWSTR lpFileName)
	assertl_reflect_as(::EncryptFileW(lpFileName));
// DecryptFile
inline void DecryptFile(LPCSTR lpFileName, DWORD dwReserved)
	assertl_reflect_as(::DecryptFileA(lpFileName, dwReserved));
inline void DecryptFile(LPCWSTR lpFileName, DWORD dwReserved)
	assertl_reflect_as(::DecryptFileW(lpFileName, dwReserved));
// FileEncryptionStatus
inline void FileEncryptionStatus(LPCSTR lpFileName, LPDWORD lpStatus)
	assertl_reflect_as(::FileEncryptionStatusA(lpFileName, lpStatus));
inline void FileEncryptionStatus(LPCWSTR lpFileName, LPDWORD lpStatus)
	assertl_reflect_as(::FileEncryptionStatusW(lpFileName, lpStatus));
// OpenEncryptedFileRaw ///////////////////////////////////////
inline void OpenEncryptedFileRaw(LPCSTR lpFileName, ULONG ulFlags, PVOID *pvContext)
	assertl_reflect_as(SUCCEEDED(::OpenEncryptedFileRawA(lpFileName, ulFlags, pvContext)));
inline void OpenEncryptedFileRaw(LPCWSTR lpFileName, ULONG ulFlags, PVOID *pvContext)
	assertl_reflect_as(SUCCEEDED(::OpenEncryptedFileRawW(lpFileName, ulFlags, pvContext)));
// ReadEncryptedFileRaw
// WriteEncryptedFileRaw
// CloseEncryptedFileRaw
// OpenFile
// IsTextUnicode
// BackupRead
// BackupSeek
// BackupWrite
// CreateFileMapping
inline HANDLE CreateFileMapping(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect,
								DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName)
	assertl_reflect_as(auto h = ::CreateFileMappingA(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName), h);
// from fileapi.h
inline HANDLE CreateFileMapping(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect,
								DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName)
	assertl_reflect_as(auto h = ::CreateFileMappingW(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName), h);
// CreateFileMappingNuma
inline HANDLE CreateFileMapping(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect,
								DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCSTR lpName, DWORD nndPreferred)
	assertl_reflect_as(auto h = ::CreateFileMappingNumaA(hFile, lpFileMappingAttributes, flProtect,
														 dwMaximumSizeHigh, dwMaximumSizeLow, lpName, nndPreferred), h);
// from fileapi.h
inline HANDLE CreateFileMapping(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect,
								DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName, DWORD nndPreferred)
	assertl_reflect_as(auto h = ::CreateFileMappingNumaW(hFile, lpFileMappingAttributes, flProtect,
														 dwMaximumSizeHigh, dwMaximumSizeLow, lpName, nndPreferred), h);
// OpenFileMapping
inline HANDLE OpenFileMapping(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName)
	assertl_reflect_as(auto h = ::OpenFileMappingA(dwDesiredAccess, bInheritHandle, lpName), h);
// from fileapi.h
inline HANDLE OpenFileMapping(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName)
	assertl_reflect_as(auto h = ::OpenFileMappingW(dwDesiredAccess, bInheritHandle, lpName), h);
// GetLogicalDriveStrings
inline DWORD GetLogicalDriveStrings(LPSTR lpBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetLogicalDriveStringsA(nSize, lpBuffer), n);
// from fileapi.h
inline DWORD GetLogicalDriveStrings(LPWSTR lpBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetLogicalDriveStringsW(nSize, lpBuffer), n);
// LoadPackagedLibrary
// QueryFullProcessImageName
inline void QueryFullProcessImageName(HANDLE hProcess, DWORD dwFlags, LPSTR lpExeName, PDWORD lpdwSize)
	assertl_reflect_as(::QueryFullProcessImageNameA(hProcess, dwFlags, lpExeName, lpdwSize));
inline void QueryFullProcessImageName(HANDLE hProcess, DWORD dwFlags, LPWSTR lpExeName, PDWORD lpdwSize)
	assertl_reflect_as(::QueryFullProcessImageNameW(hProcess, dwFlags, lpExeName, lpdwSize));
// GetFirmwareEnvironmentVariable
inline DWORD GetFirmwareEnvironmentVariable(LPCSTR lpName, LPCSTR lpGuid, PVOID pBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetFirmwareEnvironmentVariableA(lpName, lpGuid, pBuffer, nSize), n);
inline DWORD GetFirmwareEnvironmentVariable(LPCWSTR lpName, LPCWSTR lpGuid, PVOID pBuffer, DWORD nSize)
	assertl_reflect_as(auto n = ::GetFirmwareEnvironmentVariableW(lpName, lpGuid, pBuffer, nSize), n);
// GetFirmwareEnvironmentVariableEx
inline DWORD GetFirmwareEnvironmentVariable(LPCSTR lpName, LPCSTR lpGuid, PVOID pBuffer, DWORD nSize, PULONG pulReturnLength)
	assertl_reflect_as(auto n = ::GetFirmwareEnvironmentVariableExA(lpName, lpGuid, pBuffer, nSize, pulReturnLength), n);
inline DWORD GetFirmwareEnvironmentVariable(LPCWSTR lpName, LPCWSTR lpGuid, PVOID pBuffer, DWORD nSize, PULONG pulReturnLength)
	assertl_reflect_as(auto n = ::GetFirmwareEnvironmentVariableExW(lpName, lpGuid, pBuffer, nSize, pulReturnLength), n);
// SetFirmwareEnvironmentVariable
inline void SetFirmwareEnvironmentVariable(LPCSTR lpName, LPCSTR lpGuid, PVOID pBuffer, DWORD nSize)
	assertl_reflect_as(::SetFirmwareEnvironmentVariableA(lpName, lpGuid, pBuffer, nSize));
inline void SetFirmwareEnvironmentVariable(LPCWSTR lpName, LPCWSTR lpGuid, PVOID pBuffer, DWORD nSize)
	assertl_reflect_as(::SetFirmwareEnvironmentVariableW(lpName, lpGuid, pBuffer, nSize));
// SetFirmwareEnvironmentVariableEx
inline void SetFirmwareEnvironmentVariable(LPCSTR lpName, LPCSTR lpGuid, PVOID pBuffer, DWORD nSize, ULONG ulFlags)
	assertl_reflect_as(::SetFirmwareEnvironmentVariableExA(lpName, lpGuid, pBuffer, nSize, ulFlags));
inline void SetFirmwareEnvironmentVariable(LPCWSTR lpName, LPCWSTR lpGuid, PVOID pBuffer, DWORD nSize, ULONG ulFlags)
	assertl_reflect_as(::SetFirmwareEnvironmentVariableExW(lpName, lpGuid, pBuffer, nSize, ulFlags));
// GetFirmwareType
// IsNativeVhdBoot
// EnumResourceTypes
inline void EnumResourceTypes(HINSTANCE hModule, ENUMRESTYPEPROCA lpEnumFunc, LONG_PTR lParam)
	assertl_reflect_as(::EnumResourceTypesA(hModule, lpEnumFunc, lParam));
inline void EnumResourceTypes(HINSTANCE hModule, ENUMRESTYPEPROCW lpEnumFunc, LONG_PTR lParam)
	assertl_reflect_as(::EnumResourceTypesW(hModule, lpEnumFunc, lParam));
// EnumResourceLanguages
inline void EnumResourceLanguages(HINSTANCE hModule, LPCSTR lpType, LPCSTR lpName, ENUMRESLANGPROCA lpEnumFunc, LONG_PTR lParam)
	assertl_reflect_as(::EnumResourceLanguagesA(hModule, lpType, lpName, lpEnumFunc, lParam));
inline void EnumResourceLanguages(HINSTANCE hModule, LPCWSTR lpType, LPCWSTR lpName, ENUMRESLANGPROCW lpEnumFunc, LONG_PTR lParam)
	assertl_reflect_as(::EnumResourceLanguagesW(hModule, lpType, lpName, lpEnumFunc, lParam));
// BeginUpdateResource
inline HANDLE BeginUpdateResource(LPCSTR pFileName, BOOL bDeleteExistingResources)
	assertl_reflect_as(auto h = ::BeginUpdateResourceA(pFileName, bDeleteExistingResources), h);
inline HANDLE BeginUpdateResource(LPCWSTR pFileName, BOOL bDeleteExistingResources)
	assertl_reflect_as(auto h = ::BeginUpdateResourceW(pFileName, bDeleteExistingResources), h);
// UpdateResource
inline void UpdateResource(HANDLE hUpdate, LPCSTR lpType, LPCSTR lpName, WORD wLanguage, LPVOID lpData, DWORD cb)
	assertl_reflect_as(::UpdateResourceA(hUpdate, lpType, lpName, wLanguage, lpData, cb));
inline void UpdateResource(HANDLE hUpdate, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage, LPVOID lpData, DWORD cb)
	assertl_reflect_as(::UpdateResourceW(hUpdate, lpType, lpName, wLanguage, lpData, cb));
// EndUpdateResource
template<bool IsUnicode = WX::IsUnicode>
inline void EndUpdateResource(HANDLE hUpdate, BOOL fDiscard) {
	if_c (IsUnicode)
		 assertl_reflect_as(::EndUpdateResourceW(hUpdate, fDiscard))
	else assertl_reflect_as(::EndUpdateResourceA(hUpdate, fDiscard))
}
// GlobalAddAtom
inline ATOM GlobalAddAtom(LPCSTR lpString)
	assertl_reflect_as(auto a = ::GlobalAddAtomA(lpString), a);
inline ATOM GlobalAddAtom(LPCWSTR lpString)
	assertl_reflect_as(auto a = ::GlobalAddAtomW(lpString), a);
// GlobalAddAtomEx
inline ATOM GlobalAddAtomEx(LPCSTR lpString, DWORD dwFlags)
	assertl_reflect_as(auto a = ::GlobalAddAtomExA(lpString, dwFlags), a);
inline ATOM GlobalAddAtomEx(LPCWSTR lpString, DWORD dwFlags)
	assertl_reflect_as(auto a = ::GlobalAddAtomExW(lpString, dwFlags), a);
// GlobalFindAtom
inline ATOM GlobalFindAtom(LPCSTR lpString)
	assertl_reflect_as(auto a = ::GlobalFindAtomA(lpString), a);
inline ATOM GlobalFindAtom(LPCWSTR lpString)
	assertl_reflect_as(auto a = ::GlobalFindAtomW(lpString), a);
// GlobalGetAtomName
inline UINT GlobalGetAtomName(ATOM nAtom, LPSTR lpBuffer, int nSize)
	assertl_reflect_as(auto n = ::GlobalGetAtomNameA(nAtom, lpBuffer, nSize), n);
inline UINT GlobalGetAtomName(ATOM nAtom, LPWSTR lpBuffer, int nSize)
	assertl_reflect_as(auto n = ::GlobalGetAtomNameW(nAtom, lpBuffer, nSize), n);
// AddAtom
inline ATOM AddAtom(LPCSTR lpString)
	assertl_reflect_as(auto a = ::AddAtomA(lpString), a);
inline ATOM AddAtom(LPCWSTR lpString)
	assertl_reflect_as(auto a = ::AddAtomW(lpString), a);
// FindAtom
inline ATOM FindAtom(LPCSTR lpString)
	assertl_reflect_as(auto a = ::FindAtomA(lpString), a);
inline ATOM FindAtom(LPCWSTR lpString)
	assertl_reflect_as(auto a = ::FindAtomW(lpString), a);
// GetAtomName
inline UINT GetAtomName(ATOM nAtom, LPSTR lpBuffer, int nSize)
	assertl_reflect_as(auto n = ::GetAtomNameA(nAtom, lpBuffer, nSize), n);
inline UINT GetAtomName(ATOM nAtom, LPWSTR lpBuffer, int nSize)
	assertl_reflect_as(auto n = ::GetAtomNameW(nAtom, lpBuffer, nSize), n);
// GetProfileInt
inline UINT GetProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nDefault)
	reflect_as(::GetProfileIntA(lpAppName, lpKeyName, nDefault));
inline UINT GetProfileInt(LPCWSTR lpAppName, LPCWSTR lpKeyName, int nDefault)
	reflect_as(::GetProfileIntW(lpAppName, lpKeyName, nDefault));
// GetProfileString
inline DWORD GetProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString, int nSize)
	reflect_as(::GetProfileStringA(lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize));
inline DWORD GetProfileString(LPCWSTR lpAppName, LPCWSTR lpKeyName, LPCWSTR lpDefault, LPWSTR lpReturnedString, int nSize)
	reflect_as(::GetProfileStringW(lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize));
// WriteProfileString
inline void WriteProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpString)
	assertl_reflect_as(::WriteProfileStringA(lpAppName, lpKeyName, lpString));
inline void WriteProfileString(LPCWSTR lpAppName, LPCWSTR lpKeyName, LPCWSTR lpString)
	assertl_reflect_as(::WriteProfileStringW(lpAppName, lpKeyName, lpString));
// GetProfileSection
inline DWORD GetProfileSection(LPCSTR lpAppName, LPSTR lpReturnedString, int nSize)
	reflect_as(::GetProfileSectionA(lpAppName, lpReturnedString, nSize));
inline DWORD GetProfileSection(LPCWSTR lpAppName, LPWSTR lpReturnedString, int nSize)
	reflect_as(::GetProfileSectionW(lpAppName, lpReturnedString, nSize));
// WriteProfileSection
inline void WriteProfileSection(LPCSTR lpAppName, LPCSTR lpString)
	assertl_reflect_as(::WriteProfileSectionA(lpAppName, lpString));
inline void WriteProfileSection(LPCWSTR lpAppName, LPCWSTR lpString)
	assertl_reflect_as(::WriteProfileSectionW(lpAppName, lpString));
// GetPrivateProfileInt
inline UINT GetPrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nDefault, LPCSTR lpFileName)
	reflect_as(::GetPrivateProfileIntA(lpAppName, lpKeyName, nDefault, lpFileName));
inline UINT GetPrivateProfileInt(LPCWSTR lpAppName, LPCWSTR lpKeyName, int nDefault, LPCWSTR lpFileName)
	reflect_as(::GetPrivateProfileIntW(lpAppName, lpKeyName, nDefault, lpFileName));
// GetPrivateProfileString
inline DWORD GetPrivateProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault,
									 LPSTR lpReturnedString, int nSize, LPCSTR lpFileName)
	assertl_reflect_as(auto n = ::GetPrivateProfileStringA(
		lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize, lpFileName), n);
inline DWORD GetPrivateProfileString(LPCWSTR lpAppName, LPCWSTR lpKeyName, LPCWSTR lpDefault,
									 LPWSTR lpReturnedString, int nSize, LPCWSTR lpFileName)
	assertl_reflect_as(auto n = ::GetPrivateProfileStringW(
		lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize, lpFileName), n);
// WritePrivateProfileString
inline void WritePrivateProfileString(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpString, LPCSTR lpFileName)
	assertl_reflect_as(::WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName));
inline void WritePrivateProfileString(LPCWSTR lpAppName, LPCWSTR lpKeyName, LPCWSTR lpString, LPCWSTR lpFileName)
	assertl_reflect_as(::WritePrivateProfileStringW(lpAppName, lpKeyName, lpString, lpFileName));
// GetPrivateProfileSection
inline DWORD GetPrivateProfileSection(LPCSTR lpAppName, LPSTR lpReturnedString, int nSize, LPCSTR lpFileName)
	assertl_reflect_as(auto n = ::GetPrivateProfileSectionA(lpAppName, lpReturnedString, nSize, lpFileName), n);
inline DWORD GetPrivateProfileSection(LPCWSTR lpAppName, LPWSTR lpReturnedString, int nSize, LPCWSTR lpFileName)
	assertl_reflect_as(auto n = ::GetPrivateProfileSectionW(lpAppName, lpReturnedString, nSize, lpFileName), n);
// WritePrivateProfileSection
inline void WritePrivateProfileSection(LPCSTR lpAppName, LPCSTR lpString, LPCSTR lpFileName)
	assertl_reflect_as(::WritePrivateProfileSectionA(lpAppName, lpString, lpFileName));
inline void WritePrivateProfileSection(LPCWSTR lpAppName, LPCWSTR lpString, LPCWSTR lpFileName)
	assertl_reflect_as(::WritePrivateProfileSectionW(lpAppName, lpString, lpFileName));
// GetPrivateProfileSectionNames
inline DWORD GetPrivateProfileSectionNames(LPSTR lpszReturnBuffer, int nSize, LPCSTR lpFileName)
	assertl_reflect_as(auto n = ::GetPrivateProfileSectionNamesA(lpszReturnBuffer, nSize, lpFileName), n);
inline DWORD GetPrivateProfileSectionNames(LPWSTR lpszReturnBuffer, int nSize, LPCWSTR lpFileName)
	assertl_reflect_as(auto n = ::GetPrivateProfileSectionNamesW(lpszReturnBuffer, nSize, lpFileName), n);
// GetPrivateProfileStruct
inline void GetPrivateProfileStruct(LPCSTR lpszSection, LPCSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, LPCSTR lpszFile)
	assertl_reflect_as(::GetPrivateProfileStructA(lpszSection, lpszKey, lpStruct, uSizeStruct, lpszFile));
inline void GetPrivateProfileStruct(LPCWSTR lpszSection, LPCWSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, LPCWSTR lpszFile)
	assertl_reflect_as(::GetPrivateProfileStructW(lpszSection, lpszKey, lpStruct, uSizeStruct, lpszFile));
// WritePrivateProfileStruct
inline void WritePrivateProfileStruct(LPCSTR lpszSection, LPCSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, LPCSTR lpszFile)
	assertl_reflect_as(::WritePrivateProfileStructA(lpszSection, lpszKey, lpStruct, uSizeStruct, lpszFile));
inline void WritePrivateProfileStruct(LPCWSTR lpszSection, LPCWSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, LPCWSTR lpszFile)
	assertl_reflect_as(::WritePrivateProfileStructW(lpszSection, lpszKey, lpStruct, uSizeStruct, lpszFile));
// SetDllDirectory
inline void SetDllDirectory(LPCSTR lpPathName)
	assertl_reflect_as(::SetDllDirectoryA(lpPathName));
inline void SetDllDirectory(LPCWSTR lpPathName)
	assertl_reflect_as(::SetDllDirectoryW(lpPathName));
// GetDllDirectory
inline DWORD GetDllDirectory(DWORD nBufferLength, LPSTR lpBuffer)
	assertl_reflect_as(auto n = ::GetDllDirectoryA(nBufferLength, lpBuffer), n);
inline DWORD GetDllDirectory(DWORD nBufferLength, LPWSTR lpBuffer)
	assertl_reflect_as(auto n = ::GetDllDirectoryW(nBufferLength, lpBuffer), n);
// SetSearchPathMode
// CreateDirectoryEx
inline void CreateDirectory(LPCSTR lpTemplateDirectory, LPCSTR lpNewDirectory, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateDirectoryExA(lpTemplateDirectory, lpNewDirectory, lpSecurityAttributes));
inline void CreateDirectory(LPCWSTR lpTemplateDirectory, LPCWSTR lpNewDirectory, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateDirectoryExW(lpTemplateDirectory, lpNewDirectory, lpSecurityAttributes));
// CreateDirectoryTransacted
inline void CreateDirectory(LPCSTR lpTemplateDirectory, LPCSTR lpNewDirectory, LPSECURITY_ATTRIBUTES lpSecurityAttributes, HANDLE hTransaction)
	assertl_reflect_as(::CreateDirectoryTransactedA(lpTemplateDirectory, lpNewDirectory, lpSecurityAttributes, hTransaction));
inline void CreateDirectory(LPCWSTR lpTemplateDirectory, LPCWSTR lpNewDirectory, LPSECURITY_ATTRIBUTES lpSecurityAttributes, HANDLE hTransaction)
	assertl_reflect_as(::CreateDirectoryTransactedW(lpTemplateDirectory, lpNewDirectory, lpSecurityAttributes, hTransaction));
// RemoveDirectory
// from fileapi.h
inline void RemoveDirectory(LPCSTR lpPathName)
	assertl_reflect_as(::RemoveDirectoryA(lpPathName));
// from fileapi.h
inline void RemoveDirectory(LPCWSTR lpPathName)
	assertl_reflect_as(::RemoveDirectoryW(lpPathName));
// RemoveDirectoryTransacted
inline void RemoveDirectory(LPCSTR lpPathName, HANDLE hTransaction)
	assertl_reflect_as(::RemoveDirectoryTransactedA(lpPathName, hTransaction));
inline void RemoveDirectory(LPCWSTR lpPathName, HANDLE hTransaction)
	assertl_reflect_as(::RemoveDirectoryTransactedW(lpPathName, hTransaction));
// GetFullPathName
// from fileapi.h
inline DWORD GetFullPathName(LPCSTR lpFileName, DWORD nBufferLength, LPSTR lpBuffer, LPSTR *lpFilePart)
	assertl_reflect_as(auto n = ::GetFullPathNameA(lpFileName, nBufferLength, lpBuffer, lpFilePart), n);
// from fileapi.h
inline DWORD GetFullPathName(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart)
	assertl_reflect_as(auto n = ::GetFullPathNameW(lpFileName, nBufferLength, lpBuffer, lpFilePart), n);
// GetFullPathNameTransacted
inline DWORD GetFullPathName(LPCSTR lpFileName, DWORD nBufferLength, LPSTR lpBuffer, LPSTR *lpFilePart, HANDLE hTransaction)
	assertl_reflect_as(auto n = ::GetFullPathNameTransactedA(lpFileName, nBufferLength, lpBuffer, lpFilePart, hTransaction), n);
inline DWORD GetFullPathName(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart, HANDLE hTransaction)
	assertl_reflect_as(auto n = ::GetFullPathNameTransactedW(lpFileName, nBufferLength, lpBuffer, lpFilePart, hTransaction), n);
// DefineDosDevice
inline void DefineDosDevice(DWORD dwFlags, LPCSTR lpDeviceName, LPCSTR lpTargetPath)
	assertl_reflect_as(::DefineDosDeviceA(dwFlags, lpDeviceName, lpTargetPath));
// from fileapi.h
inline void DefineDosDevice(DWORD dwFlags, LPCWSTR lpDeviceName, LPCWSTR lpTargetPath)
	assertl_reflect_as(::DefineDosDeviceW(dwFlags, lpDeviceName, lpTargetPath));
// QueryDosDevice
inline DWORD QueryDosDevice(LPCSTR lpDeviceName, LPSTR lpTargetPath, DWORD ucchMax)
	assertl_reflect_as(auto n = ::QueryDosDeviceA(lpDeviceName, lpTargetPath, ucchMax), n);
// from fileapi.h
inline DWORD QueryDosDevice(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax)
	assertl_reflect_as(auto n = ::QueryDosDeviceW(lpDeviceName, lpTargetPath, ucchMax), n);
// CreateFileTransacted
inline HANDLE CreateFile(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
						 DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile,
						 HANDLE hTransaction, PUSHORT pusMiniVersion, PVOID  lpExtendedParameter)
	assertl_reflect_as(auto h = ::CreateFileTransactedA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
														dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile,
														hTransaction, pusMiniVersion, lpExtendedParameter); h != INVALID_HANDLE_VALUE, h);
inline HANDLE CreateFile(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
						 DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile,
						 HANDLE hTransaction, PUSHORT pusMiniVersion, PVOID  lpExtendedParameter)
	assertl_reflect_as(auto h = ::CreateFileTransactedW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
														dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile,
														hTransaction, pusMiniVersion, lpExtendedParameter); h != INVALID_HANDLE_VALUE, h);
// ReOpenFile
// SetFileAttributes
// from fileapi.h
inline void SetFileAttributes(LPCSTR lpFileName, DWORD dwFileAttributes)
	assertl_reflect_as(::SetFileAttributesA(lpFileName, dwFileAttributes));
// from fileapi.h
inline void SetFileAttributes(LPCWSTR lpFileName, DWORD dwFileAttributes)
	assertl_reflect_as(::SetFileAttributesW(lpFileName, dwFileAttributes));
// SetFileAttributesTransacted
inline void SetFileAttributes(LPCSTR lpFileName, DWORD dwFileAttributes, HANDLE hTransaction)
	assertl_reflect_as(::SetFileAttributesTransactedA(lpFileName, dwFileAttributes, hTransaction));
inline void SetFileAttributes(LPCWSTR lpFileName, DWORD dwFileAttributes, HANDLE hTransaction)
	assertl_reflect_as(::SetFileAttributesTransactedW(lpFileName, dwFileAttributes, hTransaction));
// GetFileAttributes
// from fileapi.h
inline DWORD GetFileAttributes(LPCSTR lpFileName)
	assertl_reflect_as(auto n = ::GetFileAttributesA(lpFileName); n != INVALID_FILE_ATTRIBUTES, n);
// from fileapi.h
inline DWORD GetFileAttributes(LPCWSTR lpFileName)
	assertl_reflect_as(auto n = ::GetFileAttributesW(lpFileName); n != INVALID_FILE_ATTRIBUTES, n);
// GetFileAttributesEx
inline void GetFileAttributes(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)
	assertl_reflect_as(::GetFileAttributesExA(lpFileName, fInfoLevelId, lpFileInformation));
inline void GetFileAttributes(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation)
	assertl_reflect_as(::GetFileAttributesExW(lpFileName, fInfoLevelId, lpFileInformation));
// GetFileAttributesTransacted
inline void GetFileAttributes(LPCSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation, HANDLE hTransaction)
	assertl_reflect_as(::GetFileAttributesTransactedA(lpFileName, fInfoLevelId, lpFileInformation, hTransaction));
inline void GetFileAttributes(LPCWSTR lpFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation, HANDLE hTransaction)
	assertl_reflect_as(::GetFileAttributesTransactedW(lpFileName, fInfoLevelId, lpFileInformation, hTransaction));
// GetCompressedFileSize
// from fileapi.h
inline DWORD GetCompressedFileSize(LPCSTR lpFileName, LPDWORD lpFileSizeHigh)
	assertl_reflect_as(auto n = ::GetCompressedFileSizeA(lpFileName, lpFileSizeHigh); n != INVALID_FILE_SIZE, n);
// from fileapi.h
inline DWORD GetCompressedFileSize(LPCWSTR lpFileName, LPDWORD lpFileSizeHigh)
	assertl_reflect_as(auto n = ::GetCompressedFileSizeW(lpFileName, lpFileSizeHigh); n != INVALID_FILE_SIZE, n);
// GetCompressedFileSizeTransacted
inline DWORD GetCompressedFileSize(LPCSTR lpFileName, LPDWORD lpFileSizeHigh, HANDLE hTransaction)
	assertl_reflect_as(auto n = ::GetCompressedFileSizeTransactedA(lpFileName, lpFileSizeHigh, hTransaction); n != INVALID_FILE_SIZE, n);
inline DWORD GetCompressedFileSize(LPCWSTR lpFileName, LPDWORD lpFileSizeHigh, HANDLE hTransaction)
	assertl_reflect_as(auto n = ::GetCompressedFileSizeTransactedW(lpFileName, lpFileSizeHigh, hTransaction); n != INVALID_FILE_SIZE, n);
// DeleteFileTransacted
inline void DeleteFile(LPCSTR lpFileName, HANDLE hTransaction)
	assertl_reflect_as(::DeleteFileTransactedA(lpFileName, hTransaction));
inline void DeleteFile(LPCWSTR lpFileName, HANDLE hTransaction)
	assertl_reflect_as(::DeleteFileTransactedW(lpFileName, hTransaction));
// CheckNameLegalDOS8Dot3
inline void CheckNameLegalDOS8Dot3(LPCSTR lpName, LPSTR lpOemName, DWORD OemNameSize, PBOOL pbNameContainsSpaces, PBOOL pbNameLegal)
	assertl_reflect_as(::CheckNameLegalDOS8Dot3A(lpName, lpOemName, OemNameSize, pbNameContainsSpaces, pbNameLegal));
inline void CheckNameLegalDOS8Dot3(LPCWSTR lpName, LPSTR lpOemName, DWORD OemNameSize, PBOOL pbNameContainsSpaces, PBOOL pbNameLegal)
	assertl_reflect_as(::CheckNameLegalDOS8Dot3W(lpName, lpOemName, OemNameSize, pbNameContainsSpaces, pbNameLegal));
// FindFirstFile
// from fileapi.h
inline HANDLE FindFirstFile(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
	assertl_reflect_as(auto h = ::FindFirstFileA(lpFileName, lpFindFileData); h != INVALID_HANDLE_VALUE, h);
// from fileapi.h
inline HANDLE FindFirstFile(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
	assertl_reflect_as(auto h = ::FindFirstFileW(lpFileName, lpFindFileData); h != INVALID_HANDLE_VALUE, h);
// FindFirstFileEx
// from fileapi.h
inline HANDLE FindFirstFile(LPCSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData,
							FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags)
	assertl_reflect_as(auto h = ::FindFirstFileExA(lpFileName, fInfoLevelId, lpFindFileData,
												   fSearchOp, lpSearchFilter, dwAdditionalFlags); h != INVALID_HANDLE_VALUE, h);
// from fileapi.h
inline HANDLE FindFirstFile(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData,
							FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags)
	assertl_reflect_as(auto h = ::FindFirstFileExW(lpFileName, fInfoLevelId, lpFindFileData,
												   fSearchOp, lpSearchFilter, dwAdditionalFlags); h != INVALID_HANDLE_VALUE, h);
// FindFirstFileTransacted
inline HANDLE FindFirstFile(LPCSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData,
							FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags, HANDLE hTransaction)
	assertl_reflect_as(auto h = ::FindFirstFileTransactedA(lpFileName, fInfoLevelId, lpFindFileData,
														   fSearchOp, lpSearchFilter, dwAdditionalFlags, hTransaction); h != INVALID_HANDLE_VALUE, h);
inline HANDLE FindFirstFile(LPCWSTR lpFileName, FINDEX_INFO_LEVELS fInfoLevelId, LPVOID lpFindFileData,
							FINDEX_SEARCH_OPS fSearchOp, LPVOID lpSearchFilter, DWORD dwAdditionalFlags, HANDLE hTransaction)
	assertl_reflect_as(auto h = ::FindFirstFileTransactedW(lpFileName, fInfoLevelId, lpFindFileData,
														   fSearchOp, lpSearchFilter, dwAdditionalFlags, hTransaction); h != INVALID_HANDLE_VALUE, h);
// CopyFile
inline void CopyFile(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists)
	assertl_reflect_as(::CopyFileA(lpExistingFileName, lpNewFileName, bFailIfExists))
inline void CopyFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists)
	assertl_reflect_as(::CopyFileW(lpExistingFileName, lpNewFileName, bFailIfExists))
// CopyFileEx
inline void CopyFile(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine,
					 LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags)
	assertl_reflect_as(::CopyFileExA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags));
inline void CopyFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine,
					 LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags)
	assertl_reflect_as(::CopyFileExW(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags));
// CopyFileTransacted
// CopyFile2
// MoveFile
inline void MoveFile(LPCSTR lpExistingFileName, LPCSTR lpNewFileName)
	assertl_reflect_as(::MoveFileA(lpExistingFileName, lpNewFileName));
inline void MoveFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName)
	assertl_reflect_as(::MoveFileW(lpExistingFileName, lpNewFileName));
// MoveFileEx
inline void MoveFile(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, DWORD dwFlags)
	assertl_reflect_as(::MoveFileExA(lpExistingFileName, lpNewFileName, dwFlags));
inline void MoveFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, DWORD dwFlags)
	assertl_reflect_as(::MoveFileExW(lpExistingFileName, lpNewFileName, dwFlags));
// MoveFileWithProgress
inline void MoveFile(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, DWORD dwFlags)
	assertl_reflect_as(::MoveFileWithProgressA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags));
inline void MoveFile(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, DWORD dwFlags)
	assertl_reflect_as(::MoveFileWithProgressW(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags));
// ReplaceFile
inline void ReplaceFile(LPCSTR lpReplacedFileName, LPCSTR lpReplacementFileName, LPCSTR lpBackupFileName, DWORD dwReplaceFlags, LPVOID lpExclude, LPVOID lpReserved)
	assertl_reflect_as(::ReplaceFileA(lpReplacedFileName, lpReplacementFileName, lpBackupFileName, dwReplaceFlags, lpExclude, lpReserved));
inline void ReplaceFile(LPCWSTR lpReplacedFileName, LPCWSTR lpReplacementFileName, LPCWSTR lpBackupFileName, DWORD dwReplaceFlags, LPVOID lpExclude, LPVOID lpReserved)
	assertl_reflect_as(::ReplaceFileW(lpReplacedFileName, lpReplacementFileName, lpBackupFileName, dwReplaceFlags, lpExclude, lpReserved));
// CreateHardLink
inline void CreateHardLink(LPCSTR lpFileName, LPCSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateHardLinkA(lpFileName, lpExistingFileName, lpSecurityAttributes));
inline void CreateHardLink(LPCWSTR lpFileName, LPCWSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(::CreateHardLinkW(lpFileName, lpExistingFileName, lpSecurityAttributes));
// CreateHardLinkTransacted
inline void CreateHardLink(LPCSTR lpFileName, LPCSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes, HANDLE hTransaction)
	assertl_reflect_as(::CreateHardLinkTransactedA(lpFileName, lpExistingFileName, lpSecurityAttributes, hTransaction));
inline void CreateHardLink(LPCWSTR lpFileName, LPCWSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes, HANDLE hTransaction)
	assertl_reflect_as(::CreateHardLinkTransactedW(lpFileName, lpExistingFileName, lpSecurityAttributes, hTransaction));
// FindFirstStreamTransacted
inline HANDLE FindFirstStream(LPCWSTR lpFileName, STREAM_INFO_LEVELS InfoLevel, LPVOID lpFindStreamData, DWORD dwFlags, HANDLE hTransaction)
	assertl_reflect_as(auto h = ::FindFirstStreamTransactedW(lpFileName, InfoLevel, lpFindStreamData, dwFlags, hTransaction); h != INVALID_HANDLE_VALUE, h);
// FindFirstFileName
inline HANDLE FindFirstFileNameTransacted(LPCWSTR lpFileName, DWORD dwFlags, LPDWORD StringLength, PWSTR LinkName, HANDLE hTransaction)
	assertl_reflect_as(auto h = ::FindFirstFileNameTransactedW(lpFileName, dwFlags, StringLength, LinkName, hTransaction); h != INVALID_HANDLE_VALUE, h);
// CreateNamedPipe
inline HANDLE CreateNamedPipe(LPCSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize,
							  DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(auto h = ::CreateNamedPipeA(lpName, dwOpenMode, dwPipeMode, nMaxInstances, nOutBufferSize,
														 nInBufferSize, nDefaultTimeOut, lpSecurityAttributes); h != INVALID_HANDLE_VALUE, h);
// from namedpipeapi.h
inline HANDLE CreateNamedPipe(LPCWSTR lpName, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize,
							  DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	assertl_reflect_as(auto h = ::CreateNamedPipeW(lpName, dwOpenMode, dwPipeMode, nMaxInstances, nOutBufferSize,
														 nInBufferSize, nDefaultTimeOut, lpSecurityAttributes); h != INVALID_HANDLE_VALUE, h);
// GetNamedPipeHandleState
inline void GetNamedPipeHandleState(HANDLE hNamedPipe, LPDWORD lpState, LPDWORD lpCurInstances, LPDWORD lpMaxCollectionCount,
									LPDWORD lpCollectDataTimeout, LPSTR lpUserName, DWORD nMaxUserNameSize)
	assertl_reflect_as(::GetNamedPipeHandleStateA(hNamedPipe, lpState, lpCurInstances, lpMaxCollectionCount,
												  lpCollectDataTimeout, lpUserName, nMaxUserNameSize));
// from namedpipeapi.h
inline void GetNamedPipeHandleState(HANDLE hNamedPipe, LPDWORD lpState, LPDWORD lpCurInstances, LPDWORD lpMaxCollectionCount,
									LPDWORD lpCollectDataTimeout, LPWSTR lpUserName, DWORD nMaxUserNameSize)
	assertl_reflect_as(::GetNamedPipeHandleStateW(hNamedPipe, lpState, lpCurInstances, lpMaxCollectionCount,
												  lpCollectDataTimeout, lpUserName, nMaxUserNameSize));
// CallNamedPipe
inline void CallNamedPipe(LPCSTR lpNamedPipeName, LPVOID lpInBuffer, DWORD nInBufferSize,
						  LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesRead, DWORD nTimeOut)
	assertl_reflect_as(::CallNamedPipeA(lpNamedPipeName, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesRead, nTimeOut));
// from namedpipeapi.h
inline void CallNamedPipe(LPCWSTR lpNamedPipeName, LPVOID lpInBuffer, DWORD nInBufferSize,
						  LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesRead, DWORD nTimeOut)
	assertl_reflect_as(::CallNamedPipeW(lpNamedPipeName, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesRead, nTimeOut));
// WaitNamedPipe
inline void WaitNamedPipe(LPCSTR lpNamedPipeName, DWORD nTimeOut)
	assertl_reflect_as(::WaitNamedPipeA(lpNamedPipeName, nTimeOut));
// from namedpipeapi.h
inline void WaitNamedPipe(LPCWSTR lpNamedPipeName, DWORD nTimeOut)
	assertl_reflect_as(::WaitNamedPipeW(lpNamedPipeName, nTimeOut));
// GetNamedPipeClientComputerName
inline void GetNamedPipeClientComputerName(HANDLE Pipe, LPSTR ClientComputerName, ULONG ClientComputerNameLength)
	assertl_reflect_as(::GetNamedPipeClientComputerNameA(Pipe, ClientComputerName, ClientComputerNameLength));
// from namedpipeapi.h
inline void GetNamedPipeClientComputerName(HANDLE Pipe, LPWSTR ClientComputerName, ULONG ClientComputerNameLength)
	assertl_reflect_as(::GetNamedPipeClientComputerNameW(Pipe, ClientComputerName, ClientComputerNameLength));
// GetNamedPipeClientProcessId
// GetNamedPipeClientSessionId
// GetNamedPipeServerProcessId
// GetNamedPipeServerSessionId
// SetVolumeLabel
inline void SetVolumeLabel(LPCSTR lpRootPathName, LPCSTR lpVolumeName)
	assertl_reflect_as(::SetVolumeLabelA(lpRootPathName, lpVolumeName));
inline void SetVolumeLabel(LPCWSTR lpRootPathName, LPCWSTR lpVolumeName)
	assertl_reflect_as(::SetVolumeLabelW(lpRootPathName, lpVolumeName));
// SetFileBandwidthReservation
// GetFileBandwidthReservation
// ClearEventLog
// BackupEventLog
inline void BackupEventLog(HANDLE hEventLog, LPCSTR lpBackupFileName)
	assertl_reflect_as(::BackupEventLogA(hEventLog, lpBackupFileName));
inline void BackupEventLog(HANDLE hEventLog, LPCWSTR lpBackupFileName)
	assertl_reflect_as(::BackupEventLogW(hEventLog, lpBackupFileName));
// CloseEventLog
// DeregisterEventSource
// NotifyChangeEventLog
// GetNumberOfEventLogRecords
// GetOldestEventLogRecord
// OpenEventLog
inline HANDLE OpenEventLog(LPCSTR lpUNCServerName, LPCSTR lpSourceName)
	assertl_reflect_as(auto h = ::OpenEventLogA(lpUNCServerName, lpSourceName), h);
inline HANDLE OpenEventLog(LPCWSTR lpUNCServerName, LPCWSTR lpSourceName)
	assertl_reflect_as(auto h = ::OpenEventLogW(lpUNCServerName, lpSourceName), h);
// RegisterEventSource
inline HANDLE RegisterEventSource(LPCSTR lpUNCServerName, LPCSTR lpSourceName)
	assertl_reflect_as(auto h = ::RegisterEventSourceA(lpUNCServerName, lpSourceName), h);
inline HANDLE RegisterEventSource(LPCWSTR lpUNCServerName, LPCWSTR lpSourceName)
	assertl_reflect_as(auto h = ::RegisterEventSourceW(lpUNCServerName, lpSourceName), h);
// OpenBackupEventLog
inline HANDLE OpenBackupEventLog(LPCSTR lpUNCServerName, LPCSTR lpFileName)
	assertl_reflect_as(auto h = ::OpenBackupEventLogA(lpUNCServerName, lpFileName), h);
inline HANDLE OpenBackupEventLog(LPCWSTR lpUNCServerName, LPCWSTR lpFileName)
	assertl_reflect_as(auto h = ::OpenBackupEventLogW(lpUNCServerName, lpFileName), h);
// ReadEventLog
template<bool IsUnicode = WX::IsUnicode>
inline DWORD ReadEventLog(HANDLE hEventLog, DWORD dwReadFlags, DWORD dwRecordOffset, LPVOID lpBuffer,
						  DWORD nNumberOfBytesToRead, LPDWORD pnBytesRead, LPDWORD pnMinNumberOfBytesNeeded) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto n = ::ReadEventLogW(hEventLog, dwReadFlags, dwRecordOffset, lpBuffer,
													nNumberOfBytesToRead, pnBytesRead, pnMinNumberOfBytesNeeded), n)
	else assertl_reflect_as(auto n = ::ReadEventLogA(hEventLog, dwReadFlags, dwRecordOffset, lpBuffer,
													nNumberOfBytesToRead, pnBytesRead, pnMinNumberOfBytesNeeded), n)
}
// ReportEvent
inline void ReportEvent(HANDLE hEventLog, WORD wType, WORD wCategory, DWORD dwEventID,
						PSID lpUserSid, WORD wNumStrings, DWORD dwDataSize, LPCSTR *lpStrings, LPVOID lpRawData)
	assertl_reflect_as(::ReportEventA(hEventLog, wType, wCategory, dwEventID, lpUserSid, wNumStrings,
									  dwDataSize, lpStrings, lpRawData));
inline void ReportEvent(HANDLE hEventLog, WORD wType, WORD wCategory, DWORD dwEventID,
						PSID lpUserSid, WORD wNumStrings, DWORD dwDataSize, LPCWSTR *lpStrings, LPVOID lpRawData)
	assertl_reflect_as(::ReportEventW(hEventLog, wType, wCategory, dwEventID, lpUserSid, wNumStrings,
									  dwDataSize, lpStrings, lpRawData));
// GetEventLogInformation
// OperationStart
// OperationEnd
// AccessCheckAndAuditAlarm
inline void AccessCheckAndAuditAlarm(LPCSTR SubsystemName, LPVOID HandleId, LPSTR ObjectTypeName,
									 LPSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor,
									 DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation,
									 LPDWORD GrantedAccess, LPBOOL AccessStatus, LPBOOL GenerateOnClose)
	assertl_reflect_as(::AccessCheckAndAuditAlarmA(SubsystemName, HandleId, ObjectTypeName, ObjectName,
												   SecurityDescriptor, DesiredAccess, GenericMapping, ObjectCreation,
												   GrantedAccess, AccessStatus, GenerateOnClose));
// from securitybaseapi.h
inline void AccessCheckAndAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, LPWSTR ObjectTypeName,
									 LPWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor,
									 DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation,
									 LPDWORD GrantedAccess, LPBOOL AccessStatus, LPBOOL GenerateOnClose)
	assertl_reflect_as(::AccessCheckAndAuditAlarmW(SubsystemName, HandleId, ObjectTypeName, ObjectName,
												   SecurityDescriptor, DesiredAccess, GenericMapping, ObjectCreation,
												   GrantedAccess, AccessStatus, GenerateOnClose));
// AccessCheckByTypeAndAuditAlarmA
// AccessCheckByTypeResultListAndAuditAlarm
inline void AccessCheckByTypeResultListAndAuditAlarm(LPCSTR SubsystemName, LPVOID HandleId, LPSTR ObjectTypeName,
													 LPSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor,
													 PSID PrincipalSelfSid, DWORD DesiredAccess, AUDIT_EVENT_TYPE AuditType,
													 DWORD Flags, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength,
													 PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess,
													 LPDWORD AccessStatus, LPBOOL pfGenerateOnClose)
	assertl_reflect_as(::AccessCheckByTypeResultListAndAuditAlarmA(SubsystemName, HandleId, ObjectTypeName, ObjectName,
																   SecurityDescriptor, PrincipalSelfSid, DesiredAccess,
																   AuditType, Flags, ObjectTypeList, ObjectTypeListLength,
																   GenericMapping, ObjectCreation, GrantedAccess,
																   AccessStatus, pfGenerateOnClose));
// from securitybaseapi.h
inline void AccessCheckByTypeResultListAndAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, LPWSTR ObjectTypeName,
													 LPWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor,
													 PSID PrincipalSelfSid, DWORD DesiredAccess, AUDIT_EVENT_TYPE AuditType,
													 DWORD Flags, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength,
													 PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess,
													 LPDWORD AccessStatus, LPBOOL pfGenerateOnClose)
	assertl_reflect_as(::AccessCheckByTypeResultListAndAuditAlarmW(SubsystemName, HandleId, ObjectTypeName, ObjectName,
																   SecurityDescriptor, PrincipalSelfSid, DesiredAccess,
																   AuditType, Flags, ObjectTypeList, ObjectTypeListLength,
																   GenericMapping, ObjectCreation, GrantedAccess,
																   AccessStatus, pfGenerateOnClose));
// AccessCheckByTypeResultListAndAuditAlarmByHandle
inline void AccessCheckByTypeResultListAndAuditAlarmByHandle(LPCSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken,
															 LPCSTR ObjectTypeName, LPCSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor,
															 PSID PrincipalSelfSid, DWORD DesiredAccess, AUDIT_EVENT_TYPE AuditType,
															 DWORD Flags, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength,
															 PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess,
															 LPDWORD AccessStatusList, LPBOOL pfGenerateOnClose)
	assertl_reflect_as(::AccessCheckByTypeResultListAndAuditAlarmByHandleA(SubsystemName, HandleId, ClientToken,
																		   ObjectTypeName, ObjectName, SecurityDescriptor,
																		   PrincipalSelfSid, DesiredAccess, AuditType,
																		   Flags, ObjectTypeList, ObjectTypeListLength,
																		   GenericMapping, ObjectCreation, GrantedAccess,
																		   AccessStatusList, pfGenerateOnClose));
// from securitybaseapi.h
inline void AccessCheckByTypeResultListAndAuditAlarmByHandle(LPCWSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken,
															 LPCWSTR ObjectTypeName, LPCWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor,
															 PSID PrincipalSelfSid, DWORD DesiredAccess, AUDIT_EVENT_TYPE AuditType,
															 DWORD Flags, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength,
															 PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess,
															 LPDWORD AccessStatusList, LPBOOL pfGenerateOnClose)
	assertl_reflect_as(::AccessCheckByTypeResultListAndAuditAlarmByHandleW(SubsystemName, HandleId, ClientToken,
																		   ObjectTypeName, ObjectName, SecurityDescriptor,
																		   PrincipalSelfSid, DesiredAccess, AuditType,
																		   Flags, ObjectTypeList, ObjectTypeListLength,
																		   GenericMapping, ObjectCreation, GrantedAccess,
																		   AccessStatusList, pfGenerateOnClose));
// ObjectOpenAuditAlarm
inline void ObjectOpenAuditAlarm(LPCSTR SubsystemName, LPVOID HandleId, LPSTR ObjectTypeName, LPSTR ObjectName,
								 PSECURITY_DESCRIPTOR pSecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess,
								 DWORD GrantedAccess, PPRIVILEGE_SET Privileges, BOOL ObjectCreation, BOOL AccessGranted,
								 LPBOOL GenerateOnClose)
	assertl_reflect_as(::ObjectOpenAuditAlarmA(SubsystemName, HandleId, ObjectTypeName, ObjectName,
											   pSecurityDescriptor, ClientToken, DesiredAccess, GrantedAccess,
											   Privileges, ObjectCreation, AccessGranted, GenerateOnClose));
// from securitybaseapi.h
inline void ObjectOpenAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, LPWSTR ObjectTypeName, LPWSTR ObjectName,
								 PSECURITY_DESCRIPTOR pSecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess,
								 DWORD GrantedAccess, PPRIVILEGE_SET Privileges, BOOL ObjectCreation, BOOL AccessGranted,
								 LPBOOL GenerateOnClose)
	assertl_reflect_as(::ObjectOpenAuditAlarmW(SubsystemName, HandleId, ObjectTypeName, ObjectName,
											   pSecurityDescriptor, ClientToken, DesiredAccess, GrantedAccess,
											   Privileges, ObjectCreation, AccessGranted, GenerateOnClose));
// ObjectPrivilegeAuditAlarm
inline void ObjectPrivilegeAuditAlarm(LPCSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken,
									  DWORD DesiredAccess, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
	assertl_reflect_as(::ObjectPrivilegeAuditAlarmA(SubsystemName, HandleId, ClientToken, DesiredAccess, Privileges, AccessGranted));
// from securitybaseapi.h
inline void ObjectPrivilegeAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken,
									  DWORD DesiredAccess, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
	assertl_reflect_as(::ObjectPrivilegeAuditAlarmW(SubsystemName, HandleId, ClientToken, DesiredAccess, Privileges, AccessGranted));
// ObjectCloseAuditAlarm
inline void ObjectCloseAuditAlarm(LPCSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
	assertl_reflect_as(::ObjectCloseAuditAlarmA(SubsystemName, HandleId, GenerateOnClose));
// from securitybaseapi.h
inline void ObjectCloseAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
	assertl_reflect_as(::ObjectCloseAuditAlarmW(SubsystemName, HandleId, GenerateOnClose));
// ObjectDeleteAuditAlarm
inline void ObjectDeleteAuditAlarm(LPCSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
	assertl_reflect_as(::ObjectDeleteAuditAlarmA(SubsystemName, HandleId, GenerateOnClose));
// from securitybaseapi.h
inline void ObjectDeleteAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
	assertl_reflect_as(::ObjectDeleteAuditAlarmW(SubsystemName, HandleId, GenerateOnClose));
// PrivilegedServiceAuditAlarm
inline void PrivilegedServiceAuditAlarm(LPCSTR SubsystemName, LPCSTR ServiceName, HANDLE ClientToken,
										PPRIVILEGE_SET Privileges, BOOL AccessGranted)
	assertl_reflect_as(::PrivilegedServiceAuditAlarmA(SubsystemName, ServiceName, ClientToken, Privileges, AccessGranted));
// from securitybaseapi.h
inline void PrivilegedServiceAuditAlarm(LPCWSTR SubsystemName, LPCWSTR ServiceName, HANDLE ClientToken,
										PPRIVILEGE_SET Privileges, BOOL AccessGranted)
	assertl_reflect_as(::PrivilegedServiceAuditAlarmW(SubsystemName, ServiceName, ClientToken, Privileges, AccessGranted));
// AddConditionalAce
// SetFileSecurity
inline void SetFileSecurity(LPCSTR lpFileName, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor)
	assertl_reflect_as(::SetFileSecurityA(lpFileName, SecurityInformation, pSecurityDescriptor));
// from securitybaseapi.h
inline void SetFileSecurity(LPCWSTR lpFileName, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor)
	assertl_reflect_as(::SetFileSecurityW(lpFileName, SecurityInformation, pSecurityDescriptor));
// GetFileSecurity
inline void GetFileSecurity(LPCSTR lpFileName, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor,
							DWORD nLength, LPDWORD lpnLengthNeeded)
	assertl_reflect_as(::GetFileSecurityA(lpFileName, SecurityInformation, pSecurityDescriptor, nLength, lpnLengthNeeded));
// from securitybaseapi.h
inline void GetFileSecurity(LPCWSTR lpFileName, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor,
							DWORD nLength, LPDWORD lpnLengthNeeded)
	assertl_reflect_as(::GetFileSecurityW(lpFileName, SecurityInformation, pSecurityDescriptor, nLength, lpnLengthNeeded));
// ReadDirectoryChanges
inline void ReadDirectoryChanges(HANDLE hDirectory, LPVOID lpBuffer, DWORD nBufferLength, BOOL bWatchSubtree,
								 DWORD dwNotifyFilter, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped,
								 LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
	assertl_reflect_as(::ReadDirectoryChangesW(hDirectory, lpBuffer, nBufferLength, bWatchSubtree,
											   dwNotifyFilter, lpBytesReturned, lpOverlapped, lpCompletionRoutine));
#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// ReadDirectoryChangesEx
inline void ReadDirectoryChanges(HANDLE hDirectory, LPVOID lpBuffer, DWORD nBufferLength, BOOL bWatchSubtree,
								 DWORD dwNotifyFilter, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped,
								 LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
								 READ_DIRECTORY_NOTIFY_INFORMATION_CLASS ReadDirectoryNotifyInformationClass)
	assertl_reflect_as(::ReadDirectoryChangesExW(hDirectory, lpBuffer, nBufferLength, bWatchSubtree,
												 dwNotifyFilter, lpBytesReturned, lpOverlapped, lpCompletionRoutine,
												 ReadDirectoryNotifyInformationClass));
#endif
// MapViewOfFileExNuma
// IsBadReadPtr - deprecated
// IsBadWritePtr - deprecated
// IsBadCodePtr - deprecated
// IsBadStringPtr - deprecated
// LookupAccountSid
inline void LookupAccountSid(LPCSTR lpSystemName, PSID Sid, LPSTR Name, LPDWORD cchName,
							 LPSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountSidA(lpSystemName, Sid, Name, cchName, ReferencedDomainName,
										   cchReferencedDomainName, peUse));
inline void LookupAccountSid(LPCWSTR lpSystemName, PSID Sid, LPWSTR Name, LPDWORD cchName,
							 LPWSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountSidW(lpSystemName, Sid, Name, cchName, ReferencedDomainName,
										   cchReferencedDomainName, peUse));
// LookupAccountName
inline void LookupAccountName(LPCSTR lpSystemName, LPCSTR lpAccountName, PSID Sid, LPDWORD cchSid,
							  LPSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountNameA(lpSystemName, lpAccountName, Sid, cchSid, ReferencedDomainName,
											cchReferencedDomainName, peUse));
inline void LookupAccountName(LPCWSTR lpSystemName, LPCWSTR lpAccountName, PSID Sid, LPDWORD cchSid,
							  LPWSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountNameW(lpSystemName, lpAccountName, Sid, cchSid, ReferencedDomainName,
											cchReferencedDomainName, peUse));
// LookupAccountNameLocal
inline void LookupAccountNameLocal(LPCSTR lpAccountName, PSID Sid, LPDWORD cchSid,
								   LPSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountNameLocalA(lpAccountName, Sid, cchSid, ReferencedDomainName,
												 cchReferencedDomainName, peUse));
inline void LookupAccountNameLocal(LPCWSTR lpAccountName, PSID Sid, LPDWORD cchSid,
								   LPWSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountNameLocalW(lpAccountName, Sid, cchSid, ReferencedDomainName,
												 cchReferencedDomainName, peUse));
// LookupAccountSidLocal
inline void LookupAccountSidLocal(PSID Sid, LPSTR Name, LPDWORD cchName,
								  LPSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountSidLocalA(Sid, Name, cchName, ReferencedDomainName,
												cchReferencedDomainName, peUse));
inline void LookupAccountSidLocal(PSID Sid, LPWSTR Name, LPDWORD cchName,
								  LPWSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
	assertl_reflect_as(::LookupAccountSidLocalW(Sid, Name, cchName, ReferencedDomainName,
												cchReferencedDomainName, peUse));
// LookupPrivilegeValue
inline void LookupPrivilegeValue(LPCSTR lpSystemName, LPCSTR lpName, PLUID lpLuid)
	assertl_reflect_as(::LookupPrivilegeValueA(lpSystemName, lpName, lpLuid));
inline void LookupPrivilegeValue(LPCWSTR lpSystemName, LPCWSTR lpName, PLUID lpLuid)
	assertl_reflect_as(::LookupPrivilegeValueW(lpSystemName, lpName, lpLuid));
// LookupPrivilegeName
inline void LookupPrivilegeName(LPCSTR lpSystemName, PLUID lpLuid, LPSTR lpName, LPDWORD cchName)
	assertl_reflect_as(::LookupPrivilegeNameA(lpSystemName, lpLuid, lpName, cchName));
inline void LookupPrivilegeName(LPCWSTR lpSystemName, PLUID lpLuid, LPWSTR lpName, LPDWORD cchName)
	assertl_reflect_as(::LookupPrivilegeNameW(lpSystemName, lpLuid, lpName, cchName));
// LookupPrivilegeDisplayName
inline void LookupPrivilegeDisplayName(LPCSTR lpSystemName, LPCSTR lpName, LPSTR lpDisplayName,
									   LPDWORD cchDisplayName, LPDWORD lpLanguageId)
	assertl_reflect_as(::LookupPrivilegeDisplayNameA(lpSystemName, lpName, lpDisplayName, cchDisplayName, lpLanguageId));
inline void LookupPrivilegeDisplayName(LPCWSTR lpSystemName, LPCWSTR lpName, LPWSTR lpDisplayName,
									   LPDWORD cchDisplayName, LPDWORD lpLanguageId)
	assertl_reflect_as(::LookupPrivilegeDisplayNameW(lpSystemName, lpName, lpDisplayName, cchDisplayName, lpLanguageId));
// BuildCommDCB
inline void BuildCommDCB(LPCSTR lpDef, LPDCB lpDCB)
	assertl_reflect_as(::BuildCommDCBA(lpDef, lpDCB));
inline void BuildCommDCB(LPCWSTR lpDef, LPDCB lpDCB)
	assertl_reflect_as(::BuildCommDCBW(lpDef, lpDCB));
// BuildCommDCBAndTimeouts
inline void BuildCommDCBAndTimeouts(LPCSTR lpDef, LPDCB lpDCB, LPCOMMTIMEOUTS lpCommTimeouts)
	assertl_reflect_as(::BuildCommDCBAndTimeoutsA(lpDef, lpDCB, lpCommTimeouts));
inline void BuildCommDCBAndTimeouts(LPCWSTR lpDef, LPDCB lpDCB, LPCOMMTIMEOUTS lpCommTimeouts)
	assertl_reflect_as(::BuildCommDCBAndTimeoutsW(lpDef, lpDCB, lpCommTimeouts));
// CommConfigDialog
inline void CommConfigDialog(LPCSTR lpszName, HWND hWnd, LPCOMMCONFIG lpCC)
	assertl_reflect_as(::CommConfigDialogA(lpszName, hWnd, lpCC));
inline void CommConfigDialog(LPCWSTR lpszName, HWND hWnd, LPCOMMCONFIG lpCC)
	assertl_reflect_as(::CommConfigDialogW(lpszName, hWnd, lpCC));
// GetDefaultCommConfig
inline void GetDefaultCommConfig(LPCSTR lpszName, LPCOMMCONFIG lpCC, LPDWORD lpdwSize)
	assertl_reflect_as(::GetDefaultCommConfigA(lpszName, lpCC, lpdwSize));
inline void GetDefaultCommConfig(LPCWSTR lpszName, LPCOMMCONFIG lpCC, LPDWORD lpdwSize)
	assertl_reflect_as(::GetDefaultCommConfigW(lpszName, lpCC, lpdwSize));
// SetDefaultCommConfig
inline void SetDefaultCommConfig(LPCSTR lpszName, LPCOMMCONFIG lpCC, DWORD dwSize)
	assertl_reflect_as(::SetDefaultCommConfigA(lpszName, lpCC, dwSize));
inline void SetDefaultCommConfig(LPCWSTR lpszName, LPCOMMCONFIG lpCC, DWORD dwSize)
	assertl_reflect_as(::SetDefaultCommConfigW(lpszName, lpCC, dwSize));
// GetComputerName
inline void GetComputerName(LPSTR lpBuffer, LPDWORD nSize)
	assertl_reflect_as(::GetComputerNameA(lpBuffer, nSize));
inline void GetComputerName(LPWSTR lpBuffer, LPDWORD nSize)
	assertl_reflect_as(::GetComputerNameW(lpBuffer, nSize));
// DnsHostnameToComputerName
inline void DnsHostnameToComputerName(LPCSTR Hostname, LPSTR ComputerName, LPDWORD nSize)
	assertl_reflect_as(::DnsHostnameToComputerNameA(Hostname, ComputerName, nSize));
inline void DnsHostnameToComputerName(LPCWSTR Hostname, LPWSTR ComputerName, LPDWORD nSize)
	assertl_reflect_as(::DnsHostnameToComputerNameW(Hostname, ComputerName, nSize));
// GetUserName
inline void GetUserName(LPSTR lpBuffer, LPDWORD nSize)
	assertl_reflect_as(::GetUserNameA(lpBuffer, nSize));
inline void GetUserName(LPWSTR lpBuffer, LPDWORD nSize)
	assertl_reflect_as(::GetUserNameW(lpBuffer, nSize));
// LogonUser
inline void LogonUser(LPCSTR lpszUsername, LPCSTR lpszDomain, LPCSTR lpszPassword, DWORD dwLogonType,
					  DWORD dwLogonProvider, PHANDLE phToken)
	assertl_reflect_as(::LogonUserA(lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken));
inline void LogonUser(LPCWSTR lpszUsername, LPCWSTR lpszDomain, LPCWSTR lpszPassword, DWORD dwLogonType,
					  DWORD dwLogonProvider, PHANDLE phToken)
	assertl_reflect_as(::LogonUserW(lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken));
// LogonUserEx
inline void LogonUser(LPCSTR lpszUsername, LPCSTR lpszDomain, LPCSTR lpszPassword, DWORD dwLogonType,
					  DWORD dwLogonProvider, PHANDLE phToken,
					  PSID *ppLogonSid, PVOID *ppProfileBuffer, LPDWORD pdwProfileLength, PQUOTA_LIMITS pQuotaLimits)
	assertl_reflect_as(::LogonUserExA(lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider,
									  phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits));
inline void LogonUser(LPCWSTR lpszUsername, LPCWSTR lpszDomain, LPCWSTR lpszPassword, DWORD dwLogonType,
					  DWORD dwLogonProvider, PHANDLE phToken,
					  PSID *ppLogonSid, PVOID *ppProfileBuffer, LPDWORD pdwProfileLength, PQUOTA_LIMITS pQuotaLimits)
	assertl_reflect_as(::LogonUserExW(lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider,
									  phToken, ppLogonSid, ppProfileBuffer, pdwProfileLength, pQuotaLimits));
// CreateProcessWithLogon
inline void CreateProcessWithLogon(LPCWSTR lpUsername, LPCWSTR lpDomain, LPCWSTR lpPassword, DWORD dwLogonFlags,
								   LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
								   DWORD dwCreationFlags, LPVOID lpEnvironment,
								   LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
								   LPPROCESS_INFORMATION lpProcessInformation)
	assertl_reflect_as(::CreateProcessWithLogonW(lpUsername, lpDomain, lpPassword, dwLogonFlags,
												 lpApplicationName, lpCommandLine, dwCreationFlags,
												 lpEnvironment, lpCurrentDirectory, lpStartupInfo,
												 lpProcessInformation));
// CreateProcessWithToken
inline void CreateProcessWithToken(HANDLE hToken, DWORD dwLogonFlags, LPCWSTR lpApplicationName,
								   LPWSTR lpCommandLine, DWORD dwCreationFlags, LPVOID lpEnvironment,
								   LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
								   LPPROCESS_INFORMATION lpProcessInformation)
	assertl_reflect_as(::CreateProcessWithTokenW(hToken, dwLogonFlags, lpApplicationName, lpCommandLine,
												 dwCreationFlags, lpEnvironment, lpCurrentDirectory,
												 lpStartupInfo, lpProcessInformation));
// RegisterWaitForSingleObject
inline void RegisterWaitForSingleObject(PHANDLE phNewWaitObject, HANDLE hObject, WAITORTIMERCALLBACK Callback, PVOID Context, ULONG dwMilliseconds, ULONG dwFlags)
	assertl_reflect_as(::RegisterWaitForSingleObject(phNewWaitObject, hObject, Callback, Context, dwMilliseconds, dwFlags));
// UnregisterWait
inline void UnregisterWait(HANDLE WaitHandle)
	assertl_reflect_as(::UnregisterWait(WaitHandle));
// BindIoCompletionCallback
// CreatePrivateNamespace
inline HANDLE CreatePrivateNamespace(LPSECURITY_ATTRIBUTES lpPrivateNamespaceAttributes, LPVOID lpBoundaryDescriptor,
									 LPCSTR lpAliasPrefix)
	assertl_reflect_as(auto h = ::CreatePrivateNamespaceA(lpPrivateNamespaceAttributes, lpBoundaryDescriptor, lpAliasPrefix), h);
// from namespaceapi.h
inline HANDLE CreatePrivateNamespace(LPSECURITY_ATTRIBUTES lpPrivateNamespaceAttributes, LPVOID lpBoundaryDescriptor,
									 LPCWSTR lpAliasPrefix)
	assertl_reflect_as(auto h = ::CreatePrivateNamespaceW(lpPrivateNamespaceAttributes, lpBoundaryDescriptor, lpAliasPrefix), h);
// OpenPrivateNamespace
inline HANDLE OpenPrivateNamespace(LPVOID lpBoundaryDescriptor, LPCSTR lpAliasPrefix)
	assertl_reflect_as(auto h = ::OpenPrivateNamespaceA(lpBoundaryDescriptor, lpAliasPrefix), h);
// from namespaceapi.h
inline HANDLE OpenPrivateNamespace(LPVOID lpBoundaryDescriptor, LPCWSTR lpAliasPrefix)
	assertl_reflect_as(auto h = ::OpenPrivateNamespaceW(lpBoundaryDescriptor, lpAliasPrefix), h);
// CreateBoundaryDescriptor
inline HANDLE CreateBoundaryDescriptor(LPCSTR Name, DWORD Flags)
	assertl_reflect_as(auto h = ::CreateBoundaryDescriptorA(Name, Flags), h);
// namespaceapi.h
inline HANDLE CreateBoundaryDescriptor(LPCWSTR Name, DWORD Flags)
	assertl_reflect_as(auto h = ::CreateBoundaryDescriptorW(Name, Flags), h);
// AddIntegrityLabelToBoundaryDescriptor
// GetCurrentHwProfile
inline void GetCurrentHwProfile(LPHW_PROFILE_INFOA lpHwProfileInfo)
	assertl_reflect_as(::GetCurrentHwProfileA(lpHwProfileInfo));
inline void GetCurrentHwProfile(LPHW_PROFILE_INFOW lpHwProfileInfo)
	assertl_reflect_as(::GetCurrentHwProfileW(lpHwProfileInfo));
// VerifyVersionInfo
//inline void VerifyVersionInfo(LPOSVERSIONINFOEXA lpVersionInfo, DWORD dwTypeMask, DWORDLONG dwlConditionMask)
//	assertl_reflect_as(::VerifyVersionInfoA(lpVersionInfo, dwTypeMask, dwlConditionMask));
//inline void VerifyVersionInfo(LPOSVERSIONINFOEXW lpVersionInfo, DWORD dwTypeMask, DWORDLONG dwlConditionMask)
//	assertl_reflect_as(::VerifyVersionInfoW(lpVersionInfo, dwTypeMask, dwlConditionMask));// SetSystemPowerState
// GetSystemPowerStatus
// MapUserPhysicalPagesScatter
// CreateJobObject
inline HANDLE CreateJobObject(LPSECURITY_ATTRIBUTES lpJobAttributes, LPCSTR lpName)
	assertl_reflect_as(auto h = ::CreateJobObjectA(lpJobAttributes, lpName), h);
// from jobapi2.h
inline HANDLE CreateJobObject(LPSECURITY_ATTRIBUTES lpJobAttributes, LPCWSTR lpName)
	assertl_reflect_as(auto h = ::CreateJobObjectW(lpJobAttributes, lpName), h);
// OpenJobObject
inline HANDLE OpenJobObject(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName)
	assertl_reflect_as(auto h = ::OpenJobObjectA(dwDesiredAccess, bInheritHandle, lpName), h);
// from jobapi2.h
inline HANDLE OpenJobObject(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName)
	assertl_reflect_as(auto h = ::OpenJobObjectW(dwDesiredAccess, bInheritHandle, lpName), h);
// FindFirstVolume
inline HANDLE FindFirstVolume(LPSTR lpszVolumeName, DWORD cchBufferLength)
	assertl_reflect_as(auto h = ::FindFirstVolumeA(lpszVolumeName, cchBufferLength); h != INVALID_HANDLE_VALUE, h);
// from fileapi.h
inline HANDLE FindFirstVolume(LPWSTR lpszVolumeName, DWORD cchBufferLength)
	assertl_reflect_as(auto h = ::FindFirstVolumeW(lpszVolumeName, cchBufferLength); h != INVALID_HANDLE_VALUE, h);
// FindNextVolume
inline void FindNextVolume(HANDLE hFindVolume, LPSTR lpszVolumeName, DWORD cchBufferLength)
	assertl_reflect_as(::FindNextVolumeA(hFindVolume, lpszVolumeName, cchBufferLength));
// from fileapi.h
inline void FindNextVolume(HANDLE hFindVolume, LPWSTR lpszVolumeName, DWORD cchBufferLength)
	assertl_reflect_as(::FindNextVolumeW(hFindVolume, lpszVolumeName, cchBufferLength));
// FindFirstVolumeMountPoint
inline HANDLE FindFirstVolumeMountPoint(LPCSTR lpszRootPathName, LPSTR lpszVolumeMountPoint, DWORD cchBufferLength)
	assertl_reflect_as(auto h = ::FindFirstVolumeMountPointA(lpszRootPathName, lpszVolumeMountPoint, cchBufferLength); h != INVALID_HANDLE_VALUE, h);
inline HANDLE FindFirstVolumeMountPoint(LPCWSTR lpszRootPathName, LPWSTR lpszVolumeMountPoint, DWORD cchBufferLength)
	assertl_reflect_as(auto h = ::FindFirstVolumeMountPointW(lpszRootPathName, lpszVolumeMountPoint, cchBufferLength); h != INVALID_HANDLE_VALUE, h);
// FindNextVolumeMountPoint
inline void FindNextVolumeMountPoint(HANDLE hFindVolumeMountPoint, LPSTR lpszVolumeMountPoint, DWORD cchBufferLength)
	assertl_reflect_as(::FindNextVolumeMountPointA(hFindVolumeMountPoint, lpszVolumeMountPoint, cchBufferLength));
inline void FindNextVolumeMountPoint(HANDLE hFindVolumeMountPoint, LPWSTR lpszVolumeMountPoint, DWORD cchBufferLength)
	assertl_reflect_as(::FindNextVolumeMountPointW(hFindVolumeMountPoint, lpszVolumeMountPoint, cchBufferLength));
// FindVolumeMountPointClose
// SetVolumeMountPoint
inline void SetVolumeMountPoint(LPCSTR lpszVolumeMountPoint, LPCSTR lpszVolumeName)
	assertl_reflect_as(::SetVolumeMountPointA(lpszVolumeMountPoint, lpszVolumeName));
inline void SetVolumeMountPoint(LPCWSTR lpszVolumeMountPoint, LPCWSTR lpszVolumeName)
	assertl_reflect_as(::SetVolumeMountPointW(lpszVolumeMountPoint, lpszVolumeName));
// DeleteVolumeMountPoint
inline void DeleteVolumeMountPoint(LPCSTR lpszVolumeMountPoint)
	assertl_reflect_as(::DeleteVolumeMountPointA(lpszVolumeMountPoint));
// from fileapi.h
inline void DeleteVolumeMountPoint(LPCWSTR lpszVolumeMountPoint)
	assertl_reflect_as(::DeleteVolumeMountPointW(lpszVolumeMountPoint));
// GetVolumeNameForVolumeMountPoint
inline void GetVolumeNameForVolumeMountPoint(LPCSTR lpszVolumeMountPoint, LPSTR lpszVolumeName, DWORD cchBufferLength)
	assertl_reflect_as(::GetVolumeNameForVolumeMountPointA(lpszVolumeMountPoint, lpszVolumeName, cchBufferLength));
// from fileapi.h
inline void GetVolumeNameForVolumeMountPoint(LPCWSTR lpszVolumeMountPoint, LPWSTR lpszVolumeName, DWORD cchBufferLength)
	assertl_reflect_as(::GetVolumeNameForVolumeMountPointW(lpszVolumeMountPoint, lpszVolumeName, cchBufferLength));
// GetVolumePathName
inline void GetVolumePathName(LPCSTR lpszFileName, LPSTR lpszVolumePathName, DWORD cchBufferLength)
	assertl_reflect_as(::GetVolumePathNameA(lpszFileName, lpszVolumePathName, cchBufferLength));
// from fileapi.h
inline void GetVolumePathName(LPCWSTR lpszFileName, LPWSTR lpszVolumePathName, DWORD cchBufferLength)
	assertl_reflect_as(::GetVolumePathNameW(lpszFileName, lpszVolumePathName, cchBufferLength));
// GetVolumePathNamesForVolumeName
inline void GetVolumePathNamesForVolumeName(LPCSTR lpszVolumeName, LPSTR lpszVolumePathNames, DWORD cchBufferLength,
											LPDWORD lpcchReturnLength)
	assertl_reflect_as(::GetVolumePathNamesForVolumeNameA(lpszVolumeName, lpszVolumePathNames, cchBufferLength,
														  lpcchReturnLength));
// from fileapi.h
inline void GetVolumePathNamesForVolumeName(LPCWSTR lpszVolumeName, LPWSTR lpszVolumePathNames, DWORD cchBufferLength,
											LPDWORD lpcchReturnLength)
	assertl_reflect_as(::GetVolumePathNamesForVolumeNameW(lpszVolumeName, lpszVolumePathNames, cchBufferLength,
														  lpcchReturnLength));
// CreateActCtx
inline HANDLE CreateActCtx(PCACTCTXA pActCtx)
	assertl_reflect_as(auto h = ::CreateActCtxA(pActCtx); h != INVALID_HANDLE_VALUE, h);
inline HANDLE CreateActCtx(PCACTCTXW pActCtx)
	assertl_reflect_as(auto h = ::CreateActCtxW(pActCtx); h != INVALID_HANDLE_VALUE, h);
// AddRefActCtx
// ReleaseActCtx
// ZombifyActCtx
// ActivateActCtx
// DeactivateActCtx
// GetCurrentActCtx
// FindActCtxSectionString
inline void FindActCtxSectionString(DWORD dwFlags, const GUID *lpExtensionGuid, ULONG ulSectionId,
									LPCSTR lpStringToFind, PACTCTX_SECTION_KEYED_DATA pData)
	assertl_reflect_as(::FindActCtxSectionStringA(dwFlags, lpExtensionGuid, ulSectionId, lpStringToFind, pData));
inline void FindActCtxSectionString(DWORD dwFlags, const GUID *lpExtensionGuid, ULONG ulSectionId,
									LPCWSTR lpStringToFind, PACTCTX_SECTION_KEYED_DATA pData)
	assertl_reflect_as(::FindActCtxSectionStringW(dwFlags, lpExtensionGuid, ulSectionId, lpStringToFind, pData));
// FindActCtxSectionGuid
// QueryActCtx
inline void QueryActCtx(DWORD dwFlags, HANDLE hActCtx,
						PVOID pvSubInstance, ULONG ulInfoClass,
						PVOID pvBuffer, SIZE_T cbBuffer, SIZE_T *pcbWrittenOrRequired)
	assertl_reflect_as(::QueryActCtxW(dwFlags, hActCtx,
									  pvSubInstance, ulInfoClass,
									  pvBuffer, cbBuffer, pcbWrittenOrRequired));
// WTSGetActiveConsoleSessionId
// GetActiveProcessorGroupCount
// GetMaximumProcessorGroupCount
// GetActiveProcessorCount
// GetMaximumProcessorCount
// GetNumaProcessorNode
// GetNumaNodeNumberFromHandle
// GetNumaProcessorNodeEx
// GetNumaNodeProcessorMask
// GetNumaAvailableMemoryNode
// GetNumaAvailableMemoryNodeEx
// GetNumaProximityNode
// RegisterApplicationRecoveryCallback
// UnregisterApplicationRecoveryCallback
// RegisterApplicationRestart
// UnregisterApplicationRestart
// GetApplicationRecoveryCallback
// GetApplicationRestartSettings
// ApplicationRecoveryInProgress
// ApplicationRecoveryFinished
// GetFileInformationByHandleEx
// GetFileInformationByName
// OpenFileById
// CreateSymbolicLink
inline void CreateSymbolicLink(LPCSTR lpSymlinkFileName, LPCSTR lpTargetFileName, DWORD dwFlags)
	assertl_reflect_as(::CreateSymbolicLinkA(lpSymlinkFileName, lpTargetFileName, dwFlags));
inline void CreateSymbolicLink(LPCWSTR lpSymlinkFileName, LPCWSTR lpTargetFileName, DWORD dwFlags)
	assertl_reflect_as(::CreateSymbolicLinkW(lpSymlinkFileName, lpTargetFileName, dwFlags));
// QueryActCtxSettings
inline void QueryActCtxSettings(DWORD dwFlags, HANDLE hActCtx,
								PCWSTR settingsNameSpace, PCWSTR settingName,
								PWSTR pvBuffer, SIZE_T dwBuffer, SIZE_T *pdwWrittenOrRequired)
	assertl_reflect_as(::QueryActCtxSettingsW(dwFlags, hActCtx,
											  settingsNameSpace, settingName,
											  pvBuffer, dwBuffer, pdwWrittenOrRequired));
// CreateSymbolicLinkTransacted
inline void CreateSymbolicLink(LPCSTR lpSymlinkFileName, LPCSTR lpTargetFileName, DWORD dwFlags,
							   HANDLE hTransaction)
	assertl_reflect_as(::CreateSymbolicLinkTransactedA(lpSymlinkFileName, lpTargetFileName, dwFlags, hTransaction));
inline void CreateSymbolicLinkTransacted(LPCWSTR lpSymlinkFileName, LPCWSTR lpTargetFileName, DWORD dwFlags,
										 HANDLE hTransaction)
	assertl_reflect_as(::CreateSymbolicLinkTransactedW(lpSymlinkFileName, lpTargetFileName, dwFlags, hTransaction));
// AddSecureMemoryCacheCallback
// RemoveSecureMemoryCacheCallback
// CopyContext
// InitializeContext
// InitializeContext2
// GetEnabledXStateFeatures
// GetXStateFeaturesMask
// LocateXStateFeature
// SetXStateFeaturesMask
// GetThreadEnabledXStateFeatures
// EnableProcessOptionalXStateFeatures
// EnableThreadProfiling
// DisableThreadProfiling
// QueryThreadProfiling
// ReadThreadProfilingData
// DestroyThreadpoolEnvironment
// InitializeThreadpoolEnvironment
// InterlockedExchangeSubtract
// SetThreadpoolCallbackCleanupGroup
// SetThreadpoolCallbackLibrary
// SetThreadpoolCallbackPersistent
// SetThreadpoolCallbackPool
// SetThreadpoolCallbackPriority
// SetThreadpoolCallbackRunsLong
#pragma endregion

#pragma region WinUser.h
// wvsprintf - Deprecated
// wsprintf - Deprecated
// LoadKeyboardLayout
inline HKL LoadKeyboardLayout(LPCSTR pwszKLID, UINT Flags)
	assertl_reflect_as(auto h = ::LoadKeyboardLayoutA(pwszKLID, Flags), h);
inline HKL LoadKeyboardLayout(LPCWSTR pwszKLID, UINT Flags)
	assertl_reflect_as(auto h = ::LoadKeyboardLayoutW(pwszKLID, Flags), h);
// ActivateKeyboardLayout
inline HKL ActivateKeyboardLayout(HKL hkl, UINT Flags)
	assertl_reflect_as(auto h = ::ActivateKeyboardLayout(hkl, Flags), h);
// ToUnicodeEx
inline int ToUnicodeEx(UINT wVirtKey, UINT wScanCode, CONST BYTE *lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags, HKL dwhkl)
	reflect_as(::ToUnicodeEx(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags, dwhkl));
// UnloadKeyboardLayout
inline void UnloadKeyboardLayout(HKL hkl)
	assertl_reflect_as(::UnloadKeyboardLayout(hkl));
// GetKeyboardLayoutName
inline void GetKeyboardLayoutName(LPSTR pwszKLID)
	assertl_reflect_as(::GetKeyboardLayoutNameA(pwszKLID));
inline void GetKeyboardLayoutName(LPWSTR pwszKLID)
	assertl_reflect_as(::GetKeyboardLayoutNameW(pwszKLID));
// GetKeyboardLayoutList
inline int GetKeyboardLayoutList(int nBuff, HKL FAR *lpList)
	assertl_reflect_as(auto h = ::GetKeyboardLayoutList(nBuff, lpList), h);
// GetKeyboardLayout
inline HKL GetKeyboardLayout(DWORD idThread)
	reflect_as(::GetKeyboardLayout(idThread));
// GetMouseMovePointsEx
inline int GetMouseMovePointsEx(UINT cbSize, LPMOUSEMOVEPOINT lppt, LPMOUSEMOVEPOINT lpptBuf, int nBufPoints, DWORD resolution)
	assertl_reflect_as(auto h = ::GetMouseMovePointsEx(cbSize, lppt, lpptBuf, nBufPoints, resolution), h);
// CreateDesktop
inline HDESK CreateDesktop(LPCSTR lpszDesktop, LPCSTR lpszDevice, DEVMODEA* pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
	assertl_reflect_as(auto h = ::CreateDesktopA(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa), h);
inline HDESK CreateDesktop(LPCWSTR lpszDesktop, LPCWSTR lpszDevice, DEVMODEW* pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
	assertl_reflect_as(auto h = ::CreateDesktopW(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa), h);
// CreateDesktopEx
inline HDESK CreateDesktopEx(LPCSTR lpszDesktop, LPCSTR lpszDevice, DEVMODEA* pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
	assertl_reflect_as(auto h = ::CreateDesktopExA(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid), h);
inline HDESK CreateDesktopEx(LPCWSTR lpszDesktop, LPCWSTR lpszDevice, DEVMODEW* pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
	assertl_reflect_as(auto h = ::CreateDesktopExW(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid), h);
// OpenDesktop
inline HDESK OpenDesktop(LPCSTR lpszDesktop, DWORD dwFlags, BOOL fInherit, ACCESS_MASK dwDesiredAccess)
	assertl_reflect_as(auto h = ::OpenDesktopA(lpszDesktop, dwFlags, fInherit, dwDesiredAccess), h);
inline HDESK OpenDesktop(LPCWSTR lpszDesktop, DWORD dwFlags, BOOL fInherit, ACCESS_MASK dwDesiredAccess)
	assertl_reflect_as(auto h = ::OpenDesktopW(lpszDesktop, dwFlags, fInherit, dwDesiredAccess), h);
// OpenInputDesktop
inline HDESK OpenInputDesktop(DWORD dwFlags, BOOL fInherit, ACCESS_MASK dwDesiredAccess)
	assertl_reflect_as(auto h = ::OpenInputDesktop(dwFlags, fInherit, dwDesiredAccess), h);
// EnumDesktops
inline void EnumDesktops(HWINSTA hwinsta, DESKTOPENUMPROCA lpEnumFunc, LPARAM lParam)
	assertl_reflect_as(::EnumDesktopsA(hwinsta, lpEnumFunc, lParam));
inline void EnumDesktops(HWINSTA hwinsta, DESKTOPENUMPROCW lpEnumFunc, LPARAM lParam)
	assertl_reflect_as(::EnumDesktopsW(hwinsta, lpEnumFunc, lParam));
// EnumDesktopWindows
inline void EnumDesktopWindows(HDESK hDesktop, WNDENUMPROC lpfn, LPARAM lParam)
	assertl_reflect_as(::EnumDesktopWindows(hDesktop, lpfn, lParam));
// SwitchDesktop
inline void SwitchDesktop(HDESK hDesktop)
	assertl_reflect_as(::SwitchDesktop(hDesktop));
// SetThreadDesktop
inline void SetThreadDesktop(HDESK hDesktop)
	assertl_reflect_as(::SetThreadDesktop(hDesktop));
// CloseDesktop
inline void CloseDesktop(HDESK hDesktop)
	assertl_reflect_as(::CloseDesktop(hDesktop));
// GetThreadDesktop
inline HDESK GetThreadDesktop(DWORD dwThreadId)
	assertl_reflect_as(auto h = ::GetThreadDesktop(dwThreadId), h);
// CreateWindowStation
inline HWINSTA CreateWindowStation(LPCSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
	assertl_reflect_as(auto h = ::CreateWindowStationA(lpwinsta, dwFlags, dwDesiredAccess, lpsa), h);
inline HWINSTA CreateWindowStation(LPCWSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
	assertl_reflect_as(auto h = ::CreateWindowStationW(lpwinsta, dwFlags, dwDesiredAccess, lpsa), h);
// OpenWindowStation
inline HWINSTA OpenWindowStation(LPCSTR lpszWinSta, BOOL fInherit, ACCESS_MASK dwDesiredAccess)
	assertl_reflect_as(auto h = ::OpenWindowStationA(lpszWinSta, fInherit, dwDesiredAccess), h);
inline HWINSTA OpenWindowStation(LPCWSTR lpszWinSta, BOOL fInherit, ACCESS_MASK dwDesiredAccess)
	assertl_reflect_as(auto h = ::OpenWindowStationW(lpszWinSta, fInherit, dwDesiredAccess), h);
// EnumWindowStations
inline void EnumWindowStations(WINSTAENUMPROCA lpEnumFunc, LPARAM lParam)
	assertl_reflect_as(::EnumWindowStationsA(lpEnumFunc, lParam));
inline void EnumWindowStations(WINSTAENUMPROCW lpEnumFunc, LPARAM lParam)
	assertl_reflect_as(::EnumWindowStationsW(lpEnumFunc, lParam));
// CloseWindowStation
inline void CloseWindowStation(HWINSTA hWinSta)
	assertl_reflect_as(::CloseWindowStation(hWinSta));
// SetProcessWindowStation
inline void SetProcessWindowStation(HWINSTA hWinSta)
	assertl_reflect_as(::SetProcessWindowStation(hWinSta));
// GetProcessWindowStation
inline HWINSTA GetProcessWindowStation()
	assertl_reflect_as(auto h = ::GetProcessWindowStation(), h);
// SetUserObjectSecurity
inline void SetUserObjectSecurity(HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID)
	assertl_reflect_as(::SetUserObjectSecurity(hObj, pSIRequested, pSID));
// GetUserObjectSecurity
inline void GetUserObjectSecurity(HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID, DWORD nLength, LPDWORD lpnLengthNeeded)
	assertl_reflect_as(::GetUserObjectSecurity(hObj, pSIRequested, pSID, nLength, lpnLengthNeeded));
// GetUserObjectInformation
template<bool IsUnicode = WX::IsUnicode>
inline void GetUserObjectInformation(HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength, LPDWORD lpnLengthNeeded) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GetUserObjectInformationW(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded))
	else assertl_reflect_as(::GetUserObjectInformationA(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded))
}
// SetUserObjectInformation
template<bool IsUnicode = WX::IsUnicode>
inline void SetUserObjectInformation(HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength) {
	if_c (IsUnicode)
		 assertl_reflect_as(::SetUserObjectInformationW(hObj, nIndex, pvInfo, nLength))
	else assertl_reflect_as(::SetUserObjectInformationA(hObj, nIndex, pvInfo, nLength))
}
inline bool IsHungAppWindow(HWND hwnd)
	reflect_as(::IsHungAppWindow(hwnd));
// DisableProcessWindowsGhosting
inline void DisableProcessWindowsGhosting()
	reflect_to(::DisableProcessWindowsGhosting());
// RegisterWindowMessage
inline UINT RegisterWindowMessage(LPCSTR lpString)
	assertl_reflect_as(auto h = ::RegisterWindowMessageA(lpString), h);
inline UINT RegisterWindowMessage(LPCWSTR lpString)
	assertl_reflect_as(auto h = ::RegisterWindowMessageW(lpString), h);
// TrackMouseEvent
inline void TrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack)
	assertl_reflect_as(::TrackMouseEvent(lpEventTrack));
// DrawEdge
inline void DrawEdge(HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags)
	assertl_reflect_as(::DrawEdge(hdc, qrc, edge, grfFlags));
// DrawFrameControl
inline void DrawFrameControl(HDC hdc, LPRECT lprc, UINT uType, UINT uState)
	assertl_reflect_as(::DrawFrameControl(hdc, lprc, uType, uState));
// DrawCaption
inline void DrawCaption(HWND hwnd, HDC hdc, CONST RECT * lprect, UINT flags)
	assertl_reflect_as(::DrawCaption(hwnd, hdc, lprect, flags));
// DrawAnimatedRects
inline void DrawAnimatedRects(HWND hwnd, int idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo)
	assertl_reflect_as(::DrawAnimatedRects(hwnd, idAni, lprcFrom, lprcTo));
// GetMessage
template<bool IsUnicode = WX::IsUnicode>
inline bool GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::GetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax); h >= 0, h)
	else assertl_reflect_as(auto h = ::GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax); h >= 0, h)
}
// TranslateMessage
inline bool TranslateMessage(CONST MSG *lpMsg)
	reflect_as(::TranslateMessage(lpMsg));
// DispatchMessage
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT DispatchMessage(CONST MSG *lpMsg) {
	if_c (IsUnicode)
		 reflect_as(::DispatchMessageW(lpMsg))
	else reflect_as(::DispatchMessageA(lpMsg))
}
// SetMessageQueue
// PeekMessage
template<bool IsUnicode = WX::IsUnicode>
inline bool PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
	if_c (IsUnicode)
		 reflect_as(::PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
	else reflect_as(::PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg))
}
// RegisterHotKey
inline void RegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk)
	assertl_reflect_as(::RegisterHotKey(hWnd, id, fsModifiers, vk));
// UnregisterHotKey
inline void UnregisterHotKey(HWND hWnd, int id)
	assertl_reflect_as(::UnregisterHotKey(hWnd, id));
// ExitWindowsEx
inline void ExitWindowsEx(UINT uFlags, DWORD dwReason)
	assertl_reflect_as(::ExitWindowsEx(uFlags, dwReason));
// SwapMouseButton
inline bool SwapMouseButton(BOOL fSwap)
	reflect_as(::SwapMouseButton(fSwap));
// GetMessagePos
inline DWORD GetMessagePos()
	reflect_as(::GetMessagePos());
// GetMessageTime
inline LONG GetMessageTime()
	reflect_as(::GetMessageTime());
// GetMessageExtraInfo
inline LPARAM GetMessageExtraInfo()
	reflect_as(::GetMessageExtraInfo());
// GetUnpredictedMessagePos
inline DWORD GetUnpredictedMessagePos()
	reflect_as(::GetUnpredictedMessagePos());
// IsWow64Message
inline bool IsWow64Message()
	reflect_as(::IsWow64Message());
// SetMessageExtraInfo
inline LPARAM SetMessageExtraInfo(LPARAM lParam)
	reflect_as(::SetMessageExtraInfo(lParam));
// SendMessage
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::SendMessageW(hWnd, Msg, wParam, lParam), h)
	else nt_assertl_reflect_to(auto h = ::SendMessageA(hWnd, Msg, wParam, lParam), h)
}
// SendMessageTimeout
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT SendMessageTimeout(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::SendMessageTimeoutW(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult), h)
	else nt_assertl_reflect_to(auto h = ::SendMessageTimeoutA(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult), h)
}
// SendNotifyMessage
template<bool IsUnicode = WX::IsUnicode>
inline void SendNotifyMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 assertl_reflect_as(::SendNotifyMessageW(hWnd, Msg, wParam, lParam))
	else assertl_reflect_as(::SendNotifyMessageA(hWnd, Msg, wParam, lParam))
}
// SendMessageCallback
template<bool IsUnicode = WX::IsUnicode>
inline void SendMessageCallback(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, SENDASYNCPROC lpResultCallBack, ULONG_PTR dwData) {
	if_c (IsUnicode)
		 assertl_reflect_as(::SendMessageCallbackW(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData))
	else assertl_reflect_as(::SendMessageCallbackA(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData))
}
// BroadcastSystemMessageEx
template<bool IsUnicode = WX::IsUnicode>
inline long BroadcastSystemMessageEx(DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam, PBSMINFO pbsmInfo) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::BroadcastSystemMessageExW(flags, lpInfo, Msg, wParam, lParam, pbsmInfo), h)
	else assertl_reflect_as(auto h = ::BroadcastSystemMessageExA(flags, lpInfo, Msg, wParam, lParam, pbsmInfo), h)
}
// BroadcastSystemMessage
template<bool IsUnicode = WX::IsUnicode>
inline long BroadcastSystemMessage(DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::BroadcastSystemMessageW(flags, lpInfo, Msg, wParam, lParam), h)
	else assertl_reflect_as(auto h = ::BroadcastSystemMessageA(flags, lpInfo, Msg, wParam, lParam), h)
}
// RegisterDeviceNotification
template<bool IsUnicode = WX::IsUnicode>
inline HDEVNOTIFY RegisterDeviceNotification(HANDLE hRecipient, LPVOID NotificationFilter, DWORD Flags) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::RegisterDeviceNotificationW(hRecipient, NotificationFilter, Flags), h)
	else assertl_reflect_as(auto h = ::RegisterDeviceNotificationA(hRecipient, NotificationFilter, Flags), h)
}
// UnregisterDeviceNotification
inline void UnregisterDeviceNotification(HDEVNOTIFY Handle)
	assertl_reflect_as(::UnregisterDeviceNotification(Handle));
// RegisterPowerSettingNotification
inline HPOWERNOTIFY RegisterPowerSettingNotification(HANDLE hRecipient, LPCGUID PowerSettingGuid, DWORD Flags)
	assertl_reflect_as(auto h = ::RegisterPowerSettingNotification(hRecipient, PowerSettingGuid, Flags), h);
// UnregisterPowerSettingNotification
inline void UnregisterPowerSettingNotification(HPOWERNOTIFY Handle)
	assertl_reflect_as(::UnregisterPowerSettingNotification(Handle));
// RegisterSuspendResumeNotification
inline HPOWERNOTIFY RegisterSuspendResumeNotification(HANDLE hRecipient, DWORD Flags)
	assertl_reflect_as(auto h = ::RegisterSuspendResumeNotification(hRecipient, Flags), h);
// UnregisterSuspendResumeNotification
inline void UnregisterSuspendResumeNotification(HPOWERNOTIFY Handle)
	assertl_reflect_as(::UnregisterSuspendResumeNotification(Handle));
// PostMessage
template<bool IsUnicode = WX::IsUnicode>
inline void PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 assertl_reflect_as(::PostMessageW(hWnd, Msg, wParam, lParam))
	else assertl_reflect_as(::PostMessageA(hWnd, Msg, wParam, lParam))
}
// PostThreadMessage
template<bool IsUnicode = WX::IsUnicode>
inline void PostThreadMessage(DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 assertl_reflect_as(::PostThreadMessageW(idThread, Msg, wParam, lParam))
	else assertl_reflect_as(::PostThreadMessageA(idThread, Msg, wParam, lParam))
}
// AttachThreadInput
inline void AttachThreadInput(DWORD idAttach, DWORD idAttachTo, BOOL fAttach)
	assertl_reflect_as(::AttachThreadInput(idAttach, idAttachTo, fAttach));
// ReplyMessage
inline bool ReplyMessage(LRESULT lResult)
	reflect_as(::ReplyMessage(lResult));
// WaitMessage
inline void WaitMessage()
	assertl_reflect_as(::WaitMessage());
// WaitForInputIdle
inline DWORD WaitForInputIdle(HANDLE hProcess, DWORD dwMilliseconds)
	assertl_reflect_as(auto h = ::WaitForInputIdle(hProcess, dwMilliseconds), h);
// DefWindowProc
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 reflect_as(::DefWindowProcW(hWnd, Msg, wParam, lParam))
	else reflect_as(::DefWindowProcA(hWnd, Msg, wParam, lParam))
}
// PostQuitMessage
inline void PostQuitMessage(int nExitCode)
	reflect_to(::PostQuitMessage(nExitCode));
// CallWindowProc
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT CallWindowProc(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 reflect_as(::CallWindowProcW(lpPrevWndFunc, hWnd, Msg, wParam, lParam))
	else reflect_as(::CallWindowProcA(lpPrevWndFunc, hWnd, Msg, wParam, lParam))
}
// InSendMessage
inline bool InSendMessage()
	reflect_as(::InSendMessage());
// InSendMessageEx
inline DWORD InSendMessageEx(LPVOID lpReserved)
	reflect_as(::InSendMessageEx(lpReserved));
// GetDoubleClickTime
inline UINT GetDoubleClickTime()
	reflect_as(::GetDoubleClickTime());
// SetDoubleClickTime
inline void SetDoubleClickTime(UINT uMillisecond)
	assertl_reflect_as(::SetDoubleClickTime(uMillisecond));
// RegisterClass
inline ATOM RegisterClass(CONST WNDCLASSA *lpWndClass)
	assertl_reflect_as(auto h = ::RegisterClassA(lpWndClass), h);
inline ATOM RegisterClass(CONST WNDCLASSW *lpWndClass)
	assertl_reflect_as(auto h = ::RegisterClassW(lpWndClass), h);
// UnregisterClass
inline void UnregisterClass(LPCSTR lpClassName, HINSTANCE hInstance)
	assertl_reflect_as(::UnregisterClassA(lpClassName, hInstance));
inline void UnregisterClass(LPCWSTR lpClassName, HINSTANCE hInstance)
	assertl_reflect_as(::UnregisterClassW(lpClassName, hInstance));
// GetClassInfo
inline void GetClassInfo(HINSTANCE hInstance, LPCSTR lpClassName, LPWNDCLASSA lpWndClass)
	assertl_reflect_as(::GetClassInfoA(hInstance, lpClassName, lpWndClass));
inline void GetClassInfo(HINSTANCE hInstance, LPCWSTR lpClassName, LPWNDCLASSW lpWndClass)
	assertl_reflect_as(::GetClassInfoW(hInstance, lpClassName, lpWndClass));
// RegisterClassEx
inline ATOM RegisterClass(CONST WNDCLASSEXA *lpcWndClass)
	assertl_reflect_as(auto h = ::RegisterClassExA(lpcWndClass), h);
inline ATOM RegisterClass(CONST WNDCLASSEXW *lpcWndClass)
	assertl_reflect_as(auto h = ::RegisterClassExW(lpcWndClass), h);
// GetClassInfoEx
inline void GetClassInfoEx(HINSTANCE hInstance, LPCSTR lpszClass, LPWNDCLASSEXA lpwcx)
	assertl_reflect_as(::GetClassInfoExA(hInstance, lpszClass, lpwcx));
inline void GetClassInfoEx(HINSTANCE hInstance, LPCWSTR lpszClass, LPWNDCLASSEXW lpwcx)
	assertl_reflect_as(::GetClassInfoExW(hInstance, lpszClass, lpwcx));
// CreateWindowEx
inline HWND CreateWindow(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
	assertl_reflect_as(auto h = ::CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam), h);
inline HWND CreateWindow(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
	assertl_reflect_as(auto h = ::CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam), h);
inline bool IsWindow(HWND hWnd)
	reflect_as(::IsWindow(hWnd));
// IsMenu
inline bool IsMenu(HMENU hMenu)
	reflect_as(::IsMenu(hMenu));
// IsChild
inline bool IsChild(HWND hWndParent, HWND hWnd)
	reflect_as(::IsChild(hWndParent, hWnd));
inline void DestroyWindow(HWND hWnd)
	assertl_reflect_as(::DestroyWindow(hWnd));
inline bool ShowWindow(HWND hWnd, int nCmdShow)
	reflect_as(::ShowWindow(hWnd, nCmdShow));
inline void AnimateWindow(HWND hWnd, DWORD dwTime, DWORD dwFlags)
	assertl_reflect_as(::AnimateWindow(hWnd, dwTime, dwFlags));
inline void UpdateLayeredWindow(HWND hWnd, HDC hdcDst, POINT* pptDst, SIZE* psize, HDC hdcSrc, POINT* pptSrc, COLORREF crKey, BLENDFUNCTION* pblend, DWORD dwFlags)
	assertl_reflect_as(::UpdateLayeredWindow(hWnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags));
// UpdateLayeredWindowIndirect
inline void UpdateLayeredWindowIndirect(HWND hWnd, const UPDATELAYEREDWINDOWINFO* pULWInfo)
	assertl_reflect_as(::UpdateLayeredWindowIndirect(hWnd, pULWInfo));
// GetLayeredWindowAttributes
inline void GetLayeredWindowAttributes(HWND hwnd, COLORREF* pcrKey, BYTE* pbAlpha, DWORD* pdwFlags)
	assertl_reflect_as(::GetLayeredWindowAttributes(hwnd, pcrKey, pbAlpha, pdwFlags));
inline bool PrintWindow(HWND hwnd, HDC hdcBlt, UINT nFlags)
	reflect_as(::PrintWindow(hwnd, hdcBlt, nFlags));
// SetLayeredWindowAttributes
inline void SetLayeredWindowAttributes(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
	assertl_reflect_as(::SetLayeredWindowAttributes(hwnd, crKey, bAlpha, dwFlags));
// ShowWindowAsync
inline bool ShowWindowAsync(HWND hWnd, int nCmdShow)
	reflect_as(::ShowWindowAsync(hWnd, nCmdShow));
inline bool FlashWindow(HWND hWnd, BOOL bInvert)
	reflect_as(::FlashWindow(hWnd, bInvert));
// FlashWindowEx
inline bool FlashWindow(PFLASHWINFO pfwi)
	reflect_as(::FlashWindowEx(pfwi));
// ShowOwnedPopups
inline void ShowOwnedPopups(HWND hWnd, BOOL fShow)
	assertl_reflect_as(::ShowOwnedPopups(hWnd, fShow));
// OpenIcon
inline void OpenIcon(HWND hWnd)
	assertl_reflect_as(::OpenIcon(hWnd));
inline void CloseWindow(HWND hWnd)
	assertl_reflect_as(::CloseWindow(hWnd));
inline void MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
	assertl_reflect_as(::MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint));
// SetWindowPos
inline void SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
	assertl_reflect_as(::SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags));
// GetWindowPlacement
inline void GetWindowPlacement(HWND hWnd, WINDOWPLACEMENT *lpwndpl)
	assertl_reflect_as(::GetWindowPlacement(hWnd, lpwndpl));
// SetWindowPlacement
inline void SetWindowPlacement(HWND hWnd, CONST WINDOWPLACEMENT *lpwndpl)
	assertl_reflect_as(::SetWindowPlacement(hWnd, lpwndpl));
// GetWindowDisplayAffinity
inline void GetWindowDisplayAffinity(HWND hWnd, DWORD* pdwAffinity)
	assertl_reflect_as(::GetWindowDisplayAffinity(hWnd, pdwAffinity));
// SetWindowDisplayAffinity
inline void SetWindowDisplayAffinity(HWND hWnd, DWORD dwAffinity)
	assertl_reflect_as(::SetWindowDisplayAffinity(hWnd, dwAffinity));
// BeginDeferWindowPos
inline HDWP BeginDeferWindowPos(int nNumWindows)
	assertl_reflect_as(auto h = ::BeginDeferWindowPos(nNumWindows), h);
// DeferWindowPos
inline HDWP DeferWindowPos(HDWP hWinPosInfo, HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
	assertl_reflect_as(auto h = ::DeferWindowPos(hWinPosInfo, hWnd, hWndInsertAfter, x, y, cx, cy, uFlags), h);
// EndDeferWindowPos
inline void EndDeferWindowPos(HDWP hWinPosInfo)
	assertl_reflect_as(::EndDeferWindowPos(hWinPosInfo));
// IsWindowVisible
inline bool IsWindowVisible(HWND hWnd)
	reflect_as(::IsWindowVisible(hWnd));
// IsIconic
inline bool IsIconic(HWND hWnd)
	reflect_as(::IsIconic(hWnd));
// AnyPopup
inline bool AnyPopup()
	reflect_as(::AnyPopup());
// BringWindowToTop
inline void BringWindowToTop(HWND hWnd)
	assertl_reflect_as(::BringWindowToTop(hWnd));
// IsZoomed
inline bool IsZoomed(HWND hWnd)
	reflect_as(::IsZoomed(hWnd));
// CreateDialogParam
inline HWND CreateDialog(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
	assertl_reflect_as(auto h = ::CreateDialogParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam), h);
inline HWND CreateDialog(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
	assertl_reflect_as(auto h = ::CreateDialogParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam), h);
// CreateDialogIndirectParam
template<bool IsUnicode = WX::IsUnicode>
inline HWND CreateDialog(HINSTANCE hInstance, LPCDLGTEMPLATE lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam), h)
	else assertl_reflect_as(auto h = ::CreateDialogIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam), h)
}
// DialogBoxParam
inline INT_PTR DialogBox(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
	nt_assertl_reflect_to(auto h = ::DialogBoxParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam), h);
inline INT_PTR DialogBox(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
	nt_assertl_reflect_to(auto h = ::DialogBoxParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam), h);
// DialogBoxIndirectParam
template<bool IsUnicode = WX::IsUnicode>
inline INT_PTR DialogBox(HINSTANCE hInstance, LPCDLGTEMPLATE hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::DialogBoxIndirectParamW(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam), h)
	else nt_assertl_reflect_to(auto h = ::DialogBoxIndirectParamA(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam), h)
}
// EndDialog
inline void EndDialog(HWND hDlg, INT_PTR nResult)
	assertl_reflect_as(::EndDialog(hDlg, nResult));
// GetDlgItem
inline HWND GetDlgItem(HWND hDlg, int nIDDlgItem)
	assertl_reflect_as(auto h = ::GetDlgItem(hDlg, nIDDlgItem), h);
// SetDlgItemInt
inline void SetDlgItemInt(HWND hDlg, int nIDDlgItem, UINT uValue, BOOL bSigned)
	assertl_reflect_as(::SetDlgItemInt(hDlg, nIDDlgItem, uValue, bSigned));
// GetDlgItemInt
inline UINT GetDlgItemInt(HWND hDlg, int nIDDlgItem, BOOL *lpTranslated, BOOL bSigned)
	assertl_reflect_as(auto h = ::GetDlgItemInt(hDlg, nIDDlgItem, lpTranslated, bSigned); h != !*lpTranslated, h);
// SetDlgItemText
inline void SetDlgItemText(HWND hDlg, int nIDDlgItem, LPCSTR lpString)
	assertl_reflect_as(::SetDlgItemTextA(hDlg, nIDDlgItem, lpString));
inline void SetDlgItemText(HWND hDlg, int nIDDlgItem, LPCWSTR lpString)
	assertl_reflect_as(::SetDlgItemTextW(hDlg, nIDDlgItem, lpString));
// GetDlgItemText
inline UINT GetDlgItemText(HWND hDlg, int nIDDlgItem, LPSTR lpString, int cchMax)
	assertl_reflect_as(auto h = ::GetDlgItemTextA(hDlg, nIDDlgItem, lpString, cchMax), h);
inline UINT GetDlgItemText(HWND hDlg, int nIDDlgItem, LPWSTR lpString, int cchMax)
	assertl_reflect_as(auto h = ::GetDlgItemTextW(hDlg, nIDDlgItem, lpString, cchMax), h);
// CheckDlgButton
inline void CheckDlgButton(HWND hDlg, int nIDButton, UINT uCheck)
	assertl_reflect_as(::CheckDlgButton(hDlg, nIDButton, uCheck));
// CheckRadioButton
inline void CheckRadioButton(HWND hDlg, int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
	assertl_reflect_as(::CheckRadioButton(hDlg, nIDFirstButton, nIDLastButton, nIDCheckButton));
// IsDlgButtonChecked
inline UINT IsDlgButtonChecked(HWND hDlg, int nIDButton)
	reflect_as(::IsDlgButtonChecked(hDlg, nIDButton));
// SendDlgItemMessage
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT SendDlgItemMessage(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, lParam), h)
	else nt_assertl_reflect_to(auto h = ::SendDlgItemMessageA(hDlg, nIDDlgItem, Msg, wParam, lParam), h)
}
// GetNextDlgGroupItem
inline HWND GetNextDlgGroupItem(HWND hDlg, HWND hCtl, BOOL bPrevious)
	assertl_reflect_as(auto h = ::GetNextDlgGroupItem(hDlg, hCtl, bPrevious), h);
// GetNextDlgTabItem
inline HWND GetNextDlgTabItem(HWND hDlg, HWND hCtl, BOOL bPrevious)
	assertl_reflect_as(auto h = ::GetNextDlgTabItem(hDlg, hCtl, bPrevious), h);
// GetDlgCtrlID
inline int GetDlgCtrlID(HWND hWnd)
	assertl_reflect_as(auto h = ::GetDlgCtrlID(hWnd), h);
// GetDialogBaseUnits
inline long GetDialogBaseUnits()
	reflect_as(::GetDialogBaseUnits());
// DefDlgProc
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT DefDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 reflect_as(::DefDlgProcW(hDlg, Msg, wParam, lParam))
	else reflect_as(::DefDlgProcA(hDlg, Msg, wParam, lParam))
}
// SetDialogControlDpiChangeBehavior
inline void SetDialogControlDpiChangeBehavior(HWND hWnd, DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS mask, DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS values)
	assertl_reflect_as(::SetDialogControlDpiChangeBehavior(hWnd, mask, values));
// GetDialogControlDpiChangeBehavior
inline DIALOG_CONTROL_DPI_CHANGE_BEHAVIORS GetDialogControlDpiChangeBehavior(HWND hWnd)
	assertl_reflect_as(auto h = ::GetDialogControlDpiChangeBehavior(hWnd), h);
// SetDialogDpiChangeBehavior
inline void SetDialogDpiChangeBehavior(HWND hDlg, DIALOG_DPI_CHANGE_BEHAVIORS mask, DIALOG_DPI_CHANGE_BEHAVIORS values)
	assertl_reflect_as(::SetDialogDpiChangeBehavior(hDlg, mask, values));
// GetDialogDpiChangeBehavior
inline DIALOG_DPI_CHANGE_BEHAVIORS GetDialogDpiChangeBehavior(HWND hDlg)
	assertl_reflect_as(auto h = ::GetDialogDpiChangeBehavior(hDlg), h);
// CallMsgFilter
template<bool IsUnicode = WX::IsUnicode>
inline bool CallMsgFilter(LPMSG lpMsg, int nCode) {
	if_c (IsUnicode)
		 reflect_as(::CallMsgFilterW(lpMsg, nCode))
	else reflect_as(::CallMsgFilterA(lpMsg, nCode))
}
// OpenClipboard
inline void OpenClipboard(HWND hWndNewOwner)
	assertl_reflect_as(::OpenClipboard(hWndNewOwner));
// CloseClipboard
inline void CloseClipboard()
	assertl_reflect_as(::CloseClipboard());
// GetClipboardSequenceNumber
inline DWORD GetClipboardSequenceNumber()
	reflect_as(::GetClipboardSequenceNumber());
// GetClipboardOwner
inline HWND GetClipboardOwner()
	assertl_reflect_as(auto h = ::GetClipboardOwner(), h);
// SetClipboardViewer
inline HWND SetClipboardViewer(HWND hWndNewViewer)
	assertl_reflect_as(auto h = ::SetClipboardViewer(hWndNewViewer), h);
// GetClipboardViewer
inline HWND GetClipboardViewer()
	assertl_reflect_as(auto h = ::GetClipboardViewer(), h);
// ChangeClipboardChain
inline bool ChangeClipboardChain(HWND hWndRemove, HWND hWndNewNext)
	reflect_as(::ChangeClipboardChain(hWndRemove, hWndNewNext));
// SetClipboardData
inline HANDLE SetClipboardData(UINT uFormat, HANDLE hMem)
	assertl_reflect_as(auto h = ::SetClipboardData(uFormat, hMem), h);
// GetClipboardData
inline HANDLE GetClipboardData(UINT uFormat)
	assertl_reflect_as(auto h = ::GetClipboardData(uFormat), h);
// GetClipboardMetadata
// RegisterClipboardFormat
inline UINT RegisterClipboardFormat(LPCSTR lpszFormat)
	reflect_as(::RegisterClipboardFormatA(lpszFormat));
inline UINT RegisterClipboardFormat(LPCWSTR lpszFormat)
	reflect_as(::RegisterClipboardFormatW(lpszFormat));
// CountClipboardFormats
inline int CountClipboardFormats()
	assertl_reflect_as(auto h = ::CountClipboardFormats(), h);
// EnumClipboardFormats
inline UINT EnumClipboardFormats(UINT format)
	assertl_reflect_as(auto h = ::EnumClipboardFormats(format), h);
// GetClipboardFormatName
inline int GetClipboardFormatName(UINT format, LPSTR lpszFormatName, int cchMaxCount)
	assertl_reflect_as(auto h = ::GetClipboardFormatNameA(format, lpszFormatName, cchMaxCount), h);
inline int GetClipboardFormatName(UINT format, LPWSTR lpszFormatName, int cchMaxCount)
	assertl_reflect_as(auto h = ::GetClipboardFormatNameW(format, lpszFormatName, cchMaxCount), h);
// EmptyClipboard
inline void EmptyClipboard()
	assertl_reflect_as(::EmptyClipboard());
// IsClipboardFormatAvailable
inline bool IsClipboardFormatAvailable(UINT format)
	reflect_as(::IsClipboardFormatAvailable(format));
// GetPriorityClipboardFormat
inline int GetPriorityClipboardFormat(UINT *paFormatPriorityList, int cFormats)
	assertl_reflect_as(auto h = ::GetPriorityClipboardFormat(paFormatPriorityList, cFormats), h);
inline HWND GetOpenClipboardWindow()
	assertl_reflect_as(auto h = ::GetOpenClipboardWindow(), h);
// AddClipboardFormatListener
inline void AddClipboardFormatListener(HWND hwnd)
	assertl_reflect_as(::AddClipboardFormatListener(hwnd));
// RemoveClipboardFormatListener
inline void RemoveClipboardFormatListener(HWND hwnd)
	assertl_reflect_as(::RemoveClipboardFormatListener(hwnd));
// GetUpdatedClipboardFormats
inline void GetUpdatedClipboardFormats(PUINT lpuiFormats, UINT cFormats, PUINT pcFormatsOut)
	assertl_reflect_as(::GetUpdatedClipboardFormats(lpuiFormats, cFormats, pcFormatsOut));
// CharToOem - Deprecated
// OemToChar - Deprecated
// CharToOemBuff - Deprecated
// OemToCharBuff - Deprecated
// CharUpper - Deprecated
// CharUpperBuff - Deprecated
// CharLower - Deprecated
// CharLowerBuff - Deprecated
// CharNext - Deprecated
// CharPrev - Deprecated
// CharNextExA
// CharPrevExA
// IsCharAlpha - Deprecated
// IsCharAlphaNumeric - Deprecated
// IsCharUpper - Deprecated
// IsCharLower - Deprecated
// SetFocus
inline HWND SetFocus(HWND hWnd)
	assertl_reflect_as(auto h = ::SetFocus(hWnd), h);
inline HWND GetActiveWindow()
	reflect_as(::GetActiveWindow());
// GetFocus
inline HWND GetFocus()
	reflect_as(::GetFocus());
// GetKBCodePage
inline UINT GetKBCodePage()
	reflect_as(::GetKBCodePage());
// GetKeyState
inline SHORT GetKeyState(int nVirtKey)
	reflect_as(::GetKeyState(nVirtKey));
// GetAsyncKeyState
inline SHORT GetAsyncKeyState(int vKey)
	reflect_as(::GetAsyncKeyState(vKey));
// GetKeyboardState
inline void GetKeyboardState(PBYTE lpKeyState)
	assertl_reflect_as(::GetKeyboardState(lpKeyState));
// SetKeyboardState
inline void SetKeyboardState(LPBYTE lpKeyState)
	assertl_reflect_as(::SetKeyboardState(lpKeyState));
// GetKeyNameText
inline int GetKeyNameText(LONG lParam, LPSTR lpString, int cchSize)
	assertl_reflect_as(auto h = ::GetKeyNameTextA(lParam, lpString, cchSize), h);
inline int GetKeyNameText(LONG lParam, LPWSTR lpString, int cchSize)
	assertl_reflect_as(auto h = ::GetKeyNameTextW(lParam, lpString, cchSize), h);
// GetKeyboardType
inline int GetKeyboardType(int nTypeFlag)
	nt_assertl_reflect_to(auto h = ::GetKeyboardType(nTypeFlag), h);
// ToAscii
inline int ToAscii(UINT uVirtKey, UINT uScanCode, CONST BYTE *lpKeyState, LPWORD lpChar, UINT uFlags)
	reflect_as(::ToAscii(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags));
// ToAsciiEx
inline int ToAsciiEx(UINT uVirtKey, UINT uScanCode, CONST BYTE *lpKeyState, LPWORD lpChar, UINT uFlags, HKL dwhkl)
	reflect_as(::ToAsciiEx(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags, dwhkl));
// ToUnicode
inline int ToUnicode(UINT wVirtKey, UINT wScanCode, CONST BYTE *lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags)
	reflect_as(::ToUnicode(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags));
// OemKeyScan
inline DWORD OemKeyScan(WORD wOemChar)
	reflect_as(::OemKeyScan(wOemChar));
// VkKeyScan
inline SHORT VkKeyScan(CHAR ch)
	reflect_as(::VkKeyScanA(ch));
inline SHORT VkKeyScan(WCHAR ch)
	reflect_as(::VkKeyScanW(ch));
// VkKeyScanEx
inline SHORT VkKeyScanEx(CHAR ch, HKL dwhkl)
	reflect_as(::VkKeyScanExA(ch, dwhkl));
inline SHORT VkKeyScanEx(WCHAR ch, HKL dwhkl)
	reflect_as(::VkKeyScanExW(ch, dwhkl));
// keybd_event
// mouse_event
// SendInput
inline UINT SendInput(UINT cInputs, LPINPUT pInputs, int cbSize)
	assertl_reflect_as(auto h = ::SendInput(cInputs, pInputs, cbSize), h);
// GetTouchInputInfo
inline void GetTouchInputInfo(HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize)
	assertl_reflect_as(::GetTouchInputInfo(hTouchInput, cInputs, pInputs, cbSize));
// CloseTouchInputHandle
inline void CloseTouchInputHandle(HTOUCHINPUT hTouchInput)
	assertl_reflect_as(::CloseTouchInputHandle(hTouchInput));
inline void RegisterTouchWindow(HWND hwnd, ULONG ulFlags)
	assertl_reflect_as(::RegisterTouchWindow(hwnd, ulFlags));
inline void UnregisterTouchWindow(HWND hwnd)
	assertl_reflect_as(::UnregisterTouchWindow(hwnd));
inline bool IsTouchWindow(HWND hwnd, PULONG pulFlags)
	reflect_as(::IsTouchWindow(hwnd, pulFlags));
// InitializeTouchInjection
inline void InitializeTouchInjection(UINT32 maxCount, DWORD dwMode)
	assertl_reflect_as(::InitializeTouchInjection(maxCount, dwMode));
// InjectTouchInput
inline void InjectTouchInput(UINT32 count, CONST POINTER_TOUCH_INFO *contacts)
	assertl_reflect_as(::InjectTouchInput(count, contacts));
// GetPointerType
inline void GetPointerType(UINT32 pointerId, POINTER_INPUT_TYPE *pointerType)
	assertl_reflect_as(::GetPointerType(pointerId, pointerType));
// GetPointerCursorId
inline void GetPointerCursorId(UINT32 pointerId, UINT32 *cursorId)
	assertl_reflect_as(::GetPointerCursorId(pointerId, cursorId));
// GetPointerInfo
inline void GetPointerInfo(UINT32 pointerId, POINTER_INFO *pointerInfo)
	assertl_reflect_as(::GetPointerInfo(pointerId, pointerInfo));
// GetPointerInfoHistory
inline void GetPointerInfoHistory(UINT32 pointerId, UINT32 *entriesCount, POINTER_INFO *pointerInfo)
	assertl_reflect_as(::GetPointerInfoHistory(pointerId, entriesCount, pointerInfo));
// GetPointerFrameInfo
inline void GetPointerFrameInfo(UINT32 pointerId, UINT32 *pointerCount, POINTER_INFO *pointerInfo)
	assertl_reflect_as(::GetPointerFrameInfo(pointerId, pointerCount, pointerInfo));
// GetPointerFrameInfoHistory
inline void GetPointerFrameInfoHistory(UINT32 pointerId, UINT32 *entriesCount, UINT32 *pointerCount, POINTER_INFO *pointerInfo)
	assertl_reflect_as(::GetPointerFrameInfoHistory(pointerId, entriesCount, pointerCount, pointerInfo));
// GetPointerTouchInfo
inline void GetPointerTouchInfo(UINT32 pointerId, POINTER_TOUCH_INFO *touchInfo)
	assertl_reflect_as(::GetPointerTouchInfo(pointerId, touchInfo));
// GetPointerTouchInfoHistory
inline void GetPointerTouchInfoHistory(UINT32 pointerId, UINT32 *entriesCount, POINTER_TOUCH_INFO *touchInfo)
	assertl_reflect_as(::GetPointerTouchInfoHistory(pointerId, entriesCount, touchInfo));
// GetPointerFrameTouchInfo
inline void GetPointerFrameTouchInfo(UINT32 pointerId, UINT32 *pointerCount, POINTER_TOUCH_INFO *touchInfo)
	assertl_reflect_as(::GetPointerFrameTouchInfo(pointerId, pointerCount, touchInfo));
// GetPointerFrameTouchInfoHistory
inline void GetPointerFrameTouchInfoHistory(UINT32 pointerId, UINT32 *entriesCount, UINT32 *pointerCount, POINTER_TOUCH_INFO *touchInfo)
	assertl_reflect_as(::GetPointerFrameTouchInfoHistory(pointerId, entriesCount, pointerCount, touchInfo));
// GetPointerPenInfo
inline void GetPointerPenInfo(UINT32 pointerId, POINTER_PEN_INFO *penInfo)
	assertl_reflect_as(::GetPointerPenInfo(pointerId, penInfo));
// GetPointerPenInfoHistory
inline void GetPointerPenInfoHistory(UINT32 pointerId, UINT32 *entriesCount, POINTER_PEN_INFO *penInfo)
	assertl_reflect_as(::GetPointerPenInfoHistory(pointerId, entriesCount, penInfo));
// GetPointerFramePenInfo
inline void GetPointerFramePenInfo(UINT32 pointerId, UINT32 *pointerCount, POINTER_PEN_INFO *penInfo)
	assertl_reflect_as(::GetPointerFramePenInfo(pointerId, pointerCount, penInfo));
// GetPointerFramePenInfoHistory
inline void GetPointerFramePenInfoHistory(UINT32 pointerId, UINT32 *entriesCount, UINT32 *pointerCount, POINTER_PEN_INFO *penInfo)
	assertl_reflect_as(::GetPointerFramePenInfoHistory(pointerId, entriesCount, pointerCount, penInfo));
// SkipPointerFrameMessages
inline void SkipPointerFrameMessages(UINT32 pointerId)
	assertl_reflect_as(::SkipPointerFrameMessages(pointerId));
// RegisterPointerInputTarget
inline void RegisterPointerInputTarget(HWND hwnd, POINTER_INPUT_TYPE pointerType)
	assertl_reflect_as(::RegisterPointerInputTarget(hwnd, pointerType));
// UnregisterPointerInputTarget
inline void UnregisterPointerInputTarget(HWND hwnd, POINTER_INPUT_TYPE pointerType)
	assertl_reflect_as(::UnregisterPointerInputTarget(hwnd, pointerType));
// RegisterPointerInputTargetEx
// UnregisterPointerInputTargetEx
#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
// CreateSyntheticPointerDevice
inline HSYNTHETICPOINTERDEVICE CreateSyntheticPointerDevice(POINTER_INPUT_TYPE pointerType, ULONG maxCount, POINTER_FEEDBACK_MODE mode)
	assertl_reflect_as(auto h = ::CreateSyntheticPointerDevice(pointerType, maxCount, mode), h);
// InjectSyntheticPointerInput
inline void InjectSyntheticPointerInput(HSYNTHETICPOINTERDEVICE device, CONST POINTER_TYPE_INFO* pointerInfo, UINT32 count)
	assertl_reflect_as(::InjectSyntheticPointerInput(device, pointerInfo, count));
// DestroySyntheticPointerDevice
inline void DestroySyntheticPointerDevice(HSYNTHETICPOINTERDEVICE device)
	reflect_to(::DestroySyntheticPointerDevice(device));
#endif
// EnableMouseInPointer
inline void EnableMouseInPointer(BOOL fEnable)
	assertl_reflect_as(::EnableMouseInPointer(fEnable));
// IsMouseInPointerEnabled
inline bool IsMouseInPointerEnabled()
	reflect_as(::IsMouseInPointerEnabled());
// EnableMouseInPointerForThread
inline void RegisterTouchHitTestingWindow(HWND hwnd, ULONG value)
	assertl_reflect_as(::RegisterTouchHitTestingWindow(hwnd, value));
// EvaluateProximityToRect
inline void EvaluateProximityToRect(const RECT *controlBoundingBox, const TOUCH_HIT_TESTING_INPUT *pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *pProximityEval)
	assertl_reflect_as(::EvaluateProximityToRect(controlBoundingBox, pHitTestingInput, pProximityEval));
// EvaluateProximityToPolygon
inline void EvaluateProximityToPolygon(UINT32 numVertices, const POINT *controlPolygon, const TOUCH_HIT_TESTING_INPUT *pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *pProximityEval)
	assertl_reflect_as(::EvaluateProximityToPolygon(numVertices, controlPolygon, pHitTestingInput, pProximityEval));
// PackTouchHitTestingProximityEvaluation
inline LRESULT PackTouchHitTestingProximityEvaluation(const TOUCH_HIT_TESTING_INPUT *pHitTestingInput, const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION *pProximityEval)
	nt_assertl_reflect_to(auto h = ::PackTouchHitTestingProximityEvaluation(pHitTestingInput, pProximityEval), h);
// GetWindowFeedbackSetting
inline void GetWindowFeedbackSetting(HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32* pSize, VOID* config)
	assertl_reflect_as(::GetWindowFeedbackSetting(hwnd, feedback, dwFlags, pSize, config));
// SetWindowFeedbackSetting
inline void SetWindowFeedbackSetting(HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32 size, CONST VOID* configuration)
	assertl_reflect_as(::SetWindowFeedbackSetting(hwnd, feedback, dwFlags, size, configuration));
// GetPointerInputTransform - Deprecated
//inline void GetPointerInputTransform(UINT32 pointerId, UINT32 historyCount, INPUT_TRANSFORM *inputTransform)
//	assertl_reflect_as(::GetPointerInputTransform(pointerId, historyCount, inputTransform));
// GetLastInputInfo
inline void GetLastInputInfo(PLASTINPUTINFO plii)
	assertl_reflect_as(::GetLastInputInfo(plii));
// MapVirtualKey
template<bool IsUnicode = WX::IsUnicode>
inline UINT MapVirtualKey(UINT uCode, UINT uMapType) {
	if_c (IsUnicode)
		 reflect_as(::MapVirtualKeyW(uCode, uMapType))
	else reflect_as(::MapVirtualKeyA(uCode, uMapType))
}
// MapVirtualKeyEx
template<bool IsUnicode = WX::IsUnicode>
inline UINT MapVirtualKeyEx(UINT uCode, UINT uMapType, HKL dwhkl) {
	if_c (IsUnicode)
		 reflect_as(::MapVirtualKeyExW(uCode, uMapType, dwhkl))
	else reflect_as(::MapVirtualKeyExA(uCode, uMapType, dwhkl))
}
// GetInputState
inline bool GetInputState()
	reflect_as(::GetInputState());
// GetQueueStatus
inline DWORD GetQueueStatus(UINT flags)
	reflect_as(::GetQueueStatus(flags));
// GetCapture
inline HWND GetCapture()
	reflect_as(::GetCapture());
// SetCapture
inline HWND SetCapture(HWND hWnd)
	reflect_as(::SetCapture(hWnd));
// ReleaseCapture
inline void ReleaseCapture()
	assertl_reflect_as(::ReleaseCapture());
// MsgWaitForMultipleObjects
inline DWORD MsgWaitForMultipleObjects(DWORD nCount, CONST HANDLE *pHandles, BOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask)
	assertl_reflect_as(auto h = ::MsgWaitForMultipleObjects(nCount, pHandles, fWaitAll, dwMilliseconds, dwWakeMask), h);
// MsgWaitForMultipleObjectsEx
inline DWORD MsgWaitForMultipleObjectsEx(DWORD nCount, CONST HANDLE *pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags)
	assertl_reflect_as(auto h = ::MsgWaitForMultipleObjectsEx(nCount, pHandles, dwMilliseconds, dwWakeMask, dwFlags), h);
// SetTimer
inline UINT_PTR SetTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
	assertl_reflect_as(auto h = ::SetTimer(hWnd, nIDEvent, uElapse, lpTimerFunc), h);
// SetCoalescableTimer
inline UINT_PTR SetCoalescableTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc, ULONG uToleranceDelay)
	assertl_reflect_as(auto h = ::SetCoalescableTimer(hWnd, nIDEvent, uElapse, lpTimerFunc, uToleranceDelay), h);
// KillTimer
inline void KillTimer(HWND hWnd, UINT_PTR uIDEvent)
	assertl_reflect_as(::KillTimer(hWnd, uIDEvent));
// IsWindowUnicode
inline bool IsWindowUnicode(HWND hWnd)
	reflect_as(::IsWindowUnicode(hWnd));
inline bool EnableWindow(HWND hWnd, BOOL bEnable)
	reflect_as(::EnableWindow(hWnd, bEnable));
// IsWindowEnabled
inline bool IsWindowEnabled(HWND hWnd)
	reflect_as(::IsWindowEnabled(hWnd));
// LoadAccelerators
inline HACCEL LoadAccelerators(HINSTANCE hInstance, LPCSTR lpTableName)
	assertl_reflect_as(auto h = ::LoadAcceleratorsA(hInstance, lpTableName), h);
inline HACCEL LoadAccelerators(HINSTANCE hInstance, LPCWSTR lpTableName)
	assertl_reflect_as(auto h = ::LoadAcceleratorsW(hInstance, lpTableName), h);
// CreateAcceleratorTable
template<bool IsUnicode = WX::IsUnicode>
inline HACCEL CreateAcceleratorTable(LPACCEL paccel, int cAccel) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::CreateAcceleratorTableW(paccel, cAccel), h)
	else assertl_reflect_as(auto h = ::CreateAcceleratorTableA(paccel, cAccel), h)
}
// DestroyAcceleratorTable
inline void DestroyAcceleratorTable(HACCEL hAccel)
	assertl_reflect_as(::DestroyAcceleratorTable(hAccel));
// CopyAcceleratorTable
template<bool IsUnicode = WX::IsUnicode>
inline int CopyAcceleratorTable(HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries) {
	if_c (IsUnicode)
		 reflect_as(::CopyAcceleratorTableW(hAccelSrc, lpAccelDst, cAccelEntries))
	else reflect_as(::CopyAcceleratorTableA(hAccelSrc, lpAccelDst, cAccelEntries))
}
// TranslateAccelerator
template<bool IsUnicode = WX::IsUnicode>
inline int TranslateAccelerator(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::TranslateAcceleratorW(hWnd, hAccTable, lpMsg), h)
	else assertl_reflect_as(auto h = ::TranslateAcceleratorA(hWnd, hAccTable, lpMsg), h)
}
// GetSystemMetrics
inline int GetSystemMetrics(int nIndex)
	assertl_reflect_as(auto h = ::GetSystemMetrics(nIndex), h);
// GetSystemMetricsForDpi
inline int GetSystemMetricsForDpi(int nIndex, UINT dpi)
	assertl_reflect_as(auto h = ::GetSystemMetricsForDpi(nIndex, dpi), h);
// LoadMenu
inline HMENU LoadMenu(HINSTANCE hInstance, LPCSTR lpMenuName)
	assertl_reflect_as(auto h = ::LoadMenuA(hInstance, lpMenuName), h);
inline HMENU LoadMenu(HINSTANCE hInstance, LPCWSTR lpMenuName)
	assertl_reflect_as(auto h = ::LoadMenuW(hInstance, lpMenuName), h);
// LoadMenuIndirect
template<bool IsUnicode = WX::IsUnicode>
inline HMENU LoadMenu(CONST MENUTEMPLATE *lpMenuTemplate) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::LoadMenuIndirectW(lpMenuTemplate), h)
	else assertl_reflect_as(auto h = ::LoadMenuIndirectA(lpMenuTemplate), h)
}
// GetMenu
inline HMENU GetMenu(HWND hWnd)
	reflect_as(::GetMenu(hWnd));
// SetMenu
inline void SetMenu(HWND hWnd, HMENU hMenu)
	assertl_reflect_as(::SetMenu(hWnd, hMenu));
// ChangeMenu - Undocumented
// HiliteMenuItem
inline bool HiliteMenuItem(HWND hWnd, HMENU hMenu, UINT uIDHiliteItem, UINT uHilite)
	reflect_as(::HiliteMenuItem(hWnd, hMenu, uIDHiliteItem, uHilite));
// GetMenuString
inline int GetMenuString(HMENU hMenu, UINT uIDItem, LPSTR lpString, int cchMax, UINT flags)
	assertl_reflect_as(auto h = ::GetMenuStringA(hMenu, uIDItem, lpString, cchMax, flags), h);
inline int GetMenuString(HMENU hMenu, UINT uIDItem, LPWSTR lpString, int cchMax, UINT flags)
	assertl_reflect_as(auto h = ::GetMenuStringW(hMenu, uIDItem, lpString, cchMax, flags), h);
// GetMenuState
inline UINT GetMenuState(HMENU hMenu, UINT uId, UINT uFlags)
	reflect_as(::GetMenuState(hMenu, uId, uFlags));
// DrawMenuBar
inline void DrawMenuBar(HWND hWnd)
	assertl_reflect_as(::DrawMenuBar(hWnd));
// GetSystemMenu
inline HMENU GetSystemMenu(HWND hWnd, BOOL bRevert)
	reflect_as(::GetSystemMenu(hWnd, bRevert));
// CreateMenu
inline HMENU CreateMenu()
	assertl_reflect_as(auto h = ::CreateMenu(), h);
// CreatePopupMenu
inline HMENU CreatePopupMenu()
	assertl_reflect_as(auto h = ::CreatePopupMenu(), h);
// DestroyMenu
inline void DestroyMenu(HMENU hMenu)
	assertl_reflect_as(::DestroyMenu(hMenu));
// CheckMenuItem
inline DWORD CheckMenuItem(HMENU hMenu, UINT uIDCheckItem, UINT uCheck)
	assertl_reflect_as(auto h = ::CheckMenuItem(hMenu, uIDCheckItem, uCheck), h);
// EnableMenuItem
inline void EnableMenuItem(HMENU hMenu, UINT uIDEnableItem, UINT uEnable)
	assertl_reflect_as(::EnableMenuItem(hMenu, uIDEnableItem, uEnable));
// GetSubMenu
inline HMENU GetSubMenu(HMENU hMenu, int nPos)
	reflect_as(::GetSubMenu(hMenu, nPos));
// GetMenuItemID
inline UINT GetMenuItemID(HMENU hMenu, int nPos)
	reflect_as(::GetMenuItemID(hMenu, nPos));
// GetMenuItemCount
inline int GetMenuItemCount(HMENU hMenu)
	assertl_reflect_as(auto h = ::GetMenuItemCount(hMenu), h);
// InsertMenu
inline void InsertMenu(HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
	assertl_reflect_as(::InsertMenuA(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem));
inline void InsertMenu(HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
	assertl_reflect_as(::InsertMenuW(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem));
// AppendMenu
inline void AppendMenu(HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
	assertl_reflect_as(::AppendMenuA(hMenu, uFlags, uIDNewItem, lpNewItem));
inline void AppendMenu(HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
	assertl_reflect_as(::AppendMenuW(hMenu, uFlags, uIDNewItem, lpNewItem));
// ModifyMenu
inline void ModifyMenu(HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
	assertl_reflect_as(::ModifyMenuA(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem));
inline void ModifyMenu(HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
	assertl_reflect_as(::ModifyMenuW(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem));
// RemoveMenu
inline void RemoveMenu(HMENU hMenu, UINT uPosition, UINT uFlags)
	assertl_reflect_as(::RemoveMenu(hMenu, uPosition, uFlags));
// DeleteMenu
inline void DeleteMenu(HMENU hMenu, UINT uPosition, UINT uFlags)
	assertl_reflect_as(::DeleteMenu(hMenu, uPosition, uFlags));
// SetMenuItemBitmaps
inline void SetMenuItemBitmaps(HMENU hMenu, UINT uPosition, UINT uFlags, HBITMAP hBitmapUnchecked, HBITMAP hBitmapChecked)
	assertl_reflect_as(::SetMenuItemBitmaps(hMenu, uPosition, uFlags, hBitmapUnchecked, hBitmapChecked));
// GetMenuCheckMarkDimensions
inline LONG GetMenuCheckMarkDimensions()
	reflect_as(::GetMenuCheckMarkDimensions());
// TrackPopupMenu
inline void TrackPopupMenu(HMENU hMenu, UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT *prcRect)
	assertl_reflect_as(::TrackPopupMenu(hMenu, uFlags, x, y, nReserved, hWnd, prcRect));
// TrackPopupMenuEx
inline void TrackPopupMenuEx(HMENU hMenu, UINT uFlags, int x, int y, HWND hwnd, LPTPMPARAMS lptpm)
	assertl_reflect_as(::TrackPopupMenuEx(hMenu, uFlags, x, y, hwnd, lptpm));
// CalculatePopupWindowPosition
inline void CalculatePopupWindowPosition(const POINT *anchorPoint, const SIZE *windowSize, UINT flags, RECT *excludeRect, RECT *popupWindowPosition)
	assertl_reflect_as(::CalculatePopupWindowPosition(anchorPoint, windowSize, flags, excludeRect, popupWindowPosition));
// GetMenuInfo
inline void GetMenuInfo(HMENU hMenu, LPMENUINFO lpMenuInfo)
	assertl_reflect_as(::GetMenuInfo(hMenu, lpMenuInfo));
// SetMenuInfo
inline void SetMenuInfo(HMENU hmenu, LPCMENUINFO lpcMenuInfo)
	assertl_reflect_as(::SetMenuInfo(hmenu, lpcMenuInfo));
// EndMenu
inline void EndMenu()
	assertl_reflect_as(::EndMenu());
// InsertMenuItem
inline void InsertMenuItem(HMENU hmenu, UINT item, BOOL fByPosition, LPCMENUITEMINFOA lpmi)
	assertl_reflect_as(::InsertMenuItemA(hmenu, item, fByPosition, lpmi));
inline void InsertMenuItem(HMENU hmenu, UINT item, BOOL fByPosition, LPCMENUITEMINFOW lpmi)
	assertl_reflect_as(::InsertMenuItemW(hmenu, item, fByPosition, lpmi));
// GetMenuItemInfo
inline void GetMenuItemInfo(HMENU hmenu, UINT item, BOOL fByPosition, LPMENUITEMINFOA lpmii)
	assertl_reflect_as(::GetMenuItemInfoA(hmenu, item, fByPosition, lpmii));
inline void GetMenuItemInfo(HMENU hmenu, UINT item, BOOL fByPosition, LPMENUITEMINFOW lpmii)
	assertl_reflect_as(::GetMenuItemInfoW(hmenu, item, fByPosition, lpmii));
// SetMenuItemInfo
inline void SetMenuItemInfo(HMENU hmenu, UINT item, BOOL fByPositon, LPCMENUITEMINFOA lpmii)
	assertl_reflect_as(::SetMenuItemInfoA(hmenu, item, fByPositon, lpmii));
inline void SetMenuItemInfo(HMENU hmenu, UINT item, BOOL fByPositon, LPCMENUITEMINFOW lpmii)
	assertl_reflect_as(::SetMenuItemInfoW(hmenu, item, fByPositon, lpmii));
// GetMenuDefaultItem
inline UINT GetMenuDefaultItem(HMENU hMenu, UINT fByPos, UINT gmdiFlags)
	assertl_reflect_as(auto h = ::GetMenuDefaultItem(hMenu, fByPos, gmdiFlags); h != -1, h);
// SetMenuDefaultItem
inline void SetMenuDefaultItem(HMENU hMenu, UINT uItem, UINT fByPos)
	assertl_reflect_as(::SetMenuDefaultItem(hMenu, uItem, fByPos));
// GetMenuItemRect
inline void GetMenuItemRect(HWND hWnd, HMENU hMenu, UINT uItem, LPRECT lprcItem)
	assertl_reflect_as(::GetMenuItemRect(hWnd, hMenu, uItem, lprcItem));
// MenuItemFromPoint
inline int MenuItemFromPoint(HWND hWnd, HMENU hMenu, POINT ptScreen)
	reflect_as(::MenuItemFromPoint(hWnd, hMenu, ptScreen));
// DragObject
// DragDetect
inline bool DragDetect(HWND hwnd, POINT pt)
	reflect_as(::DragDetect(hwnd, pt));
// DrawIcon
inline void DrawIcon(HDC hDC, int X, int Y, HICON hIcon)
	assertl_reflect_as(::DrawIcon(hDC, X, Y, hIcon));
// DrawText
inline int DrawText(HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format)
	assertl_reflect_as(auto h = ::DrawTextA(hdc, lpchText, cchText, lprc, format), h);
inline int DrawText(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format)
	assertl_reflect_as(auto h = ::DrawTextW(hdc, lpchText, cchText, lprc, format), h);
// DrawTextEx
inline int DrawText(HDC hdc, LPSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
	assertl_reflect_as(auto h = ::DrawTextExA(hdc, lpchText, cchText, lprc, format, lpdtp), h);
inline int DrawText(HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
	assertl_reflect_as(auto h = ::DrawTextExW(hdc, lpchText, cchText, lprc, format, lpdtp), h);
// GrayString
template<bool IsUnicode = WX::IsUnicode>
inline void GrayString(HDC hDC, HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int X, int Y, int nWidth, int nHeight) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GrayStringW(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight))
	else assertl_reflect_as(::GrayStringA(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight))
}
// DrawState
template<bool IsUnicode = WX::IsUnicode>
inline void DrawState(HDC hdc, HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags) {
	if_c (IsUnicode)
		 assertl_reflect_as(::DrawStateW(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags))
	else assertl_reflect_as(::DrawStateA(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags))
}
// TabbedTextOut
inline LONG TabbedTextOut(HDC hdc, int x, int y, LPCSTR lpString, int chCount, int nTabPositions, CONST INT *lpnTabStopPositions, int nTabOrigin)
	assertl_reflect_as(auto h = ::TabbedTextOutA(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin), h);
inline LONG TabbedTextOut(HDC hdc, int x, int y, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT *lpnTabStopPositions, int nTabOrigin)
	assertl_reflect_as(auto h = ::TabbedTextOutW(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin), h);
// GetTabbedTextExtent
inline DWORD GetTabbedTextExtent(HDC hdc, LPCSTR lpString, int chCount, int nTabPositions, CONST INT *lpnTabStopPositions)
	assertl_reflect_as(auto h = ::GetTabbedTextExtentA(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions), h);
inline DWORD GetTabbedTextExtent(HDC hdc, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT *lpnTabStopPositions)
	assertl_reflect_as(auto h = ::GetTabbedTextExtentW(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions), h);
inline void UpdateWindow(HWND hWnd)
	assertl_reflect_as(::UpdateWindow(hWnd));
inline HWND SetActiveWindow(HWND hWnd)
	assertl_reflect_as(auto h = ::SetActiveWindow(hWnd), h);
inline HWND GetForegroundWindow()
	reflect_as(::GetForegroundWindow());
// PaintDesktop
inline void PaintDesktop(HDC hdc)
	assertl_reflect_as(::PaintDesktop(hdc));
inline void SwitchToThisWindow(HWND hwnd, BOOL fUnknown)
	reflect_to(::SwitchToThisWindow(hwnd, fUnknown));
inline void SetForegroundWindow(HWND hWnd)
	assertl_reflect_as(::SetForegroundWindow(hWnd));
inline void AllowSetForegroundWindow(DWORD dwProcessId)
	assertl_reflect_as(::AllowSetForegroundWindow(dwProcessId));
inline void LockSetForegroundWindow(UINT uLockCode)
	assertl_reflect_as(::LockSetForegroundWindow(uLockCode));
// WindowFromDC
inline HWND WindowFromDC(HDC hDC)
	reflect_as(::WindowFromDC(hDC));
// GetDC
inline HDC GetDC(HWND hWnd)
	assertl_reflect_as(auto h = ::GetDC(hWnd), h);
// GetDCEx
inline HDC GetDCEx(HWND hWnd, HRGN hrgnClip, DWORD flags)
	assertl_reflect_as(auto h = ::GetDCEx(hWnd, hrgnClip, flags), h);
// GetWindowDC
inline HDC GetWindowDC(HWND hWnd)
	assertl_reflect_as(auto h = ::GetWindowDC(hWnd), h);
// ReleaseDC
inline int ReleaseDC(HWND hWnd, HDC hDC)
	assertl_reflect_as(auto h = ::ReleaseDC(hWnd, hDC), h);
// BeginPaint
inline HDC BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint)
	assertl_reflect_as(auto h = ::BeginPaint(hWnd, lpPaint), h);
// EndPaint
inline void EndPaint(HWND hWnd, CONST PAINTSTRUCT *lpPaint)
	assertl_reflect_as(::EndPaint(hWnd, lpPaint));
// GetUpdateRect
inline bool GetUpdateRect(HWND hWnd, LPRECT lpRect, BOOL bErase)
	reflect_as(::GetUpdateRect(hWnd, lpRect, bErase));
// GetUpdateRgn
inline int GetUpdateRgn(HWND hWnd, HRGN hRgn, BOOL bErase)
	assertl_reflect_as(auto h = ::GetUpdateRgn(hWnd, hRgn, bErase), h);
// SetWindowRgn
inline int SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw)
	assertl_reflect_as(auto h = ::SetWindowRgn(hWnd, hRgn, bRedraw), h);
// GetWindowRgn
inline int GetWindowRgn(HWND hWnd, HRGN hRgn)
	assertl_reflect_as(auto h = ::GetWindowRgn(hWnd, hRgn), h);
// GetWindowRgnBox
inline int GetWindowRgnBox(HWND hWnd, LPRECT lprc)
	assertl_reflect_as(auto h = ::GetWindowRgnBox(hWnd, lprc), h);
// ExcludeUpdateRgn
inline int ExcludeUpdateRgn(HDC hDC, HWND hWnd)
	assertl_reflect_as(auto h = ::ExcludeUpdateRgn(hDC, hWnd), h);
// InvalidateRect
inline void InvalidateRect(HWND hWnd, CONST RECT *lpRect, BOOL bErase)
	assertl_reflect_as(::InvalidateRect(hWnd, lpRect, bErase));
// ValidateRect
inline void ValidateRect(HWND hWnd, CONST RECT *lpRect)
	assertl_reflect_as(::ValidateRect(hWnd, lpRect));
// InvalidateRgn
inline void InvalidateRgn(HWND hWnd, HRGN hRgn, BOOL bErase)
	assertl_reflect_as(::InvalidateRgn(hWnd, hRgn, bErase));
// ValidateRgn
inline void ValidateRgn(HWND hWnd, HRGN hRgn)
	assertl_reflect_as(::ValidateRgn(hWnd, hRgn));
inline void RedrawWindow(HWND hWnd, CONST RECT *lprcUpdate, HRGN hrgnUpdate, UINT flags)
	assertl_reflect_as(::RedrawWindow(hWnd, lprcUpdate, hrgnUpdate, flags));
// LockWindowUpdate
inline void LockWindowUpdate(HWND hWndLock)
	assertl_reflect_as(::LockWindowUpdate(hWndLock));
inline void ScrollWindow(HWND hWnd, int XAmount, int YAmount, CONST RECT *lpRect, CONST RECT *lpClipRect)
	assertl_reflect_as(::ScrollWindow(hWnd, XAmount, YAmount, lpRect, lpClipRect));
// ScrollDC
inline void ScrollDC(HDC hDC, int dx, int dy, CONST RECT *lprcScroll, CONST RECT *lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate)
	assertl_reflect_as(::ScrollDC(hDC, dx, dy, lprcScroll, lprcClip, hrgnUpdate, lprcUpdate));
// ScrollWindowEx
inline int ScrollWindowEx(HWND hWnd, int dx, int dy, CONST RECT *prcScroll, CONST RECT *prcClip, HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags)
	assertl_reflect_as(auto h = ::ScrollWindowEx(hWnd, dx, dy, prcScroll, prcClip, hrgnUpdate, prcUpdate, flags), h);
// SetScrollPos
inline int SetScrollPos(HWND hWnd, int nBar, int nPos, BOOL bRedraw)
	assertl_reflect_as(auto h = ::SetScrollPos(hWnd, nBar, nPos, bRedraw), h);
// GetScrollPos
inline int GetScrollPos(HWND hWnd, int nBar)
	assertl_reflect_as(auto h = ::GetScrollPos(hWnd, nBar), h);
// SetScrollRange
inline void SetScrollRange(HWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
	assertl_reflect_as(::SetScrollRange(hWnd, nBar, nMinPos, nMaxPos, bRedraw));
// GetScrollRange
inline void GetScrollRange(HWND hWnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
	assertl_reflect_as(::GetScrollRange(hWnd, nBar, lpMinPos, lpMaxPos));
// ShowScrollBar
inline void ShowScrollBar(HWND hWnd, int wBar, BOOL bShow)
	assertl_reflect_as(::ShowScrollBar(hWnd, wBar, bShow));
// EnableScrollBar
inline void EnableScrollBar(HWND hWnd, UINT wSBflags, UINT wArrows)
	assertl_reflect_as(::EnableScrollBar(hWnd, wSBflags, wArrows));
// SetProp
inline void SetProp(HWND hWnd, LPCSTR lpString, HANDLE hData)
	assertl_reflect_as(::SetPropA(hWnd, lpString, hData));
inline void SetProp(HWND hWnd, LPCWSTR lpString, HANDLE hData)
	assertl_reflect_as(::SetPropW(hWnd, lpString, hData));
// GetProp
inline HANDLE GetProp(HWND hWnd, LPCSTR lpString)
	reflect_as(::GetPropA(hWnd, lpString));
inline HANDLE GetProp(HWND hWnd, LPCWSTR lpString)
	reflect_as(::GetPropW(hWnd, lpString));
// RemoveProp
inline HANDLE RemoveProp(HWND hWnd, LPCSTR lpString)
	nt_assertl_reflect_to(auto h = ::RemovePropA(hWnd, lpString), h);
inline HANDLE RemoveProp(HWND hWnd, LPCWSTR lpString)
	nt_assertl_reflect_to(auto h = ::RemovePropW(hWnd, lpString), h);
// EnumPropsEx
inline int EnumProps(HWND hWnd, PROPENUMPROCEXA lpEnumFunc, LPARAM lParam)
	assertl_reflect_as(auto h = ::EnumPropsExA(hWnd, lpEnumFunc, lParam), h);
inline int EnumProps(HWND hWnd, PROPENUMPROCEXW lpEnumFunc, LPARAM lParam)
	assertl_reflect_as(auto h = ::EnumPropsExW(hWnd, lpEnumFunc, lParam), h);
// EnumProps
inline int EnumProps(HWND hWnd, PROPENUMPROCA lpEnumFunc)
	assertl_reflect_as(auto h = ::EnumPropsA(hWnd, lpEnumFunc), h);
inline int EnumProps(HWND hWnd, PROPENUMPROCW lpEnumFunc)
	assertl_reflect_as(auto h = ::EnumPropsW(hWnd, lpEnumFunc), h);
// SetWindowText
inline void SetWindowText(HWND hWnd, LPCSTR lpString)
	assertl_reflect_as(::SetWindowTextA(hWnd, lpString));
inline void SetWindowText(HWND hWnd, LPCWSTR lpString)
	assertl_reflect_as(::SetWindowTextW(hWnd, lpString));
// GetWindowText
inline int GetWindowText(HWND hWnd, LPSTR lpString, int nMaxCount)
	nt_assertl_reflect_to(auto h = ::GetWindowTextA(hWnd, lpString, nMaxCount), h);
inline int GetWindowText(HWND hWnd, LPWSTR lpString, int nMaxCount)
	nt_assertl_reflect_to(auto h = ::GetWindowTextW(hWnd, lpString, nMaxCount), h);
// GetWindowTextLength
template<bool IsUnicode = WX::IsUnicode>
inline int GetWindowTextLength(HWND hWnd) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::GetWindowTextLengthW(hWnd), h)
	else nt_assertl_reflect_to(auto h = ::GetWindowTextLengthA(hWnd), h)
}
// GetClientRect
inline void GetClientRect(HWND hWnd, LPRECT lpRect)
	assertl_reflect_as(::GetClientRect(hWnd, lpRect));
// GetWindowRect
inline void GetWindowRect(HWND hWnd, LPRECT lpRect)
	assertl_reflect_as(::GetWindowRect(hWnd, lpRect));
// AdjustWindowRect
inline void AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu)
	assertl_reflect_as(::AdjustWindowRect(lpRect, dwStyle, bMenu));
// AdjustWindowRectEx
inline void AdjustWindowRect(LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle)
	assertl_reflect_as(::AdjustWindowRectEx(lpRect, dwStyle, bMenu, dwExStyle));
// AdjustWindowRectExForDpi
inline void AdjustWindowRectForDpi(LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle, UINT dpi)
	assertl_reflect_as(::AdjustWindowRectExForDpi(lpRect, dwStyle, bMenu, dwExStyle, dpi));
// SetWindowContextHelpId
inline void SetWindowContextHelpId(HWND hwnd, DWORD dwID)
	assertl_reflect_as(::SetWindowContextHelpId(hwnd, dwID));
// GetWindowContextHelpId
inline DWORD GetWindowContextHelpId(HWND  hwnd)
	reflect_as(::GetWindowContextHelpId(hwnd));
// SetMenuContextHelpId
inline void SetMenuContextHelpId(HMENU  hwnd, DWORD dwID)
	assertl_reflect_as(::SetMenuContextHelpId(hwnd, dwID));
// GetMenuContextHelpId
inline DWORD GetMenuContextHelpId(HMENU hmenu)
	reflect_as(::GetMenuContextHelpId(hmenu));
// MessageBox
inline int MessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
	assertl_reflect_as(auto h = ::MessageBoxA(hWnd, lpText, lpCaption, uType), h);
inline int MessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
	assertl_reflect_as(auto h = ::MessageBoxW(hWnd, lpText, lpCaption, uType), h);
// MessageBoxEx
inline int MessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId)
	assertl_reflect_as(auto h = ::MessageBoxExA(hWnd, lpText, lpCaption, uType, wLanguageId), h);
inline int MessageBox(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType, WORD wLanguageId)
	assertl_reflect_as(auto h = ::MessageBoxExW(hWnd, lpText, lpCaption, uType, wLanguageId), h);
// MessageBoxIndirect
inline int MessageBox(CONST MSGBOXPARAMSA * lpmbp)
	assertl_reflect_as(auto h = ::MessageBoxIndirectA(lpmbp), h);
inline int MessageBox(CONST MSGBOXPARAMSW * lpmbp)
	assertl_reflect_as(auto h = ::MessageBoxIndirectW(lpmbp), h);
// MessageBeep
inline void MessageBeep(UINT uType)
	assertl_reflect_as(::MessageBeep(uType));
// ShowCursor
inline int ShowCursor(BOOL bShow)
	reflect_as(::ShowCursor(bShow));
// SetCursorPos
inline void SetCursorPos(int X, int Y)
	assertl_reflect_as(::SetCursorPos(X, Y));
// SetPhysicalCursorPos
inline void SetPhysicalCursorPos(int X, int Y)
	assertl_reflect_as(::SetPhysicalCursorPos(X, Y));
// SetCursor
inline HCURSOR SetCursor(HCURSOR hCursor)
	reflect_as(::SetCursor(hCursor));
// GetCursorPos
inline void GetCursorPos(LPPOINT lpPoint)
	assertl_reflect_as(::GetCursorPos(lpPoint));
// GetPhysicalCursorPos
inline void GetPhysicalCursorPos(LPPOINT lpPoint)
	assertl_reflect_as(::GetPhysicalCursorPos(lpPoint));
// GetClipCursor
inline void GetClipCursor(LPRECT lpRect)
	assertl_reflect_as(::GetClipCursor(lpRect));
// GetCursor
inline HCURSOR GetCursor()
	reflect_as(::GetCursor());
// CreateCaret
inline void CreateCaret(HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight)
	assertl_reflect_as(::CreateCaret(hWnd, hBitmap, nWidth, nHeight));
// GetCaretBlinkTime
inline UINT GetCaretBlinkTime()
	assertl_reflect_as(auto h = ::GetCaretBlinkTime(), h);
// SetCaretBlinkTime
inline void SetCaretBlinkTime(UINT uMSeconds)
	assertl_reflect_as(::SetCaretBlinkTime(uMSeconds));
// DestroyCaret
inline void DestroyCaret()
	assertl_reflect_as(::DestroyCaret());
// HideCaret
inline void HideCaret(HWND hWnd)
	assertl_reflect_as(::HideCaret(hWnd));
// ShowCaret
inline void ShowCaret(HWND hWnd)
	assertl_reflect_as(::ShowCaret(hWnd));
// SetCaretPos
inline void SetCaretPos(int X, int Y)
	assertl_reflect_as(::SetCaretPos(X, Y));
// GetCaretPos
inline void GetCaretPos(LPPOINT lpPoint)
	assertl_reflect_as(::GetCaretPos(lpPoint));
// ClientToScreen
inline void ClientToScreen(HWND hWnd, LPPOINT lpPoint)
	assertl_reflect_as(::ClientToScreen(hWnd, lpPoint));
// ScreenToClient
inline void ScreenToClient(HWND hWnd, LPPOINT lpPoint)
	assertl_reflect_as(::ScreenToClient(hWnd, lpPoint));
// LogicalToPhysicalPoint
inline void LogicalToPhysicalPoint(HWND hWnd, LPPOINT lpPoint)
	assertl_reflect_as(::LogicalToPhysicalPoint(hWnd, lpPoint));
// PhysicalToLogicalPoint
inline void PhysicalToLogicalPoint(HWND hWnd, LPPOINT lpPoint)
	assertl_reflect_as(::PhysicalToLogicalPoint(hWnd, lpPoint));
// LogicalToPhysicalPointForPerMonitorDPI
inline void LogicalToPhysicalPointForPerMonitorDPI(HWND hWnd, LPPOINT lpPoint)
	assertl_reflect_as(::LogicalToPhysicalPointForPerMonitorDPI(hWnd, lpPoint));
// PhysicalToLogicalPointForPerMonitorDPI
inline void PhysicalToLogicalPointForPerMonitorDPI(HWND hWnd, LPPOINT lpPoint)
	assertl_reflect_as(::PhysicalToLogicalPointForPerMonitorDPI(hWnd, lpPoint));
// MapWindowPoints
inline int MapWindowPoints(HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints, UINT cPoints)
	nt_assertl_reflect_to(auto h = ::MapWindowPoints(hWndFrom, hWndTo, lpPoints, cPoints), h);
// WindowFromPoint
inline HWND WindowFromPoint(POINT Point)
	reflect_as(::WindowFromPoint(Point));
// WindowFromPhysicalPoint
inline HWND WindowFromPhysicalPoint(POINT Point)
	reflect_as(::WindowFromPhysicalPoint(Point));
// ChildWindowFromPoint
inline HWND ChildWindowFromPoint(HWND hWndParent, POINT Point)
	reflect_as(::ChildWindowFromPoint(hWndParent, Point));
// ClipCursor
inline void ClipCursor(CONST RECT *lpRect)
	assertl_reflect_as(::ClipCursor(lpRect));
// ChildWindowFromPointEx
inline HWND ChildWindowFromPointEx(HWND hwnd, POINT pt, UINT flags)
	reflect_as(::ChildWindowFromPointEx(hwnd, pt, flags));
// GetSysColor
inline DWORD GetSysColor(int nIndex)
	reflect_as(::GetSysColor(nIndex));
// GetSysColorBrush
inline HBRUSH GetSysColorBrush(int nIndex)
	reflect_as(::GetSysColorBrush(nIndex));
// SetSysColors
inline void SetSysColors(int cElements, CONST INT * lpaElements, CONST COLORREF * lpaRgbValues)
	assertl_reflect_as(::SetSysColors(cElements, lpaElements, lpaRgbValues));
// DrawFocusRect
inline void DrawFocusRect(HDC hDC, CONST RECT * lprc)
	assertl_reflect_as(::DrawFocusRect(hDC, lprc));
// FillRect
inline void FillRect(HDC hDC, CONST RECT *lprc, HBRUSH hbr)
	assertl_reflect_as(::FillRect(hDC, lprc, hbr));
// FrameRect
inline void FrameRect(HDC hDC, CONST RECT *lprc, HBRUSH hbr)
	assertl_reflect_as(::FrameRect(hDC, lprc, hbr));
// InvertRect
inline void InvertRect(HDC hDC, CONST RECT *lprc)
	assertl_reflect_as(::InvertRect(hDC, lprc));
// SetRect
// SetRectEmpty
// CopyRect
// InflateRect
// IntersectRect
// UnionRect
// SubtractRect
// OffsetRect
// IsRectEmpty
// EqualRect
// PtInRect
// GetWindowWord
inline WORD GetWindowWord(HWND hWnd, int nIndex)
	nt_assertl_reflect_to(auto h = ::GetWindowWord(hWnd, nIndex), h);
// SetWindowWord
inline WORD SetWindowWord(HWND hWnd, int nIndex, WORD wNewWord)
	nt_assertl_reflect_to(auto h = ::SetWindowWord(hWnd, nIndex, wNewWord), h);
// GetWindowLong - Deprecated
// SetWindowLong - Deprecated
// GetWindowLongPtr
template<bool IsUnicode = WX::IsUnicode>
inline LONG_PTR GetWindowLongPtr(HWND hWnd, int nIndex) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::GetWindowLongPtrW(hWnd, nIndex), h)
	else nt_assertl_reflect_to(auto h = ::GetWindowLongPtrA(hWnd, nIndex), h)
}
// SetWindowLongPtr
template<bool IsUnicode = WX::IsUnicode>
inline LONG_PTR SetWindowLongPtr(HWND hWnd, int nIndex, LONG_PTR dwNewLong) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::SetWindowLongPtrW(hWnd, nIndex, dwNewLong), h)
	else nt_assertl_reflect_to(auto h = ::SetWindowLongPtrA(hWnd, nIndex, dwNewLong), h)
}
// GetClassWord
inline WORD GetClassWord(HWND hWnd, int nIndex)
	nt_assertl_reflect_to(auto h = ::GetClassWord(hWnd, nIndex), h);
// SetClassWord
inline WORD SetClassWord(HWND hWnd, int nIndex, WORD wNewWord)
	nt_assertl_reflect_to(auto h = ::SetClassWord(hWnd, nIndex, wNewWord), h);
// GetClassLong - Deprecated
// SetClassLong - Deprecated
// GetClassLongPtr
template<bool IsUnicode = WX::IsUnicode>
inline ULONG_PTR GetClassLongPtr(HWND hWnd, int nIndex) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::GetClassLongPtrW(hWnd, nIndex), h)
	else nt_assertl_reflect_to(auto h = ::GetClassLongPtrA(hWnd, nIndex), h)
}
// SetClassLongPtr
template<bool IsUnicode = WX::IsUnicode>
inline ULONG_PTR SetClassLongPtr(HWND hWnd, int nIndex, LONG_PTR dwNewLong) {
	if_c (IsUnicode)
		 nt_assertl_reflect_to(auto h = ::SetClassLongPtrW(hWnd, nIndex, dwNewLong), h)
	else nt_assertl_reflect_to(auto h = ::SetClassLongPtrA(hWnd, nIndex, dwNewLong), h)
}
// GetProcessDefaultLayout
inline void GetProcessDefaultLayout(DWORD *pdwDefaultLayout)
	assertl_reflect_as(::GetProcessDefaultLayout(pdwDefaultLayout));
// SetProcessDefaultLayout
inline void SetProcessDefaultLayout(DWORD dwDefaultLayout)
	assertl_reflect_as(::SetProcessDefaultLayout(dwDefaultLayout));
inline HWND GetDesktopWindow()
	reflect_as(::GetDesktopWindow());
// GetParent
inline HWND GetParent(HWND hWnd)
	nt_assertl_reflect_to(auto h = ::GetParent(hWnd), h);
// SetParent
inline HWND SetParent(HWND hWndChild, HWND hWndNewParent)
	nt_assertl_reflect_to(auto h = ::SetParent(hWndChild, hWndNewParent), h);
// EnumChildWindows
inline bool EnumChildWindows(HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam)
	reflect_as(::EnumChildWindows(hWndParent, lpEnumFunc, lParam));
// FindWindow
inline HWND FindWindow(LPCSTR lpClassName, LPCSTR lpWindowName)
	reflect_as(::FindWindowA(lpClassName, lpWindowName));
inline HWND FindWindow(LPCWSTR lpClassName, LPCWSTR lpWindowName)
	reflect_as(::FindWindowW(lpClassName, lpWindowName));
// FindWindowEx
inline HWND FindWindowEx(HWND hWndParent, HWND hWndChildAfter, LPCSTR lpszClass, LPCSTR lpszWindow)
	assertl_reflect_as(auto h = ::FindWindowExA(hWndParent, hWndChildAfter, lpszClass, lpszWindow), h);
inline HWND FindWindowEx(HWND hWndParent, HWND hWndChildAfter, LPCWSTR lpszClass, LPCWSTR lpszWindow)
	assertl_reflect_as(auto h = ::FindWindowExW(hWndParent, hWndChildAfter, lpszClass, lpszWindow), h);
inline HWND GetShellWindow()
	reflect_as(::GetShellWindow());
inline void RegisterShellHookWindow(HWND hwnd)
	assertl_reflect_as(::RegisterShellHookWindow(hwnd));
inline void DeregisterShellHookWindow(HWND hwnd)
	assertl_reflect_as(::DeregisterShellHookWindow(hwnd));
// EnumWindows
inline void EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam)
	assertl_reflect_as(::EnumWindows(lpEnumFunc, lParam));
// EnumThreadWindows
inline bool EnumThreadWindows(DWORD dwThreadId, WNDENUMPROC lpfn, LPARAM lParam)
	reflect_as(::EnumThreadWindows(dwThreadId, lpfn, lParam));
// GetClassName
inline int GetClassName(HWND hWnd, LPSTR lpClassName, int nMaxCount)
	assertl_reflect_as(auto h = ::GetClassNameA(hWnd, lpClassName, nMaxCount), h);
inline int GetClassName(HWND hWnd, LPWSTR lpClassName, int nMaxCount)
	assertl_reflect_as(auto h = ::GetClassNameW(hWnd, lpClassName, nMaxCount), h);
inline HWND GetTopWindow(HWND hWnd)
	nt_assertl_reflect_to(auto h = ::GetTopWindow(hWnd), h);
// GetWindowThreadProcessId
inline DWORD GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId)
	assertl_reflect_as(auto h = ::GetWindowThreadProcessId(hWnd, lpdwProcessId), h);
// IsGUIThread
inline bool IsGUIThread(BOOL bConvert)
	reflect_as(::IsGUIThread(bConvert));
// GetLastActivePopup
inline HWND GetLastActivePopup(HWND hWnd)
	reflect_as(::GetLastActivePopup(hWnd));
inline HWND GetWindow(HWND hWnd, UINT uCmd)
	nt_assertl_reflect_to(auto h = ::GetWindow(hWnd, uCmd), h);
// SetWindowsHook - Undocumented
// UnhookWindowsHook
// SetWindowsHookEx
template<bool IsUnicode = WX::IsUnicode>
inline HHOOK SetWindowsHookEx(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::SetWindowsHookExW(idHook, lpfn, hmod, dwThreadId), h)
	else assertl_reflect_as(auto h = ::SetWindowsHookExA(idHook, lpfn, hmod, dwThreadId), h)
}
// UnhookWindowsHookEx
inline void UnhookWindowsHookEx(HHOOK hhk)
	assertl_reflect_as(::UnhookWindowsHookEx(hhk));
// CallNextHookEx
inline LRESULT CallNextHookEx(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam)
	reflect_as(::CallNextHookEx(hhk, nCode, wParam, lParam));
// CheckMenuRadioItem
inline void CheckMenuRadioItem(HMENU hmenu, UINT first, UINT last, UINT check, UINT flags)
	assertl_reflect_as(::CheckMenuRadioItem(hmenu, first, last, check, flags));
// LoadBitmap
inline HBITMAP LoadBitmap(HINSTANCE hInstance, LPCSTR lpBitmapName)
	assertl_reflect_as(auto h = ::LoadBitmapA(hInstance, lpBitmapName), h);
inline HBITMAP LoadBitmap(HINSTANCE hInstance, LPCWSTR lpBitmapName)
	assertl_reflect_as(auto h = ::LoadBitmapW(hInstance, lpBitmapName), h);
// LoadCursor
inline HCURSOR LoadCursor(HINSTANCE hInstance, LPCSTR lpCursorName)
	assertl_reflect_as(auto h = ::LoadCursorA(hInstance, lpCursorName), h);
inline HCURSOR LoadCursor(HINSTANCE hInstance, LPCWSTR lpCursorName)
	assertl_reflect_as(auto h = ::LoadCursorW(hInstance, lpCursorName), h);
// LoadCursorFromFile
inline HCURSOR LoadCursorFromFile(LPCSTR lpFileName)
	assertl_reflect_as(auto h = ::LoadCursorFromFileA(lpFileName), h);
inline HCURSOR LoadCursorFromFile(LPCWSTR lpFileName)
	assertl_reflect_as(auto h = ::LoadCursorFromFileW(lpFileName), h);
// CreateCursor
inline HCURSOR CreateCursor(HINSTANCE hInst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane)
	assertl_reflect_as(auto h = ::CreateCursor(hInst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane), h);
// DestroyCursor
inline void DestroyCursor(HCURSOR hCursor)
	assertl_reflect_as(::DestroyCursor(hCursor));
// SetSystemCursor
inline void SetSystemCursor(HCURSOR hcur, DWORD id)
	assertl_reflect_as(::SetSystemCursor(hcur, id));
// LoadIcon
inline HICON LoadIcon(HINSTANCE hInstance, LPCSTR lpIconName)
	assertl_reflect_as(auto h = ::LoadIconA(hInstance, lpIconName), h);
inline HICON LoadIcon(HINSTANCE hInstance, LPCWSTR lpIconName)
	assertl_reflect_as(auto h = ::LoadIconW(hInstance, lpIconName), h);
// PrivateExtractIcons
inline UINT PrivateExtractIcons(LPCSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON *phicon, UINT *piconid, UINT nIcons, UINT flags)
	assertl_reflect_as(auto h = ::PrivateExtractIconsA(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags); h != -1, h);
inline UINT PrivateExtractIcons(LPCWSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON *phicon, UINT *piconid, UINT nIcons, UINT flags)
	assertl_reflect_as(auto h = ::PrivateExtractIconsW(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags); h != -1, h);
// CreateIcon
inline HICON CreateIcon(HINSTANCE hInstance, int nWidth, int nHeight, BYTE cPlanes, BYTE cBitsPixel, CONST BYTE *lpbANDbits, CONST BYTE *lpbXORbits)
	assertl_reflect_as(auto h = ::CreateIcon(hInstance, nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits), h);
// DestroyIcon
inline void DestroyIcon(HICON hIcon)
	assertl_reflect_as(::DestroyIcon(hIcon));
// LookupIconIdFromDirectory
inline int LookupIconIdFromDirectory(PBYTE presbits, BOOL fIcon)
	assertl_reflect_as(auto h = ::LookupIconIdFromDirectory(presbits, fIcon), h);
// LookupIconIdFromDirectoryEx
inline int LookupIconIdFromDirectoryEx(PBYTE presbits, BOOL fIcon, int cxDesired, int cyDesired, UINT Flags)
	assertl_reflect_as(auto h = ::LookupIconIdFromDirectoryEx(presbits, fIcon, cxDesired, cyDesired, Flags), h);
// CreateIconFromResource
inline HICON CreateIconFromResource(PBYTE presbits, DWORD dwResSize, BOOL fIcon, DWORD dwVer)
	assertl_reflect_as(auto h = ::CreateIconFromResource(presbits, dwResSize, fIcon, dwVer), h);
// CreateIconFromResourceEx
inline HICON CreateIconFromResourceEx(PBYTE presbits, DWORD dwResSize, BOOL fIcon, DWORD dwVer, int cxDesired, int cyDesired, UINT Flags)
	assertl_reflect_as(auto h = ::CreateIconFromResourceEx(presbits, dwResSize, fIcon, dwVer, cxDesired, cyDesired, Flags), h);
#if (NTDDI_VERSION >= NTDDI_WIN10_CO) && !__GNUC__
// SetThreadCursorCreationScaling
inline UINT SetThreadCursorCreationScaling(UINT cursorDpi)
	reflect_as(::SetThreadCursorCreationScaling(cursorDpi));
#endif
// LoadImage
inline HANDLE LoadImage(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
	assertl_reflect_as(auto h = ::LoadImageA(hInst, name, type, cx, cy, fuLoad), h);
inline HANDLE LoadImage(HINSTANCE hInst, LPCWSTR name, UINT type, int cx, int cy, UINT fuLoad)
	assertl_reflect_as(auto h = ::LoadImageW(hInst, name, type, cx, cy, fuLoad), h);
//// CopyImage
//inline HANDLE CopyImage(HANDLE h, UINT type, int cx, int cy, UINT flags)
//	assertl_reflect_as(auto h = ::CopyImage(h, type, cx, cy, flags), h);
// DrawIconEx
inline void DrawIconEx(HDC hdc, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
	assertl_reflect_as(::DrawIconEx(hdc, xLeft, yTop, hIcon, cxWidth, cyWidth, istepIfAniCur, hbrFlickerFreeDraw, diFlags));
// CreateIconIndirect
inline HICON CreateIcon(PICONINFO piconinfo)
	assertl_reflect_as(auto h = ::CreateIconIndirect(piconinfo), h);
// CopyIcon
inline HICON CopyIcon(HICON hIcon)
	assertl_reflect_as(auto h = ::CopyIcon(hIcon), h);
// GetIconInfo
inline void GetIconInfo(HICON hIcon, PICONINFO piconinfo)
	assertl_reflect_as(::GetIconInfo(hIcon, piconinfo));
// GetIconInfoEx
inline void GetIconInfoEx(HICON hicon, PICONINFOEXA piconinfo)
	assertl_reflect_as(::GetIconInfoExA(hicon, piconinfo));
inline void GetIconInfoEx(HICON hicon, PICONINFOEXW piconinfo)
	assertl_reflect_as(::GetIconInfoExW(hicon, piconinfo));
// IsDialogMessage
template<bool IsUnicode = WX::IsUnicode>
inline bool IsDialogMessage(HWND hDlg, LPMSG lpMsg) {
	if_c (IsUnicode)
		 reflect_as(::IsDialogMessageW(hDlg, lpMsg))
	else reflect_as(::IsDialogMessageA(hDlg, lpMsg))
}
// MapDialogRect
inline void MapDialogRect(HWND hDlg, LPRECT lpRect)
	assertl_reflect_as(::MapDialogRect(hDlg, lpRect));
// DlgDirList
inline int DlgDirList(HWND hDlg, LPSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
	assertl_reflect_as(auto h = ::DlgDirListA(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType), h);
inline int DlgDirList(HWND hDlg, LPWSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
	assertl_reflect_as(auto h = ::DlgDirListW(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType), h);
// DlgDirSelectEx
inline void DlgDirSelectEx(HWND hwndDlg, LPSTR lpString, int chCount, int idListBox)
	assertl_reflect_as(::DlgDirSelectExA(hwndDlg, lpString, chCount, idListBox));
inline void DlgDirSelectEx(HWND hwndDlg, LPWSTR lpString, int chCount, int idListBox)
	assertl_reflect_as(::DlgDirSelectExW(hwndDlg, lpString, chCount, idListBox));
// DlgDirListComboBox
inline int DlgDirListComboBox(HWND hDlg, LPSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
	assertl_reflect_as(auto h = ::DlgDirListComboBoxA(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype), h);
inline int DlgDirListComboBox(HWND hDlg, LPWSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
	assertl_reflect_as(auto h = ::DlgDirListComboBoxW(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype), h);
// DlgDirSelectComboBoxEx
inline void DlgDirSelectComboBoxEx(HWND hwndDlg, LPSTR lpString, int cchOut, int idComboBox)
	assertl_reflect_as(::DlgDirSelectComboBoxExA(hwndDlg, lpString, cchOut, idComboBox));
inline void DlgDirSelectComboBoxEx(HWND hwndDlg, LPWSTR lpString, int cchOut, int idComboBox)
	assertl_reflect_as(::DlgDirSelectComboBoxExW(hwndDlg, lpString, cchOut, idComboBox));
// SetScrollInfo
inline int SetScrollInfo(HWND hwnd, int nBar, LPCSCROLLINFO lpsi, BOOL redraw)
	reflect_as(::SetScrollInfo(hwnd, nBar, lpsi, redraw));
// GetScrollInfo
inline void GetScrollInfo(HWND hwnd, int nBar, LPSCROLLINFO lpsi)
	assertl_reflect_as(::GetScrollInfo(hwnd, nBar, lpsi));
// DefFrameProc
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT DefFrameProc(HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 reflect_as(::DefFrameProcW(hWnd, hWndMDIClient, uMsg, wParam, lParam))
	else reflect_as(::DefFrameProcA(hWnd, hWndMDIClient, uMsg, wParam, lParam))
}
// DefMDIChildProc
template<bool IsUnicode = WX::IsUnicode>
inline LRESULT DefMDIChildProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if_c (IsUnicode)
		 reflect_as(::DefMDIChildProcW(hWnd, uMsg, wParam, lParam))
	else reflect_as(::DefMDIChildProcA(hWnd, uMsg, wParam, lParam))
}
// TranslateMDISysAccel
inline bool TranslateMDISysAccel(HWND hWndClient, LPMSG lpMsg)
	reflect_as(::TranslateMDISysAccel(hWndClient, lpMsg));
// ArrangeIconicWindows
inline UINT ArrangeIconicWindows(HWND hWnd)
	assertl_reflect_as(auto h = ::ArrangeIconicWindows(hWnd), h);
// CreateMDIWindow
inline HWND CreateMDIWindow(LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
	assertl_reflect_as(auto h = ::CreateMDIWindowA(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam), h);
inline HWND CreateMDIWindow(LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
	assertl_reflect_as(auto h = ::CreateMDIWindowW(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam), h);
// TileWindows
inline WORD TileWindows(HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND FAR * lpKids)
	assertl_reflect_as(auto h = ::TileWindows(hwndParent, wHow, lpRect, cKids, lpKids), h);
// CascadeWindows
inline WORD CascadeWindows(HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND FAR * lpKids)
	assertl_reflect_as(auto h = ::CascadeWindows(hwndParent, wHow, lpRect, cKids, lpKids), h);
// WinHelp
inline void WinHelp(HWND hWndMain, LPCSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
	assertl_reflect_as(::WinHelpA(hWndMain, lpszHelp, uCommand, dwData));
inline void WinHelp(HWND hWndMain, LPCWSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
	assertl_reflect_as(::WinHelpW(hWndMain, lpszHelp, uCommand, dwData));
// GetGuiResources
inline DWORD GetGuiResources(HANDLE hProcess, DWORD uiFlags)
	assertl_reflect_as(auto h = ::GetGuiResources(hProcess, uiFlags), h);
// ChangeDisplaySettings
inline LONG ChangeDisplaySettings(DEVMODEA* lpDevMode, DWORD dwFlags)
	reflect_as(::ChangeDisplaySettingsA(lpDevMode, dwFlags));
inline LONG ChangeDisplaySettings(DEVMODEW* lpDevMode, DWORD dwFlags)
	reflect_as(::ChangeDisplaySettingsW(lpDevMode, dwFlags));
// ChangeDisplaySettingsEx
inline LONG ChangeDisplaySettingsEx(LPCSTR lpszDeviceName, DEVMODEA* lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
	reflect_as(::ChangeDisplaySettingsExA(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam));
inline LONG ChangeDisplaySettingsEx(LPCWSTR lpszDeviceName, DEVMODEW* lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
	reflect_as(::ChangeDisplaySettingsExW(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam));
// EnumDisplaySettings
inline void EnumDisplaySettings(LPCSTR lpszDeviceName, DWORD iModeNum, DEVMODEA* lpDevMode)
	assertl_reflect_as(::EnumDisplaySettingsA(lpszDeviceName, iModeNum, lpDevMode));
inline void EnumDisplaySettings(LPCWSTR lpszDeviceName, DWORD iModeNum, DEVMODEW* lpDevMode)
	assertl_reflect_as(::EnumDisplaySettingsW(lpszDeviceName, iModeNum, lpDevMode));
// EnumDisplaySettingsEx
inline void EnumDisplaySettingsEx(LPCSTR lpszDeviceName, DWORD iModeNum, DEVMODEA* lpDevMode, DWORD dwFlags)
	assertl_reflect_as(::EnumDisplaySettingsExA(lpszDeviceName, iModeNum, lpDevMode, dwFlags));
inline void EnumDisplaySettingsEx(LPCWSTR lpszDeviceName, DWORD iModeNum, DEVMODEW* lpDevMode, DWORD dwFlags)
	assertl_reflect_as(::EnumDisplaySettingsExW(lpszDeviceName, iModeNum, lpDevMode, dwFlags));
// EnumDisplayDevices
inline void EnumDisplayDevices(LPCSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEA lpDisplayDevice, DWORD dwFlags)
	assertl_reflect_as(::EnumDisplayDevicesA(lpDevice, iDevNum, lpDisplayDevice, dwFlags));
inline void EnumDisplayDevices(LPCWSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEW lpDisplayDevice, DWORD dwFlags)
	assertl_reflect_as(::EnumDisplayDevicesW(lpDevice, iDevNum, lpDisplayDevice, dwFlags));
// GetDisplayConfigBufferSizes
inline LONG GetDisplayConfigBufferSizes(UINT32 flags, UINT32* numPathArrayElements, UINT32* numModeInfoArrayElements)
	reflect_as(::GetDisplayConfigBufferSizes(flags, numPathArrayElements, numModeInfoArrayElements));
// SetDisplayConfig
inline LONG SetDisplayConfig(UINT32 numPathArrayElements, DISPLAYCONFIG_PATH_INFO* pathArray, UINT32 numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO* modeInfoArray, UINT32 flags)
	reflect_as(::SetDisplayConfig(numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, flags));
// QueryDisplayConfig
inline LONG QueryDisplayConfig(UINT32 flags, UINT32* numPathArrayElements, DISPLAYCONFIG_PATH_INFO* pathArray, UINT32* numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO* modeInfoArray, DISPLAYCONFIG_TOPOLOGY_ID* currentTopologyId)
	reflect_as(::QueryDisplayConfig(flags, numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, currentTopologyId));
// DisplayConfigGetDeviceInfo
inline LONG DisplayConfigGetDeviceInfo(DISPLAYCONFIG_DEVICE_INFO_HEADER* requestPacket)
	reflect_as(::DisplayConfigGetDeviceInfo(requestPacket));
// DisplayConfigSetDeviceInfo
inline LONG DisplayConfigSetDeviceInfo(DISPLAYCONFIG_DEVICE_INFO_HEADER* setPacket)
	reflect_as(::DisplayConfigSetDeviceInfo(setPacket));
// SystemParametersInfo
template<bool IsUnicode = WX::IsUnicode>
inline void SystemParametersInfo(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni) {
	if_c (IsUnicode)
		 assertl_reflect_as(::SystemParametersInfoW(uiAction, uiParam, pvParam, fWinIni))
	else assertl_reflect_as(::SystemParametersInfoA(uiAction, uiParam, pvParam, fWinIni))
}
// SystemParametersInfoForDpi
inline void SystemParametersInfoForDpi(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni, UINT dpi)
	assertl_reflect_as(::SystemParametersInfoForDpi(uiAction, uiParam, pvParam, fWinIni, dpi));
// SoundSentry
inline void SoundSentry()
	assertl_reflect_as(::SoundSentry());
// SetDebugErrorLevel
// SetLastErrorEx
// InternalGetWindowText
inline int InternalGetWindowText(HWND hWnd, LPWSTR pString, int cchMaxCount)
	nt_assertl_reflect_to(auto h = ::InternalGetWindowText(hWnd, pString, cchMaxCount), h);
// EndTask
// CancelShutdown
// MonitorFromPoint
inline HMONITOR MonitorFromPoint(POINT pt, DWORD dwFlags)
	reflect_as(::MonitorFromPoint(pt, dwFlags));
// MonitorFromRect
inline HMONITOR MonitorFromRect(LPCRECT lprc, DWORD dwFlags)
	reflect_as(::MonitorFromRect(lprc, dwFlags));
inline HMONITOR MonitorFromWindow(HWND hwnd, DWORD dwFlags)
	reflect_as(::MonitorFromWindow(hwnd, dwFlags));
// GetMonitorInfo
template<bool IsUnicode = WX::IsUnicode>
inline void GetMonitorInfo(HMONITOR hMonitor, LPMONITORINFO lpmi) {
	if_c (IsUnicode)
		 assertl_reflect_as(::GetMonitorInfoW(hMonitor, lpmi))
	else assertl_reflect_as(::GetMonitorInfoA(hMonitor, lpmi))
}
// EnumDisplayMonitors
inline void EnumDisplayMonitors(HDC hdc, LPCRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData)
	assertl_reflect_as(::EnumDisplayMonitors(hdc, lprcClip, lpfnEnum, dwData));
// NotifyWinEvent
inline void NotifyWinEvent(DWORD event, HWND hwnd, LONG idObject, LONG idChild)
	reflect_to(::NotifyWinEvent(event, hwnd, idObject, idChild));
// SetWinEventHook
inline HWINEVENTHOOK SetWinEventHook(DWORD eventMin, DWORD eventMax, HMODULE hmodWinEventProc, WINEVENTPROC pfnWinEventProc, DWORD idProcess, DWORD idThread, DWORD dwFlags)
	assertl_reflect_as(auto h = ::SetWinEventHook(eventMin, eventMax, hmodWinEventProc, pfnWinEventProc, idProcess, idThread, dwFlags), h);
// IsWinEventHookInstalled
inline bool IsWinEventHookInstalled(DWORD event)
	reflect_as(::IsWinEventHookInstalled(event));
// UnhookWinEvent
inline void UnhookWinEvent(HWINEVENTHOOK hWinEventHook)
	assertl_reflect_as(::UnhookWinEvent(hWinEventHook));
// GetGUIThreadInfo
inline void GetGUIThreadInfo(DWORD idThread, PGUITHREADINFO pgui)
	assertl_reflect_as(::GetGUIThreadInfo(idThread, pgui));
// BlockInput
inline void BlockInput(BOOL fBlockIt)
	assertl_reflect_as(::BlockInput(fBlockIt));
// SetProcessDPIAware
inline void SetProcessDPIAware()
	assertl_reflect_as(::SetProcessDPIAware());
// IsProcessDPIAware
inline bool IsProcessDPIAware()
	reflect_as(::IsProcessDPIAware());
// SetThreadDpiAwarenessContext
inline DPI_AWARENESS_CONTEXT SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT dpiContext)
	assertl_reflect_as(auto h = ::SetThreadDpiAwarenessContext(dpiContext), h);
// GetThreadDpiAwarenessContext
inline DPI_AWARENESS_CONTEXT GetThreadDpiAwarenessContext()
	reflect_as(::GetThreadDpiAwarenessContext());
// GetWindowDpiAwarenessContext
inline DPI_AWARENESS_CONTEXT GetWindowDpiAwarenessContext(HWND hwnd)
	assertl_reflect_as(auto h = ::GetWindowDpiAwarenessContext(hwnd), h);
// GetAwarenessFromDpiAwarenessContext
inline DPI_AWARENESS GetAwarenessFromDpiAwarenessContext(DPI_AWARENESS_CONTEXT value)
	assertl_reflect_as(auto h = ::GetAwarenessFromDpiAwarenessContext(value), h);
// GetDpiFromDpiAwarenessContext
inline UINT GetDpiFromDpiAwarenessContext(DPI_AWARENESS_CONTEXT value)
	reflect_as(::GetDpiFromDpiAwarenessContext(value));
// AreDpiAwarenessContextsEqual
inline bool AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT dpiContextA, DPI_AWARENESS_CONTEXT dpiContextB)
	reflect_as(::AreDpiAwarenessContextsEqual(dpiContextA, dpiContextB));
// IsValidDpiAwarenessContext
inline bool IsValidDpiAwarenessContext(DPI_AWARENESS_CONTEXT value)
	reflect_as(::IsValidDpiAwarenessContext(value));
inline UINT GetDpiForWindow(HWND hwnd)
	assertl_reflect_as(auto h = ::GetDpiForWindow(hwnd), h);
// GetDpiForSystem
inline UINT GetDpiForSystem()
	reflect_as(::GetDpiForSystem());
// GetSystemDpiForProcess
inline UINT GetSystemDpiForProcess(HANDLE hProcess)
	reflect_as(::GetSystemDpiForProcess(hProcess));
// EnableNonClientDpiScaling
inline void EnableNonClientDpiScaling(HWND hwnd)
	assertl_reflect_as(::EnableNonClientDpiScaling(hwnd));
// InheritWindowMonitor
inline void InheritWindowMonitor(HWND hwnd, HWND hwndInherit)
	assertl_reflect_as(::InheritWindowMonitor(hwnd, hwndInherit));
// SetProcessDpiAwarenessContext
inline void SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT value)
	assertl_reflect_as(::SetProcessDpiAwarenessContext(value));
#if (NTDDI_VERSION >= NTDDI_WIN10_19H1)
// GetDpiAwarenessContextForProcess
inline DPI_AWARENESS_CONTEXT GetDpiAwarenessContextForProcess(HANDLE hProcess)
	reflect_as(::GetDpiAwarenessContextForProcess(hProcess));
#endif
// SetThreadDpiHostingBehavior
inline DPI_HOSTING_BEHAVIOR SetThreadDpiHostingBehavior(DPI_HOSTING_BEHAVIOR value)
	assertl_reflect_as(auto h = ::SetThreadDpiHostingBehavior(value), h);
// GetThreadDpiHostingBehavior
inline DPI_HOSTING_BEHAVIOR GetThreadDpiHostingBehavior()
	reflect_as(::GetThreadDpiHostingBehavior());
// GetWindowDpiHostingBehavior
inline DPI_HOSTING_BEHAVIOR GetWindowDpiHostingBehavior(HWND hwnd)
	reflect_as(::GetWindowDpiHostingBehavior(hwnd));
// GetWindowModuleFileName
inline UINT GetWindowModuleFileName(HWND hwnd, LPSTR pszFileName, UINT cchFileNameMax)
	assertl_reflect_as(auto h = ::GetWindowModuleFileNameA(hwnd, pszFileName, cchFileNameMax), h);
inline UINT GetWindowModuleFileName(HWND hwnd, LPWSTR pszFileName, UINT cchFileNameMax)
	assertl_reflect_as(auto h = ::GetWindowModuleFileNameW(hwnd, pszFileName, cchFileNameMax), h);
// GetCursorInfo
inline void GetCursorInfo(PCURSORINFO pci)
	assertl_reflect_as(::GetCursorInfo(pci));
// GetWindowInfo
inline void GetWindowInfo(HWND hwnd, PWINDOWINFO pwi)
	assertl_reflect_as(::GetWindowInfo(hwnd, pwi));
// GetTitleBarInfo
inline void GetTitleBarInfo(HWND hwnd, PTITLEBARINFO pti)
	assertl_reflect_as(::GetTitleBarInfo(hwnd, pti));
// GetMenuBarInfo
inline void GetMenuBarInfo(HWND hwnd, LONG idObject, LONG idItem, PMENUBARINFO pmbi)
	assertl_reflect_as(::GetMenuBarInfo(hwnd, idObject, idItem, pmbi));
// GetScrollBarInfo
inline void GetScrollBarInfo(HWND hwnd, LONG idObject, PSCROLLBARINFO psbi)
	assertl_reflect_as(::GetScrollBarInfo(hwnd, idObject, psbi));
// GetComboBoxInfo
inline void GetComboBoxInfo(HWND hwndCombo, PCOMBOBOXINFO pcbi)
	assertl_reflect_as(::GetComboBoxInfo(hwndCombo, pcbi));
// GetAncestor
inline HWND GetAncestor(HWND hwnd, UINT gaFlags)
	reflect_as(::GetAncestor(hwnd, gaFlags));
// RealChildWindowFromPoint
inline HWND RealChildWindowFromPoint(HWND hwndParent, POINT ptParentClientCoords)
	reflect_as(::RealChildWindowFromPoint(hwndParent, ptParentClientCoords));
// RealGetWindowClass
inline UINT RealGetWindowClass(HWND hwnd, LPSTR ptszClassName, UINT cchClassNameMax)
	assertl_reflect_as(auto h = ::RealGetWindowClassA(hwnd, ptszClassName, cchClassNameMax), h);
inline UINT RealGetWindowClass(HWND hwnd, LPWSTR ptszClassName, UINT cchClassNameMax)
	assertl_reflect_as(auto h = ::RealGetWindowClassW(hwnd, ptszClassName, cchClassNameMax), h);
// GetAltTabInfo
inline void GetAltTabInfo(HWND hwnd, int iItem, PALTTABINFO pati, LPSTR pszItemText, UINT cchItemText)
	assertl_reflect_as(::GetAltTabInfoA(hwnd, iItem, pati, pszItemText, cchItemText));
inline void GetAltTabInfo(HWND hwnd, int iItem, PALTTABINFO pati, LPWSTR pszItemText, UINT cchItemText)
	assertl_reflect_as(::GetAltTabInfoW(hwnd, iItem, pati, pszItemText, cchItemText));
// GetListBoxInfo
inline DWORD GetListBoxInfo(HWND hwnd)
	reflect_as(::GetListBoxInfo(hwnd));
// LockWorkStation
inline void LockWorkStation()
	assertl_reflect_as(::LockWorkStation());
// UserHandleGrantAccess
inline void UserHandleGrantAccess(HANDLE hUserHandle, HANDLE hJob, BOOL bGrant)
	assertl_reflect_as(::UserHandleGrantAccess(hUserHandle, hJob, bGrant));
// GetRawInputData
inline UINT GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
	assertl_reflect_as(auto h = ::GetRawInputData(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader); h != -1, h);
// GetRawInputDeviceInfo
template<bool IsUnicode = WX::IsUnicode>
inline UINT GetRawInputDeviceInfo(HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize) {
	if_c (IsUnicode)
		 assertl_reflect_as(auto h = ::GetRawInputDeviceInfoW(hDevice, uiCommand, pData, pcbSize); h != -1, h)
	else assertl_reflect_as(auto h = ::GetRawInputDeviceInfoA(hDevice, uiCommand, pData, pcbSize); h != -1, h)
}
// GetRawInputBuffer
inline UINT GetRawInputBuffer(PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader)
	assertl_reflect_as(auto h = ::GetRawInputBuffer(pData, pcbSize, cbSizeHeader); h != -1, h);
// RegisterRawInputDevices
inline void RegisterRawInputDevices(PCRAWINPUTDEVICE pRawInputDevices, UINT uiNumDevices, UINT cbSize)
	assertl_reflect_as(::RegisterRawInputDevices(pRawInputDevices, uiNumDevices, cbSize));
// GetRegisteredRawInputDevices
inline UINT GetRegisteredRawInputDevices(PRAWINPUTDEVICE pRawInputDevices, PUINT puiNumDevices, UINT cbSize)
	assertl_reflect_as(auto h = ::GetRegisteredRawInputDevices(pRawInputDevices, puiNumDevices, cbSize); h != -1, h);
// GetRawInputDeviceList
inline UINT GetRawInputDeviceList(PRAWINPUTDEVICELIST pRawInputDeviceList, PUINT puiNumDevices, UINT cbSize)
	assertl_reflect_as(auto h = ::GetRawInputDeviceList(pRawInputDeviceList, puiNumDevices, cbSize); h != -1, h);
// DefRawInputProc
inline LRESULT DefRawInputProc(PRAWINPUT* paRawInput, INT nInput, UINT cbSizeHeader)
	assertl_reflect_as(auto h = ::DefRawInputProc(paRawInput, nInput, cbSizeHeader), h);
// GetPointerDevices
inline void GetPointerDevices(UINT32* deviceCount, POINTER_DEVICE_INFO *pointerDevices)
	assertl_reflect_as(::GetPointerDevices(deviceCount, pointerDevices));
// GetPointerDevice
inline void GetPointerDevice(HANDLE device, POINTER_DEVICE_INFO *pointerDevice)
	assertl_reflect_as(::GetPointerDevice(device, pointerDevice));
// GetPointerDeviceProperties
inline void GetPointerDeviceProperties(HANDLE device, UINT32* propertyCount, POINTER_DEVICE_PROPERTY *pointerProperties)
	assertl_reflect_as(::GetPointerDeviceProperties(device, propertyCount, pointerProperties));
// RegisterPointerDeviceNotifications
inline void RegisterPointerDeviceNotifications(HWND window, BOOL notifyRange)
	assertl_reflect_as(::RegisterPointerDeviceNotifications(window, notifyRange));
// GetPointerDeviceRects
inline void GetPointerDeviceRects(HANDLE device, RECT* pointerDeviceRect, RECT* displayRect)
	assertl_reflect_as(::GetPointerDeviceRects(device, pointerDeviceRect, displayRect));
// GetPointerDeviceCursors
inline void GetPointerDeviceCursors(HANDLE device, UINT32* cursorCount, POINTER_DEVICE_CURSOR_INFO *deviceCursors)
	assertl_reflect_as(::GetPointerDeviceCursors(device, cursorCount, deviceCursors));
// GetRawPointerDeviceData
inline void GetRawPointerDeviceData(UINT32 pointerId, UINT32 historyCount, UINT32 propertiesCount, POINTER_DEVICE_PROPERTY* pProperties, LONG* pValues)
	assertl_reflect_as(::GetRawPointerDeviceData(pointerId, historyCount, propertiesCount, pProperties, pValues));
// ChangeWindowMessageFilter
inline void ChangeWindowMessageFilter(UINT message, DWORD dwFlag)
	assertl_reflect_as(::ChangeWindowMessageFilter(message, dwFlag));
// ChangeWindowMessageFilterEx
inline void ChangeWindowMessageFilterEx(HWND hwnd, UINT message, DWORD action, PCHANGEFILTERSTRUCT pChangeFilterStruct)
	assertl_reflect_as(::ChangeWindowMessageFilterEx(hwnd, message, action, pChangeFilterStruct));
// GetGestureInfo
inline void GetGestureInfo(HGESTUREINFO hGestureInfo, PGESTUREINFO pGestureInfo)
	assertl_reflect_as(::GetGestureInfo(hGestureInfo, pGestureInfo));
// GetGestureExtraArgs
inline void GetGestureExtraArgs(HGESTUREINFO hGestureInfo, UINT cbExtraArgs, PBYTE pExtraArgs)
	assertl_reflect_as(::GetGestureExtraArgs(hGestureInfo, cbExtraArgs, pExtraArgs));
// CloseGestureInfoHandle
inline void CloseGestureInfoHandle(HGESTUREINFO hGestureInfo)
	assertl_reflect_as(::CloseGestureInfoHandle(hGestureInfo));
// SetGestureConfig
inline void SetGestureConfig(HWND hwnd, DWORD dwReserved, UINT cIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
	assertl_reflect_as(::SetGestureConfig(hwnd, dwReserved, cIDs, pGestureConfig, cbSize));
// GetGestureConfig
inline void GetGestureConfig(HWND hwnd, DWORD dwReserved, DWORD dwFlags, PUINT pcIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
	assertl_reflect_as(::GetGestureConfig(hwnd, dwReserved, dwFlags, pcIDs, pGestureConfig, cbSize));
// ShutdownBlockReasonCreate
inline void ShutdownBlockReasonCreate(HWND hWnd, LPCWSTR pwszReason)
	assertl_reflect_as(::ShutdownBlockReasonCreate(hWnd, pwszReason));
// ShutdownBlockReasonQuery
inline void ShutdownBlockReasonQuery(HWND hWnd, LPWSTR pwszBuff, DWORD *pcchBuff)
	assertl_reflect_as(::ShutdownBlockReasonQuery(hWnd, pwszBuff, pcchBuff));
// ShutdownBlockReasonDestroy
inline void ShutdownBlockReasonDestroy(HWND hWnd)
	assertl_reflect_as(::ShutdownBlockReasonDestroy(hWnd));
// GetCurrentInputMessageSource
inline void GetCurrentInputMessageSource(INPUT_MESSAGE_SOURCE *inputMessageSource)
	assertl_reflect_as(::GetCurrentInputMessageSource(inputMessageSource));
// GetCIMSSM
// GetAutoRotationState
inline void GetAutoRotationState(PAR_STATE pState)
	assertl_reflect_as(::GetAutoRotationState(pState));
// GetDisplayAutoRotationPreferences
inline void GetDisplayAutoRotationPreferences(ORIENTATION_PREFERENCE *pOrientation)
	assertl_reflect_as(::GetDisplayAutoRotationPreferences(pOrientation));
// GetDisplayAutoRotationPreferencesByProcessId
inline void GetDisplayAutoRotationPreferencesByProcessId(DWORD dwProcessId, ORIENTATION_PREFERENCE *pOrientation, BOOL *fRotateScreen)
	assertl_reflect_as(::GetDisplayAutoRotationPreferencesByProcessId(dwProcessId, pOrientation, fRotateScreen));
// SetDisplayAutoRotationPreferences
inline void SetDisplayAutoRotationPreferences(ORIENTATION_PREFERENCE orientation)
	assertl_reflect_as(::SetDisplayAutoRotationPreferences(orientation));
// IsImmersiveProcess
inline bool IsImmersiveProcess(HANDLE hProcess)
	nt_assertl_reflect_to(auto h = ::IsImmersiveProcess(hProcess), h);
// SetProcessRestrictionExemption
inline void SetProcessRestrictionExemption(BOOL fEnableExemption)
	assertl_reflect_as(::SetProcessRestrictionExemption(fEnableExemption));
// ApplyWindowAction
// SetAdditionalForegroundBoostProcesses - Deprecated
// RegisterForTooltipDismissNotification - Deprecated
// IsWindowArranged - Deprecated
// GetCurrentMonitorTopologyId
// RegisterCloakedNotification
#pragma endregion

}
