     $(OBJDIR)/controlflow.cmo:  $(OBJDIR)/pretty.cmi \
         $(OBJDIR)/lockutil.cmi \
         $(OBJDIR)/labelflow.cmi   $(OBJDIR)/heap.cmo \
     $(OBJDIR)/errormsg.cmi  $(OBJDIR)/cil.cmi \
         $(OBJDIR)/controlflow.cmi 
     $(OBJDIR)/controlflow.cmx:  $(OBJDIR)/pretty.cmx \
         $(OBJDIR)/lockutil.cmx \
         $(OBJDIR)/labelflow.cmx   $(OBJDIR)/heap.cmx \
     $(OBJDIR)/errormsg.cmx  $(OBJDIR)/cil.cmx \
         $(OBJDIR)/controlflow.cmi 
