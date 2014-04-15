     $(OBJDIR)/lockprofile.cmo: \
         $(OBJDIR)/labelflow.cmi  $(OBJDIR)/errormsg.cmi \
         $(OBJDIR)/lockprofile.cmi 
     $(OBJDIR)/lockprofile.cmx: \
         $(OBJDIR)/labelflow.cmx  $(OBJDIR)/errormsg.cmx \
         $(OBJDIR)/lockprofile.cmi 
