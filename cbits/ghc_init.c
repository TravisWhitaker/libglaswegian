#include <HsFFI.h>
#include <Rts.h>

void ghc_init()
{
    RtsConfig conf = defaultRtsConfig;
    conf.rts_opts_enabled = RtsOptsAll;
    int argc = 3;
    char* argv[] = { "libglaswegian", "+RTS", "-A256M", 0};
    char** rargv = argv;
    hs_init_ghc(&argc, &rargv, conf);
}
