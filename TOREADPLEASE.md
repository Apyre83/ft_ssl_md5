gcc main.c src/DES/ft_des.c -Iinclude -Ift_printf/includes -Iget_next_line -o ft_ssl
./ft_ssl des -e -k 0123456789ABCDEF -i input.txt -o output.enc                
./ft_ssl des -d -k 0123456789ABCDEF -i output.enc -o decrypted.txt
cat output.enc
echo '\nRESULT:'
cat decrypted.txt
