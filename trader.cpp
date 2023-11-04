#include "receiver.h"
#include <vector>
#include <string>
using namespace std;

void part_1(string message){
    string message_copy = message;

        vector<string> Inputs;          // To save the message into different strings that are accumulated in a vector
        int pos1 = 0;
        int pos2 = message_copy.find('#');
        while(true){
            if(pos2 == -1){
                break;
            }
            Inputs.push_back(message_copy.substr(pos1, pos2+1-pos1));
            pos1 = pos2 + 2;
            pos2 = message_copy.find('#',pos1);
        }
        //cout<<"pikachu"<<endl;

        vector<string> Stocks;
        vector<int> curr_pr;                // These 2 vectors will help in remembering the latest price;
        vector<string> Outputs;             // To save outputs

        int pos3;
        string curr_in;
        while(!Inputs.empty()){
            curr_in = Inputs[0];

            pos1 = curr_in.find(' ');
            pos2 = curr_in.find(' ',pos1+1);
            pos3 = curr_in.find('#');

            string stock_name = curr_in.substr(0,pos1);
            int stock_price = stoi(curr_in.substr(pos1+1, pos2));

            bool found = false;
            int n = 0;

            for (const std::string& element : Stocks) {
                if (element == stock_name) {
                    found = true;
                    break;
                }
                n++;
            }

            if(!found){
                Stocks.push_back(stock_name);
                curr_pr.push_back(stock_price);
                if(curr_in[pos3-1] == 's') curr_in[pos3-1] = 'b';
                else curr_in[pos3-1] = 's';
                Outputs.push_back(curr_in.substr(0,curr_in.length()-1));
            }

            else{
                if(curr_in[pos3-1] == 's'){
                    if(stock_price < curr_pr[n]){
                        curr_in[pos3-1] = 'b';
                        curr_pr[n] = stock_price;
                        Outputs.push_back(curr_in.substr(0,curr_in.length()-1));
                    }
                    else{
                        Outputs.push_back("No Trade");
                    }
                }

                else{
                    if(stock_price > curr_pr[n]){
                        curr_in[pos3-1] = 's';
                        curr_pr[n] = stock_price;
                        Outputs.push_back(curr_in.substr(0,curr_in.length()-1));
                    }
                    else{
                        Outputs.push_back("No Trade");
                    }
                }
            }

            Inputs.erase(Inputs.begin());
        }

        while(!Outputs.empty()){
            cout<<Outputs[0]<<endl;
            Outputs.erase(Outputs.begin());
        }
}

int main(int argc, char* argv[]) {

    Receiver rcv;
    sleep(5);
    string message = rcv.readIML();
    string message_copy = message;


    if(strcmp(argv[1],"1") == 0){
        part_1(message);
    }

    return 0;
}
