// Copyright 2007-2010 Baptiste Lepilleur and The JsonCpp Authors
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef CPPTL_JSON_ALLOCATOR_H_INCLUDED
#define CPPTL_JSON_ALLOCATOR_H_INCLUDED

#include <cstring>
#include <memory>

#pragma pack(push, 8)

namespace Json {
template<typename TComObject>
class SecureAllocator {
	public:
		// Type definitions
		using value_type      = TComObject;
		using pointer         = TComObject*;
		using const_pointer   = const TComObject*;
		using reference       = TComObject&;
		using const_reference = const TComObject&;
		using size_type       = std::size_t;
		using difference_type = std::ptrdiff_t;

		/**
		 * Allocate memory for N items using the standard allocator.
		 */
		pointer allocate(size_type n) {
			// allocate using "global operator new"
			return static_cast<pointer>(::operator new(n * sizeof(TComObject)));
		}

		/**
		 * Release memory which was allocated for N items at pointer P.
		 *
		 * The memory block is filled with zeroes before being released.
		 * The pointer argument is tagged as "volatile" to prevent the
		 * compiler optimizing out this critical step.
		 */
		void deallocate(volatile pointer p, size_type n) {
			std::memset(p, 0, n * sizeof(TComObject));
			// free using "global operator delete"
			::operator delete(p);
		}

		/**
		 * Construct an item in-place at pointer P.
		 */
		template<typename... Args>
		void construct(pointer p, Args&&... args) {
			// construct using "placement new" and "perfect forwarding"
			::new (static_cast<void*>(p)) TComObject(std::forward<Args>(args)...);
		}

		size_type max_size() const {
			return size_t(-1) / sizeof(TComObject);
		}

		pointer address( reference x ) const {
			return std::addressof(x);
		}

		const_pointer address( const_reference x ) const {
			return std::addressof(x);
		}

		/**
		 * Destroy an item in-place at pointer P.
		 */
		void destroy(pointer p) {
			// destroy using "explicit destructor"
			p->~TComObject();
		}

		// Boilerplate
		SecureAllocator() {}
		template<typename U> SecureAllocator(const SecureAllocator<U>&) {}
		template<typename U> struct rebind { using other = SecureAllocator<U>; };
};


template<typename TComObject, typename U>
bool operator==(const SecureAllocator<TComObject>&, const SecureAllocator<U>&) {
	return true;
}

template<typename TComObject, typename U>
bool operator!=(const SecureAllocator<TComObject>&, const SecureAllocator<U>&) {
	return false;
}

} //namespace Json

#pragma pack(pop)

#endif // CPPTL_JSON_ALLOCATOR_H_INCLUDED
