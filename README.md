
A Client/Server model that communicate on two terminals in the linux enviroment.
<br />
Tool: visual studio code--love the split editor function
<br />
<br />
**What is a socket?**<br />
A socket is the basic building block for communication.<br />
<br />
**What is a stream socket?**<br />
A bidirectional flow of data that when two of this sockets connected, it provide an interface.<br />
<br />
**How dose this program work?**<br />
The first step is to create a stream socket.<br />
client=socket(AF_INET, SOCK_STREAM,0);<br />
Af_INEt: Internet domain.<br />
SOCK_STREAM: stream socket type.<br />
0: tells the system to select an appropriate protocol that made up the communication domain.<br />
<br />
Once the stream socket is created successful, it needs to be bounded with a name to process communication. <br />

bind(client, name, namelen)<br />
name: For this part, I just used what I found from google and place it here. Because this related to something called Network Address function, and I am not going to dig too deep into this at this stage. But I understand this is something about binding the internet address and port number with the socket<br />
<br />
After the socket is bounded, it will start to wait for incoming connections using the function listen(client,1). Where 1 is the maximum number of connections.<br />
<br />
When the server is listening for connection requests, the connect function in the client’s program connects to the server that has the same port number. Then the server will accept the connection using the function connect();<br />
<br />
what is next is to read and send messages to each other using the read() and write().<br />

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


** 04/15/2017**<br />
Fixed the issue of binding the socket.the issue occured after closing the program and try to recompile it.<br />

cause:TCP sockets can have relatively long delay between adding data to the send buffer and having the TCP implementation really send that data.<br />
So, when the TCP socket is closed, the send buffer still has the pending data which is actually considered as sent. The socket then will go into a state call time_wait. In this state, the socket will wait untill all pending data has been successfully sent or until time out.<br />
In short, even though the socket is closed, the data is still pending. <br />

Solution: using SO_REUSEADDR solved the issue and which play an important role in the way of how sockets bind to the ports.
<br />
Link to the solutions:<br />
1, http://stackoverflow.com/questions/14388706/socket-options-so-reuseaddr-and-so-reuseport-how-do-they-differ-do-they-mean-t
2, http://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr
