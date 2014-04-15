cat $1 |tail -50 |
grep -v gcc | awk '
BEGIN { x = 0 }
/shared:/ { x = 1 }
{ if (x == 1) print $0 }'

