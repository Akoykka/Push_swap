#valgrinds everything
#input filename consisting of lines of random numbers.
while read -r line
do
	valgrind --leak-check=full ./push_swap "$line" | valgrind --leak-check=full ./checker "$line"
done < "$1"