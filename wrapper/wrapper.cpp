#include "pch.h"
#include "wrapper.h"

#pragma region conversion functions
inline const char* skwrapper::seedkeywrapper::convertStringToChar(String^ str)
{
	return context->marshal_as<const char*>(str);
}

inline void skwrapper::seedkeywrapper::convertByteToChar(array<unsigned char>^ source, unsigned char* dest)
{
	Marshal::Copy(source, 0, IntPtr(const_cast<unsigned char*>(dest)), source->Length);

	return;
}

inline array<unsigned char>^ skwrapper::seedkeywrapper::convertNativeCharToByteArray(unsigned char* chars, int count)
{
	array<unsigned char>^ local_list = gcnew array<unsigned char>(count);

	Marshal::Copy(IntPtr(const_cast<unsigned char*>(chars)), local_list, 0, count);

	return local_list;
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

skwrapper::VKeyGenResultExOpt skwrapper::seedkeywrapper::GenerateKeyExOpt(array<unsigned char>^ ipSeedArray, const unsigned int iSecurityLevel, String^ ipVariant, String^ ipOptions, array<unsigned char>^% iopKeyArray, unsigned int% oActualKeyArraySize)
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
