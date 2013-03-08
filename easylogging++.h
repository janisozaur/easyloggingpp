///////////////////////////////////////////////////////////////////////////////////
//                                                                               //
//   easylogging++.h - Core of EasyLogging++                                     //
//                                                                               //
//   EasyLogging++ v6.10                                                         //
//   Cross platform logging made easy for C++ applications                       //
//   Author Majid Khan <mkhan3189@gmail.com>                                     //
//   http://www.icplusplus.com                                                   //
//   https://github.com/mkhan3189/EasyLoggingPP                                  //
//                                                                               //
//   Copyright (c) 2012-2013 Majid Khan                                          //
//                                                                               //
//   This software is provided 'as-is', without any express or implied           //
//   warranty. In no event will the authors be held liable for any damages       //
//   arising from the use of this software.                                      //
//                                                                               //
//   Permission is granted to anyone to use this software for any purpose,       //
//   including commercial applications, and to alter it and redistribute         //
//   it freely, subject to the following restrictions:                           //
//                                                                               //
//   1. The origin of this software must not be misrepresented; you must         //
//      not claim that you wrote the original software. If you use this          //
//      software in a product, an acknowledgment in the product documentation    //
//      would be appreciated but is not required.                                //
//                                                                               //
//   2. Altered source versions must be plainly marked as such, and must         //
//      not be misrepresented as being the original software.                    //
//                                                                               //
//   3. This notice may not be removed or altered from any source                //
//      distribution                                                             //
//                                                                               //
//   Part of this software uses/include code from TinyThread++                   //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////

#ifndef EASYLOGGINGPP_H
#define EASYLOGGINGPP_H

// _LOGGING_ENABLED specifies whether or not writing logs are enabled.
// If this is set to 0, nothing will be logged. On the contrary, 1 means
// logs are enabled.
#define _LOGGING_ENABLED 1

// Following configurations are for each logging level, each with three
// parts; note: *** refers to log level in each of the following description.
//
// PART 1
// ======
// _ENABLE_***_LOGS specifies whether or not *** logs are enabled.
// This is similar to _LOGGING_ENABLED except the level effected is
// specific to config name only. 1 = enabled; 0 = disabled
//
// PART 2
// ======
// _***_LOGS_TO_STANDARD_OUTPUT specifies whether or not *** logs are enabled
// to be written to standard output. Standard output varies from OS to OS,
// typically it is terminal for linux and command prompt for windows.
// This will only effect corresponding log level.
//
// PART 3
// ======
// _***_LOGS_TO_FILE specifies whether or not *** logs are to be written to
// file. It is recommended to be always 1 i.e, enabled. If you wish some logs
// not be recorded to log file then you proabably want to disable those logs

#define _ENABLE_DEBUG_LOGS 1
#define _DEBUG_LOGS_TO_STANDARD_OUTPUT 1
#define _DEBUG_LOGS_TO_FILE 1

#define _ENABLE_INFO_LOGS 1
#define _INFO_LOGS_TO_STANDARD_OUTPUT 1
#define _INFO_LOGS_TO_FILE 1

#define _ENABLE_WARNING_LOGS 1
#define _WARNING_LOGS_TO_STANDARD_OUTPUT 1
#define _WARNING_LOGS_TO_FILE 1

#define _ENABLE_ERROR_LOGS 1
#define _ERROR_LOGS_TO_STANDARD_OUTPUT 1
#define _ERROR_LOGS_TO_FILE 1

#define _ENABLE_FATAL_LOGS 1
#define _FATAL_LOGS_TO_STANDARD_OUTPUT 1
#define _FATAL_LOGS_TO_FILE 1

#define _ENABLE_PERFORMANCE_LOGS 1
#define _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT 1
#define _PERFORMANCE_LOGS_TO_FILE 1

#define _ENABLE_VERBOSE_LOGS 1
#define _VERBOSE_LOGS_TO_STANDARD_OUTPUT 1
#define _VERBOSE_LOGS_TO_FILE 1

#define _ENABLE_QA_LOGS 1
#define _QA_LOGS_TO_STANDARD_OUTPUT 1
#define _QA_LOGS_TO_FILE 1

//
// High-level log evaluation
//
#if ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))
#    define _ENABLE_EASYLOGGING 1
#endif // ((_LOGGING_ENABLED) && !defined(_DISABLE_LOGS))

//
// OS evaluation
//
// Windows
#if defined(_WIN32)
#    define _WINDOWS 1
#    define _WINDOWS_32 1
#endif // defined(_WIN32)
#if defined(_WIN64)
#    define _WINDOWS 1
#    define _WINDOWS_64 1
#endif // defined(_WIN64)
// Linux
#if (defined(__linux) || defined(__linux__))
#    define _LINUX 1
#endif // (defined(__linux) || defined(__linux__))
// Mac
#if defined(__APPLE__)
#    define _MAC 1
#endif // defined(__APPLE__)

#define _UNIX ((_LINUX || _MAC) && (!_WINDOWS))

//
// Log location macros
//
#if !defined(__FILE__)
#    define __FILE__ ""
#endif // !defined(__FILE__)
#if !defined(__LINE__)
#    define __LINE__ ""
#endif // !defined(__LINE__)
// Determine appropriate function macro according to current compiler
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#    define __func__ __FUNCTION__
#elif defined(__GNUC__) && (__GNUC__ >= 2)
#   define __func__ __PRETTY_FUNCTION__
#else
#    define __func__ ""
#endif // defined(_MSC_VER) && (_MSC_VER >= 1020)

//
// Compiler evaluation
//
// GNU
#if defined(__GNUC__)
#    if defined(__GXX_EXPERIMENTAL_CXX0X__)
#        define _CXX0X 1
#    endif // defined(__GXX_EXPERIMENTAL_CXX0X__)
#endif // defined(__GNUC__)
// VC++ (http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx)
#if defined(_MSC_VER)
#    if (_MSC_VER == 1600)
#        define _CXX0X 1
#    elif (_MSC_VER == 1700)
#        define _CXX11 1
#    endif // (_MSC_VER == 1600)
#endif // defined(_MSC_VER)

#if (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
// Embedded fast_mutex (part of TinyThread++)
#ifndef _FAST_MUTEX_H_
#define _FAST_MUTEX_H_
#if !defined(_TTHREAD_PLATFORM_DEFINED_)
#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#define _TTHREAD_WIN32_
#else
#define _TTHREAD_POSIX_
#endif
#define _TTHREAD_PLATFORM_DEFINED_
#endif
#if (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))) || \
    (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))) || \
    (defined(__GNUC__) && (defined(__ppc__)))
#define _FAST_MUTEX_ASM_
#else
#define _FAST_MUTEX_SYS_
#endif

#if defined(_TTHREAD_WIN32_)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define __UNDEF_LEAN_AND_MEAN
#endif
#include <windows.h>
#define _WINDOWS_HEADER_INCLUDED_FROM_FAST_MUTEX_H // Not part of fastmutex
#ifdef __UNDEF_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef __UNDEF_LEAN_AND_MEAN
#endif
#else
#ifdef _FAST_MUTEX_ASM_
#include <sched.h>
#else
#include <pthread.h>
#endif
#endif
namespace tthread {
class fast_mutex {
public:
    /// Constructor.
#if defined(_FAST_MUTEX_ASM_)
    fast_mutex() : mLock(0) {}
#else
    fast_mutex()
    {
#if defined(_TTHREAD_WIN32_)
        InitializeCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_init(&mHandle, NULL);
#endif
    }
#endif
#if !defined(_FAST_MUTEX_ASM_)
    ~fast_mutex()
    {
#if defined(_TTHREAD_WIN32_)
        DeleteCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_destroy(&mHandle);
#endif
    }
#endif
    inline void lock()
    {
#if defined(_FAST_MUTEX_ASM_)
        bool gotLock;
        do {
            gotLock = try_lock();
            if(!gotLock)
            {
#if defined(_TTHREAD_WIN32_)
                Sleep(0);
#elif defined(_TTHREAD_POSIX_)
                sched_yield();
#endif
            }
        } while(!gotLock);
#else
#if defined(_TTHREAD_WIN32_)
        EnterCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_lock(&mHandle);
#endif
#endif
    }
    inline bool try_lock()
    {
#if defined(_FAST_MUTEX_ASM_)
        int oldLock;
#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile (
                    "movl $1,%%eax\n\t"
                    "xchg %%eax,%0\n\t"
                    "movl %%eax,%1\n\t"
                    : "=m" (mLock), "=m" (oldLock)
                    :
                    : "%eax", "memory"
                    );
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &mLock;
        __asm {
            mov eax,1
                    mov ecx,ptrLock
                    xchg eax,[ecx]
                    mov oldLock,eax
        }
#elif defined(__GNUC__) && (defined(__ppc__))
        int newLock = 1;
        asm volatile (
                    "\n1:\n\t"
                    "lwarx  %0,0,%1\n\t"
                    "cmpwi  0,%0,0\n\t"
                    "bne-   2f\n\t"
                    "stwcx. %2,0,%1\n\t"
                    "bne-   1b\n\t"
                    "isync\n"
                    "2:\n\t"
                    : "=&r" (oldLock)
                    : "r" (&mLock), "r" (newLock)
                    : "cr0", "memory"
                    );
#endif
        return (oldLock == 0);
#else
#if defined(_TTHREAD_WIN32_)
        return TryEnterCriticalSection(&mHandle) ? true : false;
#elif defined(_TTHREAD_POSIX_)
        return (pthread_mutex_trylock(&mHandle) == 0) ? true : false;
#endif
#endif
    }
    inline void unlock()
    {
#if defined(_FAST_MUTEX_ASM_)
#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
        asm volatile (
                    "movl $0,%%eax\n\t"
                    "xchg %%eax,%0\n\t"
                    : "=m" (mLock)
                    :
                    : "%eax", "memory"
                    );
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
        int *ptrLock = &mLock;
        __asm {
            mov eax,0
                    mov ecx,ptrLock
                    xchg eax,[ecx]
        }
#elif defined(__GNUC__) && (defined(__ppc__))
        asm volatile (
                    "sync\n\t"
                    : : : "memory"
                    );
        mLock = 0;
#endif
#else
#if defined(_TTHREAD_WIN32_)
        LeaveCriticalSection(&mHandle);
#elif defined(_TTHREAD_POSIX_)
        pthread_mutex_unlock(&mHandle);
#endif
#endif
    }
private:
#if defined(_FAST_MUTEX_ASM_)
    int mLock;
#else
#if defined(_TTHREAD_WIN32_)
    CRITICAL_SECTION mHandle;
#elif defined(_TTHREAD_POSIX_)
    pthread_mutex_t mHandle;
#endif
#endif
};
}
#endif // _FAST_MUTEX_H_
//
// Mutex specific initialization
//
#    define MUTEX_TYPE tthread::fast_mutex
#    define _MUTEX_SPECIFIC_INIT static MUTEX_TYPE mutex_;
#    define _LOCK_MUTEX easyloggingpp::internal::mutex_.lock();
#    define _UNLOCK_MUTEX easyloggingpp::internal::mutex_.unlock();
#else
#    define _MUTEX_SPECIFIC_INIT
#    define _LOCK_MUTEX
#    define _UNLOCK_MUTEX
#endif // (!defined(_DISABLE_MUTEX) && (_ENABLE_EASYLOGGING))
//
// Includes
//
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#if _WINDOWS
#    include <direct.h>
#    ifndef (_WINDOWS_HEADER_INCLUDED_FROM_FAST_MUTEX_H)
#        include <windows.h>
#    endif
#endif // _WINDOWS
#if _UNIX
#    include <sys/stat.h>
#    include <sys/time.h>
#endif // _UNIX
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace easyloggingpp {

namespace configurations {

// This section contains configurations that are to set by developer.
// These sections can be splitted into two parts;
//
//   * Log formats
//   * Miscellaneous configurations
//
// First part contains all the formatting configuration for each log
// level. Developers are expected to only change the values and not
// data type or constant name.
// Format specifiers used are as following:
//
//  SPECIFIER     |                  DESCRIPTION
// ===============|==================================================
//   %level       |   Log level, e.g, INFO, DEBUG, ERROR etc
//   %datetime    |   Current date and time (while writing log)
//   %date        |   Current date only
//   %time        |   Current time only
//   %user        |   User running the application
//   %host        |   Host/computer name the application is running on
//   %func        |   Function of logging
//   %loc         |   Filename and line number of logging
//   %log         |   The actual log message
//   %vlevel      |   Verbose level (only applicable for VERBOSE logs)
//   \n           |   New line character
//   \t           |   Tab character
//
// Further reading on:
// https://github.com/mkhan3189/EasyLoggingPP/blob/master/README.md#log-format
const std::string    DEFAULT_LOG_FORMAT       =    "%type [%level] [%datetime] %log\n";
const std::string    DEBUG_LOG_FORMAT         =    "%type [%level] [%datetime] [%user@%host] [%func] [%loc] %log\n";
const std::string    INFO_LOG_FORMAT          =    DEFAULT_LOG_FORMAT;
const std::string    WARNING_LOG_FORMAT       =    DEFAULT_LOG_FORMAT;
const std::string    ERROR_LOG_FORMAT         =    DEFAULT_LOG_FORMAT;
const std::string    FATAL_LOG_FORMAT         =    DEFAULT_LOG_FORMAT;
const std::string    PERFORMANCE_LOG_FORMAT   =    DEFAULT_LOG_FORMAT;
const std::string    VERBOSE_LOG_FORMAT       =    "%type [%level-%vlevel] [%datetime] %log\n";
const std::string    QA_LOG_FORMAT            =    DEFAULT_LOG_FORMAT;

// Part 2 is miscellaneous configurations

// SHOW_STD_OUTPUT
//   High level configuration to determine whether or not to show log to standard
//   output i.e, terminal or command prompt. If this is set to false, logs will not
//   be shown to standard output regardless of log level setting _***_LOGS_TO_STANDARD_OUTPUT
//   Recommendation: true
const bool           SHOW_STD_OUTPUT          =    true;


// SAVE_TO_FILE
//   Same as SHOW_STD_OUTPUT but for saving to file. If this is false, logs will not
//   be written to file regardless of log level setting _***_LOGS_TO_FILE.
//   Be careful when you set this option to false
//   Recommendation: true
const bool           SAVE_TO_FILE             =    true;


// LOG_FILENAME
//   Filename of log file. This should only be filename and not the whole path.
//   Path is set in different configuration below (CUSTOM_LOG_FILE_LOCATION).
//   If custom location is not used, log will be saved in executable path.
const std::string    LOG_FILENAME             =    "myeasylog.log";


// CUSTOM_LOG_FILE_LOCATION
//   Path where log file should be saved. Configuration below (USE_CUSTOM_LOCATION)
//   must be set to true in order for this to take affect.
//   NOTES
//    * This location path should end with slash ( '/' for linux and '\' for windows)
//    * This has to be absolute path. Relative paths will not work
//   Recommendation: Set value according to your need - Do not leave empty
//   If you do not want to use this set USE_CUSTOM_LOCATION to false instead.
const std::string    CUSTOM_LOG_FILE_LOCATION =    "logs/";


// USE_CUSTOM_LOCATION
//   If this is true, logs will be saved to location set in configuration above
//   (CUSTOM_LOG_FILE_LOCATION). Default log location is application run path.
//   Recommendation: As required
const bool           USE_CUSTOM_LOCATION      =    true;

// SHOW_START_FUNCTION_LOG
//   When using performance logging, this determines whether or not to show
//   when a certain function has started executing.
//   Recommendation: false
const bool           SHOW_START_FUNCTION_LOG  =    false;

} // namespace configurations
} // namespace easyloggingpp

//
// Low-level log evaluation
//
#define _DEBUG_LOG       ((_ENABLE_DEBUG_LOGS) && !defined(_DISABLE_DEBUG_LOGS) && (_ENABLE_EASYLOGGING))
#define _INFO_LOG        ((_ENABLE_INFO_LOGS) && !defined(_DISABLE_INFO_LOGS) && (_ENABLE_EASYLOGGING))
#define _WARNING_LOG     ((_ENABLE_WARNING_LOGS) && !defined(_DISABLE_WARNING_LOGS) && (_ENABLE_EASYLOGGING))
#define _ERROR_LOG       ((_ENABLE_ERROR_LOGS) && !defined(_DISABLE_ERROR_LOGS) && (_ENABLE_EASYLOGGING))
#define _PERFORMANCE_LOG ((_ENABLE_PERFORMANCE_LOGS) && !defined(_DISABLE_PERFORMANCE_LOGS) && (_ENABLE_EASYLOGGING))
#define _FATAL_LOG       ((_ENABLE_FATAL_LOGS) && !defined(_DISABLE_FATAL_LOGS) && (_ENABLE_EASYLOGGING))
#define _VERBOSE_LOG     ((_ENABLE_VERBOSE_LOGS) && !defined(_DISABLE_VERBOSE_LOGS) && (_ENABLE_EASYLOGGING))
#define _QA_LOG          ((_ENABLE_QA_LOGS) && defined(_QUALITY_ASSURANCE) && (_ENABLE_EASYLOGGING))

#if _UNIX
// Permissions for unix-based systems
#define _LOG_PERMS S_IRUSR | S_IWUSR | S_IXUSR | S_IWGRP | S_IRGRP | S_IXGRP | S_IWOTH | S_IXOTH
#endif // _UNIX

#define _SUPPRESS_UNUSED_WARN(x) (void)x

namespace easyloggingpp {

namespace version {
static const char* versionNumber = "6.10";
} // namespace version

namespace internal {
_MUTEX_SPECIFIC_INIT
namespace helper {
    // OSUtilities class specifically written for EasyLogging++
    // This class contains functionalities related to operating system
    class OSUtilities {
    public:
        // Runs command on terminal and returns the output.
        // This is applicable only on linux and mac, for all other OS, an empty string is returned.
        static std::string getBashOutput(const char* command) {
#if _UNIX
            FILE* proc = popen(command, "r");
            if (proc != NULL) {
                const short hBuffMaxSize = 20;
                char hBuff[hBuffMaxSize];
                fgets(hBuff, hBuffMaxSize, proc);
                pclose(proc);
                short actualHBuffSize = strlen(hBuff);
                if (actualHBuffSize > 0) {
                    if (hBuff[actualHBuffSize - 1] == '\n') {
                        hBuff[actualHBuffSize - 1] = '\0';
                    }
                    return std::string(hBuff);
                }
                return std::string();
            } else {
                return std::string();
            }
#else
            return "";
#endif // _UNIX
        }

        // Gets current username.
        static const char* currentUser(void) {
#if _WINDOWS
            const char* username = getenv("USERNAME");
#elif _UNIX
            const char* username = getenv("USER");
#endif // _WINDOWS
            if ((username == NULL) || (!strcmp(username, ""))) {
                // Try harder on unix-based systems
                return OSUtilities::getBashOutput("whoami").c_str();
            } else {
                return username;
            }
        }

        // Gets current host name or computer name.
        static const char* currentHost(void) {
#if _WINDOWS
            const char* hostname = getenv("COMPUTERNAME");
#elif _UNIX
            const char* hostname = getenv("HOSTNAME");
#endif // _WINDOWS
            if ((hostname == NULL) || ((strcmp(hostname, "") == 0))) {
                // Try harder on unix-based systems
                hostname = OSUtilities::getBashOutput("hostname").c_str();
                if (!strcmp(hostname, "")) {
                    return "unknown-host";
                } else {
                    return hostname;
                }
            } else {
                return hostname;
            }
        }

        // Determines whether or not provided path_ exist in current file system
        static inline bool pathExists(const char* path_) {
            if (path_ == NULL) {
                return false;
            }
#if _WINDOWS
            DWORD fileType = GetFileAttributesA(path_);
            if (fileType == INVALID_FILE_ATTRIBUTES) {
                return false;
            }
            return (fileType & FILE_ATTRIBUTE_DIRECTORY);
#elif _UNIX
            struct stat st;
            return (stat(path_, &st) == 0);
#endif // _WINDOWS
        }

        // Creates path as specified
        static bool createPath(const std::string& path_) {
            if (path_.empty()) {
                return false;
            }
            if (OSUtilities::pathExists(path_.c_str())) {
                return true;
            }
#   if _WINDOWS
            const char* pathDelim_ = "\\";
#   elif _UNIX
            const char* pathDelim_ = "/";
#   endif // _WINDOWS
            int status = -1;
            char* currPath_ = const_cast<char*>(path_.c_str());
            std::string buildingPath_;
            if (path_[0] == '/') {
                buildingPath_ = "/";
            }
            currPath_ = strtok(currPath_, pathDelim_);
            while (currPath_ != NULL) {
                buildingPath_.append(currPath_);
                buildingPath_.append(pathDelim_);
#   if _WINDOWS
                status = _mkdir(buildingPath_.c_str());
#   elif _UNIX
                status = mkdir(buildingPath_.c_str(), _LOG_PERMS);
#   endif // _WINDOWS
                currPath_ = strtok(NULL, pathDelim_);
            }
            if (status == -1) {
                return false;
            }
            return true;
        }

    private:
        // Disable initilization
        OSUtilities(void);
        OSUtilities(const OSUtilities&);
        OSUtilities& operator=(const OSUtilities&);
    }; // class OSUtilities

    class LogManipulator {
    public:
        static void updateFormatValue(const std::string& formatSpecifier_,
                                      const std::string& value_,
                                      std::string& currentFormat_) {
            size_t foundAt = -1;
            while ((foundAt = currentFormat_.find(formatSpecifier_, foundAt + 1)) != std::string::npos){
                if (currentFormat_[foundAt > 0 ? foundAt - 1 : 0] == 'E') {
                    currentFormat_.erase(foundAt > 0 ? foundAt - 1 : 0, 1);
                    ++foundAt;
                } else {
                    currentFormat_ = currentFormat_.replace(foundAt, formatSpecifier_.size(), value_);
                    continue;
                }
            }
        }
    private:
        // Disable initilization
        LogManipulator(void);
        LogManipulator(const LogManipulator&);
        LogManipulator& operator=(const LogManipulator&);
    }; // class LogManipulator

    class DateUtilities {
    public:
        enum kDateTimeFormat { kDateOnly, kTimeOnly, kDateTime };

        // Gets current date and time with milliseconds.
        static std::string getDateTime(unsigned int format_) {
            long milliSeconds = 0;
            const int kDateBuffSize_ = 30;
            const char* kDateFormatLocal_ = "%d/%m/%Y";
            const char* kTimeFormatLocal_ = "%H:%M:%S";
            char dateBuffer_[kDateBuffSize_] = "";
            char dateFormat_[kDateBuffSize_];
            if (format_ == kDateOnly) {
                strcpy(dateFormat_, kDateFormatLocal_);
            } else if (format_ == kTimeOnly) {
                strcpy(dateFormat_, kTimeFormatLocal_);
            } else {
                strcpy(dateFormat_, kDateFormatLocal_);
                strcat(dateFormat_, " ");
                strcat(dateFormat_, kTimeFormatLocal_);
            }
#if _UNIX
            timeval currTime;
            gettimeofday(&currTime, NULL);
            if ((format_ == kDateTime) || (format_ == kTimeOnly)) {
                milliSeconds = currTime.tv_usec / 1000;
            }
            struct tm * timeInfo = localtime(&currTime.tv_sec);

            strftime(dateBuffer_, kDateBuffSize_, dateFormat_, timeInfo);
            if ((format_ == kDateTime) || (format_ == kTimeOnly)) {
                sprintf(dateBuffer_, "%s.%03ld", dateBuffer_, milliSeconds);
            }
#elif _WINDOWS
            if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", dateBuffer_, kDateBufferSize_) != 0) {
                static DWORD oldTick = GetTickCount();
                if ((format_ == kDateTime) || (format_ == kTimeOnly)) {
                    milliSeconds = (long)(GetTickCount() - oldTick) % 1000;
                    sprintf(dateBuffer_, "%s.%03ld", dateBuffer_, milliSeconds);
                }
            }
#endif // _UNIX
            return std::string(dateBuffer_);
        }

        static std::string formatSeconds(double seconds_) {
            double result = seconds_;
            std::string unit = "seconds";
            std::stringstream stream_;
            if (result > 60.0f) {
                result /= 60; unit = "minutes";
                if (result > 60.0f) {
                    result /= 60; unit = "hours";
                    if (result > 24.0f) {
                        result /= 24; unit = "days";
                    }
                }
            }
            stream_ << result << " " << unit;
            return stream_.str();
        }
    private:
        // Disable initilization
        DateUtilities(void);
        DateUtilities(const DateUtilities&);
        DateUtilities& operator=(const DateUtilities&);
    }; // class DateUtilities
} // namespace helper

using namespace easyloggingpp::configurations;
using namespace easyloggingpp::internal::helper;

template<class Class, class Iterator, class Predicate>
class Register {
public:
    explicit Register(void) {
    }

    explicit Register(const Register& register_) :
        list_(register_.list_) {
    }

    Register& operator=(const Register& register_) {
        list_ = register_.list_;
    }

    virtual ~Register(void) {
        unregisterAll();
    }

    template<typename T2>
    Class* get(const T2& t2_) {
        Iterator iter = std::find_if(list_.begin(), list_.end(), Predicate(t2_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }

    inline size_t count(void) const {
        return list_.size();
    }

    inline bool empty(void) const {
        return list_.empty();
    }
protected:
    inline void registerNew(Class* t_) {
        list_.push_back(t_);
    }

    inline void unregisterAll(void) {
        if (!empty()) {
            std::for_each(list_.begin(), list_.end(), std::bind1st(std::mem_fun(&Register::unregister), this));
            list_.clear();
        }
    }

    inline void unregister(Class* t_) {
        if (t_) {
            delete t_;
            t_ = NULL;
        }
    }

    std::vector<Class*> list_;
}; // class Register

class LogType {
public:
    typedef std::vector<LogType*>::const_iterator Iterator;

    explicit LogType(const std::string& name_) :
        name_(name_),
        logName_(logName_)
    {
    }

    explicit LogType(const std::string& name_,
                      const std::string& logName_) :
        name_(name_),
        logName_(logName_)
    {
    }

    inline std::string name(void) const {
        return name_;
    }

    inline std::string logName(void) const {
        return logName_;
    }

    class Predicate {
    public:
        explicit Predicate(const std::string& name_) :
            name_(name_)
        {
        }
        bool operator()(const LogType* logType_) {
            return ((logType_ != NULL) &&
                    (logType_->name_ == name_));
        }
    private:
        std::string name_;
    };
private:
    std::string name_;
    std::string logName_;
}; // class LogType

class RegisteredLogTypes : public Register<LogType, LogType::Iterator, LogType::Predicate> {
public:
    explicit RegisteredLogTypes(void)
    {
        registerNew(new LogType("TrivialLogger", "LOG"));
        registerNew(new LogType("BusinessLogger", "BUSINESS"));
        registerNew(new LogType("SecurityLogger", "SECURITY"));
    }
}; // class RegisteredLogTypes

class SeverityLevel {
public:
    typedef std::vector< SeverityLevel* >::const_iterator Iterator;

    explicit SeverityLevel(const std::string& name_,
                           const std::string& format_,
                           bool toStandardOutput_,
                           bool toFile_) :
        name_(name_),
        format_(format_),
        toStandardOutput_(toStandardOutput_),
        toFile_(toFile_)
    {
        LogManipulator::updateFormatValue("%level", name_, this->format_);
    }

    inline bool operator==(const std::string& name_) const {
        return this->name_ == name_;
    }

    inline std::string name(void) const {
        return name_;
    }

    inline std::string format(void) const {
        return format_;
    }

    inline bool toStandardOutput(void) const {
        return toStandardOutput_;
    }

    inline bool toFile(void) const {
        return toFile_;
    }

    class Predicate {
    public:
        explicit Predicate(const std::string& name_) :
            name_(name_)
        {
        }
        inline bool operator()(const SeverityLevel* level_) {
            return *level_ == name_;
        }

    private:
        std::string name_;
    };

private:
    std::string name_;
    std::string format_;
    bool toStandardOutput_;
    bool toFile_;
}; // class SeverityLevel

class RegisteredSeverityLevels : public Register<SeverityLevel, SeverityLevel::Iterator, SeverityLevel::Predicate> {
public:
    explicit RegisteredSeverityLevels(void)
    {
        registerNew(
                    new SeverityLevel("DEBUG", DEBUG_LOG_FORMAT, _DEBUG_LOGS_TO_STANDARD_OUTPUT, _DEBUG_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel("INFO", INFO_LOG_FORMAT, _INFO_LOGS_TO_STANDARD_OUTPUT, _INFO_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel("WARNING", WARNING_LOG_FORMAT, _WARNING_LOGS_TO_STANDARD_OUTPUT, _WARNING_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel("ERROR", ERROR_LOG_FORMAT, _ERROR_LOGS_TO_STANDARD_OUTPUT, _ERROR_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel("FATAL", FATAL_LOG_FORMAT, _FATAL_LOGS_TO_STANDARD_OUTPUT, _FATAL_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel("PERFORMANCE", PERFORMANCE_LOG_FORMAT, _PERFORMANCE_LOGS_TO_STANDARD_OUTPUT, _PERFORMANCE_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel("VERBOSE", VERBOSE_LOG_FORMAT, _VERBOSE_LOGS_TO_STANDARD_OUTPUT, _VERBOSE_LOGS_TO_FILE));
        registerNew(
                    new SeverityLevel("QA", QA_LOG_FORMAT, _QA_LOGS_TO_STANDARD_OUTPUT, _QA_LOGS_TO_FILE));
    }
}; // class RegisteredSeverityLevels

class LogCounter {
public:
    typedef std::vector< LogCounter* >::iterator Iterator;
    const static unsigned int kMax = 5000;

    explicit LogCounter(void) :
        file_(""),
        line_(0),
        position_(1)
    {

    }

    explicit LogCounter(const char* file_,
                        unsigned long int line_) :
        file_(file_),
        line_(line_),
        position_(1) {}

    inline void resetLocation(const char* file_,
                              unsigned long int line_) {
        this->file_ = file_;
        this->line_ = line_;
    }

    inline void reset(unsigned int n_) {
        if (position_ >= LogCounter::kMax) {
            position_ = (n_ >= 1 ? 5000 % n_ : 0);
        }
        ++position_;
    }

    inline const char* file(void) const {
        return file_;
    }

    inline unsigned long int line(void) const {
        return line_;
    }

    inline unsigned int position(void) const {
        return position_;
    }

    class Predicate {
    public:
        explicit Predicate(const char* file_, unsigned long int line_)
            : file_(file_),
              line_(line_)
        {
        }
        inline bool operator()(const LogCounter* counter_) {
            return ((counter_ != NULL) &&
                    (counter_->file_ == file_) &&
                    (counter_->line_ == line_));
        }

    private:
        const char* file_;
        unsigned long int line_;
    };

private:
    const char* file_;
    unsigned long int line_;
    unsigned int position_;
}; // class LogCounter

class RegisteredCounters : public Register<LogCounter, LogCounter::Iterator, LogCounter::Predicate>  {
public:
    bool valid(const char* file_, unsigned long int line_, unsigned int n_) {
        bool result_ = false;
        LogCounter* counter_ = get(file_, line_);
        if (counter_ == NULL) {
            registerNew(counter_ = new LogCounter(file_, line_));
        }
        if (n_ >= 1 && counter_->position() != 0 && counter_->position() % n_ == 0) {
            result_ = true;
        }
        counter_->reset(n_);
        return result_;
    }

private:
    LogCounter* get(const char* file_, unsigned long int line_) {
        LogCounter::Iterator iter = std::find_if(list_.begin(), list_.end(), LogCounter::Predicate(file_, line_));
        if (iter != list_.end() && *iter != NULL) {
            return *iter;
        }
        return NULL;
    }
}; // class RegisteredCounters

class Logger {
public:
    explicit Logger(void) :
        kFinalFilename_(USE_CUSTOM_LOCATION ?
                            CUSTOM_LOG_FILE_LOCATION + LOG_FILENAME:
                            LOG_FILENAME),
        kUser_(OSUtilities::currentUser()),
        kHost_(OSUtilities::currentHost()),
        initialized_(true),
        stream_(new std::stringstream()),
        logFile_(NULL),
        registeredLogTypes_(new RegisteredLogTypes()),
        registeredSeverityLevels_(new RegisteredSeverityLevels()),
        registeredLogCounters_(new RegisteredCounters())
    {
        if (SAVE_TO_FILE) {
            fileGood_ = USE_CUSTOM_LOCATION ?
                        !LOG_FILENAME.empty() && OSUtilities::createPath(CUSTOM_LOG_FILE_LOCATION) :
                        !LOG_FILENAME.empty();
            if (fileGood_) {
#if (_ALWAYS_CLEAN_LOGS)
                logFile_ = new std::ofstream(kFinalFilename_.c_str(), std::ofstream::out);
#else
                logFile_ = new std::ofstream(kFinalFilename_.c_str(), std::ofstream::out | std::ofstream::app);
#endif

                if (logFile_->is_open()) {
                    logFile_->close();
                } else {
                    if (logFile_) {
                        delete logFile_;
                        logFile_ = NULL;
                    }
                    fileGood_ = false;
                }
            } else {
                std::cout << "\nBad file for writing logs to [" << kFinalFilename_ << "] Please check the configurations\n";
            }
        }
    }

    virtual ~Logger(void) {
        if (stream_) {
            delete stream_;
            stream_ = NULL;
        }
        if (logFile_) {
            delete logFile_;
            logFile_ = NULL;
        }
        if (registeredLogTypes_) {
            delete registeredLogTypes_;
            registeredLogTypes_ = NULL;
        }
        if (registeredSeverityLevels_) {
            delete registeredSeverityLevels_;
            registeredSeverityLevels_ = NULL;
        }
        if (registeredLogCounters_) {
            delete registeredLogCounters_;
            registeredLogCounters_ = NULL;
        }
    }

    void setArgs(int argc, char** argv) {
        while (argc-- > 0) {
#if _VERBOSE_LOG
            const unsigned short kMaxVerboseLevel = 9;
            // Look for --v=X argument
            if ((strlen(argv[argc]) >= 5) &&
                    (argv[argc][0] == '-') &&
                    (argv[argc][1] == '-') &&
                    (argv[argc][2] == 'v') &&
                    (argv[argc][3] == '=') &&
                    (isdigit(argv[argc][4]))) {
                // Current argument is --v=X
                // where X is a digit between 0-9
                appVerbose_ = static_cast<short>(atoi(argv[argc] + 4));
            }
            // Look for --verbose argument
            else if ((strlen(argv[argc]) == 9) &&
                     (argv[argc][0] == '-') &&
                     (argv[argc][1] == '-') &&
                     (argv[argc][2] == 'v') &&
                     (argv[argc][3] == 'e') &&
                     (argv[argc][4] == 'r') &&
                     (argv[argc][5] == 'b') &&
                     (argv[argc][6] == 'o') &&
                     (argv[argc][7] == 's') &&
                     (argv[argc][8] == 'e')) {
                appVerbose_ = kMaxVerboseLevel;
            }
            // Look for -v argument
            else if ((strlen(argv[argc]) == 2) &&
                     (argv[argc][0] == '-') &&
                     (argv[argc][1] == 'v')) {
                appVerbose_ = kMaxVerboseLevel;
            }
#else
            _SUPPRESS_UNUSED_WARN(argv);
            appVerbose_ = 0;
#endif // _VERBOSE_LOG
        }
    }

    inline void setArgs(int argc, const char** argv) {
        char** args = const_cast<char**>(argv);
        setArgs(argc, args);
    }

    inline void buildLine(const std::string& logType_, const std::string& severityLevel_, const char* func_,
                          const char* file_, const unsigned long int line_, unsigned short verboseLevel_ = 0) {
        LogType* type_ = registeredLogTypes_->get(logType_);
        SeverityLevel* level_ = registeredSeverityLevels_->get(severityLevel_);
        currLogLine_ = level_->format();
        std::string formatSpecifier_ = "";
        std::string value_ = "";
        // DateTime
        unsigned int dateTimeFormat_ = 0;
        if (level_->format().find("%datetime") != std::string::npos) {
            dateTimeFormat_ = DateUtilities::kDateTime;
            formatSpecifier_ = "%datetime";
        } else if (level_->format().find("%date") != std::string::npos) {
            dateTimeFormat_ = DateUtilities::kDateOnly;
            formatSpecifier_ = "%date";
        } else if (level_->format().find("%time") != std::string::npos) {
            dateTimeFormat_ = DateUtilities::kTimeOnly;
            formatSpecifier_ = "%time";
        } else {
            dateTimeFormat_ = 0;
        }
        if (dateTimeFormat_ != 0) {
            value_ = DateUtilities::getDateTime (dateTimeFormat_);
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        if (type_ && level_->format().find("%type") != std::string::npos) {
            value_ = type_->logName();
            formatSpecifier_ = "%type";
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        if (level_->format().find("%loc") != std::string::npos) {
            tempStream_ << file_ << ":" << line_;
            value_ = tempStream_.str();
            formatSpecifier_ = "%loc";
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        if (level_->format().find("%func") != std::string::npos) {
            value_ = std::string(func_);
            formatSpecifier_ = "%func";
            LogManipulator::updateFormatValue(formatSpecifier_, value_, currLogLine_);
        }
        if (level_->format().find("%user") != std::string::npos) {
            formatSpecifier_ = "%user";
            LogManipulator::updateFormatValue(formatSpecifier_, kUser_, currLogLine_);
        }
        if (level_->format().find("%host") != std::string::npos) {
            formatSpecifier_ = "%host";
            LogManipulator::updateFormatValue(formatSpecifier_, kHost_, currLogLine_);
        }
        if (level_->format().find("%log") != std::string::npos) {
            formatSpecifier_ = "%log";
            LogManipulator::updateFormatValue(formatSpecifier_, stream_->str(), currLogLine_);
        }
        // Verbose specific log
        if (verboseLevel_ > 0) {
            // Verbose level
            tempStream_.str("");
            tempStream_ << verboseLevel_;
            value_ = tempStream_.str();
            formatSpecifier_ = "%vlevel";
            LogManipulator::updateFormatValue(formatSpecifier_, tempStream_.str(), currLogLine_);
        }
        write(level_);
    }

    inline void write(SeverityLevel* level_) {
        if (SHOW_STD_OUTPUT && level_->toStandardOutput()) {
            std::cout << currLogLine_;
        }
        if (SAVE_TO_FILE && fileGood() && level_->toFile()) {
            logFile_->open(kFinalFilename_.c_str(), std::ofstream::out | std::ofstream::app);
            (*logFile_) << currLogLine_;
            logFile_->close();
        }
        clear();
    }

    inline void clear(void) {
        stream_->str("");
        tempStream_.str("");
    }

    inline std::stringstream* stream(void) {
        return stream_;
    }

    inline RegisteredSeverityLevels* registeredSeverityLevels(void) const {
        return registeredSeverityLevels_;
    }

    inline RegisteredCounters* registeredLogCounters(void) {
        return registeredLogCounters_;
    }

    inline bool fileGood(void) const {
        return fileGood_;
    }

    inline unsigned short appVerbose(void) const {
        return appVerbose_;
    }

    inline bool initialized(void) const {
        return initialized_;
    }

    const std::string kFinalFilename_;
    const std::string kUser_;
    const std::string kHost_;
private:
    bool initialized_;
    bool fileGood_;
    std::string currLogLine_;
    std::stringstream tempStream_;
    std::stringstream* stream_;
    std::ofstream* logFile_;
    RegisteredLogTypes* registeredLogTypes_;
    RegisteredSeverityLevels* registeredSeverityLevels_;
    RegisteredCounters* registeredLogCounters_;
    unsigned short appVerbose_;
}; // class Logger

//
// Helper macros
//
#define _LOGGER easyloggingppLogger_
#define _QUALIFIED_LOGGER ::easyloggingpp::internal::_LOGGER
#define _STREAM_PTR _LOGGER.stream()
#define _STREAM *_STREAM_PTR
#define _WRITE_LOG(type_, level_, func_, file_, line_)                                     \
    if (logAspect_ == kNormal) {                                                    \
    _LOGGER.buildLine(type_, level_, func_, file_, line_);                                 \
} else if (logAspect_ == kConditional && condition_) {                              \
    _LOGGER.buildLine(type_, level_, func_, file_, line_);                                 \
} else if (logAspect_ == kInterval) {                                               \
    if (_LOGGER.registeredLogCounters()->valid(file_, line_, counter_)) {           \
    _LOGGER.buildLine(type_, level_, func_, file_, line_);                                 \
}                                                                                   \
}

#define _LOG_TO_STREAM _STREAM << log_; return _STREAM;

extern easyloggingpp::internal::Logger _LOGGER;

class LogWriter {
public:
    enum kLogAspect { kNormal,
                      kConditional,
                      kInterval
                    };

    explicit LogWriter(kLogAspect logAspect_,
                       const std::string& logType_,
                       const std::string& severityLevel_,
                       const char* func_,
                       const char* file_,
                       const unsigned long int line_,
                       bool condition_ = true,
                       unsigned int verboseLevel_ = 0,
                       int counter_ = 0) :
        logAspect_(logAspect_),
        logType_(logType_),
        severityLevel_(severityLevel_),
        func_(func_),
        file_(file_),
        line_(line_),
        condition_(condition_),
        verboseLevel_(verboseLevel_),
        counter_(counter_){
        _LOCK_MUTEX;
    }

    ~LogWriter(void) {
        writeLog();
        _UNLOCK_MUTEX;
    }

    inline std::ostream& operator<<(const std::string& log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(char log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(bool log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(signed short log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(unsigned short log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(signed int log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(unsigned int log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(signed long log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(unsigned long log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(float log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(double log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(const char* log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(const void* log_) { _LOG_TO_STREAM }
    inline std::ostream& operator<<(long double log_) { _LOG_TO_STREAM }
private:
    inline void writeLog(void) const {
        if (severityLevel_ == "DEBUG") {
#if (_DEBUG_LOG)
            _WRITE_LOG(logType_, "DEBUG", func_, file_, line_);
#endif
        } else if (severityLevel_ == "WARNING") {
#if (_WARNING_LOG)
            _WRITE_LOG(logType_, "WARNING", func_, file_, line_);
#endif
        } else if (severityLevel_ == "ERROR") {
#if (_ERROR_LOG)
            _WRITE_LOG(logType_, "ERROR", func_, file_, line_);
#endif
        } else if (severityLevel_ == "INFO") {
#if (_INFO_LOG)
            _WRITE_LOG(logType_, "INFO", func_, file_, line_);
#endif
        } else if (severityLevel_ == "FATAL") {
#if (_FATAL_LOG)
            _WRITE_LOG(logType_, "FATAL", func_, file_, line_);
#endif
        } else if (severityLevel_ == "PERFORMANCE") {
#if (_PERFORMANCE_LOG)
            _WRITE_LOG(logType_, "PERFORMANCE", func_, file_, line_);
#endif
        } else if (severityLevel_ == "QA") {
#if (_QA_LOG)
            _WRITE_LOG(logType_, "QA", func_, file_, line_);
#endif
        } else if (severityLevel_ == "VERBOSE") {
#if (_VERBOSE_LOG)
            if (logAspect_ == kNormal && _LOGGER.appVerbose() >= verboseLevel_) {
                _LOGGER.buildLine(logType_, "VERBOSE", func_, file_, line_, verboseLevel_);
            } else if (logAspect_ == kConditional && condition_ && _LOGGER.appVerbose() >= verboseLevel_) {
                _LOGGER.buildLine(logType_, "VERBOSE", func_, file_, line_, verboseLevel_);
            } else if (logAspect_ == kInterval && _LOGGER.appVerbose() >= verboseLevel_) {
                if (_LOGGER.registeredLogCounters()->valid(file_, line_, counter_)) {
                    _LOGGER.buildLine(logType_, "VERBOSE", func_, file_, line_, verboseLevel_);
                }
            }
#endif
        }
        _LOGGER.clear();
    }
    unsigned int logAspect_;
    std::string logType_;
    std::string severityLevel_;
    const char* func_;
    const char* file_;
    const unsigned long int line_;
    bool condition_;
    unsigned int verboseLevel_;
    int counter_;
}; // class LogWriter

} // namespace internal

} // namespace easyloggingpp

//
// Performance tracking macros
//
#if _PERFORMANCE_LOG
#    define START_FUNCTION_LOG "Executing [" << __func__ << "]"
#    define TIME_OUTPUT "Executed [" << __func__ << "] in [~ " <<                                  \
         easyloggingpp::internal::DateUtilities::formatSeconds(                                    \
         difftime(functionEndTime, functionStartTime)) << "]"
#   define FUNC_SUB_COMMON_START {                                                                 \
        if (easyloggingpp::configurations::SHOW_START_FUNCTION_LOG) {                              \
            LPERFORMANCE << START_FUNCTION_LOG;                                                    \
        }                                                                                          \
        time_t functionStartTime, functionEndTime;                                                 \
        time(&functionStartTime);
#    define FUNC_SUB_COMMON_END time(&functionEndTime); LPERFORMANCE << TIME_OUTPUT;
#    define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#    define END_SUB FUNC_SUB_COMMON_END }
#    define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS FUNC_SUB_COMMON_START
#    define RETURN(return_value) FUNC_SUB_COMMON_END return return_value;
#    define END_FUNC(return_value) RETURN(return_value) }
#    define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#    define END_MAIN(return_value) FUNC_SUB_COMMON_END; _END_EASYLOGGINGPP; return return_value; }
#    define RETURN_MAIN(exit_status) _END_EASYLOGGINGPP return exit_status;
#else
#    define SUB(FUNCTION_NAME,PARAMS) void FUNCTION_NAME PARAMS {
#    define END_SUB }
#    define FUNC(RETURNING_TYPE,FUNCTION_NAME,PARAMS) RETURNING_TYPE FUNCTION_NAME PARAMS {
#    define END_FUNC(x) return x; }
#    define RETURN(expr) return expr;
#    define MAIN(argc, argv) FUNC(int, main, (argc, argv))
#    define END_MAIN(x) _END_EASYLOGGINGPP return x; }
#    define RETURN_MAIN(exit_status) _END_EASYLOGGINGPP return exit_status;
#endif // _PERFORMANCE_LOG

namespace easyloggingpp {
namespace helper {

class MyEasyLog {
    // Reads log from current log file an returns standard string
    static std::string readLog(void) {
        _LOCK_MUTEX;
        std::stringstream ss;
        if (::easyloggingpp::configurations::SAVE_TO_FILE) {
            std::ifstream logFileReader(_QUALIFIED_LOGGER.kFinalFilename_.c_str(), std::ifstream::in);
            if (logFileReader.is_open()) {
                std::string line;
                while (logFileReader.good()) {
                    std::getline(logFileReader, line);
                    ss << line << std::endl;
                }
                logFileReader.close();
            } else {
                ss << "Error opening log file [" << _QUALIFIED_LOGGER.kFinalFilename_ << "]";
            }
        } else {
            ss << "Logs are not being saved to file!";
        }
        _UNLOCK_MUTEX;
        return ss.str();
    }
}; // class MyEasyLog
} // namespace helper
} // namespace easyloggingpp
//
// Log writing macros
//
// Normal logs
#define LINFO LogWriter(LogWriter::kNormal,           \
    "TrivialLogger", "INFO", __func__, __FILE__, __LINE__)
#define LWARNING LogWriter(LogWriter::kNormal,        \
    "TrivialLogger", "WARNING", __func__, __FILE__, __LINE__)
#define LDEBUG LogWriter(LogWriter::kNormal,          \
    "TrivialLogger", "DEBUG", __func__, __FILE__, __LINE__)
#define LERROR LogWriter(LogWriter::kNormal,          \
    "TrivialLogger", "ERROR", __func__, __FILE__, __LINE__)
#define LFATAL LogWriter(LogWriter::kNormal,          \
    "TrivialLogger", "FATAL", __func__, __FILE__, __LINE__)
#define LPERFORMANCE LogWriter(LogWriter::kNormal,    \
    "TrivialLogger", "PERFORMANCE", __func__, __FILE__, __LINE__)
#define LQA LogWriter(LogWriter::kNormal,             \
    "TrivialLogger", "QA", __func__, __FILE__, __LINE__)
#define LVERBOSE(level) LogWriter(LogWriter::kNormal, \
    "TrivialLogger", "VERBOSE", __func__, __FILE__, __LINE__, true, level)
// Conditional logs
#define LINFO_IF(condition) LogWriter(LogWriter::kConditional,           \
    "TrivialLogger", "INFO", __func__, __FILE__, __LINE__, condition)
#define LWARNING_IF(condition) LogWriter(LogWriter::kConditional,        \
    "TrivialLogger", "WARNING", __func__, __FILE__, __LINE__, condition)
#define LDEBUG_IF(condition) LogWriter(LogWriter::kConditional,          \
    "TrivialLogger", "DEBUG", __func__, __FILE__, __LINE__, condition)
#define LERROR_IF(condition) LogWriter(LogWriter::kConditional,          \
    "TrivialLogger", "ERROR", __func__, __FILE__, __LINE__, condition)
#define LFATAL_IF(condition) LogWriter(LogWriter::kConditional,          \
    "TrivialLogger", "FATAL", __func__, __FILE__, __LINE__, condition)
#define LPERFORMANCE_IF(condition) LogWriter(LogWriter::kConditional,    \
    "TrivialLogger", "PERFORMANCE", __func__, __FILE__, __LINE__, condition)
#define LQA_IF(condition) LogWriter(LogWriter::kConditional,             \
    "TrivialLogger", "QA", __func__, __FILE__, __LINE__, condition)
#define LVERBOSE_IF(condition, level) LogWriter(LogWriter::kConditional, \
    "TrivialLogger", "VERBOSE", __func__, __FILE__, __LINE__, condition, level)
// Interval logs
#define LINFO_EVERY_N(n) LogWriter(LogWriter::kInterval,                  \
    "TrivialLogger", "INFO", __func__, __FILE__, __LINE__, true, 0, n)
#define LWARNING_EVERY_N(n) LogWriter(LogWriter::kInterval,               \
    "TrivialLogger", "WARNING", __func__, __FILE__, __LINE__, true, 0, n)
#define LDEBUG_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "TrivialLogger", "DEBUG", __func__, __FILE__, __LINE__, true, 0, n)
#define LERROR_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "TrivialLogger", "ERROR", __func__, __FILE__, __LINE__, true, 0, n)
#define LFATAL_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "TrivialLogger", "FATAL", __func__, __FILE__, __LINE__, true, 0, n)
#define LPERFORMANCE_EVERY_N(n) LogWriter(LogWriter::kInterval,           \
    "TrivialLogger", "PERFORMANCE", __func__, __FILE__, __LINE__, true, 0, n)
#define LQA_EVERY_N(n) LogWriter(LogWriter::kInterval,                    \
    "TrivialLogger", "QA", __func__, __FILE__, __LINE__, condition, 0, n)
#define LVERBOSE_EVERY_N(n, level) LogWriter(LogWriter::kInterval,        \
    "TrivialLogger", "VERBOSE", __func__, __FILE__, __LINE__, true, level, n)

// Normal logs (Business)
#define BINFO LogWriter(LogWriter::kNormal,           \
    "BusinessLogger", "INFO", __func__, __FILE__, __LINE__)
#define BWARNING LogWriter(LogWriter::kNormal,        \
    "BusinessLogger", "WARNING", __func__, __FILE__, __LINE__)
#define BDEBUG LogWriter(LogWriter::kNormal,          \
    "BusinessLogger", "DEBUG", __func__, __FILE__, __LINE__)
#define BERROR LogWriter(LogWriter::kNormal,          \
    "BusinessLogger", "ERROR", __func__, __FILE__, __LINE__)
#define BFATAL LogWriter(LogWriter::kNormal,          \
    "BusinessLogger", "FATAL", __func__, __FILE__, __LINE__)
#define BPERFORMANCE LogWriter(LogWriter::kNormal,    \
    "BusinessLogger", "PERFORMANCE", __func__, __FILE__, __LINE__)
#define BQA LogWriter(LogWriter::kNormal,             \
    "BusinessLogger", "QA", __func__, __FILE__, __LINE__)
#define BVERBOSE(level) LogWriter(LogWriter::kNormal, \
    "BusinessLogger", "VERBOSE", __func__, __FILE__, __LINE__, true, level)
// Conditional logs (Business)
#define BINFO_IF(condition) LogWriter(LogWriter::kConditional,           \
    "BusinessLogger", "INFO", __func__, __FILE__, __LINE__, condition)
#define BWARNING_IF(condition) LogWriter(LogWriter::kConditional,        \
    "BusinessLogger", "WARNING", __func__, __FILE__, __LINE__, condition)
#define BDEBUG_IF(condition) LogWriter(LogWriter::kConditional,          \
    "BusinessLogger", "DEBUG", __func__, __FILE__, __LINE__, condition)
#define BERROR_IF(condition) LogWriter(LogWriter::kConditional,          \
    "BusinessLogger", "ERROR", __func__, __FILE__, __LINE__, condition)
#define BFATAL_IF(condition) LogWriter(LogWriter::kConditional,          \
    "BusinessLogger", "FATAL", __func__, __FILE__, __LINE__, condition)
#define BPERFORMANCE_IF(condition) LogWriter(LogWriter::kConditional,    \
    "BusinessLogger", "PERFORMANCE", __func__, __FILE__, __LINE__, condition)
#define BQA_IF(condition) LogWriter(LogWriter::kConditional,             \
    "BusinessLogger", "QA", __func__, __FILE__, __LINE__, condition)
#define BVERBOSE_IF(condition, level) LogWriter(LogWriter::kConditional, \
    "BusinessLogger", "VERBOSE", __func__, __FILE__, __LINE__, condition, level)
// Interval logs (Business)
#define BINFO_EVERY_N(n) LogWriter(LogWriter::kInterval,                  \
    "BusinessLogger", "INFO", __func__, __FILE__, __LINE__, true, 0, n)
#define BWARNING_EVERY_N(n) LogWriter(LogWriter::kInterval,               \
    "BusinessLogger", "WARNING", __func__, __FILE__, __LINE__, true, 0, n)
#define BDEBUG_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "BusinessLogger", "DEBUG", __func__, __FILE__, __LINE__, true, 0, n)
#define BERROR_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "BusinessLogger", "ERROR", __func__, __FILE__, __LINE__, true, 0, n)
#define BFATAL_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "BusinessLogger", "FATAL", __func__, __FILE__, __LINE__, true, 0, n)
#define BPERFORMANCE_EVERY_N(n) LogWriter(LogWriter::kInterval,           \
    "BusinessLogger", "PERFORMANCE", __func__, __FILE__, __LINE__, true, 0, n)
#define BQA_EVERY_N(n) LogWriter(LogWriter::kInterval,                    \
    "BusinessLogger", "QA", __func__, __FILE__, __LINE__, condition, 0, n)
#define BVERBOSE_EVERY_N(n, level) LogWriter(LogWriter::kInterval,        \
    "BusinessLogger", "VERBOSE", __func__, __FILE__, __LINE__, true, level, n)

// Normal logs (Security)
#define SINFO LogWriter(LogWriter::kNormal,           \
    "SecurityLogger", "INFO", __func__, __FILE__, __LINE__)
#define SWARNING LogWriter(LogWriter::kNormal,        \
    "SecurityLogger", "WARNING", __func__, __FILE__, __LINE__)
#define SDEBUG LogWriter(LogWriter::kNormal,          \
    "SecurityLogger", "DEBUG", __func__, __FILE__, __LINE__)
#define SERROR LogWriter(LogWriter::kNormal,          \
    "SecurityLogger", "ERROR", __func__, __FILE__, __LINE__)
#define SFATAL LogWriter(LogWriter::kNormal,          \
    "SecurityLogger","FATAL", __func__, __FILE__, __LINE__)
#define SPERFORMANCE LogWriter(LogWriter::kNormal,    \
    "SecurityLogger", "PERFORMANCE", __func__, __FILE__, __LINE__)
#define SQA LogWriter(LogWriter::kNormal,             \
    "SecurityLogger", "QA", __func__, __FILE__, __LINE__)
#define SVERBOSE(level) LogWriter(LogWriter::kNormal, \
    "SecurityLogger", "VERBOSE", __func__, __FILE__, __LINE__, true, level)
// Conditional logs (Security)
#define SINFO_IF(condition) LogWriter(LogWriter::kConditional,           \
    "SecurityLogger", "INFO", __func__, __FILE__, __LINE__, condition)
#define SWARNING_IF(condition) LogWriter(LogWriter::kConditional,        \
    "SecurityLogger", "WARNING", __func__, __FILE__, __LINE__, condition)
#define SDEBUG_IF(condition) LogWriter(LogWriter::kConditional,          \
    "SecurityLogger", "DEBUG", __func__, __FILE__, __LINE__, condition)
#define SERROR_IF(condition) LogWriter(LogWriter::kConditional,          \
    "SecurityLogger", "ERROR", __func__, __FILE__, __LINE__, condition)
#define SFATAL_IF(condition) LogWriter(LogWriter::kConditional,          \
    "SecurityLogger", "FATAL", __func__, __FILE__, __LINE__, condition)
#define SPERFORMANCE_IF(condition) LogWriter(LogWriter::kConditional,    \
    "SecurityLogger", "PERFORMANCE", __func__, __FILE__, __LINE__, condition)
#define SQA_IF(condition) LogWriter(LogWriter::kConditional,             \
    "SecurityLogger", "QA", __func__, __FILE__, __LINE__, condition)
#define SVERBOSE_IF(condition, level) LogWriter(LogWriter::kConditional, \
    "SecurityLogger", "VERBOSE", __func__, __FILE__, __LINE__, condition, level)
// Interval logs (Security)
#define SINFO_EVERY_N(n) LogWriter(LogWriter::kInterval,                  \
    "SecurityLogger", "INFO", __func__, __FILE__, __LINE__, true, 0, n)
#define SWARNING_EVERY_N(n) LogWriter(LogWriter::kInterval,               \
    "SecurityLogger", "WARNING", __func__, __FILE__, __LINE__, true, 0, n)
#define SDEBUG_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "SecurityLogger", "DEBUG", __func__, __FILE__, __LINE__, true, 0, n)
#define SERROR_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "SecurityLogger", "ERROR", __func__, __FILE__, __LINE__, true, 0, n)
#define SFATAL_EVERY_N(n) LogWriter(LogWriter::kInterval,                 \
    "SecurityLogger", "FATAL", __func__, __FILE__, __LINE__, true, 0, n)
#define SPERFORMANCE_EVERY_N(n) LogWriter(LogWriter::kInterval,           \
    "SecurityLogger", "PERFORMANCE", __func__, __FILE__, __LINE__, true, 0, n)
#define SQA_EVERY_N(n) LogWriter(LogWriter::kInterval,                    \
    "SecurityLogger", "QA", __func__, __FILE__, __LINE__, condition, 0, n)
#define SVERBOSE_EVERY_N(n, level) LogWriter(LogWriter::kInterval,        \
    "SecurityLogger", "VERBOSE", __func__, __FILE__, __LINE__, true, level, n)
//
// Legacy log macros
//
#ifdef _SUPPORT_LEGACY_LOG_NAMES
// Normal logs
#    define DEBUG(log_) LDEBUG << log_;
#    define INFO(log_) LINFO << log_;
#    define WARNING(log_) LWARNING << log_;
#    define ERROR(log_) LERROR << log_;
#    define FATAL(log_) LFATAL << log_;
#    define PERFORMANCE(log_) LPERFORMANCE << log_;
#    define VERBOSE(vlevel_, log_) LVERBOSE(vlevel_) << log_;
#    define QA(log_) LQA << log_;
// Conditional logs
#    define DEBUG_IF(cond_, log_) LDEBUG_IF(cond_) << log_;
#    define INFO_IF(cond_, log_) LINFO_IF(cond_) << log_;
#    define WARNING_IF(cond_, log_) LWARNING_IF(cond_) << log_;
#    define ERROR_IF(cond_, log_) LERROR_IF(cond_) << log_;
#    define FATAL_IF(cond_, log_) LFATAL_IF(cond_) << log_;
#    define PERFORMANCE_IF(cond_, log_) LPERFORMANCE_IF(cond_) << log_;
#    define VERBOSE_IF(cond_, vlevel_, log_) LVERBOSE_IF(cond_, vlevel_) << log_;
#    define QA_IF(cond_, log_) LQA << log_;
// Interval logs
#    define DEBUG_EVERY_N(n_, log_) LDEBUG_EVERY_N(n_) << log_;
#    define INFO_EVERY_N(n_, log_) LINFO_EVERY_N(n_) << log_;
#    define WARNING_EVERY_N(n_, log_) LWARNING_EVERY_N(n_) << log_;
#    define ERROR_EVERY_N(n_, log_) LERROR_EVERY_N(n_) << log_;
#    define FATAL_EVERY_N(n_, log_) LFATAL_EVERY_N(n_) << log_;
#    define PERFORMANCE_EVERY_N(n_, log_) LPERFORMANCE_EVERY_N(n_) << log_;
#    define VERBOSE_EVERY_N(n_, vlevel_, log_) LVERBOSE_EVERY_N(n_, vlevel_) << log_;
#    define QA_EVERY_N(n_, log_) LQA_EVERY_N(n_) << log_;
#endif // _SUPPORT_LEGACY_LOG_NAMES

// When using log levels that require program arguments, for example VERBOSE logs require
// to see what VERBOSE levels to log by looking at --v=X argument or --verbose (for level 9)
// argument, following macro should be used.
#define _START_EASYLOGGINGPP(argc, argv) \
    _LOGGER.setArgs(argc, argv);

#define _INITIALIZE_EASYLOGGINGPP   \
    namespace easyloggingpp {       \
        namespace internal {        \
            Logger _LOGGER;         \
        }                           \
    }

#define _END_EASYLOGGINGPP

using namespace easyloggingpp::internal;

#endif //EASYLOGGINGPP_H
