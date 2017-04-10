#include <iostream>
#include <string.h>
#include <netinet/in.h>//for hton
#include <stdlib.h>//for exit
#include <unistd.h>//for close
using namespace std;

int main()
{
    int client;
    bool end = false;
    int bufsize = 100;//max lenghth of each word, red=3
    char buffer[bufsize];

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    int portNum =150000;
    server_addr.sin_port = htons(portNum);


    client = socket(AF_INET, SOCK_STREAM, 0);//initializing the TCP socket
    
    //connect return -1 if the server is not compiled, return 0 otherwise
    if( connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr))==-1)
        cout<<"No server is found, programing terminated."<<endl;   
    else
    {
        cout << "Connection with the server established."<<endl;
        cout<<"you can send '0' to the server to end the connection."<<endl;
        do 
         {   
            cout << "\nClient: ";
            while (true)
            {
                cin >> buffer;//your message
                send(client, buffer, bufsize, 0);//send it to the server
                if(*buffer=='.') break;//tells the server that you have done talking
                if(*buffer=='0')//tells the server to terminate the connection
                {
                    end=true;
                    break;
                }
            }  
            cout << "Server: ";
            while (true)
            {
                recv(client, buffer, bufsize, 0);//receive the message from the server
                cout << buffer << " ";
                if(*buffer=='.') break;//the message from the server must end with * so the client knows is its turn to talk.
                if(*buffer=='0') 
                 {
                    end =true;
                    break;
                 }
            }
        } while (!end);
    }
    close(client);
    return 0;
}

