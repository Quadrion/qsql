#ifndef __uniqueptr_h_
#define __uniqueptr_h_

#include <cstddef>

#include "qtl/utility.h"

namespace qtl
{
	template<typename T>
	class unique_ptr
	{
	public:
		/// <summary>
		/// Constructs a new shared pointer object pointing to nullptr.  Complexity O(1)
		/// </summary>
		constexpr unique_ptr() noexcept;

		/// <summary>
		/// Explicitly constructs a shared pointer pointing to nullptr.  Complexity O(1)
		/// </summary>
		constexpr unique_ptr(std::nullptr_t) noexcept;

		/// <summary>
		/// Constructs a shared pointer from a pre-existing pointer.  Assigning a pointer to a shared
		/// pointer gives the shared pointer ownership of the object.  Deleting this pointer after passing
		/// it to the shared pointer is undefined behavior.  Complexity O(1)
		/// </summary>
		/// <param name="ptr">
		/// Pointer to make shared pointer of. 
		/// </param>
		explicit unique_ptr(T* ptr);

		/// <summary>
		/// Constructs a shared pointer from another shared pointer.  Complexity O(1)
		/// </summary>
		unique_ptr(const unique_ptr&) = delete;

		/// <summary>
		/// Moves a shared pointer from another shared pointer.  Complexity O(1)
		/// </summary>
		/// <param name="ptr">
		/// Shared pointer to move
		/// </param>
		unique_ptr(unique_ptr&& ptr) noexcept;

		/// <summary>
		/// Constructs a shared pointer from another shared pointer.  Complexity O(1)
		/// </summary>
		/// <typeparam name="T2">
		/// Type of other shared pointer
		/// </typeparam>
		template<typename T2>
		unique_ptr(const unique_ptr<T2>&) = delete;

		/// <summary>
		/// Constructs a shared pointer from another shared pointer.  Complexity O(1)
		/// </summary>
		/// <typeparam name="T2">
		/// Type of other shared pointer
		/// </typeparam>
		/// <param name="ptr">
		/// Shared pointer to move
		/// </param>
		template<typename T2>
		unique_ptr(unique_ptr<T2>&& ptr) noexcept;

		/// <summary>
		/// Deconstructs shared pointer.  When the reference count is 0,
		/// the owned object is deleted.  Complexity O(1)
		/// </summary>
		virtual ~unique_ptr();

		/// <summary>
		/// Copies a shared pointer from another shared pointer.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// Reference to this
		/// </returns>
		unique_ptr& operator=(const unique_ptr&) = delete;

		/// <summary>
		/// Copies a shared pointer from another shared pointer.  Complexity O(1)
		/// </summary>
		/// <param name="other">
		/// Pointer to move from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		unique_ptr& operator=(unique_ptr&& other) noexcept;

		/// <summary>
		/// Copies a shared pointer from a null pointer.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// Reference to this
		/// </returns>
		unique_ptr& operator=(std::nullptr_t) noexcept;

		/// <summary>
		/// Assigns this value from another shared pointer in the same inheritance hierarchy.  Complexity O(1)
		/// </summary>
		/// <typeparam name="T2">
		/// Type of other pointer to copy from
		/// </typeparam>
		/// <param name="other">
		/// Pointer to copy from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		template<typename T2>
		unique_ptr& operator=(const unique_ptr<T2>& other) = delete;

		/// <summary>
		/// Assigns this value from another shared pointer in the same inheritance hierarchy.  Complexity O(1)
		/// </summary>
		/// <typeparam name="T2">
		/// Type of other pointer to copy from
		/// </typeparam>
		/// <param name="other">
		/// Pointer to move from
		/// </param>
		/// <returns>
		/// Reference to this
		/// </returns>
		template<typename T2>
		unique_ptr& operator=(unique_ptr<T2>&& other) noexcept;

		/// <summary>
		/// Checks if two shared pointers point to the same value.  Complexity O(1)
		/// </summary>
		/// <param name="other">
		/// Pointer to check for equality against
		/// </param>
		/// <returns>
		/// If pointer points to the same value
		/// </returns>
		bool operator==(const unique_ptr& other) const noexcept;

		/// <summary>
		/// Checks if two shared pointers do not point to the same value.  Complexity O(1)
		/// </summary>
		/// <param name="other">
		/// Pointer to check for inequality against
		/// </param>
		/// <returns>
		/// If pointer does not point to the same value
		/// </returns>
		bool operator!=(const unique_ptr& other) const noexcept;

		/// <summary>
		/// Checks if two shared pointers point to the same value.  Complexity O(1)
		/// </summary>
		/// <typeparam name="T2">
		/// Type of other pointer
		/// </typeparam>
		/// <param name="other">
		/// Pointer to check for equality against
		/// </param>
		/// <returns>
		/// If pointer points to the same value
		/// </returns>
		template<typename T2>
		bool operator==(const unique_ptr<T2>& other) const noexcept;

		/// <summary>
		/// Checks if two shared pointers do not point to the same value.  Complexity O(1)
		/// </summary>
		/// </typeparam>
		/// <param name="other">
		/// Pointer to check for equality against
		/// </param>
		/// <param name="other">
		/// Pointer to check for inequality against
		/// </param>
		/// <returns>
		/// If pointer does not point to the same value
		/// </returns>
		template<typename T2>
		bool operator!=(const unique_ptr<T2>& other) const noexcept;

		/// <summary>
		/// Resets this pointer to a nullptr.  Complexity O(1)
		/// </summary>
		void reset() noexcept;

		/// <summary>
		/// Resets this pointer to the supplied pointer.  Shared pointer now owns
		/// the provided pointer.  Operations on this pointer after assignment are undefined
		/// behaviors.  Complexity O(1)
		/// </summary>
		/// <param name="ptr">
		/// Pointer to set shared pointer to
		/// </param>
		void reset(T* ptr);

		/// <summary>
		/// Shared pointer to swap values with.  Complexity O(1)
		/// </summary>
		/// <param name="r">
		/// Pointer to swap with
		/// </param>
		void swap(unique_ptr& r) noexcept;

		/// <summary>
		/// Gets the value pointed to by the shared pointer.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// Pointer to owned object
		/// </returns>
		T* get() const noexcept;

		/// <summary>
		/// Dereferences owned object and returns reference to it.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// Reference to owned object
		/// </returns>
		T& operator*() const noexcept;

		/// <summary>
		/// Gets owned object and returns pointer to it.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// Pointer to owned object
		/// </returns>
		T* operator->() const noexcept;

		/// <summary>
		/// Returns if the shared pointer points to a valid, non null resource.  Complexity O(1)
		/// </summary>
		/// <returns>
		/// True if object owned is valid and non null, else false
		/// </returns>
		explicit operator bool() const noexcept;
	private:
		T* pointer = nullptr;

		template <typename T2>
		friend class unique_ptr;
	};

	template<typename T, typename ... Arguments>
	qtl::unique_ptr<T> make_unique(Arguments && ... args) {
		return unique_ptr<T>(new T(qtl::forward<Arguments>(args)...));
	}

	template<typename T>
	inline constexpr unique_ptr<T>::unique_ptr() noexcept
	{
		pointer = nullptr;
	}

	template<typename T>
	inline constexpr unique_ptr<T>::unique_ptr(std::nullptr_t) noexcept
		: unique_ptr<T>()
	{
	}

	template<typename T>
	inline unique_ptr<T>::unique_ptr(T * ptr)
		: unique_ptr<T>()
	{
		pointer = ptr;
	}

	template<typename T>
	inline unique_ptr<T>::unique_ptr(unique_ptr&& ptr) noexcept
	{
		pointer = ptr.pointer;
		ptr.pointer = nullptr;
	}

	template<typename T>
	template<typename T2>
	inline unique_ptr<T>::unique_ptr(unique_ptr<T2>&& ptr) noexcept
	{
		pointer = reinterpret_cast<T>(ptr.pointer);
		ptr.pointer = nullptr;
	}

	template<typename T>
	inline unique_ptr<T>::~unique_ptr()
	{
		if (pointer)
		{
			delete pointer;
		}
	}

	template<typename T>
	inline unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& other) noexcept
	{
		if (pointer)
		{
			delete pointer;
		}
		pointer = other.pointer;
		other.pointer = nullptr;
		return *this;
	}

	template<typename T>
	inline unique_ptr<T>& unique_ptr<T>::operator=(std::nullptr_t) noexcept
	{
		if (pointer)
		{
			delete pointer;
		}
		pointer = nullptr;
		return *this;
	}

	template<typename T>
	inline bool unique_ptr<T>::operator==(const unique_ptr & other) const noexcept
	{
		return pointer == other.pointer;
	}

	template<typename T>
	inline bool unique_ptr<T>::operator!=(const unique_ptr & other) const noexcept
	{
		return pointer != other.pointer;
	}

	template<typename T>
	template <typename T2>
	inline bool unique_ptr<T>::operator==(const unique_ptr<T2> & other) const noexcept
	{
		return pointer == other.pointer;
	}

	template<typename T>
	template <typename T2>
	inline bool unique_ptr<T>::operator!=(const unique_ptr<T2> & other) const noexcept
	{
		return pointer != other.pointer;
	}

	template <typename T>
	template <typename T2>
	inline unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T2>&& other) noexcept
	{
		if (pointer)
		{
			delete pointer;
		}
		pointer = other.pointer;
		other.pointer = nullptr;
		return *this;
	}

	template<typename T>
	inline void unique_ptr<T>::reset() noexcept
	{
		if (pointer)
		{
			delete pointer;
		}
		pointer = nullptr;
	}

	template<typename T>
	inline void unique_ptr<T>::reset(T * ptr)
	{
		if (pointer)
		{
			delete pointer;
		}
		pointer = nullptr;
	}

	template<typename T>
	inline void unique_ptr<T>::swap(unique_ptr & r) noexcept
	{
		auto tmp = pointer;
		pointer = r.pointer;
		r.pointer = tmp;
	}

	template<typename T>
	inline T * unique_ptr<T>::get() const noexcept
	{
		return pointer;
	}

	template<typename T>
	inline T & unique_ptr<T>::operator*() const noexcept
	{
		return *(pointer);
	}

	template<typename T>
	inline T * unique_ptr<T>::operator->() const noexcept
	{
		return get();
	}

	template<typename T>
	inline unique_ptr<T>::operator bool() const noexcept
	{
		return pointer != nullptr;
	}
} // qtl 

#endif // __uniqueptr_h_
