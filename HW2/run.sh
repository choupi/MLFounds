for i in `seq 1 5000`;do 
    ./ds
done |awk '{i+=$1; o+=$2} END {print i/NR, o/NR}'
