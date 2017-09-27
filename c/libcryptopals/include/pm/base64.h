#ifndef PM_BASE64_H_
#define PM_BASE64_H_

#include "pm.h"
#include <stdio.h>

extern ssize_t pm_base64_encode(
        char *buffer,
        size_t szBuffer,
        void const *data,
        size_t szData);

extern ssize_t pm_base64_decode(
        void *buffer,
        size_t szBuffer,
        char const *data,
        size_t szData);

#endif
