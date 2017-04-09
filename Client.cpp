#include <iostream>
#include <string.h>
#include <netinet/in.h>//for hton
#include <stdlib.h>//for exit
#include <unistd.h>//for close
//#include <netdb.h>//removed and has no effect
using namespace std;

int main()
{
    int client;
    bool end = false;
    int bufsize = 100;
    char buffer[bufsize];

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    int portNum =150000;
    server_addr.sin_port = htons(portNum);


    client = socket(AF_INET, SOCK_STREAM, 0);
    //connect=-1 if no server is found, = 0 otherwise
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
                cin >> buffer;
                send(client, buffer, bufsize, 0);
                if(*buffer=='.') break;
                if(*buffer=='0')
                {
                    end=true;
                    break;
                }
            }  
            cout << "Server: ";
            while (true)
            {
                recv(client, buffer, bufsize, 0);
                cout << buffer << " ";
                if(*buffer=='.') break;
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

