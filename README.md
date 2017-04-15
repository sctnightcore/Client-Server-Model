
A Client/Server model that communicate on two terminals in the linux enviroment.
<br />
<br />

Socket type used: Stream socket.
<br />
<br />

Tool: visual studio code--love the split editor function
<br />
<br />
# Links<br />

Visual Studio code:https://code.visualstudio.com/download<br />
Link to the tutorial: http://users.pja.edu.pl/~jms/qnx/help/tcpip_4.25_en/prog_guide/sock_advanced_tut.html<br />
TCP/IP Libraries: http://users.pja.edu.pl/~jms/qnx/help/tcpip_4.25_en/prog_guide/libraries.html<br />


# Note<br />
The limitations that I need to work on are:

1, Only one to one connection. For mutiple clients, I need to learn about threading.

2, Message has to be ended with a chosen chracter in order to break the while loop instead of after pressing the enter key. 

3, Only one message at a time after ending it.

Currently, I am working on 2 and 3. At the same time, I will also study threading.


# 04/15/2017<br />
Fixed the issue of binding the socket.the issue occured after closing the program and try to recompile it.<br />

cause:TCP sockets can have relatively long delay between adding data to the send buffer and having the TCP implementation really send that data.<br />
So, when the TCP socket is closed, the send buffer still has the pending data which is actually considered as sent. The socket then will go into a state call time_wait. In this state, the socket will wait untill all pending data has been successfully sent or until time out.<br />
In short, even though the socket is closed, the data is still pending. <br />

Solution: using SO_REUSEADDR solved the issue and which play an important role in the way of how sockets bind to the ports.
<br />
Link to the solutions:<br />
1, http://stackoverflow.com/questions/14388706/socket-options-so-reuseaddr-and-so-reuseport-how-do-they-differ-do-they-mean-t
2, http://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr
