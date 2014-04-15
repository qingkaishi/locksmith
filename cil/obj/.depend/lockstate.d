     $(OBJDIR)/lockstate.cmo:  $(OBJDIR)/pretty.cmi \
         $(OBJDIR)/labelflow.cmi  $(OBJDIR)/errormsg.cmi \
         $(OBJDIR)/controlflow.cmi \
         $(OBJDIR)/lockstate.cmi 
     $(OBJDIR)/lockstate.cmx:  $(OBJDIR)/pretty.cmx \
         $(OBJDIR)/labelflow.cmx  $(OBJDIR)/errormsg.cmx \
         $(OBJDIR)/controlflow.cmx \
         $(OBJDIR)/lockstate.cmi 
