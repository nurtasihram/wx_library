module;

#define WX_CPPM_REALTIME
#include "wx_realtime"
#include "wx__realtime.inl"

export module wx.realtime;

import wx;
import wx.proto;

export namespace WX {

template<class AnyChild>
class WaitableBase : public HandleBase<AnyChild> {
public:
	using super = HandleBase<AnyChild>;
protected:
	WaitableBase(HANDLE h) : super(h) {}
	WaitableBase(const WaitableBase &w) : super(w) {}
public:
	WaitableBase() {}
	WaitableBase(Null) {}
public:
	inline DWORD Wait(DWORD dwMilliseconds = INFINITE) const reflect_as(WX::WaitForSingleObject(self, dwMilliseconds));
};

#pragma region Event
enum_flags(EventAccess, HandleAccess,
	All    = EVENT_ALL_ACCESS,
	Modify = EVENT_MODIFY_STATE);
class BaseOf_Waitable(Event) {
public:
	using super = WaitableBase<Event>;
	using Access = EventAccess;
protected:
	Event(HANDLE h) : super(h) {}
	Event(const Event &evt) : super(evt) {}
public:
	Event() : Event(Create()) {}
	Event(Null) {}
	Event(Event &evt) : super(evt) {}
	Event(Event &&evt) : super(evt) {}
public: // Create
	template<class LPCTSTR>
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
		inline auto &Security(LPSECURITY_ATTRIBUTES pSA) reflect_to_self(this->lpAttributes = pSA);
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator Event() const reflect_as(WX::CreateEvent(lpAttributes, bManualReset, bInitialState, lpName));
	};
	static inline CreateStruct<LPCTSTR> Create() reflect_as(O);
	static inline CreateStruct<LPCSTR> Create(LPCSTR lpName) reflect_as(lpName);
	static inline CreateStruct<LPCWSTR> Create(LPCWSTR lpName) reflect_as(lpName);
public: // Open
	template<class LPCTSTR>
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
		inline operator Event() const reflect_as(WX::OpenEvent(dwDesiredAccess.yield(), bInheritHandle, lpName));
	};
	static inline OpenStruct<LPCTSTR> Open() reflect_as(O);
	static inline OpenStruct<LPCSTR> Open(LPCSTR lpName) reflect_as(lpName);
	static inline OpenStruct<LPCWSTR> Open(LPCWSTR lpName) reflect_as(lpName);
public:
	inline void Set() reflect_to(WX::SetEvent(self));
	inline void Reset() reflect_to(WX::ResetEvent(self));
	inline void Pulse() reflect_to(WX::PulseEvent(self));
public:
	using super::operator=;
	inline auto &operator=(bool bState) reflect_to_self(if (bState) Set(); else Reset(););
};
using CEvent = RefAs<Event>;
#pragma endregion

#pragma region Mutex
enum_flags(MutexAccess, HandleAccess,
	All    = MUTEX_ALL_ACCESS,
	Modify = MUTEX_MODIFY_STATE);
class BaseOf_Waitable(Mutex) {
public:
	using super = WaitableBase<Mutex>;
	using Access = MutexAccess;
protected:
	Mutex(HANDLE h) : super(h) {}
	Mutex(const Mutex &m) : super(m.hObject) reflect_to(m.hObject = O);
public:
	Mutex() : Mutex(Create()) {}
	Mutex(Null) {}
	Mutex(Mutex &m) : super(m) {}
	Mutex(Mutex &&m) : super(m) {}
public: // Create
	template<class LPCTSTR>
	class CreateStruct {
		friend class Mutex;
		LPSECURITY_ATTRIBUTES lpMutexAttributes = O;
		bool bInitialState = false;
		LPCTSTR lpName;
	protected:
		CreateStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &Preset(bool bInitialState = true) reflect_to_self(this->bInitialState = bInitialState);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpMutexAttributes) reflect_to_self(this->lpMutexAttributes = lpMutexAttributes);
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator Mutex() const reflect_as(WX::CreateMutex(lpMutexAttributes, bInitialState, lpName));
	};
	static inline CreateStruct<LPCTSTR> Create() reflect_as(O);
	static inline CreateStruct<LPCSTR> Create(LPCSTR lpName) reflect_as(lpName);
	static inline CreateStruct<LPCWSTR> Create(LPCWSTR lpName) reflect_as(lpName);
public: // Open
	template<class LPCTSTR>
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
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator Mutex() const reflect_as(WX::OpenMutex(dwDesiredAccess.yield(), bInheritHandle, lpName));
	};
	static inline OpenStruct<LPCTSTR> Open() reflect_as(O);
	static inline OpenStruct<LPCSTR> Open(LPCSTR lpName) reflect_as(lpName);
	static inline OpenStruct<LPCWSTR> Open(LPCWSTR lpName) reflect_as(lpName);
public:
	inline void Release() reflect_to(WX::ReleaseMutex(self));
public:
	using super::operator=;
};
using CMutex = RefAs<Mutex>;
#pragma endregion

#pragma region Semaphore
enum_flags(SemaphoreAccess, HandleAccess,
	All    = SEMAPHORE_ALL_ACCESS,
	Modify = SEMAPHORE_MODIFY_STATE);
class BaseOf_Waitable(Semaphore) {
public:
	using super = WaitableBase<Semaphore>;
	using Access = SemaphoreAccess;
protected:
	Semaphore(HANDLE h) : super(h) {}
	Semaphore(const Semaphore & s) : super(s.hObject) reflect_to(s.hObject = O);
#if 0
public:
	Semaphore() : Semaphore(Create()) {}
	Semaphore(Null) {}
	Semaphore(Semaphore & s) : super(s) {}
	Semaphore(Semaphore && s) : super(s) {}
public: // Create
	template<class LPCTSTR>
	class CreateStruct {
		friend class Semaphore;
		LPSECURITY_ATTRIBUTES lpSemaphoreAttributes = O;
		LONG lInitialCount = 0;
		LONG lMaximumCount = 1;
		LPCTSTR lpName;
	protected:
		CreateStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &InitialCount(LONG lInitialCount) reflect_to_self(this->lInitialCount = lInitialCount);
		inline auto &MaximumCount(LONG lMaximumCount) reflect_to_self(this->lMaximumCount = lMaximumCount);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpSemaphoreAttributes) reflect_to_self(this->lpSemaphoreAttributes = lpSemaphoreAttributes);
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator Semaphore() const assertl_reflect_as(CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName), h);
	};
	static inline CreateStruct<LPCTSTR> Create() reflect_as(O);
	static inline CreateStruct<LPCSTR> Create(LPCSTR lpName) reflect_as(lpName);
	static inline CreateStruct<LPCWSTR> Create(LPCWSTR lpName) reflect_as(lpName);
public: // Open
	template<class LPCTSTR>
	class OpenStruct {
		friend class Semaphore;
		Access dwDesiredAccess = Access::Modify;
		bool bInheritHandle = false;
		LPCTSTR lpName;
	protected:
		OpenStruct(LPCTSTR lpName) : lpName(lpName) {}
	public:
		inline auto &Accesses(Access dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Inherit(bool bInheritHandle = true) reflect_to_self(this->bInheritHandle = bInheritHandle);
		inline auto &Name(LPCTSTR lpName) reflect_to_self(this->lpName = lpName);
	public:
		inline operator Semaphore() const reflect_as(WX::OpenSemaphore(dwDesiredAccess.yield(), bInheritHandle, lpName));
	};
	static inline OpenStruct<LPCTSTR> Open() reflect_as(O);
	static inline OpenStruct<LPCSTR> Open(LPCSTR lpName) reflect_as(lpName);
	static inline OpenStruct<LPCWSTR> Open(LPCWSTR lpName) reflect_as(lpName);
#endif
public:
	using super::operator=;
};
#pragma endregion

#pragma region WaitableTimer
enum_flags(TimerAccess, HandleAccess,
	All    = TIMER_ALL_ACCESS,
	Modify = TIMER_MODIFY_STATE);
using WaitableTimerAccess = TimerAccess;
class BaseOf_Waitable(WaitableTimer) {
public:
	using super = WaitableBase<WaitableTimer>;
	using Access = TimerAccess;
protected:
	WaitableTimer(HANDLE h) : super(h) {}
	WaitableTimer(const WaitableTimer &t) : super(t.hObject) reflect_to(t.hObject = O);
#if 0
public:
	WaitableTimer() : WaitableTimer(Create()) {}
	WaitableTimer(Null) {}
	WaitableTimer(WaitableTimer &t) : super(t) {}
	WaitableTimer(WaitableTimer &&t) : super(t) {}
public:
	template<class LPCTSTR>
	class CreateStruct {
		friend class WaitableTimer;
		LPSECURITY_ATTRIBUTES lpWaitableTimerAttributes = O;
		bool bManualReset = false;
		LPCTSTR lpWaitableTimerName = O;
	protected:
		CreateStruct(LPCTSTR lpWaitableTimerName) : lpWaitableTimerName(lpWaitableTimerName) {}
	public:
		inline auto &ManualReset(bool bManualReset = true) reflect_to_self(this->bManualReset = bManualReset);
		inline auto &Security(LPSECURITY_ATTRIBUTES lpWaitableTimerAttributes) reflect_to_self(this->lpWaitableTimerAttributes = lpWaitableTimerAttributes);
		inline auto &Name(LPCTSTR lpWaitableTimerName) reflect_to_self(this->lpWaitableTimerName = lpWaitableTimerName);
	public:
		inline operator WaitableTimer() const reflect_as(WX::CreateWaitableWaitableTimer(lpWaitableTimerAttributes, bManualReset, lpWaitableTimerName));
	};
	static inline CreateStruct<LPCTSTR> Create() reflect_as(O);
	static inline CreateStruct<LPCSTR> Create(LPCSTR lpWaitableTimerName) reflect_as(lpWaitableTimerName);
	static inline CreateStruct<LPCWSTR> Create(LPCWSTR lpWaitableTimerName) reflect_as(lpWaitableTimerName);
public:
	template<class LPCTSTR>
	class OpenStruct {
		friend class WaitableTimer;
		Access dwDesiredAccess = Access::Modify;
		BOOL bInheritHandle = FALSE;
		LPCTSTR lpWaitableTimerName;
	protected:
		OpenStruct(LPCTSTR lpWaitableTimerName) : lpWaitableTimerName(lpWaitableTimerName) {}
	public:
		inline auto &Accesses(Access dwDesiredAccess) reflect_to_self(this->dwDesiredAccess = dwDesiredAccess);
		inline auto &Inherit(BOOL bInheritHandle = TRUE) reflect_to_self(this->bInheritHandle = bInheritHandle);
		inline auto &Name(LPCTSTR lpWaitableTimerName) reflect_to_self(this->lpWaitableTimerName = lpWaitableTimerName);
	public:
		inline operator WaitableTimer() const reflect_as(WX::OpenWaitableWaitableTimer(dwDesiredAccess.yield(), bInheritHandle, lpWaitableTimerName));
	};
	static inline OpenStruct<LPCTSTR> Open() reflect_as(O);
	static inline OpenStruct<LPCSTR> Open(LPCSTR lpWaitableTimerName) reflect_as(lpWaitableTimerName);
	static inline OpenStruct<LPCWSTR> Open(LPCWSTR lpWaitableTimerName) reflect_as(lpWaitableTimerName);
#endif
public:
	using super::operator=;
};
using Timer = WaitableTimer;
#pragma endregion

#pragma region PrivateNamespace
class BaseOf_Handle(PrivateNamespace) {
public:
	using super = HandleBase<PrivateNamespace>;
protected:
	PrivateNamespace(HANDLE h) : super(h) {}
	PrivateNamespace(const PrivateNamespace & t) : super(t.hObject) reflect_to(t.hObject = O);
public:
	PrivateNamespace() {}
	PrivateNamespace(PrivateNamespace &t) : super(t) {}
	PrivateNamespace(PrivateNamespace &&t) : super(t) {}
};
using Namespace = PrivateNamespace;
#pragma endregion

struct PTTimes { FileTime CreationTime, ExitTime, KernelTime, UserTime; };

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
class BaseOf_Waitable(ThreadBase<>) {
public:
	using super = WaitableBase<ThreadBase<>>;
	using Access = ThreadAccess;
protected:
	INNER_USE(Thread);
	friend class Process;
	ThreadBase(HANDLE h) : super(h) {}
	ThreadBase(const ThreadBase &t) : super(t.hObject) reflect_to(t.hObject = O);
public:
	ThreadBase() {}
	ThreadBase(Null) {}
	ThreadBase(ThreadBase &t) : super(t.hObject) reflect_to(t.hObject = O);
	ThreadBase(ThreadBase &&t) : super(t.hObject) reflect_to(t.hObject = O);
public:
	template<class AnyChild = void>
	class CreateStruct : public ChainExtender<CreateStruct<AnyChild>, AnyChild> {
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
		inline auto &Security(LPSECURITY_ATTRIBUTES lpThreadAttributes) reflect_to_child(this->lpThreadAttributes = lpThreadAttributes);
		inline auto &StackSize(size_t dwStackSize) reflect_to_child(this->dwStackSize = dwStackSize, this->dwCreationFlags &= ~STACK_SIZE_PARAM_IS_A_RESERVATION);
		inline auto &Suspend(bool bSuspend = true) reflect_to_child(this->dwCreationFlags = bSuspend ? (this->dwCreationFlags | CREATE_SUSPENDED) : (this->dwCreationFlags & ~CREATE_SUSPENDED));
	public:
		template<class _Child>
		inline ThreadBase<_Child> Create() reflect_as(WX::CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, O));
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
		inline operator ThreadBase() const reflect_as(WX::OpenThread(dwDesiredAccess.yield(), bInheritHandle, dwThreadId));
	};
	static inline OpenStruct Open(DWORD dwProcessId) reflect_as(dwProcessId);
	static inline Thread Current() reflect_as(WX::GetCurrentThread());
	static inline void Exit(DWORD dwExitCode = 0) reflect_to(WX::ExitThread(dwExitCode));
public:
	inline DWORD Suspend() reflect_as(WX::SuspendThread(self));
	inline DWORD Resume() reflect_as(WX::ResumeThread(self));
	inline void Terminate(DWORD dwExitCode = 0) reflect_to(WX::TerminateThread(this->hObject, dwExitCode));
	template<class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline void Post(MsgType msgid, WParam wParam = 0, LParam lParam = 0) reflect_to(WX::PostThreadMessage<>(ID(), reuse_as<UINT>(msgid), small_cast<WPARAM>(wParam), small_cast<LPARAM>(lParam)));
	template<class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline void PostA(MsgType msgid, WParam wParam = 0, LParam lParam = 0) reflect_to(WX::PostThreadMessage<false>(ID(), reuse_as<UINT>(msgid), small_cast<WPARAM>(wParam), small_cast<LPARAM>(lParam)));
	template<class MsgType = UINT, class WParam = WPARAM, class LParam = LPARAM>
	inline void PostW(MsgType msgid, WParam wParam = 0, LParam lParam = 0) reflect_to(WX::PostThreadMessage<true>(ID(), reuse_as<UINT>(msgid), small_cast<WPARAM>(wParam), small_cast<LPARAM>(lParam)));
#pragma region Properties
public: // Property - ID
	/* W */ inline DWORD ID() const reflect_as(WX::GetThreadId(self));
public: // Property - ExitCode
	/* W */ inline DWORD ExitCode() const reflect_to(DWORD dwExitCode; WX::GetExitCodeThread(self, &dwExitCode), dwExitCode);
public: // Property - StillActive
	/* W */ inline bool StillActive() const {
		if (self)
			if (ExitCode() == STILL_ACTIVE)
				return !super::Wait(0);
		return false;
	}
public: // Property - ProcessID
	/* R */ inline auto ProcessID() const reflect_as(WX::GetProcessIdOfThread(self));
public: // Property - Times
	/* R */ inline auto Times() reflect_to(PTTimes t; WX::GetThreadTimes(self, &t.CreationTime, &t.ExitTime, &t.KernelTime, &t.UserTime), t);
#pragma endregion
public:
	using super::operator=;
};
template<class AnyChild>
class ThreadBase : public Thread,
	public ChainExtender<ThreadBase<AnyChild>, AnyChild> {
public:
	using super = Thread;
protected:
	friend class ThreadBase<>;
	using ChainExtender<ThreadBase<AnyChild>, AnyChild>::child_;
	static DWORD WINAPI Proc(LPVOID lpThis) {
		auto pThis = static_cast<ThreadBase *>(lpThis);
	retry:
		try {
			return pThis->Run();
		} catch (Exception err) {
			if (pThis->Catch(err))
				goto retry;
			return pThis->Final();
		}
		return -2; // unreachable
	}
protected:
	use_member(OnRun);
	inline DWORD Run() {
		static_assert(member_OnRun_of<AnyChild>::is_addressable,
					  "Member OnRun uncallable, unexisted or undefined");
		if constexpr (member_OnRun_of<AnyChild>::template compatible_to<DWORD()>)
			return child.OnRun();
		else {
			static_assert(member_OnRun_of<AnyChild>::template compatible_to<void()>,
						  "Member OnRun must be compatible to DWORD() or void()");
			return (child.OnRun(), 0);
		}
	}
	use_member(OnCatch);
	inline wx_answer Catch(const Exception &err) {
		if constexpr (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer(Exception)>)
			return child.OnCatch(err);
		elif constexpr (member_OnCatch_of<AnyChild>::template compatible_to<wx_answer()>)
			return child.OnCatch();
		elif constexpr (member_OnCatch_of<AnyChild>::template compatible_to<void(Exception)>)
			return (child.OnCatch(err), false);
		elif constexpr (member_OnCatch_of<AnyChild>::template compatible_to<void()>)
			return (child.OnCatch(), false);
		else {
			static_assert(!member_OnCatch_of<AnyChild>::is_addressable,
						  "Member OnCatch must be compatible as wx_answer(Exception), wx_answer(), void(Exception) or void()");
			switch (MsgBox(Cats(T("Thread[PID:"), ID(), T("] error")), err.toString())) {
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
	use_member(OnFinal);
	inline DWORD Final() {
		if constexpr (member_OnFinal_of<AnyChild>::template compatible_to<DWORD()>)
			return child.OnFinal();
		elif constexpr (member_OnFinal_of<AnyChild>::template compatible_to<void()>)
			return (child.OnFinal(), -1);
		else {
			static_assert(!member_OnFinal_of<AnyChild>::is_addressable,
						  "Member OnFinal must be compatible to DWORD() or void()");
			return -3;
		}
	}
protected:
	ThreadBase(HANDLE h) : super(h) {}
	ThreadBase(const ThreadBase &t) : super(t) {}
public:
	ThreadBase() {}
	ThreadBase(Null) {}
	ThreadBase(ThreadBase &t) : super(t) {}
	ThreadBase(ThreadBase &&t) : super(t) {}
public:
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
protected:
	inline auto &operator=(ThreadBase &t) reflect_to_child(std::swap(this->hObject, t.hObject));
	inline auto &operator=(ThreadBase &&t) reflect_to_child(std::swap(this->hObject, t.hObject));
	inline auto &operator=(const ThreadBase &t) const reflect_to_child(std::swap(this->hObject, t.hObject));
};
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
				return f();
			else {
				static_assert(static_compatible<AnyCallable, void()>, "Error uncompatible");
				return (f(), 0L);
			}
		}
	};
	StartClosure *lpStart = O;
	inline DWORD OnRun() reflect_as((*lpStart)());
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
				return lOnCatch(err);
			elif constexpr (static_compatible<AnyCatch, wx_answer()>)
				return lOnCatch();
			elif constexpr (static_compatible<AnyCatch, void(Exception)>)
				return (lOnCatch(err), false);
			else {
				static_assert(static_compatible<AnyCatch, void()>, "OnCatch uncompatible");
				return (lOnCatch(err), false);
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
	LThread(const AnyCallable &OnRun) : lpStart(new InlineStartClosure<AnyCallable>(OnRun)) {}
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

#pragma region Environment
template<bool IsUnicode = WX::IsUnicode>
class EnvironmentsX {
	using TCHAR = XCHAR<IsUnicode>;
	using LPTCH = TCHAR *;
	using LPCTSTR = const TCHAR *;
	using String = StringBase<TCHAR>;
private:
	LPTCH lpEnv = O;
public:
	class Variable {
		friend class EnvironmentsX;
		const String name;
		const String value;
	public:
		Variable() {}
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
			DWORD len;
			assertl((len = ExpandEnvironmentStrings(value, O, 0)) > 0);
			if (len - 1 == value.Length()) return &value;
			auto lpsz = String::Alloc(len - 1);
			assertl(len == ExpandEnvironmentStrings(value, lpsz, len));
			return{ len, lpsz };
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
	EnvironmentsX(LPTCH lpEnv) : lpEnv(lpEnv) {}
public:
	EnvironmentsX() {}
	EnvironmentsX(Null) {}
	EnvironmentsX(EnvironmentsX &env) : lpEnv(env.lpEnv) reflect_to(env.lpEnv = O);
	EnvironmentsX(EnvironmentsX &&env) : lpEnv(env.lpEnv) reflect_to(env.lpEnv = O);
	~EnvironmentsX() reflect_to(Free());
public:
	static inline EnvironmentsX From(std::initializer_list<const String> envs) {
		size_t maxlen = 1;
		for (const String &env : envs)
			if (env.Length())
				maxlen += env.Length() + 1;
		if (maxlen <= 1) return O;
		LPTCH lpEnv = (LPTCH)ThisHeap->Alloc(maxlen * sizeof(TCHAR)), pEnv = lpEnv;
		for (const String &env : envs)
			if (auto len = env.Length()) {
				CopyMemory(pEnv, (LPCTSTR)env, len * sizeof(TCHAR));
				pEnv += len;
				*pEnv++ = '\0';
			}
		*pEnv = '\0';
		return lpEnv;
	}
	static inline EnvironmentsX From(std::initializer_list<const Variable> vars) {
		size_t maxlen = 1;
		for (const Variable &var : vars)
			if (var)
				maxlen += var.name.Length() + var.value.Length() + 2;
		if (maxlen <= 1) return O;
		LPTCH lpEnv = (LPTCH)ThisHeap->Alloc(maxlen * sizeof(TCHAR)), pEnv = lpEnv;
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
	static inline EnvironmentsX Current() reflect_as(GetEnvironmentStrings<IsUnicode>());
public:
	inline void Free() {
		if (lpEnv)
			FreeEnvironmentStrings(lpEnv);
		lpEnv = O;
	}
public:
	inline void Use() const reflect_to(SetEnvironmentStrings(lpEnv));
#pragma region Properties
public: // Property - Count
	/* R */ inline size_t Count() const {
		if (!lpEnv) return 0;
		size_t count = 0;
		for (auto ch = lpEnv; *ch != '\0'; ++ch) {
			while (*ch != '\0')
				++ch;
			++count;
		}
		return count;
	}
public: // Property - Entries
	template<size_t MaxLen = MaxLenNotice>
	/* R */ inline std::vector<String> Entries() const {
		size_t count = Count();
		std::vector<String> list(count);
		auto lpEnv = this->lpEnv;
		for (const String &e : list)
			lpEnv += (e = CString(lpEnv, v)).Length() + 1;
		return list;
	}
public: // Property - Variables
	template<size_t MaxLen = MaxLenNotice>
	/* R */ inline std::vector<Variable> Variables() const {
		size_t count = Count();
		std::vector<Variable> list(count);
		auto lpEnv = this->lpEnv;
		for (const Variable &e : list) {
			auto lpName = lpEnv;
			while (*lpEnv++ != '=');
			e.name = CString(lpEnv - lpName - 1, lpName);
			e.value = CString(lpEnv, MaxLen);
			lpEnv += e.value.Length() + 1;
		}
		return list;
	}
#pragma endregion
public:
	inline operator bool() const reflect_as(lpEnv);
	inline operator LPTCH() const reflect_as(lpEnv);
};
using Environments = EnvironmentsX<IsUnicode>;
using EnvironmentsA = EnvironmentsX<false>;
using EnvironmentsW = EnvironmentsX<true>;
class CurrentEnvironment {
	template<class TCHAR>
	class Variable {
		locale_charmode(IsCharW<TCHAR>);
		using LPCTSTR = const TCHAR *;
		using String = StringX<IsUnicode>;
	private:
		LPCTSTR lpName;
	public:
		Variable(LPCTSTR lpName) : lpName(lpName) {}
	public: // Property - Value
		/* W */ inline auto &Value(LPCTSTR lpValue) 
			reflect_to_self(SetEnvironmentVariable(lpName, lpValue));
		/* R */ inline String Value() const {
			auto len = GetEnvironmentVariable(lpName, O, 0);
			auto lpsz = String::Alloc(len - 1);
			assertl(len - 1 == GetEnvironmentVariable(lpName, lpsz, len));
			return{ len, lpsz };
		}
	public: // Property - Expand
		/* R */ inline String Expand() const {
			auto &&val = Value();
			auto len = ExpandEnvironmentStrings(val, O, 0);
			if (val.Length() == len) return val;
			auto lpsz = String::Alloc(len - 1);
			assertl(len - 1 == ExpandEnvironmentStrings(val, lpsz, len));
			return{ len, lpsz };
		}
	public:
		inline auto &operator=(LPCTSTR lpValue) reflect_to_self(Value(lpValue));
		inline operator bool() const reflect_as(GetEnvironmentVariable(lpName, O, 0));
		inline operator String() const reflect_as(Value());
		inline String operator+() const reflect_as(Expand());
		inline bool operator!=(Null) const reflect_as(GetEnvironmentVariable(lpName, O, 0) != 0);
		inline bool operator==(Null) const reflect_as(GetEnvironmentVariable(lpName, O, 0) == 0);
	};
public:
///	inline operator Environments() reflect_as(Environments::Current());
//	inline void operator=(const Environments &env) reflect_to(env.Use());
	template<class TCHAR>
	inline Variable<TCHAR> operator[](const TCHAR *lpName) reflect_as(lpName);
} inline Environment;
#pragma endregion

#pragma region Process
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
template<bool IsUnicode = WX::IsUnicode>
class StartupInfoX : public RefStruct<switch_structx(STARTUPINFO)> {
	using_structx(WNDCLASSEX);
	using LPTSTR = LPXSTR<IsUnicode>;
	using String = StringX<IsUnicode>;
public:
	using super = RefStruct<STARTUPINFO>;
public:
	StartupInfoX() reflect_to(WX::GetStartupInfo(this));
	StartupInfoX(Null) reflect_to(self->cb = sizeof(*self));
	StartupInfoX(const STARTUPINFO &si) : super(si) {}
public: // Property - Desktop
 	/* W */ inline auto&Desktop(LPTSTR lpDesktop) reflect_to_self(self->lpDesktop = lpDesktop);
	template<size_t MaxLen = MaxLenTitle>
 	/* R */ inline const String Desktop() const reflect_as(CString(self->lpDesktop, MaxLen));
public: // Property - Title
 	/* W */ inline auto &Title(LPTSTR lpTitle) reflect_to_self(self->lpTitle = lpTitle);
	template<size_t MaxLen = MaxLenTitle>
	/* R */ inline const String Title() const reflect_as(CString(self->lpTitle, MaxLen));
public: // Property - Position
	/* W */ inline auto  &Position(LPoint pos) reflect_to_self(self->dwFlags |= STARTF_USEPOSITION, self->dwX = pos.x, self->dwY = pos.y);
	/* R */ inline LPoint Position() const reflect_as({ (LONG)self->dwX, (LONG)self->dwY });
public: // Property - Size
	/* W */ inline auto &Size(LSize size) reflect_to_self(self->dwFlags |= STARTF_USESIZE, self->dwXSize = size.cx, self->dwYSize = size.cy);
	/* R */ inline LSize Size() const reflect_as({ (LONG)self->dwXSize, (LONG)self->dwYSize });
public: // Property - CountCmhars
	/* W */ inline auto &CountChars(LSize size) reflect_to_self(self->dwFlags |= STARTF_USECOUNTCHARS, self->dwXCountChars = size.cx, self->dwYCountChars = size.cy);
	/* R */ inline LSize CountChars() const reflect_as({ (LONG)self->dwXCountChars, (LONG)self->dwYCountChars });
public: // Property - FillAttribute
	/* W */ inline auto &FillAttribute(DWORD dwFillAttribute) reflect_to_self(self->dwFlags |= STARTF_USEFILLATTRIBUTE, self->dwFillAttribute = dwFillAttribute);
	/* R */ inline auto  FillAttribute() const reflect_as(self->dwFillAttribute);
public: // Property - Flags
	/* R */ inline StartupFlag Flags() const reflect_as(reuse_as<StartupFlag>(self->dwFlags));
public: // Property - Show
	/* W */ inline auto  &Show(WX::SW wShow) reflect_to_self(self->dwFlags |= STARTF_USESHOWWINDOW, self->wShowWindow = wShow.yield());
	/* R */ inline WX::SW Show() const reflect_as(reuse_as<WX::SW>((DWORD)self->wShowWindow));
public: // Property - StdInput
	/* W */ inline auto &StdInput(HANDLE hStdInput) reflect_to_self(self->dwFlags |= STARTF_USESTDHANDLES, self->hStdInput = hStdInput);
	/* R */ inline auto  StdInput() const reflect_as(self->hStdInput);
public: // Property - StdOutput
	/* W */ inline auto &StdOutput(HANDLE hStdOutput) reflect_to_self(self->dwFlags |= STARTF_USESTDHANDLES, self->hStdOutput = hStdOutput);
	/* R */ inline auto  StdOutput() const reflect_as(self->hStdOutput);
public: // Property - StdError
	/* W */ inline auto &StdError(HANDLE hStdError) reflect_to_self(self->dwFlags |= STARTF_USESTDHANDLES, self->hStdError = hStdError);
	/* R */ inline auto  StdError() const reflect_as(self->hStdError);
};
using StartupInfo = StartupInfoX<IsUnicode>;
using StartupInfoA = StartupInfoX<false>;
using StartupInfoW = StartupInfoX<true>;
enum_flags(ProcessCreateFlag, DWORD,
	Default         = 0,
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
	All          = PROCESS_ALL_ACCESS);
class BaseOf_Waitable(Process) {
public:
	using super = WaitableBase<Process>;
	using Access = ProcessAccess;
	using CreateFlag = ProcessCreateFlag;
protected:
	Process(HANDLE h) : super(h) {}
	Process(const Process &p) : super(p) {}
public:
	Process() {}
	Process(Null) {}
	Process(Process &p) : super(p) {}
	Process(Process &&p) : super(p) {}
public:
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
		inline auto &Security(LPSECURITY_ATTRIBUTES lpProcessAttributes) reflect_to_self(this->lpProcessAttributes = lpProcessAttributes);
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
		inline auto &Create() reflect_to(CreateProcess(
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
public:
	inline void Terminate(UINT uExitCode = 0) {
		if (super::hObject)
			TerminateProcess(super::hObject, uExitCode);
		super::hObject = O;
	}
#pragma region Properties
public: // Property - ExitCode
	/* R */ inline auto ExitCode() const reflect_to(DWORD dwCode; GetExitCodeProcess(self, &dwCode), dwCode);
public: // Property - ID
	/* R */ inline auto ID() const reflect_as(GetProcessId(self));
public: // Property - SysDPI
	/* R */ inline UINT SysDPI() const reflect_as(WX::GetSystemDpiForProcess(self));
public: // Property - Memory
//	/* W */ inline auto Memory() const reflect_to(PROCESS_MEMORY_COUNTERS pmc; GetProcessMemoryInfo(self, &pmc, sizeof(pmc)), pmc);
public: // Property - Times
	/* R */ inline auto Times() reflect_to(PTTimes t; WX::GetProcessTimes(self, &t.CreationTime, &t.ExitTime, &t.KernelTime, &t.UserTime), t);
public: // Property - WorkingSetSize
	/* W */ inline auto &WorkingSetSize(SIZE_T Min, SIZE_T Max) assertl_reflect_as_self(SetProcessWorkingSetSize(self, Min, Max));
	/* R */ inline auto  WorkingSetSize() const assertl_reflect_to(struct _B_(SIZE_T Min, Max;) size, GetProcessWorkingSetSize(self, &size.Min, &size.Max), size);
public: // Property - HandleCount
	/* R */ inline DWORD HandleCount() const reflect_to(DWORD dwHandleCount; GetProcessHandleCount(self, &dwHandleCount), dwHandleCount);
public: // Property - Immersive
	/* R */ inline bool Immersive() const reflect_as(WX::IsImmersiveProcess(self));
#pragma endregion
public:
	using super::operator=;
};
using CProcess = RefAs<Process>;
#pragma endregion

// Property - CommandLine
template<bool IsUnicode = WX::IsUnicode>
/* R */ inline StringX<IsUnicode> CommandLine() reflect_as(+CString(GetCommandLine<IsUnicode>(), 0x1ff));
/* R */ inline StringA CommandLineA() reflect_as(CommandLine<false>());
/* R */ inline StringW CommandLineW() reflect_as(CommandLine<true>());
// Property - Directory
template<class TCHAR>
/* W */ inline void CurrentDirectory(const TCHAR *lpPath) reflect_to(SetCurrentDirectory(lpPath));
template<bool IsUnicode>
/* R */ inline StringX<IsUnicode> CurrentDirectory() {
	auto len = GetCurrentDirectory(0, (LPXSTR<IsUnicode>)O);
	auto lpsz = StringX<IsUnicode>::Alloc(len);
	assertl(len == GetCurrentDirectory(len, lpsz));
	return{ len, lpsz };
}
/* R */ inline StringA CurrentDirectoryA() reflect_as(CurrentDirectory<false>());
/* R */ inline StringW CurrentDirectoryW() reflect_as(CurrentDirectory<true>());
// Property - UserName
template<bool IsUnicode>
/* R */ inline StringX<IsUnicode> CurrentUserName() {
	DWORD len = 0;
	GetUserName((LPXSTR<IsUnicode>)O, &len);
	auto lpsz = StringX<IsUnicode>::Alloc(len);
	GetUserName(lpsz, &len);
	return{ len, lpsz };
}
inline StringA CurrentUserNameA() reflect_as(CurrentUserName<false>());
inline StringW CurrentUserNameW() reflect_as(CurrentUserName<true>());
// Property - ComputerName
template<bool IsUnicode>
/* R */ inline StringX<IsUnicode> CurrentComputerName() {
	DWORD len = 0;
	GetComputerName((LPXSTR<IsUnicode>)O, &len);
	auto lpsz = StringX<IsUnicode>::Alloc(len);
	GetComputerName(lpsz, &len);
	return{ len, lpsz };
}
/* R */ inline StringA CurrentComputerNameA() reflect_as(CurrentComputerName<false>());
/* R */ inline StringW CurrentComputerNameW() reflect_as(CurrentComputerName<true>());
// Property - ProcessID
/* R */ inline DWORD CurrentProcessID() reflect_as(GetCurrentProcessId());
// Property - ThreadID
/* R */ inline DWORD CurrentThreadID() reflect_as(GetCurrentThreadId());

}
