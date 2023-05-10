echo "echo "42 is nice" | ./ft_ssl sha256"
echo '(stdin)= 35f1d6de0302e2086a4e472266efb3a9'
echo "42 is nice" | ./ft_ssl MD5
echo ""

echo "echo "42 is nice" | ./ft_ssl md5 -p"
echo '("42 is nice")= 35f1d6de0302e2086a4e472266efb3a9'
echo "42 is nice" | ./ft_ssl MD5 -p
echo ""

echo 'echo "Pity the living." | ./ft_ssl md5 -q -r'
echo 'e20c3b973f63482a778f3fd1869b7f25'
echo "Pity the living." | ./ft_ssl MD5 -q -r
echo ""

echo 'echo "And above all," > file'
echo "And above all," > file
echo './ft_ssl md5 file'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
./ft_ssl MD5 file
echo ""

echo './ft_ssl md5 -r file'
echo '53d53ea94217b259c11a5a2d104ec58a file'
./ft_ssl MD5 -r file
echo ""

echo './ft_ssl md5 -s "pity those that aren'"'"'t following baerista on spotify."'
echo 'MD5 ("pity those that aren'"'"'t following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f'
./ft_ssl MD5 -s "pity those that arent following baerista on spotify."
echo ""

echo 'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file'
echo '("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
echo "be sure to handle edge cases carefully" | ./ft_ssl MD5 -p file
echo ""

echo 'echo "some of this will not make sense at first" | ./ft_ssl md5 file'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
echo "some of this will not make sense at first" | ./ft_ssl MD5 file
echo ""

echo 'echo "but eventually you will understand" | ./ft_ssl md5 -p -r file'
echo '("but eventually you will understand")= dcdd84e0f635694d2a943fa8d3905281'
echo '53d53ea94217b259c11a5a2d104ec58a file'
echo "but eventually you will understand" | ./ft_ssl MD5 -p -r file
echo ""

echo 'echo "GL HF let'"'"'s go" | ./ft_ssl md5 -p -s "foo" file'
echo '("GL HF let'"'"'s go")= d1e3cc342b6da09480b27ec57ff243e2'
echo 'MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
echo '--------------------------------------------------------'
echo "GL HF let's go" | ./ft_ssl MD5 -p -s "foo" file
echo ""

echo 'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"'
echo '("one more thing")= a0bd1876c6f011dd50fae52827f445f5'
echo 'acbd18db4cc2f85cedef654fccc4a4d8 "foo"'
echo '53d53ea94217b259c11a5a2d104ec58a file'
echo 'ft_ssl: md5: -s: No such file or directory'
echo 'ft_ssl: md5: bar: No such file or directory'
echo '--------------------------------------------------------'
echo "one more thing" | ./ft_ssl MD5 -r -p -s "foo" file -s "bar"
echo ""

echo 'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file'
echo 'just to be extra clear'
echo '3ba35f1ea0d170cb3b9a752e3360286c'
echo 'acbd18db4cc2f85cedef654fccc4a4d8'
echo '53d53ea94217b259c11a5a2d104ec58a'
echo '--------------------------------------------------------'
echo "just to be extra clear" | ./ft_ssl MD5 -r -q -p -s "foo" file
rm file
