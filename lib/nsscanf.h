#ifndef EXPIUM_NSSCANF_H
#define EXPIUM_NSSCANF_H

#ifndef EXPIUM_NSSCANF_ENABLE_INT
#define EXPIUM_NSSCANF_ENABLE_INT 1
#endif

#ifndef EXPIUM_NSSCANF_ENABLE_UNSIGNED
#define EXPIUM_NSSCANF_ENABLE_UNSIGNED 1
#endif

#ifndef EXPIUM_NSSCANF_ENABLE_STRING
#define EXPIUM_NSSCANF_ENABLE_STRING 1
#endif

#ifdef __cplusplus
extern "C"
{
#endif

  int expium_nsscanf(const char *str, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif // EXPIUM_NSSCANF_H