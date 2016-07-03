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

			
			const char* CC_CLEAR		= "\033[0m"; // 关闭所有属性
			const char* CC_HILIGH		= "\033[1m"; // 高亮
			const char* CC_HILIGH_HALF	= "\033[2m"; // 亮度减半
			const char* CC_XIAHUA		= "\033[3m"; // 斜体
			const char* CC_UNDERLINE	= "\033[4m"; // 下划线
			const char* CC_FLASH		= "\033[5m"; // 闪烁
			const char* CC_QFLASH		= "\033[6m"; // 快闪
			const char* CC_INTERV		= "\033[7m"; // 反显
			const char* CC_HIDE			= "\033[8m"; // 消隐
			const char* CC_DELETE		= "\033[9m"; // 中间一道横线
			// 10 - 19 关于字体的
			// 21 - 29 基本与1 - 9正好相反
			// 30 - 37 设置前景色
			// 40 - 47 设置背景色
			const char* CC_BLACK		= "\033[30m"; // : 黑
			const char* CC_RED			= "\033[31m"; // : 红
			const char* CC_GREEN		= "\033[32m"; // : 绿
			const char* CC_YELLOW		= "\033[33m"; // : 黄
			const char* CC_BLUE			= "\033[34m"; // : 蓝色
			const char* CC_PUIPLE		= "\033[35m"; // : 紫色
			const char* CC_DARK_GRAN	= "\033[36m"; // : 深绿
			const char* CC_WHITE		= "\033[37m"; // : 白色
			// 38 打开下划线, 设置默认前景色
			// 39 关闭下划线, 设置默认前景色
			// 40 黑色背景
			// 41 红色背景
			// 42 绿色背景
			// 43 棕色背景
			// 44 蓝色背景
			// 45 品红背景
			// 46 孔雀蓝背景
			// 47 白色背景
			// 48 不知道什么东西
			// 49 设置默认背景色
			// 50 - 89 没用
			// 90 - 109 又是设置前景背景的，比之前的颜色浅
			// \033[nA 光标上移n行
			// \033[nB 光标下移n行
			// \033[nC 光标右移n行
			// \033[nD 光标左移n行
			// \033[y; xH设置光标位置
			// \033[2J 清屏
			// \033[K 清除从光标到行尾的内容
			// \033[s 保存光标位置
			// \033[u 恢复光标位置
			// \033[? 25l 隐藏光标
			// \033[? 25h 显示光标

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
