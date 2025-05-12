#pragma once

#include <windows.h>
#include <heapapi.h>
#include <psapi.h>

#include "wx_window.h"
#include "wx_security.h"

namespace WX {

#pragma region Event
enum_flags(EventAccess, HandleAccess,
	All    = EVENT_ALL_ACCESS,
	Modify = EVENT_MODIFY_STATE);
class BaseOf_Handle(Event) {
public:
	using super = HandleBase<Event>;
	using Access = EventAccess;
protected:
	Event(HANDLE h) : super(h) {}
	Event(const Event &evt) : super(evt) {}
public:
	Event() : Event(Create()) {}
	Event(Null) {}
	Event(Event &evt) : super(evt) {}
	Event(Event &&evt) : super(evt) {}

	using super::operator=;

	class CreateStruct {
		friend class Event;
		LPSECURITY_ATTRIBUTES lpAttributes = O;
		bool bManualReset = false;
		bool bInitialState = false;
		LPCTSTR lpName;
		CreateStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &Preset(bool bInitialState = true) reflect_to_self(this->bInitialState = bInitialState);
		inline auto &AutoReset(bool bAutoReset = true) reflect_to_self(this->bManualReset = !bAutoReset);
		inline auto &ManualReset(bool bManualReset = true) reflect_to_self(this->bManualReset = bManualReset);
		inline auto &Security(const SecAttr &sa) reflect_to_self(this->lpAttributes = &sa);
		inline auto &Security(LPSECURITY_ATTRIBUTES pSA) reflect_to_self(this->lpAttributes = pSA);
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator Event() const assertl_reflect_as(auto h = CreateEvent(lpAttributes, bManualReset, bInitialState, lpName), h);
	};
	static inline CreateStruct Create(LPCTSTR lpName = O) reflect_as(lpName);

	class OpenStruct {
		friend class Event;
		Access dwDesiredAccess = Access::Modify;
		BOOL bInheritHandle = false;
		LPCTSTR lpName;
		OpenStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &Accesses(Access dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Inherit(bool bInheritHandle = true) reflect_to_self(this->bInheritHandle = bInheritHandle);
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator Event() const assertl_reflect_as(auto h = OpenEvent(dwDesiredAccess.yield(), bInheritHandle, lpName), h);
	};
	static inline OpenStruct Open(LPCTSTR lpName = O) reflect_as(lpName);

	inline Event&Set() assertl_reflect_as_self(SetEvent(self));
	inline Event&Reset() assertl_reflect_as_self(ResetEvent(self));

	inline auto&operator=(bool bState) reflect_as(bState ? Set() : Reset());
};
#pragma endregion

#pragma region Mutex
enum_flags(MutexAccess, HandleAccess,
	All    = MUTEX_ALL_ACCESS,
	Modify = MUTEX_MODIFY_STATE);
class BaseOf_Handle(Mutex) {
public:
	using super = HandleBase<Mutex>;
	using Access = MutexAccess;
protected:
	Mutex(HANDLE h) : super(h) {}
	Mutex(const Mutex &m) : super(m.hObject) reflect_to(m.hObject = O);
public:
	Mutex() : Mutex(Create()) {}
	Mutex(Null) {}
	Mutex(Mutex &m) : super(m) {}
	Mutex(Mutex &&m) : super(m) {}

	using super::operator=;

	inline auto &Release() assertl_reflect_as_self(ReleaseMutex(self));

	class CreateStruct {
		friend class Mutex;
		LPSECURITY_ATTRIBUTES lpMutexAttributes = O;
		bool bInitialState = false;
		LPCTSTR lpName;
	protected:
		CreateStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &Preset(bool bInitialState = true) reflect_to_self(this->bInitialState = bInitialState);
		inline auto &Security(const SecAttr &MutexAttributes) reflect_to_self(this->lpMutexAttributes = &MutexAttributes);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpMutexAttributes) reflect_to_self(this->lpMutexAttributes = lpMutexAttributes);
	public:
		inline operator Mutex() const assertl_reflect_as(auto h = CreateMutex(lpMutexAttributes, bInitialState, lpName), h);
	};
	static inline CreateStruct Create(LPCTSTR lpName = O) reflect_as(lpName);

	class OpenStruct {
		friend class Mutex;
		Access dwDesiredAccess = Access::Modify;
		bool bInheritHandle = false;
		LPCTSTR lpName;
	protected:
		OpenStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &Accesses(Access dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Inherit(bool bInheritHandle = true) reflect_to_self(this->bInheritHandle = bInheritHandle);
	public:
		inline operator Mutex() const assertl_reflect_as(auto h = OpenMutex(dwDesiredAccess.yield(), bInheritHandle, lpName), h);
	};
	static inline OpenStruct Open(LPCTSTR lpName = O) reflect_as(lpName);
};
#pragma endregion

#pragma region ThreadBase
enum_flags(ThreadAccess, Handle::Access,
	Resume            = THREAD_RESUME,
	Terminate         = THREAD_TERMINATE,
	SuspendResume     = THREAD_SUSPEND_RESUME,
	GetContext        = THREAD_GET_CONTEXT,
	SetContext        = THREAD_SET_CONTEXT,
	QueryInfo         = THREAD_QUERY_INFORMATION,
	QueryInfoLimit    = THREAD_QUERY_LIMITED_INFORMATION,
	SetInfo           = THREAD_SET_INFORMATION,
	SetInfoLimit      = THREAD_SET_LIMITED_INFORMATION,
	SetToken          = THREAD_SET_THREAD_TOKEN,
	Impersonate       = THREAD_IMPERSONATE,
	ImpersonateDirect = THREAD_DIRECT_IMPERSONATION,
	All               = THREAD_ALL_ACCESS);
template<class AnyChild = void>
class ThreadBase;
using Thread = ThreadBase<>;
using CThread = RefAs<Thread>;
template<>
class ThreadBase<> : public HandleBase<ThreadBase<>> {
public:
	using super = HandleBase<ThreadBase<>>;
	using Access = ThreadAccess;
protected:
	friend union RefAs<Thread>;
	friend class Process;
	ThreadBase(HANDLE h) : super(h) {}
	ThreadBase(const ThreadBase &t) : super(t.hObject) reflect_to(t.hObject = O);
public:
	ThreadBase() {}
	ThreadBase(Null) {}
	ThreadBase(ThreadBase &t) : super(t.hObject) reflect_to(t.hObject = O);
	ThreadBase(ThreadBase &&t) : super(t.hObject) reflect_to(t.hObject = O);

	using super::operator=;

	template<class AnyChild = void>
	class CreateStruct : public ChainExtend<CreateStruct<AnyChild>, AnyChild> {
		friend class ThreadBase;
		LPSECURITY_ATTRIBUTES lpThreadAttributes = O;
		SIZE_T dwStackSize = 0;
		LPTHREAD_START_ROUTINE lpStartAddress;
		LPVOID lpParameter;
		DWORD dwCreationFlags = STACK_SIZE_PARAM_IS_A_RESERVATION;
	protected:
		CreateStruct(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter) : lpStartAddress(lpStartAddress), lpParameter(lpParameter) {}
		CreateStruct(const CreateStruct &) = default;
	public:
		inline auto &Security(const SecAttr &ThreadAttributes) reflect_to_child(this->lpThreadAttributes = &ThreadAttributes);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpThreadAttributes) reflect_to_child(this->lpThreadAttributes = lpThreadAttributes);
		inline auto &StackSize(size_t dwStackSize) reflect_to_child(this->dwStackSize = dwStackSize, this->dwCreationFlags &= ~STACK_SIZE_PARAM_IS_A_RESERVATION);
		inline auto &Suspend(bool bSuspend = true) reflect_to_child(this->dwCreationFlags = bSuspend ? (this->dwCreationFlags | CREATE_SUSPENDED) : (this->dwCreationFlags & ~CREATE_SUSPENDED));
	public:
		template<class _Child>
		inline ThreadBase<_Child> Create() assertl_reflect_as(auto h = CreateThread(this->lpThreadAttributes, this->dwStackSize, this->lpStartAddress, this->lpParameter, this->dwCreationFlags, O), h);
	};
	static inline CreateStruct<> Create(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter = O) reflect_as({ lpStartAddress, lpParameter });

	class OpenStruct {
		friend class ThreadBase;
		Access dwDesiredAccess = Access::All;
		bool bInheritHandle = false;
		DWORD dwThreadId;
		OpenStruct(DWORD dwThreadId) : dwThreadId(dwThreadId) {}
	public:
		inline auto &Accesses(Access dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Inherit(bool bInheritHandle) reflect_to_self(this->bInheritHandle = bInheritHandle);
	public:
		inline operator ThreadBase() const reflect_as(OpenThread(dwDesiredAccess.yield(), bInheritHandle, dwThreadId));
	};
	static inline OpenStruct Open(DWORD dwProcessId) reflect_as(dwProcessId);

	static inline Thread Current() reflect_as(GetCurrentThread());

	inline void Suspend() assertl_reflect_as(SuspendThread(self));
	inline void Resume()  assertl_reflect_as(ResumeThread(self));

	inline void Terminate(DWORD dwExitCode = 0) assertl_reflect_as(TerminateThread(this->hObject, dwExitCode));
	inline bool TerminateWait(DWORD dwMilliSec, DWORD dwExitCode = 0) {
		if (WaitForSignal(dwMilliSec)) return false;
		Terminate(dwExitCode);
		return true;
	}

	static inline void Exit(DWORD dwExitCode = 0) reflect_to(ExitThread(dwExitCode));

	template<class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline void Post(MsgType msgid, WParam wParam = 0, LParam lParam = 0) assertl_reflect_as(PostThreadMessage(ID(), reuse_as<UINT>(msgid), small_cast<WPARAM>(wParam), small_cast<LPARAM>(lParam)));
	inline void Post(const Message &msg) assertl_reflect_as(PostThreadMessage(ID(), msg.ID(), msg.ParamW(), msg.ParamL()));

#pragma region Properties
public: // Property - ID
	/* W */ inline DWORD ID() const assertl_reflect_as(auto id = GetThreadId(self), id);
public: // Property - ExitCode
	/* W */ inline DWORD ExitCode() const assertl_reflect_to(DWORD dwExitCode, GetExitCodeThread(self, &dwExitCode), dwExitCode);
public: // Property - StillActive
	/* W */ inline bool StillActive() const {
		if (self)
			try {
				if (ExitCode() == STILL_ACTIVE)
					return !super::WaitForSignal(0);
			} catch (...) {}
		return false;
	}
public: // Property - ProcessID
	/* R */ inline DWORD ProcessID() const nt_assertl_reflect_to(DWORD dwID = GetProcessIdOfThread(self), dwID);
#pragma endregion
};
template<class AnyChild>
class ThreadBase : public ChainExtend<ThreadBase<AnyChild>, AnyChild>,
	public Thread {
public:
	using super = Thread;
protected:
	friend class ThreadBase<>;
	using ChainExtend<ThreadBase<AnyChild>, AnyChild>::child_;
	static DWORD WINAPI Proc(LPVOID lpThis) {
		auto pThis = static_cast<ThreadBase *>(lpThis);
	retry:
		try {
			return pThis->Start();
		} catch (Exception err) {
			if (pThis->Catch(err))
				goto retry;
			return pThis->Final();
		}
		return -2; // unreachable
	}
protected:
	def_memberof(OnStart);
	inline DWORD Start() {
		if constexpr (member_OnStart_of<AnyChild>::template compatible_to<DWORD()>)
			reflect_as(child.OnStart())
		else if constexpr (member_OnStart_of<AnyChild>::template compatible_to<void()>)
			reflect_to(child.OnStart(), 0)
		else {
			static_assert(member_OnStart_of<AnyChild>::callable, "OnStart uncallable or unexisted");
			static_assert(!member_OnStart_of<AnyChild>::callable, "OnStart uncompatible");
			return 0;
		}
	}
	def_memberof(OnCatch);
	inline wx_answer Catch(const Exception &err) {
		if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer(Exception)>)
			reflect_as(child.OnCatch(err))
		else if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer()>)
			reflect_as(child.OnCatch())
		else if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<void(Exception)>)
			reflect_to(child.OnCatch(err), false)
		else if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<void()>)
			reflect_to(child.OnCatch(), false)
		else {
			static_assert(!member_OnCatch_of<AnyChild>::callable, "OnCatch uncompatible");
			switch (MsgBox(Cats(_T("Thread[PID:"), ID(), _T("] error")), err)) {
				case IDIGNORE:
					wx_answer_ignore;
				case IDRETRY:
					wx_answer_retry;
				case IDABORT:
					break;
			}
			wx_answer_abort(err);
		}
	}
	def_memberof(OnFinal);
	inline DWORD Final() {
		if constexpr (member_OnFinal_of<AnyChild>::template compatible_to<DWORD()>)
			reflect_as(child.OnFinal())
		else if constexpr (member_OnFinal_of<AnyChild>::template compatible_to<void()>)
			reflect_to(child.OnFinal(), -1)
		else {
			static_assert(!member_OnFinal_of<AnyChild>::callable, "OnFinal uncallable");
			return -3;
		}
	}
protected:
	inline auto &operator=(ThreadBase &t) reflect_to_child(std::swap(this->hObject, t.hObject));
	inline auto &operator=(ThreadBase &&t) reflect_to_child(std::swap(this->hObject, t.hObject));
	inline auto &operator=(const ThreadBase &t) const reflect_to_child(std::swap(this->hObject, t.hObject));

	ThreadBase(HANDLE h) : super(h) {}
	ThreadBase(const ThreadBase &t) : super(t) {}
public:
	ThreadBase() {}
	ThreadBase(Null) {}
	ThreadBase(ThreadBase &t) : super(t) {}
	ThreadBase(ThreadBase &&t) : super(t) {}
	~ThreadBase() reflect_to(if (StillActive()) super::WaitForSignal());

	class CreateStruct : public Thread::CreateStruct<CreateStruct> {
	public:
		using super = Thread::CreateStruct<CreateStruct>;
	protected:
		friend class ThreadBase;
		ThreadBase &_this;
		CreateStruct(ThreadBase & _this) : super(Proc, &_this), _this(_this) {}
	public:
		inline bool Create() reflect_as(this->_this = super::template Create<AnyChild>());
		inline operator bool() reflect_as(this->_this.StillActive() ? false : Create());
	};
	inline CreateStruct Create() reflect_to_self();
};
#define SFINAE_Thread(name) friend class WX::ThreadBase<name>; using super = WX::ThreadBase<name>
#define BaseOf_Thread(name) name : public WX::ThreadBase<name>

class BaseOf_Thread(LThread) {
	SFINAE_Thread(LThread);
protected:
	struct StartClosure {
		virtual ~StartClosure() {}
		virtual DWORD operator()() = 0;
	};
	template<class AnyCallable>
	struct InlineStartClosure : StartClosure {
		AnyCallable f;
		InlineStartClosure(const AnyCallable &f) : f(f) {}
		DWORD operator()() override {
			if constexpr (static_compatible<AnyCallable, DWORD()>)
				reflect_as(f())
			else {
				static_assert(static_compatible<AnyCallable, void()>, "Error uncompatible");
				reflect_to(f(), 0)
			}
		}
	};
	StartClosure *lpStart = O;
	inline DWORD OnStart() reflect_as((*lpStart)());
protected:
	struct ExceptionClosure {
		virtual ~ExceptionClosure() {}
		virtual bool OnCatch(const Exception &err) = 0;
	};
	template<class AnyCatch>
	struct InlineExceptionClosure : ExceptionClosure {
		AnyCatch lOnCatch;
		InlineExceptionClosure(const AnyCatch &lOnCatch) : lOnCatch(lOnCatch) {}
		bool OnCatch(const Exception &err) override {
			if constexpr (static_compatible<AnyCatch, wx_answer(Exception)>)
				reflect_as(lOnCatch(err))
			else if constexpr (static_compatible<AnyCatch, wx_answer()>)
				reflect_as(lOnCatch())
			else if constexpr (static_compatible<AnyCatch, void(Exception)>)
				reflect_to(lOnCatch(err), false)
			else {
				static_assert(static_compatible<AnyCatch, void()>, "OnCatch uncompatible");
				reflect_to(lOnCatch(err), false);
			}
		}
	};
	ExceptionClosure *lpException = O;
	inline bool OnCatch(const Exception &err) reflect_as(lpException ? lpException->OnCatch(err) : false);
public:
	template<class AnyCatch>
	void SetOnCatch(const AnyCatch &Catch) reflect_to(lpException = new InlineExceptionClosure<AnyCatch>(Catch));
public:
	template<class AnyCallable>
	LThread(const AnyCallable &OnStart) : lpStart(new InlineStartClosure<AnyCallable>(OnStart)) {}
	~LThread() {
		if (StillActive())
			Terminate();
		if (lpStart)
			delete lpStart,
			lpStart = O;
		if (lpException)
			delete lpException,
			lpException = O;
	}
};
#pragma endregion

#pragma region Process
enum_flags(ProccessCreateFlag, DWORD,
	enum_default Default         = 0,

	DebugProcess                 = DEBUG_PROCESS,
	DebugOnlyThisProcess         = DEBUG_ONLY_THIS_PROCESS,
	CreateSuspended              = CREATE_SUSPENDED,
	DetachedProcess              = DETACHED_PROCESS,

	CreateNewConsole             = CREATE_NEW_CONSOLE,
	NormalPriorityClass          = NORMAL_PRIORITY_CLASS,
	IdlePriorityClass            = IDLE_PRIORITY_CLASS,
	HighPriorityClass            = HIGH_PRIORITY_CLASS,

	RealtimePriorityClass        = REALTIME_PRIORITY_CLASS,
	CreateNewProcessGroup        = CREATE_NEW_PROCESS_GROUP,
	CreateUnicodeEnvironment     = CREATE_UNICODE_ENVIRONMENT,
	CreateSeparateWowVdm         = CREATE_SEPARATE_WOW_VDM,

	CreateSharedWowVdm           = CREATE_SHARED_WOW_VDM,
	CreateForceDos               = CREATE_FORCEDOS,
	BelowNormalPriorityClass     = BELOW_NORMAL_PRIORITY_CLASS,
	AboveNormalPriorityClass     = ABOVE_NORMAL_PRIORITY_CLASS,

	InheritParentAffinity        = INHERIT_PARENT_AFFINITY,
	InheritCallerPriority        = INHERIT_CALLER_PRIORITY,
	CreateProtectedProcess       = CREATE_PROTECTED_PROCESS,
	ExtendedStartupInfoPresent   = EXTENDED_STARTUPINFO_PRESENT,

	ProcessModeBackgroundBegin   = PROCESS_MODE_BACKGROUND_BEGIN,
	ProcessModeBackgroundEnd     = PROCESS_MODE_BACKGROUND_END,
	CreateSecureProcess          = CREATE_SECURE_PROCESS,

	CreateBreakawayFromJob       = CREATE_BREAKAWAY_FROM_JOB,
	CreatePreserveCodeAuthzLevel = CREATE_PRESERVE_CODE_AUTHZ_LEVEL,
	CreateDefaultErrorMode       = CREATE_DEFAULT_ERROR_MODE,
	CreateNoWindow               = CREATE_NO_WINDOW,

	ProfileUser                  = PROFILE_USER,
	ProfileKernel                = PROFILE_KERNEL,
	ProfileServer                = PROFILE_SERVER,
	CreateIgnoreSystemDefault    = CREATE_IGNORE_SYSTEM_DEFAULT);
enum_flags(ProcessAccess, DWORD,
	Terminate                 = PROCESS_TERMINATE,
	CreateThread              = PROCESS_CREATE_THREAD,
	SetSessionid              = PROCESS_SET_SESSIONID,
	VmOperation               = PROCESS_VM_OPERATION,
	VmRead                    = PROCESS_VM_READ,
	VmWrite                   = PROCESS_VM_WRITE,
	DupHandle                 = PROCESS_DUP_HANDLE,
	CreateProcess             = PROCESS_CREATE_PROCESS,
	SetQuota                  = PROCESS_SET_QUOTA,
	SetInformation            = PROCESS_SET_INFORMATION,
	QueryInformation          = PROCESS_QUERY_INFORMATION,
	SuspendResume             = PROCESS_SUSPEND_RESUME,
	QueryLimitedInformation   = PROCESS_QUERY_LIMITED_INFORMATION,
	SetLimitedInformation     = PROCESS_SET_LIMITED_INFORMATION,
	enum_complex All          = PROCESS_ALL_ACCESS);
class Environments {
	LPTCH lpEnv = O;
public:
	class Variable {
		friend class Environments;
		const String name;
		const String value;
	public:
		Variable() {}
		//Variable(const Variable &var) : name(var.name), value(var.value) {}
		Variable(const String &entry) {
			LPCTSTR lpName = entry, pName = lpName;
			while (*pName++ != '=');
			name = +CString(pName - lpName - 1, lpName);
			value = +CString(pName, entry.Length() - name.Length());
		}
		Variable(const String &name, const String &value) reflect_to(this->name = name; this->value = value);
	public: // Property - Name
		/* W */ inline Variable &Name(const String &name) reflect_to_self(this->name = name);
		/* R */ inline const String &Name() const reflect_as(this->name);
	public: // Property - Value
		/* W */ inline Variable &Value(const String &value) reflect_to_self(this->value = value);
		/* R */ inline const String &Value() const reflect_as(this->value);
	public: // Property - ValueExpend
		inline String ValueExpend() const {
			if (!value) return O;
			DWORD lenDst;
			assertl((lenDst = ExpandEnvironmentStrings(value, O, 0)));
			if (lenDst - 1 == value.Length()) return &value;
			String eval((size_t)lenDst - 1);
			ExpandEnvironmentStrings(value, eval, lenDst);
			return eval;
		}
	public:
		inline auto &operator=(const String &value) reflect_to_self(Value(value));
		inline operator bool() const reflect_as(name);
		inline operator String() const reflect_as(&Value());
		inline String operator+() const reflect_as(ValueExpend());
		inline bool operator!=(Null) const reflect_as(name);
		inline bool operator==(Null) const reflect_as(!name);
	};
protected:
	Environments(LPTCH lpEnv) : lpEnv(lpEnv) {}
public:
	Environments() {}
	Environments(Null) {}
	Environments(Environments &env) : lpEnv(env.lpEnv) reflect_to(env.lpEnv = O);
	Environments(Environments &&env) : lpEnv(env.lpEnv) reflect_to(env.lpEnv = O);
	~Environments() reflect_to(Free());

	inline void Free() {
		if (lpEnv) {
			assertl(FreeEnvironmentStrings(lpEnv));
			lpEnv = O;
		}
	}

	static inline Environments From(std::initializer_list<const String> envs) {
		size_t maxlen = 1;
		for (const String &env : envs)
			if (env.Length())
				maxlen += env.Length() + 1;
		if (maxlen <= 1) return O;
		LPTCH lpEnv = (LPTCH)Heap::This.Alloc(maxlen * sizeof(TCHAR)), pEnv = lpEnv;
		for (const String &env : envs)
			if (auto len = env.Length()) {
				CopyMemory(pEnv, (LPCTSTR)env, len * sizeof(TCHAR));
				pEnv += len;
				*pEnv++ = '\0';
			}
		*pEnv = '\0';
		return lpEnv;
	}
	static inline Environments From(std::initializer_list<const Variable> vars) {
		size_t maxlen = 1;
		for (const Variable &var : vars)
			if (var)
				maxlen += var.name.Length() + var.value.Length() + 2;
		if (maxlen <= 1) return O;
		LPTCH lpEnv = (LPTCH)Heap::This.Alloc(maxlen * sizeof(TCHAR)), pEnv = lpEnv;
		for (const Variable &var : vars)
			if (var) {
				CopyMemory(pEnv, (LPCTSTR)var.name, var.name.Length() * sizeof(TCHAR));
				pEnv += var.name.Length();
				*pEnv++ = '=';
				CopyMemory(pEnv, (LPCTSTR)var.value, var.value.Length() * sizeof(TCHAR));
				pEnv += var.value.Length();
				*pEnv++ = '\0';
			}
		*pEnv = '\0';
		return lpEnv;
	}
	static inline Environments Current() assertl_reflect_as(auto lpEnv = GetEnvironmentStrings(), lpEnv);

	inline void Use() const assertl_reflect_as(SetEnvironmentStrings(lpEnv));

public: // Property - Count
	/* R */ inline size_t Count() const {
		if (!lpEnv) return 0;
		size_t count = 0;
		for (auto ch = lpEnv; *ch != '\0'; ++ch) {
			while (*ch != '\0') ++ch;
			++count;
		}
		return count;
	}
public: // Property - Entries
	/* R */ inline std::vector<String> Entries() const {
		size_t count = Count();
		std::vector<String> list(count);
		auto lpEnv = this->lpEnv;
		for (const String &e : list)
			lpEnv += (e = CString(lpEnv, MaxLenNotice)).Length() + 1;
		return list;
	}
public: // Property - Variables
	/* R */ inline std::vector<Variable> Variables() const {
		size_t count = Count();
		std::vector<Variable> list(count);
		auto lpEnv = this->lpEnv;
		for (const Variable &e : list) {
			auto lpName = lpEnv;
			while (*lpEnv++ != '=');
			e.name = CString(lpEnv - lpName - 1, lpName);
			e.value = CString(lpEnv, MaxLenNotice);
			lpEnv += e.value.Length() + 1;
		}
		return list;
	}

public:
	inline operator bool() const reflect_as(lpEnv);
	inline operator LPTCH() const reflect_as(lpEnv);
};
using EnvVar = Environments::Variable;
class CurrentEnvironment {
	class Variable {
		friend class CurrentEnvironment;
		const String name;
	public:
		Variable(const String &name) : name(+name) {}
	public: // Property - Value
		/* W */ inline Variable &Value(const String &value) assertl_reflect_as_self(SetEnvironmentVariable(name, value.str_safe()));
		/* R */ inline String Value() const {
			DWORD len;
			assertl((len = GetEnvironmentVariable(name, O, 0)));
			String value((size_t)len - 1);
			GetEnvironmentVariable(name, value, len);
			return value;
		}
	public: // Property - ValueExpend
		inline String ValueExpend() const {
			DWORD lenSrc;
			assertl((lenSrc = GetEnvironmentVariable(name, O, 0)));
			String value((size_t)lenSrc - 1);
			GetEnvironmentVariable(name, value, lenSrc);
			DWORD lenDst;
			assertl((lenDst = ExpandEnvironmentStrings(value, O, 0)));
			if (lenSrc == lenDst) return value;
			String eval((size_t)lenDst - 1);
			ExpandEnvironmentStrings(value, eval, lenDst);
			return eval;
		}
	public:
		inline auto &operator=(const String &value) reflect_to_self(Value(value));
		inline operator bool() const reflect_as(GetEnvironmentVariable(name, O, 0));
		inline operator String() const reflect_as(Value());
		inline String operator+() const reflect_as(ValueExpend());
		inline bool operator!=(Null) const reflect_as(GetEnvironmentVariable(name, O, 0) != 0);
		inline bool operator==(Null) const reflect_as(GetEnvironmentVariable(name, O, 0) == 0);
	};
public:
	inline operator Environments() reflect_as(Environments::Current());
	inline Variable operator[](const String &str) reflect_as(str);
	inline CurrentEnvironment &operator=(const Environments &env) reflect_to_self(env.Use());
} inline Environment;
enum_flags(StartupFlag, DWORD,
	UseShowWindow       = STARTF_USESHOWWINDOW,
	UseSize             = STARTF_USESIZE,
	UsePosition         = STARTF_USEPOSITION,
	UseCountChars       = STARTF_USECOUNTCHARS,
	UseFillAttribute    = STARTF_USEFILLATTRIBUTE,
	UseStdHandles       = STARTF_USESTDHANDLES,
	UseHotKey           = STARTF_USEHOTKEY,

	RunFullScreen       = STARTF_RUNFULLSCREEN,

	ForceOnFeedback     = STARTF_FORCEONFEEDBACK,
	ForceOffFeedback    = STARTF_FORCEOFFFEEDBACK,

	TitleIsLinkName     = STARTF_TITLEISLINKNAME,
	TitleIsAppID        = STARTF_TITLEISAPPID,
	PreventPinning      = STARTF_PREVENTPINNING,
	UntrustedSource     = STARTF_UNTRUSTEDSOURCE);
class StartupInfo : protected STARTUPINFO {
public:
	StartupInfo() : STARTUPINFO{ 0 } reflect_to(this->cb = sizeof(*this));
// public: // Property - Desktop
// 	/* W */ inline auto &Desktop(LPWSTR lpDesktop) reflect_to_self(this->lpDesktop = lpDesktop);
// 	/* R */ inline auto  Desktop() const reflect_as(this->lpDesktop);
// public: // Property - Title
// 	/* W */ inline auto &Title(LPWSTR lpTitle) reflect_to_self(this->lpTitle = lpTitle);
// 	/* R */ inline auto  Title() const reflect_as(this->lpTitle);
public: // Property - Position
	/* W */ inline auto  &Position(LPoint pos) reflect_to_self(this->dwFlags |= STARTF_USEPOSITION, this->dwX = pos.x, this->dwY = pos.y);
	/* R */ inline LPoint Position() const reflect_as({ (LONG)this->dwX, (LONG)this->dwY });
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(this->dwFlags |= STARTF_USESIZE, this->dwXSize = size.cx, this->dwYSize = size.cy);
	/* R */ inline LSize Size() const reflect_as({ (LONG)this->dwXSize, (LONG)this->dwYSize });
public: // Property - CountCmhars
	/* W */ inline auto &CountChars(LSize size) reflect_to_self(this->dwFlags |= STARTF_USECOUNTCHARS, this->dwXCountChars = size.cx, this->dwYCountChars = size.cy);
	/* R */ inline LSize CountChars() const reflect_as({ (LONG)this->dwXCountChars, (LONG)this->dwYCountChars });
public: // Property - FillAttribute
	/* W */ inline auto &FillAttribute(DWORD dwFillAttribute) reflect_to_self(this->dwFlags |= STARTF_USEFILLATTRIBUTE, this->dwFillAttribute = dwFillAttribute);
	/* R */ inline auto  FillAttribute() const reflect_as(this->dwFillAttribute);
public: // Property - Flags
	/* R */ inline StartupFlag Flags() const reflect_as(reuse_as<StartupFlag>(this->dwFlags));
public: // Property - Show
	/* W */ inline auto  &Show(WX::SW wShow) reflect_to_self(this->dwFlags |= STARTF_USESHOWWINDOW, this->wShowWindow = wShow.yield());
	/* R */ inline WX::SW Show() const reflect_as(reuse_as<WX::SW>((DWORD)this->wShowWindow));
public: // Property - StdInput
	/* W */ inline auto &StdInput(HANDLE hStdInput) reflect_to_self(this->dwFlags |= STARTF_USESTDHANDLES, this->hStdInput = hStdInput);
	/* R */ inline auto  StdInput() const reflect_as(this->hStdInput);
public: // Property - StdOutput
	/* W */ inline auto &StdOutput(HANDLE hStdOutput) reflect_to_self(this->dwFlags |= STARTF_USESTDHANDLES, this->hStdOutput = hStdOutput);
	/* R */ inline auto  StdOutput() const reflect_as(this->hStdOutput);
public: // Property - StdError
	/* W */ inline auto &StdError(HANDLE hStdError) reflect_to_self(this->dwFlags |= STARTF_USESTDHANDLES, this->hStdError = hStdError);
	/* R */ inline auto  StdError() const reflect_as(this->hStdError);
public:
	inline LPSTARTUPINFO operator&() reflect_as(this);
};
class Process;
using CProcess = RefAs<Process>;
class BaseOf_Handle(Process) {
public:
	using super = HandleBase<Process>;
	using Access = ProcessAccess;
	using CreateFlag = ProccessCreateFlag;
protected:
	Process(HANDLE h) : super(h) {}
	Process(const Process &p) : super(p) {}
public:
	Process() {}
	Process(Null) {}
	Process(Process &p) : super(p) {}
	Process(Process &&p) : super(p) {}

	using super::operator=;

	class CreateStruct {
		LPCTSTR lpApplicationName;
		mutable LPTSTR lpCommandLine;
		LPSECURITY_ATTRIBUTES lpProcessAttributes = O;
		LPSECURITY_ATTRIBUTES lpThreadAttributes = O;
		bool bInheritHandles = false;
		CreateFlag dwCreationFlags = CreateFlag::Default;
		LPVOID lpEnvironment = O;
		LPCTSTR lpCurrentDirectory = O;
		StartupInfo startupInfo;
		PROCESS_INFORMATION processInfo = { O };
	public:
		CreateStruct(const CreateStruct &cs) { *this = cs, cs.lpCommandLine = O; }
		CreateStruct(LPCTSTR lpApplicationName, const String &Cmdl) : lpApplicationName(lpApplicationName), lpCommandLine(*Cmdl) {}
		~CreateStruct() {
			if (lpCommandLine)
				String::Free(lpCommandLine),
				lpCommandLine = O;
		}
	public:
		inline auto &Security(const SecAttr &ProcessAttributes) reflect_to_self(this->lpProcessAttributes = &ProcessAttributes);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpProcessAttributes) reflect_to_self(this->lpProcessAttributes = lpProcessAttributes);
		inline auto &SecurityThread(const SecAttr &ThreadAttributes) reflect_to_self(this->lpThreadAttributes = &ThreadAttributes);
		inline auto &SecurityThread(LPSECURITY_ATTRIBUTES lpThreadAttributes) reflect_to_self(this->lpThreadAttributes = lpThreadAttributes);
		inline auto &InheritHandles(bool bInheritHandles = true) reflect_to_self(this->bInheritHandles = bInheritHandles);
	public:
		inline auto &DebugProcess() reflect_to_self(this->dwCreationFlags |= CreateFlag::DebugProcess);
		inline auto &DebugOnlyThisProcess() reflect_to_self(this->dwCreationFlags |= CreateFlag::DebugOnlyThisProcess);
		inline auto &Suspended() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateSuspended);
		inline auto &DetachedProcess() reflect_to_self(this->dwCreationFlags |= CreateFlag::DetachedProcess);

		inline auto &NewConsole() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateNewConsole);
		inline auto &NormalPriorityClass() reflect_to_self(this->dwCreationFlags |= CreateFlag::NormalPriorityClass);
		inline auto &IdlePriorityClass() reflect_to_self(this->dwCreationFlags |= CreateFlag::IdlePriorityClass);
		inline auto &HighPriorityClass() reflect_to_self(this->dwCreationFlags |= CreateFlag::HighPriorityClass);

		inline auto &RealtimePriorityClass() reflect_to_self(this->dwCreationFlags |= CreateFlag::RealtimePriorityClass);
		inline auto &NewProcessGroup() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateNewProcessGroup);
		inline auto &UnicodeEnvironment() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateUnicodeEnvironment);
		inline auto &SeparateWowVdm() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateSeparateWowVdm);

		inline auto &SharedWowVdm() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateSharedWowVdm);
		inline auto &ForceDos() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateForceDos);
		inline auto &BelowNormalPriorityClass() reflect_to_self(this->dwCreationFlags |= CreateFlag::BelowNormalPriorityClass);
		inline auto &AboveNormalPriorityClass() reflect_to_self(this->dwCreationFlags |= CreateFlag::AboveNormalPriorityClass);

		inline auto &InheritParentAffinity() reflect_to_self(this->dwCreationFlags |= CreateFlag::InheritParentAffinity);
		inline auto &InheritCallerPriority() reflect_to_self(this->dwCreationFlags |= CreateFlag::InheritCallerPriority);
		inline auto &ProtectedProcess() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateProtectedProcess);
		inline auto &ExtendedStartupInfoPresent() reflect_to_self();

		inline auto &ProcessModeBackgroundBegin() reflect_to_self(this->dwCreationFlags |= CreateFlag::ProcessModeBackgroundBegin);
		inline auto &ProcessModeBackgroundEnd() reflect_to_self(this->dwCreationFlags |= CreateFlag::ProcessModeBackgroundEnd);
		inline auto &SecureProcess() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateSecureProcess);

		inline auto &BreakawayFromJob() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateBreakawayFromJob);
		inline auto &PreserveCodeAuthzLevel() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreatePreserveCodeAuthzLevel);
		inline auto &DefaultErrorMode() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateDefaultErrorMode);
		inline auto &NoWindow() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateNoWindow);

		inline auto &ProfileUser() reflect_to_self(this->dwCreationFlags |= CreateFlag::ProfileUser);
		inline auto &ProfileKernel() reflect_to_self(this->dwCreationFlags |= CreateFlag::ProfileKernel);
		inline auto &ProfileServer() reflect_to_self(this->dwCreationFlags |= CreateFlag::ProfileServer);
		inline auto &IgnoreSystemDefault() reflect_to_self(this->dwCreationFlags |= CreateFlag::CreateIgnoreSystemDefault);
	public:
		inline auto &StartupInfo(const WX::StartupInfo &si) reflect_to_self(this->startupInfo = si, this->dwCreationFlags |= CreateFlag::ExtendedStartupInfoPresent);
		inline auto &CurrentDirectory(LPCTSTR lpCurrentDirectory) reflect_to_self(this->lpCurrentDirectory = lpCurrentDirectory);
	public:
		inline auto &Create() assertl_reflect_as(CreateProcess(
			lpApplicationName, lpCommandLine,
			lpProcessAttributes, lpThreadAttributes, bInheritHandles,
			dwCreationFlags.yield(), lpEnvironment, lpCurrentDirectory,
			&startupInfo, &processInfo), processInfo);
		inline operator Process() reflect_as(processInfo.hProcess ? processInfo.hProcess : Create().hProcess);
		inline operator Thread() reflect_as(processInfo.hProcess ? processInfo.hThread : Create().hThread);
	};
	static inline CreateStruct Create(LPCTSTR lpApplicationName, const String &CommandLine = O) reflect_as({lpApplicationName, CommandLine});

	class OpenStruct {
		friend class Process;
		Access dwDesiredAccess = Access::All;
		bool bInheritHandle = false;
		DWORD dwProcessId;
		OpenStruct(DWORD dwProcessId) : dwProcessId(dwProcessId) {}
	public:
		inline auto &Accesses(Access dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Inherit(bool bInheritHandle = true) reflect_to_self(this->bInheritHandle = bInheritHandle);
	public:
		inline operator Process() reflect_as(OpenProcess(dwDesiredAccess.yield(), bInheritHandle, dwProcessId));
	};
	static inline OpenStruct Open(DWORD dwProcessId) reflect_as(dwProcessId);

	static inline Process Current() reflect_as(GetCurrentProcess());
	static inline void Exit(UINT uExitCode = 0) reflect_to(ExitProcess(uExitCode));

	inline bool Terminate(UINT uExitCode = 0) {
		if (super::hObject)
			if (!TerminateProcess(super::hObject, uExitCode))
				return false;
		super::hObject = O;
		return true;
	}
	inline bool TerminateWait(DWORD dwMilliSec, DWORD dwExitCode = 0) {
		if (WaitForSignal(dwMilliSec)) return false;
		Terminate(dwExitCode);
		return true;
	}

public: // Property - ExitCode
	/* R */ inline auto ExitCode() const reflect_to(DWORD dwCode, (dwCode = GetExitCodeProcess(self, &dwCode)), dwCode);
public: // Property - ID
	/* R */ inline auto ID() const reflect_as(GetProcessId(self));
public: // Property - Memory
	/* W */ inline auto Memory() const assertl_reflect_to(PROCESS_MEMORY_COUNTERS pmc, GetProcessMemoryInfo(self, &pmc, sizeof(pmc)), pmc);
public: // Property - WorkingSetSize
	/* W */ inline auto &WorkingSetSize(SIZE_T Min, SIZE_T Max) assertl_reflect_as_self(SetProcessWorkingSetSize(self, Min, Max));
	/* R */ inline auto  WorkingSetSize() const assertl_reflect_to(struct _B_(SIZE_T Min, Max;) size, GetProcessWorkingSetSize(self, &size.Min, &size.Max), size);
public: // Property - HandleCount
	/* R */ inline DWORD HandleCount() const assertl_reflect_as(DWORD dwCount = 0, GetProcessHandleCount(self, &dwCount), dwCount);
public: // Property - WorkingSetSizeEx
	//GetProcessWorkingSetSizeEx
	//SetProcessWorkingSetSizeEx
public: // Property - Informations
	//GetProcessInformation
	//SetProcessInformation
public: // Property - PriorityBoost
	//GetProcessPriorityBoost
	//SetProcessPriorityBoost
public: // Property - ShutdownParameters
	//GetProcessShutdownParameters
	//SetProcessShutdownParameters
public: // Property - MitigationPolicy
	//GetProcessMitigationPolicy
	//SetProcessMitigationPolicy

public: // Property - CommandLine
	/* R */ static inline String CommandLine() reflect_as(+CString(GetCommandLine(), MaxLenNotice));
public: // Property - Environment
	/* W */ static inline void Environment(LPTCH lpNewEnvironment) assertl_reflect_as(SetEnvironmentStrings(lpNewEnvironment));
	/* R */ inline Environments Environment() assertl_reflect_to(LPTCH lpEnv, (lpEnv = GetEnvironmentStrings()), reuse_as<Environments>(lpEnv));

};
#pragma endregion

}
