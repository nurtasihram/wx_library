#include <iostream>

#include "WandX.h"

using namespace WandX;
using namespace std;

#pragma region Test Of Enum
enum_flags(ExampleFlags, int,
		   Default = 0,
		   FlagA = 0x01,
		   FlagB = 0x02,
		   FlagC = 0x04);
enum_flags(ExampleFlags2, ExampleFlags,
		   FlagD = 0x08,
		   FlagE = 0x10,
		   FlagF = 0x20);

enum_class(ExampleEnum, int, 
		   Default = -1,
		   EnumA = 0, EnumB = 1, EnumC = 2);
enum_class(ExampleEnum2, ExampleEnum,
		   EnumD = 3,
		   EnumE = 4,
		   EnumF = 5);

void test_enum() {
	static_assert(ExampleFlags ::EnumEntryCount == 4);
	static_assert(ExampleFlags2::EnumEntryCount == 3);
	static_assert(ExampleEnum  ::EnumEntryCount == 4);
	static_assert(ExampleEnum2 ::EnumEntryCount == 3);

	// Compile-time reflection
	cout << "ExampleFlags:  " << ExampleFlags ::EnumProtoString << endl;
	cout << "ExampleFlags2: " << ExampleFlags2::EnumProtoString << endl;
	cout << "ExampleEnum:   " << ExampleEnum  ::EnumProtoString << endl;
	cout << "ExampleEnum2:  " << ExampleEnum2 ::EnumProtoString << endl;
	cout << "ExampleFlags Names:  "
		<< ExampleFlags::EnumEntryNames[0] << ", "
		<< ExampleFlags::EnumEntryNames[1] << ", "
		<< ExampleFlags::EnumEntryNames[2] << ", "
		<< ExampleFlags::EnumEntryNames[3] << endl;
	cout << "ExampleFlags2 Names: "
		<< ExampleFlags2::EnumEntryNames[0] << ", "
		<< ExampleFlags2::EnumEntryNames[1] << ", "
		<< ExampleFlags2::EnumEntryNames[2] << endl;
	cout << "ExampleEnum Names:   "
		<< ExampleEnum::EnumEntryNames[0] << ", "
		<< ExampleEnum::EnumEntryNames[1] << ", "
		<< ExampleEnum::EnumEntryNames[2] << ", "
		<< ExampleEnum::EnumEntryNames[3] << endl;
	cout << "ExampleEnum2 Names:  "
		<< ExampleEnum2::EnumEntryNames[0] << ", "
		<< ExampleEnum2::EnumEntryNames[1] << ", "
		<< ExampleEnum2::EnumEntryNames[2] << endl;

	// Usage
	ExampleFlags flags = ExampleFlags::FlagA | ExampleFlags::FlagC;
	ExampleEnum  enm = ExampleEnum::EnumB;
	cout << "Flags: " << (int)flags << endl;
	cout << "Enum: " << (int)enm << endl;

	ExampleFlags2 flags2 = ExampleFlags2::FlagD | ExampleFlags2::FlagF;
	ExampleEnum2  enm2 = ExampleEnum2::EnumE;
	cout << "Flags2: " << (int)flags2 << endl;
	cout << "Enum2: " << (int)enm2 << endl;

	ExampleFlags2 combinedFlags = flags | flags2;
	cout << "Combined Flags: " << (int)combinedFlags << endl;

	ExampleFlags defaultFlags;
	ExampleFlags2 defaultFlags2;
	ExampleEnum defaultEnum;
	ExampleEnum2 defaultEnum2;
	cout << "Default Flags:  " << (int)defaultFlags  << endl;
	cout << "Default Flags2: " << (int)defaultFlags2 << endl;
	cout << "Default Enum:   " << (int)defaultEnum   << endl;
	cout << "Default Enum2:  " << (int)defaultEnum2  << endl;
}
#pragma endregion

int main() {
	test_enum();
	return 0;
}
