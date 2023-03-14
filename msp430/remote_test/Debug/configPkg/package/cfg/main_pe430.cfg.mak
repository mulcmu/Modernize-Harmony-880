# invoke SourceDir generated makefile for main.pe430
main.pe430: .libraries,main.pe430
.libraries,main.pe430: package/cfg/main_pe430.xdl
	$(MAKE) -f C:\DOCUME~1\Administrator\workspace_v6_1\remote_test/src/makefile.libs

clean::
	$(MAKE) -f C:\DOCUME~1\Administrator\workspace_v6_1\remote_test/src/makefile.libs clean

