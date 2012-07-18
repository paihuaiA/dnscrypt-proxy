
#include <config.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "plugin_options.h"
#include "plugin_support.h"

int
plugin_option_parse_str(DCPluginSupportContext * const dcps_context, char *str)
{
    DCPluginSupport *dcps;
    char            *arg;
    char            *plugin_name;
    char            *tmp;

    assert(dcps_context != NULL);
    assert(str != NULL);
    if (*(plugin_name = str) == 0) {
        return -1;
    }
    if ((arg = strchr(str, ',')) != NULL) {
        *arg++ = 0;
    }
    if ((dcps = plugin_support_new(plugin_name)) == NULL) {
        return -1;
    }
    while (arg != NULL) {
        if ((tmp = strchr(arg, ',')) != NULL) {
            *tmp++ = 0;
        }
        if (plugin_support_add_option(dcps, arg) != 0) {
            return -1;
        }
        arg = tmp;
    }
    return plugin_support_context_insert(dcps_context, dcps);
}
