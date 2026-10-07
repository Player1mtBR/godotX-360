#include <stdint.h>

#include <ppc/timebase.h>
#include <mbedtls/platform_time.h>

mbedtls_ms_time_t mbedtls_ms_time(void)
{
    return (mbedtls_ms_time_t)(mftb() / (PPC_TIMEBASE_FREQ / 1000));
}
