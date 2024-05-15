CC_TYPES=("default" "tictoc" "mvcc")
NUM_WAREHOUSES=("1" "64")
OUTPUT_DIR=$1

mkdir -p "$OUTPUT_DIR"
START_TIME=$SECOND

for cc_type in "${CC_TYPES[@]}"; do
    for num_warehouses in "${NUM_WAREHOUSES[@]}"; do
                for repeat in {1..3}; do
                    echo "Running TPCC with cc_type=${cc_type}, num_warehouses=${num_warehouses}"
                    filename="${OUTPUT_DIR}/tpccfull_${cc_type}_num_warehouses${num_warehouses}_${repeat}.txt"
                    err_filename="${OUTPUT_DIR}/tpccfull_${cc_type}_num_warehouses${num_warehouses}_${repeat}.err"
                    ./tpcc_bench -t32 -m0 "-i${cc_type}" -g -x "-w${num_warehouses}" > >(tee $filename) 2> >(tee $err_filename >&2)
                done
                ELAPSED_TIME=$((SECONDS - START_TIME))
                echo "Current Runtime ${ELAPSED_TIME} s"
    done
done
