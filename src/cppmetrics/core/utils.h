/*
 * Copyright 2000-2014 NeuStar, Inc. All rights reserved.
 * NeuStar, the Neustar logo and related names and logos are registered
 * trademarks, service marks or tradenames of NeuStar, Inc. All other
 * product names, company names, marks, logos and symbols may be trademarks
 * of their respective owners.
 */

/*
 * utils.h
 *
 *  Created on: Jun 12, 2014
 *      Author: vpoliboy
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <chrono>
#include <locale>
#include <ctime>
#include <string>
#include <sstream>
#include "cppmetrics/core/types.h"

namespace cppmetrics {
namespace core {

inline std::uint64_t get_millis_from_epoch() {
	auto now = std::chrono::system_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	return dur.count();
}

inline std::uint64_t get_seconds_from_epoch() {
	auto now = std::chrono::system_clock::now();
	auto dir = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
	return dir.count();
}

inline std::string utc_timestamp(const std::locale& current_locale) {
	std::locale loc(current_locale);

	std::time_t timestamp;
	std::time ( &timestamp );

	const std::time_put<char>& time_put = std::use_facet< std::time_put<char> > (loc);

	std::stringstream s;
	s.imbue(loc);

	std::tm *localized_time = std::localtime(&timestamp);

	std::string pattern("%d-%M-%y %H:%M:%S%F %Q");
	time_put.put(s, s, ' ', localized_time, pattern.data(), pattern.data() + pattern.length());

	return s.str();

//    std::ostringstream ss;
//    // assumes std::cout's locale has been set appropriately for the entire app
//    boost::posix_time::time_facet* t_facet(new boost::posix_time::time_facet());
//    t_facet->time_duration_format("%d-%M-%y %H:%M:%S%F %Q");
//    ss.imbue(std::locale(current_locale, t_facet));
//    ss << boost::posix_time::microsec_clock::universal_time();
//    return ss.str();
}

}
}

#endif /* UTILS_H_ */
