/\/tmp\// { next; }
/LockSmith run for/ { next; }
/STARTING/ { out = 1; };
{ if (out) { print $0 } };
/DONE/ { out = 0; };
