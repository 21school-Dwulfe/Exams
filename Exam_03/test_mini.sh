gcc mini.c -o my_mini -Wall -Wextra -Werror -lm
gcc mini_origin.c -o original_mini -Wall -Wextra -Werror -lm
echo "\n\n"
echo "TEST - <ex_1>"
echo "NO original_mini"
./my_mini ex_1
echo "Original"
./original_mini ex_1_mini
echo "\n\n"
echo "TEST - <ex_2>"
echo "NO original_mini"
./my_mini ex_2
echo "Original"
./original_mini ex_2_mini
echo "\n\n"
echo "TEST - <NULL>"
echo "NO original_mini"
./my_mini
echo "Original"
./original_mini
echo "\n\n"
echo "TEST - <Error file>"
echo "NO original_mini"
./my_mini ex
echo "Original"
./original_mini ex
rm my_mini
rm original_mini
