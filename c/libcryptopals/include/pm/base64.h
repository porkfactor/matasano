#ifndef PM_BASE64_H_
#define PM_BASE64_H_

#include "pm.h"
#include <stdint.h>
#include <stdio.h>

#define PM_BASE64_DECODED_SIZE(x)       ((PM_ROUND_UP(x, 4UL) * 3UL) / 4UL)
#define PM_BASE64_ENCODED_SIZE(x)       ((PM_ROUND_UP(x, 3UL) * 4UL) / 3UL)

enum pm_base64_encoding_e
{
	PM_BASE64_RFC3458,
	PM_BASE64_RFC4648,
	PM_BASE64_RFC7515,
	PM_BASE64_XML_IDENTIFIER,
	PM_BASE64_XML_NAME_TOKEN,
};

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
