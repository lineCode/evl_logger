#if _PF_WINDOWS_
#include <wtypes.h>
#endif 

#include <evl_logger/win_console_color.h>
#include <cstdio>

namespace evl
{
	namespace utility
	{

		static ColorTypeMapCode g_color_type_map_code;

#if _PF_WINDOWS_

		//Standard Output Handle
		static HANDLE std_con_out;

		//If colorprotect is true, background and text colors will never be the same
		static bool colorprotect = false;


		/*
		textcol - current text color
		backcol - current back color
		deftextcol - original text color
		defbackcol - original back color
		*/
		static ConsoleColorType textcol, backcol, deftextcol, defbackcol;

		void update_colors()
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(std_con_out, &csbi);
			textcol = ConsoleColorType(csbi.wAttributes & 15);
			backcol = ConsoleColorType((csbi.wAttributes & 0xf0) >> 4);
		}

		void set_color(ConsoleColorType textcolor, ConsoleColorType backcolor)
		{
			if (colorprotect && textcolor == backcolor)
				return;

			textcol = textcolor;
			backcol = backcolor;
			unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
			SetConsoleTextAttribute(std_con_out, wAttributes);
		}

		void set_text_color(ConsoleColorType textcolor)
		{
			if (colorprotect && textcolor == backcol)
				return;

			textcol = textcolor;
			unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
			SetConsoleTextAttribute(std_con_out, wAttributes);
		}

		void set_back_color(ConsoleColorType backcolor)
		{
			if (colorprotect && textcol == backcolor)
				return;

			backcol = backcolor;
			unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
			SetConsoleTextAttribute(std_con_out, wAttributes);
		}

		void init_console_color()
		{
			std_con_out = GetStdHandle(STD_OUTPUT_HANDLE);
			update_colors();
			deftextcol = textcol; defbackcol = backcol;

			
			const char* CC_CLEAR		= "\033[0m"; // �ر���������
			const char* CC_HILIGH		= "\033[1m"; // ����
			const char* CC_HILIGH_HALF	= "\033[2m"; // ���ȼ���
			const char* CC_XIAHUA		= "\033[3m"; // б��
			const char* CC_UNDERLINE	= "\033[4m"; // �»���
			const char* CC_FLASH		= "\033[5m"; // ��˸
			const char* CC_QFLASH		= "\033[6m"; // ����
			const char* CC_INTERV		= "\033[7m"; // ����
			const char* CC_HIDE			= "\033[8m"; // ����
			const char* CC_DELETE		= "\033[9m"; // �м�һ������
			// 10 - 19 ���������
			// 21 - 29 ������1 - 9�����෴
			// 30 - 37 ����ǰ��ɫ
			// 40 - 47 ���ñ���ɫ
			const char* CC_BLACK		= "\033[30m"; // : ��
			const char* CC_RED			= "\033[31m"; // : ��
			const char* CC_GREEN		= "\033[32m"; // : ��
			const char* CC_YELLOW		= "\033[33m"; // : ��
			const char* CC_BLUE			= "\033[34m"; // : ��ɫ
			const char* CC_PUIPLE		= "\033[35m"; // : ��ɫ
			const char* CC_DARK_GRAN	= "\033[36m"; // : ����
			const char* CC_WHITE		= "\033[37m"; // : ��ɫ
			// 38 ���»���, ����Ĭ��ǰ��ɫ
			// 39 �ر��»���, ����Ĭ��ǰ��ɫ
			// 40 ��ɫ����
			// 41 ��ɫ����
			// 42 ��ɫ����
			// 43 ��ɫ����
			// 44 ��ɫ����
			// 45 Ʒ�챳��
			// 46 ��ȸ������
			// 47 ��ɫ����
			// 48 ��֪��ʲô����
			// 49 ����Ĭ�ϱ���ɫ
			// 50 - 89 û��
			// 90 - 109 ��������ǰ�������ģ���֮ǰ����ɫǳ
			// \033[nA �������n��
			// \033[nB �������n��
			// \033[nC �������n��
			// \033[nD �������n��
			// \033[y; xH���ù��λ��
			// \033[2J ����
			// \033[K ����ӹ�굽��β������
			// \033[s ������λ��
			// \033[u �ָ����λ��
			// \033[? 25l ���ع��
			// \033[? 25h ��ʾ���

			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_BLACK			 ] = CC_BLACK;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_BLUE		 ] = CC_BLUE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_GREEN	 ] = CC_GREEN;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_AQUA		 ] = CC_GREEN;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPEDARK_CYAN		 ] = CC_GREEN;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_RED		 ] = CC_RED;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_PURPLE	 ] = CC_PUIPLE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_PINK		 ] = CC_PUIPLE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_MAGENTA 	 ] = CC_PUIPLE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_YELLOW	 ] = CC_YELLOW;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_DARK_WHITE     ] = CC_WHITE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_GRAY			 ] = CC_WHITE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_BLUE			 ] = CC_BLUE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_GREEN			 ] = CC_GREEN;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_AQUA			 ] = CC_GREEN;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_CYAN			 ] = CC_GREEN;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_RED			 ] = CC_RED;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_PURPLE	     ] = CC_PUIPLE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_PINK			 ] = CC_PUIPLE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_MAGENTA		 ] = CC_PUIPLE;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_YELLOW		 ] = CC_YELLOW;
			g_color_type_map_code.color_type_map_color[CONSOLE_COLOR_TYPE_WHITE			 ] = CC_WHITE;
		}
#elif _PF_LINUX_
        ///////////////////////


		//Standard Output Handle
		// static HANDLE std_con_out;

		//If colorprotect is true, background and text colors will never be the same
		static bool colorprotect = false;

		/*
		textcol - current text color
		backcol - current back color
		deftextcol - original text color
		defbackcol - original back color
		*/
		static ConsoleColorType textcol, backcol, deftextcol, defbackcol;

		void update_colors()
		{
			// CONSOLE_SCREEN_BUFFER_INFO csbi;
			// GetConsoleScreenBufferInfo(std_con_out, &csbi);
			// textcol = ConsoleColorType(csbi.wAttributes & 15);
			// backcol = ConsoleColorType((csbi.wAttributes & 0xf0) >> 4);
		}

		void set_color(ConsoleColorType textcolor, ConsoleColorType backcolor)
		{
			if (colorprotect && textcolor == backcolor)
			 	return;

			// textcol = textcolor;
			// backcol = backcolor;
			// unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
			// SetConsoleTextAttribute(std_con_out, wAttributes);
		}

		void set_text_color(ConsoleColorType textcolor)
		{
			if (colorprotect && textcolor == backcol)
				return;

			if(textcolor > MAX_CONSOLE_COLOR_COUNT)
				return;

			printf(g_color_type_map_code.color_type_map_color[textcolor]);
		}

		void set_back_color(ConsoleColorType backcolor)
		{
			if (colorprotect && textcol == backcolor)
				return;

			// backcol = backcolor;
			// unsigned short wAttributes = ((unsigned int)backcol << 4) | (unsigned int)textcol;
			// SetConsoleTextAttribute(std_con_out, wAttributes);
		}

		void init_console_color()
		{
			// std_con_out = GetStdHandle(STD_OUTPUT_HANDLE);
			// update_colors();
			// deftextcol = textcol; defbackcol = backcol;
		}
#endif // _PF_
	} // namespace utility
}	//end of namespace evl
