module;

#include <windows.h>
#include <aclapi.h>
#include <sddl.h>

#include "wx_type"

export module wx.security;

#pragma region Win32 Prototype Includes
namespace WX {

#pragma region SDDL.h
#undef ConvertSidToStringSid
// ConvertSidToStringSidA
inline void ConvertSidToStringSid(PSID Sid, LPSTR *StringSid)
	assertl_reflect_as(::ConvertSidToStringSidA(Sid, StringSid));
// ConvertSidToStringSidW
inline void ConvertSidToStringSid(PSID Sid, LPWSTR *StringSid)
	assertl_reflect_as(::ConvertSidToStringSidW(Sid, StringSid));
#undef ConvertStringSidToSid
// ConvertStringSidToSidA
inline void ConvertStringSidToSid(LPCSTR StringSid, PSID *Sid)
	assertl_reflect_as(::ConvertStringSidToSidA(StringSid, Sid));
// ConvertStringSidToSidW
inline void ConvertStringSidToSid(LPCWSTR StringSid, PSID *Sid)
	assertl_reflect_as(::ConvertStringSidToSidW(StringSid, Sid));
#undef ConvertStringSecurityDescriptorToSecurityDescriptor
// ConvertStringSecurityDescriptorToSecurityDescriptorA
inline void ConvertStringSecurityDescriptorToSecurityDescriptor(LPCSTR StringSecurityDescriptor,
																DWORD StringSDRevision,
																PSECURITY_DESCRIPTOR *SecurityDescriptor,
																PULONG SecurityDescriptorSize)
	assertl_reflect_as(::ConvertStringSecurityDescriptorToSecurityDescriptorA(StringSecurityDescriptor,
																			  StringSDRevision,
																			  SecurityDescriptor,
																			  SecurityDescriptorSize));
// ConvertStringSecurityDescriptorToSecurityDescriptorW
inline void ConvertStringSecurityDescriptorToSecurityDescriptor(LPCWSTR StringSecurityDescriptor,
																DWORD StringSDRevision,
																PSECURITY_DESCRIPTOR *SecurityDescriptor,
																PULONG SecurityDescriptorSize)
	assertl_reflect_as(::ConvertStringSecurityDescriptorToSecurityDescriptorW(StringSecurityDescriptor,
																			  StringSDRevision,
																			  SecurityDescriptor,
																			  SecurityDescriptorSize));
#undef ConvertSecurityDescriptorToStringSecurityDescriptor
// ConvertSecurityDescriptorToStringSecurityDescriptorA
inline void ConvertSecurityDescriptorToStringSecurityDescriptor(PSECURITY_DESCRIPTOR SecurityDescriptor,
																DWORD StringSDRevision,
																SECURITY_INFORMATION SecurityInformation,
																LPSTR *StringSecurityDescriptor,
																PULONG StringSecurityDescriptorLen)
	assertl_reflect_as(::ConvertSecurityDescriptorToStringSecurityDescriptorA(SecurityDescriptor,
																			  StringSDRevision,
																			  SecurityInformation,
																			  StringSecurityDescriptor,
																			  StringSecurityDescriptorLen));
// ConvertSecurityDescriptorToStringSecurityDescriptorW
inline void ConvertSecurityDescriptorToStringSecurityDescriptor(PSECURITY_DESCRIPTOR SecurityDescriptor,
																DWORD StringSDRevision,
																SECURITY_INFORMATION SecurityInformation,
																LPWSTR *StringSecurityDescriptor,
																PULONG StringSecurityDescriptorLen)
	assertl_reflect_as(::ConvertSecurityDescriptorToStringSecurityDescriptorW(SecurityDescriptor,
																			  StringSDRevision,
																			  SecurityInformation,
																			  StringSecurityDescriptor,
																			  StringSecurityDescriptorLen));
#pragma endregion

#pragma region SecurityBaseAPI.h
// AccessCheck
inline void AccessCheck(PSECURITY_DESCRIPTOR pSecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, PPRIVILEGE_SET PrivilegeSet, LPDWORD PrivilegeSetLength, LPDWORD GrantedAccess, LPBOOL AccessStatus)
    assertl_reflect_as(::AccessCheck(pSecurityDescriptor, ClientToken, DesiredAccess, GenericMapping, PrivilegeSet, PrivilegeSetLength, GrantedAccess, AccessStatus));
// AccessCheckAndAuditAlarmW
inline void AccessCheckAndAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, LPWSTR ObjectTypeName, LPWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor, DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess, LPBOOL AccessStatus, LPBOOL pfGenerateOnClose)
    assertl_reflect_as(::AccessCheckAndAuditAlarmW(SubsystemName, HandleId, ObjectTypeName, ObjectName, SecurityDescriptor, DesiredAccess, GenericMapping, ObjectCreation, GrantedAccess, AccessStatus, pfGenerateOnClose));
// AccessCheckByType
inline void AccessCheckByType(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID PrincipalSelfSid, HANDLE ClientToken, DWORD DesiredAccess, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength, PGENERIC_MAPPING GenericMapping, PPRIVILEGE_SET PrivilegeSet, LPDWORD PrivilegeSetLength, LPDWORD GrantedAccess, LPBOOL AccessStatus)
    assertl_reflect_as(::AccessCheckByType(pSecurityDescriptor, PrincipalSelfSid, ClientToken, DesiredAccess, ObjectTypeList, ObjectTypeListLength, GenericMapping, PrivilegeSet, PrivilegeSetLength, GrantedAccess, AccessStatus));
// AccessCheckByTypeResultList
inline void AccessCheckByTypeResultList(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID PrincipalSelfSid, HANDLE ClientToken, DWORD DesiredAccess, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength, PGENERIC_MAPPING GenericMapping, PPRIVILEGE_SET PrivilegeSet, LPDWORD PrivilegeSetLength, LPDWORD GrantedAccessList, LPDWORD AccessStatusList)
    assertl_reflect_as(::AccessCheckByTypeResultList(pSecurityDescriptor, PrincipalSelfSid, ClientToken, DesiredAccess, ObjectTypeList, ObjectTypeListLength, GenericMapping, PrivilegeSet, PrivilegeSetLength, GrantedAccessList, AccessStatusList));
// AccessCheckByTypeAndAuditAlarmW
inline void AccessCheckByTypeAndAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, LPCWSTR ObjectTypeName, LPCWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor, PSID PrincipalSelfSid, DWORD DesiredAccess, AUDIT_EVENT_TYPE AuditType, DWORD Flags, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess, LPBOOL AccessStatus, LPBOOL pfGenerateOnClose)
    assertl_reflect_as(::AccessCheckByTypeAndAuditAlarmW(SubsystemName, HandleId, ObjectTypeName, ObjectName, SecurityDescriptor, PrincipalSelfSid, DesiredAccess, AuditType, Flags, ObjectTypeList, ObjectTypeListLength, GenericMapping, ObjectCreation, GrantedAccess, AccessStatus, pfGenerateOnClose));
// AccessCheckByTypeResultListAndAuditAlarmW
inline void AccessCheckByTypeResultListAndAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, LPCWSTR ObjectTypeName, LPCWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor, PSID PrincipalSelfSid, DWORD DesiredAccess, AUDIT_EVENT_TYPE AuditType, DWORD Flags, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccessList, LPDWORD AccessStatusList, LPBOOL pfGenerateOnClose)
    assertl_reflect_as(::AccessCheckByTypeResultListAndAuditAlarmW(SubsystemName, HandleId, ObjectTypeName, ObjectName, SecurityDescriptor, PrincipalSelfSid, DesiredAccess, AuditType, Flags, ObjectTypeList, ObjectTypeListLength, GenericMapping, ObjectCreation, GrantedAccessList, AccessStatusList, pfGenerateOnClose));
// AccessCheckByTypeResultListAndAuditAlarmByHandleW
inline void AccessCheckByTypeResultListAndAuditAlarmByHandle(LPCWSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken, LPCWSTR ObjectTypeName, LPCWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor, PSID PrincipalSelfSid, DWORD DesiredAccess, AUDIT_EVENT_TYPE AuditType, DWORD Flags, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccessList, LPDWORD AccessStatusList, LPBOOL pfGenerateOnClose)
    assertl_reflect_as(::AccessCheckByTypeResultListAndAuditAlarmByHandleW(SubsystemName, HandleId, ClientToken, ObjectTypeName, ObjectName, SecurityDescriptor, PrincipalSelfSid, DesiredAccess, AuditType, Flags, ObjectTypeList, ObjectTypeListLength, GenericMapping, ObjectCreation, GrantedAccessList, AccessStatusList, pfGenerateOnClose));
// AddAccessAllowedAce
inline void AddAccessAllowedAce(PACL pAcl, DWORD dwAceRevision, DWORD AccessMask, PSID pSid)
    assertl_reflect_as(::AddAccessAllowedAce(pAcl, dwAceRevision, AccessMask, pSid));
// AddAccessAllowedAceEx
inline void AddAccessAllowedAceEx(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, PSID pSid)
    assertl_reflect_as(::AddAccessAllowedAceEx(pAcl, dwAceRevision, AceFlags, AccessMask, pSid));
// AddAccessAllowedObjectAce
inline void AddAccessAllowedObjectAce(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, GUID* ObjectTypeGuid, GUID* InheritedObjectTypeGuid, PSID pSid)
    assertl_reflect_as(::AddAccessAllowedObjectAce(pAcl, dwAceRevision, AceFlags, AccessMask, ObjectTypeGuid, InheritedObjectTypeGuid, pSid));
// AddAccessDeniedAce
inline void AddAccessDeniedAce(PACL pAcl, DWORD dwAceRevision, DWORD AccessMask, PSID pSid)
    assertl_reflect_as(::AddAccessDeniedAce(pAcl, dwAceRevision, AccessMask, pSid));
// AddAccessDeniedAceEx
inline void AddAccessDeniedAceEx(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, PSID pSid)
    assertl_reflect_as(::AddAccessDeniedAceEx(pAcl, dwAceRevision, AceFlags, AccessMask, pSid));
// AddAccessDeniedObjectAce
inline void AddAccessDeniedObjectAce(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, GUID* ObjectTypeGuid, GUID* InheritedObjectTypeGuid, PSID pSid)
    assertl_reflect_as(::AddAccessDeniedObjectAce(pAcl, dwAceRevision, AceFlags, AccessMask, ObjectTypeGuid, InheritedObjectTypeGuid, pSid));
// AddAce
inline void AddAce(PACL pAcl, DWORD dwAceRevision, DWORD dwStartingAceIndex, LPVOID pAceList, DWORD nAceListLength)
    assertl_reflect_as(::AddAce(pAcl, dwAceRevision, dwStartingAceIndex, pAceList, nAceListLength));
// AddAuditAccessAce
inline void AddAuditAccessAce(PACL pAcl, DWORD dwAceRevision, DWORD dwAccessMask, PSID pSid, BOOL bAuditSuccess, BOOL bAuditFailure)
    assertl_reflect_as(::AddAuditAccessAce(pAcl, dwAceRevision, dwAccessMask, pSid, bAuditSuccess, bAuditFailure));
// AddAuditAccessAceEx
inline void AddAuditAccessAceEx(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD dwAccessMask, PSID pSid, BOOL bAuditSuccess, BOOL bAuditFailure)
    assertl_reflect_as(::AddAuditAccessAceEx(pAcl, dwAceRevision, AceFlags, dwAccessMask, pSid, bAuditSuccess, bAuditFailure));
// AddAuditAccessObjectAce
inline void AddAuditAccessObjectAce(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, GUID* ObjectTypeGuid, GUID* InheritedObjectTypeGuid, PSID pSid, BOOL bAuditSuccess, BOOL bAuditFailure)
    assertl_reflect_as(::AddAuditAccessObjectAce(pAcl, dwAceRevision, AceFlags, AccessMask, ObjectTypeGuid, InheritedObjectTypeGuid, pSid, bAuditSuccess, bAuditFailure));
// AddMandatoryAce
inline void AddMandatoryAce(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD MandatoryPolicy, PSID pLabelSid)
    assertl_reflect_as(::AddMandatoryAce(pAcl, dwAceRevision, AceFlags, MandatoryPolicy, pLabelSid));
// AddResourceAttributeAce
inline void AddResourceAttributeAce(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, PSID pSid, PCLAIM_SECURITY_ATTRIBUTES_INFORMATION pAttributeInfo, PDWORD pReturnLength)
    assertl_reflect_as(::AddResourceAttributeAce(pAcl, dwAceRevision, AceFlags, AccessMask, pSid, pAttributeInfo, pReturnLength));
// AddScopedPolicyIDAce
inline void AddScopedPolicyIDAce(PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, PSID pSid)
    assertl_reflect_as(::AddScopedPolicyIDAce(pAcl, dwAceRevision, AceFlags, AccessMask, pSid));
// AdjustTokenGroups
inline void AdjustTokenGroups(HANDLE TokenHandle, BOOL ResetToDefault, PTOKEN_GROUPS NewState, DWORD BufferLength, PTOKEN_GROUPS PreviousState, PDWORD ReturnLength)
    assertl_reflect_as(::AdjustTokenGroups(TokenHandle, ResetToDefault, NewState, BufferLength, PreviousState, ReturnLength));
// AdjustTokenPrivileges
inline void AdjustTokenPrivileges(HANDLE TokenHandle, BOOL DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, DWORD BufferLength, PTOKEN_PRIVILEGES PreviousState, PDWORD ReturnLength)
    assertl_reflect_as(::AdjustTokenPrivileges(TokenHandle, DisableAllPrivileges, NewState, BufferLength, PreviousState, ReturnLength));
// AllocateAndInitializeSid
inline void AllocateAndInitializeSid(PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount, DWORD nSubAuthority0, DWORD nSubAuthority1, DWORD nSubAuthority2, DWORD nSubAuthority3, DWORD nSubAuthority4, DWORD nSubAuthority5, DWORD nSubAuthority6, DWORD nSubAuthority7, PSID* pSid)
    assertl_reflect_as(::AllocateAndInitializeSid(pIdentifierAuthority, nSubAuthorityCount, nSubAuthority0, nSubAuthority1, nSubAuthority2, nSubAuthority3, nSubAuthority4, nSubAuthority5, nSubAuthority6, nSubAuthority7, pSid));
// AllocateLocallyUniqueId
inline void AllocateLocallyUniqueId(PLUID Luid)
    assertl_reflect_as(::AllocateLocallyUniqueId(Luid));
// AreAllAccessesGranted
inline void AreAllAccessesGranted(DWORD GrantedAccess, DWORD DesiredAccess)
    assertl_reflect_as(::AreAllAccessesGranted(GrantedAccess, DesiredAccess));
// AreAnyAccessesGranted
inline bool AreAnyAccessesGranted(DWORD GrantedAccess, DWORD DesiredAccess)
    reflect_as(::AreAnyAccessesGranted(GrantedAccess, DesiredAccess));
// CheckTokenMembership
inline void CheckTokenMembership(HANDLE TokenHandle, PSID SidToCheck, PBOOL IsMember)
    assertl_reflect_as(::CheckTokenMembership(TokenHandle, SidToCheck, IsMember));
// CheckTokenCapability
inline void CheckTokenCapability(HANDLE TokenHandle, PSID CapabilitySidToCheck, PBOOL HasCapability)
    assertl_reflect_as(::CheckTokenCapability(TokenHandle, CapabilitySidToCheck, HasCapability));
// GetAppContainerAce
inline void GetAppContainerAce(PACL Acl, DWORD StartingAceIndex, PVOID* AppContainerAce, DWORD* AppContainerAceIndex)
    assertl_reflect_as(::GetAppContainerAce(Acl, StartingAceIndex, AppContainerAce, AppContainerAceIndex));
// CheckTokenMembershipEx
inline void CheckTokenMembershipEx(HANDLE TokenHandle, PSID SidToCheck, DWORD Flags, PBOOL IsMember)
    assertl_reflect_as(::CheckTokenMembershipEx(TokenHandle, SidToCheck, Flags, IsMember));
// ConvertToAutoInheritPrivateObjectSecurity
inline void ConvertToAutoInheritPrivateObjectSecurity(PSECURITY_DESCRIPTOR ParentDescriptor, PSECURITY_DESCRIPTOR CurrentSecurityDescriptor, PSECURITY_DESCRIPTOR* NewSecurityDescriptor, GUID* ObjectType, BOOLEAN IsDirectoryObject, PGENERIC_MAPPING GenericMapping)
    assertl_reflect_as(::ConvertToAutoInheritPrivateObjectSecurity(ParentDescriptor, CurrentSecurityDescriptor, NewSecurityDescriptor, ObjectType, IsDirectoryObject, GenericMapping));
// CopySid
inline void CopySid(DWORD nDestinationSidLength, PSID pDestinationSid, PSID pSourceSid)
    assertl_reflect_as(::CopySid(nDestinationSidLength, pDestinationSid, pSourceSid));
// CreatePrivateObjectSecurity
inline void CreatePrivateObjectSecurity(PSECURITY_DESCRIPTOR ParentDescriptor, PSECURITY_DESCRIPTOR CreatorDescriptor, PSECURITY_DESCRIPTOR* NewDescriptor, BOOL IsDirectoryObject, HANDLE Token, PGENERIC_MAPPING GenericMapping)
    assertl_reflect_as(::CreatePrivateObjectSecurity(ParentDescriptor, CreatorDescriptor, NewDescriptor, IsDirectoryObject, Token, GenericMapping));
// CreatePrivateObjectSecurityEx
inline void CreatePrivateObjectSecurityEx(PSECURITY_DESCRIPTOR ParentDescriptor, PSECURITY_DESCRIPTOR CreatorDescriptor, PSECURITY_DESCRIPTOR* NewDescriptor, GUID* ObjectType, BOOL IsContainerObject, ULONG AutoInheritFlags, HANDLE Token, PGENERIC_MAPPING GenericMapping)
    assertl_reflect_as(::CreatePrivateObjectSecurityEx(ParentDescriptor, CreatorDescriptor, NewDescriptor, ObjectType, IsContainerObject, AutoInheritFlags, Token, GenericMapping));
// CreatePrivateObjectSecurityWithMultipleInheritance
inline void CreatePrivateObjectSecurityWithMultipleInheritance(PSECURITY_DESCRIPTOR ParentDescriptor, PSECURITY_DESCRIPTOR CreatorDescriptor, PSECURITY_DESCRIPTOR* NewDescriptor, GUID** ObjectTypes, ULONG GuidCount, BOOL IsContainerObject, ULONG AutoInheritFlags, HANDLE Token, PGENERIC_MAPPING GenericMapping)
    assertl_reflect_as(::CreatePrivateObjectSecurityWithMultipleInheritance(ParentDescriptor, CreatorDescriptor, NewDescriptor, ObjectTypes, GuidCount, IsContainerObject, AutoInheritFlags, Token, GenericMapping));
// CreateRestrictedToken
inline void CreateRestrictedToken(HANDLE ExistingTokenHandle, DWORD Flags, DWORD DisableSidCount, PSID_AND_ATTRIBUTES SidsToDisable, DWORD DeletePrivilegeCount, PLUID_AND_ATTRIBUTES PrivilegesToDelete, DWORD RestrictedSidCount, PSID_AND_ATTRIBUTES SidsToRestrict, PHANDLE NewTokenHandle)
    assertl_reflect_as(::CreateRestrictedToken(ExistingTokenHandle, Flags, DisableSidCount, SidsToDisable, DeletePrivilegeCount, PrivilegesToDelete, RestrictedSidCount, SidsToRestrict, NewTokenHandle));
// CreateWellKnownSid
inline void CreateWellKnownSid(WELL_KNOWN_SID_TYPE WellKnownSidType, PSID DomainSid, PSID pSid, DWORD* cbSid)
    assertl_reflect_as(::CreateWellKnownSid(WellKnownSidType, DomainSid, pSid, cbSid));
// EqualDomainSid
inline void EqualDomainSid(PSID pSid1, PSID pSid2, BOOL* pfEqual)
    assertl_reflect_as(::EqualDomainSid(pSid1, pSid2, pfEqual));
// DeleteAce
inline void DeleteAce(PACL pAcl, DWORD dwAceIndex)
    assertl_reflect_as(::DeleteAce(pAcl, dwAceIndex));
// DestroyPrivateObjectSecurity
inline void DestroyPrivateObjectSecurity(PSECURITY_DESCRIPTOR* ObjectDescriptor)
    assertl_reflect_as(::DestroyPrivateObjectSecurity(ObjectDescriptor));
// DuplicateToken
inline void DuplicateToken(HANDLE ExistingTokenHandle, SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, PHANDLE DuplicateTokenHandle)
    assertl_reflect_as(::DuplicateToken(ExistingTokenHandle, ImpersonationLevel, DuplicateTokenHandle));
// DuplicateTokenEx
inline void DuplicateTokenEx(HANDLE hExistingToken, DWORD dwDesiredAccess, LPSECURITY_ATTRIBUTES lpTokenAttributes, SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, TOKEN_TYPE TokenType, PHANDLE phNewToken)
    assertl_reflect_as(::DuplicateTokenEx(hExistingToken, dwDesiredAccess, lpTokenAttributes, ImpersonationLevel, TokenType, phNewToken));
// EqualPrefixSid
inline bool EqualPrefixSid(PSID pSid1, PSID pSid2)
    reflect_as(::EqualPrefixSid(pSid1, pSid2));
// EqualSid
inline bool EqualSid(PSID pSid1, PSID pSid2)
    reflect_as(::EqualSid(pSid1, pSid2));
// FindFirstFreeAce
inline void FindFirstFreeAce(PACL pAcl, LPVOID* pAce)
    assertl_reflect_as(::FindFirstFreeAce(pAcl, pAce));
// GetAce
inline void GetAce(PACL pAcl, DWORD dwAceIndex, LPVOID* pAce)
    assertl_reflect_as(::GetAce(pAcl, dwAceIndex, pAce));
// GetAclInformation
inline void GetAclInformation(PACL pAcl, LPVOID pAclInformation, DWORD nAclInformationLength, ACL_INFORMATION_CLASS dwAclInformationClass)
    assertl_reflect_as(::GetAclInformation(pAcl, pAclInformation, nAclInformationLength, dwAclInformationClass));
// GetFileSecurityW
inline void GetFileSecurity(LPCWSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded)
    assertl_reflect_as(::GetFileSecurityW(lpFileName, RequestedInformation, pSecurityDescriptor, nLength, lpnLengthNeeded));
// GetKernelObjectSecurity
inline void GetKernelObjectSecurity(HANDLE Handle, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded)
    assertl_reflect_as(::GetKernelObjectSecurity(Handle, RequestedInformation, pSecurityDescriptor, nLength, lpnLengthNeeded));
// GetPrivateObjectSecurity
inline void GetPrivateObjectSecurity(PSECURITY_DESCRIPTOR ObjectDescriptor, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR ResultantDescriptor, DWORD DescriptorLength, PDWORD ReturnLength)
    assertl_reflect_as(::GetPrivateObjectSecurity(ObjectDescriptor, SecurityInformation, ResultantDescriptor, DescriptorLength, ReturnLength));
// GetSecurityDescriptorControl
inline void GetSecurityDescriptorControl(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSECURITY_DESCRIPTOR_CONTROL pControl, LPDWORD lpdwRevision)
    assertl_reflect_as(::GetSecurityDescriptorControl(pSecurityDescriptor, pControl, lpdwRevision));
// GetSecurityDescriptorDacl
inline void GetSecurityDescriptorDacl(PSECURITY_DESCRIPTOR pSecurityDescriptor, LPBOOL lpbDaclPresent, PACL* pDacl, LPBOOL lpbDaclDefaulted)
    assertl_reflect_as(::GetSecurityDescriptorDacl(pSecurityDescriptor, lpbDaclPresent, pDacl, lpbDaclDefaulted));
// GetSecurityDescriptorGroup
inline void GetSecurityDescriptorGroup(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID* pGroup, LPBOOL lpbGroupDefaulted)
    assertl_reflect_as(::GetSecurityDescriptorGroup(pSecurityDescriptor, pGroup, lpbGroupDefaulted));
// GetSecurityDescriptorOwner
inline void GetSecurityDescriptorOwner(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID* pOwner, LPBOOL lpbOwnerDefaulted)
    assertl_reflect_as(::GetSecurityDescriptorOwner(pSecurityDescriptor, pOwner, lpbOwnerDefaulted));
// GetSecurityDescriptorSacl
inline void GetSecurityDescriptorSacl(PSECURITY_DESCRIPTOR pSecurityDescriptor, LPBOOL lpbSaclPresent, PACL* pSacl, LPBOOL lpbSaclDefaulted)
    assertl_reflect_as(::GetSecurityDescriptorSacl(pSecurityDescriptor, lpbSaclPresent, pSacl, lpbSaclDefaulted));
// GetTokenInformation
inline void GetTokenInformation(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength, PDWORD ReturnLength)
    assertl_reflect_as(::GetTokenInformation(TokenHandle, TokenInformationClass, TokenInformation, TokenInformationLength, ReturnLength));
// GetWindowsAccountDomainSid
inline void GetWindowsAccountDomainSid(PSID pSid, PSID pDomainSid, DWORD* cbDomainSid)
    assertl_reflect_as(::GetWindowsAccountDomainSid(pSid, pDomainSid, cbDomainSid));
// ImpersonateAnonymousToken
inline void ImpersonateAnonymousToken(HANDLE ThreadHandle)
    assertl_reflect_as(::ImpersonateAnonymousToken(ThreadHandle));
// ImpersonateLoggedOnUser
inline void ImpersonateLoggedOnUser(HANDLE hToken)
    assertl_reflect_as(::ImpersonateLoggedOnUser(hToken));
// ImpersonateSelf
inline void ImpersonateSelf(SECURITY_IMPERSONATION_LEVEL ImpersonationLevel)
    assertl_reflect_as(::ImpersonateSelf(ImpersonationLevel));
// InitializeAcl
inline void InitializeAcl(PACL pAcl, DWORD nAclLength, DWORD dwAclRevision)
    assertl_reflect_as(::InitializeAcl(pAcl, nAclLength, dwAclRevision));
// InitializeSecurityDescriptor
inline void InitializeSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD dwRevision)
    assertl_reflect_as(::InitializeSecurityDescriptor(pSecurityDescriptor, dwRevision));
// InitializeSid
inline void InitializeSid(PSID Sid, PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount)
    assertl_reflect_as(::InitializeSid(Sid, pIdentifierAuthority, nSubAuthorityCount));
// IsTokenRestricted
inline bool IsTokenRestricted(HANDLE TokenHandle)
    reflect_as(::IsTokenRestricted(TokenHandle));
// IsValidAcl
inline bool IsValidAcl(PACL pAcl)
    reflect_as(::IsValidAcl(pAcl));
// IsValidSecurityDescriptor
inline bool IsValidSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor)
    reflect_as(::IsValidSecurityDescriptor(pSecurityDescriptor));
// IsValidSid
inline bool IsValidSid(PSID pSid)
    reflect_as(::IsValidSid(pSid));
// IsWellKnownSid
inline bool IsWellKnownSid(PSID pSid, WELL_KNOWN_SID_TYPE WellKnownSidType)
    reflect_as(::IsWellKnownSid(pSid, WellKnownSidType));
// MakeAbsoluteSD
inline void MakeAbsoluteSD(PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor, PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor, LPDWORD lpdwAbsoluteSecurityDescriptorSize, PACL pDacl, LPDWORD lpdwDaclSize, PACL pSacl, LPDWORD lpdwSaclSize, PSID pOwner, LPDWORD lpdwOwnerSize, PSID pPrimaryGroup, LPDWORD lpdwPrimaryGroupSize)
    assertl_reflect_as(::MakeAbsoluteSD(pSelfRelativeSecurityDescriptor, pAbsoluteSecurityDescriptor, lpdwAbsoluteSecurityDescriptorSize, pDacl, lpdwDaclSize, pSacl, lpdwSaclSize, pOwner, lpdwOwnerSize, pPrimaryGroup, lpdwPrimaryGroupSize));
// MakeSelfRelativeSD
inline void MakeSelfRelativeSD(PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor, PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor, LPDWORD lpdwBufferLength)
    assertl_reflect_as(::MakeSelfRelativeSD(pAbsoluteSecurityDescriptor, pSelfRelativeSecurityDescriptor, lpdwBufferLength));
// ObjectCloseAuditAlarmW
inline void ObjectCloseAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
    assertl_reflect_as(::ObjectCloseAuditAlarmW(SubsystemName, HandleId, GenerateOnClose));
// ObjectDeleteAuditAlarmW
inline void ObjectDeleteAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
    assertl_reflect_as(::ObjectDeleteAuditAlarmW(SubsystemName, HandleId, GenerateOnClose));
// ObjectOpenAuditAlarmW
inline void ObjectOpenAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, LPWSTR ObjectTypeName, LPWSTR ObjectName, PSECURITY_DESCRIPTOR pSecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess, DWORD GrantedAccess, PPRIVILEGE_SET Privileges, BOOL ObjectCreation, BOOL AccessGranted, LPBOOL GenerateOnClose)
    assertl_reflect_as(::ObjectOpenAuditAlarmW(SubsystemName, HandleId, ObjectTypeName, ObjectName, pSecurityDescriptor, ClientToken, DesiredAccess, GrantedAccess, Privileges, ObjectCreation, AccessGranted, GenerateOnClose));
// ObjectPrivilegeAuditAlarmW
inline void ObjectPrivilegeAuditAlarm(LPCWSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken, DWORD DesiredAccess, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
    assertl_reflect_as(::ObjectPrivilegeAuditAlarmW(SubsystemName, HandleId, ClientToken, DesiredAccess, Privileges, AccessGranted));
// PrivilegeCheck
inline void PrivilegeCheck(HANDLE ClientToken, PPRIVILEGE_SET RequiredPrivileges, LPBOOL pfResult)
    assertl_reflect_as(::PrivilegeCheck(ClientToken, RequiredPrivileges, pfResult));
// PrivilegedServiceAuditAlarmW
inline void PrivilegedServiceAuditAlarm(LPCWSTR SubsystemName, LPCWSTR ServiceName, HANDLE ClientToken, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
    assertl_reflect_as(::PrivilegedServiceAuditAlarmW(SubsystemName, ServiceName, ClientToken, Privileges, AccessGranted));
// RevertToSelf
inline void RevertToSelf()
    assertl_reflect_as(::RevertToSelf());
// SetAclInformation
inline void SetAclInformation(PACL pAcl, LPVOID pAclInformation, DWORD nAclInformationLength, ACL_INFORMATION_CLASS dwAclInformationClass)
    assertl_reflect_as(::SetAclInformation(pAcl, pAclInformation, nAclInformationLength, dwAclInformationClass));
// SetFileSecurityW
inline void SetFileSecurity(LPCWSTR lpFileName, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor)
    assertl_reflect_as(::SetFileSecurityW(lpFileName, SecurityInformation, pSecurityDescriptor));
// SetKernelObjectSecurity
inline void SetKernelObjectSecurity(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor)
    assertl_reflect_as(::SetKernelObjectSecurity(Handle, SecurityInformation, SecurityDescriptor));
// SetPrivateObjectSecurity
inline void SetPrivateObjectSecurity(SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR ModificationDescriptor, PSECURITY_DESCRIPTOR* ObjectsSecurityDescriptor, PGENERIC_MAPPING GenericMapping, HANDLE Token)
    assertl_reflect_as(::SetPrivateObjectSecurity(SecurityInformation, ModificationDescriptor, ObjectsSecurityDescriptor, GenericMapping, Token));
// SetPrivateObjectSecurityEx
inline void SetPrivateObjectSecurityEx(SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR ModificationDescriptor, PSECURITY_DESCRIPTOR* ObjectsSecurityDescriptor, ULONG AutoInheritFlags, PGENERIC_MAPPING GenericMapping, HANDLE Token)
    assertl_reflect_as(::SetPrivateObjectSecurityEx(SecurityInformation, ModificationDescriptor, ObjectsSecurityDescriptor, AutoInheritFlags, GenericMapping, Token));
// SetSecurityDescriptorControl
inline void SetSecurityDescriptorControl(PSECURITY_DESCRIPTOR pSecurityDescriptor, SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest, SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet)
    assertl_reflect_as(::SetSecurityDescriptorControl(pSecurityDescriptor, ControlBitsOfInterest, ControlBitsToSet));
// SetSecurityDescriptorDacl
inline void SetSecurityDescriptorDacl(PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOL bDaclPresent, PACL pDacl, BOOL bDaclDefaulted)
    assertl_reflect_as(::SetSecurityDescriptorDacl(pSecurityDescriptor, bDaclPresent, pDacl, bDaclDefaulted));
// SetSecurityDescriptorGroup
inline void SetSecurityDescriptorGroup(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID pGroup, BOOL bGroupDefaulted)
    assertl_reflect_as(::SetSecurityDescriptorGroup(pSecurityDescriptor, pGroup, bGroupDefaulted));
// SetSecurityDescriptorOwner
inline void SetSecurityDescriptorOwner(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID pOwner, BOOL bOwnerDefaulted)
    assertl_reflect_as(::SetSecurityDescriptorOwner(pSecurityDescriptor, pOwner, bOwnerDefaulted));
// SetSecurityDescriptorSacl
inline void SetSecurityDescriptorSacl(PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOL bSaclPresent, PACL pSacl, BOOL bSaclDefaulted)
    assertl_reflect_as(::SetSecurityDescriptorSacl(pSecurityDescriptor, bSaclPresent, pSacl, bSaclDefaulted));
// SetTokenInformation
inline void SetTokenInformation(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength)
    assertl_reflect_as(::SetTokenInformation(TokenHandle, TokenInformationClass, TokenInformation, TokenInformationLength));
// SetCachedSigningLevel
inline void SetCachedSigningLevel(PHANDLE SourceFiles, ULONG SourceFileCount, ULONG Flags, HANDLE TargetFile)
    assertl_reflect_as(::SetCachedSigningLevel(SourceFiles, SourceFileCount, Flags, TargetFile));
// GetCachedSigningLevel
inline void GetCachedSigningLevel(HANDLE File, PULONG Flags, PULONG SigningLevel, PUCHAR Thumbprint, PULONG ThumbprintSize, PULONG ThumbprintAlgorithm)
    assertl_reflect_as(::GetCachedSigningLevel(File, Flags, SigningLevel, Thumbprint, ThumbprintSize, ThumbprintAlgorithm));
// DeriveCapabilitySidsFromName
inline void DeriveCapabilitySidsFromName(LPCWSTR CapName, PSID** CapabilityGroupSids, DWORD* CapabilityGroupSidCount, PSID** CapabilitySids, DWORD* CapabilitySidCount)
    assertl_reflect_as(::DeriveCapabilitySidsFromName(CapName, CapabilityGroupSids, CapabilityGroupSidCount, CapabilitySids, CapabilitySidCount));
// GetLengthSid
inline DWORD GetLengthSid(PSID pSid)
    reflect_as(::GetLengthSid(pSid));
// GetSecurityDescriptorLength
inline DWORD GetSecurityDescriptorLength(PSECURITY_DESCRIPTOR pSecurityDescriptor)
    reflect_as(::GetSecurityDescriptorLength(pSecurityDescriptor));
// GetSecurityDescriptorRMControl
inline void GetSecurityDescriptorRMControl(PSECURITY_DESCRIPTOR SecurityDescriptor, PUCHAR RMControl)
    assertl_reflect_as(::GetSecurityDescriptorRMControl(SecurityDescriptor, RMControl) == ERROR_SUCCESS);
// GetSidLengthRequired
inline DWORD GetSidLengthRequired(UCHAR nSubAuthorityCount)
    reflect_as(::GetSidLengthRequired(nSubAuthorityCount));
// SetSecurityDescriptorRMControl
inline void SetSecurityDescriptorRMControl(PSECURITY_DESCRIPTOR SecurityDescriptor, PUCHAR RMControl)
	assertl_reflect_as(::SetSecurityDescriptorRMControl(SecurityDescriptor, RMControl) == ERROR_SUCCESS);
// CveEventWrite
inline void CveEventWrite(PCWSTR CveId, PCWSTR AdditionalDetails)
    assertl_reflect_as(::CveEventWrite(CveId, AdditionalDetails) == ERROR_SUCCESS);
// GetSidSubAuthority
inline PDWORD GetSidSubAuthority(PSID pSid, DWORD nSubAuthority)
    nt_assertl_reflect_to(auto h = ::GetSidSubAuthority(pSid, nSubAuthority), h);
// GetSidIdentifierAuthority
inline PSID_IDENTIFIER_AUTHORITY GetSidIdentifierAuthority(PSID pSid)
    nt_assertl_reflect_to(auto h = ::GetSidIdentifierAuthority(pSid), h);
// GetSidSubAuthorityCount
inline PUCHAR GetSidSubAuthorityCount(PSID pSid)
    nt_assertl_reflect_to(auto h = ::GetSidSubAuthorityCount(pSid), h);
// FreeSid
inline void FreeSid(PSID pSid)
    assertl_reflect_as(!::FreeSid(pSid));
// MapGenericMask
inline void MapGenericMask(PDWORD AccessMask, PGENERIC_MAPPING GenericMapping)
    reflect_to(::MapGenericMask(AccessMask, GenericMapping));
// QuerySecurityAccessMask
inline void QuerySecurityAccessMask(SECURITY_INFORMATION SecurityInformation, LPDWORD DesiredAccess)
    reflect_to(::QuerySecurityAccessMask(SecurityInformation, DesiredAccess));
// SetSecurityAccessMask
inline void SetSecurityAccessMask(SECURITY_INFORMATION SecurityInformation, LPDWORD DesiredAccess)
    reflect_to(::SetSecurityAccessMask(SecurityInformation, DesiredAccess));
#pragma endregion

#pragma region AclAPI.h
#undef SetEntriesInAcl
// SetEntriesInAclA
inline void SetEntriesInAcl(ULONG cCountOfExplicitEntries, PEXPLICIT_ACCESS_A pListOfExplicitEntries, PACL OldAcl, PACL * NewAcl)
    assertl_reflect_as(::SetEntriesInAclA(cCountOfExplicitEntries, pListOfExplicitEntries, OldAcl, NewAcl) == ERROR_SUCCESS);
// SetEntriesInAclW
inline void SetEntriesInAcl(ULONG cCountOfExplicitEntries, PEXPLICIT_ACCESS_W pListOfExplicitEntries, PACL OldAcl, PACL * NewAcl)
    assertl_reflect_as(::SetEntriesInAclW(cCountOfExplicitEntries, pListOfExplicitEntries, OldAcl, NewAcl) == ERROR_SUCCESS);
#undef GetExplicitEntriesFromAcl
// GetExplicitEntriesFromAclA
inline void GetExplicitEntriesFromAcl(PACL pacl, PULONG pcCountOfExplicitEntries, PEXPLICIT_ACCESS_A * pListOfExplicitEntries)
    assertl_reflect_as(::GetExplicitEntriesFromAclA(pacl, pcCountOfExplicitEntries, pListOfExplicitEntries) == ERROR_SUCCESS);
// GetExplicitEntriesFromAclW
inline void GetExplicitEntriesFromAcl(PACL pacl, PULONG pcCountOfExplicitEntries, PEXPLICIT_ACCESS_W * pListOfExplicitEntries)
    assertl_reflect_as(::GetExplicitEntriesFromAclW(pacl, pcCountOfExplicitEntries, pListOfExplicitEntries) == ERROR_SUCCESS);
#undef GetEffectiveRightsFromAcl
// GetEffectiveRightsFromAclA
inline void GetEffectiveRightsFromAcl(PACL pacl, PTRUSTEE_A pTrustee, PACCESS_MASK pAccessRights)
    assertl_reflect_as(::GetEffectiveRightsFromAclA(pacl, pTrustee, pAccessRights) == ERROR_SUCCESS);
// GetEffectiveRightsFromAclW
inline void GetEffectiveRightsFromAcl(PACL pacl, PTRUSTEE_W pTrustee, PACCESS_MASK pAccessRights)
    assertl_reflect_as(::GetEffectiveRightsFromAclW(pacl, pTrustee, pAccessRights) == ERROR_SUCCESS);
#undef GetAuditedPermissionsFromAcl
// GetAuditedPermissionsFromAclA
inline void GetAuditedPermissionsFromAcl(PACL pacl, PTRUSTEE_A pTrustee, PACCESS_MASK pSuccessfulAuditedRights, PACCESS_MASK pFailedAuditRights)
    assertl_reflect_as(::GetAuditedPermissionsFromAclA(pacl, pTrustee, pSuccessfulAuditedRights, pFailedAuditRights) == ERROR_SUCCESS);
// GetAuditedPermissionsFromAclW
inline void GetAuditedPermissionsFromAcl(PACL pacl, PTRUSTEE_W pTrustee, PACCESS_MASK pSuccessfulAuditedRights, PACCESS_MASK pFailedAuditRights)
    assertl_reflect_as(::GetAuditedPermissionsFromAclW(pacl, pTrustee, pSuccessfulAuditedRights, pFailedAuditRights) == ERROR_SUCCESS);
#undef GetNamedSecurityInfo
// GetNamedSecurityInfoA
inline void GetNamedSecurityInfo(LPCSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID * ppsidOwner, PSID * ppsidGroup, PACL * ppDacl, PACL * ppSacl, PSECURITY_DESCRIPTOR * ppSecurityDescriptor)
    assertl_reflect_as(::GetNamedSecurityInfoA(pObjectName, ObjectType, SecurityInfo, ppsidOwner, ppsidGroup, ppDacl, ppSacl, ppSecurityDescriptor) == ERROR_SUCCESS);
// GetNamedSecurityInfoW
inline void GetNamedSecurityInfo(LPCWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID * ppsidOwner, PSID * ppsidGroup, PACL * ppDacl, PACL * ppSacl, PSECURITY_DESCRIPTOR * ppSecurityDescriptor)
    assertl_reflect_as(::GetNamedSecurityInfoW(pObjectName, ObjectType, SecurityInfo, ppsidOwner, ppsidGroup, ppDacl, ppSacl, ppSecurityDescriptor) == ERROR_SUCCESS);
// GetSecurityInfo
inline void GetSecurityInfo(HANDLE handle, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID * ppsidOwner, PSID * ppsidGroup, PACL * ppDacl, PACL * ppSacl, PSECURITY_DESCRIPTOR * ppSecurityDescriptor)
    assertl_reflect_as(::GetSecurityInfo(handle, ObjectType, SecurityInfo, ppsidOwner, ppsidGroup, ppDacl, ppSacl, ppSecurityDescriptor) == ERROR_SUCCESS);
#undef SetNamedSecurityInfo
// SetNamedSecurityInfoA
inline void SetNamedSecurityInfo(LPSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID psidOwner, PSID psidGroup, PACL pDacl, PACL pSacl)
    assertl_reflect_as(::SetNamedSecurityInfoA(pObjectName, ObjectType, SecurityInfo, psidOwner, psidGroup, pDacl, pSacl) == ERROR_SUCCESS);
// SetNamedSecurityInfoW
inline void SetNamedSecurityInfo(LPWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID psidOwner, PSID psidGroup, PACL pDacl, PACL pSacl)
    assertl_reflect_as(::SetNamedSecurityInfoW(pObjectName, ObjectType, SecurityInfo, psidOwner, psidGroup, pDacl, pSacl) == ERROR_SUCCESS);
// SetSecurityInfo
inline void SetSecurityInfo(HANDLE handle, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID psidOwner, PSID psidGroup, PACL pDacl, PACL pSacl)
    assertl_reflect_as(::SetSecurityInfo(handle, ObjectType, SecurityInfo, psidOwner, psidGroup, pDacl, pSacl) == ERROR_SUCCESS);
#undef GetInheritanceSource
// GetInheritanceSourceA
inline void GetInheritanceSource(LPSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, BOOL Container, GUID	** pObjectClassGuids, DWORD GuidCount, PACL pAcl, PFN_OBJECT_MGR_FUNCTS pfnArray, PGENERIC_MAPPING pGenericMapping, PINHERITED_FROMA pInheritArray)
    assertl_reflect_as(::GetInheritanceSourceA(pObjectName, ObjectType, SecurityInfo, Container, pObjectClassGuids, GuidCount, pAcl, pfnArray, pGenericMapping, pInheritArray) == ERROR_SUCCESS);
// GetInheritanceSourceW
inline void GetInheritanceSource(LPWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, BOOL Container, GUID	** pObjectClassGuids, DWORD GuidCount, PACL pAcl, PFN_OBJECT_MGR_FUNCTS pfnArray, PGENERIC_MAPPING pGenericMapping, PINHERITED_FROMW pInheritArray)
    assertl_reflect_as(::GetInheritanceSourceW(pObjectName, ObjectType, SecurityInfo, Container, pObjectClassGuids, GuidCount, pAcl, pfnArray, pGenericMapping, pInheritArray) == ERROR_SUCCESS);
// FreeInheritedFromArray
inline void FreeInheritedFromArray(PINHERITED_FROMW pInheritArray, USHORT AceCnt, PFN_OBJECT_MGR_FUNCTS pfnArray)
    assertl_reflect_as(::FreeInheritedFromArray(pInheritArray, AceCnt, pfnArray) == ERROR_SUCCESS);
#undef TreeResetNamedSecurityInfo
// TreeResetNamedSecurityInfoA
inline void TreeResetNamedSecurityInfo(LPSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID pOwner, PSID pGroup, PACL pDacl, PACL pSacl, BOOL KeepExplicit, FN_PROGRESS fnProgress, PROG_INVOKE_SETTING ProgressInvokeSetting, PVOID Args)
    assertl_reflect_as(::TreeResetNamedSecurityInfoA(pObjectName, ObjectType, SecurityInfo, pOwner, pGroup, pDacl, pSacl, KeepExplicit, fnProgress, ProgressInvokeSetting, Args) == ERROR_SUCCESS);
// TreeResetNamedSecurityInfoW
inline void TreeResetNamedSecurityInfo(LPWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID pOwner, PSID pGroup, PACL pDacl, PACL pSacl, BOOL KeepExplicit, FN_PROGRESS fnProgress, PROG_INVOKE_SETTING ProgressInvokeSetting, PVOID Args)
    assertl_reflect_as(::TreeResetNamedSecurityInfoW(pObjectName, ObjectType, SecurityInfo, pOwner, pGroup, pDacl, pSacl, KeepExplicit, fnProgress, ProgressInvokeSetting, Args) == ERROR_SUCCESS);
#undef TreeSetNamedSecurityInfo
// TreeSetNamedSecurityInfoA
inline void TreeSetNamedSecurityInfo(LPSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID pOwner, PSID pGroup, PACL pDacl, PACL pSacl, DWORD dwAction, FN_PROGRESS fnProgress, PROG_INVOKE_SETTING ProgressInvokeSetting, PVOID Args)
    assertl_reflect_as(::TreeSetNamedSecurityInfoA(pObjectName, ObjectType, SecurityInfo, pOwner, pGroup, pDacl, pSacl, dwAction, fnProgress, ProgressInvokeSetting, Args) == ERROR_SUCCESS);
// TreeSetNamedSecurityInfoW
inline void TreeSetNamedSecurityInfo(LPWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID pOwner, PSID pGroup, PACL pDacl, PACL pSacl, DWORD dwAction, FN_PROGRESS fnProgress, PROG_INVOKE_SETTING ProgressInvokeSetting, PVOID Args)
    assertl_reflect_as(::TreeSetNamedSecurityInfoW(pObjectName, ObjectType, SecurityInfo, pOwner, pGroup, pDacl, pSacl, dwAction, fnProgress, ProgressInvokeSetting, Args) == ERROR_SUCCESS);
#undef BuildSecurityDescriptor
// BuildSecurityDescriptorA
inline void BuildSecurityDescriptor(PTRUSTEE_A pOwner, PTRUSTEE_A pGroup, ULONG cCountOfAccessEntries, PEXPLICIT_ACCESS_A pListOfAccessEntries, ULONG cCountOfAuditEntries, PEXPLICIT_ACCESS_A pListOfAuditEntries, PSECURITY_DESCRIPTOR pOldSD, PULONG pSizeNewSD, PSECURITY_DESCRIPTOR * pNewSD)
    assertl_reflect_as(::BuildSecurityDescriptorA(pOwner, pGroup, cCountOfAccessEntries, pListOfAccessEntries, cCountOfAuditEntries, pListOfAuditEntries, pOldSD, pSizeNewSD, pNewSD) == ERROR_SUCCESS);
// BuildSecurityDescriptorW
inline void BuildSecurityDescriptor(PTRUSTEE_W pOwner, PTRUSTEE_W pGroup, ULONG cCountOfAccessEntries, PEXPLICIT_ACCESS_W pListOfAccessEntries, ULONG cCountOfAuditEntries, PEXPLICIT_ACCESS_W pListOfAuditEntries, PSECURITY_DESCRIPTOR pOldSD, PULONG pSizeNewSD, PSECURITY_DESCRIPTOR * pNewSD)
    assertl_reflect_as(::BuildSecurityDescriptorW(pOwner, pGroup, cCountOfAccessEntries, pListOfAccessEntries, cCountOfAuditEntries, pListOfAuditEntries, pOldSD, pSizeNewSD, pNewSD) == ERROR_SUCCESS);
#undef LookupSecurityDescriptorParts
// LookupSecurityDescriptorPartsA
inline void LookupSecurityDescriptorParts(PTRUSTEE_A * ppOwner, PTRUSTEE_A * ppGroup, PULONG pcCountOfAccessEntries, PEXPLICIT_ACCESS_A * ppListOfAccessEntries, PULONG pcCountOfAuditEntries, PEXPLICIT_ACCESS_A * ppListOfAuditEntries, PSECURITY_DESCRIPTOR pSD)
    assertl_reflect_as(::LookupSecurityDescriptorPartsA(ppOwner, ppGroup, pcCountOfAccessEntries, ppListOfAccessEntries, pcCountOfAuditEntries, ppListOfAuditEntries, pSD) == ERROR_SUCCESS);
// LookupSecurityDescriptorPartsW
inline void LookupSecurityDescriptorParts(PTRUSTEE_W * ppOwner, PTRUSTEE_W * ppGroup, PULONG pcCountOfAccessEntries, PEXPLICIT_ACCESS_W * ppListOfAccessEntries, PULONG pcCountOfAuditEntries, PEXPLICIT_ACCESS_W * ppListOfAuditEntries, PSECURITY_DESCRIPTOR pSD)
    assertl_reflect_as(::LookupSecurityDescriptorPartsW(ppOwner, ppGroup, pcCountOfAccessEntries, ppListOfAccessEntries, pcCountOfAuditEntries, ppListOfAuditEntries, pSD) == ERROR_SUCCESS);
#undef BuildExplicitAccessWithName
// BuildExplicitAccessWithNameA
inline void BuildExplicitAccessWithName(PEXPLICIT_ACCESS_A pExplicitAccess, LPSTR pTrusteeName, DWORD AccessPermissions, ACCESS_MODE AccessMode, DWORD Inheritance)
    reflect_to(::BuildExplicitAccessWithNameA(pExplicitAccess, pTrusteeName, AccessPermissions, AccessMode, Inheritance));
// BuildExplicitAccessWithNameW
inline void BuildExplicitAccessWithName(PEXPLICIT_ACCESS_W pExplicitAccess, LPWSTR pTrusteeName, DWORD AccessPermissions, ACCESS_MODE AccessMode, DWORD Inheritance)
    reflect_to(::BuildExplicitAccessWithNameW(pExplicitAccess, pTrusteeName, AccessPermissions, AccessMode, Inheritance));
#undef BuildTrusteeWithName
// BuildTrusteeWithNameA
inline void BuildTrusteeWithName(PTRUSTEE_A pTrustee, LPSTR pName)
    reflect_to(::BuildTrusteeWithNameA(pTrustee, pName));
// BuildTrusteeWithNameW
inline void BuildTrusteeWithName(PTRUSTEE_W pTrustee, LPWSTR pName)
    reflect_to(::BuildTrusteeWithNameW(pTrustee, pName));
#undef BuildTrusteeWithSid
// BuildTrusteeWithSidA
inline void BuildTrusteeWithSid(PTRUSTEE_A pTrustee, PSID pSid)
    reflect_to(::BuildTrusteeWithSidA(pTrustee, pSid));
// BuildTrusteeWithSidW
inline void BuildTrusteeWithSid(PTRUSTEE_W pTrustee, PSID pSid)
    reflect_to(::BuildTrusteeWithSidW(pTrustee, pSid));
#undef BuildTrusteeWithObjectsAndSid
// BuildTrusteeWithObjectsAndSidA
inline void BuildTrusteeWithObjectsAndSid(PTRUSTEE_A pTrustee, POBJECTS_AND_SID pObjSid, GUID * pObjectGuid, GUID * pInheritedObjectGuid, PSID pSid)
    reflect_to(::BuildTrusteeWithObjectsAndSidA(pTrustee, pObjSid, pObjectGuid, pInheritedObjectGuid, pSid));
// BuildTrusteeWithObjectsAndSidW
inline void BuildTrusteeWithObjectsAndSid(PTRUSTEE_W pTrustee, POBJECTS_AND_SID pObjSid, GUID * pObjectGuid, GUID * pInheritedObjectGuid, PSID pSid)
    reflect_to(::BuildTrusteeWithObjectsAndSidW(pTrustee, pObjSid, pObjectGuid, pInheritedObjectGuid, pSid));
#undef BuildTrusteeWithObjectsAndName
// BuildTrusteeWithObjectsAndNameA
inline void BuildTrusteeWithObjectsAndName(PTRUSTEE_A pTrustee, POBJECTS_AND_NAME_A pObjName, SE_OBJECT_TYPE ObjectType, LPSTR ObjectTypeName, LPSTR InheritedObjectTypeName, LPSTR Name)
    reflect_to(::BuildTrusteeWithObjectsAndNameA(pTrustee, pObjName, ObjectType, ObjectTypeName, InheritedObjectTypeName, Name));
// BuildTrusteeWithObjectsAndNameW
inline void BuildTrusteeWithObjectsAndName(PTRUSTEE_W pTrustee, POBJECTS_AND_NAME_W pObjName, SE_OBJECT_TYPE ObjectType, LPWSTR ObjectTypeName, LPWSTR InheritedObjectTypeName, LPWSTR Name)
    reflect_to(::BuildTrusteeWithObjectsAndNameW(pTrustee, pObjName, ObjectType, ObjectTypeName, InheritedObjectTypeName, Name));
#undef GetTrusteeName
// GetTrusteeNameA
inline LPSTR GetTrusteeName(PTRUSTEE_A pTrustee)
    reflect_as(::GetTrusteeNameA(pTrustee));
// GetTrusteeNameW
inline LPWSTR GetTrusteeName(PTRUSTEE_W pTrustee)
    reflect_as(::GetTrusteeNameW(pTrustee));
#undef GetTrusteeType
// GetTrusteeTypeA
inline TRUSTEE_TYPE GetTrusteeType(PTRUSTEE_A pTrustee)
    reflect_as(::GetTrusteeTypeA(pTrustee));
// GetTrusteeTypeW
inline TRUSTEE_TYPE GetTrusteeType(PTRUSTEE_W pTrustee)
    reflect_as(::GetTrusteeTypeW(pTrustee));
#undef GetTrusteeForm
// GetTrusteeFormA
inline TRUSTEE_FORM GetTrusteeForm(PTRUSTEE_A pTrustee)
    reflect_as(::GetTrusteeFormA(pTrustee));
// GetTrusteeFormW
inline TRUSTEE_FORM GetTrusteeForm(PTRUSTEE_W pTrustee)
    reflect_as(::GetTrusteeFormW(pTrustee));
#pragma endregion

}
#pragma endregion

namespace WX {

#pragma region Security Identifiers
using RID = DWORD;

class SecurityIdentifiersAuthority {
	mutable SID_IDENTIFIER_AUTHORITY sia{ 0 };
	[[maybe_unused]] WORD _ = 0;
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
	SecurityIdentifier(LPCSTR lpszSID) reflect_to(WX::ConvertStringSidToSid(lpszSID, &pSID));
	SecurityIdentifier(LPCWSTR lpszSID) reflect_to(WX::ConvertStringSidToSid(lpszSID, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 1, nSA0, 0, 0, 0, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 2, nSA0, nSA1, 0, 0, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 3, nSA0, nSA1, nSA2, 0, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 4, nSA0, nSA1, nSA2, nSA3, 0, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 5, nSA0, nSA1, nSA2, nSA3, nSA4, 0, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4, RID nSA5)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 6, nSA0, nSA1, nSA2, nSA3, nSA4, nSA5, 0, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4, RID nSA5, RID nSA6)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 7, nSA0, nSA1, nSA2, nSA3, nSA4, nSA5, nSA6, 0, &pSID));
	SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, RID nSA0, RID nSA1, RID nSA2, RID nSA3, RID nSA4, RID nSA5, RID nSA6, RID nSA7)
		reflect_to(WX::AllocateAndInitializeSid(&sia, 8, nSA0, nSA1, nSA2, nSA3, nSA4, nSA5, nSA6, nSA7, &pSID));
	//SecurityIdentifier(SID_IDENTIFIER_AUTHORITY &sia, BYTE nSubAuthorityCount = 0) {
	//	assertl(pSID = (PSID)LocalAlloc(0, GetSidLengthRequired(nSubAuthorityCount)));
	//	assertl(InitializeSid(pSID, &sia, nSubAuthorityCount));
	//}
	~SecurityIdentifier() reflect_to(Delete());
public:
	inline void Delete() reflect_to(Local::AutoFree(pSID));
public:
	inline bool EqualDomain(PSID pSID) reflect_to(BOOL eq, WX::EqualDomainSid(this->pSID, pSID, &eq), eq);
	inline bool EqualPrefix(PSID pSID) reflect_as(WX::EqualPrefixSid(this->pSID, pSID));
	//GetWindowsAccountDomainSid
	//IsWellKnownSid
	template<bool IsUnicode = WX::IsUnicode>
	inline StringX<IsUnicode> toString() const 
		reflect_to(LocalPointer<XCHAR<IsUnicode>> szSID(LocalHeap),
				   WX::ConvertSidToStringSid(this->pSID, &(*szSID)),
				   +CString(&szSID, MaxLenClass));
	inline StringA toStringA() const reflect_as(toString<false>());
	inline StringW toStringW() const reflect_as(toString<true>());

#pragma region Properties
public: // Property - Size
	/* R */ inline DWORD Size() const reflect_as(WX::GetLengthSid(this->pSID));
public: // Property - AuthorityID
	/* R */ inline SecAuthorID AuthorityID() const reflect_as(*WX::GetSidIdentifierAuthority(this->pSID));
public: // Property - AuthorityCount
	/* R */ inline PUCHAR SubAuthorityCount() const reflect_as(WX::GetSidSubAuthorityCount(this->pSID));
#pragma endregion

public:
	inline operator bool() const reflect_as(this->pSID ? IsValidSid(this->pSID) : false);
	inline operator StringA() const reflect_as(toString<false>());
	inline operator StringW() const reflect_as(toString<true>());
	inline PSID operator&() const reflect_as(this->pSID);
	inline SecurityIdentifier operator+() const {
		if (!*this) return O;
		auto size = Size();
		auto npSID = Local::Alloc(size);
		CopySid(size, npSID, pSID);
		return npSID;
	}
	inline RID &operator[](BYTE uSubAuthorityIndex) reflect_as(*WX::GetSidSubAuthority(this->pSID, uSubAuthorityIndex));
	inline RID  operator[](BYTE uSubAuthorityIndex) const reflect_as(*WX::GetSidSubAuthority(this->pSID, uSubAuthorityIndex));
	inline bool operator==(PSID pSID) const reflect_as(WX::EqualSid(this->pSID, pSID));
	inline bool operator!=(PSID pSID) const reflect_as(WX::EqualSid(this->pSID, pSID));
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
public:
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
struct AccessMask {
public:
	WORD SpecificRights;
	BYTE StandardRights;
	BYTE AccessSystemAcl : 1;
private:
	[[maybe_unused]] BYTE _ : 3;
public:
	BYTE GenericAll : 1;
	BYTE GenericExecute : 1;
	BYTE GenericWrite : 1;
	BYTE GenericRead : 1;
};
class AccessControlEntry {
	PACCESS_ALLOWED_ACE pACE = O;
public:
	using Types = AceTypes;
	using Flag = AceFlag;
public:
//	AccessControlEntry(const SecID &sid) : pACE(Local) {}
	AccessControlEntry(Null) {}
public:
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
public:
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
		inline auto &Delete() reflect_to_self(WX::DeleteAce(&acl, dwAceIndex));
		inline bool operator==(Null) const reflect_as(dwAceIndex >= acl.Count());
		inline bool operator!=(Null) const reflect_as(dwAceIndex <  acl.Count());
		inline bool operator==(const Iterator &i) const assertl_reflect_as(&acl == &i.acl, dwAceIndex == i.dwAceIndex);
		inline bool operator!=(const Iterator &i) const assertl_reflect_as(&acl == &i.acl, dwAceIndex != i.dwAceIndex);
		inline Entry *operator&() reflect_to(LPVOID lpACE, WX::GetAce(&acl, dwAceIndex, &lpACE), ref_as<Entry *>(lpACE));
		inline const Entry *operator&() const reflect_to(LPVOID lpACE, WX::GetAce(&acl, dwAceIndex, &lpACE), ref_as<const Entry *>(lpACE));
		inline Entry *operator->() reflect_to(LPVOID lpACE, WX::GetAce(&acl, dwAceIndex, &lpACE), ref_as<Entry *>(lpACE));
		inline const Entry *operator->() const reflect_to(LPVOID lpACE, WX::GetAce(&acl, dwAceIndex, &lpACE), ref_as<const Entry *>(lpACE));
		inline Entry & operator*() reflect_to(LPVOID lpACE, WX::GetAce(&acl, dwAceIndex, &lpACE), *ref_as<Entry *>(lpACE));
		inline const Entry & operator*() const reflect_to(LPVOID lpACE, WX::GetAce(&acl, dwAceIndex, &lpACE), *ref_as<const Entry *>(lpACE));
		inline Iterator &operator++() reflect_to_self(++dwAceIndex);
		inline const Iterator &operator++() const reflect_to_self(++dwAceIndex);
		inline Iterator operator++(int) reflect_as({ acl, dwAceIndex++ });
		inline const Iterator operator++(int) const reflect_as({ acl, dwAceIndex++ });
	};
public:
	AccessControlList() {}
	AccessControlList(Null) {}
	AccessControlList(AccessControlList &acl) : pACL(&acl) reflect_to(acl.pACL = O);
	AccessControlList(AccessControlList &&acl) : pACL(&acl) reflect_to(acl.pACL = O);
	AccessControlList(const AccessControlList &) = delete;
	AccessControlList(std::initializer_list<AccessExplicit> list) reflect_to(SetEntriesInAcl((ULONG)list.size(), (EXPLICIT_ACCESS *)list.begin(), O, &pACL));
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
	/* R */ inline DWORD Count() const reflect_to(ACL_SIZE_INFORMATION asi, WX::GetAclInformation(pACL, &asi, sizeof(asi), AclSizeInformation), asi.AceCount);
public: // Property - Usage
	struct _Usage {
		DWORD used, free;
		inline DWORD Total() const reflect_as(used + free);
	};
	/* R */ inline auto Usage() const reflect_to(ACL_SIZE_INFORMATION asi, WX::GetAclInformation(pACL, &asi, sizeof(asi), AclSizeInformation), _Usage{ asi.AclBytesInUse, asi.AclBytesFree });
public: // Property - Size
	/* R */ inline DWORD Size() const reflect_as(Usage().Total());
public: // Property - Revision
	/* W */ inline auto &Revision(DWORD dwRevision) reflect_to_self(ACL_REVISION_INFORMATION ari{ dwRevision }; WX::GetAclInformation(pACL, &ari, sizeof(ACL_REVISION_INFORMATION), AclRevisionInformation));
	/* R */ inline DWORD Revision() const reflect_to(ACL_REVISION_INFORMATION ari, WX::GetAclInformation(pACL, &ari, sizeof(ACL_REVISION_INFORMATION), AclRevisionInformation), ari.AclRevision);
#pragma endregion
public:
	inline Iterator begin() reflect_as({ self, 0 });
	inline const Iterator begin() const reflect_as({ self, 0 });
	inline Iterator end() reflect_as({ self, Count() });
	inline const Iterator end() const reflect_as({ self, Count() });
public:
	inline PACL &operator&() const reflect_as(pACL);
	inline operator bool() const reflect_as(pACL ? WX::IsValidAcl(pACL) : false);
	inline Iterator operator[](DWORD dwAceIndex) reflect_as({ self, dwAceIndex });
	inline const Iterator operator[](DWORD dwAceIndex) const reflect_as({ self, dwAceIndex });

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
			if_c (_SACL_1_DACL_0_)
				 WX::GetSecurityDescriptorSacl(&sd, &bPresent, &pACL, &bDefault);
			else WX::GetSecurityDescriptorDacl(&sd, &bPresent, &pACL, &bDefault);
			this->bDefault = bDefault, this->bPresent = bPresent;
		}
		xACL(SecurityDescriptor &sd, PACL pACL) : sd(sd), pACL(pACL), bPresent(true), bModified(true) {}
		inline void __Set() {
			if (bModified) {
				if_c (_SACL_1_DACL_0_)
					 WX::SetSecurityDescriptorSacl(&sd, bPresent, pACL, bDefault);
				else WX::SetSecurityDescriptorDacl(&sd, bPresent, pACL, bDefault);
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
			if_c(_GSID_1_OSID_0_)
				 GetSecurityDescriptorGroup(&sd, &pSID, &bDefault);
			else GetSecurityDescriptorOwner(&sd, &pSID, &bDefault);
			this->bDefault = bDefault;
		}
		xSID(SecurityDescriptor &sd, PSID pSID) : sd(sd), pSID(pSID), bModified(true) {}
		inline void __Set() {
			if (bModified) {
				if_c (_GSID_1_OSID_0_)
					 SetSecurityDescriptorGroup(&sd, pSID, bDefault);
				else SetSecurityDescriptorOwner(&sd, pSID, bDefault);
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
	SecurityDescriptor() : pSD(Local::Alloc<SECURITY_DESCRIPTOR>()) reflect_to(WX::InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION));
	SecurityDescriptor(Null) {}
	SecurityDescriptor(SecurityDescriptor &sd) : pSD(sd.pSD) reflect_to(sd.pSD = O);
	SecurityDescriptor(SecurityDescriptor &&sd) : pSD(sd.pSD) reflect_to(sd.pSD = O);
	SecurityDescriptor(const SecurityDescriptor &sd) = delete;
	SecurityDescriptor(LPCSTR lpszDesc) reflect_to(ULONG size; WX::ConvertStringSecurityDescriptorToSecurityDescriptor(lpszDesc, SDDL_REVISION_1, &pSD, &size));
	SecurityDescriptor(LPCWSTR lpszDesc) reflect_to(ULONG size; WX::ConvertStringSecurityDescriptorToSecurityDescriptor(lpszDesc, SDDL_REVISION_1, &pSD, &size));
public:
	inline void Delete() reflect_to(Local::AutoFree(pSD));
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
	/* R */ inline DWORD Size() const reflect_as(WX::GetSecurityDescriptorLength(pSD));
public: // Property - Controls
	/* W */ inline auto &Controls(Control ctl) reflect_to_self(WX::SetSecurityDescriptorControl(pSD, ctl.mask, ctl.flags));
	/* R */ inline Control Controls() const reflect_to(WORD ctl; DWORD rev, WX::GetSecurityDescriptorControl(pSD, &ctl, &rev), ctl);
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
public:
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
#pragma region Properties
public: // Property - Inherit
	/* W */ inline auto &Inherit(bool bInheritHandle) reflect_to_self(this->bInheritHandle = bInheritHandle);
	/* R */ inline bool  Inherit() const reflect_as(this->bInheritHandle);
public: // Property - Descriptor
	/* W */ inline auto &Descriptor(const SecDesc &sd) reflect_to_self(this->lpSecurityDescriptor = &sd);
	/* R */ inline SecDesc &Descriptor() const reflect_as(ref_as<SecDesc>(this->lpSecurityDescriptor));
#pragma endregion
public:
	inline PSECURITY_ATTRIBUTES operator&() const reflect_as(reuse_as<PSECURITY_ATTRIBUTES>(this));
};
using SecAttr = SecurityAttributes;
static inline constexpr SecurityAttributes InheritHandle = true;
#pragma endregion

}
