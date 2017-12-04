#ifndef _NO_EXECVE

/* execl.c */

/* This and the other exec*.c files in this directory require 
   the target to provide the _execve syscall.  */

#include <_ansi.h>
#include <unistd.h>

/* Only deal with a pointer to environ, to work around subtle bugs with shared
   libraries and/or small data systems where the user declares his own
   'environ'.  */
static char ***p_environ = &environ;

#ifdef _HAVE_STDC

#include <stdarg.h>

int
_DEFUN(execl, (path, arg0, ...), 
      const char *path,
      const char *arg0, ...)

#else

#include <varargs.h>

int
_DEFUN(execl, (path, arg0, va_alist),
     const char *path,
     const char *arg0,
     va_dcl)

#endif

{
  int i;
  va_list args;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;
  do
      argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);
  va_end (args);

  return _execve (path, (char * const  *) argv, *p_environ);
}
#endif /* !_NO_EXECVE  */
