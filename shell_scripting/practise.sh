#!/bin/bash
echo "it works"

# for loop
for i in {1..5}
do
echo "count isssss: $i"
done


# while loop
count=1
while [ $count -le 5 ]; do
  echo "Count: $count"
  count=$((count + 1))
done

# get input
name=""
echo "enter name pls"
read name
echo "your name is $name"

# if else
if [ "$name" = "hashir" ]; then
    echo "names match!"
else
    echo "names do not match"
fi