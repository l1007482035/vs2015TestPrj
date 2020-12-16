// testfreetype.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "testfreetype.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef _DEBUG
#pragma comment(lib,"../vc2015/Debug/freetyped.lib")
#else
#pragma comment(lib,"../vc2015/Release/freetype.lib")
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;



#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H


#define WIDTH   640
#define HEIGHT  480


/* origin is the upper left corner */
unsigned char image[HEIGHT][WIDTH];


/* Replace this function with something useful. */

void
draw_bitmap(FT_Bitmap*  bitmap,
	FT_Int      x,
	FT_Int      y)
{
	FT_Int  i, j, p, q;
	FT_Int  x_max = x + bitmap->width;
	FT_Int  y_max = y + bitmap->rows;


	/* for simplicity, we assume that `bitmap->pixel_mode' */
	/* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

	for (i = x, p = 0; i < x_max; i++, p++)
	{
		for (j = y, q = 0; j < y_max; j++, q++)
		{
			if (i < 0 || j < 0 ||
				i >= WIDTH || j >= HEIGHT)
				continue;

			image[j][i] |= bitmap->buffer[q * bitmap->width + p];
		}
	}
}


void
show_image(void)
{
	int  i, j;


	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
			putchar(image[i][j] == 0 ? ' '
				: image[i][j] < 128 ? '+'
				: '*');
		putchar('\n');
	}
}

#include <locale.h>

int main()
{
	setlocale(LC_CTYPE, "");
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 在此处为应用程序的行为编写代码。

			FT_Library    library;
			FT_Face       face;

			FT_GlyphSlot  slot;
			FT_Matrix     matrix;                 /* transformation matrix */
			FT_Vector     pen;                    /* untransformed origin  */
			FT_Error      error;

			char*         filename;
			char*         text;

			double        angle;
			int           target_height;
			int           n, num_chars;

			filename = "C:\\Windows\\Fonts\\STLITI.TTF";                           /* first argument     */
			text = "helloworld";                           /* second argument    */
			num_chars = strlen(text);
			angle = (25.0 / 360) * 3.14159 * 2;      /* use 25 degrees     */
			target_height = HEIGHT;

			error = FT_Init_FreeType(&library);              /* initialize library */
															 /* error handling omitted */

			error = FT_New_Face(library, filename, 0, &face);/* create face object */
															 /* error handling omitted */

															 /* use 50pt at 100dpi */
			error = FT_Set_Char_Size(face, 50 * 64, 0,
				100, 0);                /* set character size */
										/* error handling omitted */

										/* cmap selection omitted;                                        */
										/* for simplicity we assume that the font contains a Unicode cmap */

			slot = face->glyph;

			/* set up matrix */
			matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
			matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
			matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
			matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

			/* the pen position in 26.6 cartesian space coordinates; */
			/* start at (300,200) relative to the upper left corner  */
			pen.x = 300 * 64;
			pen.y = (target_height - 200) * 64;

			for (n = 0; n < num_chars; n++)
			{
				/* set transformation */
				FT_Set_Transform(face, &matrix, &pen);

				/* load glyph image into the slot (erase previous one) */
				error = FT_Load_Char(face, text[n], FT_LOAD_RENDER);
				if (error)
					continue;                 /* ignore errors */

											  /* now, draw to our target surface (convert position) */
				draw_bitmap(&slot->bitmap,
					slot->bitmap_left,
					target_height - slot->bitmap_top);

				/* increment pen position */
				pen.x += slot->advance.x;
				pen.y += slot->advance.y;
			}

			show_image();

			FT_Done_Face(face);
			FT_Done_FreeType(library);




        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}
