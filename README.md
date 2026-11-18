# JFTP

[Español](#español) · [English](#english)

## Español

Módulos de una adaptación de escritorio para copiar archivos entre Windows y un servidor FTP. El código recuperado explica cómo se organizaban los destinos y las transferencias en espera.

### Qué puedes hacer

- Relaciona la selección de direcciones con las operaciones del cliente.
- Conserva una cola de archivos con parámetros de reintento y opciones de transferencia.
- Incluye la página de preferencias del actualizador.

### Ejemplo

Para estudiar el flujo, imagina copiar dos archivos de texto a un servidor local. Revisa en `DelayFiles` qué datos conserva el cliente sobre la tarea pendiente.

### Cómo empezar

El código se creó para Windows y Visual C++. Usa las versiones de MFC o de los SDK que indiquen la solución y sus referencias. Los recursos y componentes externos de la época pueden requerir una copia autorizada. La compilación completa depende de ese entorno original.

Puntos de entrada en el código. [`src/ActualizacionesPage.cpp`](src/ActualizacionesPage.cpp), [`src/DelayFiles.cpp`](src/DelayFiles.cpp), [`src/DireccionDlg.cpp`](src/DireccionDlg.cpp).

FTP Wanderer, de Pablo van der Meer, es el cliente de referencia. Esta edición contiene los módulos de la adaptación.

Las fechas del historial se apoyan en Git o en la evidencia disponible de los respaldos. Las fechas reconstruidas a partir de archivos sin zona horaria usan las 12:00 UTC como referencia.

## English

Modules from a Windows FTP client adaptation. The recovered source shows how the program organized destinations and queued file transfers.

### What you can do

- Connect address selection to client operations.
- Keep a file queue with retry settings and transfer options.
- Include the updater preferences page.

### Example

To explore the flow, picture copying two text files to a local server. Review what `DelayFiles` keeps for the pending work.

### Getting started

The code was written for Windows and Visual C++. Use the MFC and SDK versions indicated by the solution and its references. Historical resources and external components may require an authorized copy. A full build depends on that original environment.

Entry points in the source. [`src/ActualizacionesPage.cpp`](src/ActualizacionesPage.cpp), [`src/DelayFiles.cpp`](src/DelayFiles.cpp), [`src/DireccionDlg.cpp`](src/DireccionDlg.cpp).

FTP Wanderer, by Pablo van der Meer, is the reference client. This edition contains the adaptation modules.

History dates come from Git or available backup evidence. Reconstructed dates from files with no time zone use 12:00 UTC as a reference.
