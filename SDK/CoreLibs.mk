
CORELIBS =

ifneq ($(YOCLIBIUVDIR),)
CORELIBS += libiuv$(LIBEXT)
endif

ifneq ($(YOCLIBINETUTILSDIR),)
CORELIBS += libinetutils$(LIBEXT)
endif

ifneq ($(IDJSDIR),)
CORELIBS += libidjs$(LIBEXT)

ifeq ($(CONFIG_UKERNEL_TYPE),banana)
#CORELIBS += libdevice_transport$(LIBEXT)
#CORELIBS += libdevice_ota$(LIBEXT)
#CORELIBS += libdevice_time_calibration$(LIBEXT)
endif

ifeq ($(CONFIG_UKERNEL_TYPE),lemon)
#CORELIBS += libdevice_transport$(LIBEXT)
#CORELIBS += libdevice_time_calibration$(LIBEXT)
endif

ifeq ($(CONFIG_XIAOYUN),y)
#CORELIBS += libxiaoyun$(LIBEXT)
endif
ifeq ($(CONFIG_UKERNEL_TYPE),banana)
#CORELIBS += libmedia$(LIBEXT)
endif
#CORELIBS += libyunio$(LIBEXT)
endif

ifeq ($(CONFIG_LIB_MEDIA),y)
#CORELIBS += libmedia$(LIBEXT)
endif

ifneq ($(IDTFSDIR),)
#CORELIBS += libid2$(LIBEXT)
#NUTTXLIBS += libtfshal$(LIBEXT)
endif
ifneq ($(YOCLIBCRYPTO_MBEDTLS),)
CORELIBS += libmbedcrypto$(LIBEXT)
endif

ifneq ($(YOCLIBOPENSSLDIR),)
CORELIBS += libssl$(LIBEXT)
CORELIBS += libcrypto2$(LIBEXT)
endif

ifneq ($(YOCLIBMOSQUITTODIR),)
CORELIBS += libmosquitto$(LIBEXT)
endif

ifneq ($(YOCLIBDUEROSDIR),)
CORELIBS += libdueros$(LIBEXT)
endif

ifneq ($(YOCLIBAWSIOTDIR),)
CORELIBS += libawsiot$(LIBEXT)
endif

ifneq ($(YOCLIBMADDIR),)
CORELIBS += libmad$(LIBEXT)
endif

ifneq ($(YOCLIBAUDIOMODULESDIR),)
CORELIBS += libaudiomodules$(LIBEXT)
endif

ifneq ($(CONFIG_SYSTEM_DMR),)
#CORELIBS += libdmr$(LIBEXT)
endif
ifneq ($(CONFIG_SYSTEM_AIRPLAY),)
#CORELIBS += libshairport$(LIBEXT)
endif
