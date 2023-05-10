#!/bin/bash
# generate a random string with length from 0 to 100000 (tested only in Mac OS M1)

while true; do
  length=$(jot -r 1 0 100000)
  generated_str=$(LC_CTYPE=C tr -dc '[:alnum:][:punct:]' < /dev/urandom | head -c $length)

  openssl_hash=$(echo -n "$generated_str" | openssl sha256)
  ft_ssl_hash=$(echo -n "$generated_str" | ./ft_ssl sha256 -q)

  if [ "$openssl_hash" != "$ft_ssl_hash" ]; then
    echo "Hashes do not match for string '$generated_str'"
    echo ""
	  echo "$generated_str"
	  echo "$generated_str" > failed
    echo "OpenSSL hash: $openssl_hash"
    echo "ft_ssl hash:   $ft_ssl_hash"
    break
  fi

  echo "String:       $generated_str"
  echo ""
  echo "OpenSSL hash: $openssl_hash"
  echo "ft_ssl hash:   $ft_ssl_hash"
  echo ""
done
