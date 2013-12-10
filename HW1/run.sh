for i in `seq 1 20`;do 
  cat hw1_15_train.dat |shuf| ./pla |grep update|sed 's/update=//'; 
done |awk '{s+=$1} END {print s/NR}'
