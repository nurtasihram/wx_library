module;

#include "wx_types"
#include <aclapi.h>
#include <sddl.h>

export module wx.security;

namespace WX {

#pragma region Security Identifiers
using RID = DWORD;

class SecurityIdentifiersAuthority {
	mutable SID_IDENTIFIER_AUTHORITY sia{ 0 };
	[[maybe_unused]] WORD ___ = 0;
public:
	SecurityIdentifiersAuthority() { static_assert(sizeof(self) == 8, "alignment error"); }
	SecurityIdentifiersAuthority(const arrayof<BYTE, 6> &sia) : sia(ref_as<const SID_IDENTIFIER_AUTHORITY>(sia)) {}
	constexpr SecurityIdentifiersAuthority(BYTE s0, BYTE s1, BYTE s2, BYTE s3, BYTE s4, BYTE s5) : sia({ s0, s1, s2, s3, s4, s5 }) {}
	SecurityIdentifiersAuthority(const SID_IDENTIFIER_AUTHORITY &sia) : sia(sia) {}
	inline bool operator==(const SecurityIdentifiersAuthority &s) const reflect_as(reuse_as<uint64_t>(self) == reuse_as<uint64_t>(s));
	inline bool operator!=(const SecurityIdentifiersAuthority &s) const reflect_as(reuse_as<uint64_t>(self) != reuse_as<uint64_t>(s));
	inline operator String() const
		reflect_as(format(T("S-1-%d-%d-%d-%d-%d-%d-%d"), sia.Value[0], sia.Value[1], sia.Value[2], sia.Value[3], sia.Value[4], sia.Value[5]));
	inline operator SID_IDENTIFIER_AUTHORITY &() const reflect_as(sia);
	inline PSID_IDENTIFIER_AUTHORITY operator &() const reflect_as(&sia);
};
using SecAuthorID = SecurityIdentifiersAuthority;

struct SecurityIdentifiersAuthorities {
	static constexpr SecAuthorID
		Null    = SECURITY_NULL_SID_AUTHORITY,
		World   = SECURITY_WORLD_SID_AUTHORITY,
		Local   = SECURITY_LOCAL_SID_AUTHORITY,
		Creator = SECURITY_CREATOR_SID_AUTHORITY,
		NT      = SECURITY_NT_AUTHORITY;
};
using SecAuthorIDs = SecurityIdentifiersAuthorities;
class SecurityIdentifier {
	friend class SecurityDescriptor;
	mutable PSID pSID = O;
	SecurityIdentifier(PSID pSID) : pSID(pSID) {}
public:
	SecurityIdentifier() {}
	SecurityIdentifier(Null) {}
	SecurityIdentifier(SecurityIdentifier &sid) : pSID(&sid) reflect_to(sid.pSID = O);
	SecurityIdentifier(SecurityIdentifier &&sid) : pSID(&sid) reflect_to(sid.pSID = O);
	SecurityIdentifier(const SecurityIdentifier &) = delete;
	SecurityIdentifier(LPCTSTR lpszSID) assertl(ConvertStringSidToSid(lpszSID, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0)
		assertl(AllocateAndInitializeSid(&sia, 1, nSA0, 0, 0, 0, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1)
		assertl(AllocateAndInitializeSid(&sia, 2, nSA0, nSA1, 0, 0, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2)
		assertl(AllocateAndInitializeSid(&sia, 3, nSA0, nSA1, nSA2, 0, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3)
		assertl(AllocateAndInitializeSid(&sia, 4, nSA0, nSA1, nSA2, nSA3, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4)
		assertl(AllocateAndInitializeSid(&sia, 5, nSA0, nSA1, nSA2, nSA3, nSA4, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4, RID nSA5)
		assertl(AllocateAndInitializeSid(&sia, 6, nSA0, nSA1, nSA2, nSA3, nSA4, nSA5, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4, RID nSA5, RID nSA6)
		assertl(AllocateAndInitializeSid(&sia, 7, nSA0, nSA1, nSA2, nSA3, nSA4, nSA5, nSA6, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4, RID nSA5, RID nSA6, RID nSA7)
		assertl(AllocateAndInitializeSid(&sia, 8, nSA0, nSA1, nSA2, nSA3, nSA4, nSA5, nSA6, nSA7, &pSID));
	//SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, BYTE nSubAuthorityCount = 0) {
	//	assertl(pSID = (PSID)LocalAlloc(0, GetSidLengthRequired(nSubAuthorityCount)));
	//	assertl(InitializeSid(pSID, &sia, nSubAuthorityCount));
	//}
	~SecurityIdentifier() reflect_to(Delete());
public:
	inline bool Delete() {
		if (pSID)
			if (!LocalFree(pSID))
				return false;
		pSID = O;
		return true;
	}
public:
	inline bool EqualDomain(PSID pSID) assertl_reflect_to(BOOL eq, EqualDomainSid(this->pSID, pSID, &eq), eq);
	inline bool EqualPrefix(PSID pSID) reflect_as(EqualPrefixSid(this->pSID, pSID));
public: // Property - Size
	/* R */ inline DWORD Size() const assertl_reflect_as(auto size = GetLengthSid(this->pSID), size);
public: // Property - AuthorityID
	/* R */ SecAuthorID AuthorityID() const assertl_reflect_as(auto id = GetSidIdentifierAuthority(this->pSID), *id);
public: // Property - AuthorityCount
	/* S */ UCHAR &SubAuthorityCount() assertl_reflect_as(auto pCount = GetSidSubAuthorityCount(this->pSID), *pCount);
	/* R */ UCHAR  SubAuthorityCount() const assertl_reflect_as(auto pCount = GetSidSubAuthorityCount(this->pSID), *pCount);
public: // 
	//GetWindowsAccountDomainSid
	//IsWellKnownSid
	inline operator bool() const reflect_as(this->pSID ? IsValidSid(this->pSID) : false);
	inline operator StringA() const assertl_reflect_to(AutoPointer<_M_(Local, CHAR)> szSID(LocalHeap), ConvertSidToStringSidA(this->pSID, &(*szSID)), +CString(&szSID, MaxLenClass));
	inline operator StringW() const assertl_reflect_to(AutoPointer<_M_(Local, WCHAR)> szSID(LocalHeap), ConvertSidToStringSidW(this->pSID, &(*szSID)), +CString(&szSID, MaxLenClass));
	inline PSID operator&() const reflect_as(this->pSID);
	inline SecurityIdentifier operator+() const {
		if (!*this) return O;
		auto size = Size();
		auto npSID = Local::Alloc(size);
		assertl(CopySid(size, npSID, pSID));
		return npSID;
	}
	inline RID &operator[](BYTE uSubAuthorityIndex) assertl_reflect_as(auto dwAuthority = GetSidSubAuthority(this->pSID, uSubAuthorityIndex), *dwAuthority);
	inline RID  operator[](BYTE uSubAuthorityIndex) const assertl_reflect_as(auto dwAuthority = GetSidSubAuthority(this->pSID, uSubAuthorityIndex), *dwAuthority);
	inline bool operator==(PSID pSID) const reflect_as(EqualSid(this->pSID, pSID));
	inline bool operator!=(PSID pSID) const reflect_as(EqualSid(this->pSID, pSID));
};
using SecID = SecurityIdentifier;
#pragma endregion

#pragma region Access Control
enum_flags(AccessPermission, DWORD,
	QueryValue          = KEY_QUERY_VALUE,
	Value               = KEY_SET_VALUE,
	CreateSubKey        = KEY_CREATE_SUB_KEY,
	EnumerateSubKeys    = KEY_ENUMERATE_SUB_KEYS,
	Notify              = KEY_NOTIFY,
	CreateLink          = KEY_CREATE_LINK,
	Wow64Key32          = KEY_WOW64_32KEY,
	Wow64Key64          = KEY_WOW64_64KEY,
	Wow64Res            = KEY_WOW64_RES,
	Read       = KEY_READ,
	Write      = KEY_WRITE,
	Execute    = KEY_EXECUTE,
	AllAccess  = KEY_ALL_ACCESS);
enum_class(TrustForms, TRUSTEE_FORM,
	SID            = TRUSTEE_IS_SID,
	Name           = TRUSTEE_IS_NAME,
	BadForm        = TRUSTEE_BAD_FORM,
	ObjectsAndSID  = TRUSTEE_IS_OBJECTS_AND_SID,
	ObjectsAndName = TRUSTEE_IS_OBJECTS_AND_NAME);
enum_class(TrustTypes, TRUSTEE_TYPE,
	Unknown        = TRUSTEE_IS_UNKNOWN,
	User           = TRUSTEE_IS_USER,
	Group          = TRUSTEE_IS_GROUP,
	Domain         = TRUSTEE_IS_DOMAIN,
	Alias          = TRUSTEE_IS_ALIAS,
	WellKnownGroup = TRUSTEE_IS_WELL_KNOWN_GROUP,
	Deleted        = TRUSTEE_IS_DELETED,
	Invalid        = TRUSTEE_IS_INVALID,
	Computer       = TRUSTEE_IS_COMPUTER);
enum_flags(AccessInherit, DWORD,
	No          = NO_INHERITANCE,
	Objects     = SUB_OBJECTS_ONLY_INHERIT,
	Containers  = SUB_CONTAINERS_ONLY_INHERIT,
	NoPropagate = INHERIT_NO_PROPAGATE,
	Only        = INHERIT_ONLY);
enum_class(AccessModes, ACCESS_MODE,
	NoUsed          = NOT_USED_ACCESS,
	Grant           = GRANT_ACCESS,
	Set             = SET_ACCESS,
	Deny            = DENY_ACCESS,
	Revoke          = REVOKE_ACCESS,
	SetAuditSuccess = SET_AUDIT_SUCCESS,
	SetAuditFailure = SET_AUDIT_FAILURE);
class AccessExplicit : protected EXPLICIT_ACCESS {
	using super = EXPLICIT_ACCESS;
public:
	using Permission = AccessPermission;
	using Inherit = AccessInherit;
	using Modes = AccessModes;

	AccessExplicit(Modes mode = Modes::Set) : super{ 0 } reflect_to(this->grfAccessMode = mode.yield());
	AccessExplicit(const EXPLICIT_ACCESS &ea) : super(ea) {}

public: // Permissions
	/* W */ inline auto &Permissions(Permission permission) reflect_to_self(this->grfAccessPermissions = permission.yield());
public: // Inherit
	/* W */ inline auto &Inherits(Inherit inherits) reflect_to_self(this->grfInheritance = inherits.yield());
public: // Trust
	/* W */ inline auto &Trust(const SecID &sid) reflect_to_self(this->Trustee.TrusteeForm = TRUSTEE_IS_SID, this->Trustee.ptstrName = (LPTSTR)&sid);
public: // TrustBy
	/* W */ inline auto &TrustBy(TrustTypes type) reflect_to_self(this->Trustee.TrusteeType = type.yield());
};

#pragma region Access Control Entry
enum_class(AccessControlEntryTypes, BYTE,
	AccessAllowed                   = ACCESS_ALLOWED_ACE_TYPE,
	AccessDenied                    = ACCESS_DENIED_ACE_TYPE,
	SystemAudit                     = SYSTEM_AUDIT_ACE_TYPE,
	SystemAlarm                     = SYSTEM_ALARM_ACE_TYPE,
	AccessAllowedCompound           = ACCESS_ALLOWED_COMPOUND_ACE_TYPE,
	AccessAllowedObject             = ACCESS_ALLOWED_OBJECT_ACE_TYPE,
	AccessDeniedObject              = ACCESS_DENIED_OBJECT_ACE_TYPE,
	SystemAuditObject               = SYSTEM_AUDIT_OBJECT_ACE_TYPE,
	SystemAlarmObject               = SYSTEM_ALARM_OBJECT_ACE_TYPE,
	AccessAllowedCallback           = ACCESS_ALLOWED_CALLBACK_ACE_TYPE,
	AccessDeniedCallback            = ACCESS_DENIED_CALLBACK_ACE_TYPE,
	AccessAllowedCallbackObject     = ACCESS_ALLOWED_CALLBACK_OBJECT_ACE_TYPE,
	AccessDeniedCallbackObject      = ACCESS_DENIED_CALLBACK_OBJECT_ACE_TYPE,
	SystemAuditCallback             = SYSTEM_AUDIT_CALLBACK_ACE_TYPE,
	SystemAlarmCallback             = SYSTEM_ALARM_CALLBACK_ACE_TYPE,
	SystemAuditCallbackObject       = SYSTEM_AUDIT_CALLBACK_OBJECT_ACE_TYPE,
	SystemAlarmCallbackObject       = SYSTEM_ALARM_CALLBACK_OBJECT_ACE_TYPE,
	SystemMandatoryLabel            = SYSTEM_MANDATORY_LABEL_ACE_TYPE,
	SystemResourceAttribute         = SYSTEM_RESOURCE_ATTRIBUTE_ACE_TYPE,
	SystemScopedPolicyId            = SYSTEM_SCOPED_POLICY_ID_ACE_TYPE,
	SystemProcessTrustLabel         = SYSTEM_PROCESS_TRUST_LABEL_ACE_TYPE,
	SystemAccessFilter              = SYSTEM_ACCESS_FILTER_ACE_TYPE);
using AceTypes = AccessControlEntryTypes;
enum_class(AccessControlEntryFlag, BYTE,
// Inherit
	ObjectInherit                   = OBJECT_INHERIT_ACE,
	ContainerInherit                = CONTAINER_INHERIT_ACE,
	NoPropagateInherit              = NO_PROPAGATE_INHERIT_ACE,
	InheritOnlyAce                  = INHERIT_ONLY_ACE,
// Resd
	InheritedAce                    = INHERITED_ACE,
	Critical                        = CRITICAL_ACE_FLAG,
	SuccessfulAccess                = SUCCESSFUL_ACCESS_ACE_FLAG,
	FailedAccess                    = FAILED_ACCESS_ACE_FLAG,
	TrustProtectedFilter            = TRUST_PROTECTED_FILTER_ACE_FLAG);
using AceFlag = AccessControlEntryFlag;
class AccessControlEntry {
	PACCESS_ALLOWED_ACE pACE = O;
public:
	using Types = AceTypes;
	using Flag = AceFlag;
	struct AccessMask {
	public:
		WORD SpecificRights;
		BYTE StandardRights;
		BYTE AccessSystemAcl : 1;
	private:
		[[maybe_unused]] BYTE Reserved : 3;
	public:
		BYTE GenericAll : 1;
		BYTE GenericExecute : 1;
		BYTE GenericWrite : 1;
		BYTE GenericRead : 1;
	};

//	AccessControlEntry(const SecID &sid) : pACE(Local) {}
	AccessControlEntry(Null) {}

#pragma region Properties
public: // Property - Type
	/* W */ inline auto &Type(Types AceType) reflect_to_self(ref_as<Types>(pACE->Header.AceType = AceType.yield()));
	/* R */ inline Types Type() const reflect_as(ref_as<Types>(pACE->Header.AceType));
public: // Property - Flags
	/* W */ inline auto &Flags(Flag AceFlags) reflect_to_self(ref_as<Flag>(pACE->Header.AceFlags = AceFlags.yield()));
	/* R */ inline Flag  Flags() const reflect_as(ref_as<Flag>(pACE->Header.AceFlags));
public: // Property - Size
	/* R */ inline WORD Size() const reflect_as(pACE->Header.AceSize);
public: // Property - Access
	/* W */ inline auto &Access(AccessMask Mask) reflect_to_self(pACE->Mask = ref_as<ACCESS_MASK>(Mask));
	/* R */ inline const AccessMask Access() reflect_as(ref_as<AccessMask>(pACE->Mask));
public: // Property - SecurityIdentifier
	///* W */ inline auto &SecurityIdentifier(const SecID &sid) {
	//	auto size = sid.Size();
	//	CopyMemory(&pACE->SidStart, &sid, size);
	//	retself;
	//}
	/* R */ inline const SecID &SecurityIdentifier() const reflect_as(*reuse_as<const SecID *>(&pACE->SidStart));
#pragma endregion

	inline PACCESS_ALLOWED_ACE operator&() reflect_as(pACE);
};
using Ace = AccessControlEntry;
#pragma endregion

#pragma region Access Control Entry
class AccessControlList {
	friend class SecurityDescriptor;
	mutable PACL pACL = O;
public:
	using Entry = Ace;
	class Iterator {
		friend class AccessControlList;
		AccessControlList &acl;
		mutable DWORD dwAceIndex;
		Iterator(const AccessControlList &acl, DWORD dwAceIndex) : acl(const_cast<AccessControlList &>(acl)), dwAceIndex(dwAceIndex) {}
	public:
		inline auto &Delete() assertl_reflect_as_self(DeleteAce(&acl, dwAceIndex));
		inline bool operator==(Null) const reflect_as(dwAceIndex >= acl.Count());
		inline bool operator!=(Null) const reflect_as(dwAceIndex <  acl.Count());
		inline bool operator==(const Iterator &i) const assertl_reflect_as(&acl == &i.acl, dwAceIndex == i.dwAceIndex);
		inline bool operator!=(const Iterator &i) const assertl_reflect_as(&acl == &i.acl, dwAceIndex != i.dwAceIndex);
		inline Entry *operator&() assertl_reflect_to(LPVOID lpACE, GetAce(&acl, dwAceIndex, &lpACE), ref_as<Entry *>(lpACE));
		inline const Entry *operator&() const assertl_reflect_to(LPVOID lpACE, GetAce(&acl, dwAceIndex, &lpACE), ref_as<const Entry *>(lpACE));
		inline Entry *operator->() assertl_reflect_to(LPVOID lpACE, GetAce(&acl, dwAceIndex, &lpACE), ref_as<Entry *>(lpACE));
		inline const Entry *operator->() const assertl_reflect_to(LPVOID lpACE, GetAce(&acl, dwAceIndex, &lpACE), ref_as<const Entry *>(lpACE));
		inline Entry & operator*() assertl_reflect_to(LPVOID lpACE, GetAce(&acl, dwAceIndex, &lpACE), *ref_as<Entry *>(lpACE));
		inline const Entry & operator*() const assertl_reflect_to(LPVOID lpACE, GetAce(&acl, dwAceIndex, &lpACE), *ref_as<const Entry *>(lpACE));
		inline Iterator &operator++() reflect_to_self(++dwAceIndex);
		inline const Iterator &operator++() const reflect_to_self(++dwAceIndex);
		inline Iterator operator++(int) reflect_as({ acl, dwAceIndex++ });
		inline const Iterator operator++(int) const reflect_as({ acl, dwAceIndex++ });
	};

	AccessControlList() {}
	AccessControlList(Null) {}
	AccessControlList(AccessControlList &acl) : pACL(&acl) reflect_to(acl.pACL = O);
	AccessControlList(AccessControlList &&acl) : pACL(&acl) reflect_to(acl.pACL = O);
	AccessControlList(const AccessControlList &) = delete;

	AccessControlList(std::initializer_list<AccessExplicit> list) assertl(SetEntriesInAcl((ULONG)list.size(), (EXPLICIT_ACCESS *)list.begin(), O, &pACL) == ERROR_SUCCESS);

#pragma region
	//inline void Add() { AddAce(pACL, ); }

	//inline void AddAllowed() { AddAccessAllowedAce(pACL, ) }
	//inline void AddAllowed() { AddAccessAllowedAceEx(pACL, ) }
	//inline void AddAllowed() { AddAccessAllowedObjectAce(pACL, ) }

	//inline void AddDenied() { AddAccessDeniedAce(pACL, ); }
	//inline void AddDenied() { AddAccessDeniedAceEx(pACL, ) }
	//inline void AddDenied() { AddAccessDeniedObjectAce(pACL, ) }

	//inline void AddAudit() { AddAccessAuditAce(pACL, ); }
	//inline void AddAudit() { AddAccessAuditAceEx(pACL, ) }
	//inline void AddAudit() { AddAccessAuditObjectAce(pACL, ) }

	//inline void AddMandatory() { }
	//inline void AddResourceAttribute() {}
	//inline void AddScopedPolicyID() { }
#pragma endregion

	//inline auto FindFirstFree() {
	//	FindFirstFreeAce(pACL, );
	//}

#pragma region Properties
public: // Property - Count
	/* R */ inline DWORD Count() const assertl_reflect_to(ACL_SIZE_INFORMATION asi, GetAclInformation(pACL, &asi, sizeof(asi), AclSizeInformation), asi.AceCount);
public: // Property - Usage
	struct _Usage {
		DWORD used, free;
		inline DWORD Total() const reflect_as(used + free);
	};
	/* R */ inline auto Usage() const assertl_reflect_to(ACL_SIZE_INFORMATION asi, GetAclInformation(pACL, &asi, sizeof(asi), AclSizeInformation), _Usage{ asi.AclBytesInUse, asi.AclBytesFree });
public: // Property - Size
	/* R */ inline DWORD Size() const reflect_as(Usage().Total());
public: // Property - Revision
	/* W */ inline auto &Revision(DWORD dwRevision) assertl_reflect_to_self(ACL_REVISION_INFORMATION ari = { dwRevision }, GetAclInformation(pACL, &ari, sizeof(ACL_REVISION_INFORMATION), AclRevisionInformation));
	/* R */ inline DWORD Revision() const assertl_reflect_to(ACL_REVISION_INFORMATION ari, GetAclInformation(pACL, &ari, sizeof(ACL_REVISION_INFORMATION), AclRevisionInformation), ari.AclRevision);
#pragma endregion

	inline Iterator operator[](DWORD dwAceIndex) reflect_as({ self, dwAceIndex });
	inline const Iterator operator[](DWORD dwAceIndex) const reflect_as({ self, dwAceIndex });
	
	inline Iterator begin() reflect_as({ self, 0 });
	inline const Iterator begin() const reflect_as({ self, 0 });
	inline Iterator end() reflect_as({ self, Count() });
	inline const Iterator end() const reflect_as({ self, Count() });

	inline PACL &operator&() const reflect_as(pACL);
	inline operator bool() const reflect_as(pACL ? IsValidAcl(pACL) : false);
};
using AceList = AccessControlList;
#pragma endregion

#pragma endregion

#pragma region Security Descriptor
class SecurityDescriptor {
	mutable PSECURITY_DESCRIPTOR pSD = O;
	template<bool _SACL_1_DACL_0_>
	class xACL {
		friend class SecurityDescriptor;
		SecurityDescriptor &sd;
		PACL pACL = O;
		bool bDefault = false, bPresent = false, bModified = false;
		xACL(const SecurityDescriptor &sd) : sd(const_cast<SecurityDescriptor &>(sd)) {
			BOOL bDefault = false, bPresent = false;
			if constexpr (_SACL_1_DACL_0_)
				 assertl(GetSecurityDescriptorSacl(&sd, &bPresent, &pACL, &bDefault))
			else assertl(GetSecurityDescriptorDacl(&sd, &bPresent, &pACL, &bDefault))
			this->bDefault = bDefault, this->bPresent = bPresent;
		}
		xACL(SecurityDescriptor &sd, PACL pACL) : sd(sd), pACL(pACL), bPresent(true), bModified(true) {}
		inline void __Set() {
			if (bModified) {
				if constexpr (_SACL_1_DACL_0_)
					 assertl(SetSecurityDescriptorSacl(&sd, bPresent, pACL, bDefault))
				else assertl(SetSecurityDescriptorDacl(&sd, bPresent, pACL, bDefault))
			}
		}
	public:
		xACL(xACL &) = delete;
		xACL(xACL &&) = delete;
		xACL(const xACL &) = delete;
		~xACL() reflect_to(__Set());
	public: // Property - Present
		/* W */ inline auto &Present(bool bPresent) reflect_to_self(bModified |= this->bPresent != bPresent, this->bPresent = bPresent);
		/* R */ inline bool  Present() const reflect_as(this->bPresent);
	public: // Property - Default
		/* W */ inline auto &Default(bool bDefault) reflect_to_self(bModified |= this->bDefault != bDefault, this->bDefault = bDefault);
		/* R */ inline bool  Default() const reflect_as(this->bDefault);
	public:
		inline operator SecurityDescriptor &() reflect_as(sd);
		inline operator const SecurityDescriptor &() const reflect_as(sd);
		inline operator bool() const reflect_as(Present());
		inline bool operator==(Null) const reflect_as(Present() ? pACL == O : true);
		inline bool operator!=(Null) const reflect_as(Present() ? pACL != O : false);
		inline AceList &operator*() reflect_as(ref_as<AceList>(pACL));
		inline const AceList &operator*() const reflect_as(ref_as<const AceList>(pACL));
		inline AceList *operator&() reflect_as(reuse_as<AceList *>(&pACL));
		inline const AceList *operator&() const reflect_as(reuse_as<const AceList *>(&pACL));
		inline AceList *operator->() reflect_as(reuse_as<AceList *>(&pACL));
		inline const AceList *operator->() const reflect_as(reuse_as<const AceList *>(&pACL));
	};
	template<bool _GSID_1_OSID_0_>
	class xSID {
		friend class SecurityDescriptor;
		SecurityDescriptor &sd;
		PSID pSID = O;
		bool bDefault = false, bModified = false;
		xSID(const SecurityDescriptor &sd) : sd(const_cast<SecurityDescriptor &>(sd)) {
			BOOL bDefault = false;
			if constexpr (_GSID_1_OSID_0_)
				 assertl(GetSecurityDescriptorGroup(&sd, &pSID, &bDefault))
			else assertl(GetSecurityDescriptorOwner(&sd, &pSID, &bDefault))
			this->bDefault = bDefault;
		}
		xSID(SecurityDescriptor &sd, PSID pSID) : sd(sd), pSID(pSID), bModified(true) {}
		inline void __Set() {
			if (bModified) {
				if constexpr (_GSID_1_OSID_0_)
					 assertl(SetSecurityDescriptorGroup(&sd, pSID, bDefault))
				else assertl(SetSecurityDescriptorOwner(&sd, pSID, bDefault))
			}
		}
	public:
		xSID(xSID &) = delete;
		xSID(xSID &&) = delete;
		xSID(const xSID &) = delete;
		~xSID() reflect_to(__Set());
	public: // Property - Default
		/* W */ inline auto &Default(bool bDefault) reflect_to_self(bModified |= this->bDefault != bDefault, this->bDefault = bDefault);
		/* R */ inline bool  Default() const reflect_as(this->bDefault);
	public:
		inline operator bool() const reflect_as(pSID);
		inline bool operator==(Null) const reflect_as(!pSID);
		inline bool operator!=(Null) const reflect_as(pSID);
		inline SecID &operator*() reflect_as(ref_as<SecID &>(pSID));
		inline const SecID &operator*() const reflect_as(ref_as<SecID &>(pSID));
		inline SecID *operator&() reflect_as(reuse_as<SecID *>(&pSID));
		inline const SecID *operator&() const reflect_as(reuse_as<const SecID *>(&pSID));
		inline SecID *operator->() reflect_as(reuse_as<SecID *>(&pSID));
		inline const SecID *operator->() const reflect_as(reuse_as<const SecID *>(&pSID));
	};
	class Control {
		friend class SecurityDescriptor;
		SECURITY_DESCRIPTOR_CONTROL flags, mask;
	public:
		Control(WORD flags) : flags(flags), mask(flags) {}
	public: // Property - Owner_Default
		/* W */ inline auto &Owner_Default(bool bDefault) reflect_to_self(if (bDefault) flags |= SE_OWNER_DEFAULTED; mask |= SE_OWNER_DEFAULTED);
		/* R */ inline bool  Owner_Default() const reflect_as(flags &SE_OWNER_DEFAULTED);
	public: // Property - Group_Default
		/* W */ inline auto &Group_Default(bool bDefault) reflect_to_self(if (bDefault) flags |= SE_GROUP_DEFAULTED; mask |= SE_GROUP_DEFAULTED);
		/* R */ inline bool  Group_Default() const reflect_as(flags &SE_GROUP_DEFAULTED);
	public: // Property - DACL_Present
		/* W */ inline auto &DACL_Present(bool bPresent) reflect_to_self(if (bPresent) flags |= SE_DACL_PRESENT; mask |= SE_DACL_PRESENT);
		/* R */ inline bool  DACL_Present() const reflect_as(flags &SE_DACL_PRESENT);
	public: // Property - DACL_Default
		/* W */ inline auto &DACL_Default(bool bDefault) reflect_to_self(if (bDefault) flags |= SE_DACL_DEFAULTED; mask |= SE_DACL_DEFAULTED);
		/* R */ inline bool  DACL_Default() const reflect_as(flags &SE_DACL_DEFAULTED);
	public: // Property - DACL_Protect
		/* W */ inline auto &DACL_Protect(bool bProtect) reflect_to_self(if (bProtect) flags |= SE_DACL_PROTECTED; mask |= SE_DACL_PROTECTED);
		/* R */ inline bool  DACL_Protect() const reflect_as(flags &SE_DACL_PROTECTED);
	public: // Property - DACL_AutoInherit
		/* W */ inline auto &DACL_AutoInherit(bool bAutoInherit) reflect_to_self(if (bAutoInherit) flags |= SE_DACL_AUTO_INHERITED; mask |= SE_DACL_AUTO_INHERITED);
		/* R */ inline bool  DACL_AutoInherit() const reflect_as(flags &SE_DACL_AUTO_INHERITED);
	public: // Property - DACL_AutoInheritReq
		/* W */ inline auto &DACL_AutoInheritReq(bool bAutoInheritReq) reflect_to_self(if (bAutoInheritReq) flags |= SE_DACL_AUTO_INHERIT_REQ; mask |= SE_DACL_AUTO_INHERIT_REQ);
		/* R */ inline bool  DACL_AutoInheritReq() const reflect_as(flags &SE_DACL_AUTO_INHERIT_REQ);
	public: // Property - SACL_Present
		/* W */ inline auto &SACL_Present(bool bPresent) reflect_to_self(if (bPresent) flags |= SE_SACL_PRESENT; mask |= SE_SACL_PRESENT);
		/* R */ inline bool  SACL_Present() const reflect_as(flags &SE_SACL_PRESENT);
	public: // Property - SACL_Default
		/* W */ inline auto &SACL_Default(bool bDefault) reflect_to_self(if (bDefault) flags |= SE_SACL_DEFAULTED; mask |= SE_SACL_DEFAULTED);
		/* R */ inline bool  SACL_Default() const reflect_as(flags &SE_SACL_DEFAULTED);
	public: // Property - SACL_Protect
		/* W */ inline auto &SACL_Protect(bool bProtect) reflect_to_self(if (bProtect) flags |= SE_SACL_PROTECTED; mask |= SE_SACL_PROTECTED);
		/* R */ inline bool  SACL_Protect() const reflect_as(flags &SE_SACL_PROTECTED);
	public: // Property - SACL_AutoInherit
		/* W */ inline auto &SACL_AutoInherit(bool bAutoInherit) reflect_to_self(if (bAutoInherit) flags |= SE_SACL_AUTO_INHERITED; mask |= SE_SACL_AUTO_INHERITED);
		/* R */ inline bool  SACL_AutoInherit() const reflect_as(flags &SE_SACL_AUTO_INHERITED);
	public: // Property - SACL_AutoInheritReq
		/* W */ inline auto &SACL_AutoInheritReq(bool bAutoInheritReq) reflect_to_self(if (bAutoInheritReq) flags |= SE_SACL_AUTO_INHERIT_REQ; mask |= SE_SACL_AUTO_INHERIT_REQ);
		/* R */ inline bool  SACL_AutoInheritReq() const reflect_as(flags &SE_SACL_AUTO_INHERIT_REQ);
	public: // Property - ControlRM_Valid
		/* W */ inline auto &ControlRM_Valid(bool bValid) reflect_to_self(if (bValid) flags |= SE_RM_CONTROL_VALID; mask |= SE_RM_CONTROL_VALID);
		/* R */ inline bool  ControlRM_Valid() const reflect_as(flags &SE_RM_CONTROL_VALID);
	public: // Property - Self_Relative
		/* R */ inline bool  Self_Relative() const reflect_as(flags &SE_SELF_RELATIVE);
	};
	SecurityDescriptor(PSECURITY_DESCRIPTOR pSD) : pSD(pSD) {}
public:
	SecurityDescriptor() : pSD(Local::Alloc<SECURITY_DESCRIPTOR>()) assertl(InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION));
	SecurityDescriptor(Null) {}
	SecurityDescriptor(SecurityDescriptor &sd) : pSD(sd.pSD) reflect_to(sd.pSD = O);
	SecurityDescriptor(SecurityDescriptor &&sd) : pSD(sd.pSD) reflect_to(sd.pSD = O);
	SecurityDescriptor(const SecurityDescriptor &sd) = delete;
	SecurityDescriptor(LPCSTR lpszDesc) assertl_reflect_to(ULONG size, ConvertStringSecurityDescriptorToSecurityDescriptorA(lpszDesc, SDDL_REVISION_1, &pSD, &size));
	SecurityDescriptor(LPCWSTR lpszDesc) assertl_reflect_to(ULONG size, ConvertStringSecurityDescriptorToSecurityDescriptorW(lpszDesc, SDDL_REVISION_1, &pSD, &size));

	inline void Delete() reflect_to(Local::Free(pSD); pSD = O);
	inline SecurityDescriptor operator+() const {
		if (!*this) return O;
		auto size = Size();
		auto npSD = (PSECURITY_DESCRIPTOR)Local::Alloc(size);
		CopyMemory(npSD, pSD, size);
		return npSD;
	}

	//inline SecurityDescriptor RelativeSelf() {
	//	//if (!*this) return O;
	//	// MakeSelfRelativeSD(pSD, )
	//	return O;
	//}

#pragma region Properties
public: // Property - Size
	/* R */ inline DWORD Size() const assertl_reflect_as(DWORD len = GetSecurityDescriptorLength(pSD), len);
public: // Property - Controls
	/* W */ inline auto   &Controls(Control ctl) assertl_reflect_as_self(SetSecurityDescriptorControl(pSD, ctl.mask, ctl.flags));
	/* R */ inline Control Controls() const assertl_reflect_to(WORD ctl; DWORD rev, GetSecurityDescriptorControl(pSD, &ctl, &rev), ctl);
public: // Property - SelfRelative
	/* R */ inline bool SelfRelative() const reflect_as(Controls().Self_Relative());
public: // Property - Discretion
	/* W */ inline xACL<false> Discretion(const AceList &acl) reflect_as({ self, &acl });
	/* W */ inline xACL<false> Discretion(PACL pACL) reflect_as({ self, pACL });
	/* R */ inline const xACL<false> Discretion() const reflect_to_self();
public: // Property - System
	/* W */ inline xACL<true> System(const AceList &acl) reflect_as({ self, &acl });
	/* W */ inline xACL<true> System(PACL pACL) reflect_as({ self, pACL });
	/* R */ inline const xACL<true> System() const reflect_to_self();
public: // Property - Group
	/* W */ inline xSID<true> Group(const SecID &sid) reflect_as({ self, &sid });
	/* W */ inline xSID<true> Group(PSID pSID) reflect_as({ self, pSID });
	/* R */ inline const xSID<true> Group() const reflect_to_self();
public: // Property - Owner
	/* W */ inline xSID<false> Owner(const SecID &sid) reflect_as({ self, &sid });
	/* W */ inline xSID<false> Owner(PSID pSID) reflect_as({ self, pSID });
	/* R */ inline const xSID<false> Owner() const reflect_to_self();
#pragma endregion

	inline PSECURITY_DESCRIPTOR operator&() const reflect_as(pSD);
	inline operator bool() const reflect_as(pSD ? IsValidSecurityDescriptor(pSD) : false);
};
using SecDesc = SecurityDescriptor;
#pragma endregion

#pragma region Security Attributes
class SecurityAttributes : protected SECURITY_ATTRIBUTES {
public:
	SecurityAttributes() : SECURITY_ATTRIBUTES{ 0 } reflect_to(this->nLength = sizeof(*this));
	SecurityAttributes(Null) : SecurityAttributes() {}
	SecurityAttributes(SecurityAttributes &sa) : SECURITY_ATTRIBUTES(sa) reflect_to(sa.lpSecurityDescriptor = O);
	SecurityAttributes(SecurityAttributes &&sa) : SECURITY_ATTRIBUTES(sa) reflect_to(sa.lpSecurityDescriptor = O);
	SecurityAttributes(const SecurityAttributes &) = delete;
	SecurityAttributes(const SECURITY_ATTRIBUTES &sa) : SECURITY_ATTRIBUTES(sa) {}
	constexpr SecurityAttributes(bool bInherit, PSECURITY_DESCRIPTOR pSD = O) : SECURITY_ATTRIBUTES{ sizeof(*this), pSD, bInherit } {}

public: // Property - Inherit
	/* W */ inline auto &Inherit(bool bInheritHandle) reflect_to_self(this->bInheritHandle = bInheritHandle);
	/* R */ inline bool  Inherit() const reflect_as(this->bInheritHandle);
public: // Property - Descriptor
	/* W */ inline auto &Descriptor(const SecDesc &sd) reflect_to_self(this->lpSecurityDescriptor = &sd);
	/* R */ inline SecDesc &Descriptor() const reflect_as(ref_as<SecDesc>(this->lpSecurityDescriptor));

	inline PSECURITY_ATTRIBUTES operator&() const reflect_as(reuse_as<PSECURITY_ATTRIBUTES>(this));
};
using SecAttr = SecurityAttributes;
static inline constexpr SecurityAttributes InheritHandle = true;
#pragma endregion

}
