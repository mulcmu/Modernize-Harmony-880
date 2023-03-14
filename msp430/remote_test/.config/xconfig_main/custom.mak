## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e430 linker.cmd package/cfg/main_pe430.oe430

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/main_pe430.xdl
	$(SED) 's"^\"\(package/cfg/main_pe430cfg.cmd\)\"$""\"C:/Documents and Settings/Administrator/workspace_v6_1/remote_test/.config/xconfig_main/\1\""' package/cfg/main_pe430.xdl > $@
	-$(SETDATE) -r:max package/cfg/main_pe430.h compiler.opt compiler.opt.defs
