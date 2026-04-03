/*
🧩 Problem: System Logger (C++)

You are building a desktop application with:
UI module
Network module
Database module

Requirements
All modules must log messages
Logs must go to one log file
The log file must be opened only once
Log format must be consistent
No module should create its own logger

Your task
Design and implement:
A Logger class using Singleton pattern

Provide:
logInfo()
logError()

Ensure:
Only one logger instance exists
Thread-safe access (optional challenge)

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Design Thinking:
One Unified log: single log file
log format consistent:\


RULES FOR LOGGING TO KEEP IN MIND!!!
Always keep date in your log file name
Always add some name to your log file name. It will help you in the future to distinguish log files from different instances of your system.
Always log time and date (preferably up to milliseconds resolution) for every log event.
Always store your date as YYYYMMDD. Everywhere. In filename, inside of logfile. It greatly helps with sorting. Some separators are allowed (eg. 2009-11-29).
In general avoid storing logs in database. In is another point of failure in your logging schema.
If you have multithreaded system always log thread id.
If you have multi process system always log process id.
If you have many computers always log computer id.



MM:DD:YY|HH:MM:SS|Process_name|file_name|function_name|Line_number|level_of_log|action|message
03:12:2026|10:12:23|vulkanjs|score.js|get_probability|123|INFO|clicked button|This function has been called

File storage format: 
logs/
2009/
January/
    01012009.log
    02012009.log
    ...
February/
    ...
2008/


Since there are 3 modules I will have a common interface with 3 thread/process which can be logged
UI module: button clicked
Network module: button clicked
Database module: button clicked
*/


#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
    #include <direct.h>  // For _mkdir on Windows
#else
    #include <sys/stat.h>  // For mkdir on Unix/Linux
#endif

std::string get_current_time();
std::string get_current_date();
std::string get_timestamp();
FILE* create_log_file(const std::string &log_directory);


class LoggerApplication
{
    private:
    FILE *log_file = NULL;
    LoggerApplication() = default;
    LoggerApplication(const LoggerApplication&) = delete;
    LoggerApplication& operator=(const LoggerApplication&) = delete;
    
    // Relative path - works for both Windows and Linux
    // Assumes executable runs from builds/ folder, so ../logs/ points to singleton/logs/
    std::string log_directory = "../logs/";

    // Create log file path: logs/MMDDYY_logger.log
    std::string log_file_path = log_directory + get_current_date() + "_logger.log";

    // Create directory if it doesn't exist
    void ensure_log_directory()
    {
        #ifdef _WIN32
            _mkdir(log_directory.c_str());
        #else
            mkdir(log_directory.c_str(), 0777);
        #endif
    }

    FILE *create_log_file(const std:: string& log_directory)
    {

        
        // Open file in append mode
        log_file  = fopen(log_file_path.c_str(), "a+");
        
        if(!log_file)
        {
            std::cerr << "ERROR: Could not open log file: " << log_file_path << std::endl;
            return nullptr;
        }

        return log_file;
    }

    public:
    static LoggerApplication &get_logger_instance()
    {
        static LoggerApplication logger_instance;
        return logger_instance;
    }

    void logInfo(const std::string &module, const std::string &action, const std::string &message)
    {
        log_message("INFO", module, action, message);
    }

    void logError(const std::string &module, const std::string &action, const std::string &message)
    {
        log_message("ERROR", module, action, message);
    }

    void log_message(const std::string &level, const std::string &module, const std::string &action, const std::string &message)
    {
        ensure_log_directory();
        log_file = create_log_file(log_directory);


        // Format: MM:DD:YY|HH:MM:SS|Process|file|function|line|level|action|message
        std::string log_entry = get_timestamp() + "|logger_app|logger_application.cpp|" + module + "|N/A|" + level + "|" + action + "|" + message;
        
        
        fprintf(log_file, "%s\n", log_entry.c_str());
        fflush(log_file); 
        fclose(log_file);

    
        // Also print to console
        std::cout << "[" << level << "] " << message << std::endl;
        std::cout << "Logged to: " << log_file_path << std::endl;
        std::cout << "Instance address: " << &LoggerApplication::get_logger_instance() << std::endl;
    }

};








class Module
{
    public:
    virtual void button_clicked() = 0;
};


class UIModule : public Module
{
    public:
    void button_clicked() override
    {
        LoggerApplication::get_logger_instance().logInfo("UIModule", "button_clicked", "Hello from the UI Module");
    }
};

class NETWORKModule : public Module
{
    public:
    void button_clicked() override
    {
        LoggerApplication::get_logger_instance().logInfo("NETWORKModule", "button_clicked", "Hello from the Network Module");
    }
};

class DATABASEModule : public Module
{
    public:
    void button_clicked() override
    {
        LoggerApplication::get_logger_instance().logInfo("DATABASEModule", "db_query", "Database connection established");
    }
};


// Get current time in HH:MM:SS format
std::string get_current_time()
{
    std::time_t rawtime;
    std::time(&rawtime);
    std::tm* timeinfo = std::localtime(&rawtime);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << timeinfo->tm_hour << ":"
        << std::setfill('0') << std::setw(2) << timeinfo->tm_min << ":"
        << std::setfill('0') << std::setw(2) << timeinfo->tm_sec;

    return oss.str();
}

// Get current date in MMDDYY format
std::string get_current_date()
{
    std::time_t rawtime;
    std::time(&rawtime);
    std::tm* timeinfo = std::localtime(&rawtime);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << (timeinfo->tm_mon + 1) 
        << std::setfill('0') << std::setw(2) << timeinfo->tm_mday
        << std::setfill('0') << std::setw(2) << (timeinfo->tm_year % 100);

    return oss.str();
}

// Get full timestamp in MM:DD:YY|HH:MM:SS format
std::string get_timestamp()
{
    std::time_t rawtime;
    std::time(&rawtime);
    std::tm* timeinfo = std::localtime(&rawtime);

    std::ostringstream oss;
    // Date part: MM:DD:YY
    oss << std::setfill('0') << std::setw(2) << (timeinfo->tm_mon + 1) << ":"
        << std::setfill('0') << std::setw(2) << timeinfo->tm_mday << ":"
        << std::setfill('0') << std::setw(2) << (timeinfo->tm_year % 100) << "|";
    
    // Time part: HH:MM:SS
    oss << std::setfill('0') << std::setw(2) << timeinfo->tm_hour << ":"
        << std::setfill('0') << std::setw(2) << timeinfo->tm_min << ":"
        << std::setfill('0') << std::setw(2) << timeinfo->tm_sec;

    return oss.str();
}



int main()
{
    std::cout << "=== Logger Application Started ===" << std::endl;
    std::cout << "Log files will be saved in: design_patterns/creational_patterns/singleton/logs/" << std::endl;
    std::cout << std::endl;

    Module *UI = new UIModule();
    Module *network = new NETWORKModule();
    Module *database = new DATABASEModule();

    // Test all modules
    UI->button_clicked();
    network->button_clicked();
    database->button_clicked();

    // Test error logging
    LoggerApplication::get_logger_instance().logError("SystemModule", "critical_error", "Test error message");

    std::cout << std::endl;
    std::cout << "=== All logs written successfully ===" << std::endl;

    delete UI;
    delete network;
    delete database;
    
    return 0;
}

//Review and refine has to be done

