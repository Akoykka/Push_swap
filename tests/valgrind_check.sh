#valgrinds everything
#input filename consisting of lines of random numbers.
linenbr=1
while read -r line
do
	echo "THE LINE IS =======xxxxxxxxxxx===xxxxxxxxxxxx---||||||||||||||||============== $linenbr :"
	let "linenbr"++
	valgrind --leak-check=full ./push_swap "$line" | valgrind --leak-check=full ./checker "$line"
done < "$1"