#ifndef __barrier_h_
#define __barrier_h_

#if defined ( _WIN32 )
#include <Windows.h>
#elif defined ( __linux__ )
#include <pthread.h>
#endif


namespace qtl
{
	class barrier
	{
#if defined ( _WIN32 )
		typedef LPSYNCHRONIZATION_BARRIER native_handle_type;
#elif defined ( __linux__ )
		typedef pthread_barrier_t * native_handle_type;
#endif
	public:
		barrier(const unsigned int num_threads);
		~barrier();

		void wait();

		native_handle_type native_handle();
	private:
		native_handle_type __handle;
		const unsigned int __num_threads;
	};
}

#endif