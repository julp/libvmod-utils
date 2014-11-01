#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vrt.h"
#include "cache/cache.h"
#include "vcc_if.h"
#include "vsa.h"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

VCL_STRING vmod_remove_qs(const struct vrt_ctx *ctx, VCL_STRING url)
{
    char *p;

    CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

    if (NULL == url || NULL == (p = strchr(url, '?'))) {
        return url;
    } else {
        return WS_Copy(ctx->ws, url, p - url);
    }
}

VCL_BOOL vmod_startswith(const struct vrt_ctx *ctx, VCL_STRING string, VCL_STRING prefix)
{
    CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

    if (NULL == string || NULL == prefix) {
        return 0;
    } else {
        size_t str_len, prefix_len;

        str_len = strlen(str);
        prefix_len = strlen(prefix);
        if (prefix_len > str_len) {
            return 0;
        }
        return 0 == strncmp(string, prefix, prefix_len);
    }
}

VCL_STRING vmod_normalize_qs(const struct vrt_ctx *ctx, VCL_STRING url)
{
    char *p;

    CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

    if (NULL == url || NULL == (p = strchr(url, '?')) || '\0' != p[1]) {
        return url;
    } else {
        return WS_Copy(ctx->ws, url, p - url);
    }
}

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

VCL_STRING vmod_resolve(const struct vrt_ctx *ctx, VCL_IP ip)
{
    int rc;
    socklen_t sl;
    const struct sockaddr *sa;
    char hostname[NI_MAXHOST];

    CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);

    if (NULL != (sa = VSA_Get_Sockaddr(ip, &sl))) {
        if (0 == (rc = getnameinfo(sa, sizeof(*sa), hostname, ARRAY_SIZE(hostname), NULL, 0, NI_NAMEREQD))) {
            return WS_Copy(ctx->ws, hostname, -1);
        }
    }

    return NULL;
}
