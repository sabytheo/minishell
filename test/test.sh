
echo ls -l
echo "   echo      hello    world   "
echo "echo 'hello world'"
echo 'echo "42 is cool"'
echo "echo 'single' \"double\""
echo "echo 'unclosed"
echo "ls | grep minishell"
echo "cat < input.txt > output.txt"
echo "echo test >> log.txt << EOF"\
echo "echo \$USER"\
echo "echo \"Hello \$USER\""
echo "echo '\$USER'"
echo "echo \$DOES_NOT_EXIST"
echo "echo   \$USER  'is'  \"cool\"  > file | grep 'c'"
echo "cat < file | grep foo | sort > sorted.txt"
echo -e "echo\thello\t\tworld"
echo ""
echo "        "
echo "echo \\$USER"
echo "echo \$?"
