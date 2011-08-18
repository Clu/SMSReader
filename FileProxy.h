#ifndef _FILEPROXY_H_
#define _FILEPROXY_H_

    #include <fstream>
    #include <iostream>
    #include <sstream>

    #include <cstring>

    // Should be system independant 
    #include <sys/stat.h> 

    #include "boost/smart_ptr.hpp"

    #include <gammu/gammu.h>

    #include "Config.h"



    /*
     *  SMS are saved in the directory set by dir
     *  Naming convention is: PhoneNummber_seconds:minutes:hours:day:month:year
     *                        this should be unique enough.
     */


    class FileProxy
    {
        public:

            FileProxy();
            ~FileProxy();

            // XXX: Ugly shit, but i'm to drunk to fix it (msg should be retrieved directly by sms->Text but whatever)
            //      Messed up code isn't a problem as long as it'll do the job (c) Anonymous
            static bool SaveSMS(GSM_SMSMessage* sms, std::string dir, std::string msg);
            static bool SMSAlreadyExists(GSM_SMSMessage* sms, std::string dir);


        private:
            static std::string GetFilename(GSM_SMSMessage* sms, std::string dir);

    };

#endif
