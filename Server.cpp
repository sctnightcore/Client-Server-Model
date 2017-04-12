
#include <sys/socket.h>//AF_INET, sock)stream, socket, connect
#include <sys/types.h>//without this header file the program still runs
#include <netinet/in.h>//htons, also fix struct sockaddr_in server={0} has initializer but incomplete tyoe error
#include <iostream>
#include <unistd.h>//read(), write(), close()
using namespace std;

int main()
{
    /*  client/server are two file descriptors
        These two variables store the values returned 
        by the socket system call and the accept system call.
    */

     int client, server;

    /*
    initializing a TCP socket connection with the below function
    sock_fd = socket( domain, type, protocol);

    domain: The domain is specified as one of the manifest constants 
    defined in the file <sys/socket.h>. For the Internet domain, this 
    constant is AF_INET. 

    Protocol: leave protocol unspecified (a value of 0), the system
     will select an appropriate protocol from those protocols that 
     make up the communication domain and that can be used to support 
     the requested socket type.(not 100% always 0)

    type: Stream socket
    Provides for the bidirectional, reliable, sequenced, and 
    unduplicated flow of data without record boundaries. Aside 
    from the bidirectional nature of the dataflow, a pair of connected
    stream sockets provides an interface nearly identical to that of 
    pipes.
    
    Note: Sockets are typed according to the communication properties visible 
    to a user. Processes are presumed to communicate only between sockets of the same type. 

    client: This call would result in a stream socket being created
     with the TCP protocol providing the underlying communication 
     support.

    */
     client = socket(AF_INET, SOCK_STREAM, 0);

     if(client>0)
     cout<<"Sucessfully established socket connection."<<endl;
     else
       {
           cout<<"Failed to establish sockey connection"<<endl;
           return 0;
       }
 /*
 
        struct sockaddr_in
        {
          short   sin_family;
          u_short sin_port;
          struct  in_addr sin_addr;
          char    sin_zero[];
        };
        
        sin_family:specifies the address family, ususally the constant "AF_INET".
      
        sin_port: specifies the port number and must be used with htons()
                  which is a function that converts the "host byte order" to 
                  "network byte order" so it can transmitted and routed properly when
                  opennig the socket connection. the reason for this is that computers and network 
                  protocols order their bytes in a non-compatible fashion, each the opposite of the other.

        sin_addr: holds the IP address return by inet_addr() to be used in the socket connection
        sin_zero: used with a char array buffer, usually set to 0

        Need to initialize server_addr
    */

    struct sockaddr_in sin={0};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);

   /*
        bind( s, name, namelen );
        The bind() system call binds a socket to an address, 
        in this case the address of the current host and port number 
        on which the server will run(sockaddr_in).
        Success=0, error=-1, same for connect()
   */

    if (bind(client,(struct sockaddr*)&sin,sizeof(sin))==-1)
         cout<<"Error binding."<<endl;
    
    else//returned 0
    {
        cout << "Server: Waiting for incoming connection..." << endl;
       
       /*
        The listen system call allows the process to listen 
        on the socket for connections. 
        The program will be stay idle here if there are no 
        incomming connections.
        The first argument is the socket file descriptor, 
        and the second is the size for the number of clients 
        The maximum size permitted by most 
        systems is 5.
       */

        listen(client, 1);

        /*
       after establishing connection with client, the accept() retrurns a new socket which
       responsible all communication in this connection.
       The second qrgument is a reference pointer to the addrees of the client
       size is the size of this structure

       socklen_t=int type of width of at least 32 bits
       */

        socklen_t size= sizeof(sin);
        server = accept(client,(struct sockaddr *)&sin,&size);
        cout<<"Connection established."<<endl;
        cout << "Enter 0 to end the connection" << endl;
        cout<<endl;
       /*
       During run time, I noticed that if msize is set to 5, then any words 
       that with more than 5 characters will not be display normally
       100 is big enough.
       */

        int msize = 100;
        char message[msize];
        bool end = false;//boolean statement to end while loop
        do
        {
            cout<<"Client: ";
            while(true)

            {    
                 /*
                send(s, buf, sizeof (buf), flags);
                recv(s, buf, sizeof (buf), flags);
                recv() and send() are virtually identical to read() and 
                write(), the extra flags argument is important (the flag
                values are defined in <sys/socket.h>).
                */
                read(server, message, msize);//receive TCp socket
               if(*message!='0')//if the message contains 0, then no need to show it
                    cout<<message << " ";//put space between each word
                if(*message=='.') break;// know is my turn to speak
                if (*message == '0')//received connection termination request from the client.
                {
                    end = true;
                    return 0;
                }
            }
            cout << "\nServer: ";
            while(true)
            {
                cin >> message;
                write(server, message, msize);
                if(*message=='.') break;
                if (*message == '0') 
                {
                    end = true;
                    break;
                }
            } 
        } while (!end);
        /*
            shutdown(s,0) vs close(s)
            close is the way to destroy a socket.
            Using shutdown is a flexible way to block communication in one o both directions,
            and you will still be able to receive pending data from the other side.
        */
        close(client);
        close(server);
      
    }//end else
    return 0;
}
