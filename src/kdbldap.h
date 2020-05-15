#ifndef DELTALDAP_H_
#define DELTALDAP_H_

#include "k.h"

#ifdef _WIN32
#define EXP __declspec(dllexport)
#else
#define EXP
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* TODO */
EXP K kdbldap_init(K todo);
EXP K kdbldap_set_option(K option,K value);

#ifdef __cplusplus
}
#endif

#endif