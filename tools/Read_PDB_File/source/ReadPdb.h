#pragma once

typedef struct {
	long long address;
	char pointer;
}address_type;

typedef struct {
	int num_offset;
	address_type addr_list[10];
	wchar_t* type;
} return_type;

#ifdef __cplusplus
extern "C"
{
#endif
	__declspec(dllimport) void LoadPdb(char* path);

	__declspec(dllimport) void GetVariable(char* var, return_type* ret);

#ifdef __cplusplus
}
#endif
