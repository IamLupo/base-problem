nr="$1"

for f in *.txt;
do
	output=$(cat "$f" | grep $nr --color --only-matching -Fx)
	
	if [ -n "$output" ]; then
		echo $f;
		echo $output;
	fi
done
