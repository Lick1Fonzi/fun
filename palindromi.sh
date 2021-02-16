read str
lung=${#str}
declare -i endindex=$((lung-1))

function palindrec(){
	if [ ${str:$1:1} == " " ]; then
	return palindrec $(($1+1)) $2;
	elif [ ${str:$2:1} == " " ]; then
	return palindrec $1 $(($2-1));
	fi
	if [ ${str:$1:1} == ${str:$2:1} ]; then
	if [ $1 -eq $2 ]; then
	return 0;
	fi
	return palindrec $(( $1 + 1 )) $(( $2 - 1 )); 
	else
	return 1;
	fi
}
(palindrec 0 $endindex ) 2> /dev/null
var=$?
if [ $var -ne 1 ]; then
var=0
echo $var
else
echo $var
fi

