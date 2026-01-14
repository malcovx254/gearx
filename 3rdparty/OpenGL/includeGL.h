#ifndef GEARX_3RDPARTY_OPENGL_OPENGL_H

#define GEARX_3RDPARTY_OPENGL_OPENGL_H

#define WINDOWS_MSYS2

#ifdef WINDOWS
#include <windows.h>
#include <GL/glut.h>
#include <GL/glew.h>

#endif

#ifdef WINDOWS_MSYS2
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <GL/glew.h>
#endif

#endif
