    #include <iostream>

    #include "boost/smart_ptr.hpp" 
    
    #include "Connection.h"
    #include "SMSReader.h"

    int main(int argc, char** argv)
    {

        boost::shared_ptr<SMSReader> reader;
        
        try 
        {
            Connection c(false);
            c.ReadConfig("k800i");
            c.ConnectToPhone();
            reader = c.GetSMSReader();

            if (reader.get()->RefreshSMS())
                std::cout << "Successfully read all messages!" << std::endl;

        } catch (const char* exception)
        {
            reader.reset();
            std::cout << exception << std::endl;
            return -1;
        }

        reader.reset();
        return 0;
    }
