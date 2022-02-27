import sys
import os.path
import os

base = sys.argv[1]
work_dir = sys.argv[2]

list_file = os.path.join(base, "classes.lst")
tvm = os.path.join(work_dir, "tvm")
result_dir = os.path.join(work_dir, "result")

script_name = os.path.join(work_dir, "run-tests.sh")

with open(script_name, 'w') as script:
    script.write(f"rm -rf {result_dir}\n")
    script.write(f"mkdir {result_dir}\n")

    for s in open(list_file):
        test_id, class_file = s.strip().split(',')
        test_id = int(test_id)
        class_file = os.path.join(base, "classes", class_file)
        result_file = os.path.join(result_dir, f"{test_id:08d}.txt")
        script.write(f"{tvm} '{class_file}' -printClass > {result_file}\n")

