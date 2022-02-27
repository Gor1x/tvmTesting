
echo "args: $*"

repo_dir=$1
work_dir=$2
git_dir=${work_dir}/external

mkdir ${git_dir}
cd ${git_dir}
git clone https://github.com/sreznick/tvm-tests
cd tvm-tests/classPrint/wildfly
unzip -q classes.zip


python3 ${repo_dir}/tests/scripts/prepare.py $PWD ${work_dir}
bash ${work_dir}/run-tests.sh
diff -b -r $PWD/gold ${work_dir}/result

