#!/bin/bash

EXEC="./cw.debug"
TESTS_IN="tests/in"
TEST_OUT="tests/out/out"

count_pass_tests=0
total_tests=0

for test in $TESTS_IN/*.in; do
    name_test=$(basename "$test" .in)
    name_out="$TESTS_IN/${name_test}.out"

    total_tests=$((total_tests + 1))

    $EXEC < "$test" > "$TEST_OUT"

    if diff "$TEST_OUT" "$name_out" > /dev/null; then
        echo "Test ${name_test}: pass"
        count_pass_tests=$((count_pass_tests + 1))
    else
        echo "Test ${name_test}: fail"
        diff -u "$TEST_OUT" "$name_out"
    fi
done

echo "Tests $count_pass_tests / $total_tests passed."

rm -f "$TEST_OUT"