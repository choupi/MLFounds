for i in `seq 1 2000`;do 
cat hw1_18_train.dat |shuf|./pck hw1_18_test.dat;
done | awk '{s+=$1} END {print s/NR}'
