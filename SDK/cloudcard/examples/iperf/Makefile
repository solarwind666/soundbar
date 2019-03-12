-include $(TOPDIR)/Make.defs
APPNAME = iperf
PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 2048

ASRCS =
CXXSRCS =  Client.cxx \
        Launch.cxx  List.cxx \
        Listener.cxx \
        PerfSocket.cxx \
        Server.cxx \
        Settings.cxx \
	delay.cxx

CSRCS = \
        Locale.c \
        ReportCSV.c \
        ReportDefault.c \
        Reporter.c \
        SocketAddr.c \
        gnu_getopt.c \
        gnu_getopt_long.c \
        service.c \
        sockets.c \
        stdio.c \
        tcp_window_size.c \
	Extractor.c \
	gettimeofday.c \
	error.c \
	signal.c \
	Thread.c \
	inet_ntop.c \
	inet_pton.c \
	snprintf.c \
	string.c

MAINSRC = iperf_main.cxx
CXXFLAGS += -I$(TOPDIR)/../cloudcard/examples/iperf/include  -DHAVE_CONFIG_H -finline-functions -fmessage-length=0 -fno-inline-functions-called-once -fgcse-after-reload -frerun-cse-after-loop -frename-registers -no-canonical-prefixes 
CFLAGS += -I$(TOPDIR)/../cloudcard/examples/iperf/include   -DHAVE_CONFIG_H -finline-functions -fmessage-length=0 -fno-inline-functions-called-once -fgcse-after-reload -frerun-cse-after-loop -frename-registers -no-canonical-prefixes 
CONFIG_EXAMPLES_XYZ_PROGNAME ?= iperf$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_XYZ_PROGNAME)

include $(APPDIR)/Application.mk
