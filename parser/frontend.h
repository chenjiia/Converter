#ifndef LIGER_FRONTEND_H_
#define LIGER_FRONTEND_H_

#include <glib.h>

// Called by the parser when it finishes parsing a program.
void done_parsing(GList* decl, GList* stmt);

#endif
