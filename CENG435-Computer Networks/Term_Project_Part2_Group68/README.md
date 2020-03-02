2237899-Ahmet Dara VEFA && 2169589-Alper KOCAMAN
Start by creating a slice with the given xml file for topology.
Before starting anything else you should syncronize all of your nodes by running 'sudo ntpdate -u pool.ntp.org' command on each node.
execute configureR1.sh and configureR2.sh in their respective nodes r1 and r2 with ./'shellScriptName'.
copy input.txt to source node, you can do this with scp -P <port> -i <ssh-key> <fileName> <destinationAddress>:<targetFilePath>.
If you are doing the first experiment copy contents of "source-r3-dest scripts" to their respective nodes. Else if you are doing second experiment copy contents of "source-r1&r2-dest scripts" folder to their respective nodes.
Execute python scripts on their respective nodes with python3 'scriptName.py'
First execute destination scripts, then execute router scripts and finally execute source scripts. Make sure you have copied input.txt to source.