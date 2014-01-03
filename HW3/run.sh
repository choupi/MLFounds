for i in `seq 1 1000`;do 
    ./genSample | ./linearReg 3
done |awk '{s+=$3} END {print s/NR}'
