# MosquittoSend
Little program to send mosquitto commands from command line, commands are linked in text file.

  ____________________________________________________________________________________________________
  -- The program sends mosquitto commands along with data stored in a tab-delimited command file --
  Use: mosquitto_send [ARGUMENTS]");
    -f FILENAME       : change filename to FILENAME
    -c COMMAND NAME   : search and execute given command
    -s SLEEPTIME      : set given sleeptime between commands, default 0
    -h HOST           : change default host mosquitto server to HOST
    -i ID             : device ID, default 0, set it before a command to modify all the following commands
    -a PREFIX         : set the prefix parameter, dependency (-b), set it before a command to modify all the following commands
    -b SUFFIX         : set the suffix parameter, dependency (-a), set it before a command to modify all the following commands 
    -d                : debug mode
    -m                : show help
  ____________________________________________________________________________________________________
