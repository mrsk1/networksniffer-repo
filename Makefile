
.PHONY : clean
OBJ= read.o

OUTFILE = sniffer

# Beautify Output
quiet_cmd_cc_o_cc  = @ echo "GEN  $(PWD)/$@ "

$(OUTFILE) : $(OBJ)
	gcc -o $@ $(OBJ) 



%.o:%.c
	@gcc -c $<
	$(quiet_cmd_cc_o_cc)


clean:
	rm  -rf $(OUTFILE) $(OBJ)


