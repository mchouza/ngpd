#ifndef PROFILING_H
#define PROFILING_H

#include <cassert>
#include <map>
#include <string>

#ifndef MY_PROFILER_STORAGE
#define NO_STORAGE
#include <profiler.hpp>
#undef NO_STORAGE
#else
#include <profiler.hpp>
#endif

/// Para efectuar profiling de la evaluación
class MyProfiler : public boost::prof::basic_profiler<
								boost::prof::empty_logging_policy,
								boost::prof::default_stats_policy,
								boost::high_resolution_timer>
{
public:
	/// Constructor
	MyProfiler(const char* desc) : basic_profiler(desc) {}
};

#endif
