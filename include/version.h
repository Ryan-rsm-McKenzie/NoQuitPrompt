#ifndef	NOQUITPROMPT_VERSION_INCLUDED
#define NOQUITPROMPT_VERSION_INCLUDED

#define NOQUITPROMPT_MAKE_STR_HELPER(x) #x
#define NOQUITPROMPT_MAKE_STR(x) NOQUITPROMPT_MAKE_STR_HELPER(x)

#define NOQUITPROMPT_VERSION_MAJOR		1
#define NOQUITPROMPT_VERSION_MINOR		2
#define NOQUITPROMPT_VERSION_PATCH		2
#define NOQUITPROMPT_VERSION_BETA		0
#define NOQUITPROMPT_VERSION_VERSTRING	NOQUITPROMPT_MAKE_STR(NOQUITPROMPT_VERSION_MAJOR) "." NOQUITPROMPT_MAKE_STR(NOQUITPROMPT_VERSION_MINOR) "." NOQUITPROMPT_MAKE_STR(NOQUITPROMPT_VERSION_PATCH) "." NOQUITPROMPT_MAKE_STR(NOQUITPROMPT_VERSION_BETA)

#endif
