#ifndef __unorderedset_h_
#define __unorderedset_h_

#include "qtl/hash.h"
#include "qtl/utility.h"

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <new>

namespace qtl
{
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	namespace qinternal
	{
		template <typename Key>
		struct unordered_set_node
		{
			Key key;
			std::size_t probe_count = 0;
			bool is_occupied = false;

			void swap(unordered_set_node & other)
			{
				qtl::swap(key, other.key);
				qtl::swap(probe_count, other.probe_count);
				qtl::swap(is_occupied, other.is_occupied);
			}
		};

		template <typename Key>
		class forward_unordered_set_iterator
		{
			unordered_set_node<Key>* __data;
			std::size_t __cursor;
			std::size_t __capacity;
		public:
			forward_unordered_set_iterator(unordered_set_node<Key>* ptr, std::size_t it, std::size_t cap);
			forward_unordered_set_iterator<Key>& operator++();

			bool operator!=(const forward_unordered_set_iterator<Key>& it) const;
			bool operator==(const forward_unordered_set_iterator<Key>& it) const;

			Key& operator*();
			const Key& operator*() const;

			Key* operator->();
			const Key* operator->() const;
		};

		template<typename Key>
		inline forward_unordered_set_iterator<Key>::forward_unordered_set_iterator(unordered_set_node<Key>* ptr, std::size_t it, std::size_t cap)
			: __data(ptr), __cursor(it), __capacity(cap)
		{
		}

		template<typename Key>
		inline forward_unordered_set_iterator<Key>& forward_unordered_set_iterator<Key>::operator++()
		{
			while (++__cursor < __capacity)
			{
				if (__data[__cursor].is_occupied)
				{
					break;
				}
			}
			return *this;
		}

		template<typename Key>
		inline bool forward_unordered_set_iterator<Key>::operator!=(const forward_unordered_set_iterator<Key>& it) const
		{
			return (__cursor != it.__cursor) || (__data != it.__data);
		}

		template<typename Key>
		inline bool forward_unordered_set_iterator<Key>::operator==(const forward_unordered_set_iterator<Key>& it) const
		{
			return (__cursor == it.__cursor) && (__data == it.__data);
		}

		template<typename Key>
		inline Key& forward_unordered_set_iterator<Key>::operator*()
		{
			return __data[__cursor].key;
		}

		template<typename Key>
		inline const Key& forward_unordered_set_iterator<Key>::operator*() const
		{
			return __data[__cursor].key;
		}

		template<typename Key>
		inline Key* forward_unordered_set_iterator<Key>::operator->()
		{
			return &(__data + __cursor)->key;
		}

		template<typename Key>
		inline const Key* forward_unordered_set_iterator<Key>::operator->() const
		{
			return &(__data + __cursor)->key;
		}

	} // qinternal
#endif

	/// <summary>
	/// Unordered set using hashing scheme for item placement.  Uses robin hood heuristic to reduce
	/// probe sequence length.  The set allows for no duplicate keys.
	/// </summary>
	/// <param name="Key">
	/// Type of value to be stored in the key
	/// </param>
	/// <param name="Hash">
	/// Hashing function to be used.  By default, it is qtl::hash<Key>
	/// </param>
	/// <param name="DefaultSize">
	/// Initial size of the hash set.  By default, it is 8
	/// </param>
	template <typename Key, typename Hash = qtl::hash<Key>, std::size_t DefaultSize = 8>
	class unordered_set
	{
	public:

		/// <summary>
		/// Forward iterator for unordered set. 
		/// </summary>
		/// <typeparam name="K">
		/// Key type
		/// </typeparam>
		/// <typeparam name="V">
		/// Value type
		/// </typeparam>
		template <typename K>
		using forward_iterator = typename qinternal::forward_unordered_set_iterator<K>;

		/// <summary>
		/// Constructs a new, empty unordered set.  Complexity O(1)
		/// </summary>
		unordered_set() noexcept;

		/// <summary>
		/// Copy constructor.  Complexity O(n)
		/// </summary>
		/// <param name="other">
		/// Map to copy from
		/// </param>
		unordered_set(const unordered_set& other);

		/// <summary>
		/// Move constructor.  Complexity O(1)
		/// </summary>
		/// <param name="other">
		/// Map to move from
		/// </param>
		unordered_set(unordered_set&& other) noexcept;

		/// <summary>
		/// Deconstructs an unordered set.  Complexity O(n)
		/// </summary>
		~unordered_set();

		/// <summary>
		/// Copy operator.  Complexity O(n)
		/// </summary>
		/// <param name="other">
		/// Map to copy from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		unordered_set& operator=(const unordered_set& other);

		/// <summary>
		/// Move operator.  Complexity O(1)
		/// </summary>
		/// <param name="other">
		/// Map to move from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		unordered_set& operator=(unordered_set&& other) noexcept;

		/// <summary>
		/// Returns if the set is empty.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// True if set is empty
		/// </returns>
		bool empty() const;

		/// <summary>
		/// Returns size of the set.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// Size of set
		/// </returns>
		std::size_t size() const;

		/// <summary>
		/// Clears the contents from the set.  Complexity O(n)
		/// </summary>
		void clear();

		/// <summary>
		/// Sets the number of buckets in the set when the requested size is greater than the 
		/// current usage.  Average and Worst Case - Complexity O(n), Best Case - Complexity O(1)
		/// </summary>
		/// <param name="newSize">
		/// Requested size
		/// </param>
		void reserve(const std::size_t newSize);

		/// <summary>
		/// Inserts an element into the set.  Best and Average Case - Complexity O(1), Worst Case - Complexity O(n)
		/// </summary>
		/// <param name="pair">
		/// Pair to insert
		/// </param>
		void insert(const Key& pair);

		/// <summary>
		/// Inserts an element into the set.  Best and Average Case - Complexity O(1), Worst Case - Complexity O(n)
		/// </summary>
		/// <param name="pair">
		/// Pair to insert
		/// </param>
		void insert(Key&& pair);

		/// <summary>
		/// Searches for an element in the set.  If the element it found, it has its probe count increased.  If the
		/// probe count is greater than the previous element in the probe sequence, the elements are swapped per the
		/// robin hood heuristic.  Best and average case - Complexity O(1), Worse Case - Complexity O(n)
		/// </summary>
		/// <param name="key">
		/// Key to search for in set
		/// </param>
		/// <returns>
		/// Iterator to element found.  If element not found, returns end iterator
		/// </returns>
		forward_iterator<Key> find(const Key& key);

		/// <summary>
		/// Searches for an element in the set.  If the element it found, it has its probe count increased.  If the
		/// probe count is greater than the previous element in the probe sequence, the elements are swapped per the
		/// robin hood heuristic.  Best and average case - Complexity O(1), Worse Case - Complexity O(n)
		/// </summary>
		/// <param name="key">
		/// Key to search for in set
		/// </param>
		/// <returns>
		/// Iterator to element found.  If element not found, returns end iterator
		/// </returns>
		const forward_iterator<Key> find(const Key& key) const;

		/// <summary>
		/// Erases an element from the set. Best and average case - Complexity O(1), Worse Case - Complexity O(n)
		/// </summary>
		/// <param name="key">
		/// Key value to search for
		/// </param>
		/// <returns>
		/// 0 if element not found
		/// </returns>
		std::size_t erase(const Key& key);

		/// <summary>
		/// Gets an iterator to the first element in the set.  Best and average case - Complexity O(1), Worse Case - Complexity O(n)
		/// </summary>
		/// <returns>
		/// Iterator to first element.
		/// </returns>
		forward_iterator<Key> begin();

		/// <summary>
		/// Gets an iterator to the first element in the set.  Best and average case - Complexity O(1), Worse Case - Complexity O(n)
		/// </summary>
		/// <returns>
		/// Iterator to first element.
		/// </returns>
		const forward_iterator<Key> begin() const;

		/// <summary>
		/// Gets an iterator to the end element in the set.  Best and average case - Complexity O(1), Worse Case - Complexity O(n)
		/// </summary>
		/// <returns>
		/// Iterator to end element.
		/// </returns>
		forward_iterator<Key> end();

		/// <summary>
		/// Gets an iterator to the end element in the set.  Best and average case - Complexity O(1), Worse Case - Complexity O(n)
		/// </summary>
		/// <returns>
		/// Iterator to end element.
		/// </returns>
		const forward_iterator<Key> end() const;
	private:
		static constexpr double __rebalance_factor = 0.7;
		std::size_t __capacity;
		std::size_t __usage;
		qinternal::unordered_set_node<Key>* __data;
		Hash __hasher;

		void __resize(const std::size_t newSize);
		bool __insert(const Key& data, qinternal::unordered_set_node<Key>* buffer, const std::size_t bufferSize);
		bool __insert(Key&& data, qinternal::unordered_set_node<Key>* buffer, const std::size_t bufferSize);
	};

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline unordered_set<Key, Hash, DefaultSize>::unordered_set() noexcept
		: __capacity(DefaultSize), __usage(0), __data(nullptr)
	{
		__resize(__capacity);
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline unordered_set<Key, Hash, DefaultSize>::unordered_set(const unordered_set<Key, Hash, DefaultSize>& other)
		: __capacity(other.__capacity), __usage(0), __data(nullptr)
	{
		__resize(__capacity);
		for (auto it : other)
		{
			insert({ it, it.second });
		}
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline unordered_set<Key, Hash, DefaultSize>::unordered_set(unordered_set<Key, Hash, DefaultSize>&& other) noexcept
		: __capacity(other.__capacity), __usage(other.__usage), __data(other.__data)
	{
		other.__data = nullptr;
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline unordered_set<Key, Hash, DefaultSize>::~unordered_set()
	{
		if (__data)
		{
			clear();
			delete[] reinterpret_cast<char*>(__data);
		}
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline unordered_set<Key, Hash, DefaultSize>& unordered_set<Key, Hash, DefaultSize>::operator=(const unordered_set<Key, Hash, DefaultSize>& other)
	{
		if (__data)
		{
			clear();
			delete[] reinterpret_cast<char*>(__data);
			__data = nullptr;
		}

		reserve(other.__capacity);

		for (auto it : other)
		{
			insert({ it, it.second });
		}

		return *this;
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline unordered_set<Key, Hash, DefaultSize>& unordered_set<Key, Hash, DefaultSize>::operator=(unordered_set<Key, Hash, DefaultSize>&& other) noexcept
	{
		__data = other.__data;
		__usage = other.__usage;
		__capacity = other.__capacity;

		other.__data = nullptr;

		return *this;
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline bool unordered_set<Key, Hash, DefaultSize>::empty() const
	{
		return __usage == 0;
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline std::size_t unordered_set<Key, Hash, DefaultSize>::size() const
	{
		return __usage;
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline void unordered_set<Key, Hash, DefaultSize>::clear()
	{
		for (std::size_t i = 0; i < __capacity; i++)
		{
			auto & v = __data[i];
			if (v.is_occupied)
			{
				using qinternal::unordered_set_node;

				v.~unordered_set_node<Key>();
			}
		}
		__usage = 0;
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline void unordered_set<Key, Hash, DefaultSize>::reserve(const std::size_t newSize)
	{
		if (newSize > __usage)
			__resize(newSize);
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline void unordered_set<Key, Hash, DefaultSize>::insert(const Key& pair)
	{
		if (static_cast<double>(__usage) / static_cast<double>(__capacity) > __rebalance_factor)
		{
			__resize(__capacity * 2);
		}
		if (__insert(pair, __data, __capacity))
		{
			__usage++;
		}
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline void unordered_set<Key, Hash, DefaultSize>::insert(Key&& pair)
	{
		if (static_cast<double>(__usage) / static_cast<double>(__capacity) > __rebalance_factor)
		{
			__resize(__capacity * 2);
		}
		if (__insert(pair, __data, __capacity))
		{
			__usage++;
		}
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline typename unordered_set<Key, Hash, DefaultSize>::template forward_iterator<Key> unordered_set<Key, Hash, DefaultSize>::find(const Key & key)
	{
		const std::size_t hashed = __hasher(key);
		std::size_t idx = fast_mod2(hashed, __capacity); // (hashed) % __capacity;
		if (__data[idx].is_occupied && __data[idx].key == key)
		{
			__data[idx].probe_count++;
			return unordered_set<Key, Hash, DefaultSize>::forward_iterator<Key>(__data, idx, __capacity);
		}

		for (std::size_t i = 0; i < __capacity; i++)
		{
			idx = fast_mod2(hashed + i, __capacity); // (hashed + i) % __capacity;
			if (__data[idx].is_occupied)
			{
				std::size_t next_idx = fast_mod2(hashed + i + 1, __capacity); // (hashed + i + 1) % __capacity;
				if (__data[next_idx].is_occupied && __data[next_idx].key == key)
				{
					__data[next_idx].probe_count++;
					if (__data[next_idx].probe_count > __data[idx].probe_count)
					{
						qtl::swap(__data[next_idx], __data[idx]);
						return unordered_set<Key, Hash, DefaultSize>::forward_iterator<Key>(__data, idx, __capacity);
					}
					else
					{
						return unordered_set<Key, Hash, DefaultSize>::forward_iterator<Key>(__data, next_idx, __capacity);
					}
				}
			}
			else
			{
				break;
			}
		}

		return unordered_set<Key, Hash, DefaultSize>::forward_iterator<Key>(__data, __capacity, __capacity);
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline const typename unordered_set<Key, Hash, DefaultSize>::template forward_iterator<Key> unordered_set<Key, Hash, DefaultSize>::find(const Key & key) const
	{
		const std::size_t hashed = __hasher(key);
		std::size_t idx = fast_mod2(hashed, __capacity); // (hashed) % __capacity;
		if (__data[idx].is_occupied && __data[idx].key == key)
		{
			__data[idx].probe_count++;
			return unordered_set<Key, Hash, DefaultSize>::forward_iterator<Key>(__data, idx, __capacity);
		}

		for (std::size_t i = 0; i < __capacity; i++)
		{
			idx = fast_mod2(hashed + i, __capacity); // (hashed + i) % __capacity;
			if (__data[idx].is_occupied)
			{
				std::size_t next_idx = fast_mod2(hashed + i + 1, __capacity); // (hashed + i + 1) % __capacity;
				if (__data[next_idx].is_occupied && __data[next_idx].key == key)
				{
					__data[next_idx].probe_count++;
					if (__data[next_idx].probe_count > __data[idx].probe_count)
					{
						qtl::swap(__data[next_idx], __data[idx]);
						return unordered_set<Key, Hash, DefaultSize>::forward_iterator<Key>(__data, idx, __capacity);
					}
				}
			}
			else
			{
				break;
			}
		}

		return unordered_set<Key, Hash, DefaultSize>::forward_iterator<Key>(__data, __capacity, __capacity);
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline std::size_t unordered_set<Key, Hash, DefaultSize>::erase(const Key & key)
	{
		const std::size_t hashed = __hasher(key);
		std::size_t remove_loc = __capacity;
		for (std::size_t i = 0; i < __capacity; i++)
		{
			std::size_t search_idx = fast_mod2(hashed + i, __capacity); // (hashed + i) % __capacity;
			if (__data[search_idx].key == key)
			{
				remove_loc = search_idx;
				break;
			}
		}
		if (remove_loc != __capacity)
		{
			using qinternal::unordered_set_node;

			auto it_to_remove = __data[remove_loc];
			it_to_remove.~unordered_set_node<Key>();
			new (__data + remove_loc) unordered_set_node<Key>();
			it_to_remove.is_occupied = false;
			it_to_remove.probe_count = 0;

			std::size_t open_slot = remove_loc;
			std::size_t search_len = 1;

			for (std::size_t i = 1; i < __capacity; i++)
			{
				std::size_t search_idx = fast_mod2(open_slot + i, __capacity); // (open_slot + i) % __capacity;
				if (!__data[search_idx].is_occupied)
				{
					search_len = i;
					break;
				}
			}

			for (std::size_t i = 1; i < search_len; i++)
			{
				std::size_t search_idx = fast_mod2(remove_loc + i, __capacity); // (remove_loc + i) % __capacity;

				const std::size_t hash_v = __hasher(__data[search_idx].key);
				const std::size_t cur_probe_length = search_idx >= hash_v ? (search_idx - hash_v) : (__capacity - (hash_v - search_idx));
				const std::size_t new_probe_length = open_slot >= hash_v ? (open_slot - hash_v) : (__capacity - (hash_v - open_slot));
				if (new_probe_length < cur_probe_length)
				{
					__data[open_slot] = __data[search_idx];
					open_slot = search_idx;

					it_to_remove = __data[search_idx];
					it_to_remove.~unordered_set_node<Key>();
					new (__data + search_idx) unordered_set_node<Key>();
					it_to_remove.is_occupied = false;
					it_to_remove.probe_count = 0;
				}
			}
			__usage--;
		}
		return remove_loc == __capacity ? 0 : 1;
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline typename unordered_set<Key, Hash, DefaultSize>::template forward_iterator<Key> unordered_set<Key, Hash, DefaultSize>::begin()
	{
		std::size_t first = 0;
		while (first < __capacity && !__data[first].is_occupied)
		{
			first++;
		}
		return forward_iterator<Key>(__data, first, __capacity);
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline const typename unordered_set<Key, Hash, DefaultSize>::template forward_iterator<Key> unordered_set<Key, Hash, DefaultSize>::begin() const
	{
		std::size_t first = 0;
		while (first < __capacity && !__data[first].is_occupied)
		{
			first++;
		}
		return forward_iterator<Key>(__data, first, __capacity);
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline typename unordered_set<Key, Hash, DefaultSize>::template forward_iterator<Key> unordered_set<Key, Hash, DefaultSize>::end()
	{
		return forward_iterator<Key>(__data, __capacity, __capacity);
	}

	template<typename Key, typename Hash, std::size_t DefaultSize>
	inline const typename unordered_set<Key, Hash, DefaultSize>::template forward_iterator<Key> unordered_set<Key, Hash, DefaultSize>::end() const
	{
		return forward_iterator<Key>(__data, __capacity, __capacity);
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline void unordered_set<Key, Hash, DefaultSize>::__resize(const std::size_t newSize)
	{
		std::size_t sz = newSize * sizeof(qinternal::unordered_set_node<Key>);
		qinternal::unordered_set_node<Key>* buf = reinterpret_cast<qinternal::unordered_set_node<Key>*>(new char[sz]);
		memset(buf, 0, sz);
		if (__data == nullptr)
		{
			__data = buf;
			return;
		}
		for (std::size_t i = 0; i < __capacity; i++)
		{
			if (__data[i].is_occupied)
			{
				__insert(__data[i].key, buf, newSize);
			}
		}
		delete[] reinterpret_cast<char*>(__data);
		__data = buf;
		__capacity = newSize;
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline bool unordered_set<Key, Hash, DefaultSize>::__insert(const Key& data, qinternal::unordered_set_node<Key>* buffer, const std::size_t bufferSize)
	{
		const std::size_t hashed = __hasher(data);
		for (std::size_t i = 0; i < bufferSize; i++)
		{
			std::size_t idx = fast_mod2(hashed + i, bufferSize); // (hashed + i) % bufferSize;

			if (!buffer[idx].is_occupied)
			{
				// found an open slot
				auto loc = ::new (buffer + idx) qinternal::unordered_set_node<Key>();
				loc->key = data;
				loc->is_occupied = true;
				loc->probe_count = 0;
				return true;
			}
			else
			{
				if (buffer[idx].key == data)
				{
					return false;
				}
			}
			assert(i != bufferSize - 1); // only breaks if the entire set is traversed without finding a slot. THIS SHOULD NEVER HAPPEN
		}
		return false;
	}

	template <typename Key, typename Hash, std::size_t DefaultSize>
	inline bool unordered_set<Key, Hash, DefaultSize>::__insert(Key&& data, qinternal::unordered_set_node<Key>* buffer, const std::size_t bufferSize)
	{
		const std::size_t hashed = __hasher(data);
		for (std::size_t i = 0; i < bufferSize; i++)
		{
			std::size_t idx = fast_mod2(hashed + i, bufferSize); // (hashed + i) % bufferSize;

			if (!buffer[idx].is_occupied)
			{
				// found an open slot
				auto loc = new (buffer + idx) qinternal::unordered_set_node<Key>();
				loc->key = data;
				loc->is_occupied = true;
				loc->probe_count = 0;
				return true;
			}
			else
			{
				if (buffer[idx].key == data)
				{
					return false;
				}
			}
			assert(i != bufferSize - 1); // only breaks if the entire set is traversed without finding a slot. THIS SHOULD NEVER HAPPEN
		}
		return false;
	}

} // qtl

#endif