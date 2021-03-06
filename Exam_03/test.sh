gcc micro.c -o nooriginal -Wall -Wextra -Werror
gcc micro_origin.c -o original -Wall -Wextra -Werror
echo ""
echo "TEST - <ex_1>"
echo "NO original"
./nooriginal ex_1
echo "Original"
./original ex_1
echo ""
echo "TEST - <ex_2>"
echo "NO original"
./nooriginal ex_2
echo "Original"
./original ex_2
echo ""
echo "TEST - <ex_3>"
echo "NO original"
./nooriginal ex_3
echo "Original"
./original ex_3
echo ""
echo "TEST - <ex_4>"
echo "NO original"
./nooriginal ex_4
echo "Original"
./original ex_4
echo ""
echo "TEST - <NULL>"
echo "NO original"
./nooriginal
echo "Original"
./original
echo ""
echo "TEST - <Error file>"
echo "NO original"
./nooriginal ex
echo "Original"
./original ex
rm nooriginal
rm original