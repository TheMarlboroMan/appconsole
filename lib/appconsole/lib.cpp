#include <appconsole/lib.h>
#include <sstream>
using namespace appconsole;

std::string appconsole::get_lib_version() {

	std::stringstream ss;
	ss<<MAJOR_VERSION<<"."<<MINOR_VERSION<<"."<<PATCH_VERSION<<"-"<<LIB_VERSION<<"-"<<RELEASE_VERSION;
	return ss.str();
} 
