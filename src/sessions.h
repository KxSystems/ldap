#ifndef SESSIONS_H_
#define SESSIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

void  addSession(int idx, void* sess);
void* getSession(int idx);
void  removeSession(int idx);

#ifdef __cplusplus
}
#endif

#endif