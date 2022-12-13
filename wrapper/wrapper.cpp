#include "pch.h"
#include "wrapper.h"

extern "C"
{
#include "..\seedkey\GenerateKeyExOpt.h"
}

#pragma region conversion functions
inline const char* skwrapper::seedkeywrapper::convertStringToChar(String^ str)
{
	return context->marshal_as<const char*>(str);
}

inline void skwrapper::seedkeywrapper::convertByteToChar(array<Byte>^ source, unsigned char* dest)
{
	for (int i = 0; i < source->Length; i++)
	{
		dest[i] = (unsigned char)source[i];
	}
	return;
}

inline array<Byte>^ skwrapper::seedkeywrapper::convertNativeCharToByteArray(unsigned char* chars, int count)
{
	Collections::Generic::List<Byte>^ local_list = gcnew Collections::Generic::List<Byte>();

	for (int i = 0; i < count; i++)
	{
		local_list->Add((Byte)chars[i]);
	}

	return local_list->ToArray();
}
#pragma endregion

#pragma region Constructor and Deconstructor
skwrapper::seedkeywrapper::seedkeywrapper(void)
{
	context = gcnew msclr::interop::marshal_context();
}

skwrapper::seedkeywrapper::~seedkeywrapper(void)
{
	context->~marshal_context();
}
#pragma endregion

skwrapper::VKeyGenResultExOpt skwrapper::seedkeywrapper::GenerateKeyExOpt(array<Byte>^ ipSeedArray, const unsigned int iSecurityLevel, String^ ipVariant, String^ ipOptions, array<Byte>^% iopKeyArray, unsigned int% oActualKeyArraySize)
{
	VKeyGenResultExOpt retVal = VKeyGenResultExOpt::KGREO_Ok;
	unsigned int iSeedArraySize = ipSeedArray->Length;
	unsigned char* local_ipSeedArray = (unsigned char*)malloc(sizeof(unsigned char) * iSeedArraySize);
	const char* local_ipVariant = convertStringToChar(ipVariant);
	const char* local_ipOptions = convertStringToChar(ipOptions);
	unsigned int iMaxKeyArraySize = iopKeyArray->Length;
	unsigned char* local_iopKeyArray = (unsigned char*)malloc(sizeof(unsigned char) * iMaxKeyArraySize);
	unsigned int local_oActualKeyArraySize = 0;

	convertByteToChar(ipSeedArray, local_ipSeedArray);

	retVal = (VKeyGenResultExOpt)::GenerateKeyExOpt(local_ipSeedArray, iSeedArraySize, iSecurityLevel, local_ipVariant, local_ipOptions, local_iopKeyArray, iMaxKeyArraySize, local_oActualKeyArraySize);

	iopKeyArray = convertNativeCharToByteArray(local_iopKeyArray, iMaxKeyArraySize);
	oActualKeyArraySize = local_oActualKeyArraySize;

	free(local_iopKeyArray);
	free(local_ipSeedArray);

	return retVal;
}
