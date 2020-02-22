// Start the RTS.
void ghc_init();

// Stop the RTS.
void ghc_cleanup();

// Like malloc() but better!
void* ghc_alloc(size_t);

// Like free() but better!
void ghc_free(void*);
