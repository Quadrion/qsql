#ifndef __graph_h_
#define __graph_h_

#include "qtl/algorithm.h"
#include "qtl/unordered_set.h"
#include "qtl/vector.h"

namespace qtl
{
	/// <summary>
	/// Represents a node in a graph
	/// </summary>
	/// <typeparam name="T">
	/// Type stored in graph node
	/// </typeparam>
	template<typename T>
	struct graph_node
	{
		T* value;
		qtl::vector<graph_node<T>*> nodes;
	};

	/// <summary>
	/// Represents a graph.  The graph do not own the values stored
	/// by the graph
	/// </summary>
	/// <typeparam name="T">
	/// Type stored in graph
	/// </typeparam>
	template<typename T>
	class graph
	{
	public:
		/// <summary>
		/// Constructs an empty graph
		/// </summary>
		graph();

		/// <summary>
		/// Deleted copy constructor
		/// </summary>
		graph(const graph&) = delete;

		/// <summary>
		/// Default move constructor
		/// </summary>
		graph(graph&&) noexcept = default;

		/// <summary>
		/// Deletes all nodes in graph, but not their stored values
		/// </summary>
		~graph();

		/// <summary>
		/// Deleted copy assignment
		/// </summary>
		/// <returns>
		/// Reference to this
		/// </returns>
		graph& operator=(const graph&) = delete;

		/// <summary>
		/// Default move assignment
		/// </summary>
		/// <returns>
		/// Reference to this
		/// </returns>
		graph& operator=(const graph&&) noexcept = delete;

		/// <summary>
		/// Adds a value to the graph given its inbound and outbound nodes
		/// </summary>
		/// <param name="value">
		/// Value to insert into the graph
		/// </param>
		/// <param name="inbound">
		/// Inbound nodes
		/// </param>
		/// <param name="outbound">
		/// Outbound nodes
		/// </param>
		/// <returns>
		/// Node in graph containing the value
		/// </returns>
		graph_node<T>* add(T* value, qtl::vector<graph_node<T>*> inbound, qtl::vector<graph_node<T>*> outbound);

		/// <summary>
		/// Removes a node from the graph
		/// </summary>
		/// <param name="node">
		/// Node to remove from the graph
		/// </param>
		void remove(graph_node<T>* node);

		/// <summary>
		/// Searchs for a node from the graph
		/// </summary>
		/// <param name="value">
		/// Value to search for in the graph.
		/// </param>
		/// <returns>
		/// First node reached by DFS that has a value
		/// matching the provided value
		/// </returns>
		graph_node<T>* dfs(T* value);

		/// <summary>
		/// Returns a reference to the list of root nodes
		/// </summary>
		/// <returns>
		/// Reference to root nodes 
		/// </returns>
		qtl::unordered_set<graph_node<T>*>& getRoots();
	private:
		qtl::unordered_set<graph_node<T>*> __roots;

		void __dfs(graph_node<T>* node, qtl::unordered_map<graph_node<T>*, bool>& visited);
		void __dfs_remove(graph_node<T>* toRemove, graph_node<T>* node, qtl::unordered_map<graph_node<T>*, bool>& visited);
		graph_node<T>* __dfs_search(T* search, graph_node<T>* node, qtl::unordered_map<graph_node<T>*, bool>& visited);
	};

	template<typename T>
	inline graph<T>::graph()
	{
	}

	template<typename T>
	inline graph<T>::~graph()
	{
		qtl::unordered_map<graph_node<T>*, bool> visited_map;
		for (auto node : __roots)
		{
			__dfs(node, visited_map);
		}

		for (auto it : visited_map)
		{
			delete it.first;
		}
	}

	template<typename T>
	inline graph_node<T>* graph<T>::add(T * value, qtl::vector<graph_node<T>*> inbound, qtl::vector<graph_node<T>*> outbound)
	{
		graph_node<T>* node = new graph_node<T>;

		for (graph_node<T>* conn : inbound)
		{
			conn->nodes.push_back(node);
		}

		if (inbound.empty())
		{
			__roots.insert(node);
		}

		for (graph_node<T>* conn : outbound)
		{
			node->nodes.push_back(conn);
			auto rootIt = __roots.find(conn);
			if (rootIt != __roots.end())
			{
				__roots.erase(conn);
			}
		}

		node->value = value;

		return node;
	}

	template<typename T>
	inline void graph<T>::remove(graph_node<T>* node)
	{
		qtl::unordered_map<graph_node<T>*, bool> visited_map;
		for (auto n : __roots)
		{
			__dfs_remove(node, n, visited_map);
		}
		delete node;
	}

	template<typename T>
	inline graph_node<T>* graph<T>::dfs(T * value)
	{
		qtl::unordered_map<graph_node<T>*, bool> visited_map;
		for (auto n : __roots)
		{
			auto res = __dfs_search(value, n, visited_map);
			if (res)
			{
				return res;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline qtl::unordered_set<graph_node<T>*>& graph<T>::getRoots()
	{
		return __roots;
	}

	template<typename T>
	inline void graph<T>::__dfs(graph_node<T>* node, qtl::unordered_map<graph_node<T>*, bool>& visited)
	{
		visited[node] = true;
		for (auto it : node->nodes)
		{
			if (!visited[it])
			{
				__dfs(it, visited);
			}
		}
	}

	template<typename T>
	inline void graph<T>::__dfs_remove(graph_node<T>* toRemove, graph_node<T>* node, qtl::unordered_map<graph_node<T>*, bool>& visited)
	{
		visited[node] = true;
		for (auto it : node->nodes)
		{
			if (!visited[it])
			{
				__dfs_remove(toRemove, it, visited);
			}
		}
		auto findIt = qtl::find(node->nodes.begin(), node->nodes.end(), toRemove);
		if (findIt != node->nodes.end())
		{
			node->nodes.erase(findIt);
			if (node->nodes.empty())
			{
				__roots.insert(node);
			}
		}
	}

	template<typename T>
	inline graph_node<T>* graph<T>::__dfs_search(T* search, graph_node<T>* node, qtl::unordered_map<graph_node<T>*, bool>& visited)
	{
		visited[node] = true;
		if (search == node->value)
		{
			return node;
		}
		for (auto it : node->nodes)
		{
			if (!visited[it])
			{
				auto res = __dfs_search(search, it, visited);
				if (res)
				{
					return res;
				}
			}
		}
		return nullptr;
	}
}

#endif