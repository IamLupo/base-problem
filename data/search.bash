nr="$1"

for f in *.txt;
do
	output=$(cat "$f" | grep $nr --color -n --only-matching -Fx)
	
	if [ -n "$output" ]; then
		echo $f;
		echo $output;
	fi
done
