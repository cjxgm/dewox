AC_INIT([dewox], [0.12], [cjxgm@126.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC

ERR=0

AC_CHECK_HEADER([math.h], , [ERR=1])
AC_CHECK_LIB([m], [sin], , [ERR=1])
if test $ERR == 1; then
	AC_MSG_ERROR([There is not a math library???])
fi

AC_CHECK_HEADER([GL/gl.h], , [ERR=1])
AC_CHECK_LIB([GL], [glBegin], , [ERR=1])
if test $ERR == 1; then
	AC_MSG_ERROR([Please have OpenGL installed.])
fi

AC_CHECK_HEADER([GL/glut.h], , [ERR=1])
AC_CHECK_LIB([glut], [glutSwapBuffers], , [ERR=1])
if test $ERR == 1; then
	AC_MSG_ERROR([Please have GLUT installed.])
fi

AC_CHECK_HEADER([AL/al.h], , [ERR=1])
AC_CHECK_HEADER([AL/alc.h], , [ERR=1])
AC_CHECK_LIB([openal], [alSourcePlay], , [ERR=1])
if test $ERR == 1; then
	AC_MSG_ERROR([Please have OpenAL installed.])
fi

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
