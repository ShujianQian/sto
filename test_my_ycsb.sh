ALPHAS=("0.0" "0.99")
READ_TYPES=("full")
CC_TYPES=("default" "tictoc" "mvcc")
YCSB_BENCH=("F")
OUTPUT_DIR=$1

mkdir -p "$OUTPUT_DIR"
START_TIME=$SECOND

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

for cc_type in "${CC_TYPES[@]}"; do
    for read_type in "${READ_TYPES[@]}"; do
        for ycsb_bench in "${YCSB_BENCH[@]}"; do
            for alpha in "${ALPHAS[@]}"; do
                for repeat in {1..1}; do
                    echo -c "${GREEN}Running YCSB with alpha=${alpha}, read_type=${read_type}, cc_type=${cc_type}, ycsb_bench=${ycsb_bench}${NC}"
                    filename="${OUTPUT_DIR}/${cc_type}_${read_type}_${alpha}_YCSB${ycsb_bench}_${repeat}.txt"
                    err_filename="${OUTPUT_DIR}/${cc_type}_${read_type}_${alpha}_YCSB${ycsb_bench}_${repeat}.err"
                    ./ycsb_bench -t32 "-m${ycsb_bench}" "-i${cc_type}" -g -x "-s${alpha}" "-r${read_type}" > >(tee $filename) 2> >(tee $err_filename >&2)
                done
                ELAPSED_TIME=$((SECONDS - START_TIME))
                echo "${BLUE}Current Runtime ${ELAPSED_TIME} s${NC}"
            done
        done
    done
done
