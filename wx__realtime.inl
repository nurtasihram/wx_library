#pragma once

namespace WX {

#pragma region processthreadsapi.h
// QueueUserAPC
inline void QueueUserAPC(PAPCFUNC pfnAPC, HANDLE hThread, ULONG_PTR dwData)
	assertl_reflect_as(::QueueUserAPC(pfnAPC, hThread, dwData));
#if (NTDDI_VERSION >= NTDDI_WIN10_MN)
// QueueUserAPC2
inline void QueueUserAPC2(PAPCFUNC pfnAPC, HANDLE hThread, ULONG_PTR dwData, QUEUE_USER_APC_FLAGS Flags)
	assertl_reflect_as(::QueueUserAPC2(pfnAPC, hThread, dwData, Flags));
#endif
// GetProcessTimes
inline void GetProcessTimes(HANDLE hProcess, LPFILETIME lpCreationTime, LPFILETIME lpExitTime,
							LPFILETIME lpKernelTime, LPFILETIME lpUserTime)
	assertl_reflect_as(::GetProcessTimes(hProcess, lpCreationTime, lpExitTime, lpKernelTime, lpUserTime));
// GetCurrentProcess
inline HANDLE GetCurrentProcess()
	reflect_as(::GetCurrentProcess());
// GetCurrentProcessId
inline DWORD GetCurrentProcessId()
	reflect_as(::GetCurrentProcessId());
// ExitProcess
inline void ExitProcess(UINT uExitCode)
	reflect_to(::ExitProcess(uExitCode));
// TerminateProcess
inline void TerminateProcess(HANDLE hProcess, UINT uExitCode)
	assertl_reflect_as(::TerminateProcess(hProcess, uExitCode));
// GetExitCodeProcess
inline void GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode)
	assertl_reflect_as(::GetExitCodeProcess(hProcess, lpExitCode));
// SwitchToThread
inline void SwitchToThread()
	assertl_reflect_as(::SwitchToThread());
// CreateThread
inline HANDLE CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize,
						   LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags,
						   LPDWORD lpThreadId)
	assertl_reflect_as(auto h = ::CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId), h);
// CreateRemoteThread
inline HANDLE CreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes,
								 SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter,
								 DWORD dwCreationFlags, LPDWORD lpThreadId)
	assertl_reflect_as(auto h = ::CreateRemoteThread(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId), h);
// GetCurrentThread
inline HANDLE GetCurrentThread()
	reflect_as(::GetCurrentThread());
// GetCurrentThreadId
inline DWORD GetCurrentThreadId()
	reflect_as(::GetCurrentThreadId());
// OpenThread
inline HANDLE OpenThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId)
	assertl_reflect_as(auto h = ::OpenThread(dwDesiredAccess, bInheritHandle, dwThreadId); h != NULL, h);
// SetThreadPriority
inline void SetThreadPriority(HANDLE hThread, int nPriority)
	assertl_reflect_as(::SetThreadPriority(hThread, nPriority));
// SetThreadPriorityBoost
inline void SetThreadPriorityBoost(HANDLE hThread, BOOL bEnable)
	assertl_reflect_as(::SetThreadPriorityBoost(hThread, bEnable));
// GetThreadPriorityBoost
inline void GetThreadPriorityBoost(HANDLE hThread, PBOOL pEnable)
	assertl_reflect_as(::GetThreadPriorityBoost(hThread, pEnable));
// GetThreadPriority
inline int GetThreadPriority(HANDLE hThread)
	assertl_reflect_as(auto res = ::GetThreadPriority(hThread); res != THREAD_PRIORITY_ERROR_RETURN, res);
// ExitThread
inline void ExitThread(DWORD dwExitCode)
	reflect_as(::ExitThread(dwExitCode));
// TerminateThread
inline void TerminateThread(HANDLE hThread, DWORD dwExitCode)
	assertl_reflect_as(::TerminateThread(hThread, dwExitCode));
// GetExitCodeThread
inline void GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode)
	assertl_reflect_as(::GetExitCodeThread(hThread, lpExitCode));
// SuspendThread
inline DWORD SuspendThread(HANDLE hThread)
	assertl_reflect_as(auto res = ::SuspendThread(hThread); res >= 0, res);
// ResumeThread
inline DWORD ResumeThread(HANDLE hThread)
	assertl_reflect_as(auto res = ::ResumeThread(hThread); res >= 0, res);
// TlsAlloc
inline DWORD TlsAlloc()
	assertl_reflect_as(auto n = ::TlsAlloc(); n != TLS_OUT_OF_INDEXES, n);
// TlsGetValue
inline LPVOID TlsGetValue(DWORD dwTlsIndex)
	nt_assertl_reflect_to(auto p = ::TlsGetValue(dwTlsIndex), p);
// TlsSetValue
inline void TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue)
	assertl_reflect_as(::TlsSetValue(dwTlsIndex, lpTlsValue));
// TlsFree
inline void TlsFree(DWORD dwTlsIndex)
	assertl_reflect_as(::TlsFree(dwTlsIndex));
// CreateProcess // GetExitCodeProcess
inline void CreateProcess(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
						  LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
						  LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo,
						  LPPROCESS_INFORMATION lpProcessInformation)
	assertl_reflect_as(::CreateProcessA(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes,
										bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
										lpStartupInfo, lpProcessInformation));
inline void CreateProcess(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
						  LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
						  LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
						  LPPROCESS_INFORMATION lpProcessInformation)
	assertl_reflect_as(::CreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes,
										bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory,
										lpStartupInfo, lpProcessInformation));
// SetProcessShutdownParameters
inline void SetProcessShutdownParameters(DWORD dwLevel, DWORD dwFlags)
	assertl_reflect_as(::SetProcessShutdownParameters(dwLevel, dwFlags));
// GetProcessVersion
inline DWORD GetProcessVersion(DWORD ProcessId)
	assertl_reflect_as(auto n = ::GetProcessVersion(ProcessId), n);
// CreateProcessAsUser // GetExitCodeProcess
inline void CreateProcessAsUser(HANDLE hToken, LPCSTR lpApplicationName, LPSTR lpCommandLine,
								LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
								BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
								LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo,
								LPPROCESS_INFORMATION lpProcessInformation)
	assertl_reflect_as(::CreateProcessAsUserA(hToken, lpApplicationName, lpCommandLine,
											  lpProcessAttributes, lpThreadAttributes, bInheritHandles,
											  dwCreationFlags, lpEnvironment, lpCurrentDirectory,
											  lpStartupInfo, lpProcessInformation));
inline void CreateProcessAsUser(HANDLE hToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
								LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
								BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
								LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
								LPPROCESS_INFORMATION lpProcessInformation)
	assertl_reflect_as(::CreateProcessAsUserW(hToken, lpApplicationName, lpCommandLine,
											  lpProcessAttributes, lpThreadAttributes, bInheritHandles,
											  dwCreationFlags, lpEnvironment, lpCurrentDirectory,
											  lpStartupInfo, lpProcessInformation));
// GetCurrentProcessToken
inline HANDLE GetCurrentProcessToken()
	reflect_as(::GetCurrentProcessToken());
// GetCurrentThreadToken
inline HANDLE GetCurrentThreadToken()
	reflect_as(::GetCurrentThreadToken());
// GetCurrentThreadEffectiveToken
inline HANDLE GetCurrentThreadEffectiveToken()
	reflect_as(::GetCurrentThreadEffectiveToken());
// SetThreadToken
inline void SetThreadToken(PHANDLE ThreadToken, HANDLE hToken)
	assertl_reflect_as(::SetThreadToken(ThreadToken, hToken));
// OpenProcessToken
inline void OpenProcessToken(HANDLE hProcess, DWORD dwDesiredAccess, PHANDLE lpToken)
	assertl_reflect_as(::OpenProcessToken(hProcess, dwDesiredAccess, lpToken));
// OpenThreadToken
inline void OpenThreadToken(HANDLE hThread, DWORD dwDesiredAccess, BOOL bOpenAsSelf, PHANDLE lpToken)
	assertl_reflect_as(::OpenThreadToken(hThread, dwDesiredAccess, bOpenAsSelf, lpToken));
// SetPriorityClass
inline void SetPriorityClass(HANDLE hProcess, DWORD dwPriorityClass)
	assertl_reflect_as(::SetPriorityClass(hProcess, dwPriorityClass));
// GetPriorityClass
inline DWORD GetPriorityClass(HANDLE hProcess)
	assertl_reflect_as(auto res = ::GetPriorityClass(hProcess), res);
// SetThreadStackGuarantee
inline void SetThreadStackGuarantee(PULONG StackSizeInBytes)
	assertl_reflect_as(::SetThreadStackGuarantee(StackSizeInBytes));
// ProcessIdToSessionId
inline void ProcessIdToSessionId(DWORD dwProcessId, DWORD* pSessionId)
	assertl_reflect_as(::ProcessIdToSessionId(dwProcessId, pSessionId));
// GetProcessId
inline DWORD GetProcessId(HANDLE hProcess)
	assertl_reflect_as(auto res = ::GetProcessId(hProcess), res);
// GetThreadId
inline DWORD GetThreadId(HANDLE hThread)
	assertl_reflect_as(auto res = ::GetThreadId(hThread), res);
// FlushProcessWriteBuffers
inline void FlushProcessWriteBuffers()
	reflect_as(::FlushProcessWriteBuffers());
// GetProcessIdOfThread
inline DWORD GetProcessIdOfThread(HANDLE hThread)
	assertl_reflect_as(auto res = ::GetProcessIdOfThread(hThread); res != 0, res);
// InitializeProcThreadAttributeList
inline void InitializeProcThreadAttributeList(LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, DWORD dwAttributeCount, DWORD dwFlags, PSIZE_T lpSize)
	assertl_reflect_as(::InitializeProcThreadAttributeList(lpAttributeList, dwAttributeCount, dwFlags, lpSize));
// DeleteProcThreadAttributeList
inline void DeleteProcThreadAttributeList(LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList)
	reflect_as(::DeleteProcThreadAttributeList(lpAttributeList));
// UpdateProcThreadAttribute
inline void UpdateProcThreadAttribute(LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, DWORD dwFlags, DWORD_PTR Attribute, PVOID lpValue, SIZE_T cbSize, PVOID lpPreviousValue, PSIZE_T lpReturnSize)
	assertl_reflect_as(::UpdateProcThreadAttribute(lpAttributeList, dwFlags, Attribute, lpValue, cbSize, lpPreviousValue, lpReturnSize));
#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
// SetProcessDynamicEHContinuationTargets
inline void SetProcessDynamicEHContinuationTargets(HANDLE hProcess, USHORT NumberOfTargets, PPROCESS_DYNAMIC_EH_CONTINUATION_TARGET pTargets)
	assertl_reflect_as(::SetProcessDynamicEHContinuationTargets(hProcess, NumberOfTargets, pTargets));
#endif
#if (NTDDI_VERSION >= NTDDI_WIN10_FE)
// SetProcessDynamicEnforcedCetCompatibleRanges
inline void SetProcessDynamicEnforcedCetCompatibleRanges(HANDLE hProcess, USHORT NumberOfRanges, PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE pRanges)
	assertl_reflect_as(::SetProcessDynamicEnforcedCetCompatibleRanges(hProcess, NumberOfRanges, pRanges));
#endif
// SetProcessAffinityUpdateMode
inline void SetProcessAffinityUpdateMode(HANDLE hProcess, DWORD dwFlags)
	assertl_reflect_as(::SetProcessAffinityUpdateMode(hProcess, dwFlags));
// QueryProcessAffinityUpdateMode
inline void QueryProcessAffinityUpdateMode(HANDLE hProcess, LPDWORD lpdwFlags)
	assertl_reflect_as(::QueryProcessAffinityUpdateMode(hProcess, lpdwFlags));
// CreateRemoteThreadEx
inline HANDLE CreateRemoteThreadEx(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, LPDWORD lpThreadId)
	assertl_reflect_as(auto h = ::CreateRemoteThreadEx(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpAttributeList, lpThreadId), h);
// GetCurrentThreadStackLimits
inline void GetCurrentThreadStackLimits(PULONG_PTR LowLimit, PULONG_PTR HighLimit)
	reflect_as(::GetCurrentThreadStackLimits(LowLimit, HighLimit));
// GetThreadContext
inline void GetThreadContext(HANDLE hThread, LPCONTEXT lpContext)
	assertl_reflect_as(::GetThreadContext(hThread, lpContext));
// GetProcessMitigationPolicy
inline void GetProcessMitigationPolicy(HANDLE hProcess, PROCESS_MITIGATION_POLICY MitigationPolicy, PVOID lpBuffer, SIZE_T dwLength)
	assertl_reflect_as(::GetProcessMitigationPolicy(hProcess, MitigationPolicy, lpBuffer, dwLength));
// SetThreadContext
inline void SetThreadContext(HANDLE hThread, const CONTEXT* lpContext)
	assertl_reflect_as(::SetThreadContext(hThread, lpContext));
// SetProcessMitigationPolicy
inline void SetProcessMitigationPolicy(PROCESS_MITIGATION_POLICY MitigationPolicy, PVOID lpBuffer, SIZE_T dwLength)
	assertl_reflect_as(::SetProcessMitigationPolicy(MitigationPolicy, lpBuffer, dwLength));
// FlushInstructionCache
inline void FlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize)
	assertl_reflect_as(::FlushInstructionCache(hProcess, lpBaseAddress, dwSize));
// GetThreadTimes
inline void GetThreadTimes(HANDLE hThread, LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime)
	assertl_reflect_as(::GetThreadTimes(hThread, lpCreationTime, lpExitTime, lpKernelTime, lpUserTime));
// OpenProcess
inline HANDLE OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
	assertl_reflect_as(auto h = ::OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId), h);
// IsProcessorFeaturePresent
inline bool IsProcessorFeaturePresent(DWORD ProcessorFeature)
	reflect_as(::IsProcessorFeaturePresent(ProcessorFeature));
// GetProcessHandleCount
inline void GetProcessHandleCount(HANDLE hProcess, PDWORD pdwHandleCount)
	assertl_reflect_as(::GetProcessHandleCount(hProcess, pdwHandleCount));
// GetCurrentProcessorNumber
inline DWORD GetCurrentProcessorNumber()
	reflect_as(::GetCurrentProcessorNumber());
// SetThreadIdealProcessorEx
inline void SetThreadIdealProcessorEx(HANDLE hThread, PPROCESSOR_NUMBER lpIdealProcessor, PPROCESSOR_NUMBER lpPreviousProcessor)
	assertl_reflect_as(::SetThreadIdealProcessorEx(hThread, lpIdealProcessor, lpPreviousProcessor));
// GetThreadIdealProcessorEx
inline void GetThreadIdealProcessorEx(HANDLE hThread, PPROCESSOR_NUMBER lpIdealProcessor)
	assertl_reflect_as(::GetThreadIdealProcessorEx(hThread, lpIdealProcessor));
// GetCurrentProcessorNumberEx
inline void GetCurrentProcessorNumber(PPROCESSOR_NUMBER lpProcessorNumber)
	reflect_as(::GetCurrentProcessorNumberEx(lpProcessorNumber));
// GetProcessPriorityBoost
inline void GetProcessPriorityBoost(HANDLE hProcess, PBOOL pDisablePriorityBoost)
	assertl_reflect_as(::GetProcessPriorityBoost(hProcess, pDisablePriorityBoost));
// SetProcessPriorityBoost
inline void SetProcessPriorityBoost(HANDLE hProcess, BOOL bDisablePriorityBoost)
	assertl_reflect_as(::SetProcessPriorityBoost(hProcess, bDisablePriorityBoost));
// GetThreadIOPendingFlag
inline void GetThreadIOPendingFlag(HANDLE hThread, PBOOL lpIOIsPending)
	assertl_reflect_as(::GetThreadIOPendingFlag(hThread, lpIOIsPending));
// GetSystemTimes
inline void GetSystemTimes(LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime)
	assertl_reflect_as(::GetSystemTimes(lpIdleTime, lpKernelTime, lpUserTime));
// GetThreadInformation
inline void GetThreadInformation(HANDLE hThread, THREAD_INFORMATION_CLASS ThreadInformationClass, LPVOID lpThreadInformation, DWORD dwThreadInformationSize)
	assertl_reflect_as(::GetThreadInformation(hThread, ThreadInformationClass, lpThreadInformation, dwThreadInformationSize));
// SetThreadInformation
inline void SetThreadInformation(HANDLE hThread, THREAD_INFORMATION_CLASS ThreadInformationClass, LPVOID lpThreadInformation, DWORD dwThreadInformationSize)
	assertl_reflect_as(::SetThreadInformation(hThread, ThreadInformationClass, lpThreadInformation, dwThreadInformationSize));
// IsProcessCritical
inline void IsProcessCritical(HANDLE hProcess, PBOOL Critical)
	assertl_reflect_as(::IsProcessCritical(hProcess, Critical));
// SetProtectedPolicy
inline void SetProtectedPolicy(LPCGUID PolicyGuid, ULONG_PTR PolicyData, PULONG_PTR OldPolicyValue)
	assertl_reflect_as(::SetProtectedPolicy(PolicyGuid, PolicyData, OldPolicyValue));
// QueryProtectedPolicy
inline bool QueryProtectedPolicy(LPCGUID PolicyGuid, PULONG_PTR PolicyValue)
	reflect_as(::QueryProtectedPolicy(PolicyGuid, PolicyValue));
// SetThreadIdealProcessor
inline DWORD SetThreadIdealProcessor(HANDLE hThread, DWORD dwIdealProcessor)
	assertl_reflect_as(auto res = ::SetThreadIdealProcessor(hThread, dwIdealProcessor); res >= 0, res);
// SetProcessInformation
inline void SetProcessInformation(HANDLE hProcess, PROCESS_INFORMATION_CLASS ProcessInformationClass, LPVOID lpProcessInformation, DWORD dwProcessInformationSize)
	assertl_reflect_as(::SetProcessInformation(hProcess, ProcessInformationClass, lpProcessInformation, dwProcessInformationSize));
// GetProcessInformation
inline void GetProcessInformation(HANDLE hProcess, PROCESS_INFORMATION_CLASS ProcessInformationClass, LPVOID lpProcessInformation, DWORD dwProcessInformationSize)
	assertl_reflect_as(::GetProcessInformation(hProcess, ProcessInformationClass, lpProcessInformation, dwProcessInformationSize));
// GetProcessShutdownParameters
inline void GetProcessShutdownParameters(LPDWORD lpdwLevel, LPDWORD lpdwFlags)
	assertl_reflect_as(::GetProcessShutdownParameters(lpdwLevel, lpdwFlags));
//// SetThreadDescription
//inline void SetThreadDescription(HANDLE hThread, PCWSTR lpDescription)
//	assertl_reflect_as(::SetThreadDescription(hThread, lpDescription));
//// GetThreadDescription
//inline void GetThreadDescription(HANDLE hThread, PWSTR* lpDescription)
//	assertl_reflect_as(::GetThreadDescription(hThread, lpDescription));
// TlsGetValue2 - Deprecated
#pragma endregion

#pragma region psai.h
#pragma endregion

#pragma region synchapi.h
// InitializeSRWLock
inline void InitializeSRWLock(PSRWLOCK SRWLock)
	reflect_to(::InitializeSRWLock(SRWLock));
// ReleaseSRWLockExclusive
inline void ReleaseSRWLockExclusive(PSRWLOCK SRWLock)
	reflect_to(::ReleaseSRWLockExclusive(SRWLock));
// ReleaseSRWLockShared
inline void ReleaseSRWLockShared(PSRWLOCK SRWLock)
	reflect_to(::ReleaseSRWLockShared(SRWLock));
// AcquireSRWLockExclusive
inline void AcquireSRWLockExclusive(PSRWLOCK SRWLock)
	reflect_to(::AcquireSRWLockExclusive(SRWLock));
// AcquireSRWLockShared
inline void AcquireSRWLockShared(PSRWLOCK SRWLock)
	reflect_to(::AcquireSRWLockShared(SRWLock));
// TryAcquireSRWLockExclusive
inline bool TryAcquireSRWLockExclusive(PSRWLOCK SRWLock)
	reflect_as(::TryAcquireSRWLockExclusive(SRWLock));
// TryAcquireSRWLockShared
inline bool TryAcquireSRWLockShared(PSRWLOCK SRWLock)
	reflect_as(::TryAcquireSRWLockShared(SRWLock));
// InitializeCriticalSection
inline void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
	reflect_to(::InitializeCriticalSection(lpCriticalSection));
// EnterCriticalSection
inline void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
	reflect_to(::EnterCriticalSection(lpCriticalSection));
// LeaveCriticalSection
inline void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
	reflect_to(::LeaveCriticalSection(lpCriticalSection));
// InitializeCriticalSectionAndSpinCount
inline void InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount)
	assertl_reflect_as(::InitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount));
// InitializeCriticalSectionEx
inline void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount, DWORD Flags)
	assertl_reflect_as(::InitializeCriticalSectionEx(lpCriticalSection, dwSpinCount, Flags));
// SetCriticalSectionSpinCount
inline DWORD SetCriticalSectionSpinCount(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount)
	reflect_as(::SetCriticalSectionSpinCount(lpCriticalSection, dwSpinCount));
// TryEnterCriticalSection
inline bool TryEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
	reflect_as(::TryEnterCriticalSection(lpCriticalSection));
// DeleteCriticalSection
inline void DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
	reflect_to(::DeleteCriticalSection(lpCriticalSection));
// InitOnceInitialize
inline void InitOnceInitialize(PINIT_ONCE InitOnce)
	reflect_to(::InitOnceInitialize(InitOnce));
// InitOnceExecuteOnce
inline void InitOnceExecuteOnce(PINIT_ONCE InitOnce, PINIT_ONCE_FN InitFn, PVOID Parameter, LPVOID *Context)
	assertl_reflect_as(::InitOnceExecuteOnce(InitOnce, InitFn, Parameter, Context));
// InitOnceBeginInitialize
inline void InitOnceBeginInitialize(PINIT_ONCE InitOnce, DWORD Flags, PBOOL Pending, LPVOID *Context)
	assertl_reflect_as(::InitOnceBeginInitialize(InitOnce, Flags, Pending, Context));
// InitOnceComplete
inline void InitOnceComplete(PINIT_ONCE InitOnce, DWORD Flags, LPVOID Context)
	assertl_reflect_as(::InitOnceComplete(InitOnce, Flags, Context));
// InitializeConditionVariable
inline void InitializeConditionVariable(PCONDITION_VARIABLE ConditionVariable)
	reflect_to(::InitializeConditionVariable(ConditionVariable));
// WakeConditionVariable
inline void WakeConditionVariable(PCONDITION_VARIABLE ConditionVariable)
	reflect_to(::WakeConditionVariable(ConditionVariable));
// WakeAllConditionVariable
inline void WakeAllConditionVariable(PCONDITION_VARIABLE ConditionVariable)
	reflect_to(::WakeAllConditionVariable(ConditionVariable));
// SleepConditionVariableCS
inline void SleepConditionVariableCS(PCONDITION_VARIABLE ConditionVariable, PCRITICAL_SECTION CriticalSection, DWORD dwMilliseconds)
	assertl_reflect_as(::SleepConditionVariableCS(ConditionVariable, CriticalSection, dwMilliseconds));
// SleepConditionVariableSRW
inline void SleepConditionVariableSRW(PCONDITION_VARIABLE ConditionVariable, PSRWLOCK SRWLock, DWORD dwMilliseconds, ULONG Flags)
	assertl_reflect_as(::SleepConditionVariableSRW(ConditionVariable, SRWLock, dwMilliseconds, Flags));
// SetEvent
inline void SetEvent(HANDLE hEvent)
	reflect_to(::SetEvent(hEvent));
// ResetEvent
inline void ResetEvent(HANDLE hEvent)
	reflect_to(::ResetEvent(hEvent));
// ReleaseSemaphore
inline void ReleaseSemaphore(HANDLE hSemaphore, LONG lReleaseCount, LPLONG lpPreviousCount)
	reflect_to(::ReleaseSemaphore(hSemaphore, lReleaseCount, lpPreviousCount));
// ReleaseMutex
inline void ReleaseMutex(HANDLE hMutex)
	reflect_to(::ReleaseMutex(hMutex));
// WaitForSingleObject
inline DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
	assertl_reflect_as(auto res = ::WaitForSingleObject(hHandle, dwMilliseconds); res != WAIT_FAILED, res);
// SleepEx
inline DWORD Sleep(DWORD dwMilliseconds, BOOL bAlertable)
	reflect_as(::SleepEx(dwMilliseconds, bAlertable));
// WaitForSingleObjectEx
inline DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds, BOOL bAlertable)
	assertl_reflect_as(auto res = ::WaitForSingleObjectEx(hHandle, dwMilliseconds, bAlertable); res != WAIT_FAILED, res);
// WaitForMultipleObjectsEx
inline DWORD WaitForMultipleObjects(DWORD nCount, const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds, BOOL bAlertable)
	assertl_reflect_as(auto res = ::WaitForMultipleObjectsEx(nCount, lpHandles, bWaitAll, dwMilliseconds, bAlertable); res != WAIT_FAILED, res);
// CreateMutex
inline HANDLE CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName)
	assertl_reflect_as(auto h = ::CreateMutexA(lpMutexAttributes, bInitialOwner, lpName), h);
inline HANDLE CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName)
	assertl_reflect_as(auto h = ::CreateMutexW(lpMutexAttributes, bInitialOwner, lpName), h);
// CreateEvent
inline HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCSTR lpName)
	assertl_reflect_as(auto h = ::CreateEventA(lpEventAttributes, bManualReset, bInitialState, lpName), h);
inline HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName)
	assertl_reflect_as(auto h = ::CreateEventW(lpEventAttributes, bManualReset, bInitialState, lpName), h);
// OpenEvent
inline HANDLE OpenEvent(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName)
	assertl_reflect_as(auto h = ::OpenEventA(dwDesiredAccess, bInheritHandle, lpName), h);
inline HANDLE OpenEvent(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName)
	assertl_reflect_as(auto h = ::OpenEventW(dwDesiredAccess, bInheritHandle, lpName), h);
// SetWaitableTimer
inline void SetWaitableTimer(HANDLE hTimer, const LARGE_INTEGER *lpDueTime, LONG lPeriod, PTIMERAPCROUTINE pfnCompletionRoutine, LPVOID lpArgToCompletionRoutine, BOOL fResume)
	assertl_reflect_as(::SetWaitableTimer(hTimer, lpDueTime, lPeriod, pfnCompletionRoutine, lpArgToCompletionRoutine, fResume));
// CancelWaitableTimer
inline void CancelWaitableTimer(HANDLE hTimer)
	assertl_reflect_as(::CancelWaitableTimer(hTimer));
// CreateMutexEx
inline HANDLE CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
	assertl_reflect_as(auto h = ::CreateMutexExA(lpMutexAttributes, lpName, dwFlags, dwDesiredAccess), h);
inline HANDLE CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
	assertl_reflect_as(auto h = ::CreateMutexExW(lpMutexAttributes, lpName, dwFlags, dwDesiredAccess), h);
// CreateEventEx
inline HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
	assertl_reflect_as(auto h = ::CreateEventExA(lpEventAttributes, lpName, dwFlags, dwDesiredAccess), h);
inline HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess)
	assertl_reflect_as(auto h = ::CreateEventExW(lpEventAttributes, lpName, dwFlags, dwDesiredAccess), h);
// Sleep
inline void Sleep(DWORD dwMilliseconds)
	reflect_to(::Sleep(dwMilliseconds));
// SignalObjectAndWait
inline DWORD SignalObjectAndWait(HANDLE hObjectToSignal, HANDLE hObjectToWaitOn, DWORD dwMilliseconds, BOOL bAlertable)
	assertl_reflect_as(auto res = ::SignalObjectAndWait(hObjectToSignal, hObjectToWaitOn, dwMilliseconds, bAlertable); res != WAIT_FAILED, res);
// WaitForMultipleObjects
inline DWORD WaitForMultipleObjects(DWORD nCount, const HANDLE *lpHandles, BOOL bWaitAll, DWORD dwMilliseconds)
	assertl_reflect_as(auto res = ::WaitForMultipleObjects(nCount, lpHandles, bWaitAll, dwMilliseconds); res != WAIT_FAILED, res);
#pragma endregion

}
