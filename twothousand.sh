input="./2000"
read -r line
./push_swap "$line" | wc -l
./push_swap "$line" | ./checker "$line"
