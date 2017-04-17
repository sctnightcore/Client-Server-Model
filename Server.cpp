#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
     int client, server;

     //create socket of stream type
     client = socket(AF_INET, SOCK_STREAM, 0);
    
     //the setsockopt() solved the bind error issue, see note for detail
     int one=1;
     if(setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &one,sizeof(one)) ==0)
     cout<<"Sucessfully established socket connection."<<endl;
     else//=-1
       {
           cout<<"Failed to establish sockey connection"<<endl;
           return 0;
       }
 
    //Network address function that need to be used to bind a name to the socket
    //the portnumber must be the same between the connections
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    if (bind(client,(struct sockaddr*)&sin,sizeof(sin))==-1)//set the source address and port
         cout<<"Error binding."<<endl;
    
    else//returned 0
    {
        cout << "Server: Waiting for incoming connection..." << endl;

        //listening to connection requests
        listen(client, 1); 

        //accept the connection requests
        socklen_t size= sizeof(sin);
        server = accept(client,(struct sockaddr *)&sin,&size);

        cout<<"Connection established."<<endl;
        cout << "Enter 0 to end the connection" << endl;
        cout<<endl;
      
        int msize = 100;// just the max size of the lenghth of each english word
        char message[msize];
        bool end = false;

        //start the communication between the two connections
        do
        {
            cout<<"Client: ";
            while(true)

            {    
                
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
       
        close(client);
        close(server);
      
    }
    return 0;
}
