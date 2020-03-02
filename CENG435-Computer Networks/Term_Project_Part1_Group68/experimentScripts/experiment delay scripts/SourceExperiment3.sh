r3=$(getent ahosts "r3" | cut -d " " -f 1 | uniq)

r3_adapter=$(ip route get $r3 | grep -Po '(?<=(dev )).*(?= src| proto)')

r3_random_delay=$(( 50 ))"ms"

sudo tc qdisc add dev $r3_adapter root netem delay $r3_random_delay 5ms distribution normal