#! bin/awk -f

#find . -name \*.c  | while read ffile; do awk -f myawk.awk "$ffile"; done 
#find . -name \*.c -print0 | while read -r -d $'\0' file; do awk -f myawk.awk "$file";  done 
#find . -name \*.c -print | while read -r  file; do awk -f myawk.awk "$file";  done 

BEGIN{x; flag}

{if(NF == 0) {
   ++x; 
   if(x > 1) {
      if(flag == 0) {
         flag= 1; 
         print FILENAME " " FNR-1 
         }
      } 
   } 
else {
   x=0; 
   flag= 0
   } 
} 

#has a commit

#BEGIN{x=0; flag = 1}

#{if(NF == 0) {
#   ++x; 
 #  if(x >= 2) {
    #  if(flag) {
   #      flag= 0; 
   #      print ARGV[1] " " NR-1 
  #       }
 #     } 
#   } 
#else {
#   x=0; 
#   flag= 1
#   } 
#} 

# $0 indicate complete of line
# $1...$n indicate first word r column

#BEGIN{print ARGV[1]; x= 0}

#{if(NF== 0) {++x; if(x>= 2) print NR } else x=0;} 

#enter from the command line 
#find . -name \*.c -print0 | while read -r -d $'\0' file; do awk -f myawk.awk "$file";  done 
##########################

#find . -name  \*.c  | while read ffile; do awk -f myawk.awk "$ffile"; done 

#############################33

#find . -type f -name \*.c -print0 | while read -r -d $'\0' file; do awk -f myawk.awk "$file";  done 

################################

#find . -type f -executable -print0 | while read -r -d $'\0' file; do awk -f myawk.awk "$file";  done 

################################
#awk -v x=2 -v y=5 'BEGIN{x+y;print x+y}' 
#awk -v x=2 '{if(NF== 0) {++x; if(x>= 2) print NR } else x=0;}' fgt.c

######################
# what is the difference between print and print0 ?
# please try to in command-line !
