#include <dlfcn.h>
#include <dynamon.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#if defined(_WIN32) || defined(_WIN64)
#define DNM_PREFIX ""
#define DNM_SUFFIX ".dll"
#define DNM_MAX_PATH PATH_MAX
#define DNM_PATH_SEPARATOR "\\"

void *handle_error(void *param);

#elif defined(unix) || defined(__unix__) || defined(__unix)
#define DNM_PREFIX "lib"
#define DNM_SUFFIX
#define DNM_MAX_PATH MAX_PATH
#define DNM_PATH_SEPARATOR "/"
#endif

int str_ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

char** file_in_path(char* file) {
    char* dup = strdup(getenv("PATH"));
    char* s = dup;
    char* p = NULL;
    char** occurrences = (char**) malloc(0);
    size_t ocs = 0;
    do {
        p = strchr(s, ':');
        if (p != NULL) {
            p[0] = 0;
        }

        char* cf = strdup(p);
        if (str_ends_with(p, DNM_PATH_SEPARATOR) == 0) {
            cf = realloc(cf, strlen(cf) + strlen(DNM_PATH_SEPARATOR));
            strcat(cf, DNM_PATH_SEPARATOR);
        }
        cf = realloc(cf, strlen(cf) + strlen(file));
        strcat(cf, file);

        if (access(cf, F_OK) == 1 ) {
            occurrences = realloc(occurrences, ocs + strlen(cf));
            ocs += strlen(cf);
        }

        s = p + 1;
    } while (p != NULL);

    free(dup);

    return occurrences;
}
char* modify(char* path) {
    char* dup = strdup(path);
    path = malloc(strlen(DNM_PREFIX) + strlen(dup) + strlen(DNM_SUFFIX));
    strcat(path, DNM_PREFIX);
    strcat(path, dup);
    strcat(path, DNM_SUFFIX);
    free(dup);
    return path;
}

char* get_native_path(char* p) {
    char** paths = file_in_path(p);
    char* path;
    if (paths != NULL)
        path = paths[0];
    else return NULL;
    path = modify(path);
    return path;
}

void *handle_error(void *param) {
    char* err = dlerror();
    if (err == NULL)
        return param;
    printf("%s", err);

}

// definitions of dynamon.h functions

dnm_library dnm_create_library(void* handle) {
    dnm_library* lib = (dnm_library*) malloc(sizeof(dnm_library) + sizeof(handle));
    lib->handle = handle;
    lib = handle_error(lib);
    return lib[0];
}

dnm_library dnm_resolve_mode(char* library, int mode) {
    dlerror();
    void* handle = dlopen(library, mode);
    handle = handle_error(handle);
    if (handle == NULL)
        return DNM_ERROR;
    return dnm_create_library(handle);
}
dnm_library dnm_resolve(char *library) {
    return dnm_resolve_mode(library, RTLD_LAZY);
}

dnm_library dnm_resolve_all(char* library) {
    return dnm_resolve_mode(library, RTLD_NOW);
}

dnm_library dnm_native_resolve(char* library, int nomod) {
    if (!nomod)
        modify(library);
    return dnm_resolve(get_native_path(library));
}

dnm_library dnm_native_resolve_all(char* library, int nomod) {
    if (!nomod)
        modify(library);
    return dnm_resolve_all(get_native_path(library));
}

void* dnm_get_symbol(dnm_library library, char* symbol) {
    dlerror();
    void *sym = dlsym(library.handle, symbol);
    return handle_error(sym);
}
