#ifndef __string_h_
#define __string_h_

#include <cstddef>
#include <cstring>

#include "qtl/hash.h"

namespace qtl
{
	class string;
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    namespace qinternal
    {
        class string_forward_iterator
        {
        public:
            string_forward_iterator(const char* data, std::size_t cursor);
            string_forward_iterator& operator++();
            bool operator==(const string_forward_iterator& it) const;
            bool operator!=(const string_forward_iterator& it) const;

            char& operator*();
            const char& operator*() const;
        private:
			friend class qtl::string;
            char* __data;
            std::size_t __cursor;
        };
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

	/// <summary>
	/// Represents a null terminated sequence of characters
	/// </summary>
    class string
    {
    public:
        typedef qinternal::string_forward_iterator forward_iterator;
        typedef const qinternal::string_forward_iterator const_forward_iterator;

		/// <summary>
		/// Constructs an empty string
		/// </summary>
        string();

		/// <summary>
		/// Copy constructor for string
		/// </summary>
		/// <param name="str">
		/// String to copy from
		/// </param>
        string(const string& str);

		/// <summary>
		/// Copies substring of characters in constructor
		/// </summary>
		/// <param name="str">
		/// String to copy from
		/// </param>
		/// <param name="pos">
		/// Position to start copy at
		/// </param>
		/// <param name="len">
		/// Number of characters to copy
		/// </param>
        string(const string& str, std::size_t pos, std::size_t len = npos);

		/// <summary>
		/// Copies a buffer of characters
		/// </summary>
		/// <param name="s">
		/// Buffer of characters to copy it from
		/// </param>
        string(const char * s);

		/// <summary>
		/// Copies a buffer of characters
		/// </summary>
		/// <param name="s">
		/// Buffer of characters to copy it from
		/// </param>
		/// <param name="n">
		/// Number of characters to copy from buffer
		/// </param>
        string(const char * s, std::size_t n);

		/// <summary>
		/// Constructs a string of n of the same characters
		/// </summary>
		/// <param name="n">
		/// Number of characters
		/// </param>
		/// <param name="c">
		/// Character to insert
		/// </param>
        string(std::size_t n, char c);

		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="str">
		/// String to move from
		/// </param>
        string(string&& str) noexcept;

		/// <summary>
		/// Frees heap allocated contents of string
		/// </summary>
        ~string();

		/// <summary>
		/// Copy assignment operator
		/// </summary>
		/// <param name="str">
		/// String to copy from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& operator=(const string& str);

		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <param name="str">
		/// String to move from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& operator=(string&& str) noexcept;

		/// <summary>
		/// Copy assignment operator
		/// </summary>
		/// <param name="str">
		/// String to copy from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		string& operator=(const char * str);

		/// <summary>
		/// Equality operator
		/// </summary>
		/// <param name="other">
		/// String to check equality against
		/// </param>
		/// <returns>
		/// True if contents equal, else false
		/// </returns>
		bool operator==(const qtl::string& other) const;

		/// <summary>
		/// Inequality operator
		/// </summary>
		/// <param name="other">
		/// String to check inequality against
		/// </param>
		/// <returns>
		/// True if contents are not equal, else false
		/// </returns>
		bool operator!=(const qtl::string& other) const;

		/// <summary>
		/// Gets the number of characters in the string
		/// </summary>
		/// <returns>
		/// Number of characters in string
		/// </returns>
        std::size_t size() const noexcept;

		/// <summary>
		/// Gets the number of characters in the string
		/// </summary>
		/// <returns>
		/// Number of characters in string
		/// </returns>
        std::size_t length() const noexcept;

		/// <summary>
		/// Gets the maximum number of characters in a string
		/// </summary>
		/// <returns>
		/// Maximum number of characters in a string
		/// </returns>
        std::size_t max_size() const noexcept;

		/// <summary>
		/// Clears the contents of the string
		/// </summary>
        void clear();

		/// <summary>
		/// Iterator pointing to the beginning of the string
		/// </summary>
		/// <returns>
		/// Iterator for beginning of string
		/// </returns>
        forward_iterator begin();

		/// <summary>
		/// Iterator pointing to the beginning of the string
		/// </summary>
		/// <returns>
		/// Iterator for beginning of string
		/// </returns>
        const forward_iterator begin() const;

		/// <summary>
		/// Iterator pointing to the ending of the string
		/// </summary>
		/// <returns>
		/// Iterator for ending of string
		/// </returns>
        forward_iterator end();

		/// <summary>
		/// Iterator pointing to the ending of the string
		/// </summary>
		/// <returns>
		/// Iterator for ending of string
		/// </returns>
        const forward_iterator end() const;

		/// <summary>
		/// Gets a reference to the character at the given index
		/// </summary>
		/// <param name="idx">
		/// Index of character
		/// </param>
		/// <returns>
		/// Reference to character at given index
		/// </returns>
        char& operator[](std::size_t idx);

		/// <summary>
		/// Gets a reference to the character at the given index
		/// </summary>
		/// <param name="idx">
		/// Index of character
		/// </param>
		/// <returns>
		/// Reference to character at given index
		/// </returns>
        const char& operator[](std::size_t idx) const;

		/// <summary>
		/// Gets a reference to the character at the given index
		/// </summary>
		/// <param name="idx">
		/// Index of character
		/// </param>
		/// <returns>
		/// Reference to character at given index
		/// </returns>
        char& at(std::size_t idx);

		/// <summary>
		/// Gets a reference to the character at the given index
		/// </summary>
		/// <param name="idx">
		/// Index of character
		/// </param>
		/// <returns>
		/// Reference to character at given index
		/// </returns>
        const char& at(std::size_t idx) const;

		/// <summary>
		/// Gets reference to character at the beginning of the string
		/// </summary>
		/// <returns>
		/// Reference to first character
		/// </returns>
        char& front();

		/// <summary>
		/// Gets reference to character at the beginning of the string
		/// </summary>
		/// <returns>
		/// Reference to first character
		/// </returns>
        const char& front() const;

		/// <summary>
		/// Gets reference to character at the ending of the string
		/// </summary>
		/// <returns>
		/// Reference to last character
		/// </returns>
        char& back();

		/// <summary>
		/// Gets reference to character at the ending of the string
		/// </summary>
		/// <returns>
		/// Reference to last character
		/// </returns>
        const char& back() const;

		/// <summary>
		/// Append operator
		/// </summary>
		/// <param name="str">
		/// String to append
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& operator+=(const string& str);

		/// <summary>
		/// Append operator
		/// </summary>
		/// <param name="s">
		/// Character buffer to append
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& operator+=(const char * s);

		/// <summary>
		/// Append operator
		/// </summary>
		/// <param name="c">
		/// Character to append
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& operator+=(char c);

		/// <summary>
		/// Append operator
		/// </summary>
		/// <param name="str">
		/// String to append
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& append(const string& str);

		/// <summary>
		/// Append operator
		/// </summary>
		/// <param name="s">
		/// Character buffer to append
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& append(const char* s);

		/// <summary>
		/// Append operator
		/// </summary>
		/// <param name="c">
		/// Character to append
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& append(char c);

		/// <summary>
		/// Appends character to string
		/// </summary>
		/// <param name="c">
		/// Character to add to string
		/// </param>
        void push_back(char c);

		/// <summary>
		/// Assigns the contents of another string to this
		/// </summary>
		/// <param name="str">
		/// String to assign from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& assign(const string& str);

		/// <summary>
		/// Assigns the contents of another string to this
		/// </summary>
		/// <param name="str">
		/// String to assign from
		/// </param>
		/// <param name="pos">
		/// Start position
		/// </param>
		/// <param name="len">
		/// Length to copy
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& assign(const string& str, std::size_t pos, std::size_t len = npos);

		/// <summary>
		/// Assigns the contents of another string to this
		/// </summary>
		/// <param name="s">
		/// String to assign from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& assign(const char * s);

		/// <summary>
		/// Assigns the contents of another string to this
		/// </summary>
		/// <param name="s">
		/// String to assign from
		/// </param>
		/// <param name="n">
		/// Number of characters to copy
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& assign(const char * s, std::size_t n);

		/// <summary>
		/// Assigns the contents of another string to this
		/// </summary>
		/// <param name="str">
		/// String to assign from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& assign(string&& str) noexcept;

		/// <summary>
		/// Inserts string at position
		/// </summary>
		/// <param name="pos">
		/// Position to insert at
		/// </param>
		/// <param name="str">
		/// String to insert
		/// </param>
		/// <returns>
		/// Reference to this
		/// </param>
        string& insert(std::size_t pos, const string& str);

		/// <summary>
		/// Inserts substring string at position
		/// </summary>
		/// <param name="pos">
		/// Position to insert at
		/// </param>
		/// <param name="str">
		/// String to insert
		/// </param>
		/// <param name="subpos">
		/// Position to start substring at
		/// </param>
		/// <param name="sublen">
		/// Length of substring
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& insert(std::size_t pos, const string& str, std::size_t subpos, std::size_t sublen = npos);

		/// <summary>
		/// Inserts buffer at position
		/// </summary>
		/// <param name="pos">
		/// Position to insert at
		/// </param>
		/// <param name="s">
		/// String to insert
		/// </param>
		/// <returns>
		/// Reference to this
		/// </param>
        string& insert(std::size_t pos, const char* s);

		/// <summary>
		/// Inserts buffer string at position
		/// </summary>
		/// <param name="pos">
		/// Position to insert at
		/// </param>
		/// <param name="s">
		/// String to insert
		/// </param>
		/// <param name="n">
		/// Length of string
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& insert(std::size_t pos, const char* s, std::size_t n);

		/// <summary>
		/// Inserts character string at position
		/// </summary>
		/// <param name="pos">
		/// Position to insert at
		/// </param>
		/// <param name="n">
		/// Number of characters to insert
		/// </param>
		/// <param name="c">
		/// Character to insert
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& insert(std::size_t pos, std::size_t n, char c);

		/// <summary>
		/// Inserts buffer string at position
		/// </summary>
		/// <param name="it">
		/// Beginning interator to insert at
		/// </param>
		/// <param name="c">
		/// Character to insert
		/// </param>
		/// <param name="n">
		/// Length of string
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        forward_iterator insert(const_forward_iterator it, std::size_t n, char c);

		/// <summary>
		/// Inserts character string at position
		/// </summary>
		/// <param name="it">
		/// Beginning interator to insert at
		/// </param>
		/// <param name="c">
		/// Character to insert
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        forward_iterator insert(const_forward_iterator it, char c);

		/// <summary>
		/// Erases characters from string
		/// </summary>
		/// <param name="pos">
		/// Starting position
		/// </param>
		/// <param name="len">
		/// Number of characters to erase
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& erase(std::size_t pos = 0, std::size_t len = npos);

		/// <summary>
		/// Erases a single character from the string
		/// </summary>
		/// <param name="it">
		/// Iterator to character to erase
		/// </param>
		/// <returns>
		/// Iterator to erased character's position
		/// </returns>
        forward_iterator erase(forward_iterator it);

		/// <summary>
		/// Erases a single character from the string
		/// </summary>
		/// <param name="begin">
		/// Iterator to first character to erase
		/// </param>
		/// <param name="end">
		/// Iterator to last character to erase
		/// </param>
		/// <returns>
		/// Iterator to erased character's position
		/// </returns>
        forward_iterator erase(forward_iterator begin, forward_iterator end);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="pos">
		/// Position to replace at
		/// </param>
		/// <param name="len">
		/// Number of characters to replace
		/// </param>
		/// <param name="str">
		/// String to replace with
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(std::size_t pos, std::size_t len, const string& str);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="begin">
		/// Iterator to start replacement at
		/// </param>
		/// <param name="end">
		/// Iterator to end replacement at
		/// </param>
		/// <param name="str">
		/// String to replace with
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(const_forward_iterator begin, const_forward_iterator end, const string& str);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="pos">
		/// Position to replace at
		/// </param>
		/// <param name="len">
		/// Number of characters to replace
		/// </param>
		/// <param name="s">
		/// String to replace with
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(std::size_t pos, std::size_t len, const char * s);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="begin">
		/// Iterator to start replacement at
		/// </param>
		/// <param name="end">
		/// Iterator to end replacement at
		/// </param>
		/// <param name="s">
		/// String to replace with
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(const_forward_iterator begin, const_forward_iterator end, const char * s);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="pos">
		/// Position to replace at
		/// </param>
		/// <param name="len">
		/// Number of characters to replace
		/// </param>
		/// <param name="s">
		/// String to replace with
		/// </param>
		/// <param name="n">
		/// Number of characters from s to replace with
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(std::size_t pos, std::size_t len, const char * s, std::size_t n);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="begin">
		/// Iterator to start replacement at
		/// </param>
		/// <param name="end">
		/// Iterator to end replacement at
		/// </param>
		/// <param name="s">
		/// String to replace with
		/// </param>
		/// <param name="n">
		/// Number of characters to insert from new string
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(const_forward_iterator begin, const_forward_iterator end, const char * s, std::size_t n);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="pos">
		/// Position to start at
		/// </param>
		/// <param name="len">
		/// Iterator to end replacement at
		/// </param>
		/// <param name="n">
		/// Number of characters to insert from new string
		/// </param>
		/// <param name="c">
		/// Character to replace with
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(std::size_t pos, std::size_t len, std::size_t n, char c);

		/// <summary>
		/// Replaces the contents of the string at the provided position
		/// </summary>
		/// <param name="begin">
		/// Iterator to start replacement at
		/// </param>
		/// <param name="end">
		/// Iterator to end replacement at
		/// </param>
		/// <param name="n">
		/// String to replace with
		/// </param>
		/// <param name="c">
		/// Character to replace with
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
        string& replace(const_forward_iterator begin, const_forward_iterator end, std::size_t n, char c);

		/// <summary>
		/// Swaps contents with other string
		/// </summary>
		/// <param name="other">
		/// String to swap with
		/// </param>
        void swap(string& other);
        
		/// <summary>
		/// Removes last character from string
		/// </summary>
        void pop_back();

		/// <summary>
		/// Gets the contents of the string
		/// </summary>
		/// <returns>
		/// Buffer of string
		/// </returns>
        const char * c_str() const;
        
		/// <summary>
		/// Gets the contents of the string
		/// </summary>
		/// <returns>
		/// Buffer of string
		/// </returns>
        const char * data() const noexcept;
        
		/// <summary>
		/// Copies contents of string into the buffer
		/// </summary>
		/// <param name="s">
		/// Location of buffer
		/// </param>
		/// <param name="len">
		/// Length of sequence to copy. 
		/// </param>
		/// <param name="pos">
		/// Position to copy to
		/// </param>
		/// <returns>
		/// Length copied
		/// </returns>
        std::size_t copy(char * s, std::size_t len, std::size_t pos = 0) const;
        
		/// <summary>
		/// Finds string in another string
		/// </summary>
		/// <param name="str">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find(const string& str, std::size_t pos = 0) const noexcept;

		/// <summary>
		/// Finds string in another string
		/// </summary>
		/// <param name="s">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find(const char * s, std::size_t pos = 0) const;

		/// <summary>
		/// Finds string in another string
		/// </summary>
		/// <param name="c">
		/// Character to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find(char c, std::size_t pos = 0) const noexcept;
        
		/// <summary>
		/// Reverse search for string in another string
		/// </summary>
		/// <param name="str">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t rfind(const string& str, std::size_t pos = npos) const noexcept;

		/// <summary>
		/// Reverse search for string in another string
		/// </summary>
		/// <param name="s">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t rfind(const char * s, std::size_t pos = npos) const;

		/// <summary>
		/// Reverse search for character in another string
		/// </summary>
		/// <param name="c">
		/// Character to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t rfind(char c, std::size_t pos = npos) const noexcept;

		/// <summary>
		/// Finds finds first instance of any characters in string in another string
		/// </summary>
		/// <param name="str">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_first_of(const string& str, std::size_t pos = 0) const noexcept;

		/// <summary>
		/// Finds finds first instance of any characters in string in another string
		/// </summary>
		/// <param name="s">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_first_of(const char * s, std::size_t pos = 0) const;

		/// <summary>
		/// Finds finds first instance of character in another string
		/// </summary>
		/// <param name="c">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_first_of(char c, std::size_t pos = 0) const noexcept;
        
		/// <summary>
		/// Finds finds last instance of any characters in string in another string
		/// </summary>
		/// <param name="str">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_last_of(const string& str, std::size_t pos = 0) const noexcept;

		/// <summary>
		/// Finds finds last instance of any characters in string in another string
		/// </summary>
		/// <param name="s">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_last_of(const char * s, std::size_t pos = 0) const;

		/// <summary>
		/// Finds finds last instance of character in another string
		/// </summary>
		/// <param name="c">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_last_of(char c, std::size_t pos = 0) const noexcept;

		/// <summary>
		/// Finds finds first instance not of any characters in string in another string
		/// </summary>
		/// <param name="str">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_first_not_of(const string& str, std::size_t pos = 0) const noexcept;

		/// <summary>
		/// Finds finds first instance not of any characters in string in another string
		/// </summary>
		/// <param name="s">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_first_not_of(const char * s, std::size_t pos = 0) const;

		/// <summary>
		/// Finds finds first instance of character in another string
		/// </summary>
		/// <param name="c">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_first_not_of(char c, std::size_t pos = 0) const noexcept;
        
		/// <summary>
		/// Finds finds last instance not of any characters in string in another string
		/// </summary>
		/// <param name="str">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_last_not_of(const string& str, std::size_t pos = 0) const noexcept;

		/// <summary>
		/// Finds finds last instance not of any characters in string in another string
		/// </summary>
		/// <param name="s">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_last_not_of(const char * s, std::size_t pos = 0) const;

		/// <summary>
		/// Finds finds last instance of character in another string
		/// </summary>
		/// <param name="c">
		/// String to search for
		/// </param>
		/// <param name="pos">
		/// Search start index
		/// </param>
		/// <returns>
		/// Index found at
		/// </returns>
        std::size_t find_last_not_of(char c, std::size_t pos = 0) const noexcept;
        
		/// <summary>
		/// Gets substring of string
		/// </summary>
		/// <param name="pos">
		/// Position to start substring at
		/// </param>
		/// <param name="len">
		/// Length of substring
		/// </param>
		/// <returns>
		/// Substring
		/// </returns>
        string substr(std::size_t pos = 0, std::size_t len = npos) const;
        
		/// <summary>
		/// Performs alphabetic comparison between strings
		/// </summary>
		/// <param name="str">
		/// String to compare against
		/// </param>
		/// <returns>
		/// 0 if equivalent, less than 0 if this comes before str, else greater than 0
		/// </returns>
        int compare(const string& str) const noexcept;

		/// <summary>
		/// Performs alphabetic comparison between strings
		/// </summary>
		/// <param name="pos">
		/// Position to start comparison at
		/// </param>
		/// <param name="len">
		/// Length of substring to compare against
		/// </param>
		/// <param name="str">
		/// String to compare against
		/// </param>
		/// <returns>
		/// 0 if equivalent, less than 0 if this comes before str, else greater than 0
		/// </returns>
        int compare(std::size_t pos, std::size_t len, const string& str) const;

		/// <summary>
		/// Performs alphabetic comparison between strings
		/// </summary>
		/// <param name="pos">
		/// Position to start comparison at
		/// </param>
		/// <param name="len">
		/// Length of substring to compare against
		/// </param>
		/// <param name="str">
		/// String to compare against
		/// </param>
		/// <param name="subpos">
		/// Position in str to start comparison at
		/// </param>
		/// <param name="sublen">
		/// Length of substring in str to compare to
		/// </param>
		/// <returns>
		/// 0 if equivalent, less than 0 if this comes before str, else greater than 0
		/// </returns>
        int compare(std::size_t pos, std::size_t len, const string& str, std::size_t subpos, std::size_t sublen) const;

		/// <summary>
		/// Performs alphabetic comparison between strings
		/// </summary>
		/// <param name="s">
		/// String to compare against
		/// </param>
		/// <returns>
		/// 0 if equivalent, less than 0 if this comes before str, else greater than 0
		/// </returns>
        int compare(const char * s) const;

		/// <summary>
		/// Performs alphabetic comparison between strings
		/// </summary>
		/// <param name="pos">
		/// Position to start comparison at
		/// </param>
		/// <param name="len">
		/// Length of substring to compare against
		/// </param>
		/// <param name="s">
		/// String to compare against
		/// </param>
		/// <returns>
		/// 0 if equivalent, less than 0 if this comes before str, else greater than 0
		/// </returns>
        int compare(std::size_t pos, std::size_t len, const char * s) const;

		/// <summary>
		/// Performs alphabetic comparison between strings
		/// </summary>
		/// <param name="pos">
		/// Position to start comparison at
		/// </param>
		/// <param name="len">
		/// Length of substring to compare against
		/// </param>
		/// <param name="s">
		/// String to compare against
		/// </param>
		/// <param name="n">
		/// Number of characters in s to compare against
		/// </param>
		/// <returns>
		/// 0 if equivalent, less than 0 if this comes before str, else greater than 0
		/// </returns>
        int compare(std::size_t pos, std::size_t len, const char * s, std::size_t n) const;

		/// <summary>
		/// Adds two strings together
		/// </summary>
		/// <param name="left">
		/// Left hand parameter
		/// </param>
		/// <param name="right">
		/// Right hand parameter
		/// </param>
		/// <returns>
		/// Sum to both strings
		/// </returns>
		friend qtl::string operator+(qtl::string left, const qtl::string& right);

		/// <summary>
		/// End position of string
		/// </summary>
        static constexpr const std::size_t npos = static_cast<std::size_t>(-1);
    private:
        char * __data;
        std::size_t __len;

		void __compute_longest_possible_pre_suffix(const char* pattern, const std::size_t pattern_len, std::size_t * lps) const noexcept;
    };

	template<>
	struct hash<string>
	{
		std::size_t operator()(const string& key) const;
	};
}

#endif