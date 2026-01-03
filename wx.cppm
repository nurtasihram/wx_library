module;

#define WX_CPPM_CORE
#include "wx"

export module wx;

subtype_branch(super);
subtype_branch(ProtoEnum);

export namespace WX {

constexpr bool IsUnicode =
#if defined(UNICODE)
	UNICODE;
#elif defined(_UNICODE)
	_UNICODE;
#else
	false;
#endif

template<class Type1, class Type2>
constexpr bool is_equal = false;
template<class SameType>
constexpr bool is_equal<SameType, SameType> = true;

template<class Type1, class Type2>
constexpr bool IsEqual(Type1, Type2) reflect_as(is_equal<Type1, Type2>);

template<class Type1, class Type2>
concept IsSizeEqual = sizeof(Type1) == sizeof(Type2);

template<class AnyType>
concept IsIntager = // std::is_same_v<int8_t, AnyType> ||		// may duplicated with char
					// std::is_same_v<int16_t, AnyType> ||		// may duplicated with wchar_t
					std::is_same_v<int32_t, AnyType> ||
					std::is_same_v<int64_t, AnyType> ||
					std::is_same_v<uint8_t, AnyType> ||
					std::is_same_v<uint16_t, AnyType> ||
					std::is_same_v<uint32_t, AnyType> ||
					std::is_same_v<uint64_t, AnyType>;
template<class AnyType>
concept IsFloat = std::is_same_v<float, AnyType> ||
				  std::is_same_v<double, AnyType>;
				  // || std::is_same_v<long double, AnyType>	// Unsupport by some compilers
template<class AnyType>
concept IsNumber = IsIntager<AnyType> || IsFloat<AnyType>;

#pragma region Type Reference Helpers
template<class OutType>
inline OutType &ref_as(IsSizeEqual<OutType> auto &in) reflect_as(*(OutType *)&in);
template<class OutType>
inline OutType reuse_as(IsSizeEqual<OutType> auto in) reflect_as(*(OutType *)&in);
template<class OutType, class InType>
inline OutType small_cast(InType in) {
	misuse_assert(sizeof(OutType) >= sizeof(InType), "sizeof in-type must small or equal to out-type");
	return *(OutType *)&in;
}
template<class OutType, class InType>
inline OutType big_cast(InType in) {
	misuse_assert(sizeof(OutType) <= sizeof(InType), "sizeof in-type must big or equal to out-type");
	return *(OutType *)&in;
}
template<class AnyType>
inline AnyType &&inject(AnyType &a) {
	return static_cast<AnyType &&>(a);
}
#pragma endregion

#pragma region Array & Counter 
template<class AnyType, size_t Len>
using arrayof = AnyType[Len];
template<class AnyType, size_t Len>
constexpr size_t CountOf(const arrayof<AnyType, Len> &) reflect_as(Len);
template<class AnyType>
struct SizeOf_t { static constexpr size_t val = sizeof(AnyType); };
template<>
struct SizeOf_t<void> { static constexpr size_t val = 0; };
template<class AnyType>
constexpr size_t SizeOf = SizeOf_t<AnyType>::val;
#pragma endregion

#pragma region ToProto
template<class AnyType>
struct to_proto_t { using type = AnyType; };
template<class AnyType>
struct to_proto_t<AnyType *> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<AnyType &> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<AnyType &&> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<const AnyType> : to_proto_t<AnyType> {};
template<class AnyType>
struct to_proto_t<volatile AnyType> : to_proto_t<AnyType> {};
template<class AnyType>
using to_proto = typename to_proto_t<AnyType>::type;
#pragma endregion

#pragma region TypeList
template<class...>
struct TypeList;
template<>
struct TypeList<> {
	static constexpr size_t Length = 0;
	template<class AnyType>
	inline auto invoke(AnyType f) reflect_as(f());
};
template<>
struct TypeList<void> {
	template<int ind>
	struct index;
	template<size_t ind>
	inline void indexof() { misuse_assert(ind >= 0, "index overflowed"); }
	template<class AnyType>
	inline auto invoke(AnyType f) reflect_as(f());
};
template<class Type0>
struct TypeList<Type0> {
	Type0 type;
	template<class AnyType>
	TypeList(AnyType &type) : type(type) {}
	template<class AnyType>
	TypeList(AnyType &&type) : type(type) {}
	static constexpr size_t Length = 1;
	template<int ind, class = void>
	struct index { misuse_assert(ind >= 0, "Index overflowed"); };
	template<class ___>
	struct index<0, ___> { using type = Type0; };
	template<size_t ind>
	using IndexOf = typename index<ind>::type;
	template<size_t ind>
	inline auto &indexof() reflect_to(misuse_assert(ind >= 0, "index overflowed"), type);
public:
	template<class ClassType, class MethodType>
	inline auto invoke(ClassType &cls, MethodType method) reflect_as((cls.*method)(std::forward<Type0>(type)));
	template<class AnyType>
	inline auto invoke(AnyType f) reflect_as(f(std::forward<Type0>(type)));
};
template<class Type0, class...Types>
struct TypeList<Type0, Types...> : TypeList<Types...> {
	Type0 type;
	template<class AnyType, class...Args>
	TypeList(AnyType &type, Args...args) : TypeList<Types...>(args...), type(type) {}
	template<class AnyType, class...Args>
	TypeList(AnyType &&type, Args...args) : TypeList<Types...>(args...), type(type) {}
	static constexpr size_t Length = 1 + sizeof...(Types);
	template<size_t ind, class = void>
	struct index : TypeList<Types...>::template index<ind - 1> {};
	template<class ___>
	struct index<0, ___> { using type = Type0; };
	template<size_t ind>
	using IndexOf = typename index<ind>::type;
	template<size_t ind>
	inline auto &indexof() {
		if_c (ind)
			 return TypeList<Types...>::template indexof<ind - 1>();
		else return type;
	}
	using ind_seq = std::index_sequence_for<Type0, Types...>;
private:
	template<class ClassType, class MethodType, size_t... ind>
	inline auto invoke(ClassType &cls, MethodType method, std::index_sequence<ind...>) reflect_as((cls.*method)(indexof<ind>()...));
	template<class AnyType, size_t... ind>
	inline auto invoke(AnyType f, std::index_sequence<ind...>) reflect_as(f(indexof<ind>()...));
public:
	template<class ClassType, class MethodType>
	inline auto invoke(ClassType &cls, MethodType method) reflect_as(invoke(cls, method, ind_seq{}));
	template<class AnyType>
	inline auto invoke(AnyType f) reflect_as(invoke(f, ind_seq{}));
};
#pragma endregion

#pragma region FunctionOf
template<class OtherType>
struct __functionof {
	static constexpr bool is_static = false;
	static constexpr bool is_method = false;
};
template<class Ret, class AnyClass, class...Args>
struct __functionof<Ret(AnyClass:: *)(Args...)> {
	using Parent = AnyClass;
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(AnyClass:: *)(Args...);
	static constexpr bool is_method = true;
	static constexpr bool is_static = false;
	static constexpr bool is_ellipsis = false;
};
template<class Ret, class AnyClass, class...Args>
struct __functionof<Ret(AnyClass:: *)(Args..., ...)> {
	using Parent = AnyClass;
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(AnyClass:: *)(Args...);
	static constexpr bool is_method = true;
	static constexpr bool is_static = false;
	static constexpr bool is_ellipsis = true;
};
template<class Ret, class... Args>
struct __functionof<Ret(Args...)> {
	using Parent = void;
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(*)(Args...);
	static constexpr bool is_method = false;
	static constexpr bool is_static = true;
	static constexpr bool is_ellipsis = false;
};
template<class Ret, class... Args>
struct __functionof<Ret(Args..., ...)> {
	using Parent = void;
	using Return = Ret;
	using ArgsList = TypeList<Args...>;
	using Pointer = Ret(*)(Args...);
	static constexpr bool is_method = false;
	static constexpr bool is_static = true;
	static constexpr bool is_ellipsis = true;
};
template<class OtherType>
using functionof = __functionof<to_proto<OtherType>>;
#pragma endregion

#pragma region Static Compatible
template<class AnyCallable, class Ret, class... Args>
concept StaticCompatible =
	requires(AnyCallable f, Args... args) {
		{ f(args...) } -> std::convertible_to<Ret>;
	};
template<class AnyCallable, class FuncType>
constexpr bool static_compatible = false;
template<class AnyCallable, class Ret, class... Args>
constexpr bool static_compatible<AnyCallable, Ret(Args...)> = StaticCompatible<AnyCallable, Ret, Args...>;
#pragma endregion

#pragma region Constructor test
/* ConstructorOf */
template<class AnyType, class... Args>
struct ConstructorOf {
	static constexpr bool as_new = requires(Args... args) {
		new AnyType(args...);
	};
	static constexpr bool as_placement = requires(Args... args) {
		new(std::declval<void *>()) AnyType(args...);
	};
	static constexpr bool as_static = requires(Args... args) {
		AnyType(args...);
	};
	static constexpr bool any_ways = as_new || as_placement || as_static;
};
template<class AnyType>
struct ConstructorOf<AnyType, void> : ConstructorOf<AnyType> {};
/* ConstructorsOf */
template<class AnyType, class... ArgsLists>
struct ConstructorsOf;
template<class AnyType>
struct ConstructorsOf<AnyType> : ConstructorOf<AnyType> {};
template<class AnyType, class OtherType>
struct ConstructorsOf<AnyType, OtherType> : ConstructorOf<AnyType, OtherType> {};
template<class AnyType, template<class...> class AnyList, class... Args>
struct ConstructorsOf<AnyType, AnyList<Args...>> {};
template<class AnyType, class OtherType, class... Others>
struct ConstructorsOf<AnyType, OtherType, Others...> : ConstructorsOf<AnyType, TypeList<OtherType>, Others...> {};
template<class AnyType, template<class...> class AnyList, class... Args, class... Others>
struct ConstructorsOf<AnyType, AnyList<Args...>, Others...> {
	static constexpr bool as_new = ConstructorOf<AnyType, Args...>::as_new && ConstructorsOf<AnyType, Others...>::as_new;
	static constexpr bool as_placement = ConstructorOf<AnyType, Args...>::as_placement && ConstructorsOf<AnyType, Others...>::as_placement;
	static constexpr bool as_static = ConstructorOf<AnyType, Args...>::as_static && ConstructorsOf<AnyType, Others...>::as_static;
	static constexpr bool any_ways = ConstructorOf<AnyType, Args...>::any_ways && ConstructorsOf<AnyType, Others...>::any_ways;
};
/* ConstructorAsserts */
template<class AnyType, class... Args>
concept ConstructorNewAssert = ConstructorOf<AnyType, Args...>::as_new;
template<class AnyType, class... Args>
concept ConstructorPlacementAssert = ConstructorOf<AnyType, Args...>::as_placement;
template<class AnyType, class... Args>
concept ConstructorStaticAssert = ConstructorOf<AnyType, Args...>::as_static;
template<class AnyType, class... Args>
concept ConstructorAssert = ConstructorOf<AnyType, Args...>::any_ways;
/* ConstructorsAsserts */
template<class AnyType, class... Args>
concept ConstructorsNewAssert = ConstructorsOf<AnyType, Args...>::as_new;
template<class AnyType, class... Args>
concept ConstructorsPlacementAssert = ConstructorsOf<AnyType, Args...>::as_placement;
template<class AnyType, class... Args>
concept ConstructorsStaticAssert = ConstructorsOf<AnyType, Args...>::as_static;
template<class AnyType, class... Args>
concept ConstructorsAssert = ConstructorsOf<AnyType, Args...>::any_ways;
#pragma endregion

#pragma region Chain Extender 
template<class ParentClass, class ChildClass>
using Chain = std::conditional_t<std::is_void_v<ChildClass>, ParentClass, ChildClass>;
template<class ParentClass, class ChildClass>
concept IsChainExtended =
	(!std::is_void_v<ChildClass> && std::is_base_of_v<ParentClass, ChildClass>) ||
	  std::is_void_v<ChildClass>;
template<class ParentClass, class ChildClass>
struct ChainExtender {
	using Child = Chain<ParentClass, ChildClass>;
	using Self = ParentClass;
	ChainExtender() requires(IsChainExtended<ParentClass, ChildClass>) = default;
	Child &child_() reflect_as(*static_cast<Child *>(this));
	const Child &child_() const reflect_as(*static_cast<const Child *>(this));
	Self &self_() reflect_as(*static_cast<Self *>(this));
	const Self &self_() const reflect_as(*static_cast<const Self *>(this));
};
#define static
subtype_branch(super);
#undef static
template<class Class1, class Class2>
constexpr bool is_chain_extended_on =
std::is_void_v<Class1> || std::is_void_v<Class2> ? false :
	std::is_same_v<Class1, Class2> ? true :
	is_chain_extended_on<subtype_branchof_super<Class1, void>, Class2>;
#pragma endregion

#pragma region Class Reference
template<class AnyRef>
union RefAs {
private:
	AnyRef t;
public:
	template<class AnyType>
	RefAs(AnyType &arg) : t(arg) {}
	template<class AnyType>
	RefAs(AnyType &&arg) : t(std::forward<AnyType>(arg)) {}
	template<class AnyType>
	RefAs(const AnyType &arg) : t(arg) {}
	~RefAs() {}
public:
	template<class AnyType>
	inline operator AnyType() reflect_as((AnyType)t);
	template<class AnyType>
	inline operator AnyType() const reflect_as((AnyType)t);
	inline operator AnyRef &() reflect_as(t);
	inline operator const AnyRef &() const reflect_as(t);
	inline operator AnyRef *() reflect_as(std::addressof(t));
	inline operator const AnyRef *() const reflect_as(std::addressof(t));
	inline auto &operator*() reflect_as(t);
	inline auto &operator*() const reflect_as(t);
	inline auto operator&() reflect_as(std::addressof(t));
	inline auto operator&() const reflect_as(std::addressof(t));
	inline auto operator->() reflect_as(std::addressof(t));
	inline auto operator->() const reflect_as(std::addressof(t));
};
template<class AnyType>
union RefAs<AnyType *> {
private:
	AnyType *ptr;
public:
	template<class OtherType>
	RefAs(OtherType *ptr) : ptr((AnyType *)ptr) {}
public:
	inline operator AnyType *() reflect_as(ptr);
	inline operator const AnyType *() const reflect_as(ptr);
	inline auto &operator*() reflect_as(*ptr);
	inline auto &operator*() const reflect_as(*ptr);
	inline auto *operator&() reflect_as(&ptr);
	inline auto *operator&() const reflect_as(&ptr);
	inline auto *operator->() reflect_as(ptr);
	inline auto *operator->() const reflect_as(ptr);
};
template <class AnyStruct>
class RefStruct : protected AnyStruct {
public:
	RefStruct() : AnyStruct({ 0 }) {}
	RefStruct(const AnyStruct &s) : AnyStruct(s) {}
public:
	inline operator AnyStruct &() reflect_to_self();
	inline operator const AnyStruct &() const reflect_to_self();
	inline AnyStruct &operator*() reflect_to_self();
	inline const AnyStruct &operator *() const reflect_to_self();
	inline AnyStruct *operator&() reflect_as(this);
	inline const AnyStruct *operator&() const reflect_as(this);
	inline AnyStruct *operator->() reflect_as(this);
	inline const AnyStruct *operator->() const reflect_as(this);
};
template <class OtherType>
constexpr bool IsRef = false;
template<class RefType>
constexpr bool IsRef<RefAs<RefType>> = true;
#pragma endregion

#pragma region Exception
class Exception {
	const char
		*lpFile = O,
		*lpFunc = O,
		*lpSent = O;
	uint32_t
		uLine = 0,
		uErrCode = 0;
public:
	Exception() {}
	Exception(const char *lpszFile, const char *lpszFunc, const char *lpszSent,
			  uint32_t nLine, uint32_t uErrCode = 0) :
		lpFile(lpszFile), lpFunc(lpszFunc), lpSent(lpszSent),
		uLine(nLine), uErrCode(uErrCode) {}
public:
	inline auto File() const reflect_as(lpFile);
	inline auto Function() const reflect_as(lpFunc);
	inline auto Sentence() const reflect_as(lpSent);
	inline auto Line() const reflect_as(uLine);
	inline auto ErrorCode() const reflect_as(uErrCode);
public:
	inline operator bool() const reflect_as(lpSent);
};
#pragma endregion

#pragma region FunctionBase
template<class RetType, class... Args>
struct FunctionBase {
	virtual ~FunctionBase() = default;
	virtual RetType operator()(Args ...) = 0;
};
template<class PackType, class RetType, class... Args>
class FunctionPackage :
	public FunctionBase<RetType, Args...> {
	mutable PackType func;
public:
	FunctionPackage(PackType &f) : func(f) {}
	RetType operator()(Args ...args) override {
		static_assert(static_compatible<PackType, RetType(Args...)>, "Argument list uncompatible");
		if_c (std::is_pointer_v<PackType>)
			 return func(args...);
		else return func(args...);
	}
};
#pragma region Function
template<class...>
class Function;
template<class RetType, class... Args>
class Function<RetType(Args...)> final {
private:
	mutable FunctionBase<RetType, Args...> *func = O;
	mutable bool bAllocated = false;
public:
	Function() {}
	Function(Null) {}
	Function(const Function &f) : func(f.func) {}
public:
	template<class Type>
	Function(Type &f) : func(new FunctionPackage<Type, RetType, Args...>(f)), bAllocated(true) {}
	template<class Type>
	Function(Type f) : func(new FunctionPackage<Type, RetType, Args...>(f)), bAllocated(true) {}
	~Function() { if (func && bAllocated) delete func, func = O; }
public:
	inline operator bool() const reflect_as(!func);
	inline bool operator!=(Null) const reflect_as(func);
	inline bool operator==(Null) const reflect_as(!func);
	inline Function operator&() reflect_to_self();
	inline const Function operator&() const reflect_to_self();
	inline RetType operator()(Args...args) const reflect_as(func(args...));
	inline auto &operator=(const Function &f) const noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(const Function &f) noexcept reflect_to_self(func = f.func, bAllocated = false);
	inline auto &operator=(Function &&f) noexcept reflect_to_self(func = f.func, f.func = O, bAllocated = true);
};
template<class...FuncTypes>
using fn = Function<FuncTypes...>;
#pragma endregion
#pragma endregion

#pragma region FormatNumeral
enum class Symbol : uint8_t { Def = 0, Neg, Pos, Space };
enum class Cap : uint8_t { Small = 0, Big };
enum class Align : uint8_t { Space = 0, Zero };
enum class Rad : uint8_t { Dec = 0, Qua, Oct, Hex };
struct fmt_word {
	bool int_align : 1;
	Align int_blank : 1;
	bool int_trunc : 1;
	uint8_t int_calign : 5;

	bool float_align : 1;
	Align float_blank : 1;
	bool float_force : 1;
	uint8_t float_calign : 5;

	Symbol symbol : 2;
	Cap alfa_type : 1;
	bool right_dir : 1;
	Rad radix_type : 2;

	fmt_word() = default;
	fmt_word(const fmt_word &) = default;
	template<class CharType>
	fmt_word(const CharType *format) {
		auto ch = *format;
		if (ch == ' ') {
			right_dir = true;
			symbol = Symbol::Space;
			ch = *++format;
		}
		elif (ch == '*') {
			symbol = Symbol::Space;
			ch = *++format;
		}
		switch (ch) {
			case '+':
				symbol = Symbol::Pos;
				ch = *++format;
				break;
		}
		switch (ch) {
			case '0':
				int_blank = Align::Zero;
				int_align = true;
				ch = *++format;
				break;
			case ' ':
				int_blank = Align::Space;
				int_align = true;
				ch = *++format;
				break;
		}
		if (ch == '~') {
			int_trunc = true;
			ch = *++format;
		}
		auto align = 0;
		while ('0' <= ch && ch <= '9') {
			align *= 10;
			align += ch - '0';
			if (align > 32)
				return; // overflow
			ch = *++format;
		}
		int_calign = align;
		if (ch == '.') {
			float_force = true;
			ch = *++format;
		}
		elif (ch == '0') {
			float_blank = Align::Zero;
			float_align = true;
			ch = *++format;
		}
		align = 0;
		while ('0' <= ch && ch <= '9') {
			align *= 10;
			align += ch - '0';
			if (align > 32)
				return; // overflow
			ch = *++format;
		}
		float_calign = align;
		if (ch == ' ') {
			float_blank = Align::Space;
			float_align = true;
			ch = *++format;
		}
		switch (ch) {
			case 'q':
				radix_type = Rad::Qua;
				ch = *++format;
				break;
			case 'o':
				radix_type = Rad::Oct;
				ch = *++format;
				break;
			case 'd':
				radix_type = Rad::Dec;
				ch = *++format;
				break;
			case 'X':
				alfa_type = Cap::Big;
				[[fallthrough]];
			case 'x':
				radix_type = Rad::Hex;
				ch = *++format;
				break;
			default:
				return; // Unknown
		}
		return;
	}
};
class format_numeral : public fmt_word {
public:
	format_numeral() {}
	format_numeral(fmt_word fmt) : fmt_word(fmt) {}
	format_numeral(const char *lpFormat) : fmt_word(lpFormat) {}
	format_numeral(const wchar_t *lpFormat) : fmt_word(lpFormat) {}
private:
	template<class TCHAR>
	static inline auto __push(uintptr_t ui, TCHAR *hpString, TCHAR alfa, uint8_t radix, uint8_t int_trunc) {
		uint8_t len = 0;
		do {
			auto d_sm = ui / radix;
			auto rbit = (TCHAR)(ui - d_sm * radix);
			ui = d_sm;
			*--hpString = rbit + (rbit < 10 ? '0' : alfa);
		} while (ui && ++len < int_trunc);
		return hpString;
	}
	template<class TCHAR>
	static inline auto __push(double pure_float, TCHAR *lpString, TCHAR alfa, uint8_t radix, uint8_t float_trunc) {
		uint8_t len = 0;
		while (pure_float > 0.f && len++ < float_trunc) {
			pure_float *= radix;
			auto rbit = (TCHAR)pure_float;
			pure_float -= rbit;
			*lpString++ = rbit + (rbit < 10 ? '0' : alfa);
		}
		return lpString;
	}
	template<class TCHAR>
	static inline auto __moveH2L(TCHAR *lpString, TCHAR *hpString, int uLength) {
		while (uLength--)
			*lpString++ = *hpString++;
		return lpString;
	}
private:
	inline uint8_t _radix() const reflect_as((uint8_t)radix_type == (uint8_t)Rad::Dec ? 10 : (2 << (uint8_t)radix_type));
	template<class TCHAR>
	inline TCHAR _alfa_char() const reflect_as(((uint8_t)alfa_type == (uint8_t)Cap::Big ? 'A' : 'a') - 10);
	template<class TCHAR>
	inline TCHAR _fill_int_char() const reflect_as((uint8_t)int_blank == (uint8_t)Align::Space ? ' ' : '0');
	template<class TCHAR>
	inline TCHAR _fill_float_char() const reflect_as((uint8_t)float_blank == (uint8_t)Align::Space ? ' ' : '0');
	template<class TCHAR>
	inline auto _push(uintptr_t uint_part, TCHAR *hpBuffer, uint8_t radix, TCHAR alfa, bool neg) const {
		auto lpBuffer = __push(uint_part, hpBuffer, alfa, radix, int_trunc ? int_calign : 32);
		auto int_len = hpBuffer - lpBuffer;
		if (int_len < int_calign && int_align) {
			auto fill = _fill_int_char<TCHAR>();
			while (int_len++ < int_calign)
				*--lpBuffer = fill;
		}
		if (neg)
			*--lpBuffer = '-';
		elif ((uint8_t)symbol == (uint8_t)Symbol::Pos)
			*--lpBuffer = '+';
		elif ((uint8_t)symbol == (uint8_t)Symbol::Space)
			*--lpBuffer = ' ';
		if (right_dir)
			while (int_len++ < int_calign)
				*--lpBuffer = ' ';
		return lpBuffer;
	}
	template<class TCHAR>
	inline auto _push(double float_part, TCHAR *lpBuffer, uint8_t radix, TCHAR alfa) const {
		auto hpBuffer = __push(
			float_part, lpBuffer + 1,
			alfa, radix, float_calign);
		auto float_len = hpBuffer - lpBuffer - 1;
		if (float_align) {
			auto fill = _fill_float_char<TCHAR>();
			while (float_len++ < int_calign)
				*hpBuffer++ = fill;
		}
		if (float_len > 0)
			*lpBuffer = '.';
		elif (float_force)
			*lpBuffer = '.';
		elif (float_align)
			*lpBuffer = ' ';
		else --hpBuffer;
		return hpBuffer;
	}
public:
	template<class TCHAR>
	inline auto push(uintptr_t uint_part, TCHAR *lpBuffer, TCHAR *&hpBuffer, size_t maxLength) const {
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push(uint_part, hpBuffer, _radix(), _alfa_char<TCHAR>(), false);
		return lpBuffer;
	}
	template<class TCHAR>
	inline auto push(intptr_t int_part, TCHAR *lpBuffer, TCHAR *&hpBuffer, size_t maxLength) const {
		bool neg = int_part < 0;
		if (neg) int_part = -int_part;
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push((uintptr_t)int_part, hpBuffer, _radix(), _alfa_char<TCHAR>(), neg);
		return lpBuffer;
	}
	template<class TCHAR>
	inline auto push(double float_part, TCHAR *lpBuffer, TCHAR *&hpBuffer, size_t maxLength) const {
		auto rad = _radix();
		auto alfa = _alfa_char<TCHAR>();
		bool neg = float_part < 0.;
		if (neg) float_part = -float_part;
		auto uint_part = (uintptr_t)float_part;
		hpBuffer = lpBuffer + maxLength - 2;
		lpBuffer = _push(uint_part, hpBuffer, rad, alfa, neg);
		auto lpBufferNew = lpBuffer - float_calign;
		hpBuffer = __moveH2L(lpBufferNew, lpBuffer, (int)(hpBuffer - lpBuffer));
		lpBuffer = lpBufferNew;
		hpBuffer = _push(float_part - uint_part, hpBuffer, rad, alfa);
		return lpBuffer;
	}
public:
	static constexpr size_t MaxLen = 64;
	template<class TCHAR = ::TCHAR, class AnyType>
	inline size_t push(AnyType i, TCHAR *pBuffer) const {
		TCHAR lpBuffer[MaxLen] = { 0 }, *hpString, *lpString;
		if_c (std::is_unsigned_v<AnyType>)
			lpString = push((uintptr_t)i, lpBuffer, hpString, MaxLen);
		elif_c (std::is_integral_v<AnyType>)
			lpString = push((intptr_t)i, lpBuffer, hpString, MaxLen);
		elif_c (std::is_floating_point_v<AnyType>)
			lpString = push(i, lpBuffer, hpString, MaxLen);
		auto size = (size_t)(hpString - lpString);
		if (pBuffer)
			CopyMemory(pBuffer, lpString, size * sizeof(TCHAR));
		return size;
	}
};
const auto DEC = format_numeral("d");
const auto FPT = format_numeral(".5d");
inline format_numeral operator ""_nx(const char *format, size_t n) reflect_as(format);
inline format_numeral operator ""_nx(const wchar_t *format, size_t n) reflect_as(format);
#pragma endregion

#pragma region Enum
/* (misc) */
template<class AnyType>
concept IsEnum = requires { typename AnyType::EnumType; };
template<class Class1, class Class2>
constexpr bool is_chain_enum_on =
std::is_void_v<Class1> || std::is_void_v<Class2> ? false :
	std::is_same_v<Class1, Class2> ? true :
	is_chain_enum_on<subtype_branchof_ProtoEnum<Class1, void>, Class2>;
template<IsEnum Enum1, IsEnum Enum2, class EnumType>
inline auto __makeResult(EnumType val) {
	constexpr auto left = is_chain_enum_on<Enum1, Enum2>;
	constexpr auto right = is_chain_enum_on<Enum2, Enum1>;
	static_assert(left || right, "Convertless");
	if_c (left)
		return reuse_as<Enum1>((typename Enum1::ProtoType)val);
	else
		return reuse_as<Enum2>((typename Enum2::ProtoType)val);
}
template<class AnyType>
struct EnumUnitBase {
	using ProtoType = AnyType;
	using ProtoUnit = EnumUnitBase;
	ProtoType val;
	constexpr EnumUnitBase(ProtoType val) : val(val) {}
	static constexpr size_t CountAll = 0;
};
template<class AnyType>
using EnumUnit = std::conditional_t<IsEnum<AnyType>, AnyType, EnumUnitBase<AnyType>>;
template<class SubClass, class BaseType>
struct EnumBase {
	static constexpr bool HasProtoEnum = IsEnum<BaseType>;
	using ProtoEnum = std::conditional_t<HasProtoEnum, BaseType, void>;
	using ProtoUnit = typename EnumUnit<BaseType>::ProtoUnit;
	using ProtoType = typename ProtoUnit::ProtoType;
	static constexpr size_t CountAll() reflect_as(HasProtoEnum ? SubClass::Count + ProtoEnum::CountAll() : SubClass::Count); \
};
#pragma endregion

}
