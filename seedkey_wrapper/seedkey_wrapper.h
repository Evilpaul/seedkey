#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace skwrapper
{
	public enum class VKeyGenResultExOpt
	{
		KGREO_Ok = 0,
		KGREO_BufferToSmall = 1,
		KGREO_SecurityLevelInvalid = 2,
		KGREO_VariantInvalid = 3,
		KGREO_UnspecifiedError = 4
	};

	public ref class seedkeywrapper
	{
	private:
		msclr::interop::marshal_context^ context;

#pragma region conversion functions
		inline const char* convertStringToChar(String^ str);
		inline void convertByteToChar(array<Byte>^ source, unsigned char* dest);
		inline array<Byte>^ convertNativeCharToByteArray(unsigned char* chars, int count);
#pragma endregion

	public:
#pragma region Constructor and Deconstructor
		seedkeywrapper(void);
		~seedkeywrapper(void);
#pragma endregion

		VKeyGenResultExOpt GenerateKeyExOpt(
			[In] array<Byte>^ ipSeedArray,
			[In] const unsigned int iSecurityLevel,
			[In] String^ ipVariant,
			[In] String^ ipOptions,
			[Out] array<Byte>^% iopKeyArray,
			[Out] unsigned int% oActualKeyArraySize);
	};
}
