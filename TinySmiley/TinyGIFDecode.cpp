#include "stdafx.h"
#include "TinyGIFDecode.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

namespace Tiny
{
	extern "C"
	{
		extern unsigned char	*stbi_load_gif_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp, size_t* count);
		extern unsigned char	*stbi_load_gif_from_file(FILE *f, int *x, int *y, int *comp, int req_comp, size_t* count);
		extern void				stbi_image_free(void *retval_from_stbi_load);
	};

	TinyGIFDecode::TinyGIFDecode()
	{
	}


	TinyGIFDecode::~TinyGIFDecode()
	{
	}
}


