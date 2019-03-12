#ifndef __tree_h_
#define __tree_h_

#include "qtl/vector.h"

#include <stddef.h>

namespace qtl
{
	/// <summary>
	/// Represents a node in a tree. Does not own contents
	/// </summary>
	/// <typeparam name="T">
	/// Type stored in node
	/// </typeparam>
	template <typename T>
	struct tree_node
	{
		T* value;
		tree_node<T>* parent = nullptr;
		qtl::vector<tree_node<T>*> children;
	};

	/// <summary>
	/// Represents a tree. Does not own contents
	/// </summary>
	/// <typeparam name="T">
	/// Type stored in tree
	/// </typeparam>
	template <typename T>
	class tree
	{
	public:
		/// <summary>
		/// Constructs new tree
		/// </summary>
		/// <param name="value">
		/// Value at root
		/// </param>
		tree(T* value = nullptr);

		/// <summary>
		/// Deleted copy constructor
		/// </summary>
		tree(const tree&) = delete;

		/// <summary>
		/// Default move constructor
		/// </summary>
		/// <param name="t">
		/// Tree to move from
		/// </param>
		tree(tree&& t) noexcept;
		
		/// <summary>
		/// Deletes entire tree, but not the contents of the nodes
		/// </summary>
		~tree();

		/// <summary>
		/// Deleted copy assignment
		/// </summary>
		/// <returns>
		/// Reference to this
		/// </returns>
		tree& operator=(const tree&) = delete;

		/// <summary>
		/// Move assignment
		/// </summary>
		/// <param name="t">
		/// Tree to move from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		tree& operator=(tree&& t) noexcept;

		/// <summary>
		/// Adds value to tree
		/// </summary>
		/// <param name="value">
		/// Value to add
		/// </param>
		/// <param name="parent">
		/// Parent node
		/// </param>
		/// <returns>
		/// Node containing value
		/// </returns>
		tree_node<T>* add(T* value, tree_node<T>* parent = nullptr);

		/// <summary>
		/// Recursive remove of the node with the given value, removing
		/// all children of this node as well
		/// </summary>
		/// <param name="value">
		/// Value to remove.  If the tree contains multiple of this value, it will remove the first value found
		/// by a DFS
		/// </param>
		void remove(T* value);

		/// <summary>
		/// Recursive remove of the node, removing all of its children as well
		/// </summary>
		/// <param name="value">
		/// Node to remove
		/// </param>
		void remove(tree_node<T>* value);

		/// <summary>
		/// Searches for the given value in the tree
		/// </summary>
		/// <param name="value">
		/// Value to search for
		/// </param>
		/// <returns>
		/// First node found with matching value by DFS, nullptr if not found
		/// </returns>
		tree_node<T>* search(T* value);

		/// <summary>
		/// Gets a pointer to the root of the tree
		/// </summary>
		/// <returns>
		/// Pointer to root
		/// </returns>
		tree_node<T>* getRoot();
	private:
		tree_node<T>* __root = nullptr;
		size_t __sz;

		void __recursive_delete(tree_node<T>* node);
		tree_node<T>* __recursive_search(tree_node<T>* node, T* value);
	};

	template<typename T>
	inline tree<T>::tree(T * value)
	{
		if (value)
		{
			__root = new tree_node<T>;
			__root->value = value;
		}
	}

	template<typename T>
	inline tree<T>::tree(tree && t) noexcept
	{
		__root = t.__root;
		t.__root = nullptr;
	}

	template<typename T>
	inline tree<T>::~tree()
	{
		if (__root)
		{
			__recursive_delete(__root);
			__root = nullptr;
		}
	}

	template<typename T>
	inline tree<T>& tree<T>::operator=(tree && t) noexcept
	{
		__root = t.__root;
		t.__root = nullptr;
		return *this;
	}

	template<typename T>
	inline tree_node<T>* tree<T>::add(T * value, tree_node<T>* parent)
	{
		tree_node<T>* node = new tree_node<T>;
		node->value = value;
		if (parent)
		{
			parent->children.push_back(node);
			node->parent = parent;
		}
		else
		{
			if (__root)
			{
				node->children.push_back(__root);
				__root->parent = node;
			}
			__root = node;
		}
		return node;
	}

	template<typename T>
	inline void tree<T>::remove(T * value)
	{
		auto node = search(value);
		remove(node);
	}

	template<typename T>
	inline void tree<T>::remove(tree_node<T>* node)
	{
		if (node)
		{
			node->parent->children.erase(qtl::find(node->parent->children.begin(), node->parent->children.end(), node));
			__recursive_delete(node);
		}
	}

	template<typename T>
	inline tree_node<T>* tree<T>::search(T * value)
	{
		return __recursive_search(__root, value);
	}

	template<typename T>
	inline tree_node<T>* tree<T>::getRoot()
	{
		return __root;
	}

	template<typename T>
	inline void tree<T>::__recursive_delete(tree_node<T>* node)
	{
		for (auto child : node->children)
		{
			if (child)
			{
				__recursive_delete(child);
			}
		}
		delete node;
	}
	template<typename T>
	inline tree_node<T>* tree<T>::__recursive_search(tree_node<T>* node, T * value)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->value == value)
		{
			return node;
		}

		for (auto child : node->children)
		{
			auto res = __recursive_search(child, value);
			if (res)
			{
				return res;
			}
		}
		return nullptr;
	}
}

#endif // __tree_h_