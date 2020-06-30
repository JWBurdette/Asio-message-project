//By Joshua Burdette  April 2019
//CSC 132 02
//Program uses boost/asio library to send text data to the specified
//port of a specified ip address using UDP protocol. It could be further
//developed into a chat program. Still needs error handling to be fully
//functional. HAS NOT BEEN COMPLETELY DEBUGGED YET

#include <iostream>         //i/o library
#include <boost/asio.hpp>   //header file that includes all headers in boost/asio

//use asio namespace
using namespace boost::asio;

//function that will take data to send over the internet
void sendData(std::string address, std::string message, int port) {

    io_service io_service;               //declare an io_service
    ip::udp::socket socket(io_service);  //create a web socket with io_service
    ip::udp::endpoint target;            //create endpoint for data to be sent to

    //buffer for text data to be put in packet
    int bufferValue = message.size();

    //letters of the alphabet used in hexadecimal
    std::string letters = "abcdef";

    //bool to specify if an ip address is ipv6
    bool ipv6 = false;

    //loop checks if specified address is ipv4 or ipv6 by seeing if it has letters in it
    for (int i = 0; i <= address.size(); i++) {

        //if bool has been set to true, break the loop
        if (ipv6 == true) {
            break;
        }

        //inner loop sees if each character in address is a letter
        for (int j = 0; j <= 5; j++) {
            if (address[i] == letters[j]) {
                socket.open(ip::udp::v6()); //if so, specify ipv6 address for web socket
                ipv6 = true;
                break;
            }
        }
    }
    //otherwise, specify ipv4 socket
    if (ipv6 == false) {
        socket.open(ip::udp::v4());
    }

    //create endpoint with the ip address and port information that has been specified
    target = ip::udp::endpoint(ip::address::from_string(address), port);

    //send the message to the specified address
    socket.send_to(buffer(message, bufferValue), target);//MAY NOT WORK    BUFFERVALUE

    //close socket since we are done
    socket.close();
}

//main function
int main() {

    std::string targetAddress; //string to hold an ip address
    std::string message;       //string to store a message
    int targetPort = 80;       //int to hold port number (80 by default)
    std::string s;             //string to hold whether user wants to rerun program at the end

    //ask user to specify ip address
    std::cout << "Specify an ip address" << std::endl;

    //get input for address
    std::getline(std::cin, targetAddress);

    //ask user to specify the message
    std::cout << "Write a message" << std::endl;

    //clear cin
    std::cin.clear();

    //get message from user
    std::getline(std::cin, message);

    //ask user to specify port number
    std::cout << "Specify a port" << std::endl;

    //clear cin
    std::cin.clear();

    //get input for port
    std::cin >> targetPort;

    //call sendData function to send the message
    sendData(targetAddress, message, targetPort);

    //ask if user wants to run program again
    std::cout << "Message sent." << std::endl;

    //end program
    return 0;
}

