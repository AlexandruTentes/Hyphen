#pragma once

#define STRMANIP_H_

#include "IncludeAll.h"
#include "UtilityDataStructures.h"

namespace string_manipulation
{
    //================
    //
    //  Implementing the Array class
    //
    //================

    //Array class creates a dynamic array of any type and stores it s size

    template <typename T>
    class Array : DynamicObject<T>
    {
		public:
			Array();
			Array(T * data, int size);

			~Array();
		private:
    };

    //end of class

    //
    //  GLOBAL VARIABLES
    //

    //end of global variables

    //================
    //
    //  Implementing the namespace functions
    //
    //================

    //function size() returns the size of a sctring

    extern int size(std::string input_str);

    //end of size()

    //function char_to_string() returns a string from a (char *). It's a very bad alternative

    extern std::string char_to_string(const char * input);
    extern std::string char_to_string(char * input);

    //end of size()

    //function split() literally splits a string by a character and returns an Array of strings
    
    extern Array<std::string> split(std::string arr, char c);

    //end of split()

    //
    //  Implementing replace() function which searches all characters to be replaced and replaces them by the given character
    //

    //replace() function returns a string of the original given string but without all aparitions of a given character

    extern std::string replace(std::string arr, std::string to_replace, std::string c);

    //override replace() which replaces all substrings of to_replace[] with a given other string

    extern std::string replace(std::string arr, std::string to_replace[], int len, std::string c);

    //override of replace() which replaces to_replace[] with c[]

    extern std::string replace(std::string arr, std::string to_replace[], int len, std::string c[]);

    //end of replace()

    //replace_duplicate() replaces all duplicates of a string with another given one

    extern std::string replace_duplicate(std::string input_string, std::string to_replace, std::string replace_with);

    //end of replace_duplicate()

    //
    //  file read/write functions
    //

    extern std::string read(std::string str, void(*handler)(std::string &) = 0, short unsigned int to_output = true,
		short unsigned int get_word = false, char by_char1 = '\0', char by_char2 = '\0', char ignore_char = '\0');
    extern std::string read(std::string str, std::string bookmark, int bookmark_no, char eof);

    //a write() function which writes to a give file and a given mode

    extern void write(std::string file, std::string output, std::string mode, bool newline);

    //end of read/write

    //grep() function returns 1 if the key string matches the main string and 0 otherwise

    extern int grep(std::string str, std::string key);
    //end of fstream functions

    //
    //  OPERATOR DECLARATIONS
    //

    // the << declaration

    template <class T>
	std::ostream & operator << (std::ostream & os, Array<T> const & arr)
	{
		std::string output = "";

		for (int i = 0; i < arr.size; i++)
			output += arr.array[i] + (i + 1 != arr.size ? ", " : ";");

		return os << output;
	}

	//end of << declaration

    //end of operator declarations

}

#include "../../src/Templated/Utility/Strmanip.h"