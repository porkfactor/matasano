#include <pm/base64.h>

static char const encode_base64_xml_identifier[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_:";
static char const encode_base64_xml_name_token[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.-";
static char const encode_base64_rfc3458[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char const encode_base64_url[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static uint8_t const decode_base64_rfc3458[128] = {
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x00 - 0x07 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x08 - 0x0f */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x10 - 0x17 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x18 - 0x1f */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x20 - 0x27 */
    0x80, 0x80, 0x80, 0x3e, 0x80, 0x80, 0x80, 0x3f, /* 0x28 - 0x2f */
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, /* 0x30 - 0x37 */
    0x3c, 0x3d, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, /* 0x38 - 0x3f */
    0x80, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, /* 0x40 - 0x47 */
    0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, /* 0x48 - 0x4f */
    0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, /* 0x50 - 0x57 */
    0x17, 0x18, 0x19, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x58 - 0x5f */
    0x80, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, /* 0x60 - 0x67 */
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, /* 0x68 - 0x6f */
    0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, /* 0x70 - 0x77 */
    0x31, 0x32, 0x33, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x78 - 0x7f */
};

static inline size_t base64Encode(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData,
        char const *base64characters)
{
    size_t dataOffset = 0;
    size_t szWritten = 0;
    uint16_t bits = 0;
    uint8_t bits_remaining = 0;

    while(dataOffset < szData)
    {
        bits = (uint16_t)((bits << 8U) | data[dataOffset]);
        bits_remaining = (uint8_t)(bits_remaining + 8U);

        while(bits_remaining >= 6U)
        {
            bits_remaining = (uint8_t)(bits_remaining - 6U);
            uint8_t i = (bits >> bits_remaining) & 0x3f;
            buffer[szWritten++] = base64characters[i];
        }

        dataOffset++;
    }

    if(bits_remaining > 0U)
    {
        buffer[szWritten++] = base64characters[((bits << (6U - bits_remaining)) & 0x3f)];
    }

    buffer[szWritten] = 0;

    return szWritten;
}

static inline size_t base64EncodePadded(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData,
        char const *base64characters,
        char padCharacter)
{
    size_t szWritten = base64Encode(buffer, szBuffer, data, szData, base64characters);

    while((szWritten % 4) != 0)
    {
        buffer[szWritten++] = padCharacter;
    }

    buffer[szWritten] = 0;

    return szWritten;
}

static inline size_t base64encode_xml_identifier(char *buffer, size_t szBuffer, uint8_t const *data, size_t szData)
{
    return base64Encode(buffer, szBuffer, data, szData, encode_base64_xml_identifier);
}

static inline size_t base64encode_xml_name_token(char *buffer, size_t szBuffer, uint8_t const *data, size_t szData)
{
    return base64Encode(buffer, szBuffer, data, szData, encode_base64_xml_name_token);
}

static inline size_t base64encode_rfc3548(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData)
{
    return base64EncodePadded(buffer, szBuffer, data, szData, encode_base64_rfc3458, '=');
}

static inline size_t base64encode_rfc4648(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData)
{
    return base64EncodePadded(buffer, szBuffer, data, szData, encode_base64_url, '=');
}

static inline size_t base64encode_rfc7515(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData)
{
    return base64Encode(buffer, szBuffer, data, szData, encode_base64_url);
}

static inline size_t base64decode(
        uint8_t *buffer,
        size_t szBuffer,
        char const *data,
        size_t szData,
        uint8_t const *decode)
{
    size_t szWritten = 0UL;
    size_t count = 0UL;
    size_t pad = 0UL;
    uint8_t block[4];

    size_t i;
    for(i = 0; i < szData; i++)
    {
        uint8_t tmp = decode[(uint8_t)data[i]];
        if(likely(tmp != 0x80))
        {
            if(unlikely(data[i] == '='))
            {
                pad++;
            }

            block[count] = tmp;
            count++;

            if(count == 4)
            {
                buffer[szWritten++] = (uint8_t)((block[0] << 2U) | (block[1] >> 4U));
                buffer[szWritten++] = (uint8_t)((block[1] << 4U) | (block[2] >> 2U));
                buffer[szWritten++] = (uint8_t)((block[2] << 6U) | block[3]);
                count = 0;
                szWritten -= pad;
            }
        }
        else
        {
            continue;
        }
    }

    return szWritten;
}

static inline size_t base64decode_rfc3458(
        uint8_t *buffer,
        size_t szBuffer,
        char const *data,
        size_t szData)
{
    return base64decode(buffer, szBuffer, data, szData, decode_base64_rfc3458);
}

ssize_t pm_base64_encode(
        char *buffer,
        size_t szBuffer,
        void const *data,
        size_t szData)
{
    ssize_t rv = -1;

    if(likely(szBuffer >= PM_BASE64_ENCODED_SIZE(szData)))
    {
        rv = (ssize_t)base64encode_rfc3548(buffer, szBuffer, (uint8_t const *) (data), szData);
    }

    return rv;
}

ssize_t pm_base64_encode_strict(
        char *buffer,
        size_t szBuffer,
        void const *data,
        size_t szData,
        enum pm_base64_encoding_e encoding)
{
    ssize_t rv = -1;

    if(likely(szBuffer >= PM_BASE64_ENCODED_SIZE(szData)))
    {
        switch(encoding)
        {
        case PM_BASE64_RFC3458:
            rv = (ssize_t)base64encode_rfc3548(buffer, szBuffer, (uint8_t const *) (data), szData);
            break;

        case PM_BASE64_RFC4648:
            rv = (ssize_t)base64encode_rfc4648(buffer, szBuffer, (uint8_t const *) (data), szData);
            break;

        case PM_BASE64_RFC7515:
            rv = (ssize_t)base64encode_rfc7515(buffer, szBuffer, (uint8_t const *) (data), szData);
            break;

        case PM_BASE64_XML_IDENTIFIER:
            rv = (ssize_t)base64encode_xml_identifier(buffer, szBuffer, (uint8_t const *)data, szData);
            break;

        case PM_BASE64_XML_NAME_TOKEN:
            rv = (ssize_t)base64encode_xml_name_token(buffer, szBuffer, (uint8_t const *)data, szData);
            break;
        }

    }

    return rv;
}

ssize_t pm_base64_decode(
        void *buffer,
        size_t szBuffer,
        char const *data,
        size_t szData)
{
    ssize_t rv = -1;

    if(likely(szBuffer > PM_BASE64_DECODED_SIZE(szData)))
    {
        rv = (ssize_t)base64decode_rfc3458(buffer, szBuffer, data, szData);
    }

    return rv;
}

ssize_t pm_base64_decode_strict(
        void *buffer,
        size_t szBuffer,
        char const *data,
        size_t szData,
        enum pm_base64_encoding_e encoding)
{
    return 0;
}
