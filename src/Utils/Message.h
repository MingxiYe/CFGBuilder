#include<iostream>
using namespace std;

/**
 * Util class to print errors, warning and debug messages
 */
class Message {

private:
    static string ANSI_RESET;
    static string ANSI_YELLOW;
    static bool printDebug;

public:
    /**
     * Prints an error to the stderr
     * @param message printed error
     */
    static void printError(string message) {
        cerr<<message<<endl;
    };

    /**
     * Prints a warning to stdout with a yellow color
     * @param message printed warning
     */
    static void printWarning(string message) {
        cerr<<ANSI_YELLOW + message + ANSI_RESET<<endl;
    };

    /**
     * Prints a message as debug to stdout if the debug option is active
     * @param message
     */
    static void printDebugFun(string message) {
        if (printDebug) {
            cerr<<message<<endl;
        }
    };

    /**
     * Set the debug level
     * @param printDebug true: do print, false: don't print
     */
    static void setPrintDebug(bool printDebug) {
        Message::printDebug = printDebug;
    };

};
