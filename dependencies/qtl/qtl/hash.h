#ifndef __hash_h_
#define __hash_h_

#include <cstdint>
#include <cstddef>
#include <stdlib.h>

namespace qtl
{
	inline constexpr size_t shift()
	{
		return (sizeof(size_t) == 8) ? 3 : 2;
	}

	/// <summary>
	/// Hashing template.  To create a specialization, the hash struct
	/// must be inside the qtl namespace.  Inside that struct must be
	/// the function std::size_t operator()(const Type& key) const.
	/// </summary>
	/// <typeparam name="T">
	/// Type of value to be hashed
	/// </typeparam>
	template <typename T>
	struct hash;

	/// <summary>
	/// Specialization for hashing chars
	/// </summary>
	template <>
	struct hash<char>
	{
		/// <summary>
		/// Hash function for char
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const char& key) const;
	};

	/// <summary>
	/// Specialization for hashing unsigned chars
	/// </summary>
	template <>
	struct hash<unsigned char>
	{
		/// <summary>
		/// Hash function for unsigned char
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const unsigned char& key) const;
	};

	/// <summary>
	/// Specialization for hashing shorts
	/// </summary>
	template <>
	struct hash<short>
	{
		/// <summary>
		/// Hash function for short
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const short& key) const;
	};

	/// <summary>
	/// Specialization for hashing unsigned shorts
	/// </summary>
	template <>
	struct hash<unsigned short>
	{
		/// <summary>
		/// Hash function for unsigned short
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const unsigned short& key) const;
	};

	/// <summary>
	/// Specialization for hashing ints
	/// </summary>
	template <>
	struct hash<int>
	{
		/// <summary>
		/// Hash function for int
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const int& key) const;
	};

	/// <summary>
	/// Specialization for hashing unsigned ints
	/// </summary>
	template <>
	struct hash<unsigned int>
	{
		/// <summary>
		/// Hash function for unsigned int
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const unsigned int& key) const;
	};

	/// <summary>
	/// Specialization for hashing longs
	/// </summary>
	template <>
	struct hash<long>
	{
		/// <summary>
		/// Hash function for long
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const long& key) const;
	};

	/// <summary>
	/// Specialization for hashing unsigned longs
	/// </summary>
	template <>
	struct hash<unsigned long>
	{
		/// <summary>
		/// Hash function for unsigned long
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const unsigned long& key) const;
	};

	/// <summary>
	/// Specialization for hashing long longs
	/// </summary>
	template <>
	struct hash<long long>
	{
		/// <summary>
		/// Hash function for long long
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const long long& key) const;
	};

	/// <summary>
	/// Specialization for hashing unsigned long longs
	/// </summary>
	template <>
	struct hash<unsigned long long>
	{
		/// <summary>
		/// Hash function for unsigned long long
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const unsigned long long& key) const;
	};

	/// <summary>
	/// Specialization for hashing pointers
	/// </summary>
	/// <typeparam name="T">
	/// Type of pointer to hash
	/// </typeparam>
	template<typename T>
	struct hash<T*>
	{
		/// <summary>
		/// Hash function pointers
		/// </summary>
		/// <param name="key">
		/// Value to hash
		/// </param>
		/// <returns>
		/// Hashed value
		/// </returns>
		std::size_t operator()(const T* key) const;
	};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
	template<typename T>
	inline std::size_t hash<T*>::operator()(const T* key) const
	{
		return reinterpret_cast<size_t>(key) >> shift();
	}
#endif

	// float, double, and long double implementations not provided, as they should not be
	// used as keys for hashing.  These can be implemented as needed by the user

}

#endif