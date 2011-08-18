#ifndef _SMSREADER_H_
#define _SMSREADER_H_ 

	#include <iostream>
    #include <gammu/gammu.h>

    #include "FileProxy.h"

    class SMSReader
    {
        public:
            SMSReader(GSM_StateMachine* state);
            ~SMSReader();

           bool RefreshSMS();
        
        private:

            // XXX: Refactoring needed <-> Connection::IsGood
            bool IsGood(GSM_Error* error, int debug);
            bool CheckIfExists(GSM_SMSMessage* sms);
            bool GetInboxSMS();
            int GetInboxFolderId();

            GSM_StateMachine* state;

    };

#endif
