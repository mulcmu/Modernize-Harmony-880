#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/grace_3_10_00_82/packages;C:/ti/msp430/msp430_driverlib_2_60_00_02/packages;C:/ti/msp430/msp430_driverlib_2_60_00_02;C:/ti/ccsv6/ccs_base;C:/DOCUME~1/Administrator/workspace_v6_1/remote_test/.config
override XDCROOT = C:/ti/xdctools_3_32_00_06_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/grace_3_10_00_82/packages;C:/ti/msp430/msp430_driverlib_2_60_00_02/packages;C:/ti/msp430/msp430_driverlib_2_60_00_02;C:/ti/ccsv6/ccs_base;C:/DOCUME~1/Administrator/workspace_v6_1/remote_test/.config;C:/ti/xdctools_3_32_00_06_core/packages;..
HOSTOS = Windows
endif
