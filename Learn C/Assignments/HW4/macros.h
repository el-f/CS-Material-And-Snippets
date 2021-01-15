#ifndef MACROS_H_
#define MACROS_H_

#define CHECK_RETURN_0(pointer) if (!(pointer)) { return 0; }
#define CHECK_RETURN_NULL(pointer) if (!(pointer)) { return NULL; }
#define CHECK_MSG_RETURN_0(pointer, str) if (!(pointer)) { puts(str); return 0; }


#endif /* MACROS_H_ */
