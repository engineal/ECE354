# generated_app.mk
#
# Machine generated for a CPU named "cpu_0" as defined in:
# c:\Users\ajlucia\Desktop\GitPortable\Data\home\ECE354\lab1b\count_binary\count_binary_syslib\..\..\taj_c.ptf
#
# Generated: 2016-02-08 12:01:46.76

# DO NOT MODIFY THIS FILE
#
#   Changing this file will have subtle consequences
#   which will almost certainly lead to a nonfunctioning
#   system. If you do modify this file, be aware that your
#   changes will be overwritten and lost when this file
#   is generated again.
#
# DO NOT MODIFY THIS FILE

# assuming the Quartus project directory is the same as the PTF directory
QUARTUS_PROJECT_DIR = C:/Users/ajlucia/Desktop/GitPortable/Data/home/ECE354/lab1b

# the simulation directory is a subdirectory of the PTF directory
SIMDIR = $(QUARTUS_PROJECT_DIR)/taj_c_sim

DBL_QUOTE := "



all: delete_placeholder_warning sim

delete_placeholder_warning: do_delete_placeholder_warning
.PHONY: delete_placeholder_warning

sim: $(SIMDIR)/dummy_file
.PHONY: sim

do_delete_placeholder_warning:
	rm -f $(SIMDIR)/contents_file_warning.txt
.PHONY: do_delete_placeholder_warning

$(SIMDIR)/dummy_file: $(ELF)
	if [ ! -d $(SIMDIR) ]; then mkdir $(SIMDIR) ; fi
	@echo Hardware simulation is not enabled for the target SOPC Builder system. Skipping creation of hardware simulation model contents and simulation symbol files. \(Note: This does not affect the instruction set simulator.\)
	touch $(SIMDIR)/dummy_file


generated_app_clean:
	$(RM) $(SIMDIR)/dummy_file
.PHONY: generated_app_clean
