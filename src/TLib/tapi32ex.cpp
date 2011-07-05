static char *tap32ex_id = 
	"@(#)Copyright (C) 1996-2011 H.Shirouzu		tap32ex.cpp	Ver0.99";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: Application Frame Class
	Create					: 1996-06-01(Sat)
	Update					: 2011-03-27(Sun)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "tlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

BOOL (WINAPI *pCryptAcquireContext)(HCRYPTPROV *, LPCSTR, LPCSTR, DWORD, DWORD);
BOOL (WINAPI *pCryptReleaseContext)(HCRYPTPROV, DWORD);
BOOL (WINAPI *pCryptGenRandom)(HCRYPTPROV, DWORD, BYTE *);

BOOL (WINAPI *pCryptExportKey)(HCRYPTKEY, HCRYPTKEY, DWORD, DWORD, BYTE *, DWORD *);
BOOL (WINAPI *pCryptImportKey)(HCRYPTPROV, CONST BYTE *, DWORD, HCRYPTKEY, DWORD, HCRYPTKEY *);
BOOL (WINAPI *pCryptGenKey)(HCRYPTPROV, ALG_ID, DWORD, HCRYPTKEY *);
BOOL (WINAPI *pCryptGetUserKey)(HCRYPTPROV, DWORD, HCRYPTKEY *);
BOOL (WINAPI *pCryptDestroyKey)(HCRYPTKEY);
BOOL (WINAPI *pCryptGetKeyParam)(HCRYPTKEY, DWORD, BYTE *, DWORD *, DWORD);
BOOL (WINAPI *pCryptSetKeyParam)(HCRYPTKEY, DWORD, BYTE *, DWORD);
BOOL (WINAPI *pCryptEncrypt)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE *, DWORD *, DWORD);
BOOL (WINAPI *pCryptDecrypt)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE *, DWORD *);

BOOL (WINAPI *pCryptCreateHash)(HCRYPTPROV, ALG_ID, HCRYPTKEY, DWORD, HCRYPTHASH *);
BOOL (WINAPI *pCryptDestroyHash)(HCRYPTHASH);
BOOL (WINAPI *pCryptHashData)(HCRYPTHASH, BYTE *, DWORD, DWORD);
BOOL (WINAPI *pCryptSignHash)(HCRYPTHASH, DWORD, LPCSTR, DWORD, BYTE *, DWORD *);
BOOL (WINAPI *pCryptGetHashParam)(HCRYPTHASH, DWORD, BYTE *, DWORD *, DWORD);
BOOL (WINAPI *pCryptSetHashParam)(HCRYPTHASH, DWORD, const BYTE *, DWORD);
BOOL (WINAPI *pCryptVerifySignature)(HCRYPTHASH, CONST BYTE *, DWORD, HCRYPTKEY, LPCSTR, DWORD);

BOOL (WINAPI *pCryptProtectData)(DATA_BLOB*, LPCWSTR, DATA_BLOB*, PVOID,
		CRYPTPROTECT_PROMPTSTRUCT*, DWORD, DATA_BLOB*);
BOOL (WINAPI *pCryptUnprotectData)(DATA_BLOB*, LPWSTR*, DATA_BLOB*, PVOID,
		CRYPTPROTECT_PROMPTSTRUCT*, DWORD, DATA_BLOB*);
BOOL (WINAPI *pCryptStringToBinary) (LPCTSTR, DWORD, DWORD, BYTE *, DWORD *, DWORD *, DWORD *);
BOOL (WINAPI *pCryptBinaryToString)(const BYTE *, DWORD, DWORD, LPTSTR , DWORD *);

NTSTATUS (WINAPI *pNtQueryInformationFile)(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock,
	PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass);

BOOL TLibInit_AdvAPI32()
{
	HMODULE	advdll = ::GetModuleHandle("advapi32.dll");
	pCryptAcquireContext = (BOOL (WINAPI *)(HCRYPTPROV *, LPCSTR, LPCSTR, DWORD, DWORD))
		::GetProcAddress(advdll, "CryptAcquireContextA");
	pCryptGenRandom = (BOOL (WINAPI *)(HCRYPTPROV, DWORD, BYTE *))
		::GetProcAddress(advdll, "CryptGenRandom");
	pCryptGetKeyParam = (BOOL (WINAPI *)(HCRYPTKEY, DWORD, BYTE *, DWORD *, DWORD))
		::GetProcAddress(advdll, "CryptGetKeyParam");
	pCryptSetKeyParam = (BOOL (WINAPI *)(HCRYPTKEY, DWORD, BYTE *, DWORD))
		::GetProcAddress(advdll, "CryptSetKeyParam");
	pCryptCreateHash = (BOOL (WINAPI *)(HCRYPTPROV, ALG_ID, HCRYPTKEY, DWORD, HCRYPTHASH *))
		::GetProcAddress(advdll, "CryptCreateHash");
	pCryptDestroyHash = (BOOL (WINAPI *)(HCRYPTHASH))
		::GetProcAddress(advdll, "CryptDestroyHash");
	pCryptHashData = (BOOL (WINAPI *)(HCRYPTHASH, BYTE *, DWORD, DWORD))
		::GetProcAddress(advdll, "CryptHashData");
	pCryptGetHashParam = (BOOL (WINAPI *)(HCRYPTHASH, DWORD, BYTE *, DWORD *, DWORD))
		::GetProcAddress(advdll, "CryptGetHashParam");
	pCryptSetHashParam = (BOOL (WINAPI *)(HCRYPTHASH, DWORD, const BYTE *, DWORD))
		::GetProcAddress(advdll, "CryptSetHashParam");
	pCryptReleaseContext = (BOOL (WINAPI *)(HCRYPTPROV, DWORD))
		::GetProcAddress(advdll, "CryptReleaseContext");

	pCryptExportKey = (BOOL (WINAPI *)(HCRYPTKEY, HCRYPTKEY, DWORD, DWORD, BYTE *, DWORD *))
		::GetProcAddress(advdll, "CryptExportKey");
	pCryptGetUserKey = (BOOL (WINAPI *)(HCRYPTPROV, DWORD, HCRYPTKEY *))
		::GetProcAddress(advdll, "CryptGetUserKey");
	pCryptEncrypt = (BOOL (WINAPI *)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE *, DWORD *, DWORD))
		::GetProcAddress(advdll, "CryptEncrypt");
	pCryptGenKey = (BOOL (WINAPI *)(HCRYPTPROV, ALG_ID, DWORD, HCRYPTKEY *))
		::GetProcAddress(advdll, "CryptGenKey");
	pCryptDestroyKey = (BOOL (WINAPI *)(HCRYPTKEY))
		::GetProcAddress(advdll, "CryptDestroyKey");
	pCryptImportKey =
		(BOOL (WINAPI *)(HCRYPTPROV, CONST BYTE *, DWORD, HCRYPTKEY, DWORD, HCRYPTKEY *))
		::GetProcAddress(advdll, "CryptImportKey");
	pCryptDecrypt = (BOOL (WINAPI *)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE *, DWORD *))
		::GetProcAddress(advdll, "CryptDecrypt");
	pCryptSignHash = (BOOL (WINAPI *)(HCRYPTHASH, DWORD, LPCSTR, DWORD, BYTE *, DWORD *))
		::GetProcAddress(advdll, "CryptSignHashA");
	pCryptVerifySignature =
		(BOOL (WINAPI *)(HCRYPTHASH, CONST BYTE *, DWORD, HCRYPTKEY, LPCSTR, DWORD))
		::GetProcAddress(advdll, "CryptVerifySignatureA");

	return	TRUE;
}

BOOL TLibInit_Crypt32()
{
	HINSTANCE	cryptdll = ::LoadLibrary("crypt32.dll");

	pCryptProtectData = (BOOL (WINAPI *)(DATA_BLOB*, LPCWSTR, DATA_BLOB*,
		PVOID, CRYPTPROTECT_PROMPTSTRUCT*, DWORD, DATA_BLOB*))
		::GetProcAddress(cryptdll, "CryptProtectData");
	pCryptUnprotectData = (BOOL (WINAPI *)(DATA_BLOB*, LPWSTR*, DATA_BLOB*,
		PVOID, CRYPTPROTECT_PROMPTSTRUCT*, DWORD, DATA_BLOB*))
		::GetProcAddress(cryptdll, "CryptUnprotectData");

	pCryptStringToBinary =
		(BOOL (WINAPI *)(LPCTSTR, DWORD, DWORD, BYTE *, DWORD *, DWORD *, DWORD *))
		::GetProcAddress(cryptdll, "CryptStringToBinaryA");
	pCryptBinaryToString =
		(BOOL (WINAPI *)(const BYTE *, DWORD, DWORD, LPTSTR , DWORD *))
		::GetProcAddress(cryptdll, "CryptBinaryToStringA");

	return	TRUE;
}

BOOL TLibInit_Ntdll()
{
	HINSTANCE	ntdll = ::GetModuleHandle("ntdll.dll");

	pNtQueryInformationFile =
		(NTSTATUS (WINAPI *)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG,
		FILE_INFORMATION_CLASS FileInformationClass))
		::GetProcAddress(ntdll, "NtQueryInformationFile");

	return	TRUE;
}

TDigest::TDigest()
{
	hProv = NULL;
	hHash = NULL;
	updateSize = 0;
}

TDigest::~TDigest()
{
	if (hHash)	pCryptDestroyHash(hHash);
	if (hProv)	pCryptReleaseContext(hProv, 0);
}

BOOL TDigest::Init(TDigest::Type _type)
{
	type = _type;

	if (hProv == NULL) {
		if (!pCryptAcquireContext(&hProv, NULL, MS_DEF_DSS_PROV, PROV_DSS, 0)) {
			pCryptAcquireContext(&hProv, NULL, MS_DEF_DSS_PROV, PROV_DSS, CRYPT_NEWKEYSET);
		}
	}
	if (hHash) {
		pCryptDestroyHash(hHash);
		hHash = NULL;
	}
	updateSize = 0;

	return	pCryptCreateHash(hProv, type == SHA1 ? CALG_SHA : CALG_MD5, 0, 0, &hHash);
}

BOOL TDigest::Reset()
{
	if (updateSize > 0) {
		return	Init(type);
	}
	return	TRUE;
}

BOOL TDigest::Update(void *data, int size)
{
	updateSize += size;
	return	pCryptHashData(hHash, (BYTE *)data, size, 0);
}

BOOL TDigest::GetVal(void *data)
{
	DWORD	size = GetDigestSize();

	return	pCryptGetHashParam(hHash, HP_HASHVAL, (BYTE *)data, &size, 0);
}

BOOL TDigest::GetRevVal(void *data)
{
	if (!GetVal(data)) return FALSE;

	rev_order((BYTE *)data, GetDigestSize());
	return	TRUE;
}

void TDigest::GetEmptyVal(void *data)
{
#define EMPTY_MD5	"\xd4\x1d\x8c\xd9\x8f\x00\xb2\x04\xe9\x80\x09\x98\xec\xf8\x42\x7e"
#define EMPTY_SHA1	"\xda\x39\xa3\xee\x5e\x6b\x4b\x0d\x32\x55\xbf\xef\x95\x60\x18\x90" \
					"\xaf\xd8\x07\x09"

	if (type == MD5) {
		memcpy(data, EMPTY_MD5,  sizeof(EMPTY_MD5));
	}
	else {
		memcpy(data, EMPTY_SHA1, sizeof(EMPTY_SHA1));
	}
}

BOOL TGenRandom(void *buf, int len)
{
	static HCRYPTPROV hProv;

	if (hProv == NULL) {
		if (!pCryptAcquireContext(&hProv, NULL, MS_DEF_DSS_PROV, PROV_DSS, 0)) {
			pCryptAcquireContext(&hProv, NULL, MS_DEF_DSS_PROV, PROV_DSS, CRYPT_NEWKEYSET);
		}
	}

	if (hProv && pCryptGenRandom && pCryptGenRandom(hProv, (DWORD)len, (BYTE *)buf))
		return	TRUE;

	for (int i=0; i < len; i++) {
		*((BYTE *)buf + i) = (BYTE)(rand() >> 8);
	}

	return	 TRUE;
}


#define THASH_RAND_NUM1 757 /* prime number */
#define THASH_RAND_NUM2 769 /* prime number */

/* generated by CryptGenRandom */
int rand_data1[THASH_RAND_NUM1] = {
0x83f16d1d,0x8f9a43ea,0x8137d56a,0xd36d4791,0x9bbfd36b,0xcaae44df,0xb8dfd12d,0x57174455,
0x0bbdac9a,0x1162bcbf,0xde3eefa3,0x9970a137,0x49ba608a,0xc79d6b33,0x3d52b4f2,0x711509e9,
0x2646b1cd,0x7ddade5d,0xfcaaea1a,0x146fec6f,0x1a99d198,0xc3d1c634,0xd1a50845,0x2e06b32b,
0x02807095,0x9afc923a,0x3c5448e7,0xe5b387dc,0x8b289d96,0xb0428716,0xd965f716,0xc6b9f02a,
0x650142c2,0xd4be9b82,0xe70c8d48,0x311ecccf,0x7f73a9eb,0x52477384,0x0f2e6a13,0x6fd35a0c,
0x2af035da,0x9e2ada92,0x5492ee63,0x201a5d29,0x892daad7,0x200d2990,0x8ddf2e7d,0x775d8563,
0x6a09945f,0x1b3a3cf6,0x977f76be,0xba7db608,0x6604c211,0xf480c049,0x76db5fef,0x22615181,
0xb51f2fca,0xd7305926,0x750a5dfc,0x102e7459,0xa64f139d,0x05416e29,0x1b32a4bd,0xb8f76a72,
0x248dbbd5,0xbd5e2fc5,0x82d98566,0x9c52316a,0x89e39f4f,0x0e1e89d5,0x76bb803f,0x34357c5a,
0x39434706,0x80bd3414,0x46fed670,0x897ba8ea,0xbff460f7,0xcdaa0885,0xf2024518,0xc85b7524,
0x38e895ef,0x6bb2d9ae,0x6093be57,0xbd00241e,0x5c8e23fb,0xc75b176f,0x5c016859,0x9dce0784,
0x12114c85,0x808e0480,0x7c739056,0x21f64706,0x173447c8,0xa7ae2f34,0xdd57cd5a,0x02e6d856,
0x57ddc904,0x623a2543,0x4b1e727a,0x70ba1821,0xa0aec212,0x4b96c66e,0xf4865658,0x474dbb7b,
0x70c7d122,0x7e9f63ca,0x015d9bad,0x92a10824,0xcb6561f1,0x8c34c2fa,0x1db47841,0xafe357b2,
0x9ffcedb4,0xacce9e6d,0x22a36d9f,0xaaea180e,0x0b9b5283,0x381e12f0,0x6119d5fa,0x2f394b36,
0xb7ec64d2,0x59fc8f69,0xae328ec0,0x79349901,0x9f3c4e40,0xcafa12a7,0x1e224042,0x5210dbe5,
0xfe3b7711,0x04a81740,0x8620fa1d,0xb8482c88,0x0ae5c4e4,0x73803efc,0x9a0551e7,0xe665e262,
0x0d49c1b2,0x2bfd34d1,0x6624ec5a,0x3c66e9d0,0xc14cffdd,0x16bb3524,0xe2625791,0x9c2e0727,
0xa442f0c1,0x195f5ff0,0xbbfc5c1e,0xebeedeea,0x473adc54,0xcce00cb3,0xab4d130b,0x87acc30d,
0x8e9e0b77,0x2351c837,0x39492be6,0x00806c1a,0x88145505,0x87fbafa3,0x835bb731,0x68434f8d,
0xd7fd168c,0x29b00d49,0xc1fd645e,0x389b531d,0xa6d957df,0x9c995f5e,0x0cec9ce9,0x2de48896,
0x04133f46,0xe76ee748,0x160c0b21,0xb2983583,0xe47cabb8,0x23304d75,0xe25f6248,0x2274c01d,
0x03a1cd6c,0xc6cb44c3,0x641cff47,0xf2bfa660,0x9f66db66,0x15b12437,0xc24b5574,0xca225ed7,
0x410b830b,0x8eb74256,0xbe4cbf9c,0x231f69a8,0xba0ecf62,0xd7f87bdd,0x5b14c532,0xc5ccbaf7,
0x3a00e928,0x31cedd89,0x730c3a87,0xabd193ca,0x8d937e8f,0x3c6de267,0xdadd60f7,0xc555b16a,
0x5353be48,0x80d6ba82,0x623ef108,0x29b87505,0xdc163326,0x0abde254,0x34fd474c,0xf967dee1,
0xa36e119f,0x2dfc5975,0x76421ec5,0xa1aa3ee6,0x47fb621e,0xde104a0d,0xbbd2c2f9,0x3810df16,
0x859d0d84,0x9f5f2f74,0x8b101404,0x9f6bcd1b,0xa06dc932,0x553eed9f,0x665e6cb8,0xe98f8caa,
0x07efd2ce,0xf0faecb2,0x5970501e,0x83ce1b51,0x689ff96f,0x74b9f4e8,0x833b9a2e,0x7506ce11,
0xd04f1919,0x3ff4a56a,0xe577eafa,0x230d0432,0x5fbc3d2e,0xd3d2d05a,0x01daf511,0x2c298a83,
0xee2871e3,0xa81fc823,0x7773838b,0x859bd60c,0x42e750dd,0x0671ccb5,0x5d0f0e44,0x08349890,
0x564e1b13,0x88187f9d,0x7b0481be,0x802b5677,0x7c4efd37,0x81f76d89,0xd40d027d,0x984a7384,
0x78f49b71,0xb5244f77,0xa12159e6,0x5f1a4b09,0xe2f3550c,0xe61a90de,0x3161716f,0xe12cf69c,
0xcb78db9d,0xae31a2a3,0xa9f0961a,0xb5b39ec4,0xb7b8c99b,0x89043c08,0x83daa61d,0x46f54b5c,
0x896cb3a6,0xd97bc43c,0x3af11d39,0xf1c92693,0x8912da39,0x1d0f94aa,0xfe051646,0xa149e75a,
0xeb95491a,0xe0887f04,0x0eaa30c3,0x5c4a24f3,0xb10b7152,0x4a91bbd1,0x79f04264,0xc8aab9b3,
0xd8a0e32c,0xc080a374,0xe586c0e7,0x491a4091,0xc05c0219,0x8a4107ab,0xbe781695,0xe7d52f8a,
0x5362894d,0xa75e62e1,0xe900914f,0x11a1800d,0xbb1cb0e3,0x200a1e96,0x206f409a,0x49f6d722,
0x54dd351b,0xc4566fec,0x77cc85b1,0x233dbc3c,0x74d1848b,0xd9619738,0xb585006f,0x25ad8dec,
0x49a742e9,0x8caecdd4,0xc80e0829,0x253ce2a8,0x87faeaff,0xccfed2d8,0x7a092b02,0xfce50644,
0x0ce33e52,0x9bbc1f4d,0xf0f5e6e8,0xa54f2a69,0xc1a5ab5e,0x319d8b40,0xe7376e63,0xb6642bfc,
0x317fd8e4,0x03174c12,0x9aafc16e,0x6fb06595,0x68dcefde,0x92a3c672,0x5dad62e8,0x6e96a51b,
0xe961bd35,0x8f4e8b4b,0xcc02af7a,0xb4307e73,0xe7ef84bb,0x92e797f9,0xca9ba6bb,0xf3b7f071,
0x847cefd9,0x913ea1e0,0xc367cb13,0x01e41639,0x6474b250,0xfba15fa4,0x87d8b078,0x1b12e507,
0x68b680e0,0xe0f1a8f4,0x760a797e,0x0d755e07,0x15e009fb,0x7025ddf9,0x82a93603,0x70624a3f,
0xe6040d0d,0x479c398c,0x94ab4bd6,0x61a1abaf,0xd04306e6,0xc60d97b2,0x67ef7729,0x45df4f4c,
0xe49e7676,0xd811e7e7,0x5d953b30,0xbc31ed53,0x58ae0c76,0xc3c3fe8b,0xf0133b46,0x66b46471,
0x5ec5caa0,0x3f2fcd10,0x84d34b29,0xdf93fa60,0x08dc000b,0xb85a726e,0x341c51ae,0xd92ab209,
0xc2370b4c,0x6c162eac,0x7b1ced53,0xcb615a1c,0xe533949f,0x5664cc6a,0x89e10f89,0x8cc3cb21,
0x2a7993c3,0xb0495388,0x0c152054,0x9a90060d,0x0a4a73ca,0xf5ea4045,0x788a508f,0x901af6bd,
0xb6fda95f,0x36447609,0xafc8cd4b,0x51d85600,0x02e0b211,0x1f8b81c9,0x08c29120,0x277ac975,
0x196f98a3,0x28524cda,0x62af2cb0,0xd529f178,0xa1f4b017,0xc770b8a6,0xeca6ac2b,0x50ec84eb,
0xaa689a43,0x31934739,0xe70b8338,0x84898138,0x939e84ec,0xbc17182d,0x0736f753,0x0451dc2d,
0x2ed324ae,0x4f6dcaf1,0xbd2f1f0f,0xb4b5656b,0x663b6795,0x12198072,0x5e112975,0x0a2b5b70,
0x393f7991,0x1c32285b,0xad14eb66,0x17b8054c,0xb96acb10,0xc39f99f8,0x8efbc29a,0xb4f29c49,
0xe664a4a4,0x350af3a3,0xada98024,0xc7b3c3fb,0xa77314fc,0xde3c896f,0x5fe7fa94,0x2b8e8556,
0xc2284712,0x16d56132,0xbf57b98e,0x4fc6d518,0xecead967,0xaf112372,0x1c79f121,0x83b89ea3,
0x86831167,0xa57f277a,0x313cfa7f,0x8e8a85d2,0x7933f6e4,0x1d4f1a16,0x4cfa2498,0x61028dcb,
0x9ebeb662,0x68276c98,0x9029cb83,0xf9489fbd,0xaa0db1ec,0x5c934601,0xf6b06029,0xbf58ca0c,
0x311cf9b7,0x3cb80d50,0x23a4f363,0x96384f2c,0xca62e804,0xbf3707b1,0x522ff5ec,0x90945aa4,
0x63779b3b,0x04b7c791,0x4c14d79b,0x6684ed1b,0xffa41088,0xec486d66,0xc7c17dac,0xc5e26402,
0x66a414af,0xb05338c2,0x975f1556,0x48b85fb0,0xb1950f29,0x1693df5c,0xbbebc4a6,0x147aa717,
0x5c734f65,0x7684a4e9,0xb2fa29e9,0x464e001b,0x8144156b,0x7dba42a1,0x317734e0,0x4051eab2,
0x10088e7e,0xf75ab750,0x9c0a7e45,0x518471cd,0x51b4c6fb,0x6877d480,0xeceec069,0xeef3e798,
0x6975bce0,0x42149736,0xb5935a29,0xa2e22668,0xb4cd36a5,0x29211652,0x8c98bebe,0x01c7384a,
0xf2ed70a0,0x5f256cf4,0xf30b6953,0x0483bad5,0x4152579d,0xa8e0ec70,0x0c6c2c90,0x60aad99a,
0xa493afd9,0xe4dc4e3f,0xd49d901c,0x4b62708e,0x000262bf,0xebbc6ea3,0x1618fa0f,0xde380975,
0x2004f481,0xdecfa349,0xac331def,0xf6646b4e,0x4c2cb555,0xb559a36f,0xec112fa1,0xe136ba6f,
0x4503d8c9,0x6e4ea40a,0x84d432ef,0xd3c8e82c,0x758f7802,0xc37b226c,0xfcbafe4c,0x17e1b316,
0x1a2627d7,0x950e28cd,0x6a46ee01,0x230bcefe,0x15958fca,0xf71aad1b,0x2a06831d,0x135bc2b1,
0xcca6aff5,0x60f9dee7,0xbd60652b,0xdc07a8ad,0xd7797298,0x4f965b7e,0x1b25de2b,0xc726ad3f,
0xc73d4448,0x5dbbd65e,0x4810d538,0xb1c6db7c,0x554ea737,0x46d2bf94,0xa7db9cc1,0x6a6d2ded,
0xf8890fbe,0x8b28c3d2,0x9c0fa1d2,0xa37e3f03,0xf7fe82a2,0x23095bd0,0x8115acf8,0xc2e91340,
0x3ca2c6cf,0x90a7a81b,0xaa26761c,0x465cba52,0xf11e955c,0x6d3a7df0,0xb0dc1b40,0x675d4650,
0xc4c01362,0x54cfe021,0x6a891b9b,0xd5bae0b0,0xbcba6c28,0xbf2c3a17,0xb5d97723,0x524711d7,
0xb6b5310d,0x1b9551b0,0xa341666c,0xab33a8a4,0x856efe36,0x3ead5590,0xcf1efdde,0xb1308338,
0x408b4edd,0x7dbff72e,0xeed185e7,0x3ed2c3d2,0xa0200959,0x925e2fd7,0xfcbac04e,0x367e9b6c,
0x9b841f7e,0x3ca16926,0x01be3ac6,0x4cb3c1b3,0x6493460f,0xa9676d0e,0x87369cf8,0x2744649c,
0x736dc3bd,0xc80ec3c2,0x10cca1a8,0x8e2c8095,0x9af8f210,0x80bbd84c,0x67a6435a,0xb69e14a9,
0x06cc32d8,0x63aa64f4,0xa443d8b1,0x5918e881,0x4a2c4204,0x15b60774,0x50f847ab,0x2f4f13ee,
0x40f8c1d6,0xe33f4561,0xfac255af,0x060d6690,0x83586e97,0x83389c0f,0x6536598b,0x9a89198e,
0x81475f9a,0x87337ece,0x8bab6e47,0xe4b20aa0,0x954862f1,0xa7f55367,0x2e0e1aad,0x65438a27,
0x50c9c18f,0x79f33149,0x9d42f8bf,0xc6d51b7e,0x7381a140,0x90551a78,0xd562a5c6,0x5e7ef8a7,
0x2d56b0b0,0xf60bda4a,0x1bbf7276,0x13ca4d74,0xa8553e44,0x7f42f4d3,0xea69f6a3,0x49752831,
0x23723da2,0x234f5de8,0x0b7d3a81,0xf2b5e56f,0x65b0abbb,0x905d7e96,0xcc21c3b8,0x36f28d36,
0x96bb335e,0x93428d20,0xe55b3897,0xc80cd1ac,0x6f88ff78,0x9f66500d,0xcac5fe1c,0x4477be82,
0x50843d4a,0x809e86da,0x251aa38a,0x5736c998,0xc832d161,0x6453cb7f,0x4f556ca9,0x41333009,
0x0a74ddd8,0x79350459,0x458364c3,0x63d3dabb,0x614203d8,0x69e27270,0x382b5996,0x36cf6d45,
0x308751ef,0x4027bc18,0x848e96a3,0xa5d1b4ea,0xf7a0a30d,0xd90fcdc3,0x4bd39ead,0x780b2268,
0xd6582446,0x0bc8e465,0x1e596236,0x20418b93,0x4041560d,0xb2328e65,0x4b238769,0xc52bd2fc,
0x32866d02,0x7117d525,0xa508f2e5,0x950dcef3,0x0c36b726,0x9841482f,0x51d05bcb,0xf2c0b29c,
0xb9acf94a,0x4b72057f,0x102e0249,0x52b8bbc9,0x79dc7033,0x422e65c0,0xa2c21d57,0x332c0d7e,
0xfc655e85,0xce6b61ef,0xa1bf673d,0xa7e18e7a,0x7cb12def,0x7750cfda,0x7a51b8a4,0x95b34e37,
0x20133849,0xb86bc47c,0xffabc8e8,0xa3f90fcf,0x4fe16e3b,0x933272c3,0xd5afec19,0x15a86790,
0x57c9faa9,0xc7772eee,0xb99053fc,0xfdf3eba9,0xfd97a3e3,/*0x7195046c,0xc44a2c13,*/
};

int rand_data2[THASH_RAND_NUM2] = {
0xa99a70d7,0x0e3bff64,0x310259ac,0x10cfeef3,0x8367cf8b,0x5cafab2e,0xe5be5c2c,0xc613cdff,
0xf3280f61,0x1f45e7e6,0x96b1867c,0xd0a376f5,0x2f18be07,0x75267077,0xa1cc0262,0x1e76dc5f,
0xfc35344c,0xc9b8d885,0x6760e957,0x96f4ae65,0x50e3df03,0xf77e3b8c,0x7af9d838,0x4c13eab9,
0xac22160e,0x9a23a02f,0x8c907055,0x4a629c62,0x6087b3e5,0xf3c696cf,0x537ddb04,0x7c3c6bdf,
0x63790239,0x3468833b,0xe336d247,0x72a519a1,0x6438b794,0x9a350fcd,0x1a3297da,0x45112059,
0x9c6b335d,0x54051fb8,0xaa7872c3,0x6f7d965d,0xa6a5c229,0x23198c2b,0x94d0b03c,0x3640e540,
0x8c26e85b,0xecb0970a,0x74e93a49,0xf4b576da,0x6c3f911b,0xb2c5ba4c,0x541b4e85,0xf145531c,
0xf51dd83f,0x8d3b1bd7,0x83eb5942,0x4cb60adf,0x895290ee,0xa24d8c0f,0xe9ef6a86,0xf67585f0,
0x6e7b9213,0xfa6462b0,0x874ea4c2,0x5a704809,0x6a8c51d6,0xe09e7c19,0x1ffbc2c5,0xc0467dc7,
0x3dbe9f57,0x4b9c647a,0xc604b3c0,0x30e6039e,0x64f26eaa,0x068d94c7,0x6a2fa5cd,0x1d291b73,
0xb0c3c154,0xc1964706,0x213f69c2,0x644e4ccd,0xcd02a88b,0x96f2928e,0x867302d8,0x16949c9a,
0x10b6d545,0x238a12ea,0xc051614a,0xc5af7f73,0xec1e984b,0x8d298867,0xed5dafb2,0xcffe21af,
0x121bd3a7,0x85f006d7,0xc21337d2,0xa34a3a71,0x0c508cc1,0xaa3bfc08,0x481aa994,0x79b3baca,
0xdeea59f4,0xc3d08698,0x75dd7c3b,0x585912d0,0x026f4afb,0x967d67ee,0xd33efc37,0x98e5738f,
0x43e00a55,0x2c34c222,0x9c7b8034,0x0ef9ad07,0x909ec9bb,0x72604575,0xd74995d7,0x4a9f7570,
0x88fca31d,0x683f212f,0xf6b0a845,0x24c69154,0x30bdd059,0x4858f353,0xed24fa0d,0xed41b5d7,
0x5f7d63cb,0xc8c94b3e,0xf3605afe,0xe069467f,0xbf21cbc0,0x7477f32d,0xb673fc61,0x3f020fe8,
0xf0519cab,0x47723551,0x3581afda,0xe4321c7b,0xf6274551,0xf344187a,0xda1f7e03,0x87464528,
0x84191473,0x18e5b44f,0x1b323516,0xfd1c3207,0xcb481f43,0x349b30e1,0xfb597740,0x5a596983,
0x3705b516,0xe8d7d730,0xee986bce,0x01b6bb74,0x19bebed9,0xb2f99dac,0x5842a2f7,0x7499e685,
0x9b87aaf8,0xf92f619c,0x0a387f9a,0xa5b9b751,0x0c9923aa,0x0fda4bad,0xd9b72016,0x60141382,
0xacf64a48,0x978d4f12,0xe34c9540,0xbee2e8b7,0x99d1ea5e,0x20f69025,0x4b3eef38,0x413850c4,
0xe91f4526,0xa33a6473,0x5d3e58d4,0xe5058ed5,0x8e4f96e5,0x8c986dfa,0x085545ce,0xba1c9a79,
0x67ac0aef,0x11b0ff31,0x72a316e8,0x88fba36f,0x99b7f8a3,0x838a0f9e,0xbfe7c933,0x7d1f8710,
0xe5c7b7fc,0x080e5883,0xc3e69f26,0x21d4bf53,0x733a226c,0x36296a9a,0x5de47f9c,0x951deb1d,
0x7c41472a,0xbfca14fe,0xc85db49a,0x47628602,0x8b00ceac,0x5637bb37,0xb441d010,0x15c5920d,
0x9b485068,0x3326fdf9,0xcf684cda,0xe7dca6e5,0xfbf0f962,0x0a0a0d0a,0x153e9d8c,0x63de678f,
0x41c1ff1d,0xc00653a6,0x4c3a3c7d,0xcf4ae1d6,0x1ba19315,0x2bdd69e2,0xe111da35,0xc846c4fb,
0xa697d92a,0x68e06597,0x03b6e361,0x4b4b4844,0xdf247c2b,0x8cf9f6e9,0x4b6b0761,0x2d0cfc57,
0xb2ae19ca,0x8f334098,0x16e4f3b8,0x30d871e9,0xcd7cd6ec,0x0dde9c5c,0x9f185789,0x99d70131,
0x8f0cb6e0,0xb9c946dc,0x28f26ae4,0xc057d669,0xeaade933,0xd00c23d0,0x5bc546df,0xa5b3debe,
0x81727aef,0xaac4c603,0xcd7ff71a,0x82b6f723,0x98cb4013,0xea88fc6f,0x57081be8,0x2fb382bf,
0x53b4a1cb,0x8840640d,0x04f5dba6,0x34a816e7,0x6f7c97c7,0xd378df2a,0xb018c109,0x5082215a,
0x36ec9ae1,0x2804685d,0x8c0e93f9,0x72818552,0x5d69e90a,0x1f38b26e,0x5fc040eb,0xbc03016c,
0x12764a68,0x5f7482f9,0x8a9172fd,0x7b1f8a29,0x9d392eef,0x88ab003e,0x58810c0c,0x89491ff1,
0x0c3a52e5,0x5ea71cc9,0x2c93b8fd,0x315a59dc,0xb4baf85d,0x51ac3de9,0x1d177dd1,0x1fcd7268,
0x1853ddd6,0x48c40ea8,0xedd365bf,0x7d1ab3c4,0x5a3a1122,0xfc0165e6,0x5036f139,0x1ec9067a,
0x34de9209,0xb92aea49,0xe572a02b,0x9f866363,0x0bf5439f,0xe62dd59d,0xea2cc649,0x3358ba6f,
0xc17ba822,0xc8ba84f3,0xc608f209,0xcc8da1ec,0x61fe69f2,0x286209b2,0x752f0078,0xf33dabe0,
0x27bbbafb,0x0e5dfbd7,0x6e63cee5,0x28e5288e,0x87c10d41,0x1a442a02,0xf0d48240,0x32514c87,
0xafef4c38,0x59464e58,0x786f9abf,0x9072c748,0x2e4354b0,0xbaf0fa1b,0x3ee3da81,0xb8feb007,
0x65718ce6,0x1600a86b,0x34a56703,0x20441067,0x4a7739d4,0xc918822f,0x1f7c4c59,0xdb7aefeb,
0xb12d7a15,0x5f68bdfc,0x88851801,0x1fd42cbf,0xa379869e,0x0a473fec,0x0d1af4c2,0xc255c0af,
0x27897359,0x234866ec,0x8c1f5cb6,0x5657805b,0x0ed873f9,0xe511246c,0x4d06ea31,0x6dfc99d1,
0xc90b5c34,0x1d16215b,0x6978dee3,0x933289ae,0xb11c06d3,0xd700e7e7,0x4486618a,0x9af8115b,
0xc58c0553,0xda04a053,0x524e0c90,0xa20f7d97,0x42abaa3e,0x0bf790e2,0x9a85cea9,0xf304425d,
0x31b1da91,0x4ff62c44,0x374caff2,0xd4ecb50d,0x5dd0517f,0x7662be4c,0x7b58679d,0x0aa7361d,
0x805168a6,0xce0a363e,0xa85088df,0x2c4af23e,0x924f4275,0x0114a01a,0xbb910738,0xc250884d,
0x58da5d3b,0x341207e7,0x03aa142d,0x7899161f,0x3c24f18b,0x18865e50,0x656ba6a8,0x31a80d30,
0x6b24ecc2,0x5f4931e6,0x901c3e7a,0xdfc40760,0x4f43757e,0xed651c0e,0xbdaff1b0,0x3f2baa63,
0xb2b5c17f,0xf0f7f8aa,0x6c165fe1,0x5042a1a9,0x852e7850,0xa8a871aa,0xc5a15551,0xe8b9488a,
0xe3977f2b,0xd6849e56,0x3e5cd175,0x39957066,0xe22a3f0f,0x175d4ed2,0x3383383a,0xa0d33bda,
0xe36d4f93,0x9cd5bdb5,0x7face3f5,0x67cd6128,0xd84dd459,0x4a907a2d,0x7a14cc5c,0xc25ab6fd,
0x58cf3cc6,0x70191524,0x176c3613,0x80d6c3b7,0x5d630b16,0x84c874e3,0x4dfce0b7,0xc6457b05,
0x0ac3d064,0xca4595e1,0x5f512121,0xedb638df,0x48552e45,0x5102a2eb,0xdb8f5d0b,0xb9cfc11a,
0x59daad06,0xb3536891,0x060c22dd,0x18a0339c,0xab6b9f87,0x27439924,0xb2180df5,0x1d4aac4f,
0x69b336b4,0x777bb79c,0x857a354d,0x83665051,0x4115c822,0x0112db91,0xecb7f774,0xc004b3b6,
0x0b2ca3d8,0xda04cdd3,0x0446aa51,0x9af391ff,0x20941762,0xe5b2dc29,0x54b76d2f,0xaec3afb0,
0xecfd8fee,0x0c0b2f41,0x2a76cefe,0xcd9caff9,0x406888d7,0xaca4c6a4,0x2da160e4,0x8c50a390,
0x9a07333d,0x6db08d90,0xa1efef95,0xad224c56,0xe09907b8,0xc2de0514,0x3d78f11f,0x763689c5,
0xb775c493,0x357184f6,0x2f4f5551,0x1571aec0,0xd46740a2,0xf8e9adbb,0x381905ac,0x7cfc9c50,
0x9eafeb12,0x3afce12b,0x71598537,0xa198eae3,0x393cd128,0x3a689c6e,0xe8ac6464,0xf05efc9a,
0x8db2c6c5,0x4ee129ad,0x1759c9db,0x827b636e,0x70745e79,0x7cadf3d4,0x7961fe5a,0x3c34f1d0,
0x61a1984c,0xf95e6490,0x2bbc2b06,0x45956fb3,0x664dfc37,0x7c6d4d36,0x1175e06e,0xdc399108,
0x1eafd5d5,0x2d09a2b1,0x90d7dd5a,0x19f7dfce,0x9137377a,0x0c0ba128,0xe581acfb,0xecfadf6e,
0xd8923f60,0x45e39440,0xf70d0343,0x6324b057,0x4f9aa32c,0xf3471d88,0xc7052442,0x909183d1,
0x67ff9fef,0x33c5d66c,0xf8addd48,0x821084b1,0xadeb5a2f,0x1536309c,0x3ea31cad,0xdeb7b029,
0xca30bb3f,0xadc0d7b4,0xe90f2f22,0x45655f0e,0xb8d8a594,0xf366af23,0x12a40203,0x6669c6ba,
0x42bcf2db,0x6afa5a32,0x46300ae0,0x1dd82125,0x69e2014f,0x558e6bbf,0xb44dbf78,0xf0714769,
0x9f021ff1,0xf9dcd981,0x7f43c05e,0x8470d112,0x17584e25,0xfa1c57f2,0x4a5e2595,0x0880e5d8,
0x082428a0,0xa18d702d,0xe09d8ea9,0x61397568,0x21681a35,0x141347e3,0xaded5409,0x36f0ea6b,
0xadc34162,0x8957608f,0xfeac1769,0x81f7d698,0x057d29b0,0xb34fce1f,0x0e7cc9d0,0x78bb50a0,
0x614b84e7,0xd543bf1c,0x40864d92,0x11c953be,0x28488665,0xd9f51500,0xa4741451,0x3eb5c669,
0x87e3b2bd,0xd892dd00,0x61211812,0xe5c4237b,0x40942b79,0x927c23b9,0x9fa99e4d,0x40322ceb,
0x33fe12c2,0xc565f691,0x476d3955,0xa662e8b4,0xaf4aa861,0x5d73e65e,0x75f9bde9,0x63261652,
0x94bf5870,0xe3a9f89d,0x7562de78,0x905cbbf0,0x36553a61,0xd9cf2a5a,0xee473c67,0x2aafc6d6,
0xb2b9c0f1,0x6ddd02b4,0x5e5c3829,0xed8adec0,0x716afe6c,0x7506598a,0x2be4bbd2,0x1e3dd772,
0x5056fd16,0xea369392,0x36210c02,0xa37816ce,0x8d0d2f58,0xb6524835,0x8131befe,0x92b1f875,
0xe5c0e3f5,0x6b470c74,0x2f4e0dca,0x863bc8a7,0xd1105591,0x03ee5c43,0x74b6388c,0x00662765,
0x341c4cca,0xd5af530c,0xa3cb805e,0xbfa9692a,0x03eeaf06,0x80ed28aa,0x80515097,0xf7ba6159,
0x3f1214fc,0x45da0f44,0x7afd8d91,0x220ccf35,0x58bb92c4,0x3456bb2b,0x6366fcf6,0x2eb16561,
0x7eb86c35,0x9aacf183,0xdd194ccb,0xeaf3c784,0xe91abf6c,0x7070caca,0xf135d304,0x1a9487db,
0x55ad140d,0x00239050,0x9b9b1b42,0xdcdfd437,0xcbabb060,0x2f6c60bb,0xedc603f0,0xb9cc5d75,
0xe6bd1a25,0x2f33e520,0x65d93ddb,0xfb958d05,0xa3cd8777,0x1cc38a68,0x1839185b,0x004722a0,
0xe3912518,0x5a9b1755,0xdc61cfdb,0xc1693458,0x92f6f8cd,0x0d8cae41,0xdc954978,0xb9785907,
0x4358caea,0xef7bd8d8,0xc0cb5989,0xd43c47a9,0x4bd2daf2,0xf9316311,0x85a42afb,0xd468e8f6,
0xa2133f5b,0x271f4bed,0x4390729c,0x2405a0fd,0xa01cec1a,0x53bd92d2,0x743aaeb8,0x5cef1cd6,
0x94d9ea0a,0x127d04df,0x8d7ae261,0x03132498,0xf81c4790,0x95f3b7be,0x45c5d589,0xb12c5a9d,
0x4b447a91,0xafccc0e1,0xd92b48e4,0xfdeda286,0xb27d3515,0x03f9ee84,0x2d69ba1b,0x96889f64,
0x98783d2c,0x8f5df16c,0xf891e3a7,0x32780504,0x31b6e525,0x680b34b1,0xbb1be889,0x851baa4e,
0x19a93890,0x3179f63e,0xd0d2f757,0x530a8f8e,0x3e34256a,0xf80a4bf4,0xe353e68c,0x96f60026,
0x5291965a,0x1e621492,0x3614690b,0x85dedc84,0xdbc5e725,0xff762b8b,0x8873f574,0x86771df3,
0xf8f9ad3c,0x1fee4a28,0xabcf6785,0x8d3a8def,0x2ecf7680,0x564b8695,0x11c136b4,0xc2a94343,
0x173b68e1,0xe9a66e49,0x8e6980fc,0xa015713e,0xb0639b00,0xb714b41c,0xe878f944,0x4f97269d,
0xb81866c4,0xff8c7235,0x4e96579c,0x10c3552b,0x74bb2d64,0xeed90518,0x6107ccb2,0xa4650c85,
0x3549206d,0x78bfe476,0x0c9a4f8e,0xcc5e655b,0x975f05f3,0xe1f1d64d,0xa62cfc41,0xb6f1fa62,
0xa68bb10d,
};

/*
	手抜きハッシュ生成ルーチン
*/
u_int MakeHash(const void *data, int size, DWORD iv)
{
//#define MAKE_HASH_CORE(sum, data, offset) \
// ((((sum) << 7) | ((sum) >> 25)) ^ data ^ \
// rand_data1[(rand_data2[(offset ^ iv) % THASH_RAND_NUM2] ^ data ^ iv) % THASH_RAND_NUM1])
#define MAKE_HASH_CORE(sum, data, offset) (\
	 	  (((sum) << 7) | ((sum) >> 25)) \
		^ data \
		^ rand_data1[(data ^ offset) % THASH_RAND_NUM1] \
		^ rand_data2[(data) % THASH_RAND_NUM2] \
		)

	u_int	val = rand_data1[(size ^ iv) % THASH_RAND_NUM1]
				^ rand_data2[(size ^ iv) % THASH_RAND_NUM2]
				^ 0xe31a021d;
	u_int	offset = val ^ 0x8f8e053a;
	int		max_loop = size / sizeof(u_int);
	int		mod = size % sizeof(u_int);
	u_int	*p = (u_int *)data;

	for (u_int *end = p + max_loop; p < end; p++) {
		val = MAKE_HASH_CORE(val, *p, offset);
		offset+=11;
	}

	if (mod) {
		u_int	mod_val;
		switch (mod) {
		case 1:	mod_val = 0x01010101; memcpy(&mod_val, p, 1); break;
		case 2:	mod_val = 0x02020202; memcpy(&mod_val, p, 2); break;
		case 3:	mod_val = 0x03030303; memcpy(&mod_val, p, 3); break;
		default:mod_val = 0x04040404; memcpy(&mod_val, p, 4); break; /* not reached */
		}
		val = MAKE_HASH_CORE(val, mod_val, offset + mod);
	}
	return	val;
}

