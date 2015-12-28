#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <fstream>

namespace f3
{
	namespace util
	{
		class Log
		{
			std::ofstream file;

		public:
			enum Scope { LS_ANIMATOR };
			enum Level { L_FATAL_ERROR = -1, L_ERROR = -10, WARNING = -1000, L_INFO = 1, L_MSG = 100 };


			Log(void);
			~Log(void);
			void info(std::string str);
			void write(std::string str);
			void warning(std::string str);
			friend std::string endl();

			friend Log& operator<<(Log& out, const std::string& vec);
			friend Log& operator<<(Log& out, const Log::Level& vec);
			friend Log& operator<<(Log& out, const int& val);
			friend Log& operator<<(Log& out, const unsigned int& val);
			friend Log& operator<<(Log& out, const float& val) /* output */;
			friend Log& endl(Log& out);
			friend Log& info(Log& out);
			friend Log& warning(Log& out);
			friend Log& operator << (Log& stream, Log&  (*pFunc)(Log&) );
		private:
			void write(std::string str, std::ostream &o);
			void Log::flush();
		};

		std::ostream& tab(std::ostream& os);
	}
}

#endif