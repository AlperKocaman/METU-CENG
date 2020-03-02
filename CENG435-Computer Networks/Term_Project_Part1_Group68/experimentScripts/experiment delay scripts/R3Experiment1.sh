s=$(getent ahosts "s" | cut -d " " -f 1 | uniq)

s_adapter=$(ip route get $s | grep -Po '(?<=(dev )).*(?= src| proto)')

s_random_delay=$(( 20 ))"ms"

sudo tc qdisc add dev $s_adapter root netem delay $s_random_delay 5ms distribution normal

d=$(getent ahosts "d" | cut -d " " -f 1 | uniq)

d_adapter=$(ip route get $d | grep -Po '(?<=(dev )).*(?= src| proto)')

d_random_delay=$(( 20 ))"ms"

sudo tc qdisc add dev $d_adapter root netem delay $d_random_delay 5ms distribution normal