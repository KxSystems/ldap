#include "sessions.h"
#include <stdlib.h>
#include <string.h>

typedef struct session
{
    int   idx;
    void* session;
} session;

static session* SESSIONS = 0;
static int SESSION_SIZE = 0;

void addSession(int idx, void* sess)
{
    ++SESSION_SIZE;
    SESSIONS = realloc(SESSIONS,(SESSION_SIZE*sizeof(session)));
    SESSIONS[SESSION_SIZE-1].idx = idx;
    SESSIONS[SESSION_SIZE-1].session = sess;
}

void* getSession(int idx)
{
    int x=0;
    for (x=0;x<SESSION_SIZE;x++)
    {
        if (SESSIONS[x].idx == idx)
            return SESSIONS[x].session;
    }
    return 0;
}

void removeSession(int idx)
{
    int x=0;
    for (x=0;x<SESSION_SIZE;x++)
    {
        if (SESSIONS[x].idx == idx)
        {
            --SESSION_SIZE;
            if (SESSION_SIZE == 0)
            {
                free(SESSIONS);
                SESSIONS = 0;
                return;
            }
            if (x != SESSION_SIZE)
                memmove(SESSIONS+x,SESSIONS+(x+1),(SESSION_SIZE-x)*sizeof(session));
            SESSIONS = realloc(SESSIONS,(SESSION_SIZE*sizeof(session)));
            return;
        }
    }
    return;
}