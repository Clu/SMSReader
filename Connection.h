#ifndef _CONNECTION_H_
#define _CONNECTION_H_

	#include <iostream>
    #include <gammu/gammu.h>
    #include "boost/smart_ptr.hpp" 

    #include "SMSReader.h"

	class Connection
    {
        public:
            Connection(bool debug);
            ~Connection();

            bool ReadConfig(std::string path);
            bool ConnectToPhone();

            boost::shared_ptr<SMSReader> GetSMSReader();

            bool IsConnected();

        private:
            void Start(bool debug);
            void Quit();

            bool IsGood(GSM_Error* error);

            GSM_StateMachine* state;
            GSM_Debug_Info* debugInfo;
            GSM_Error* err;


    };

#endif
