#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

char* module_dir;

struct server_module* module_open (const char* module_name)
{
  char* module_path;
  void* handle;
  void (* module_generate) (int);
  struct server_module* module;

  /* Ruta completa del modulo */
  module_path = 
    (char*) xmalloc (strlen (module_dir) + strlen (module_name) + 2);
  sprintf (module_path, "%s/%s", module_dir, module_name);

  /* Intentar abrir la ruta como una libreria compartida  */
  handle = dlopen (module_path, RTLD_NOW);
  free (module_path);
  if (handle == NULL) {
    return NULL;
  }

  /* Busco la direccion de memoria del modulo de la libreria.  */
  module_generate = (void (*) (int)) dlsym (handle, "module_generate");
  /* Se ha cargado bien el modulo.  */
  if (module_generate == NULL) {
    /* Hemos cargado una libreria, pero no es un modulo.  */
    dlclose (handle);
    return NULL;
  }

  /* Inicializa el modulo */
  module = (struct server_module*) xmalloc (sizeof (struct server_module));
  module->handle = handle;
  module->name = xstrdup (module_name);
  module->generate_function = module_generate;
  return module;
}

void module_close (struct server_module* module)
{
  /* Cierra la libreria compartida.  */
  dlclose (module->handle);
  /* Libera el nombre del modulo.  */
  free ((char*) module->name);
  /* Libera el modulo.  */
  free (module);
}
 
