#ifndef __treemultimap_h_
#define __treemultimap_h_

#include "qtl/redblack_tree.h"
#include "qtl/vector.h"

#include <stddef.h>

namespace qtl
{
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	namespace qinternal
	{
		template <typename Key, typename Value>
		struct tree_multimap_node
		{
			qtl::pair<Key, qtl::vector<Value>> kv;

			bool operator==(const tree_multimap_node& node) const;
			bool operator!=(const tree_multimap_node& node) const;
			bool operator< (const tree_multimap_node& node) const;
			bool operator> (const tree_multimap_node& node) const;
			bool operator<=(const tree_multimap_node& node) const;
			bool operator>=(const tree_multimap_node& node) const;
		};

		template<typename Key, typename Value>
		tree_multimap_node(Key, Value)->tree_multimap_node<Key, Value>;

		template<typename Key, typename Value>
		class tree_multimap_forward_iterator
		{
		public:
			tree_multimap_forward_iterator(const rb_tree_forward_iterator<qinternal::tree_multimap_node<Key, Value>> & it, const size_t idx);
			tree_multimap_forward_iterator& operator++();

			bool operator!=(const tree_multimap_forward_iterator& other) const;
			bool operator==(const tree_multimap_forward_iterator& other) const;

			pair<Key, Value>& operator*();
			const pair<Key, Value>& operator*() const;
		private:
			rb_tree_forward_iterator<qinternal::tree_multimap_node<Key, Value>> __it;
			size_t __idx;
		};

		template<typename Key, typename Value>
		inline bool tree_multimap_node<Key, Value>::operator==(const tree_multimap_node & node) const
		{
			return kv.first == node.kv.first;
		}

		template<typename Key, typename Value>
		inline bool tree_multimap_node<Key, Value>::operator!=(const tree_multimap_node & node) const
		{
			return kv.first != node.kv.first;
		}

		template<typename Key, typename Value>
		inline bool tree_multimap_node<Key, Value>::operator<(const tree_multimap_node & node) const
		{
			return kv.first < node.kv.first;
		}

		template<typename Key, typename Value>
		inline bool tree_multimap_node<Key, Value>::operator>(const tree_multimap_node & node) const
		{
			return kv.first > node.kv.first;
		}

		template<typename Key, typename Value>
		inline bool tree_multimap_node<Key, Value>::operator<=(const tree_multimap_node & node) const
		{
			return kv.first <= node.kv.first;
		}

		template<typename Key, typename Value>
		inline bool tree_multimap_node<Key, Value>::operator>=(const tree_multimap_node & node) const
		{
			return kv.first >= node.kv.first;
		}

		template<typename Key, typename Value>
		inline tree_multimap_forward_iterator<Key, Value>::tree_multimap_forward_iterator(const rb_tree_forward_iterator<qinternal::tree_multimap_node<Key, Value>>& it, const size_t idx)
		{
			__it = it;
			__idx = idx;
		}

		template<typename Key, typename Value>
		inline tree_multimap_forward_iterator<Key, Value>& tree_multimap_forward_iterator<Key, Value>::operator++()
		{
			__idx++;
			if (__idx >= __it.node->value->second.size())
			{
				__idx = 0;
				++__it;
			}
			return *this;
		}

		template<typename Key, typename Value>
		inline bool tree_multimap_forward_iterator<Key, Value>::operator!=(const tree_multimap_forward_iterator & other) const
		{
			return __it != other.__it || __idx != other.__idx;
		}

		template<typename Key, typename Value>
		inline bool tree_multimap_forward_iterator<Key, Value>::operator==(const tree_multimap_forward_iterator & other) const
		{
			return __it == other.__it && __idx == other.__idx;
		}

		template<typename Key, typename Value>
		inline pair<Key, Value>& tree_multimap_forward_iterator<Key, Value>::operator*()
		{
			return __it.node->value->second[__idx];
		}

		template<typename Key, typename Value>
		inline const pair<Key, Value>& tree_multimap_forward_iterator<Key, Value>::operator*() const
		{
			return __it.node->value->second[__idx];
		}
	}
#endif

	/// <summary>
	/// Multimap sorted by key in a lexigraphical order
	/// </summary>
	/// <typeparam name="Key">
	/// Key type
	/// </typeparam>
	/// <typeparam name="Value">
	/// Value type
	/// </typeparam>
	template <typename Key, typename Value>
	class tree_multimap
	{
	public:
		/// <summary>
		/// Forward iterator type for tree multimap
		/// </summary>
		/// <typeparam name="K">
		/// Key type
		/// </typeparam>
		/// <typeparam name="V">
		/// Value type
		/// </typeparam>
		template<typename K, typename V>
		using forward_iterator = typename qinternal::tree_multimap_forward_iterator<Key, Value>;

		/// <summary>
		/// Constructs empty tree multimap map
		/// </summary>
		tree_multimap();

		/// <summary>
		/// Copy constructor.  Complexity O(n)
		/// </summary>
		/// <param name="other">
		/// Map to copy from
		/// </param>
		tree_multimap(const tree_multimap&) = default;

		/// <summary>
		/// Move constructor.  Complexity O(1)
		/// </summary>
		/// <param name="other">
		/// Map to move from
		/// </param>
		tree_multimap(tree_multimap&&) noexcept = default;

		/// <summary>
		/// Deallocates tree.  Complexity O(n)
		/// </summary>
		~tree_multimap() = default;

		/// <summary>
		/// Copy operator.  Complexity O(n)
		/// </summary>
		/// <param name="other">
		/// Map to copy from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		tree_multimap& operator=(const tree_multimap&) = default;

		/// <summary>
		/// Move operator.  Complexity O(1)
		/// </summary>
		/// <param name="other">
		/// Map to move from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		tree_multimap& operator=(tree_multimap&&) noexcept = default;

		bool operator==(const tree_multimap& other) const;
		bool operator!=(const tree_multimap& other) const;

		/// <summary>
		/// Clears map.  Complexity O(n)
		/// </summary>
		void clear();

		/// <summary>
		/// Erases value from tree
		/// </summary>
		/// <param name="key">
		/// Value to erase
		/// </param>
		void erase(const Key& key);

		/// <summary>
		/// Erases value from tree
		/// </summary>
		/// <param name="key">
		/// Value to erase
		/// </param>
		void erase(Key&& key);

		/// <summary>
		/// Find value in map.  Complexity O(log(n))
		/// </summary>
		/// <param name="key">
		/// Key to search for
		/// </param>
		/// <returns>
		/// Iterator to element found
		/// </returns>
		forward_iterator<Key, Value> find(const Key& key);

		/// <summary>
		/// Inserts value.  Complexity O(log(n))
		/// </summary>
		/// <param name="val">
		/// Pair to insert
		/// </param>
		void insert(const qtl::pair<Key, Value>& kv);

		/// <summary>
		/// Inserts value.  Complexity O(log(n))
		/// </summary>
		/// <param name="val">
		/// Pair to insert
		/// </param>
		void insert(qtl::pair<Key, Value>&& kv);

		/// <summary>
		/// Gets size of the map.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// Number of elements in the map
		/// </returns>
		size_t size() const noexcept;

		/// <summary>
		/// Gets if the map is empty.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// True if map is empty
		/// </returns>
		bool empty() const noexcept;

		/// <summary>
		/// Gets an iterator pointing to the beginning element
		/// </summary>
		/// <returns>
		/// Iterator pointing to beginning element
		/// </returns>
		forward_iterator<Key, Value> begin();

		/// <summary>
		/// Gets an iterator pointing to the beginning element
		/// </summary>
		/// <returns>
		/// Iterator pointing to beginning element
		/// </returns>
		const forward_iterator<Key, Value> begin() const;

		/// <summary>
		/// Gets an iterator pointing to the ending element
		/// </summary>
		/// <returns>
		/// Iterator pointing to ending element
		/// </returns>
		forward_iterator<Key, Value> end();

		/// <summary>
		/// Gets an iterator pointing to the ending element
		/// </summary>
		/// <returns>
		/// Iterator pointing to ending element
		/// </returns>
		const forward_iterator<Key, Value> end() const;
	private:
		size_t __sz;
		qtl::redblack_tree<qinternal::tree_multimap_node<Key, Value>> __tree;
	};

	template<typename Key, typename Value>
	inline tree_multimap<Key, Value>::tree_multimap()
	{
		__sz = 0;
	}
	
	template<typename Key, typename Value>
	inline bool tree_multimap<Key, Value>::operator==(const tree_multimap & other) const
	{
		return __tree == other.__tree;
	}
	
	template<typename Key, typename Value>
	inline bool tree_multimap<Key, Value>::operator!=(const tree_multimap & other) const
	{
		return __tree = other.__tree;
	}
	
	template<typename Key, typename Value>
	inline void tree_multimap<Key, Value>::clear()
	{
		__tree.clear();
		__sz = 0;
	}

	template<typename Key, typename Value>
	inline void tree_multimap<Key, Value>::erase(const Key & key)
	{
		qinternal::tree_multimap_node<Key, Value> node;
		node.kv.first = key;
		auto it = __tree.find(node);
		if (it != __tree.end())
		{
			__sz--;
			__tree.erase(key);
		}
	}

	template<typename Key, typename Value>
	inline void tree_multimap<Key, Value>::erase(Key && key)
	{
		qinternal::tree_multimap_node<Key, Value> node;
		node.kv.first = key;
		auto it = __tree.find(node);
		if (it != __tree.end())
		{
			__sz--;
			__tree.erase(key);
		}
	}

	template<typename Key, typename Value>
	inline typename tree_multimap<Key, Value>::template forward_iterator<Key, Value> tree_multimap<Key, Value>::find(const Key & key)
	{
		qinternal::tree_multimap_node<Key, Value> node;
		node.kv.first = key;
		return tree_multimap<Key, Value>::forward_iterator<Key, Value>(__tree.find(node), 0);
	}

	template<typename Key, typename Value>
	inline void tree_multimap<Key, Value>::insert(const qtl::pair<Key, Value>& kv)
	{
		qinternal::tree_multimap_node<Key, Value> node;
		node.kv.first = kv.first;
		if (__tree.find(node) == __tree.end())
		{
			node.kv.second.push_back(kv.second);
			__tree.insert(node);
		}
		else
		{
			__tree.find(node).node->value->kv.second.push_back(kv.second);
		}
		__sz++;
	}

	template<typename Key, typename Value>
	inline void tree_multimap<Key, Value>::insert(qtl::pair<Key, Value>&& kv)
	{
		qinternal::tree_multimap_node<Key, Value> node;
		node.kv.first = kv.first;
		if (__tree.find(node) == __tree.end())
		{
			node.kv.second.push_back(kv.second);
			__tree.insert(node);
		}
		else
		{
			__tree.find(node).node->value->kv.second.push_back(kv.second);
		}
		__sz++;
	}

	template<typename Key, typename Value>
	inline size_t tree_multimap<Key, Value>::size() const noexcept
	{
		return __sz;
	}

	template<typename Key, typename Value>
	inline bool tree_multimap<Key, Value>::empty() const noexcept
	{
		return __sz == 0;
	}

	template<typename Key, typename Value>
	inline typename tree_multimap<Key, Value>::template forward_iterator<Key, Value> tree_multimap<Key, Value>::begin()
	{
		return forward_iterator<Key, Value>();
	}

	template<typename Key, typename Value>
	inline const typename tree_multimap<Key, Value>::template forward_iterator<Key, Value> tree_multimap<Key, Value>::begin() const
	{
		return forward_iterator<Key, Value>();
	}

	template<typename Key, typename Value>
	inline typename tree_multimap<Key, Value>::template forward_iterator<Key, Value> tree_multimap<Key, Value>::end()
	{
		return forward_iterator<Key, Value>();
	}

	template<typename Key, typename Value>
	inline const typename tree_multimap<Key, Value>::template forward_iterator<Key, Value> tree_multimap<Key, Value>::end() const
	{
		return forward_iterator<Key, Value>();
	}
}

#endif // __treemultimap_h_