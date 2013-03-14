####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = kdoors
kdoors_SOURCES = kdpluginslistbox.cpp kdresultview.cpp kdfrmparamplugins.cpp frmparamplugins.ui kdfrmlistplugins.cpp kplugins.cpp kdhostview.cpp kdhostitem.cpp kresolvename.cpp DlgIpRange.cpp kdoors.cpp main.cpp 
kdoors_LDADD   =  -lkfile -lkdeui -lkdecore $(LIB_QT) $(LIBSOCKET)


EXTRA_DIST = main.cpp kdoors.cpp kdoors.h kdoorsui.rc kdoors.desktop kdoors.xpm mini-kdoors.xpm DlgIpRange.cpp DlgIpRange.h kresolvename.cpp kresolvename.h kdhostitem.cpp kdhostitem.h kdhostview.cpp kdhostview.h kplugins.cpp kplugins.h kdfrmlistplugins.cpp kdfrmlistplugins.h frmparamplugins.ui kdfrmparamplugins.cpp kdfrmparamplugins.h frmparamplugins.h kdresultview.cpp kdresultview.h kdpluginslistbox.cpp kdpluginslistbox.h 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Applications/
	$(INSTALL_DATA) $(srcdir)/kdoors.desktop $(kde_appsdir)/Applications/kdoors.desktop
	$(mkinstalldirs) $(kde_icondir)/medium/locolor/apps/
	$(INSTALL_DATA) $(srcdir)/kdoors.xpm $(kde_icondir)/medium/locolor/apps/kdoors.xpm
	$(mkinstalldirs) $(kde_icondir)/small/locolor/apps/
	$(INSTALL_DATA) $(srcdir)/mini-kdoors.xpm $(kde_icondir)/small/locolor/apps/kdoors.xpm

uninstall-local:
	-rm -f $(kde_appsdir)/Applications/kdoors.desktop
	-rm -f $(kde_icondir)/medium/locolor/apps/kdoors.xpm
	-rm -f $(kde_icondir)/small/locolor/apps/kdoors.xpm

####### kdevelop will overwrite this part!!! (end)############
# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
kdoors_LDFLAGS = $(all_libraries) $(KDE_RPATH)

rcdir = $(kde_datadir)/kdoors
rc_DATA = kdoorsui.rc

messages: rc.cpp
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/kdoors.pot; \
	fi

