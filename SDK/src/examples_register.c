
#include <nuttx/config.h>
#include <sys/types.h>

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct sdk_builtin_s
{
  const char *name;         /* Invocation name and as seen under /sbin/ */
  main_t      main;         /* Entry point: main(int argc, char *argv[]) */
};

#include "examples_proto.h"
static struct sdk_builtin_s sdk_builtins[] =
{
# include "examples_list.h"
	{NULL, 0}
};

static const int sdk_builtin_count = sizeof(sdk_builtins) / sizeof(sdk_builtins[0]);

#include <nuttx/module.h>
static int init_sdk_event(void)
{
	int i=0;
	printf("%s %d\n", __func__, __LINE__);
	for(i=0; i<sdk_builtin_count; i++) {
		register_builtin_app(sdk_builtins[i].name, sdk_builtins[i].main);
	}
	return 0;
}
app_entry(init_sdk_event);
