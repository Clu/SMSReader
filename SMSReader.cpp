    #include "SMSReader.h"



    SMSReader::SMSReader(GSM_StateMachine* state)
    {
        this->state = state;
        return;
    }


    SMSReader::~SMSReader()
    {
        return;
    }


    bool SMSReader::RefreshSMS()
    {
        GSM_Error err;
        GSM_MultiSMSMessage sms;
        int inboxId = GetInboxFolderId();

        err = ERR_NONE;
        int start = TRUE;

        bool quit = false;

	    sms.Number = 0;
	    sms.SMS[0].Location = 0;
	    sms.SMS[0].Folder = 0;

	    while (err == ERR_NONE && !quit) 
        {
            err = GSM_GetNextSMS(state, &sms, start);

            if (err == ERR_EMPTY) 
                break;

            if (!IsGood(&err, 2))
                break;

            start = FALSE;

		    for (int i = 0; i<sms.Number; i++) {

                if (sms.SMS[i].Folder != inboxId)
                    continue;

                if (!CheckIfExists(&sms.SMS[i]))
                    if (!FileProxy::SaveSMS(&sms.SMS[i], UNREAD_PATH, DecodeUnicodeConsole(sms.SMS[i].Text)))
                        return false;
            }

        }

        return true;
    }


    bool SMSReader::IsGood(GSM_Error* error, int debug)
    {
	    if (*error != ERR_NONE)
        {
		    std::cout << "ERROR " << "[" << debug << "]: " << std::endl << GSM_ErrorString(*error) << std::endl;
		    return false;
	    }
        return true;
    }


    bool SMSReader::CheckIfExists(GSM_SMSMessage* sms)
    {
        if (FileProxy::SMSAlreadyExists(sms, UNREAD_PATH) || FileProxy::SMSAlreadyExists(sms, READ_PATH))
            return true;

        return false;
    }


    int SMSReader::GetInboxFolderId()
    {
        GSM_SMSFolders folders;
        GSM_Error error;

        // Get folder list
        error = GSM_GetSMSFolders(state, &folders);
        if (!IsGood(&error, 1))
            return -1;

        // Search for the inbox folder
        for (int i=1; i<folders.Number; i++)
            if (folders.Folder[i].InboxFolder)
            {
                // Folder enumeration begins with 1 and not 0. Fucking mobile phone programmers should learn how to count!!!!!
                return i+1;
            }
        // I think this is an impossible condition, but you'll never know
        return -2;
    }

