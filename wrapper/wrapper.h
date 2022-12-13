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

		/// <summary>Function to generate key value from an input seed value</summary>
		/// <returns><typeparam name="VKeyGenResultExOpt">The type returned from this method</typeparam>
		/// <typeparamref name="KGREO_Ok"/> when calculation completes successfully.
		/// <typeparamref name="KGREO_BufferToSmall"/> when <param name="ipSeedArray"/> or <param name="iopKeyArray"/> do not meet size requirements.
		/// <typeparamref name="KGREO_SecurityLevelInvalid"/> when <param name="iSecurityLevel"/> does not match a known security level.
		/// <typeparamref name="KGREO_VariantInvalid"/> when <param name="ipVariant"/> does not match a known variant.
		/// <typeparamref name="KGREO_UnspecifiedError"/>when other errors occur (e.g. parameter value is null pointer).</returns>
		/// <param name="ipSeedArray">The input seed value.</param>
		/// <param name="iSecurityLevel">The security level. This value will always be an odd number to conform to ISO14229-1 requirements.</param>
		/// <param name="ipVariant">String containing the name of the ECU variant.</param>
		/// <param name="ipOptions">String containing options to be applied to the calculation.</param>
		/// <param name="iopKeyArray">The output key value.</param>
		/// <param name="oActualKeyArraySize">The actual size of the calculated key value.</param>
		VKeyGenResultExOpt GenerateKeyExOpt(
			[In] array<Byte>^ ipSeedArray,
			[In] const unsigned int iSecurityLevel,
			[In] String^ ipVariant,
			[In] String^ ipOptions,
			[Out] array<Byte>^% iopKeyArray,
			[Out] unsigned int% oActualKeyArraySize);
	};
}
