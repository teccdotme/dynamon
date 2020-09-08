#pragma once
#include <stdlib.h>

/**
 * Handles metadata for dynamon libraries.
 */
typedef struct dnm_library {
    void* handle;

} dnm_library;

#define DNM_ERROR dnm_create_library((void*) -1)

/**
 * Creates a library with the specified handle.
 *
 * @param handle The handle.
 * @return A library with <code>handle</code> as handle.
 */
dnm_library dnm_create_library(void* handle);

/**
 * Resolves a library from a specified name.
 *
 * @note
 *      Symbols will be loaded as soon as they are used.
 *
 * @param library The library to resolve.
 *                It may be relative, but must contain
 *                suffixes.
 *
 * @return The library, if found.
 *         Otherwise it will return <code>DNM_ERROR</code>
 */
dnm_library dnm_resolve_mode(char* library, int mode);

/**
 * Resolves a library from a specified name.
 *
 * @note
 *      Symbols will be loaded as soon as they are used.
 *
 * @param library The library to resolve.
 *                It may be relative, but must contain
 *                suffixes.
 *
 * @return The library, if found.
 *         Otherwise it will return <code>DNM_ERROR</code>
 */
dnm_library dnm_resolve(char* library);
/**
 * Resolves a library from a specified name.
 *
 * @note
 *      Symbols will be loaded as soon as possible.
 *
 * @param library The library to resolve.
 *                It may not be relative or absolute,
 *
 * @return The library, if found.
 *         Otherwise it will return <code>DNM_ERROR</code>
 */
dnm_library dnm_resolve_all(char* library);

/**
 * Resolves a library from a specified name.
 * Looks in the environment path and adds suffixes automatically if desired.
 *
 * @note
 *      Symbols will be loaded as soon as they are used.
 *
 * @param library The library to resolve.
 *                It may not be relative or absolute,
 *
 * @param nomod Whether or not to modify the library name.
 * @return The library, if found.
 *         Otherwise it will return <code>DNM_ERROR</code>
 */
dnm_library dnm_native_resolve(char* library, int nomod);

/**
 * Resolves a library from a specified name.
 * Looks in the environment path and adds suffixes automatically if desired.
 *
 * @note
 *      Symbols will be loaded as soon as possible.
 *
 * @param library The library to resolve.
 *                It may not be relative or absolute,
 *
 * @param nomod Whether or not to modify the library name.
 * @return The library, if found.
 *         Otherwise it will return <code>DNM_ERROR</code>
 */
dnm_library dnm_native_resolve_all(char* library, int nomod);

/**
 * Loads a symbol from the library.
 * A symbol is may be a
 *
 * @param library The library to load a symbol from.
 *
 * @param symbol The symbol to load.
 *
 * @return
 */
void* dnm_get_symbol(dnm_library library, char* symbol);