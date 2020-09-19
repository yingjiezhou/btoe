ver=$1
root -b -l <<EOF
   .X runget_sym.C("$ver")
   .q
EOF

