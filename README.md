# JFTP

[Español](#español) · [English](#english)

## Español

Módulos de una adaptación de escritorio para copiar archivos entre Windows y un servidor FTP. El código recuperado explica cómo se organizaban los destinos y las transferencias en espera.

### Esta revisión

**2004-11-22 · Recuperar preferencias y transferencias en espera.** Incorpora el diálogo de preferencias de actualización, el selector de direcciones y el código que procesa descargas en espera. Estos módulos muestran cómo se configura la adaptación y cómo retoma los archivos pendientes.

### Cómo explorar el código

El código se creó para Windows y Visual C++. Usa las versiones de MFC o de los SDK que indiquen la solución y sus referencias. Los recursos y componentes externos de la época pueden requerir una copia autorizada. La compilación completa depende de ese entorno original.

- [src/ActualizacionesPage.cpp](src/ActualizacionesPage.cpp)
- [src/DelayFiles.cpp](src/DelayFiles.cpp)
- [src/DireccionDlg.cpp](src/DireccionDlg.cpp)

El cliente de referencia es FTP Wanderer, de Pablo van der Meer.

## English

Modules from a Windows FTP client adaptation. The recovered source shows how the program organized destinations and queued file transfers.

### This revision

**2004-11-22 · Recover preferences and deferred FTP transfers.** Restore the update preferences dialog, address selector, and code that processes deferred downloads. These modules show how to configure the adaptation and how it resumes pending files.

### How to explore the source

The code was written for Windows and Visual C++. Use the MFC and SDK versions indicated by the solution and its references. Historical resources and external components may require an authorized copy. A full build depends on that original environment.

- [src/ActualizacionesPage.cpp](src/ActualizacionesPage.cpp)
- [src/DelayFiles.cpp](src/DelayFiles.cpp)
- [src/DireccionDlg.cpp](src/DireccionDlg.cpp)

The reference client is FTP Wanderer, by Pablo van der Meer.
