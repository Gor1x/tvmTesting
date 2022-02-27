
echo "args: $*"

repo_dir=$1
work_dir=$2

python3 ${repo_dir}/tests/scripts/prepare.py ${repo_dir}/tests/data/printClass ${work_dir}
bash ${work_dir}/run-tests.sh
diff -b -r ${repo_dir}/tests/data/printClass/gold ${work_dir}/result
