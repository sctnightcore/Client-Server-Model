
#include <iostream>
#include <string.h>
#include <ctime>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>//for inet_ntoa
#include <stdlib.h>//for exit
#include <unistd.h>//close the server and function
using namespace std;

int main()
{
    int client, server;

    //boolean statement to end while loop
    bool end = false;

    //see note
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    int portNum=150000;
    server_addr.sin_port = htons(portNum);
    socklen_t size;
    size = sizeof(server_addr);

    //initialiting a TCP socket connection, cout<<client=3
    client = socket(AF_INET, SOCK_STREAM, 0);
    
    ///binding the socket, it must return 0
    if (bind(client,(struct sockaddr*)&server_addr,size)<0)
    {
        cout<<"Error binding."<<endl;
        cout<< "Use a different portnumber and rerun the program."<<endl;
    }
    else
    {
        cout << "Server: Waiting for incoming connection..." << endl;
        listen(client, 1);//waiting to be connected with clients
        
        server = accept(client,(struct sockaddr *)&server_addr,&size);//server=4

        cout<<"Connection established."<<endl;
        cout << "Enter 0 to end the connection" << endl;
    
    // sending and receiving messages

    //maximum size of each word
    int bufsize = 100;
    char buffer[bufsize];
     do{
         cout << "Client: ";
         while(true)
         {
            recv(server, buffer, bufsize, 0);//receive TCp socket
            cout << buffer << " ";//put space between each word
            if(*buffer=='.') break;// know is my turn to speak
            if (*buffer == '0')//received connection termination request from the client.
            {
                end = true;
                return 0;
            }
          }
       
            cout << "\nServer: ";
          while(true)
             {
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if(*buffer=='.') break;
                if (*buffer == '0') 
                {
                    end = true;
                    break;
                }
             } 
        } while (!end);
        close(server);
    }//end else
    
    close(client);
    return 0;
}
