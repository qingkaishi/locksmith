     $(OBJDIR)/shared.cmo:  $(OBJDIR)/pretty.cmi \
         $(OBJDIR)/lockutil.cmi \
         $(OBJDIR)/lockstate.cmi \
         $(OBJDIR)/labelflow.cmi  $(OBJDIR)/errormsg.cmi \
         $(OBJDIR)/controlflow.cmi  $(OBJDIR)/cil.cmi \
         $(OBJDIR)/shared.cmi 
     $(OBJDIR)/shared.cmx:  $(OBJDIR)/pretty.cmx \
         $(OBJDIR)/lockutil.cmx \
         $(OBJDIR)/lockstate.cmx \
         $(OBJDIR)/labelflow.cmx  $(OBJDIR)/errormsg.cmx \
         $(OBJDIR)/controlflow.cmx  $(OBJDIR)/cil.cmx \
         $(OBJDIR)/shared.cmi 
