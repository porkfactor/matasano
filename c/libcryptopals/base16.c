#include <mpac/mpac_base64.h>

static uint8_t const decode_rfc_4648[128] = {
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x00 - 0x07 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x08 - 0x0f */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x10 - 0x17 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x18 - 0x1f */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x20 - 0x27 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x28 - 0x2f */
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, /* 0x30 - 0x37 */
    0x08, 0x09, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x38 - 0x3f */
    0x80, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x80, /* 0x40 - 0x47 */
    0x80, 0x08, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x48 - 0x4f */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x50 - 0x57 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x58 - 0x5f */
    0x80, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x80, /* 0x60 - 0x67 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x68 - 0x6f */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x70 - 0x77 */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, /* 0x78 - 0x7f */
};

static inline size_t base16Encode(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData,
        char const *base16characters)
{
    size_t dataOffset = 0;
    size_t szWritten = 0;

    while(dataOffset < szData)
    {
        uint8_t byte = data[dataOffset++];

        buffer[szWritten++] = base16characters[byte >> 4];
        buffer[szWritten++] = base16characters[byte & 0xf];
    }

    return szWritten;
}

static inline size_t base16_encode_uppercase(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData)
{
    return base16Encode(buffer, szBuffer, data, szData, "0123456789ABCDEF");
}

static inline size_t base16_encode_lowercase(
        char *buffer,
        size_t szBuffer,
        uint8_t const *data,
        size_t szData)
{
    return base16Encode(buffer, szBuffer, data, szData, "0123456789abcdef");
}

static inline size_t base16_decode_sequence(
        uint8_t *buffer,
        char const *data,
        uint8_t const *decode)
{
    (*buffer) = (uint8_t)((decode[(uint8_t)data[0]] << 4) | (decode[(uint8_t)data[1]]));

    return 1U;
}

static inline size_t base16Decode(
        uint8_t *buffer,
        size_t szBuffer,
        char const *data,
        size_t szData)
{
    size_t szWritten = 0;

    size_t i;
    for(i = 0; i < szData; i += 2)
    {
        szWritten += base16_decode_sequence(buffer + szWritten, data + i, decode_rfc_4648);
    }

    return szWritten;
}

ssize_t mpac_base16_decode(
        void *buffer,
        size_t szBuffer,
        char const *data,
        size_t szData)
{
    ssize_t rv = -1;

    if(likely(szBuffer >= MPAC_BASE16_DECODED_SIZE(szData)))
    {
        rv = (ssize_t)base16Decode((uint8_t *)buffer, szBuffer, data, szData);
    }

    return rv;
}

ssize_t mpac_base16_encode(
        char *buffer,
        size_t szBuffer,
        void const *data,
        size_t szData)
{
    ssize_t rv = -1;

    if(likely(szBuffer >= MPAC_BASE16_ENCODED_SIZE(szData)))
    {
        rv = (ssize_t)base16_encode_lowercase(buffer, szBuffer, (uint8_t const *)data, szData);
    }

    return rv;
}

ssize_t mpac_base16_encode_strict(
    char *buffer,
    size_t szBuffer,
    void const *data,
    size_t szData,
    enum mpac_base16_encoding_e encoding)
{
    ssize_t rv = -1;

    if(likely(szBuffer >= MPAC_BASE16_ENCODED_SIZE(szData)))
    {
        switch(encoding)
        {
        case MAPC_BASE16_RFC4648:
        case MPAC_BASE16_UPPERCASE:
            rv = (ssize_t)base16_encode_uppercase(buffer, szBuffer, (uint8_t const *)data, szData);
            break;

        case MPAC_BASE16_LOWERCASE:
            rv = (ssize_t)base16_encode_lowercase(buffer, szBuffer, (uint8_t const *)data, szData);
            break;
        }
    }

    return rv;
}
