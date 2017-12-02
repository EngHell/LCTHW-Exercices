echo "Running unit tests:"

for i in build/tests/*_tests
	do
		if test -f $i
			then
			if $VALGRIND ./$i 2>&1 >> build/tests/tests.log
				then
				echo $i PASS
				else
					echo "ERROR in test $i: here's the log at build/tests/tests.log"
					echo "------"
					tail build/tests/tests.log
					exit 1
				fi
			fi
		done
echo""
