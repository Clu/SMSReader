    #include "Connection.h"


    Connection::Connection(bool debug)
    {
        state = NULL;
        debugInfo = NULL;
        err = new GSM_Error;

        Start(debug);

        return;
    }


    Connection::~Connection()
    {
        delete err;

        Quit();

        return;
    }


    bool Connection::ReadConfig(std::string path)   
    {
        INI_Section *cfg;
        *err = GSM_FindGammuRC(&cfg, path.c_str());

        if (!IsGood(err))
        {
            Quit();
            throw "Couldn't find config";
        }

        *err = GSM_ReadConfig(cfg, GSM_GetConfig(state, 0), 0);

        if (!IsGood(err))
        {
            Quit();
            throw "Couldn't read config";
        }

    	INI_Free(cfg);

        // There could be many config sections in one file, for now we just assume it's always the first
	    GSM_SetConfigNum(state, 1);
    }


    bool Connection::ConnectToPhone()
    {
        *err = GSM_InitConnection(state, 1);
        if (!IsGood(err))
        {
            Quit();
            throw "Couldn't connect to phone";
        }

    }


    boost::shared_ptr<SMSReader> Connection::GetSMSReader()
    {
        return boost::shared_ptr<SMSReader>(new SMSReader(state));
    }


    bool Connection::IsConnected()
    {
        return GSM_IsConnected(state);
    }


    void Connection::Start(bool debug)
    {
        GSM_InitLocales(NULL);
        
        if (debug)
        {
        	debugInfo = GSM_GetGlobalDebug();
	        GSM_SetDebugFileDescriptor(stderr, TRUE, debugInfo);
	        GSM_SetDebugLevel("textall", debugInfo);
        }

        state = GSM_AllocStateMachine();

        if (state == NULL)
            throw "Couldn't initialise state machine";

        if (debug)
        {
	        debugInfo = GSM_GetDebug(state);
	        GSM_SetDebugGlobal(FALSE, debugInfo);
	        GSM_SetDebugFileDescriptor(stderr, TRUE, debugInfo);
	        GSM_SetDebugLevel("textall", debugInfo);
        }

    }


    void Connection::Quit()    
    {
        if (IsConnected())
            GSM_TerminateConnection(state);
    
        if (state != NULL)
        {
            GSM_FreeStateMachine(state);
            state = NULL;
        }

    }



    bool Connection::IsGood(GSM_Error* error)
    {
	    if (*error != ERR_NONE) 
        {
		    std::cout << "ERROR: %s\n" << GSM_ErrorString(*error) << std::endl;
		    return false;
	    }
        return true;
    }

