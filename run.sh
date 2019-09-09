user=tester

scp -P 22055 *.sh ${user}@localhost:/home/${user}/workspace/
ssh -p 22055 ${user}@localhost 'cd ${HOME}/workspace/ ; ./debug.sh ./sandbox.sh  ./ip_test.sh'