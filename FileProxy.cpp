    #include "FileProxy.h"


    FileProxy::FileProxy()
    {
        return;
    }


    FileProxy::~FileProxy()
    {
        return;
    }


    bool FileProxy::SaveSMS(GSM_SMSMessage* sms, std::string dir, std::string msg)
    {

        std::fstream smsFile(GetFilename(sms, dir).c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

        if (smsFile.bad())
            return false;

        std::cout << GetFilename(sms, dir) << std::endl;

        smsFile.write(msg.c_str(), msg.length());


        if (smsFile.bad())
            return false;

        smsFile.flush();

        smsFile.close();

        return true;
    }


    bool FileProxy::SMSAlreadyExists(GSM_SMSMessage* sms, std::string dir)
    {
        struct stat info; 

        // XXX: stat is a little bit messy, but *meh* it'll do the job
        if (stat(GetFilename(sms, dir).c_str(), &info) == 0)
        {
            return true;
        }

        return false;
    }


    std::string FileProxy::GetFilename(GSM_SMSMessage* sms, std::string dir)
    {
        std::stringstream fileName;
        fileName << dir;
        fileName << DecodeUnicodeConsole(sms->Number) << "_";
        fileName << sms->DateTime.Second << ":" << sms->DateTime.Minute << ":" << sms->DateTime.Hour << ":" 
                 << sms->DateTime.Day << ":"  << sms->DateTime.Month << ":"  << sms->DateTime.Year;

        std::string fileString = fileName.str();
        return fileString;
    }
