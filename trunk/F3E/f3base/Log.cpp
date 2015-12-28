#include "Stdafx.h"

#include "Log.h"
#include <time.h>
#include <sstream>

namespace f3
{
	namespace util
	{
		Log::Log(void)
		{
			file.open("logs/file.txt", std::ios::out);
		}

		Log::~Log(void)
		{
		}

		void Log::write(std::string str)
		{
			write(str, std::cout);
			write(str, file);
			file.flush();
		}

		void Log::flush()
		{
			std::cout.flush();
			file.flush();
		}					

		void Log::write(std::string str, std::ostream &o)
		{
			o << str;
		}

		void Log::warning( std::string str )
		{
			(*this) << f3::util::warning << str << f3::util::endl;
		}

		void Log::info( std::string str )
		{
			(*this) << f3::util::info << str << f3::util::endl;
		}

		Log& operator<<(Log& out, const std::string& vec) // output
		{
			out.write(vec);

			return out;
		}

		Log& operator<<(Log& out, const Log::Level& vec) // output
		{
			std::ostringstream ss;
			ss << "[";
			ss.width(3);
			ss << vec << "] ";
			out.write(ss.str());
			return out;
		}

		Log& operator<<(Log& out, const int& val) // output
		{
			std::ostringstream ss;
			ss << val;
			out.write(ss.str());
			return out;
		}

		Log& operator<<(Log& out, const unsigned int& val) // output
		{
			std::ostringstream ss;
			ss << val;
			out.write(ss.str());
			return out;
		}

		Log& operator<<(Log& out, const float& val) // output
		{
			std::ostringstream ss;
			ss << val;
			out.write(ss.str());
			return out;
		}

		Log& endl(Log& out)
		{	// insert newline and flush byte stream
			out.write("\n");
			out.flush();
			return (out);
		}

		Log& info(Log& out)
		{	// insert newline and flush byte stream
			out.write(" [INFO] ");

			return (out);
		}

		Log& warning(Log& out)
		{
			out.write(" [WARNING] ");
			return (out);
		}

		Log& operator << (Log& stream, Log&  (*pFunc)(Log&) )
		{
			return pFunc(stream);
		} 

		std::ostream& tab(std::ostream& os) { 

			return os << '\t' ; 

		} 
	}

}