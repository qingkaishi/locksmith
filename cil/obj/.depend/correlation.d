     $(OBJDIR)/correlation.cmo: \
         $(OBJDIR)/shared.cmi  $(OBJDIR)/pretty.cmi \
         $(OBJDIR)/lockstate.cmi \
         $(OBJDIR)/lockprofile.cmi \
         $(OBJDIR)/labelflow.cmi  $(OBJDIR)/errormsg.cmi \
         $(OBJDIR)/controlflow.cmi  $(OBJDIR)/cil.cmi \
         $(OBJDIR)/correlation.cmi 
     $(OBJDIR)/correlation.cmx: \
         $(OBJDIR)/shared.cmx  $(OBJDIR)/pretty.cmx \
         $(OBJDIR)/lockstate.cmx \
         $(OBJDIR)/lockprofile.cmx \
         $(OBJDIR)/labelflow.cmx  $(OBJDIR)/errormsg.cmx \
         $(OBJDIR)/controlflow.cmx  $(OBJDIR)/cil.cmx \
         $(OBJDIR)/correlation.cmi 
